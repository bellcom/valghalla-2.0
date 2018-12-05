#!/usr/bin/env bash

DRUSH_EXEC=$(which drush)

${DRUSH_EXEC} en module_missing_message_fixer -y;
${DRUSH_EXEC} mmmff --all;
${DRUSH_EXEC} dis module_missing_message_fixer -y
${DRUSH_EXEC} pm-uninstall views_export module_missing_message_fixer;
