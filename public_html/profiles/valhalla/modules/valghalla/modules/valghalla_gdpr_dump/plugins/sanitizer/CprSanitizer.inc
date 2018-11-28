<?php

/**
 * @file
 * Ctools plugin for CPR sanitizaion.
 */

$plugin = [
  'title' => t('CPR Sanitizer'),
  'sanitize callback' => 'valghalla_gdpr_dump_cpr_sanitize',
];

/**
 * CPR sanitize callback.
 */
function valghalla_gdpr_dump_cpr_sanitize($input) {
  if (empty($input)) {
    return $input;
  }
  return str_repeat('9', 6) . '-' . str_repeat('9', 4);
}
