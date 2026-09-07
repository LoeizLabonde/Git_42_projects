
# Build WordPress from a pinned base OS instead of using a prebuilt application image.
# This installs and configures the web server and PHP at build time so the image is fully
# defined by our Dockerfile and `.env` pins.
ARG BASE_OS=debian:12-slim
ARG WORDPRESS_VERSION=6.5.3
FROM ${BASE_OS}

# Install required packages: PHP-FPM and commonly required PHP extensions,
# wget/unzip to download WordPress, and cleanup apt lists afterwards to reduce image size.
 RUN apt-get update \
 && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
 	 php-fpm \
 	 php-cli \
 	 php-mysql \
 	 php-xml \
 	 php-mbstring \
 	 php-curl \
 	 php-zip \
 	 wget \
 	 curl \
 	 ca-certificates \
 	 tar \
 	 unzip \
 && rm -rf /var/lib/apt/lists/*

# No Apache: we run php-fpm only. Web server (nginx) will serve HTTP and forward PHP to php-fpm.

# Prefer a local tarball placed in the build context (`wordpress.tar.gz`) to avoid
# relying on network fetch during `docker build`. For reproducible builds, place a
# pinned WordPress archive in `srcs/requirements/wordpress/wordpress.tar.gz`.
# We keep a copy in /usr/src/wordpress so wp-init.sh can populate empty volumes.
COPY wordpress.tar.gz /tmp/wordpress.tar.gz
RUN mkdir -p /var/www/html /usr/src/wordpress \
 && tar -xzf /tmp/wordpress.tar.gz -C /tmp \
 && rm /tmp/wordpress.tar.gz \
 && cp -a /tmp/wordpress/* /usr/src/wordpress/ \
 && rm -rf /var/www/html/* \
 && mv /tmp/wordpress/* /var/www/html/ \
 && chown -R www-data:www-data /var/www/html /usr/src/wordpress

# Configure php-fpm pool to listen on TCP 0.0.0.0:9000 so nginx (in a separate container)
# can connect to it over the Docker network. Also add explicit `env[...]` entries
# so only the required environment variables are passed to php-fpm children.
RUN for f in /etc/php/*/fpm/pool.d/www.conf; do \
	  sed -i "s|^listen = .*|listen = 0.0.0.0:9000|" "$f" || true; \
	  sed -i "s/^;*clear_env\s*=.*/clear_env = yes/" "$f" || true; \
	  sed -i '/^env\[/d' "$f" || true; \
	    printf '%s\n' 'env[WORDPRESS_DB_HOST] = $WORDPRESS_DB_HOST' >> "$f"; \
	    printf '%s\n' 'env[WORDPRESS_DB_USER] = $WORDPRESS_DB_USER' >> "$f"; \
	    printf '%s\n' 'env[WORDPRESS_DB_PASSWORD] = $WORDPRESS_DB_PASSWORD' >> "$f"; \
	    printf '%s\n' 'env[WORDPRESS_DB_NAME] = $WORDPRESS_DB_NAME' >> "$f"; \
    done

# Install WP-CLI (phar) and a small init script that performs an idempotent
# `wp core install` at container start. This keeps installations reproducible
# and automates first-run setup when the DB is ready. The `wp-init.sh` script
# will be copied into the image and run as the container entrypoint.
RUN curl -fsSL https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar -o /usr/local/bin/wp \
 && chmod +x /usr/local/bin/wp \
 && chown root:root /usr/local/bin/wp

# Copy our custom wp-config.php to both locations
COPY wp-config.php /usr/src/wordpress/wp-config.php
COPY wp-config.php /var/www/html/wp-config.php
RUN chown www-data:www-data /usr/src/wordpress/wp-config.php /var/www/html/wp-config.php

COPY wp-init.sh /usr/local/bin/wp-init.sh
RUN chmod +x /usr/local/bin/wp-init.sh

# Expose php-fpm port (FastCGI) and run php-fpm in foreground.
EXPOSE 9000
# Run the init script which ensures WP is installed, then exec php-fpm in foreground.
ENTRYPOINT ["/usr/local/bin/wp-init.sh"]
# Use the explicit php-fpm8.2 binary available on Debian 12 base image.
CMD ["/usr/sbin/php-fpm8.2", "-F"]
