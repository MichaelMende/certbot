set -e

# ENV vars to be set by user
: "${CORE_API_LOGIN:?Need to set CORE_API_LOGIN non-empty}"
: "${CORE_API_PASSWORD:?Need to set CORE_API_PASSWORD non-empty}"

CORE_API_URL="${CORE_API_URL:=https://beta.api.core-networks.de}"

# ENV vars to be set by certbot
: "${CERTBOT_DOMAIN:?Need to set CERTBOT_DOMAIN non-empty}"
: "${CERTBOT_VALIDATION:?Need to set CERTBOT_VALIDATION non-empty}"

# programs needed
type -Pfp jq   > /dev/null
type -Pfp curl > /dev/null

# vim: ft=sh
