<?php
/**
 * @file
 * Handles the form elements of valghalla_mail 'admin/valhalla/sendmail'
 *
 * @author Yani Xu <yani@bellcom.dk>
 */

/**
 * Sendmail starting point.
 *
 * @see email_node_form_alter()
 * @see valghalla_mail_sendmail_form()
 */
function valghalla_mail_sendmail_form_step(&$form, &$form_state) {
  $nid = $form_state['node']->nid;
  drupal_goto('valghalla/administration/sendto/' . $nid);
}

/**
 * Send invitation form.
 */
function valghalla_mail_sendinvitation_form($form, &$form_state, $election_nid) {
  drupal_add_css(drupal_get_path('module', 'valghalla_mail') . '/css/valghalla_mail.css');
  drupal_add_js(drupal_get_path('module', 'valghalla_mail') . '/js/valghalla_mail.js', 'file');
  $form_state['multistep_values']['get_recipients']['invitation'] = TRUE;
  $form_state['multistep_values']['get_recipients']['election_nid'] = $election_nid;
  $form_state['multistep_values']['get_recipients']['valghalla_mail_email_node_ID'] = 'invite';
  return valghalla_mail_sendmail_send_confirm_form($form, $form_state);
}

/**
 * Stage switch.
 *
 * Step 2 : get_recipients
 * Step 3 : send_confirm
 *
 * @see valghalla_mail_sendmail_form_validate()
 * @see valghalla_mail_sendmail_form_submit()
 */
function valghalla_mail_sendmail_form($form, &$form_state, $nid) {
  drupal_add_css(drupal_get_path('module', 'valghalla_mail') . '/css/valghalla_mail.css');
  drupal_add_js(drupal_get_path('module', 'valghalla_mail') . '/js/valghalla_mail.js', 'file');

  if (!isset($form_state['stage'])) {
    $form_state['stage'] = 'get_recipients';
  }

  module_load_include('inc', 'node', 'node.pages');

  $form = array();
  $form = valghalla_mail_sendmail_get_header($form, $form_state);

  switch ($form_state['stage']) {
    case 'get_recipients':
      return valghalla_mail_sendmail_get_recipients_form($form, $form_state, $nid);

    case 'send_confirm':
      return valghalla_mail_sendmail_send_confirm_form($form, $form_state);

    default:
      return valghalla_mail_sendmail_get_recipients_form($form, $form_state, $nid);
  }

  return $form;
}

/**
 * Form for Step 1 create_email_node step.
 *
 * @see valghalla_mail_form_email_node_form_alter
 */
function valghalla_mail_sendmail_create_email_node() {
  module_load_include('inc', 'node', 'node.pages');
  return node_add('email');
}

/**
 * Form for Step 2 get_recipients step.
 *
 * @see valghalla_mail_sendmail_form()
 */
