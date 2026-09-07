# Inception - Documentation Complète du Projet

## Table des Matières
1. [Vue d'Ensemble](#vue-densemble)
2. [Architecture du Projet](#architecture-du-projet)
3. [Concepts Docker Fondamentaux](#concepts-docker-fondamentaux)
4. [Analyse Détaillée des Services](#analyse-détaillée-des-services)
5. [Réseau et Communication](#réseau-et-communication)
6. [Volumes et Persistance](#volumes-et-persistance)
7. [Sécurité](#sécurité)
8. [Démarrage et Commandes](#démarrage-et-commandes)
9. [Dépannage](#dépannage)
10. [Points Clés à Retenir](#points-clés-à-retenir)

---

## Vue d'Ensemble

**Inception** est un projet d'infrastructure système qui consiste à créer une **stack web complète** (NGINX, WordPress, MariaDB) en utilisant **Docker Compose**. L'objectif pédagogique est d'apprendre à :

- Construire des images Docker **from scratch** (pas d'images toutes faites comme `wordpress:latest`)
- Comprendre les **interactions réseau** entre containers
- Maîtriser la **persistance des données** avec les volumes Docker
- Implémenter des **bonnes pratiques de sécurité** (TLS, secrets, principe du moindre privilège)
- Orchestrer plusieurs services avec **Docker Compose**

### Contraintes du Projet (42 School)

1. ✅ **Chaque service doit tourner dans un container dédié**
2. ✅ **Images Docker construites à partir de `debian:12-slim` ou `alpine`** (pas de `:latest`, pas d'images préfabriquées)
3. ✅ **NGINX doit être le seul point d'entrée** (port 443 uniquement, TLSv1.2/1.3)
4. ✅ **Pas de mots de passe en dur dans les Dockerfiles** (utilisation de Docker secrets)
5. ✅ **Utilisation de volumes Docker** pour la persistance (pas de bind mounts pour les données sensibles)
6. ✅ **Network bridge personnalisé** pour que les containers communiquent
7. ✅ **Restart policy** : `unless-stopped` pour tous les services

---

## Architecture du Projet

```
┌──────────────────────────────────────────────────────────────┐
│                        CLIENT (Navigateur)                   │
└───────────────────────────┬──────────────────────────────────┘
                            │ HTTPS (443)
                            │ TLSv1.2/1.3
                            ▼
┌───────────────────────────────────────────────────────────────┐
│                    NGINX (Container)                          │
│  - Reverse proxy                                              │
│  - Terminaison TLS (certificat auto-signé)                    │
│  - Port 443 → localhost:443                                   │
│  - Sert les fichiers statiques (HTML, CSS, JS, images)        │
│  - Forward les requêtes PHP vers WordPress via FastCGI        │
└───────────────────────────┬───────────────────────────────────┘
                            │ FastCGI (port 9000)
                            │ Protocole: inception_net
                            ▼
┌───────────────────────────────────────────────────────────────┐
│                   WORDPRESS (Container)                       │
│  - PHP-FPM (FastCGI Process Manager)                          │
│  - WordPress 6.8.3                                            │
│  - WP-CLI pour l'automatisation                               │
│  - 2 utilisateurs: llabonde (admin), editor (editor)          │
│  - Lecture/écriture dans wp_data volume                       │
└───────────────────────────┬───────────────────────────────────┘
                            │ MySQL Protocol (port 3306)
                            │ Network: inception_net
                            ▼
┌───────────────────────────────────────────────────────────────┐
│                   MARIADB (Container)                         │
│  - MariaDB 10.11 (compatible MySQL)                           │
│  - Base de données: wordpress                                 │
│  - Utilisateur: wp_user (avec privilèges sur wordpress DB)    │
│  - Persistance: db_data volume                                │
└───────────────────────────────────────────────────────────────┘
```

### Flux d'une Requête HTTP

1. **Client** → `https://localhost/` (port 443)
2. **NGINX** reçoit la requête, déchiffre TLS, vérifie le certificat
3. **NGINX** cherche un fichier statique (`index.php`)
4. **NGINX** détecte une extension `.php` → envoie la requête à WordPress via FastCGI
5. **WordPress (PHP-FPM)** exécute le code PHP, interroge MariaDB si nécessaire
6. **MariaDB** retourne les données (posts, utilisateurs, options)
7. **WordPress** génère le HTML
8. **NGINX** renvoie le HTML au client (avec les headers de sécurité)

---

## Concepts Docker Fondamentaux

### 1. **Images vs Containers**

- **Image** : Un template **immuable** (lecture seule) contenant :
  - Le système de fichiers (OS + dépendances)
  - Les métadonnées (ENTRYPOINT, CMD, ENV, etc.)
  - Les layers (couches) empilées
  
- **Container** : Une **instance en cours d'exécution** d'une image
  - Possède une couche R/W (read-write layer) au-dessus de l'image
  - Isolé grâce aux **namespaces** (PID, NET, MNT, IPC, UTS)
  - Limité en ressources via **cgroups** (CPU, RAM)

**Exemple** :
```bash
# Construire une image (lecture du Dockerfile)
docker build -t inception-nginx ./srcs/requirements/nginx

# Créer un container à partir de l'image
docker run -d --name nginx inception-nginx

# L'image reste identique, mais chaque container a son propre état
```

### 2. **Dockerfile - Les Instructions Clés**

#### `FROM`
Définit l'image de base. Dans ce projet, on utilise `debian:12-slim` (Debian 12 Bookworm, version minimale).

```dockerfile
ARG BASE_OS=debian:12-slim
FROM ${BASE_OS}
```

**Pourquoi pas `:latest` ?**
- `:latest` est **instable** (change à chaque nouvelle version)
- Viole le principe de **reproductibilité** (builds non déterministes)
- Peut introduire des **breaking changes** sans prévenir

#### `RUN`
Exécute une commande **pendant la construction** de l'image (crée un nouveau layer).

```dockerfile
RUN apt-get update && \
    apt-get install -y nginx openssl && \
    rm -rf /var/lib/apt/lists/*
```

**Best practices** :
- Chaîner les commandes avec `&&` pour minimiser les layers
- Nettoyer les caches (`rm -rf /var/lib/apt/lists/*`) pour réduire la taille

#### `COPY` vs `ADD`
- `COPY` : Copie des fichiers locaux dans l'image (préféré)
- `ADD` : Comme COPY, mais peut extraire des archives `.tar` automatiquement (comportement implicite = dangereux)

```dockerfile
COPY docker-entrypoint.sh /usr/local/bin/
```

#### `CMD` vs `ENTRYPOINT`

- **`ENTRYPOINT`** : Commande **fixe** qui sera toujours exécutée
- **`CMD`** : Arguments **par défaut** pour l'ENTRYPOINT (peuvent être surchargés)

```dockerfile
ENTRYPOINT ["/usr/local/bin/docker-entrypoint.sh"]
CMD ["mariadbd", "--user=mysql"]
```

**Comportement** :
- Si on lance `docker run mariadb`, ça exécute : `/usr/local/bin/docker-entrypoint.sh mariadbd --user=mysql`
- Si on lance `docker run mariadb bash`, ça exécute : `/usr/local/bin/docker-entrypoint.sh bash`

**Pourquoi utiliser un entrypoint ?**
- Permet d'exécuter du **code d'initialisation** avant de démarrer le service principal
- Exemple : attendre que la DB soit initialisée, générer des configurations dynamiques

#### `EXPOSE`
Documente le port utilisé par le container (purement informatif, ne publie pas le port).

```dockerfile
EXPOSE 443
```

Pour publier le port sur l'hôte : `docker run -p 443:443 ...`

### 3. **Docker Compose - Orchestration Multi-Containers**

**Docker Compose** est un outil pour définir et lancer des applications multi-containers via un fichier YAML (`docker-compose.yml`).

#### Structure de `docker-compose.yml`

```yaml
services:          # Liste des containers à créer
  nginx:
    build:         # Instructions de build (context = dossier avec Dockerfile)
      context: ./srcs/requirements/nginx
      args:        # Arguments de build (accessible via ARG dans Dockerfile)
        - BASE_OS=${BASE_OS}
    ports:         # Mapping de ports (host:container)
      - "443:443"
    volumes:       # Montage de volumes
      - wp_data:/var/www/html:ro
    networks:      # Réseaux auxquels le container est connecté
      - inception_net
    depends_on:    # Dépendances (ordre de démarrage)
      - wordpress
    restart: unless-stopped  # Politique de redémarrage
```

#### Variables d'Environnement

Compose charge automatiquement le fichier `.env` à la racine du projet.

**`.env`** :
```bash
MYSQL_DATABASE=wordpress
MYSQL_USER=wp_user
BASE_OS=debian:12-slim
```

**Accès dans `docker-compose.yml`** :
```yaml
environment:
  - MYSQL_DATABASE=${MYSQL_DATABASE}
```

**Accès dans le Dockerfile** :
```dockerfile
ARG BASE_OS
FROM ${BASE_OS}
```

### 4. **Volumes Docker**

Les volumes permettent de **persister les données** en dehors du cycle de vie du container.

#### Types de Montages

| Type | Syntaxe | Use Case | Exemple |
|------|---------|----------|---------|
| **Volume Docker** | `volume_name:/path/in/container` | Persistance de données (géré par Docker) | `db_data:/var/lib/mysql` |
| **Bind Mount** | `/host/path:/container/path` | Développement (sync code) | `./nginx.conf:/etc/nginx/nginx.conf:ro` |
| **tmpfs Mount** | `type: tmpfs, target: /tmp` | Données temporaires (RAM) | Logs éphémères |

#### Pourquoi Utiliser des Volumes Docker ?

1. **Indépendance** : Les données survivent à la suppression du container
2. **Performance** : Plus rapide que les bind mounts (surtout sur macOS/Windows)
3. **Portabilité** : Fonctionne identiquement sur tous les OS
4. **Backup** : Facile à sauvegarder avec `docker run --volumes-from`

**Exemple de manipulation** :
```bash
# Lister les volumes
docker volume ls

# Inspecter un volume (voir où il est stocké sur l'hôte)
docker volume inspect inception_db_data

# Backup d'un volume
docker run --rm --volumes-from mariadb -v $(pwd):/backup debian:12-slim tar czf /backup/db_backup.tar.gz /var/lib/mysql

# Restore d'un volume
docker run --rm --volumes-from mariadb -v $(pwd):/backup debian:12-slim tar xzf /backup/db_backup.tar.gz
```

### 5. **Networks Docker**

Les containers communiquent via des **réseaux virtuels**. Docker crée un switch virtuel (bridge) qui route les paquets.

#### Types de Réseaux

| Driver | Description | Use Case |
|--------|-------------|----------|
| **bridge** | Réseau privé (par défaut) | Containers sur le même hôte |
| **host** | Partage la stack réseau de l'hôte | Performances max (pas d'isolation) |
| **overlay** | Réseau multi-hôtes (Swarm) | Clusters distribués |
| **none** | Pas de réseau | Isolation totale |

#### DNS Intégré

Docker Compose crée automatiquement un **serveur DNS interne** (127.0.0.11) qui résout les noms de services.

**Exemple** :
```yaml
# Dans docker-compose.yml
services:
  mariadb:
    container_name: mariadb
  wordpress:
    environment:
      - WORDPRESS_DB_HOST=mariadb:3306  # "mariadb" sera résolu en IP du container
```

**Test** :
```bash
docker-compose exec wordpress ping mariadb
# PING mariadb (172.18.0.2) 56(84) bytes of data.
```

#### Réseau `inception_net`

```yaml
networks:
  inception_net:
    name: inception_net  # Nom explicite (sinon Docker préfixe avec le nom du projet)
    driver: bridge
```

**Isolation** :
- Les containers sur `inception_net` peuvent communiquer entre eux
- Les containers sur d'autres réseaux ne peuvent pas les joindre (sauf via port mapping)

### 6. **Healthchecks**

Les healthchecks permettent à Docker de **surveiller l'état** d'un container et de le redémarrer si nécessaire.

```yaml
healthcheck:
  test: ["CMD-SHELL", "mysqladmin ping -h 127.0.0.1 --silent || exit 1"]
  interval: 10s      # Teste toutes les 10 secondes
  timeout: 5s        # Timeout après 5 secondes
  retries: 3         # Marque "unhealthy" après 3 échecs consécutifs
  start_period: 5s   # Période de grâce (pas de healthcheck pendant 5s au démarrage)
```

**États possibles** :
- `starting` : Container démarré, healthcheck pas encore exécuté
- `healthy` : Healthcheck réussi
- `unhealthy` : Healthcheck échoué après N retries

**Utilité** :
- **Orchestration** : `depends_on` peut attendre que les dépendances soient `healthy` (avec condition `service_healthy`)
- **Debugging** : `docker ps` montre l'état de santé
- **Auto-healing** : Combiné avec `restart: on-failure`, Docker redémarre les containers malades

---

## Analyse Détaillée des Services

### 1. NGINX - Reverse Proxy & Terminaison TLS

#### Rôle
NGINX agit comme **point d'entrée unique** de l'infrastructure. Il :
1. **Déchiffre le trafic TLS** (HTTPS → HTTP en interne)
2. **Sert les fichiers statiques** (images, CSS, JS) directement
3. **Proxyse les requêtes PHP** vers WordPress via FastCGI
4. **Ajoute des headers de sécurité** (HSTS, X-Frame-Options, etc.)

#### Dockerfile (`srcs/requirements/nginx/Dockerfile`)

```dockerfile
ARG BASE_OS=debian:12-slim
FROM ${BASE_OS}

# Installer NGINX et OpenSSL (pour générer le certificat auto-signé)
RUN apt-get update && \
    apt-get install -y nginx openssl && \
    rm -rf /var/lib/apt/lists/*

# Générer un certificat TLS auto-signé (validité 365 jours)
RUN mkdir -p /etc/ssl/certs /etc/ssl/private && \
    openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
      -keyout /etc/ssl/private/nginx.key \
      -out /etc/ssl/certs/nginx.crt \
      -subj "/C=FR/ST=Paris/L=Paris/O=42/OU=Student/CN=llabonde.42.fr"

# Copier la configuration NGINX
COPY conf/default /etc/nginx/sites-available/default

EXPOSE 443

CMD ["nginx", "-g", "daemon off;"]
```

**Explications** :
- `openssl req -x509` : Génère un certificat auto-signé (pas d'autorité de certification)
- `-nodes` : Pas de passphrase pour la clé privée (sinon NGINX demande le mot de passe au démarrage)
- `-subj` : Informations du certificat (CN = Common Name = nom de domaine)
- `daemon off;` : NGINX tourne en **premier plan** (nécessaire pour que Docker ne kill pas le container)

#### Configuration NGINX (`srcs/requirements/nginx/conf/default`)

```nginx
server {
    listen 443 ssl http2;
    server_name llabonde.42.fr;

    root /var/www/html;
    index index.php index.html;

    # Configuration TLS
    ssl_certificate /etc/ssl/certs/nginx.crt;
    ssl_certificate_key /etc/ssl/private/nginx.key;
    ssl_protocols TLSv1.2 TLSv1.3;  # Seulement les versions sécurisées
    ssl_ciphers 'ECDHE-ECDSA-CHACHA20-POLY1305:...';  # Chiffrement fort
    ssl_prefer_server_ciphers off;  # Laisse le client choisir (meilleure compatibilité)

    # OCSP Stapling (vérification de révocation des certificats)
    ssl_stapling on;
    ssl_stapling_verify on;
    resolver 127.0.0.11 valid=30s;  # DNS Docker interne

    # Headers de sécurité
    add_header Strict-Transport-Security "max-age=63072000; includeSubDomains; preload" always;
    add_header X-Frame-Options DENY;  # Empêche l'inclusion dans une iframe (anti-clickjacking)
    add_header X-Content-Type-Options nosniff;  # Empêche le sniffing MIME

    # Gestion des fichiers statiques
    location / {
        try_files $uri $uri/ /index.php?$args;
    }

    # Proxy vers PHP-FPM (WordPress)
    location ~ \.php$ {
        fastcgi_pass wordpress:9000;  # Nom du service Docker Compose
        fastcgi_index index.php;
        include fastcgi_params;
        fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;
        fastcgi_param PATH_INFO $fastcgi_path_info;
    }
}
```

**Concepts Clés** :

- **HTTP/2** : Active le multiplexing (plusieurs requêtes sur la même connexion TCP)
- **TLSv1.2/1.3** : Protocoles de chiffrement modernes (TLSv1.0/1.1 sont obsolètes)
- **HSTS** : Force le navigateur à toujours utiliser HTTPS (même si l'utilisateur tape `http://`)
- **FastCGI** : Protocole binaire pour communiquer avec PHP-FPM (plus rapide que CGI classique)

#### Problème : Pourquoi Pas Servir WordPress Directement ?

WordPress **n'inclut pas de serveur HTTP**. Il a besoin d'un serveur web (Apache/NGINX) pour :
1. Recevoir les requêtes HTTP
2. Appeler l'interpréteur PHP
3. Retourner la réponse

**Architectures possibles** :
- **Apache + mod_php** : PHP est un module Apache (mode "monolithique")
- **NGINX + PHP-FPM** : PHP tourne dans un processus séparé (mode "découplé") ← **Notre choix**

**Avantages de PHP-FPM** :
- **Performance** : Pool de workers PHP (évite de spawner un processus à chaque requête)
- **Isolation** : PHP et NGINX peuvent redémarrer indépendamment
- **Scalabilité** : On peut lancer plusieurs containers WordPress derrière un load balancer

---

### 2. WordPress - Application PHP

#### Rôle
WordPress est le **CMS (Content Management System)** qui génère les pages web. Il :
1. **Exécute le code PHP** (themes, plugins, core)
2. **Interroge MariaDB** pour récupérer les posts, utilisateurs, options
3. **Génère le HTML** à partir des templates
4. **Gère les médias** (uploads d'images, fichiers)

#### Dockerfile (`srcs/requirements/wordpress/Dockerfile`)

```dockerfile
ARG BASE_OS=debian:12-slim
FROM ${BASE_OS}

# Installer PHP-FPM et extensions requises par WordPress
RUN apt-get update && \
    apt-get install -y \
      php8.2-fpm \           # FastCGI Process Manager
      php8.2-mysql \         # Extension MySQL (pour se connecter à MariaDB)
      php8.2-gd \            # Manipulation d'images (thumbnails)
      php8.2-xml \           # Parsing XML (flux RSS, sitemaps)
      php8.2-mbstring \      # Support multi-byte (UTF-8)
      php8.2-curl \          # Requêtes HTTP (API, plugins)
      curl \                 # Pour télécharger WordPress
      less \                 # Éditeur (debugging)
      default-mysql-client \ # Client MySQL (wp db check)
      && rm -rf /var/lib/apt/lists/*

# Télécharger WP-CLI (outil en ligne de commande pour WordPress)
RUN curl -o /usr/local/bin/wp https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar && \
    chmod +x /usr/local/bin/wp

# Configurer PHP-FPM pour écouter sur toutes les interfaces (0.0.0.0:9000)
RUN sed -i 's/listen = \/run\/php\/php8.2-fpm.sock/listen = 9000/g' /etc/php/8.2/fpm/pool.d/www.conf

# Télécharger WordPress (version stable latest)
ARG WORDPRESS_VERSION=6.8.3
RUN curl -o /tmp/wordpress.tar.gz https://wordpress.org/wordpress-${WORDPRESS_VERSION}.tar.gz && \
    tar -xzf /tmp/wordpress.tar.gz -C /var/www/ && \
    mv /var/www/wordpress /var/www/html && \
    chown -R www-data:www-data /var/www/html

COPY wp-config.php /var/www/html/
COPY wp-init.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/wp-init.sh

WORKDIR /var/www/html
EXPOSE 9000

ENTRYPOINT ["/usr/local/bin/wp-init.sh"]
CMD ["php-fpm8.2", "-F"]  # -F = foreground (ne devient pas daemon)
```

**Explications** :
- **PHP-FPM** : Process Manager qui maintient un pool de workers PHP prêts à traiter les requêtes
- **Extensions PHP** : WordPress a besoin de `php-mysql`, `php-gd` (images), `php-xml` (RSS), etc.
- **WP-CLI** : Outil officiel WordPress pour automatiser les tâches (installation, création d'utilisateurs, backup, etc.)
- **`listen = 9000`** : Par défaut, PHP-FPM écoute sur un socket Unix (`/run/php/php8.2-fpm.sock`). On le change pour un socket TCP (0.0.0.0:9000) pour que NGINX puisse s'y connecter depuis un autre container.

#### Script d'Initialisation (`srcs/requirements/wordpress/wp-init.sh`)

Ce script est exécuté **au démarrage du container** (via ENTRYPOINT). Il :
1. Attend que MariaDB soit prêt
2. Vérifie si WordPress est installé
3. Si non, lance `wp core install`
4. Crée les utilisateurs (admin + editor)
5. Démarre PHP-FPM

```bash
#!/bin/sh
set -e

# Variables par défaut (surchargées par docker-compose)
: "${WORDPRESS_DB_HOST:=mariadb}"
: "${WORDPRESS_DB_PORT:=3306}"
: "${WP_ADMIN_USER:=llabonde}"
: "${WP_ADMIN_PASSWORD_FILE:=/run/secrets/wp_admin_password}"

# Attente de la disponibilité de la base de données (test de connexion TCP)
echo "[wp-init] Waiting for database ${WORDPRESS_DB_HOST}:${WORDPRESS_DB_PORT}..."
until php -r "if(@fsockopen('${WORDPRESS_DB_HOST}', ${WORDPRESS_DB_PORT})) exit(0); exit(1);" >/dev/null 2>&1; do
  sleep 1
done

# Vérifier si WordPress est déjà installé
if ! wp core is-installed --allow-root --path=/var/www/html 2>/dev/null; then
  echo "[wp-init] WordPress not installed, running installation..."
  
  # Lire le mot de passe depuis le fichier secret
  WP_ADMIN_PASSWORD=$(cat "$WP_ADMIN_PASSWORD_FILE")
  
  # Installer WordPress
  wp core install \
    --url="$WP_SITE_URL" \
    --title="$WP_SITE_TITLE" \
    --admin_user="$WP_ADMIN_USER" \
    --admin_password="$WP_ADMIN_PASSWORD" \
    --admin_email="$WP_ADMIN_EMAIL" \
    --allow-root \
    --path=/var/www/html
  
  # Créer un second utilisateur (rôle editor)
  wp user create "$WP_USER2_LOGIN" "$WP_USER2_EMAIL" \
    --role=editor \
    --user_pass="$WP_USER2_PASSWORD" \
    --allow-root \
    --path=/var/www/html
  
  echo "[wp-init] WordPress installation complete"
else
  echo "[wp-init] WordPress already installed"
fi

# Démarrer PHP-FPM (exec remplace le shell par PHP-FPM, pour recevoir les signaux Docker)
exec "$@"
```

**Concepts Clés** :

- **Idempotence** : Le script peut être exécuté plusieurs fois sans effet de bord (vérifie si WP est installé avant d'installer)
- **`exec "$@"`** : Remplace le processus shell par la commande passée en argument (`php-fpm8.2 -F`). Critique pour que Docker puisse envoyer les signaux (SIGTERM lors du `docker stop`)
- **`--allow-root`** : WP-CLI refuse de tourner en root par défaut (sécurité). On le force ici car on est dans un container (isolation)

#### Configuration WordPress (`srcs/requirements/wordpress/wp-config.php`)

```php
<?php
define('DB_NAME', getenv('WORDPRESS_DB_NAME'));
define('DB_USER', getenv('WORDPRESS_DB_USER'));
define('DB_PASSWORD', getenv('WORDPRESS_DB_PASSWORD'));
define('DB_HOST', getenv('WORDPRESS_DB_HOST'));
define('DB_CHARSET', 'utf8mb4');
define('DB_COLLATE', '');

// Clés de sécurité (génération : https://api.wordpress.org/secret-key/1.1/salt/)
define('AUTH_KEY',         'put your unique phrase here');
define('SECURE_AUTH_KEY',  'put your unique phrase here');
define('LOGGED_IN_KEY',    'put your unique phrase here');
define('NONCE_KEY',        'put your unique phrase here');
// ...

$table_prefix = 'wp_';
define('WP_DEBUG', false);

if (!defined('ABSPATH'))
    define('ABSPATH', __DIR__ . '/');

require_once ABSPATH . 'wp-settings.php';
```

**Explications** :
- **`DB_*`** : Informations de connexion à MariaDB (injectées via variables d'environnement)
- **Salts** : Clés secrètes pour hasher les cookies et sessions (empêche le vol de session)
- **`$table_prefix`** : Préfixe des tables MySQL (permet d'avoir plusieurs WP sur la même DB)

#### Pourquoi PHP-FPM et Pas PHP-CLI ?

| Mode | Description | Use Case |
|------|-------------|----------|
| **PHP-CLI** | Exécute un script et termine | Scripts cron, maintenance |
| **PHP-FPM** | Pool de workers persistants | Servir des requêtes HTTP |

**Avantages de PHP-FPM** :
- **Performance** : Les workers restent en mémoire (pas de recompilation du code à chaque requête)
- **Concurrence** : Gère plusieurs requêtes simultanées (pool de 5-10 workers)
- **Monitoring** : Expose des métriques (`/status`, `/ping`)

---

### 3. MariaDB - Base de Données Relationnelle

#### Rôle
MariaDB stocke **toutes les données dynamiques** de WordPress :
- **Posts** (articles, pages)
- **Utilisateurs** (login, email, rôle, mot de passe hashé)
- **Commentaires**
- **Options** (titre du site, thème actif, plugins activés)
- **Taxonomies** (catégories, tags)

#### Dockerfile (`srcs/requirements/mariadb/Dockerfile`)

```dockerfile
ARG BASE_OS=debian:12-slim
FROM ${BASE_OS}

# Installer MariaDB
RUN apt-get update && \
    apt-get install -y mariadb-server mariadb-client && \
    rm -rf /var/lib/apt/lists/*

# Copier le script d'initialisation
COPY docker-entrypoint.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/docker-entrypoint.sh

# Créer les répertoires nécessaires
RUN mkdir -p /var/lib/mysql /run/mysqld && \
    chown -R mysql:mysql /var/lib/mysql /run/mysqld

EXPOSE 3306

ENTRYPOINT ["/usr/local/bin/docker-entrypoint.sh"]
CMD ["mariadbd", "--user=mysql"]
```

#### Script d'Initialisation (`srcs/requirements/mariadb/docker-entrypoint.sh`)

Ce script gère l'**initialisation de la base de données** au premier démarrage. Problème courant : MariaDB **refuse les connexions** pendant l'initialisation (chicken-and-egg).

**Solution** : Utiliser `--skip-grant-tables` pour démarrer un serveur temporaire sans authentification, exécuter les commandes SQL, puis redémarrer normalement.

```bash
#!/bin/sh
set -e

DATADIR=/var/lib/mysql

# Créer le répertoire du socket Unix
mkdir -p /run/mysqld
chown mysql:mysql /run/mysqld

# Forcer MariaDB à écouter sur 0.0.0.0 (pas seulement 127.0.0.1)
cat > /etc/mysql/mariadb.conf.d/99-docker.cnf <<'CNF'
[mysqld]
bind-address = 0.0.0.0
CNF

# Si le répertoire de données est vide, initialiser la DB
if [ ! -d "$DATADIR/mysql" ]; then
  echo "[entrypoint] Initializing MariaDB data directory"
  
  # Créer les tables système (mysql.user, mysql.db, etc.)
  mariadb-install-db --user=mysql --datadir="$DATADIR" --skip-test-db --auth-root-authentication-method=normal
  
  # Démarrer un serveur temporaire SANS authentification (--skip-grant-tables)
  echo "[entrypoint] Starting temporary server with skip-grant-tables"
  mariadbd --user=mysql --datadir="$DATADIR" --skip-grant-tables --skip-networking --socket=/run/mysqld/mysqld.sock &
  pid="$!"
  
  # Attendre que le socket soit créé
  until [ -S /run/mysqld/mysqld.sock ] && mysql -uroot --socket=/run/mysqld/mysqld.sock -e "SELECT 1" >/dev/null 2>&1; do
    sleep 1
  done
  
  # Lire les mots de passe depuis les secrets Docker
  MYSQL_ROOT_PASSWORD=$(cat /run/secrets/mysql_root_password)
  MYSQL_PASSWORD=$(cat /run/secrets/mysql_password)
  
  # Exécuter les commandes SQL d'initialisation
  mysql --socket=/run/mysqld/mysqld.sock <<-EOSQL
    FLUSH PRIVILEGES;
    ALTER USER 'root'@'localhost' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';
    CREATE DATABASE IF NOT EXISTS \`${MYSQL_DATABASE}\`;
    CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';
    GRANT ALL PRIVILEGES ON \`${MYSQL_DATABASE}\`.* TO '${MYSQL_USER}'@'%';
    FLUSH PRIVILEGES;
  EOSQL
  
  # Arrêter le serveur temporaire
  kill "$pid"
  wait "$pid" 2>/dev/null || true
fi

# Démarrer MariaDB normalement
exec "$@"
```

**Explications** :

- **`mariadb-install-db`** : Crée les tables système (`mysql.user`, `mysql.db`, `mysql.tables_priv`, etc.)
- **`--skip-grant-tables`** : Désactive l'authentification (n'importe qui peut se connecter). Nécessaire car root n'a pas encore de mot de passe.
- **`--skip-networking`** : Désactive TCP (écoute seulement sur le socket Unix). Empêche les connexions externes pendant l'init.
- **`FLUSH PRIVILEGES`** : Recharge les tables de privilèges (nécessaire après un CREATE USER en mode skip-grant-tables)
- **`'${MYSQL_USER}'@'%'`** : Autorise l'utilisateur à se connecter depuis **n'importe quelle IP** (`%` = wildcard). Nécessaire car WordPress est dans un autre container (IP différente).

#### Problème : Pourquoi Pas `mysql_secure_installation` ?

`mysql_secure_installation` est un script interactif (demande des confirmations). Il n'est pas adapté à un environnement automatisé (Docker). On reproduit ses actions en SQL :
- Définir le mot de passe root
- Supprimer les utilisateurs anonymes (`DELETE FROM mysql.user WHERE User=''`)
- Désactiver le login root distant (`DELETE FROM mysql.user WHERE User='root' AND Host NOT IN ('localhost', '127.0.0.1')`)
- Supprimer la base de test (`DROP DATABASE IF EXISTS test`)

#### Tables WordPress

WordPress crée automatiquement 12 tables lors de l'installation :

| Table | Description |
|-------|-------------|
| `wp_posts` | Articles, pages, révisions |
| `wp_postmeta` | Métadonnées des posts (custom fields) |
| `wp_users` | Utilisateurs (login, email, password hash) |
| `wp_usermeta` | Métadonnées des utilisateurs (avatar, bio) |
| `wp_comments` | Commentaires |
| `wp_commentmeta` | Métadonnées des commentaires |
| `wp_terms` | Termes des taxonomies (catégories, tags) |
| `wp_term_taxonomy` | Types de taxonomies |
| `wp_term_relationships` | Relations posts ↔ termes |
| `wp_options` | Configuration du site (titre, URL, thème) |
| `wp_links` | Liens (blogroll) - obsolète |
| `wp_termmeta` | Métadonnées des termes |

**Exemple de requête** :
```sql
-- Lister les articles publiés
SELECT post_title, post_date FROM wp_posts WHERE post_status='publish' AND post_type='post';

-- Trouver les utilisateurs admin
SELECT user_login, user_email FROM wp_users WHERE ID IN (
  SELECT user_id FROM wp_usermeta WHERE meta_key='wp_capabilities' AND meta_value LIKE '%administrator%'
);
```

---

## Réseau et Communication

### 1. Réseau Bridge `inception_net`

Docker Compose crée un **réseau bridge privé** nommé `inception_net`. Tous les containers y sont connectés.

```yaml
networks:
  inception_net:
    name: inception_net
    driver: bridge
```

**Comportement** :
- Chaque container reçoit une IP privée (ex: 172.18.0.2, 172.18.0.3, etc.)
- Les containers peuvent se ping mutuellement par nom (DNS interne)
- L'hôte peut accéder aux containers via `localhost:<port>` (si ports mappés)

**Vérification** :
```bash
# Lister les réseaux
docker network ls

# Inspecter le réseau (voir les containers connectés)
docker network inspect inception_net

# Tester la connectivité depuis WordPress vers MariaDB
docker-compose exec wordpress ping mariadb
```

### 2. DNS Interne Docker

Docker Compose configure automatiquement un **serveur DNS interne** (127.0.0.11) qui résout les noms de services.

**Exemple** :
```bash
# Dans le container WordPress
nslookup mariadb
# Server:    127.0.0.11
# Address:   127.0.0.11#53
# 
# Name:      mariadb
# Address:   172.18.0.2
```

**Configuration NGINX** :
```nginx
resolver 127.0.0.11 valid=30s;  # Utilise le DNS Docker
```

### 3. Port Mapping

Seul NGINX expose un port sur l'hôte (443). Les autres services (WordPress, MariaDB) sont **isolés**.

```yaml
nginx:
  ports:
    - "443:443"  # Hôte:Container
```

**Schéma** :
```
Hôte (localhost:443) → Docker Proxy → NGINX (172.18.0.3:443)
                                         ↓ FastCGI
                              WordPress (172.18.0.4:9000)
                                         ↓ MySQL
                              MariaDB (172.18.0.2:3306)
```

**Sécurité** : MariaDB n'est accessible que depuis le réseau Docker (pas d'exposition sur l'hôte).

---

## Volumes et Persistance

### 1. Volume `db_data` (MariaDB)

Stocke les fichiers de la base de données (`/var/lib/mysql`).

```yaml
volumes:
  - db_data:/var/lib/mysql
```

**Contenu** :
```
/var/lib/mysql/
├── aria_log.00000001
├── aria_log_control
├── ib_buffer_pool
├── ibdata1               # Fichier InnoDB (tables système)
├── mysql/                # Base de données système (users, privileges)
├── performance_schema/   # Métriques de performance
├── wordpress/            # Base WordPress
│   ├── wp_posts.ibd      # Fichier de données de la table wp_posts
│   ├── wp_users.ibd
│   └── ...
└── ib_logfile0           # Logs de transactions (redo log)
```

**Test de persistance** :
```bash
# Créer des données
docker-compose exec wordpress wp post create --post_title="Test" --allow-root

# Supprimer le container (SANS supprimer le volume)
docker-compose down

# Redémarrer
docker-compose up -d

# Vérifier que le post existe toujours
docker-compose exec wordpress wp post list --allow-root
```

### 2. Volume `wp_data` (WordPress)

Stocke les fichiers WordPress (core, themes, plugins, uploads).

```yaml
volumes:
  - wp_data:/var/www/html
```

**Contenu** :
```
/var/www/html/
├── wp-admin/             # Interface d'administration
├── wp-includes/          # Core WordPress
├── wp-content/           # Contenu personnalisé
│   ├── themes/           # Thèmes (apparence)
│   ├── plugins/          # Plugins (fonctionnalités)
│   └── uploads/          # Médias (images, PDFs)
├── index.php             # Point d'entrée
├── wp-config.php         # Configuration
└── ...
```

**Pourquoi Partager `wp_data` entre NGINX et WordPress ?**

- **NGINX** : Sert les fichiers statiques (CSS, JS, images dans `wp-content/uploads`)
- **WordPress** : Génère les pages PHP, écrit les uploads

**Modes de montage** :
```yaml
nginx:
  volumes:
    - wp_data:/var/www/html:ro  # Read-only (NGINX ne modifie pas les fichiers)

wordpress:
  volumes:
    - wp_data:/var/www/html     # Read-write (WordPress écrit les uploads)
```

---

## Sécurité

### 1. Docker Secrets

Les secrets permettent de **stocker des données sensibles** (mots de passe, clés API) de manière sécurisée.

```yaml
secrets:
  mysql_root_password:
    file: ./secrets/mysql_root_password
  mysql_password:
    file: ./secrets/mysql_password
  wp_admin_password:
    file: ./secrets/wp_admin_password

services:
  mariadb:
    secrets:
      - mysql_root_password
      - mysql_password
```

**Comportement** :
- Docker monte les secrets en **lecture seule** dans `/run/secrets/` (tmpfs en RAM, jamais sur disque)
- Les secrets ne sont **pas versionnés** dans Git (ajoutés au `.gitignore`)
- Seuls les containers autorisés peuvent y accéder

**Lecture d'un secret** :
```bash
MYSQL_ROOT_PASSWORD=$(cat /run/secrets/mysql_root_password)
```

**Alternative moins sécurisée** : Variables d'environnement
```yaml
environment:
  - MYSQL_ROOT_PASSWORD=rootpassword  # Visible dans `docker inspect` ❌
```

### 2. TLS (HTTPS)

NGINX utilise **TLS 1.2 et 1.3** pour chiffrer le trafic. Le certificat est **auto-signé** (adapté pour le développement, mais pas pour la production).

```nginx
ssl_protocols TLSv1.2 TLSv1.3;
ssl_ciphers 'ECDHE-ECDSA-CHACHA20-POLY1305:ECDHE-RSA-CHACHA20-POLY1305:...';
```

**Différence TLS 1.2 vs 1.3** :
| Aspect | TLS 1.2 | TLS 1.3 |
|--------|---------|---------|
| Handshake | 2 RTT (round-trips) | 1 RTT (plus rapide) |
| Chiffrements faibles | Autorisés (RC4, 3DES) | Supprimés |
| Forward Secrecy | Optionnel (DHE/ECDHE) | Obligatoire |

**HSTS (HTTP Strict Transport Security)** :
```nginx
add_header Strict-Transport-Security "max-age=63072000; includeSubDomains; preload" always;
```
- Force le navigateur à **toujours utiliser HTTPS** (même si l'utilisateur tape `http://`)
- `max-age=63072000` : 2 ans (durée de la règle)
- `includeSubDomains` : S'applique aussi aux sous-domaines (www.example.com, api.example.com)
- `preload` : Demande l'inclusion dans la liste HSTS des navigateurs (protection dès la première visite)

### 3. Principe du Moindre Privilège

- **Pas de `root` dans les containers** : Les services tournent avec un utilisateur dédié (`mysql`, `www-data`)
- **Volumes en lecture seule** : NGINX n'a pas besoin de modifier `wp_data` → `:ro`
- **Réseau isolé** : MariaDB n'est accessible que depuis `inception_net`

---

## Démarrage et Commandes

### 1. Utilisation du Makefile

```bash
# Construire les images et démarrer les containers
make up

# Arrêter les containers (sans supprimer les volumes)
make down

# Arrêter et supprimer les volumes (⚠️ perte de données)
make clean

# Voir les logs en temps réel
make logs

# Redémarrer un service
make restart SERVICE=wordpress
```

### 2. Commandes Docker Compose

```bash
# Construire les images (sans cache)
docker-compose build --no-cache

# Démarrer en mode détaché (background)
docker-compose up -d

# Voir les logs
docker-compose logs -f nginx

# Exécuter une commande dans un container
docker-compose exec wordpress bash

# Redémarrer un service
docker-compose restart mariadb

# Voir l'état des services
docker-compose ps
```

### 3. Commandes de Debug

```bash
# Inspecter un container (voir les mounts, variables d'env, réseau)
docker inspect nginx

# Voir les processus dans un container
docker-compose exec wordpress ps aux

# Tester la connectivité réseau
docker-compose exec wordpress ping mariadb

# Vérifier les logs MariaDB
docker-compose logs mariadb | grep ERROR

# Lister les bases de données
docker-compose exec mariadb mysql -uroot -p -e "SHOW DATABASES;"
```

---

## Dépannage

### 1. Container `unhealthy`

**Symptôme** : `docker ps` montre `unhealthy` dans la colonne STATUS.

**Cause** : Le healthcheck échoue (service ne répond pas).

**Debug** :
```bash
# Voir les logs du healthcheck
docker inspect nginx --format='{{json .State.Health}}' | jq

# Exécuter manuellement le healthcheck
docker-compose exec nginx curl -kf https://localhost/ || echo "FAIL"
```

**Solutions** :
- Augmenter `start_period` (temps de grâce au démarrage)
- Vérifier que le service écoute sur le bon port (`netstat -tlnp`)

### 2. WordPress ne se connecte pas à MariaDB

**Symptôme** : Erreur `Error establishing a database connection`.

**Causes possibles** :
1. MariaDB pas encore prêt (WordPress démarre trop vite)
2. Mauvais credentials (mot de passe incorrect)
3. Nom d'hôte incorrect (`mariadb` au lieu de `localhost`)

**Debug** :
```bash
# Tester la connexion depuis WordPress
docker-compose exec wordpress php -r "
  \$link = mysqli_connect('mariadb', 'wp_user', 'wp_pass', 'wordpress');
  echo \$link ? 'OK' : 'FAIL';
"

# Vérifier les variables d'environnement
docker-compose exec wordpress env | grep WORDPRESS_DB
```

**Solutions** :
- Ajouter un `depends_on` avec condition `service_healthy`
- Augmenter le timeout dans `wp-init.sh`

### 3. Volume vide après redémarrage

**Symptôme** : WordPress affiche l'écran d'installation après `docker-compose down && up`.

**Cause** : Le volume a été supprimé (`docker-compose down -v`).

**Prévention** :
```bash
# Arrêter SANS supprimer les volumes
docker-compose down

# Lister les volumes pour vérifier qu'ils existent
docker volume ls | grep inception
```

### 4. Port 443 déjà utilisé

**Symptôme** : `Error starting userland proxy: listen tcp 0.0.0.0:443: bind: address already in use`.

**Cause** : Un autre processus utilise le port 443 (Apache, un autre NGINX).

**Solutions** :
```bash
# Trouver le processus qui utilise le port
sudo lsof -i :443

# Changer le port dans docker-compose.yml
ports:
  - "8443:443"  # Accès via https://localhost:8443
```

---

## Points Clés à Retenir

### 1. Architecture Multi-Tiers

- **Présentation** (NGINX) : Gère TLS, sert les statiques, proxyse les requêtes
- **Application** (WordPress) : Logique métier, génération de HTML
- **Données** (MariaDB) : Stockage persistant, transactions ACID

### 2. Isolation et Découplage

- Chaque service tourne dans un **container dédié** (indépendance)
- Communication via **réseau Docker** (pas de ports exposés sur l'hôte sauf NGINX)
- Utilisation de **volumes** pour partager les données

### 3. Sécurité

- **Secrets Docker** : Pas de mots de passe en dur
- **TLS 1.2/1.3** : Chiffrement fort
- **Headers de sécurité** : HSTS, X-Frame-Options, X-Content-Type-Options
- **Principe du moindre privilège** : Services tournent avec des utilisateurs dédiés

### 4. Bonnes Pratiques Docker

- **Images minimales** : `debian:12-slim` (pas de bloatware)
- **Pas de `:latest`** : Versions explicites pour la reproductibilité
- **Layers optimisés** : Chaîner les commandes avec `&&`, nettoyer les caches
- **Healthchecks** : Surveiller l'état des services
- **Logs** : Utiliser `stdout`/`stderr` (capturés par Docker)

### 5. WordPress + MariaDB

- **PHP-FPM** : Pool de workers pour la performance
- **WP-CLI** : Automatisation des tâches WordPress
- **Entrypoint Pattern** : Initialisation avant de démarrer le service principal
- **Idempotence** : Les scripts d'init peuvent être rejoués sans effet de bord

### 6. Debugging

- **Logs** : `docker-compose logs -f <service>`
- **Shell interactif** : `docker-compose exec <service> bash`
- **Healthchecks** : `docker ps` pour voir l'état
- **Inspection** : `docker inspect <container>` pour les détails (mounts, env, réseau)

---

## Ressources Supplémentaires

- [Documentation Docker](https://docs.docker.com/)
- [Documentation Docker Compose](https://docs.docker.com/compose/)
- [Documentation WordPress](https://developer.wordpress.org/)
- [Documentation MariaDB](https://mariadb.com/kb/en/)
- [Documentation NGINX](https://nginx.org/en/docs/)
- [WP-CLI Handbook](https://make.wordpress.org/cli/handbook/)
- [Mozilla SSL Configuration Generator](https://ssl-config.mozilla.org/)
- [Docker Security Best Practices](https://docs.docker.com/engine/security/)

---

## Conclusion

Ce projet **Inception** vous apprend à construire une infrastructure web moderne en respectant les principes **DevOps** :

- **Infrastructure as Code** : Tout est décrit dans des fichiers (Dockerfile, docker-compose.yml)
- **Reproductibilité** : `docker-compose up` crée l'environnement identique à chaque fois
- **Isolation** : Les containers ne se marchent pas dessus (namespaces, cgroups)
- **Scalabilité** : Facile d'ajouter des services (Redis, FTP, Adminer) ou de répliquer WordPress
- **Sécurité** : Secrets, TLS, principe du moindre privilège

Vous êtes maintenant capable de :
- Construire des images Docker optimisées
- Orchestrer plusieurs services avec Compose
- Débugger des problèmes réseau/volumes
- Sécuriser une infrastructure web (TLS, secrets, headers)
- Automatiser l'initialisation de bases de données

**Bravo ! 🎉**
