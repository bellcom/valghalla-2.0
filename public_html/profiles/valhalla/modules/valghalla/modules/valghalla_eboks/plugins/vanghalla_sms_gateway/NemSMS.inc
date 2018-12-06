<?php
/**
 * @file
 * Ctools plugin for Valghalla notification NemSMS gateway .
 */

$plugin = [
  'title' => t('NemSMS gateway'),
  'callback' => 'nemsms_send',
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
