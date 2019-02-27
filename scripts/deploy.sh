#!/usr/bin/env bash

DRUSH_EXEC=$(which drush)

${DRUSH_EXEC} updb -y;
${DRUSH_EXEC} composer-json-rebuild;
${DRUSH_EXEC} composer-manager install -y;

${DRUSH_EXEC} cc all;

