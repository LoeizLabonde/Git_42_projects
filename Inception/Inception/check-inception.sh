#!/bin/bash
# Script de vérification complète du projet Inception (42)
# Vérifie la conformité avec les exigences du sujet

set -e

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo "╔════════════════════════════════════════════════════════════════╗"
echo "║          VERIFICATION PROJET INCEPTION (42)                    ║"
echo "╚════════════════════════════════════════════════════════════════╝"

ERRORS=0
WARNINGS=0

check_pass() { echo -e "${GREEN}✓${NC} $1"; }
check_fail() { echo -e "${RED}✗${NC} $1"; ((ERRORS++)); }
check_warn() { echo -e "${YELLOW}⚠${NC} $1"; ((WARNINGS++)); }
check_info() { echo -e "${BLUE}ℹ${NC} $1"; }

# ═══════════════════════════════════════════════════════════════════
# 1. STRUCTURE DU PROJET
# ═══════════════════════════════════════════════════════════════════
echo -e "\n${BLUE}[1] STRUCTURE DU PROJET${NC}"

# Makefile obligatoire
if [ -f "Makefile" ]; then
    check_pass "Makefile présent"
    # Vérifier les règles obligatoires
    if grep -q "^up:" Makefile || grep -q "^all:" Makefile; then
        check_pass "Règle de démarrage présente"
    else
        check_fail "Aucune règle 'up' ou 'all' dans Makefile"
    fi
    if grep -q "^down:" Makefile || grep -q "^clean:" Makefile; then
        check_pass "Règle d'arrêt présente"
    else
        check_warn "Aucune règle 'down' ou 'clean' dans Makefile"
    fi
else
    check_fail "Makefile MANQUANT (obligatoire)"
fi

# Structure srcs/
if [ -d "srcs" ]; then
    check_pass "Dossier srcs/ présent"
else
    check_fail "Dossier srcs/ MANQUANT"
fi

# docker-compose.yml dans srcs/ OU racine
if [ -f "srcs/docker-compose.yml" ] || [ -f "docker-compose.yml" ]; then
    check_pass "docker-compose.yml présent"
    COMPOSE_FILE=$([ -f "srcs/docker-compose.yml" ] && echo "srcs/docker-compose.yml" || echo "docker-compose.yml")
else
    check_fail "docker-compose.yml MANQUANT"
fi

# .env obligatoire
if [ -f "srcs/.env" ] || [ -f ".env" ]; then
    check_pass "Fichier .env présent"
    ENV_FILE=$([ -f "srcs/.env" ] && echo "srcs/.env" || echo ".env")
else
    check_fail "Fichier .env MANQUANT (obligatoire)"
fi

# ═══════════════════════════════════════════════════════════════════
# 2. SERVICES DOCKER (3 containers minimum)
# ═══════════════════════════════════════════════════════════════════
echo -e "\n${BLUE}[2] SERVICES DOCKER${NC}"

if command -v docker-compose &> /dev/null; then
    # Vérifier que les containers tournent
    RUNNING=$(docker-compose ps --services --filter "status=running" 2>/dev/null | wc -l)
    if [ "$RUNNING" -ge 3 ]; then
        check_pass "$RUNNING services en cours d'exécution"
    else
        check_fail "Seulement $RUNNING services actifs (minimum 3 requis)"
    fi
    
    # Vérifier services spécifiques
    for service in nginx mariadb wordpress; do
        if docker-compose ps --services | grep -q "^${service}$"; then
            if docker-compose ps --filter "status=running" | grep -q "$service"; then
                check_pass "Service $service actif"
            else
                check_fail "Service $service existe mais n'est pas actif"
            fi
        else
            check_fail "Service $service MANQUANT"
        fi
    done
else
    check_fail "docker-compose non installé"
fi

# ═══════════════════════════════════════════════════════════════════
# 3. NGINX (TLSv1.2 ou TLSv1.3 uniquement)
# ═══════════════════════════════════════════════════════════════════
echo -e "\n${BLUE}[3] NGINX - Point d'entrée unique (port 443)${NC}"

