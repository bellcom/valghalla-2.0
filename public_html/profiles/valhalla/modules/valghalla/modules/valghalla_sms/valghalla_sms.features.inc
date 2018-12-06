<?php

/**
 * @file
 * valghalla_sms.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function valghalla_sms_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function valghalla_sms_node_info() {
  $items = array(
    'sms' => array(
      'name' => t('SMS skabelon'),
      'base' => 'node_content',
      'description' => t('Skabelon SMS til notifikationer'),
      'has_title' => '1',
      'title_label' => t('Navn på SMS skabelon'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
