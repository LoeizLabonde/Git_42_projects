# Build MariaDB from a pinned base OS and install the mariadb-server package.
ARG BASE_OS=debian:12-slim
FROM ${BASE_OS}

# Install MariaDB server and client. We avoid using a pre-built database image and
# instead install the server package so we manage initialization ourselves.
RUN apt-get update \
 && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    mariadb-server \
    mariadb-client \
    pwgen \
    procps \
 && rm -rf /var/lib/apt/lists/* \
 && rm -rf /var/lib/mysql/*

# Create an entrypoint that initializes the database directory (when empty), sets the
# root password and creates the requested database and user. This is a minimal development-grade
# initializer — for production, consider using the official images which include battle-tested
# initialization logic and secure defaults.
COPY docker-entrypoint.sh /usr/local/bin/docker-entrypoint.sh
RUN chmod +x /usr/local/bin/docker-entrypoint.sh

VOLUME ["/var/lib/mysql"]

EXPOSE 3306

ENTRYPOINT ["/usr/local/bin/docker-entrypoint.sh"]
# Use `mysqld_safe` as the default command. `mysqld_safe` is a wrapper that
# launches `mysqld` under the correct unprivileged user and handles restarts.
# Running `mysqld` directly as PID 1 may cause MariaDB to abort because it detects
# it's being executed as root; using `mysqld_safe` follows the distribution
# recommended way for daemon startup inside containers.
CMD ["mysqld_safe"]
