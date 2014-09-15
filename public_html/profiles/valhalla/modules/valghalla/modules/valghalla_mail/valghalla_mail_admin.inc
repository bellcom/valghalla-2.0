<?php
/**
 * Valghalla mail module
 *
 * @copyright 2012 OS2 - Offentligt Digitaliseringsfællesskab.
 * See README.md at https://github.com/os2web/valghalla_mail
 */

/**
 * Page callback for valghalla mails admin page
 *
 * @author Thomas Thune Hansen <tth@bellcom.dk>
 */
function valghalla_mail_admin_valghalla_mails($form, $form_state, $election_nid = FALSE){
  // Light styling for the form.
  $css = "
    #edit-mails,
    #edit-valghalla-role-mails {
      width: 49%;
      float: left;
      margin-right: 0.5%;
    }
    #edit-valghalla-mail-cancel {
      width: 49%;
    }
    .form-item-valghalla-mail-cancellation-from-participants-others {
      float: left;
      padding-right: 10px !important;
    }
    .form-item-valghalla-mail-cancellation-from-participants-to-mails{
      padding: 0 0 0 5px !important;
    }
    #edit-actions {
      clear: both;
    }";

  drupal_add_css($css, $option['type'] = 'inline');

  $election = node_load($election_nid);

  $form['header'] = array(
    '#type' => 'item',
    '#markup' => '<h2>Redigerer E-mail skabeloner for:<em> ' . $election->title . '</em></h2>',
  );

  $mail_types = valghalla_mail_get_mail_types();

  // Load all volunteer and mail role nodes.
  $role_nodes = node_load_multiple(array(), array('type' => 'roles'));

  $form['valghalla_volunteers_mail']['mails'] = array(
    '#type' => 'fieldset',
    '#title' => t('Standard E-Mail skabeloner'),
    '#description' => '<a href="/node/add/email?destination=/valghalla/administration/mails"><span class="glyphicon glyphicon-plus"></span> Tilføj ny</a>',
  );

  $mail_options = valghalla_mail_get_mails();

  // Generate form for selecting general mails.
  foreach($mail_types as $mail_type => $mail_type_title){
    $description = t('Vælg E-mail skabelon for ') . $mail_type_title;
    $variable_name = 'valghalla_mail_' . $election_nid . '_' . $mail_type;
    $mail_nid = variable_get($variable_name, FALSE);

    if($mail_nid){
      $description .= ' <a class="form-submit" href="/node/' . $mail_nid . '/edit?destination=/admin/valghalla/mails">'.t('edit').'</a>';
    }

    $form['valghalla_volunteers_mail']['mails'][$variable_name] = array(
      '#title' => $mail_type_title,
      '#type' => 'select',
      '#options' => $mail_options,
      '#default_value' => $mail_nid,
      '#description' => $description,
    );
  }

  /////////////////////////////////////////////
  // Role specific mails
  //
  // Generate fieldset for each role
  $form['valghalla_role_mails'] = array(
    '#title' => t('Rollespecifikke E-mail skabeloner'),
    '#type' => 'fieldset',
    '#description' => t('Herunder kan du vælge rollespecifikke E-mail skabeloner. Tryk på rolle titlen for at folde ud. Hvis du ikke vælger nogen ("ingen") bliver standard skabelonen brugt (vælges i boksen til venstre).'),
  );

  foreach($role_nodes as $role_node){
    $form['valghalla_role_mails'][$role_node->nid] = array(
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#title' => $role_node->title,
    );

    // Show referenced mails for each role
    foreach($mail_types as $mail_type => $mail_type_title){
      $mail_title = '';
      $variable_name = 'valghalla_mail_' . $election_nid . '_' . $role_node->nid . '_' . $mail_type;
      $mail_nid = variable_get($variable_name, 0);

      $mail_node = node_load($mail_nid);
      // Check if mail_node is valid
      if(is_object($mail_node)){
        $mail_title = $mail_node->title;
      }

      // Show mail title, and edit link if a mail is chosen.
      $description = t('standard');
      if($mail_nid){
        $description = $mail_title .': <a href="/node/' . $mail_nid . '/edit?destination=/admin/valhalla/mails">'.t('edit').'</a>';
      }

      $form['valghalla_role_mails'][$role_node->nid][$variable_name] = array(
        '#title' => $mail_type_title,
        '#type' => 'select',
        '#options' => $mail_options,
        '#default_value' => $mail_nid,
        '#description' => $description,
      );
    }
  }

  return system_settings_form($form);
}

/**
 * General mail settings
 */
