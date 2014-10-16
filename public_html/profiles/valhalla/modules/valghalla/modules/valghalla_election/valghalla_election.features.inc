<?php
/**
 * @file
 * valghalla_election.features.inc
 */

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
      'title_label' => t('Title'),
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
  return $items;
}
