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
      'name' => t('Roller'),
      'base' => 'node_content',
      'description' => t('Roller'),
      'has_title' => '1',
      'title_label' => t('Rolle'),
      'help' => '',
    ),
    'volunteers' => array(
      'name' => t('Deltagere'),
      'base' => 'node_content',
      'description' => t('used to store information on volunteers in the system'),
      'has_title' => '1',
      'title_label' => t('Navn'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