function valghalla_mail_sendmail_get_recipients_form($form, &$form_state, $nid) {
  if (!is_numeric($nid) || !isset($nid)) {
    form_set_error('no_email', t("Ingen mail indhold."));
  }

  $values = isset($form_state['multistep_values']['get_recipients']) ? $form_state['multistep_values']['get_recipients'] : array();

  module_load_include('inc', 'valghalla_volunteers');
  module_load_include('inc', 'valghalla_mail');

  // Get parties from Term objects.
  $taxonomy = taxonomy_vocabulary_machine_name_load('partier');

  foreach (taxonomy_get_tree($taxonomy->vid) as $tid => $term) {
    $parties[$term->tid] = $term->name;
  }

  // Elections.
  $elections = db_select('node', 'n')
          ->fields('n', array('nid', 'title'))
          ->condition('type', 'election')
          ->execute()->fetchAllKeyed();

  // Polling stations.
  $ps = db_select('node', 'n')
          ->fields('n', array('nid', 'title'))
          ->condition('type', 'polling_station')
          ->execute()->fetchAllKeyed();

  // Roles.
  $roles = db_select('node', 'n')
          ->distinct()
          ->fields('n', array('nid', 'title'))
          ->condition('n.type', 'roles')
          ->execute()->fetchAllKeyed();

  if ($nid) {
    if ($node = node_load($nid)) {
      $description = ' <a class="form-submit" href="/node/' . $nid . '/edit?destination=valghalla/administration/sendto/' . $nid . '">' . t('edit') . '</a>';
    }
    else {
      $description = ' <a class="form-submit" href="/valghalla/administration/sendmail">' . t('Add') . '</a>';
    }
  }
  else {
    $description = ' <a class="form-submit" href="/valghalla/administration/sendmail">' . t('Add') . '</a>';
  }

  $form['mail_content']['valghalla_mail_email_node_ID'] = array(
    '#title' => t('Mail indhold'),
    '#type' => 'select',
    '#options' => array($nid => isset($node->title) ? $node->title : ''),
    '#default_value' => $nid,
    '#description' => $description,
  );

  $form['recipents'] = array(
    '#type' => 'fieldset',
    '#title' => t('Modtagere'),
    '#description' => t('Hold CTRL nede for at vælge flere. Ingen valgte vil sende til alle.'),
  );

  $form['recipents']['election'] = array(
    '#type' => 'select',
    '#title' => t('Valg'),
    '#multiple' => TRUE,
    '#options' => $elections,
    '#size' => 5,
    '#prefix' => '<div style="float:left;margin-right:2em">',
    '#suffix' => '</div>',
    '#default_value' => isset($values['election']) ? $values['election'] : NULL,
  );

  $form['recipents']['rsvp_status'] = array(
    '#type' => 'select',
    '#title' => t('RSVP Status'),
    '#options' => array(
      '1' => t('Ja'),
      '2' => t('Nej'),
      '3' => t('Aldrig'),
      '0' => t('Ubesvaret'),
    ),
    '#size' => 5,
    '#prefix' => '<div style="float:left;margin-right:2em">',
    '#suffix' => '</div>',
    '#default_value' => isset($values['rsvp_status']) ? $values['rsvp_status'] : 1,
  );

  $form['recipents']['roles'] = array(
    '#type' => 'select',
    '#title' => t('Deltager type'),
    '#multiple' => TRUE,
    '#options' => $roles,
    '#size' => 5,
    '#prefix' => '<div style="float:left;margin-right:2em">',
    '#suffix' => '</div>',
    '#default_value' => isset($values['roles']) ? $values['roles'] : NULL,
  );

  $form['recipents']['party'] = array(
    '#type' => 'select',
    '#title' => t('Parti'),
    '#multiple' => TRUE,
    '#options' => $parties,
    '#size' => 5,
    '#prefix' => '<div style="float:left;margin-right:2em">',
    '#suffix' => '</div>',
    '#default_value' => isset($values['party']) ? $values['party'] : NULL,
  );

  $form['recipents']['polling_station'] = array(
    '#type' => 'select',
    '#title' => t('Valgsted'),
    '#multiple' => TRUE,
    '#options' => $ps,
    '#size' => 5,
    '#prefix' => '<div style="float:left;margin-right:2em">',
    '#suffix' => '</div>',
    '#default_value' => isset($values['polling_station']) ? $values['polling_station'] : NULL,
  );

  $form['sender'] = array(
    '#type' => 'fieldset',
    '#title' => t('Afsender'),
  );

  $form['sender']['email_sender'] = array(
    '#type' => 'checkbox',
    '#title' => t('brug min egen mail'),
    '#description' => t('Denne vil også bruges som svar-til email, så svar fra modtageren sendes til den pågældende e-mailadresse. '),
    '#default_value' => isset($values['email_sender']) ? $values['email_sender'] : 0,
  );

  global $user;
  $form['sender']['user_email'] = array(
    '#type' => 'hidden',
    '#default_value' => $user->mail,
  );

  $form['next'] = array(
    '#type' => 'submit',
    '#value' => t('Next'),
  );

  return $form;
}

/**
 * Form for Step 3 send_confirm step.
 *
 * @see valghalla_mail_sendmail_form()
 */
function valghalla_mail_sendmail_send_confirm_form($form, &$form_state) {
  global $language;

  $values = isset($form_state['multistep_values']['get_recipients']) ? $form_state['multistep_values']['get_recipients'] : array();
  $volunteers_fcids = valghalla_mail_sendmail_get_recipients($values);

  $count = 0;
  $mail_list = "";
  $to_mails = array();
  foreach (entity_load('field_collection_item', $volunteers_fcids) as $volunteer_item) {
    $volunteer_node = $volunteer_item->hostEntity();
    $to = $volunteer_node->field_email[$language->language][0]['email'];
    $recipients = $volunteer_node->title . " (" . $to . ")";
    $fc_id = $values['valghalla_mail_email_node_ID'] . "/" . $volunteer_item->item_id;
    if ($values['valghalla_mail_email_node_ID'] == 'invite') {
      $fc_id .= '/' . $values['election_nid'];
    }
    // Add link to preview.
    $prefix = " <a class='js-show-volunteer-mail' id='" . $fc_id . "' href='#'>";
    $recipients = $prefix . $recipients . "</a>";
    if ($mail_list == "") {
      $mail_list .= $recipients;
      $to_mails[$volunteer_node->nid] = $to;
    }
    else {
      $mail_list .= ", ";
      $mail_list .= $recipients;
      // TODO duplicate mail addresses.
      $to_mails[$volunteer_node->nid] = $to;
    }
    $count += 1;
  }
  $form['confirm_email_node'] = array(
    '#title' => t('Mail indhold'),
    '#type' => 'fieldset',
    '#description' => t('Klik på navnet/email-adressen for at se mailen for den modtager'),
  );
  $form['confirm_email_node']['js_mail_body'] = array(
    '#type' => 'item',
    '#prefix' => '<div class="js-volunteer-mail well">',
    '#markup' => '',
    "#suffix" => "</div>",
  );
  $form['confirm_info'] = array(
    '#title' => t('Er du sikker på du vil udsende mail til @count modtagere ?', array('@count' => $count)),
    '#type' => 'fieldset',
    '#description' => $mail_list,
  );

  $form['back'] = array(
    '#type' => 'submit',
    '#value' => t('Tilbage'),
  );

  $form['next'] = array(
    '#type' => 'submit',
    '#label' => 'Send!',
    '#value' => t('Send'),
  );

  $form_state['valghalla_sendlist'] = array(
    'valghalla_sendlist_array' => $to_mails,
    'valghalla_sendlist_acount' => $count,
  );

  return $form;
}

