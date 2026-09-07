#!/bin/sh
set -e

# Idempotent WordPress installer run by the container at startup.
# It waits for the database to be reachable, then uses WP-CLI to check if
# WordPress is installed; if not, it runs `wp core install` using environment
# variables (with sensible defaults for local development).

# Defaults (override via docker-compose/.env)
: "${WORDPRESS_DB_HOST:=mariadb}"
: "${WORDPRESS_DB_PORT:=3306}"
: "${WP_SITE_URL:=https://llabonde.42.fr}"
: "${WP_SITE_TITLE:=InceptionSite}"
: "${WP_ADMIN_USER:=llabonde}"
: "${WP_ADMIN_PASSWORD:=SecurePass123!}"
: "${WP_ADMIN_PASSWORD_FILE:=}"
: "${WP_ADMIN_EMAIL:=llabonde@student.42.fr}"
: "${WP_USER2_LOGIN:=editor}"
: "${WP_USER2_EMAIL:=editor@example.com}"
: "${WP_USER2_PASSWORD:=EditorPass123!}"

# Wait for DB to be accept connections (using php socket test)
echo "[wp-init] Waiting for database ${WORDPRESS_DB_HOST}:${WORDPRESS_DB_PORT} (TCP) ..."
tries=0
# First wait for TCP port to be open (longer timeout to tolerate slow DB startup)
until php -r "if(@fsockopen('${WORDPRESS_DB_HOST}', ${WORDPRESS_DB_PORT})) exit(0); exit(1);" >/dev/null 2>&1; do
  tries=$((tries+1))
  if [ "$tries" -ge 180 ]; then
    echo "[wp-init] Timeout waiting for database TCP port" >&2
    exit 1
  fi
  sleep 1
done

echo "[wp-init] Database TCP reachable, verifying credentials and database..."

# Next, confirm that the configured credentials can actually connect to the database
# (use a short retry loop for transient auth errors while DB finishes init).
cred_tries=0
until php -r '
  $host = getenv("WORDPRESS_DB_HOST") ?: "mariadb:3306";
  $parts = explode(":", $host);
  $h = $parts[0];
  $port = isset($parts[1]) ? $parts[1] : 3306;
  $db = getenv("WORDPRESS_DB_NAME") ?: getenv("MYSQL_DATABASE");
  $user = getenv("WORDPRESS_DB_USER") ?: getenv("MYSQL_USER");
  $pass = getenv("WORDPRESS_DB_PASSWORD") ?: getenv("MYSQL_PASSWORD");
  $ok = @mysqli_connect($h, $user, $pass, $db);
  exit($ok ? 0 : 1);
' >/dev/null 2>&1; do
  cred_tries=$((cred_tries+1))
  if [ "$cred_tries" -ge 30 ]; then
    echo "[wp-init] Unable to authenticate to database after retries" >&2
    exit 1
  fi
  sleep 1
done

echo "[wp-init] Database reachable and credentials valid"

# If /var/www/html is empty (fresh volume), copy WordPress files from image
if [ ! -f /var/www/html/index.php ]; then
  echo "[wp-init] WordPress files not found in volume, checking for backup..."
  if [ -d /usr/src/wordpress ]; then
    echo "[wp-init] Copying WordPress files from /usr/src/wordpress..."
    cp -a /usr/src/wordpress/* /var/www/html/
  else
    echo "[wp-init] ERROR: No WordPress source files found!" >&2
    exit 1
  fi
fi

# Ensure correct ownership so WP-CLI can write files when necessary.
chown -R www-data:www-data /var/www/html || true

# Move to webroot
cd /var/www/html

# If wp-config.php expects env vars, WP-CLI will use them.
# If a password file is provided, prefer it over WP_ADMIN_PASSWORD env var.
if [ -n "${WP_ADMIN_PASSWORD_FILE}" ] && [ -f "${WP_ADMIN_PASSWORD_FILE}" ]; then
  # Support simple KEY=VALUE format and look for WP_ADMIN_PASSWORD or ADMIN_PASSWORD
  p=$(grep -E '^(WP_ADMIN_PASSWORD|ADMIN_PASSWORD)=' "${WP_ADMIN_PASSWORD_FILE}" | head -n1 | cut -d'=' -f2-)
  if [ -n "$p" ]; then
    WP_ADMIN_PASSWORD="$p"
  fi
fi

# Run wp core is-installed to check. Use --allow-root to run as root inside container.
if /usr/local/bin/wp core is-installed --allow-root >/dev/null 2>&1; then
  echo "[wp-init] WordPress already installed"
  # Ensure site URL uses the canonical HTTPS value we want for this environment.
  if current_siteurl=$(/usr/local/bin/wp option get siteurl --allow-root 2>/dev/null); then
    if [ "$current_siteurl" != "${WP_SITE_URL}" ]; then
      echo "[wp-init] Updating siteurl/home to ${WP_SITE_URL}"
      /usr/local/bin/wp option update home "${WP_SITE_URL}" --allow-root >/dev/null 2>&1 || true
      /usr/local/bin/wp option update siteurl "${WP_SITE_URL}" --allow-root >/dev/null 2>&1 || true
    fi
  fi
else
  echo "[wp-init] WordPress not installed, running core install"
  /usr/local/bin/wp core install \
    --url="${WP_SITE_URL}" \
    --title="${WP_SITE_TITLE}" \
    --admin_user="${WP_ADMIN_USER}" \
    --admin_password="${WP_ADMIN_PASSWORD}" \
    --admin_email="${WP_ADMIN_EMAIL}" \
    --skip-email \
    --allow-root
  echo "[wp-init] WordPress installation finished"
fi

# Ensure second user exists (idempotent)
if ! /usr/local/bin/wp user get "${WP_USER2_LOGIN}" --allow-root >/dev/null 2>&1; then
  echo "[wp-init] Creating second user: ${WP_USER2_LOGIN}"
  /usr/local/bin/wp user create \
    "${WP_USER2_LOGIN}" \
    "${WP_USER2_EMAIL}" \
    --role=editor \
    --user_pass="${WP_USER2_PASSWORD}" \
    --allow-root
  echo "[wp-init] Second user created"
else
  echo "[wp-init] Second user ${WP_USER2_LOGIN} already exists"
fi

# Ensure debug log exists and is writable
mkdir -p wp-content
touch wp-content/debug.log || true
chown www-data:www-data wp-content/debug.log || true

# Exec the original command (Apache foreground)
exec "$@"
