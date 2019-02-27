<?php
/**
 * @file
 * valghalla_gdpr_dump.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function valghalla_gdpr_dump_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'gdpr_dump_empty_tables';
  $strongarm->value = array();
  $export['gdpr_dump_empty_tables'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'gdpr_dump_table_map';
  $strongarm->value = array(
    'field_data_field_cpr_number' => array(
      'field_cpr_number_value' => 'CprSanitizer',
    ),
    'field_data_field_email' => array(
      'field_email_email' => 'EmailSanitizer',
    ),
    'field_data_field_phone' => array(
      'field_phone_value' => 'NumberSanitizer',
    ),
    'field_data_field_phone2' => array(
      'field_phone2_value' => 'NumberSanitizer',
    ),
    'field_revision_field_cpr_number' => array(
      'field_cpr_number_value' => 'CprSanitizer',
    ),
    'field_revision_field_email' => array(
      'field_email_email' => 'EmailSanitizer',
    ),
    'field_revision_field_phone' => array(
      'field_phone_value' => 'NumberSanitizer',
    ),
    'field_revision_field_phone2' => array(
      'field_phone2_value' => 'NumberSanitizer',
    ),
  );
  $export['gdpr_dump_table_map'] = $strongarm;

  return $export;
}
