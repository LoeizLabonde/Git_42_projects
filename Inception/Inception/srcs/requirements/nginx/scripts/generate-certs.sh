#!/usr/bin/env bash
set -euo pipefail

# generate-certs.sh
# Usage: ./generate-certs.sh [domain] [days]
# Default: domain=localhost, days=365

DOMAIN=${1:-localhost}
IP_SAN=${2:-}
DAYS=${3:-365}

# If script was called like: ./generate-certs.sh <domain> <days>
# (because the IP argument was omitted and the DAYS value became $2),
# detect a numeric $2 and shift it into DAYS while clearing IP_SAN.
if [ -z "${3-}" ] && [ -n "${2-}" ] && printf '%s' "$2" | grep -Eq '^[0-9]+$$'; then
  DAYS="$2"
  IP_SAN=""
fi
BASEDIR="$(cd "$(dirname "$0")/.." && pwd)"
CERTDIR="$BASEDIR/certs"

mkdir -p "$CERTDIR"

CRT_PATH="$CERTDIR/nginx.crt"
KEY_PATH="$CERTDIR/nginx.key"

echo "Generating self-signed certificate for '$DOMAIN' (valid for $DAYS days)" >&2

# Build subjectAltName extension. Include DNS and optional IP if provided.
if [ -n "$IP_SAN" ]; then
  ADD_EXTS="subjectAltName=DNS:$DOMAIN,IP:$IP_SAN"
else
  ADD_EXTS="subjectAltName=DNS:$DOMAIN"
fi

# Use openssl -addext when available (OpenSSL >= 1.1.1). Fall back to config file otherwise.
if openssl req -help 2>&1 | grep -F -q -- "-addext"; then
  openssl req -x509 -nodes -days "$DAYS" -newkey rsa:2048 \
    -keyout "$KEY_PATH" \
    -out "$CRT_PATH" \
    -subj "/CN=$DOMAIN" \
    -addext "$ADD_EXTS" >/dev/null 2>&1
else
  TMPF=$(mktemp)
  cat > "$TMPF" <<EOF
[ req ]
default_bits = 2048
distinguished_name = req_distinguished_name
req_extensions = v3_req

[ req_distinguished_name ]

[ v3_req ]
subjectAltName = $ADD_EXTS
EOF
  openssl req -x509 -nodes -days "$DAYS" -newkey rsa:2048 \
    -keyout "$KEY_PATH" -out "$CRT_PATH" -subj "/CN=$DOMAIN" \
    -config "$TMPF" -extensions v3_req >/dev/null 2>&1
  rm -f "$TMPF"
fi

chmod 600 "$KEY_PATH"

echo "Created:" >&2
echo "  Certificate: $CRT_PATH" >&2
echo "  Private key: $KEY_PATH" >&2

cat <<'EOF'
Next steps:
 - Mount these files into your nginx container (see README in same folder).
 - Add an /etc/hosts entry on the machine(s) that will access the site mapping
   'llabonde.42.fr' to your host IP (e.g. 127.0.0.1 or 192.168.x.x).
 - Browsers will still warn because the cert is self-signed — acceptable for local/dev only.
EOF

exit 0
