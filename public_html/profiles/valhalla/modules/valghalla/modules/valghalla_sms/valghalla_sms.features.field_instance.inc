<?php

/**
 * @file
 * valghalla_sms.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function valghalla_sms_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-sms-field_sms_body'.
  $field_instances['node-sms-field_sms_body'] = array(
    'bundle' => 'sms',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_sms_body',
    'label' => 'SMS Body',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 1,
      ),
      'type' => 'text_textarea',
      'weight' => 3,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('SMS Body');

  return $field_instances;
}
