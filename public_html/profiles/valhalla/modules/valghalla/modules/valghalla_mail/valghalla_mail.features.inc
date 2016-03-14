<?php
/**
 * @file
 * valghalla_mail.features.inc
 */

/**
 * Implements hook_node_info().
 */
function valghalla_mail_node_info() {
  $items = array(
    'email' => array(
      'name' => t('E-mail'),
      'base' => 'node_content',
      'description' => t('Mailskabeloner'),
      'has_title' => '1',
      'title_label' => t('Navn på E-mail skabelon'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
