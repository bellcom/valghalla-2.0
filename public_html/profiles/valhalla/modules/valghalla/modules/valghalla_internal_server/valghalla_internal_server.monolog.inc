<?php

/**
 * @file
 * Valghalla_internal_server.monolog.inc.
 */

/**
 * Implements hook_default_monolog_profiles().
 */
function valghalla_internal_server_default_monolog_profiles() {
  $export = array();

  $profile = new stdClass();
  $profile->disabled = FALSE; /* Edit this to true to make a default profile disabled initially */
  $profile->api_version = 1;
  $profile->name = 'valghalla_internal_server_profile';
  $profile->options = array(
    'handlers' => array(
      'rotating_file_handler' => array(
        'weight' => 1,
        'label' => 'Rotating File Handler',
        'level' => '200',
        'bubble' => 1,
        'filepath' => 'private://log/valghalla_internal_server.log',
        'max_files' => '30',
        'handler' => 'rotating_file',
      ),
    ),
    'label' => 'Valghalla Internal Server Logging profile',
  );
  $export['valghalla_internal_server_profile'] = $profile;

  return $export;
}
