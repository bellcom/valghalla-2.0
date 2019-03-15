<?php

/**
 * @file
 * valghalla_volunteers.monolog.inc
 */

/**
 * Implements hook_default_monolog_profiles().
 */
function valghalla_volunteers_default_monolog_profiles() {
  $export = array();

  $profile = new stdClass();
  $profile->disabled = FALSE; /* Edit this to true to make a default profile disabled initially */
  $profile->api_version = 1;
  $profile->name = 'valghalla_volunteers_profile';
  $profile->options = array(
    'handlers' => array(
      'rotating_file_handler' => array(
        'weight' => 1,
        'label' => 'Rotating File Handler',
        'level' => '200',
        'bubble' => 1,
        'filepath' => 'private://log/valghalla_volunteers.log',
        'max_files' => '30',
        'handler' => 'rotating_file',
      ),
    ),
    'label' => 'Valghalla volunteers profile',
  );
  $export['valghalla_volunteers_profile'] = $profile;

  return $export;
}
