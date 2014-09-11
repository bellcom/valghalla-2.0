<?php
/**
 * @file
 * valghalla_polling_station.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function valghalla_polling_station_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function valghalla_polling_station_node_info() {
  $items = array(
    'polling_station' => array(
      'name' => t('Valgsted'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Valgstedets navn'),
      'help' => '',
    ),
  );
  return $items;
}
