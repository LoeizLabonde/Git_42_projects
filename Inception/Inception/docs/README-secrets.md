# Secrets (Docker Compose secrets)

This project uses Docker Compose secrets to securely pass sensitive data (database passwords, admin passwords) to containers.

Important:
- `secrets/` is ignored by Git via `.gitignore`. Do NOT commit this directory to version control.
- Secrets are mounted automatically by Docker Compose at `/run/secrets/` inside containers (read-only).
- The entrypoint scripts read secrets from `/run/secrets/` files.

Secret files (place under `secrets/`):
- `wp_admin_password` — WordPress admin user password (plain text)
- `mysql_password` — WordPress database user password
- `mysql_root_password` — MariaDB root password

Declared in `docker-compose.yml`:
```yaml
secrets:
  mysql_root_password:
    file: ./secrets/mysql_root_password
  mysql_password:
    file: ./secrets/mysql_password
  wp_admin_password:
    file: ./secrets/wp_admin_password
```

How to rotate passwords:
1. Stop the services: `docker-compose down`
2. Update the secret file (e.g. `echo "NewPassword" > secrets/wp_admin_password`)
3. Restart with clean volumes: `docker-compose up -d -V`
4. Update WordPress password via wp-cli:
   ```bash
   docker-compose exec wordpress wp user update llabonde --user_pass="NewPassword" --allow-root --path=/var/www/html
   ```

Security note:
- This approach uses Docker Compose secrets for local development.
- Files are plaintext but only accessible inside containers at `/run/secrets/`.
- For production, use Docker Swarm secrets, Kubernetes secrets, or a secrets manager (HashiCorp Vault, AWS Secrets Manager).

