###########################
# Project-wide Makefile
###########################

DOMAIN ?= llabonde.42.fr
IP ?=
DAYS ?= 365
SERVICE ?=
COMPOSE ?= docker-compose

.PHONY: help certs build up up-service restart restart-service reload logs ps down clean-volumes all dev

help:
	@echo "Usage: make <target> [DOMAIN=your.domain IP=1.2.3.4 DAYS=365 SERVICE=svc]"
	@echo
	@echo "Project targets:"
	@echo "  certs           Generate self-signed certs (default DOMAIN=$(DOMAIN))"
	@echo "  build           Build all images (uses docker-compose build)"
	@echo "  up              Build and start all services (detached)"
	@echo "  up-service      Build and start a single service (SERVICE=<name>)"
	@echo "  restart         Restart all services"
	@echo "  restart-service Restart a single service (SERVICE=<name>)"
	@echo "  reload          Reload nginx config inside the running nginx container"
	@echo "  logs            Follow logs for a service (SERVICE=<name>)"
	@echo "  ps              Show docker-compose ps"
	@echo "  down            Stop all services"
	@echo "  clean-volumes   Stop and remove containers, networks and volumes"
	@echo "  all             Generate certs and start all services"

# Generate certificate. Pass DOMAIN, optional IP (IP SAN) and DAYS.
certs:
	@echo "Generating certificate for $(DOMAIN) (IP=$(IP)) for $(DAYS) days..."
	@./srcs/requirements/nginx/scripts/generate-certs.sh $(DOMAIN) $(IP) $(DAYS)

build:
	@echo "Building all images..."
	@$(COMPOSE) build

up:
	@echo "Bringing up all services (build + up -d)..."
	@$(COMPOSE) up -d --build

up-service:
	@{ if [ -z "$(SERVICE)" ]; then echo "Specify SERVICE=<name>"; exit 1; fi }
	@echo "Bringing up service $(SERVICE)..."
	@$(COMPOSE) up -d --build $(SERVICE)

restart:
	@echo "Restarting all services..."
	@$(COMPOSE) restart

restart-service:
	@{ if [ -z "$(SERVICE)" ]; then echo "Specify SERVICE=<name>"; exit 1; fi }
	@echo "Restarting service $(SERVICE) ..."
	@$(COMPOSE) restart $(SERVICE)

reload:
	@echo "Reloading nginx inside container (nginx)..."
	@docker exec nginx nginx -s reload || true

logs:
	@{ if [ -z "$(SERVICE)" ]; then echo "Specify SERVICE=<name>"; exit 1; fi }
	@$(COMPOSE) logs -f $(SERVICE)

ps:
	@$(COMPOSE) ps

down:
	@echo "Stopping all services..."
	@$(COMPOSE) down

clean-volumes:
	@echo "Stopping and removing containers, networks and volumes..."
	@$(COMPOSE) down -v

dev: certs up

all: certs up
