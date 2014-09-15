<?php
/**
 * @file
 * valghalla_volunteers.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function valghalla_volunteers_taxonomy_default_vocabularies() {
  return array(
    'volonteers_meeting_time' => array(
      'name' => 'volonteers_meeting_time',
      'machine_name' => 'volonteers_meeting_time',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => -9,
    ),
  );
}
