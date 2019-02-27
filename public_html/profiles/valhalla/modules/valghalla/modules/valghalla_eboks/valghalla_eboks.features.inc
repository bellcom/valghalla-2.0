<?php

/**
 * @file
 * valghalla_eboks.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function valghalla_eboks_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function valghalla_eboks_node_info() {
  $items = array(
    'eboks' => array(
      'name' => t('eBoks skabelon'),
      'base' => 'node_content',
      'description' => t('eBoks skabeloner'),
      'has_title' => '1',
      'title_label' => t('Navn på eBoks skabelon'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
