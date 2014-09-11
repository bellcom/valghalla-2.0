<?php
/**
 * @file
 * Handles the form submission of the valghalla_mail_sendmail form
 * @author Yani Xu <yx@bellcom.dk>
 */

/**
 * Handles what to do with the submitted form depending on what stage has been
 * completed.
 *
 * @see valghalla_mail_sendmail_form()
 */
function valghalla_mail_sendmail_form_submit($form, &$form_state) {
  switch ($form_state['stage']) {
    case 'send_confirm':
      $form_state['multistep_values'][$form_state['stage']] = $form_state['values'];
      if ($form_state['triggering_element']['#value'] != 'Tilbage') {
        valghalla_mail_sendmail_send_confirm_submit($form, $form_state);
        $form_state['complete'] = TRUE;
      }
      break;

    default:
      $form_state['multistep_values'][$form_state['stage']] = $form_state['values'];
      $form_state['new_stage'] = valghalla_mail_sendmail_move_to_next_stage($form, $form_state);
      break;
  }

  if ($form_state['triggering_element']['#value'] == 'Tilbage') {
    $form_state['new_stage'] = valghalla_mail_sendmail_move_to_previous_stage($form, $form_state);
  }

  if (isset($form_state['multistep_values']['form_build_id'])) {
    $form_state['values']['form_build_id'] = $form_state['multistep_values']['form_build_id'];
  }
  $form_state['multistep_values']['form_build_id'] = $form_state['values']['form_build_id'];
  $form_state['stage'] = $form_state['new_stage'];
  $form_state['rebuild'] = TRUE;
}

/**
 * Submit handler for sendinvitation
 */
function valghalla_mail_sendinvitation_form_submit($form, &$form_state) {
  $election_node = node_load($form_state['multistep_values']['get_recipients']['election_nid']);
  if(is_object($election_node)){
    $election_node->field_election_mails_send[$election_node->language][0]['value'] = 1;
    node_save($election_node);
  }

  valghalla_mail_sendmail_send_confirm_submit($form, $form_state);
}

 /**
  * Handles the submission of the final stage
  * Step 3 : Send mails
  *
  */
function valghalla_mail_sendmail_send_confirm_submit($form, &$form_state){
  $multistep_values = $form_state['multistep_values'];

  // If the user is sending invitations and clicks back, send to the overview
  // page.
  if(isset($multistep_values['get_recipients']['invitation']) && $form_state['clicked_button']['#array_parents'][0] == 'back'){
    drupal_goto('admin/valghalla');
  }

  $mail_nid = $multistep_values['get_recipients']['valghalla_mail_email_node_ID'];
  $volunteers_nids = valghalla_mail_sendmail_get_recipients($multistep_values['get_recipients']);

  $mail_chunks = array_chunk($volunteers_nids, 10);

  foreach($mail_chunks as $mail_batch){
    $operations[] = array(
      'valghalla_mail_send_batch', array($mail_nid, $mail_batch, $form_state),
    );
  }

  batch_set(
    array(
      'title' => t('Sender E-mails'),
      'operations' => $operations,
      'finished' => 'valghalla_mails_send_batch_finished',
      'progress_message' => t('Sender blok @current ud af @total. Hver blok indeholder (op til) 10 modtagere.'),
      'file' => drupal_get_path('module', 'valghalla_mail') . '/includes/valghalla_mail_submit.inc',
    )
  );
}

function valghalla_mail_send_batch($mail_nid, $recipients, $form_state, &$context){
  $multistep_values = $form_state['multistep_values'];
  $mail_nid = $multistep_values['get_recipients']['valghalla_mail_email_node_ID'];
  $sendMailList_count = $form_state['valghalla_sendlist']['valghalla_sendlist_acount'];

  $mail_sender = $multistep_values['get_recipients']['email_sender'];
  if ($mail_sender) {
    $from = $multistep_values['get_recipients']['user_email'];
  }
  else {
    $from = variable_get('site_mail', 'admin@example.com');
  }
  $language = language_default();

  foreach($recipients as $nid => $fc_id){
    $volunteer_fc = entity_load_single('field_collection_item', $fc_id);
    if(!is_object($volunteer_fc)){
      continue;
    }
    $tokens = _valghalla_helper_get_token_values($volunteer_fc);

    if($mail_nid == 'invite'){
      $election_nid = $multistep_values['get_recipients']['election_nid'];
      $params = valghalla_mail_get_mail($election_nid, $tokens['!position_nid'], 'invitation');
    }
    else {
      $params = valghalla_mail_get_mail(FALSE, FALSE, FALSE, $mail_nid);
    }
    $to = $tokens['!email'];
    $params = array_merge(array('tokens' => $tokens), $params);
    $result = drupal_mail('valghalla_mail', 'mail', $to, $language, $params, $from, TRUE);
    if ($result['result'] == TRUE) {
      $msg = t('Mail nid = %nid is sent to email=%email');
      watchdog(
        'Valghalla mail', $msg, $variables = array(
          '%nid' => $mail_nid,
          '%email' => $to
          )
      );
    }
    else {
      $msg = t('Error : Mail nid = %nid is NOT sent to email=%email');
      watchdog(
        'Valghalla mail', $msg, $variables = array(
          '%nid' => $mail_nid,
          '%email' => $to
          )
      );
    }
  }

  $context['message'] = "Det er vigtigt at du ikke forlader denne side!";
}

function valghalla_mails_send_batch_finished($success, $results, $operations){
  if($success){
    drupal_set_message(t('E-mails er blevet sendt'));
    drupal_goto('valghalla/administration/valg');
  }
}
