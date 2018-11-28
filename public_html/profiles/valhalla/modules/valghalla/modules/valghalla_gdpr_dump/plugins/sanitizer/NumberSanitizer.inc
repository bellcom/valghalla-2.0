<?php

/**
 * @file
 * Ctools plugin for number sanitizaion.
 */

$plugin = [
  'title' => t('Number Sanitizer'),
  'sanitize callback' => 'valghalla_gdpr_dump_cpr_sanitize_num_sanitize',
];

/**
 * Number sanitize callback.
 */
function valghalla_gdpr_dump_cpr_sanitize_num_sanitize($input) {
  if (empty($input)) {
    return $input;
  }
  return str_repeat('9', strlen($input));
}
