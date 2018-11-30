<?php

/**
 * Implements hook_form_alter().
 */
function valghalla_internal_server_form_alter(&$form, &$form_state, $form_id) {
  if ($form_id === 'valhalla_admin_settings_form') {
    //TODO: activate
//    // Attempt the webservice request.
//    if (os2forms_webform_sharing_get_webform_node_export() !== NULL) {
//      drupal_set_message(t('Sharing repository set up correctly'));
//    }
//    else {
//      drupal_set_message(t('Could not connect to the repository. Check connection credentials'), 'error', FALSE);
//    }
//
    // Do synch, if asked.
    if (isset($form_state['triggering_element']) && $form_state['triggering_element']['#id'] == 'edit-synch-now') {
      valghalla_internal_server_cron();
    }


    $form['valghalla_internal_server_enable'] = array(
      '#type' => 'checkbox',
      '#title' => t('Valghalla intern server aktiv'),
      '#default_value' => variable_get('valghalla_internal_server_enable', FALSE),
      '#weight' => 10
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
      '#title' => t('Repository Endpoint URL'),
      '#default_value' => variable_get('valghalla_external_server_endpoint'),
      '#description' => t('The service endpoint URL of the remote repository. Do not add trailing slash!'),
      '#required' => TRUE,
    );

    $form['valghalla_internal_server_fs']['valghalla_external_server_user'] = array(
      '#type' => 'textfield',
      '#title' => t('Repository username'),
      '#default_value' => variable_get('valghalla_external_server_user'),
      '#description' => t('The service username.'),
      '#required' => TRUE,
    );

    $form['valghalla_internal_server_fs']['valghalla_external_server_password'] = array(
      '#type' => 'password',
      '#title' => t('Repository password'),
      '#description' => t('The service password. Leave blank if not changed'),
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
      '#markup' => '<div>' . t('Last synched: @datetime', array('@datetime' => format_date(variable_get('valgalla_internal_server_last_synch', 0)))) . '</div>'
    );

    $form = system_settings_form($form);
    array_unshift($form['#submit'], 'valghalla_internal_server_settings_form_submit');
  }
}

/**
 * Additional os2forms_webform_sharing_page_settings form submit handler.
 * Unsetting password on form submit if password is empty.
 *
 * @param $form
 * @param $form_state
 */
function valghalla_internal_server_settings_form_submit($form, &$form_state) {
  if ($form_state['values']['valghalla_external_server_password'] == '') {
    unset($form_state['values']['valghalla_external_server_password']);
  }
}