# Port 443 exposé
NGINX_PORTS=$(docker port nginx 2>/dev/null | grep "443/tcp" | wc -l)
if [ "$NGINX_PORTS" -gt 0 ]; then
    check_pass "Port 443 exposé"
    # Vérifier qu'aucun autre port n'est exposé (sauf 443)
    OTHER_PORTS=$(docker port nginx 2>/dev/null | grep -v "443/tcp" | wc -l)
    if [ "$OTHER_PORTS" -eq 0 ]; then
        check_pass "Aucun autre port exposé (443 seul)"
    else
        check_warn "Autres ports exposés détectés (devrait être 443 uniquement)"
    fi
else
    check_fail "Port 443 NON exposé"
fi

# Test connexion HTTPS
if curl -skI https://localhost/ 2>&1 | grep -q "HTTP/2"; then
    check_pass "NGINX répond en HTTPS"
else
    check_fail "NGINX ne répond pas en HTTPS"
fi

# Vérification TLS v1.2/1.3
TLS_VERSION=$(echo | openssl s_client -connect localhost:443 -brief 2>&1 | grep "Protocol version" | awk '{print $3}')
if [[ "$TLS_VERSION" == "TLSv1.2" ]] || [[ "$TLS_VERSION" == "TLSv1.3" ]]; then
    check_pass "TLS version: $TLS_VERSION (conforme)"
else
    check_fail "TLS version: $TLS_VERSION (doit être 1.2 ou 1.3)"
fi

# Vérifier config nginx
if docker-compose exec nginx test -f /etc/nginx/conf.d/default.conf 2>/dev/null; then
    if docker-compose exec nginx grep -q "ssl_protocols.*TLSv1\.[23]" /etc/nginx/conf.d/default.conf 2>/dev/null; then
        check_pass "Configuration TLS présente dans nginx"
    else
        check_warn "Configuration TLS non trouvée dans nginx.conf"
    fi
fi

# ═══════════════════════════════════════════════════════════════════
# 4. WORDPRESS + PHP-FPM
# ═══════════════════════════════════════════════════════════════════
echo -e "\n${BLUE}[4] WORDPRESS + PHP-FPM${NC}"

# WordPress installé
if docker-compose exec wordpress test -f /var/www/html/wp-config.php 2>/dev/null; then
    check_pass "WordPress installé (wp-config.php présent)"
else
    check_fail "WordPress NON installé"
fi

# PHP-FPM actif
if docker-compose exec wordpress pgrep php-fpm >/dev/null 2>&1; then
    check_pass "PHP-FPM en cours d'exécution"
else
    check_fail "PHP-FPM non actif"
fi

# Deux utilisateurs WordPress (admin + un autre)
WP_USERS=$(docker-compose exec wordpress wp user list --allow-root --path=/var/www/html --format=count 2>/dev/null || echo "0")
if [ "$WP_USERS" -ge 2 ]; then
    check_pass "$WP_USERS utilisateurs WordPress (minimum 2)"
    
    # Vérifier que l'admin n'est pas nommé admin/Admin/administrator
    ADMIN_USER=$(docker-compose exec wordpress wp user list --allow-root --path=/var/www/html --role=administrator --field=user_login 2>/dev/null | head -1)
    if [[ ! "$ADMIN_USER" =~ ^[Aa]dmin(istrator)?$ ]]; then
        check_pass "Nom admin valide: '$ADMIN_USER' (pas 'admin')"
    else
        check_fail "Nom admin INVALIDE: '$ADMIN_USER' (interdit)"
    fi
else
    check_fail "Seulement $WP_USERS utilisateur(s) (minimum 2 requis)"
fi

# ═══════════════════════════════════════════════════════════════════
# 5. MARIADB
# ═══════════════════════════════════════════════════════════════════
echo -e "\n${BLUE}[5] MARIADB${NC}"

# MariaDB actif
if docker-compose exec mariadb mysqladmin ping -h 127.0.0.1 --silent 2>/dev/null; then
    check_pass "MariaDB répond au ping"
