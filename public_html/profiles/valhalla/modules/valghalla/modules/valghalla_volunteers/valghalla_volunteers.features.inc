<?php
/**
 * @file
 * valghalla_volunteers.features.inc
 */

/**
 * Implements hook_node_info().
 */
function valghalla_volunteers_node_info() {
  $items = array(
    'roles' => array(
      'name' => t('Roles of volunteers'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Role'),
      'help' => '',
    ),
    'volunteers' => array(
      'name' => t('Frivillige'),
      'base' => 'node_content',
      'description' => t('used to store information on volunteers in the system'),
      'has_title' => '1',
      'title_label' => t('Navn'),
      'help' => '',
    ),
  );
  return $items;
}
