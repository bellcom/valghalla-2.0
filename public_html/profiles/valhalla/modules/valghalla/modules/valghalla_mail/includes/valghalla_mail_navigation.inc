<?php
/**
 * @file
 * Handles the navigation of the valghalla_mail_sendmail form
 */

module_load_include('inc', 'node', 'node.pages');

/**
 * Generate a header which informs the user of which stage they're on.
 */
function valghalla_mail_sendmail_get_header($form, &$form_state) {
  $form_state['stage'] = isset($form_state['stage']) ? $form_state['stage'] : 1;

  $form_stages = array(
    'create_email_node' => 1,
    'get_recipients' => 2,
    'send_confirm' => 3,
  );

  $current_step = 1;
  if (isset($form_stages[$form_state['stage']])) {
   $current_step = $form_stages[$form_state['stage']];
  }

  $stages = array(
    1 => array('data' => '1. Opret en mail'),
    2 => array('data' => '2. Modtagere'),
    3 => array('data' => '3. Send mail'),
  );

  $stages[$current_step]['data'] = '<b>' . $stages[$current_step]['data'] . '</b>';

  $stages_list = theme('item_list', array('items' => $stages));

  $form['header'] = array(
    '#type' => 'fieldset',
    '#title' => 'Send mail til frivillige.',
  );
  $form['header']['steps'] = array(
    '#markup' => $stages_list,
  );

  return $form;
}

/**
 * Given the current stage the user is on, calculate what the next step would be
 */
function valghalla_mail_sendmail_move_to_next_stage($form, &$form_state) {
  switch ($form_state['stage']) {
    case 'create_email_node':
      return 'get_recipients';
     break;

    case 'get_recipients':
      return 'send_confirm';
     break;
  }
}

/**
 * Given the current stage the user is on, calculate what the previous step
 * would be
 */
function valghalla_mail_sendmail_move_to_previous_stage($form, &$form_state) {
  switch ($form_state['stage']) {
    case 'get_recipients':
      return 'create_email_node';
     break;

    case 'send_confirm':
      return 'get_recipients';
     break;
  }
}
