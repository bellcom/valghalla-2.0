<?php
/**
 * @file
 * valghalla_tfa.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function valghalla_tfa_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'tfa_basic_phone_field';
  $strongarm->value = 'field_mobile_phone';
  $export['tfa_basic_phone_field'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'tfa_basic_sms_nanp_validate';
  $strongarm->value = 0;
  $export['tfa_basic_sms_nanp_validate'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'tfa_basic_twilio_message_text';
  $strongarm->value = 'Verifikationskode: !code';
  $export['tfa_basic_twilio_message_text'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'tfa_enabled';
  $strongarm->value = 1;
  $export['tfa_enabled'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'tfa_login_plugins';
  $strongarm->value = array(
    0 => 'valghalla_tfa_trusted_ip',
  );
  $export['tfa_login_plugins'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'tfa_validate_plugin';
  $strongarm->value = 'tfa_basic_sms';
  $export['tfa_validate_plugin'] = $strongarm;

  return $export;
}