else
    check_fail "MariaDB ne répond pas"
fi

# Base de données WordPress existe
if docker-compose exec mariadb mysql -u root -p"$(cat secrets/mysql_root_password 2>/dev/null || echo '')" -e "SHOW DATABASES LIKE 'wordpress';" 2>/dev/null | grep -q wordpress; then
    check_pass "Base de données 'wordpress' existe"
else
    check_fail "Base de données 'wordpress' MANQUANTE"
fi

# Tables WordPress présentes
WP_TABLES=$(docker-compose exec mariadb mysql -u root -p"$(cat secrets/mysql_root_password 2>/dev/null || echo '')" wordpress -e "SHOW TABLES;" 2>/dev/null | grep wp_ | wc -l)
if [ "$WP_TABLES" -ge 10 ]; then
    check_pass "$WP_TABLES tables WordPress détectées"
else
    check_warn "Seulement $WP_TABLES tables WordPress (attendu ~12)"
fi

# ═══════════════════════════════════════════════════════════════════
# 6. VOLUMES (persistance des données - Docker volumes uniquement)
# ═══════════════════════════════════════════════════════════════════
echo -e "\n${BLUE}[6] PERSISTANCE DES DONNÉES${NC}"

# Vérifier si volumes Docker (PAS de bind mounts)
WP_MOUNT_TYPE=$(docker inspect wordpress --format='{{range .Mounts}}{{if eq .Destination "/var/www/html"}}{{.Type}}{{end}}{{end}}' 2>/dev/null)
DB_MOUNT_TYPE=$(docker inspect mariadb --format='{{range .Mounts}}{{if eq .Destination "/var/lib/mysql"}}{{.Type}}{{end}}{{end}}' 2>/dev/null)

# Vérifier WordPress
if [ "$WP_MOUNT_TYPE" = "volume" ]; then
    WP_VOLUME_NAME=$(docker inspect wordpress --format='{{range .Mounts}}{{if eq .Destination "/var/www/html"}}{{.Name}}{{end}}{{end}}' 2>/dev/null)
    if docker volume ls | grep -q "$WP_VOLUME_NAME"; then
        check_pass "Volume WordPress: $WP_VOLUME_NAME (Docker volume)"
    else
        check_fail "Volume WordPress MANQUANT"
    fi
elif [ "$WP_MOUNT_TYPE" = "bind" ]; then
    WP_BIND_SOURCE=$(docker inspect wordpress --format='{{range .Mounts}}{{if eq .Destination "/var/www/html"}}{{.Source}}{{end}}{{end}}' 2>/dev/null)
    check_fail "Bind mount WordPress détecté: $WP_BIND_SOURCE (utiliser un volume Docker)"
else
    check_fail "Aucune persistance pour WordPress"
fi

# Vérifier MariaDB
if [ "$DB_MOUNT_TYPE" = "volume" ]; then
    DB_VOLUME_NAME=$(docker inspect mariadb --format='{{range .Mounts}}{{if eq .Destination "/var/lib/mysql"}}{{.Name}}{{end}}{{end}}' 2>/dev/null)
    if docker volume ls | grep -q "$DB_VOLUME_NAME"; then
        check_pass "Volume MariaDB: $DB_VOLUME_NAME (Docker volume)"
    else
        check_fail "Volume MariaDB MANQUANT"
    fi
elif [ "$DB_MOUNT_TYPE" = "bind" ]; then
    DB_BIND_SOURCE=$(docker inspect mariadb --format='{{range .Mounts}}{{if eq .Destination "/var/lib/mysql"}}{{.Source}}{{end}}{{end}}' 2>/dev/null)
    check_fail "Bind mount MariaDB détecté: $DB_BIND_SOURCE (utiliser un volume Docker)"
else
    check_fail "Aucune persistance pour MariaDB"
fi

# Vérifier que les montages sont effectifs (contiennent des données)
WP_FILES=$(docker exec wordpress sh -c 'ls -A /var/www/html 2>/dev/null | wc -l' 2>/dev/null || echo "0")
DB_FILES=$(docker exec mariadb sh -c 'ls -A /var/lib/mysql 2>/dev/null | wc -l' 2>/dev/null || echo "0")

