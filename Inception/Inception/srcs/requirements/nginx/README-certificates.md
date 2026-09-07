# Certificats pour Nginx (développement)

Ce document décrit comment générer et utiliser des certificats auto-signés pour le service `nginx` du projet (pour un usage scolaire / développement uniquement).

Fichiers créés par le script:

- `srcs/requirements/nginx/certs/nginx.crt` — certificat PEM
- `srcs/requirements/nginx/certs/nginx.key` — clé privée (permissions 600)

Script de génération

- `srcs/requirements/nginx/scripts/generate-certs.sh`

Usage

1. Générer un certificat pour `localhost` (par défaut) valable 365 jours :

```bash
./srcs/requirements/nginx/scripts/generate-certs.sh
```

2. (Optionnel) Générer pour un domaine personnalisé et durée en jours :

```bash
./srcs/requirements/nginx/scripts/generate-certs.sh example.com 730
```

Montage avec Docker Compose

Le `docker-compose.yml` du projet est déjà configuré pour monter ces fichiers dans le conteneur `nginx` :

- `./srcs/requirements/nginx/certs/nginx.crt` → `/etc/ssl/certs/nginx.crt`
- `./srcs/requirements/nginx/certs/nginx.key` → `/etc/ssl/private/nginx.key`

Assurez-vous d'avoir les lignes de volumes suivantes pour le service `nginx` :

```yaml
services:
  nginx:
    volumes:
      - wp_data:/var/www/html:ro
      - ./srcs/requirements/nginx/conf/default:/etc/nginx/conf.d/default.conf:ro
      - ./srcs/requirements/nginx/certs/nginx.crt:/etc/ssl/certs/nginx.crt:ro
      - ./srcs/requirements/nginx/certs/nginx.key:/etc/ssl/private/nginx.key:ro
```

Tests rapides

- Reconstruire et démarrer le service `nginx` :

```bash
docker-compose up -d --build nginx
```

- Tester TLSv1.3 :

```bash
openssl s_client -connect localhost:443 -servername localhost -tls1_3
```

- Tester TLSv1.2 :

```bash
openssl s_client -connect localhost:443 -servername localhost -tls1_2
```

Remarques

- Ces certificats sont auto-signés — les navigateurs afficheront un avertissement. Utilisez Let's Encrypt ou un CA « réel » pour la production.
- Pour renouveler, relancez le script ou planifiez une tâche qui régénère et redéploie.

Mapping DNS local (`/etc/hosts`)

Pour que le nom `llabonde.42.fr` pointe vers votre machine locale, ajoutez l'entrée suivante au fichier `/etc/hosts` sur les machines depuis lesquelles vous voulez accéder au service :

```text
# map llabonde.42.fr to local host (development)
127.0.0.1 llabonde.42.fr
```

Si vous voulez tester depuis d'autres appareils du réseau local, remplacez `127.0.0.1` par l'adresse IP locale de votre machine (par exemple `192.168.1.42`). L'édition de `/etc/hosts` requiert des droits administrateur :

```bash
sudo -- sh -c "echo '192.168.1.42 llabonde.42.fr' >> /etc/hosts"
```

Certificat et SAN

Le script `generate-certs.sh` peut maintenant générer un certificat contenant `subjectAltName` (SAN). Pour générer un certificat pour `llabonde.42.fr` et inclure une IP SAN :

```bash
./srcs/requirements/nginx/scripts/generate-certs.sh llabonde.42.fr 192.168.1.42 365
```

ou sans IP SAN (DNS uniquement) :

```bash
./srcs/requirements/nginx/scripts/generate-certs.sh llabonde.42.fr
```

Après regénération, redémarrez le conteneur nginx :

```bash
docker-compose restart nginx
```

