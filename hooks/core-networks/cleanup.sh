#!/bin/bash

. $(dirname $0)/_settings.inc
. $(dirname $0)/_functions.inc

get_api_token
get_api_dns_zone
delete_acme_challenge_record
commit_api_dns_changes