if [ "$WP_FILES" -gt 5 ]; then
    check_pass "WordPress data présente ($WP_FILES fichiers/dossiers)"
else
    check_warn "WordPress data vide ou manquante"
fi

if [ "$DB_FILES" -gt 5 ]; then
    check_pass "MariaDB data présente ($DB_FILES fichiers/dossiers)"
else
    check_warn "MariaDB data vide ou manquante"
fi

# ═══════════════════════════════════════════════════════════════════
# 7. NETWORK
# ═══════════════════════════════════════════════════════════════════
echo -e "\n${BLUE}[7] NETWORK DOCKER${NC}"

# Network inception existe
if docker network ls | grep -q "inception"; then
    check_pass "Network inception existe"
    
    # Vérifier que les 3 containers sont sur le même réseau  
    NETWORK_NAME="inception_net"
    CONTAINERS_IN_NET=$(docker network inspect "$NETWORK_NAME" -f '{{len .Containers}}' 2>/dev/null || echo "0")
    if [ "$CONTAINERS_IN_NET" -ge 3 ]; then
        check_pass "$CONTAINERS_IN_NET containers sur le réseau inception"
    else
        check_warn "Seulement $CONTAINERS_IN_NET containers sur le réseau"
    fi
else
    check_fail "Network inception MANQUANT"
fi

# ═══════════════════════════════════════════════════════════════════
# 8. DOCKERFILES (pas de :latest, images de base uniquement)
# ═══════════════════════════════════════════════════════════════════
echo -e "\n${BLUE}[8] DOCKERFILES${NC}"

# Vérifier :latest
if find srcs/requirements -name "Dockerfile" -exec grep -l ":latest" {} \; | grep -q .; then
    check_fail "Tag ':latest' trouvé dans Dockerfile(s) (INTERDIT)"
else
    check_pass "Aucun tag ':latest' dans Dockerfiles"
fi