/**
 * Get all the mail eddresses.
 */
function valghalla_mail_sendmail_get_recipients($values) {
  global $language;
  module_load_include('inc', 'valhalla_volunteers');

  if (isset($values['invitation']) && $values['invitation'] === TRUE) {
    $volunteer_query = new EntityFieldQuery();
    $volunteer_query->entityCondition('entity_type', 'field_collection_item')
      ->entityCondition('bundle', 'field_electioninfo')
      ->fieldCondition('field_post_role', 'target_id', 'NULL', '!=')
      ->fieldCondition('field_election', 'target_id', $values['election_nid']);

    // Ensure that e-mails only are send to volunteers on polling stations that are active
    $result = array();
    $polling_stations = odin_get_polling_stations($values['election_nid']);

    if (!empty($polling_stations)) {
      $query_result      = $volunteer_query->execute();
      $unfiltered_result = array_shift($query_result);
      foreach ($unfiltered_result as $volunteer_id => $volunteer_item) {
        $polling_station_nid = 0;

        if ($fc = entity_load_single('field_collection_item', $volunteer_item->item_id)) {
          $election_field = field_get_items('field_collection_item', $fc, 'field_election');
          $polling_station_field = field_get_items('field_collection_item', $fc, 'field_vlnt_station');
          $polling_station_nid = $polling_station_field ? $polling_station_field[0]['target_id'] : 0;
        }

        if (isset($polling_stations[$polling_station_nid])) {
          $result[] = $volunteer_id;
        }
      }
    }
    else {
      drupal_set_message(t('Der er ingen aktive valgsteder på valget'), 'warning');
    }
  }
  else {
    $rsvp_status = count($values['rsvp_status']) > 0 ? $values['rsvp_status'] : FALSE;
    $roles = count($values['roles']) > 0 ? $values['roles'] : FALSE;
    $party = count($values['party']) > 0 ? $values['party'] : FALSE;
    $polling_station = count($values['polling_station']) > 0 ? $values['polling_station'] : FALSE;
    $election = count($values['election']) > 0 ? $values['election'] : FALSE;

    // Prepare statement.
    $volunteer_query = new EntityFieldQuery();
    $volunteer_query->entityCondition('entity_type', 'field_collection_item')
        ->entityCondition('bundle', 'field_electioninfo');

    if ($election !== FALSE) {
      $volunteer_query->fieldCondition('field_election', 'target_id', $election);
    }
    if ($rsvp_status !== FALSE) {
      $volunteer_query->fieldCondition('field_rsvp', 'value', $rsvp_status);
    }
    if ($roles !== FALSE) {
      $volunteer_query->fieldCondition('field_post_role', 'target_id', $roles);
    }
    if ($party !== FALSE) {
      $volunteer_query->fieldCondition('field_post_party', 'target_id', $party);
    }
    if ($polling_station !== FALSE) {
      $volunteer_query->fieldCondition('field_vlnt_station', 'target_id', $polling_station);
    }

    $query_result = $volunteer_query->execute();
    $result       = array_keys(array_shift($query_result));
  }

  foreach (entity_load('field_collection_item', $result) as $volunteer_item) {
    $volunteer_node = $volunteer_item->hostEntity();
    if (!isset($volunteer_node)) continue;
    if (!valghalla_mail_volunteer_no_mail($volunteer_node)) {
      $volunteer_fcids[] = $volunteer_item->item_id;
    }
  }

  return $volunteer_fcids;
}


/**
 * Redirect the user to the send form for the relevant mail.
 *
 * @author: Thomas Thune Hansen <tth@bellcom.dk>
 * @todo: find out if there is a better way to do this.
 */
function valghalla_mail_resend_ajax($form, $form_state) {
  ctools_include('ajax');
  ctools_add_js('ajax-responder');
  $commands[] = ctools_ajax_command_redirect('valghalla/administration/sendto/' . $form_state['values']['resend']);
  print ajax_render($commands);
  exit;
}