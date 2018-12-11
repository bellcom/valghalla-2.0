<?php

/**
 * @file
 * Valghalla_internal_server_pages.inc.
 */

use ValghallaInternalServer\ExternalWebservice;

/**
 * Implements hook_form_alter().
 */
function valghalla_internal_server_form_alter(&$form, &$form_state, $form_id) {
  if ($form_id === 'valhalla_admin_settings_form') {
    // Do synch, if asked.
    if (isset($form_state['triggering_element']) && $form_state['triggering_element']['#id'] == 'edit-synch-now') {
      valghalla_internal_server_cron();
    }

    $form['valghalla_internal_server_enable'] = array(
      '#type' => 'checkbox',
      '#title' => t('Valghalla intern server aktiv'),
      '#default_value' => variable_get('valghalla_internal_server_enable', FALSE),
      '#weight' => 10,
    );

    $form['valghalla_internal_server_fs'] = array(
      '#type' => 'fieldset',
      '#title' => t('Valghalla intern server indstillinger'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
      '#weight' => 11,
      '#states' => array(
        'invisible' => array(
          ':input[name="valghalla_internal_server_enable"]' => array('checked' => FALSE),
        ),
      ),
    );

    $form['valghalla_internal_server_fs']['valghalla_external_server_endpoint'] = array(
      '#type' => 'textfield',
      '#title' => t('External server endpoint URL'),
      '#default_value' => variable_get('valghalla_external_server_endpoint'),
      '#description' => t('The webservice endpoint URL of the external server. Do not add trailing slash!'),
      '#required' => TRUE,
    );

    $form['valghalla_internal_server_fs']['valghalla_external_server_user'] = array(
      '#type' => 'textfield',
      '#title' => t('Endpoint username'),
      '#default_value' => variable_get('valghalla_external_server_user'),
      '#description' => t('The webservice username'),
      '#required' => TRUE,
    );

    $form['valghalla_internal_server_fs']['valghalla_external_server_password'] = array(
      '#type' => 'password',
      '#title' => t('Endpoint user password'),
      '#description' => t('The webservice password. Leave blank if not changed'),
    );

    $form['valghalla_internal_server_fs']['valghalla_external_server_hash_salt'] = array(
      '#type' => 'textfield',
      '#title' => t('Endpoint hash salt'),
      '#default_value' => variable_get('valghalla_external_server_hash_salt'),
      '#description' => t('The webservice hash salt. NB! You have to specify the correct hash salt of your external server, otherwise the communication will not work'),
      '#required' => TRUE,
    );

    $form['valghalla_internal_server_fs']['valghalla_external_server_synch_frequency'] = array(
      '#type' => 'select',
      '#title' => t('Synch frequency'),
      '#options' => array(
        '0' => 'As often as cron',
        '1' => '1 minute',
        '2' => '2 minutes',
        '3' => '3 minutes',
        '5' => '5 minutes',
        '10' => '10 minutes',
        '15' => '15 minutes',
        '30' => '30 minutes',
      ),
      '#default_value' => variable_get('valghalla_external_server_synch_frequency', 0),
      '#description' => t('Run synch every N minutes.'),
      '#required' => TRUE,
    );

    $form['valghalla_internal_server_fs']['valghalla_external_server_synch_error_message'] = array(
      '#type' => 'textarea',
      '#title' => t('Synch error message'),
      '#default_value' => variable_get('valghalla_external_server_synch_error_message'),
      '#description' => t('Provide a custom message that will be presenter if synch fails'),
    );

    $form['valghalla_internal_server_fs']['valghalla_external_server_synch_now_fs'] = array(
      '#type' => 'fieldset',
      '#title' => t('Synch now'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );

    $form['valghalla_internal_server_fs']['valghalla_external_server_synch_now_fs']['synch_now'] = array(
      '#type' => 'button',
      '#value' => t('Synch now'),
    );

    $form['valghalla_internal_server_fs']['valghalla_external_server_synch_now_fs'][] = array(
      '#markup' => '<div>' . t('Last pulled: @datetime', array('@datetime' => format_date(variable_get('valgalla_internal_server_last_clone_timestamp')))) . '</div>'
      . '<div>' . t('Last pushed: @datetime', array('@datetime' => format_date(variable_get('valgalla_internal_server_last_push_timestamp')))) . '</div>',
    );

    $form = system_settings_form($form);
    array_unshift($form['#submit'], 'valghalla_internal_server_settings_form_submit');
  }
}

/**
 * Additional valghalla_internal_server_settings form submit handler.
 *
 * Unsetting password on form submit if password is empty.
 *
 * @param mixed $form
 *   Form.
 * @param mixed $form_state
 *   Form state.
 */
function valghalla_internal_server_settings_form_submit($form, &$form_state) {
  if ($form_state['values']['valghalla_external_server_password'] == '') {
    unset($form_state['values']['valghalla_external_server_password']);
  }

  // Update heartbeat.
  $ws = new ExternalWebservice();
  variable_set('valgalla_internal_server_heartbeat', $ws->heartbeat());
}
