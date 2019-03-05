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
      // Do sync even if it's failed.
      variable_set('valghalla_synch_ok', TRUE);
      valghalla_internal_server_perform_synch(TRUE);
    }
    // Do synch check, if asked.
    if (isset($form_state['triggering_element']) && $form_state['triggering_element']['#id'] == 'edit-check-synch-now') {
      // Do sync even if it's failed.
      if (!valghalla_internal_server_synch_check()) {
        drupal_set_message("Synchronization check failed. See log messages for details.", 'warning');
      }
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
      '#title' => t('Synch frequency (via cron)'),
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
      '#description' => t('Attempt running synch every cron, but keep delays between synchs at least N minutes.'),
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

    $form['valghalla_internal_server_fs']['valghalla_external_server_synch_check'] = array(
      '#type' => 'fieldset',
      '#title' => t('Synchronization check settings'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    $form['valghalla_internal_server_fs']['valghalla_external_server_synch_check']['valghalla_internal_server_run_failed_sync'] = array(
      '#type' => 'checkbox',
      '#title' => t('Kør fejl synch'),
      '#default_value' => variable_get('valghalla_internal_server_run_failed_sync', VALGHALLA_INTERNAL_SERVER_RUN_FAILED_SYNC),
    );

    $form['valghalla_internal_server_fs']['valghalla_external_server_synch_check']['valghalla_internal_server_failed_sync_report_mail'] = array(
      '#type' => 'textfield',
      '#title' => t('Send report about failed sync to email:'),
      '#default_value' => variable_get('valghalla_internal_server_failed_sync_report_mail'),
      '#description' => t('In case of failed synchronization will be detected drupal will send email message to addresses listed in this field.'),
    );

    $form['valghalla_internal_server_fs']['valghalla_external_server_synch_check']['valghalla_internal_server_failed_sync_report_frequency'] = array(
      '#type' => 'select',
      '#title' => t('Report sending frequency'),
      '#options' => array(
        0 => 'Every check',
        900 => '15 minutes',
        1800 => '30 minutes',
        3600 => '1 hour',
        10800 => '3 hours',
        21600 => '6 hours',
        43200 => '12 hours',
        86400 => '1 day',
      ),
      '#default_value' => variable_get('valghalla_internal_server_failed_sync_report_frequency', 0),
      '#description' => t('Attempt send failed report every check, but keep delays between sending at least specific time..'),
      '#states' => array(
        'invisible' => array(
          ':input[name="valghalla_internal_server_failed_sync_report_mail"]' => array('value' => ''),
        ),
      ),
    );

    $form['valghalla_internal_server_fs']['valghalla_external_server_synch_check']['check_synch_now'] = array(
      '#type' => 'button',
      '#value' => t('Check synchronization now'),
    );

    $form['valghalla_internal_server_fs']['valghalla_external_server_synch_check'][] = array(
      '#markup' => '<div>' . t('Last synchronization check: @datetime', array('@datetime' => format_date(variable_get('valgalla_internal_server_last_synch_check')))) . '</div>',
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

/**
 * Admin form for searching log messages.
 */
function valghalla_internal_server_logs_table_form($form, &$form_state) {
  $header = array(
    'target_id' => array(
      'data' => t('Volunteer'),
      'type' => 'property',
    ),
    'cpr' => array(
      'data' => t('CPR'),
      'type' => 'property',
      'field' => 'cpr',
    ),
    'message' => array('data' => t('Message')),
    'timestamp' => array(
      'data' => t('Timestamp'),
      'type' => 'property',
      'field' => 'timestamp',
      'sort' => 'asc',
    ),
  );

  $query = db_select('valghalla_internal_server_logs', 'v')
    ->fields('v');

  $search_params = array();
  if (!empty($_GET['date_filter'])) {
    $search_params['date_filter'] = $_GET['date_filter'];

    switch ($search_params['date_filter']) {
      case 'last_hour':
        $query->condition('timestamp', strtotime('-1 hour'), '>=');
        break;

      case 'today':
        $query->condition('timestamp', strtotime('today midnight'), '>=');
        break;

      case 'last_30_days':
        $query->condition('timestamp', strtotime('-30 days'), '>=');
        break;
    }
  }
  else {
    // Last hour is default filtering.
    $query->condition('timestamp', strtotime('-1 hour'), '>=');
  }

  $query = $query->extend('PagerDefault')
    ->extend('TableSort')
    ->limit(10)
    ->orderByHeader($header);

  $result = $query->execute()->fetchAllAssoc('target_id');
  $nodes = node_load_multiple(array_keys($result));

  $options = array();
  foreach ($result as $log) {
    $node = isset($nodes[$log->target_id]) ? $nodes[$log->target_id] : NULL;
    $options[$log->id] = array(
      'target_id' => $node ? '<a href=' . url('node/' . $node->nid) . '>' . $node->title . '</a>' : t('Deleted'),
      'cpr' => $log->cpr,
      'message' => implode('<br/>', unserialize($log->message)),
      'timestamp' => format_date($log->timestamp, 'short'),
    );
  }

  $form['search'] = array(
    '#type' => 'fieldset',
    '#title' => t('Basic Search'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['search']['date_filter'] = array(
    '#type' => 'select',
    '#title' => t('Date filter'),
    '#options' => array(
      'last_hour' => t('Last hour'),
      'today' => t('Today'),
      'last_30_days' => t('Last 30 days'),
      'all' => t('Show all'),
    ),
    '#default_value' => !empty($search_params['date_filter']) ? $search_params['date_filter'] : 'last_hour',
  );

  $form['search']['search_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Search'),
  );

  $form['entities'] = array(
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $options,
    '#attributes' => array('class' => array('entity-sort-table')),
    '#empty' => t('No content.'),
  );
  $form['pager'] = array('#theme' => 'pager');

  return $form;
}

/**
 * Logs messages table for submit method.
 */
function valghalla_internal_server_logs_table_form_submit($form, &$form_state) {
  $values = $form_state['input'];

  drupal_goto('admin/valghalla/validator/internal_server_logs', array(
    'query' => array(
      'date_filter' => $values['date_filter'],
    ),
  ));
}
