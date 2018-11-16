<?php
/**
 * @file
 * valghalla_election.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function valghalla_election_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function valghalla_election_node_info() {
  $items = array(
    'constituency' => array(
      'name' => t('Valgstedskreds'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Titel'),
      'help' => '',
    ),
    'election' => array(
      'name' => t('Valg'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Titel på valg'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
