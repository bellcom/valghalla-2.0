#!/usr/bin/env bash

BASEDIR=$(dirname "$0")
DRUSH_EXEC=$(which drush)
LOG_FILE="${BASEDIR}/../logs/deployment/deployment-$(date +"%Y%m%d-%H%M").log"

# Creates directory for logs.
mkdir -p "$(dirname "$LOG_FILE")"

# Runs deployment commands.
${DRUSH_EXEC} @sites updb -y 2>&1 | tee -a $LOG_FILE;
${DRUSH_EXEC} @sites cc all -y 2>&1 | tee -a $LOG_FILE;

echo See deployment log in file $(realpath $LOG_FILE)