# Vérifier images de base (debian/alpine)
for dockerfile in srcs/requirements/*/Dockerfile; do
    if [ -f "$dockerfile" ]; then
        SERVICE=$(basename $(dirname "$dockerfile"))
        # Résoudre ARG BASE_OS si présent
        BASE_ARG=$(grep "^ARG BASE_OS=" "$dockerfile" | cut -d'=' -f2)
        FROM_LINE=$(grep "^FROM" "$dockerfile" | head -1 | awk '{print $2}')
        # Remplacer ${BASE_OS} par sa valeur
        FROM_IMAGE=${FROM_LINE/\$\{BASE_OS\}/$BASE_ARG}
        
        if echo "$FROM_IMAGE" | grep -qE "debian|alpine"; then
            check_pass "$SERVICE: Image de base Debian/Alpine ($FROM_IMAGE)"
        else
            check_warn "$SERVICE: Image '$FROM_IMAGE' (pas debian/alpine standard)"
        fi
        
        # Vérifier pas d'images toutes faites (nginx:alpine, etc.)
        if echo "$FROM_IMAGE" | grep -qE "^(nginx|wordpress|mariadb|mysql):"; then
            check_fail "$SERVICE: Utilise une image toute faite (INTERDIT)"
        fi
    fi
done

# Vérifier pas de mots de passe en dur (pas de valeurs hardcodées)
if find srcs/requirements -name "Dockerfile" -exec grep -iE "password.*=.*['\"][a-zA-Z0-9]+['\"]" {} + | grep -v "^#" | grep -v '\$' | grep -q .; then
    check_fail "Mots de passe en dur détectés dans Dockerfile(s)"
else
    check_pass "Aucun mot de passe en dur dans Dockerfiles"
fi

# ═══════════════════════════════════════════════════════════════════
# 9. DOCKER SECRETS / VARIABLES D'ENVIRONNEMENT
# ═══════════════════════════════════════════════════════════════════
echo -e "\n${BLUE}[9] SECRETS & VARIABLES D'ENVIRONNEMENT${NC}"

# Vérifier que .env n'est pas dans git
if [ -f ".gitignore" ] && grep -q "\.env" .gitignore; then
    check_pass ".env dans .gitignore"
else
    check_warn ".env pas dans .gitignore (risque de fuite)"
fi

# Vérifier Docker secrets ou variables d'environnement
if grep -q "secrets:" "$COMPOSE_FILE" 2>/dev/null; then
    check_pass "Docker secrets configurés"
else
    check_warn "Docker secrets non utilisés (variables d'env ?)"
fi

# Vérifier que secrets/ existe
if [ -d "secrets" ]; then
    check_pass "Dossier secrets/ présent"
    SECRET_COUNT=$(find secrets -type f ! -name "README*" | wc -l)
    check_info "$SECRET_COUNT fichiers secrets détectés"
fi

# ═══════════════════════════════════════════════════════════════════
# 10. RESTART POLICY
# ═══════════════════════════════════════════════════════════════════
echo -e "\n${BLUE}[10] RESTART POLICY${NC}"

# Vérifier restart policy
for service in nginx mariadb wordpress; do
    RESTART=$(docker inspect "$service" --format='{{.HostConfig.RestartPolicy.Name}}' 2>/dev/null || echo "none")
    if [[ "$RESTART" == "unless-stopped" ]] || [[ "$RESTART" == "always" ]]; then
        check_pass "$service: restart=$RESTART"
    else
        check_warn "$service: restart=$RESTART (recommandé: unless-stopped)"
    fi
done

# ═══════════════════════════════════════════════════════════════════
# 11. TESTS FONCTIONNELS
# ═══════════════════════════════════════════════════════════════════
echo -e "\n${BLUE}[11] TESTS FONCTIONNELS${NC}"

# Test WordPress accessible
WP_STATUS=$(curl -skI https://localhost/ | head -1 | grep -oE "[0-9]{3}")
if [[ "$WP_STATUS" == "200" ]] || [[ "$WP_STATUS" == "301" ]]; then
    check_pass "WordPress accessible (HTTP $WP_STATUS)"
else
    check_fail "WordPress non accessible (HTTP $WP_STATUS)"
fi

# Test connexion MariaDB depuis WordPress (si WP fonctionne, la DB est accessible)
# WordPress ne peut pas fonctionner sans connexion DB, donc si HTTP 200, la DB est OK
if [ "$WP_STATUS" = "200" ]; then
    check_pass "WordPress peut contacter MariaDB (site fonctionnel)"
else
    check_warn "Impossible de vérifier connexion DB (WordPress non accessible)"
fi

# Test healthchecks
HEALTHY=$(docker-compose ps --format json 2>/dev/null | grep -o '"Health":"healthy"' | wc -l)
if [ "$HEALTHY" -ge 2 ]; then
    check_pass "$HEALTHY containers healthy"
else
    check_warn "Seulement $HEALTHY containers healthy"
fi

# ═══════════════════════════════════════════════════════════════════
# RÉSUMÉ FINAL
# ═══════════════════════════════════════════════════════════════════
echo ""
echo "╔════════════════════════════════════════════════════════════════╗"
echo "║                      RÉSUMÉ FINAL                              ║"
echo "╚════════════════════════════════════════════════════════════════╝"

if [ $ERRORS -eq 0 ] && [ $WARNINGS -eq 0 ]; then
    echo -e "${GREEN}✓ PROJET CONFORME - Aucun problème détecté${NC}"
    exit 0
elif [ $ERRORS -eq 0 ]; then
    echo -e "${YELLOW}⚠ PROJET OK avec $WARNINGS avertissement(s)${NC}"
    exit 0
else
    echo -e "${RED}✗ $ERRORS ERREUR(S) CRITIQUE(S) détectée(s)${NC}"
    [ $WARNINGS -gt 0 ] && echo -e "${YELLOW}⚠ $WARNINGS avertissement(s)${NC}"
    exit 1
fi
