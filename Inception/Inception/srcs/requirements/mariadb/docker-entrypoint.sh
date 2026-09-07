#!/bin/sh
set -e

# Minimal MariaDB entrypoint for development use.
# - Initializes the database directory if empty
# - Starts mysqld in the background to run initial SQL statements
# - Sets root password and creates a database/user if variables are provided

DATADIR=/var/lib/mysql

# Ensure runtime socket directory exists and is writable by the mysql user.
# mysqld expects /run/mysqld to exist for the Unix socket. Containers often start
# with an empty /run; creating and chowning it prevents "No such file or directory" errors.
mkdir -p /run/mysqld
chown mysql:mysql /run/mysqld || true

# Ensure MariaDB listens on all interfaces so other containers on the compose
# network can connect. Default Debian package sets `bind-address = 127.0.0.1`.
# Create a small conf file under `/etc/mysql/mariadb.conf.d/` which takes
# precedence and forces binding to 0.0.0.0.
cat > /etc/mysql/mariadb.conf.d/99-docker.cnf <<'CNF'
[mysqld]
bind-address = 0.0.0.0
CNF
chown mysql:mysql /etc/mysql/mariadb.conf.d/99-docker.cnf || true

if [ ! -d "$DATADIR/mysql" ]; then
  echo "[entrypoint] Initializing MariaDB data directory"
  mariadb-install-db --user=mysql --datadir="$DATADIR" --skip-test-db --auth-root-authentication-method=normal

  # Start temporary server with skip-grant-tables to allow initial setup
  echo "[entrypoint] Starting temporary server with skip-grant-tables"
  mariadbd --user=mysql --datadir="$DATADIR" --skip-grant-tables --skip-networking --socket=/run/mysqld/mysqld.sock &
  pid="$!"
  echo "[entrypoint] Temporary server PID: $pid"

  # Wait for server to be ready
  i=0
  while [ $i -lt 30 ]; do
    if [ -S /run/mysqld/mysqld.sock ]; then
      echo "[entrypoint] Socket exists, testing connection"
      if mysql -uroot --socket=/run/mysqld/mysqld.sock -e "SELECT 1" >/dev/null 2>&1; then
        echo "[entrypoint] Temporary MariaDB server is ready"
        break
      else
        echo "[entrypoint] Socket exists but connection failed, waiting..."
      fi
    fi
    i=$((i+1))
    sleep 1
  done

  if [ $i -ge 30 ]; then
    echo "[entrypoint] ERROR: Timeout waiting for temporary server" >&2
    exit 1
  fi

  # Run initial SQL
  MYSQL_ROOT_PASSWORD=${MYSQL_ROOT_PASSWORD:-}
  MYSQL_DATABASE=${MYSQL_DATABASE:-}
  MYSQL_USER=${MYSQL_USER:-}
  MYSQL_PASSWORD=${MYSQL_PASSWORD:-}

  # Prefer password files if provided in /run/secrets (mounted as read-only by compose)
  if [ -n "${MYSQL_ROOT_PASSWORD_FILE:-}" ] && [ -f "${MYSQL_ROOT_PASSWORD_FILE}" ]; then
    MYSQL_ROOT_PASSWORD=$(cat "${MYSQL_ROOT_PASSWORD_FILE}")
  elif [ -f "/run/secrets/mysql_root_password" ]; then
    MYSQL_ROOT_PASSWORD=$(cat /run/secrets/mysql_root_password)
  fi

  if [ -n "${MYSQL_PASSWORD_FILE:-}" ] && [ -f "${MYSQL_PASSWORD_FILE}" ]; then
    MYSQL_PASSWORD=$(cat "${MYSQL_PASSWORD_FILE}")
  elif [ -f "/run/secrets/mysql_password" ]; then
    MYSQL_PASSWORD=$(cat /run/secrets/mysql_password)
  fi

  # Re-enable grant tables and run all SQL initialization in one batch
  echo "[entrypoint] Running SQL initialization commands"
  cat <<-EOSQL | mysql --protocol=socket --socket=/run/mysqld/mysqld.sock
		FLUSH PRIVILEGES;
		$([ -n "$MYSQL_ROOT_PASSWORD" ] && echo "ALTER USER 'root'@'localhost' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';")
		$([ -n "$MYSQL_DATABASE" ] && echo "CREATE DATABASE IF NOT EXISTS \`$MYSQL_DATABASE\`;")
		$([ -n "$MYSQL_USER" ] && [ -n "$MYSQL_PASSWORD" ] && echo "CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}'; GRANT ALL PRIVILEGES ON \`$MYSQL_DATABASE\`.* TO '${MYSQL_USER}'@'%';")
		FLUSH PRIVILEGES;
	EOSQL
  
  echo "[entrypoint] Database initialization complete"

  # Shutdown temporary server
  kill "$pid"
  wait "$pid" 2>/dev/null || true
fi

exec "$@"
