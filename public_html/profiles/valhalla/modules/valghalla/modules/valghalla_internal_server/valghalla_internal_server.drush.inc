<?php

/**
 * @file
 * Valghalla_internal_server.drush.inc.
 */

/**
 * Implements hook_drush_command().
 */
function valghalla_internal_server_drush_command() {
  $items = array();
  $items['valghalla-internal-synch'] = array(
    'callback' => 'valghalla_internal_server_perform_synch',
    'description' => 'Drush command perform Valghalla Internal server synch process.',
    'aliases' => array('valg-is'),
    'examples' => array(
      'Perform Valghalla internal server synch' => 'drush valghalla-internal-synch',
      'Perform Valghalla internal server synch (alias)' => 'drush valg-is',
    ),
  );
  $items['valghalla-internal-synch-check'] = array(
    'callback' => 'valghalla_internal_server_synch_check',
    'description' => 'Drush command perform Valghalla Internal server synchronization check process.',
    'aliases' => array('valg-isc'),
    'examples' => array(
      'Perform Valghalla internal server synchronization check' => 'drush valghalla-internal-synch-check',
      'Perform Valghalla internal server synchronization check (alias)' => 'drush valg-iss',
    ),
  );
  return $items;
}
