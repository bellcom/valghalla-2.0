<?php

/**
 * @file
 * Handles the navigation of the valghalla_notification_send_message form.
 */

/**
 * Generate a header which informs the user of which stage they're on.
 */
function valghalla_notifications_get_navigation_header(&$form, &$form_state) {
  $form_state['storage']['stage'] = isset($form_state['storage']['stage']) ? $form_state['storage']['stage'] : 1;

  $form_stages = array(
    'create_message_node' => 1,
    'get_recipients' => 2,
    'send_confirm' => 3,
  );

  $current_step = 1;
  if (isset($form_stages[$form_state['storage']['stage']])) {
    $current_step = $form_stages[$form_state['storage']['stage']];
  }

  $stages = array(
    1 => array('data' => t('1. Opret en besked')),
    2 => array('data' => t('2. Modtagere')),
    3 => array('data' => t('3. Send besked')),
  );

  $stages[$current_step]['data'] = '<strong>' . $stages[$current_step]['data'] . '</strong>';

  $stages_list = theme('item_list', array('items' => $stages));

  $form['header'] = array(
    '#type' => 'fieldset',
    '#title' => t('Send besked til deltagere.'),
    '#weight' => -100,
  );
  $form['header']['steps'] = array(
    '#markup' => $stages_list,
  );
}

/**
 * Given the current stage the user is on, calculate the next step would be.
 */
function valghalla_notifications_send_next_stage($form, &$form_state) {
  $next_stage = array(
    'create_message_node' => 'get_recipients',
    'get_recipients' => 'send_confirm',
  );
  return isset($next_stage[$form_state['storage']['stage']]) ? $next_stage[$form_state['storage']['stage']] : FALSE;
}

/**
 * Given the current stage the user is on, calculate the previous step would be.
 */
function valghalla_notifications_send_previous_stage($form, &$form_state) {
  $previous_stage = array(
    'get_recipients' => 'create_message_node',
    'send_confirm' => 'get_recipients',
  );
  return isset($previous_stage[$form_state['storage']['stage']]) ? $previous_stage[$form_state['storage']['stage']] : FALSE;
}
