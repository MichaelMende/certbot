# Functions

## Get Core-Networks API token
get_api_token() {
  echo -n "GET API token: ... "
  CORE_API_TOKEN=$(curl --silent --fail --request POST --data '{"login":"'${CORE_API_LOGIN}'","password":"'${CORE_API_PASSWORD}'"}' ${CORE_API_URL}/auth/token | jq -r '.token')
  echo done
}

## Get Zone Name
get_api_dns_zone() {
  CORE_API_DNS_ZONES=$(curl --silent --fail -H "Authorization: Bearer ${CORE_API_TOKEN}" ${CORE_API_URL}/dnszones/ | jq -r '.[].name')
  CORE_API_DNS_ZONE=$(echo "${CORE_API_DNS_ZONES} ${CERTBOT_DOMAIN}"  | tr " " "\n" | grep -Ev "^[[:space:]]*$" | rev | sort | rev | grep "^${CERTBOT_DOMAIN}$" -B 1| head -1)
  echo "${CERTBOT_DOMAIN}" | grep -Eq "^([[:alnum:]-]+\.)*${CORE_API_DNS_ZONE}$"
}

## Delete old _acme-challenge.* DNS record (if exists)
delete_acme_challenge_record(){
  echo -n "DELETE old _acme-challenge.* DNS record (if exists): ... "
  curl --silent --fail -H "Authorization: Bearer ${CORE_API_TOKEN}" --fail --request POST --data '{"name":"_acme-challenge.'${CERTBOT_DOMAIN}'.","type":"TXT"}' ${CORE_API_URL}/dnszones/${CORE_API_DNS_ZONE}/records/delete
  echo done
}

## Create new _acme-challenge.* DNS record
create_acme_challenge_record(){
  echo -n "CREATE new _acme-challenge.* DNS record: ... "
  curl --silent --fail -H "Authorization: Bearer ${CORE_API_TOKEN}" --fail --request POST --data '{"name":"_acme-challenge.'${CERTBOT_DOMAIN}'.","type":"TXT","data":"'${CERTBOT_VALIDATION}'"}' ${CORE_API_URL}/dnszones/${CORE_API_DNS_ZONE}/records/
  echo done
}

## Commit new _acme-challenge.* DNS record
commit_api_dns_changes(){
  echo -n "COMMIT new _acme-challenge.* DNS record: ... "
  curl --silent --fail -H "Authorization: Bearer ${CORE_API_TOKEN}" --fail --request POST ${CORE_API_URL}/dnszones/${CORE_API_DNS_ZONE}/records/commit
  echo done
}

# vim: ft=sh