function valghalla_mail_admin_notifications(){
  $mail_types = valghalla_mail_get_mail_types();
  $mail_options = valghalla_mail_get_mails();

  // Cancellation from participants mail settings
  $roles = db_query("SELECT name, rid FROM {role} WHERE rid > 2");
  $form['valghalla_volunteers_mail']['valghalla_mail_cancel'] = array(
    '#type' => 'fieldset',
    '#title' => t('Besked ved afbud fra deltagere'),
    '#collapsible' => TRUE,
    '#description' => t('Vælg roller der skal modtage mails ved afbud.'),
  );

  foreach ($roles as $role) {
    if($role->name == 'Valgsekretær'){
      $form['valghalla_volunteers_mail']['valghalla_mail_cancel']["valghalla_mail_cancellation_from_participants_".$role->rid]= array(
        '#type' => 'checkbox',
        '#title' => $role->name,
        '#default_value' => variable_get("valghalla_mail_cancellation_from_participants_".$role->rid),
      );
    }
  }

  $other_mails = variable_get('valghalla_mail_cancellation_from_participants_to_mails');
  $other_check = variable_get('valghalla_mail_cancellation_from_participants_others');

  if (!empty($other_mails) && empty($other_check)) {
    variable_set('valghalla_mail_cancellation_from_participants_others', 0);
    variable_set('valghalla_mail_cancellation_from_participants_to_mails','');
  }
  elseif (empty($other_mails) && $other_check) {
    variable_set("valghalla_mail_cancellation_from_participants_others", 0);
  }

  $form['valghalla_volunteers_mail']['valghalla_mail_cancel']['valghalla_mail_cancellation_from_participants_others'] = array(
      '#type' => 'checkbox',
      '#title' => t('Andre (udfyld tekstfeltet herunder):'),
      '#default_value' => variable_get("valghalla_mail_cancellation_from_participants_others"),
    );
  $form['valghalla_volunteers_mail']['valghalla_mail_cancel']['valghalla_mail_cancellation_from_participants_to_mails'] = array(
      '#type' => 'textfield',
      '#description' => t('Liste af E-mailadresser adskildt af komma'),
      '#default_value' => variable_get("valghalla_mail_cancellation_from_participants_to_mails"),
    );

  // Only choose the rsvp_no and rsvp_never types.
  foreach($mail_types as $mail_type => $mail_type_title){
    if ($mail_type == "rsvp_no" || $mail_type == "rsvp_never") {
      $description_2 = t('Vælg standard mail for: ') . $mail_type_title;
      $mailnid = variable_get("valghalla_mail_cancellation_from_participants_mail_$mail_type", FALSE);

      if($mailnid){
        $description_2 .= ' <a class="form-submit" href="/node/' . $mailnid . '/edit?destination=/admin/valghalla/mails">'.t('edit').'</a>';
      }
      elseif (node_type_load('email')) {
        $description_2 .= ' <a class="form-submit" href="/node/add/email?destination=/admin/valghalla/mails">'.t('add').'</a>';
      }
      $form['valghalla_volunteers_mail']['valghalla_mail_cancel']['valghalla_mail_cancellation_from_participants_mail_' . $mail_type] = array(
        '#type' => 'select',
        '#options' => $mail_options,
        '#default_value' => $mailnid,
        '#title' => $mail_type_title . t(' til rolle(r)'),
        '#description' => $description_2,
      );
    }
  }

  // Reminder settings.
  $form['valghalla_volunteers_mail']['options']['valghalla_rsvp_reminder_days'] = array(
      '#type' => 'textfield',
      '#title' => t('Påmindelses dage'),
      '#description' => 'Liste af dage før valg der skal udsendes påmindelser, adskildt af komma ( , ). f.eks. 14, 7, 5, 3',
      '#default_value' => variable_get('valghalla_rsvp_reminder_days', '14, 7, 5, 3'),
  );

  $form['valghalla_volunteers_mail']['mails']['valghalla_mail_send_invitation_on_add'] = array(
    '#title' => 'Send mail(invitation) til deltager når denne tilføjes på et valgsted.',
    '#default_value' => variable_get('valghalla_mail_send_invitation_on_add', TRUE),
    '#type' => 'checkbox'
  );

  return system_settings_form($form);
}

/**
 * Extra validation needed to verify reminder days can be safely exloded.
 */
function valghalla_mail_admin_valghalla_mails_validate(&$elements, &$form_state, $form_id = NULL) {
  if (preg_match('/[^\d|,| ]/', $form_state['values']['valghalla_rsvp_reminder_days'])) {
    // Found illigal chars in the form
    form_set_error('valghalla_rsvp_reminder_days', 'Dette felt skal være en komma-separeret liste af hele tal.');
  }
}
