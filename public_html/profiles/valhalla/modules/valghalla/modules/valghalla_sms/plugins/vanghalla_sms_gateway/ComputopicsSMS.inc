<?php

/**
 * @file
 * Ctools plugin for Valghalla notification Computopics SMS gateway .
 */

$plugin = [
  'title' => t('Computopics SMS gateway'),
  'callback' => 'computopic_sms_send',
];

/**
 * Computopics SMS send callback.
 */
function computopic_sms_send($to, $message, $context) {
  $result = array('status' => FALSE);
  return $result;
}
