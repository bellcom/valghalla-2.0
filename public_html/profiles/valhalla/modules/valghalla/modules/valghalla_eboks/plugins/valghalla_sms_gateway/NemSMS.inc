<?php
/**
 * @file
 * Ctools plugin for Valghalla notification NemSMS gateway .
 */

$plugin = [
  'title' => t('NemSMS gateway'),
  // Send plugin callback.
  'callback' => 'nemsms_send',
  // Optional send to callback.
  // @see valghalla_sms_send_to().
  'send_to_callback' => 'nemsms_send_to',
];

/**
 * NemSMS send callback.
 */
function nemsms_send($to, $message, $context) {
  module_load_include('inc', 'valghalla_eboks', 'includes/ServicePlatformenPrintNemSMS');
  $service = new ServicePlatformenPrintNemSMS();
  $service->prepareRequest($message, $context);
  $service->setTo($to);
  $result = $service->sendMessage();
  if (!$result['status']) {
    watchdog('valghalla_eboks', 'WS request failed. Error message: %message', array('%message' => $result['text']), WATCHDOG_ERROR);
  }

  return $result;
}

/**
 * Send to callback.
 *
 * @param object $entity
 *   Volunteer node entity.
 *
 * @return string
 *   CPR field value or FALSE.
 */
function nemsms_send_to($entity) {
  if ($field = field_get_items('node', $entity, 'field_cpr_number')) {
    return $field[0]['value'];
  }
  return FALSE;
}
