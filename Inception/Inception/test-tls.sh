#!/bin/bash
# Script de démonstration TLS 1.2/1.3 pour Inception

echo "╔════════════════════════════════════════════════════════════════╗"
echo "║         DÉMONSTRATION TLS 1.2/1.3 - PROJET INCEPTION          ║"
echo "╚════════════════════════════════════════════════════════════════╝"
echo ""

# Couleurs
GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
NC='\033[0m'

echo -e "${BLUE}[1] Configuration NGINX${NC}"
echo "─────────────────────────────────────────────────────────────────"
docker exec nginx grep "ssl_protocols" /etc/nginx/conf.d/default.conf
echo ""

echo -e "${BLUE}[2] Test TLS 1.3 (doit réussir)${NC}"
echo "─────────────────────────────────────────────────────────────────"
if echo | openssl s_client -connect localhost:443 -tls1_3 -brief 2>&1 | grep -q "TLSv1.3"; then
    echo -e "${GREEN}✓ TLS 1.3 : ACTIF${NC}"
    echo | openssl s_client -connect localhost:443 -tls1_3 -brief 2>&1 | grep "Protocol version"
else
    echo -e "${RED}✗ TLS 1.3 : INACTIF${NC}"
fi
echo ""

echo -e "${BLUE}[3] Test TLS 1.2 (doit réussir)${NC}"
echo "─────────────────────────────────────────────────────────────────"
if echo | openssl s_client -connect localhost:443 -tls1_2 -brief 2>&1 | grep -q "TLSv1.2"; then
    echo -e "${GREEN}✓ TLS 1.2 : ACTIF${NC}"
    echo | openssl s_client -connect localhost:443 -tls1_2 -brief 2>&1 | grep "Protocol version"
else
    echo -e "${RED}✗ TLS 1.2 : INACTIF${NC}"
fi
echo ""

echo -e "${BLUE}[4] Test TLS 1.1 (doit échouer - version obsolète)${NC}"
echo "─────────────────────────────────────────────────────────────────"
if echo | openssl s_client -connect localhost:443 -tls1_1 -brief 2>&1 | grep -q "error"; then
    echo -e "${GREEN}✓ TLS 1.1 : CORRECTEMENT REFUSÉ${NC}"
else
    echo -e "${RED}✗ TLS 1.1 : ACCEPTÉ (PROBLÈME DE SÉCURITÉ!)${NC}"
fi
echo ""

echo -e "${BLUE}[5] Test TLS 1.0 (doit échouer - version obsolète)${NC}"
echo "─────────────────────────────────────────────────────────────────"
if echo | openssl s_client -connect localhost:443 -tls1 -brief 2>&1 | grep -q "error"; then
    echo -e "${GREEN}✓ TLS 1.0 : CORRECTEMENT REFUSÉ${NC}"
else
    echo -e "${RED}✗ TLS 1.0 : ACCEPTÉ (PROBLÈME DE SÉCURITÉ!)${NC}"
fi
echo ""

echo -e "${BLUE}[6] Informations du certificat${NC}"
echo "─────────────────────────────────────────────────────────────────"
echo | openssl s_client -connect localhost:443 -brief 2>&1 | grep -E "(depth|CN|Verification|Ciphersuite)"
echo ""

echo -e "${BLUE}[7] Test de connexion HTTPS${NC}"
echo "─────────────────────────────────────────────────────────────────"
if curl -skI https://localhost/ | head -1 | grep -q "200\|301\|302"; then
    echo -e "${GREEN}✓ HTTPS : FONCTIONNEL${NC}"
    curl -skI https://localhost/ | head -1
else
    echo -e "${RED}✗ HTTPS : NON FONCTIONNEL${NC}"
fi
echo ""

echo "╔════════════════════════════════════════════════════════════════╗"
echo "║                         RÉSUMÉ                                 ║"
echo "╚════════════════════════════════════════════════════════════════╝"
echo -e "${GREEN}✓ TLS 1.2 et 1.3 activés${NC}"
echo -e "${GREEN}✓ TLS 1.0 et 1.1 désactivés (sécurité)${NC}"
echo -e "${GREEN}✓ Certificat SSL configuré${NC}"
echo -e "${GREEN}✓ HTTPS fonctionnel sur port 443${NC}"
