<?php

/**
 * @file
 * Valghalla_external_server_signup.pages.inc.
 */

/**
 * Builds signup form.
 */
function valghalla_external_server_signup_signup_form($form, &$form_state) {
  // Getting election from state or URL.
  $election = isset($form_state['election']) ? $form_state['election'] : NULL;
  if (!$election) {
    $election = _valghalla_external_server_signup_fetch_entity_from_url('election', 'node');
    $form_state['election'] = $election;
  }

  // Getting election notification config.
  $field_election_notif_conf_export = field_get_items('node', $election, 'field_election_notif_conf_export');
  $form_state['election_notif_conf_export'] = unserialize($field_election_notif_conf_export[0]['value']);

  // Setting the election nid into the session,
  // as some of the functionality depends on it.
  $_SESSION['election_nid'] = $election->nid;

  // Getting party from state or URL.
  $party = isset($form_state['party']) ? $form_state['party'] : NULL;
  if (!$party) {
    $party = _valghalla_external_server_signup_fetch_entity_from_url('party', 'taxonomy_term');
    $form_state['party'] = $party;
  }

  if (!$election || !$party) {
    valghalla_external_server_signup_terminate_signup();
  }

  // Getting role from form state.
  $role = isset($form_state['role']) ? $form_state['role'] : NULL;
  if (!$role) {
    // Getting role from values.
    if (isset($form_state['values']) && isset($form_state['values']['role_select'])) {
      $role_selected = $form_state['values']['role_select'];
      $role = node_load($role_selected);
    }
    // Getting role from URL.
    else {
      $role = _valghalla_external_server_signup_fetch_entity_from_url('role', 'node');
      if ($role) {
        $form_state['role_in_url'] = TRUE;
        $form_state['role'] = $role;
      }
    }
  }
  // Getting polling station from form state.
  $polling_station = isset($form_state['polling_station']) ? $form_state['polling_station'] : NULL;
  if (!$polling_station) {
    // Getting polling station from values.
    if (isset($form_state['values']) && isset($form_state['values']['polling_station_select'])) {
      $polling_station_selected = $form_state['values']['polling_station_select'];
      $polling_station = node_load($polling_station_selected);
    }
    // Getting polling station from URL.
    else {
      $polling_station = _valghalla_external_server_signup_fetch_entity_from_url('pol_st', 'node');
      if ($polling_station) {
        $form_state['polling_station_in_url'] = TRUE;
        $form_state['polling_station'] = $polling_station;
      }
    }
  }

  $form_mode = NULL;
  $election_date_str = format_date(strtotime($election->field_date['da'][0]['value']), 'custom', 'd. F Y');

  drupal_set_title($election->title);

  $form['cpr'] = array(
    '#type' => 'textfield',
    '#description' => 'Temporary field, until NemID login is added',
    '#attributes' => array(
      'placeholder' => 'Temporary field, until NemID login is added',
    ),
    '#required' => TRUE,
  );

  $form['email-container'] = array(
    '#prefix' => '<div id="js-email-container" class="form-group">',
    '#suffix' => '</div>',
  );
  $form['email-container']['email'] = array(
    '#type' => 'textfield',
    '#description' => t('Email'),
    '#attributes' => array(
      'placeholder' => t('Email'),
    ),
    '#required' => TRUE,
    '#access' => valghalla_external_server_signup_field_visibility($form_state, 'mail', ($role) ? $role->uuid : NULL),
  );
  $form['phone-container'] = array(
    '#prefix' => '<div id="js-phone-container" class="form-group">',
    '#suffix' => '</div>',
  );
  $form['phone-container']['phone'] = array(
    '#type' => 'textfield',
    '#description' => t('Telefon nr.'),
    '#attributes' => array(
      'placeholder' => t('Telefon nr.'),
    ),
    '#required' => TRUE,
    '#access' => valghalla_external_server_signup_field_visibility($form_state, 'sms', ($role) ? $role->uuid : NULL),
  );

  $form['comment'] = array(
    '#title' => t('Kommentar'),
    '#type' => 'textarea',
    '#rows' => 5,
    '#attributes' => array(
      'placeholder' => t('Skriv evt. en kommentar her'),
    ),
    '#access' => !empty($party->field_party_subsc_accept_comment) ? $party->field_party_subsc_accept_comment['und'][0]['value'] : FALSE,
  );

  if (!isset($form_state['role_in_url']) && !isset($form_state['polling_station_in_url'])) {
    $form_mode = 'party';
    $replacements = array(
      odin_get_municipality(variable_get('valhalla_settings_municipality')),
      $election->title,
      $election_date_str,
      $party->field_partinavn['und'][0]['value'],
    );
  }
  elseif (isset($form_state['role_in_url']) && !isset($form_state['polling_station_in_url'])) {
    $form_mode = 'party_role';
    $replacements = array(
      odin_get_municipality(variable_get('valhalla_settings_municipality')),
      $election->title,
      $election_date_str,
      $party->field_partinavn['und'][0]['value'],
      $role->field_description['und'][0]['value'],
      $role->field_meetingtime['und'][0]['value'],
    );
  }
  elseif (!isset($form_state['role_in_url']) && isset($form_state['polling_station_in_url'])) {
    $form_mode = 'party_polling_station';
    $replacements = array(
      odin_get_municipality(variable_get('valhalla_settings_municipality')),
      $election->title,
      $election_date_str,
      $party->field_partinavn['und'][0]['value'],
      $polling_station->title,
    );
  }
  elseif (isset($form_state['role_in_url']) && isset($form_state['polling_station_in_url'])) {
    $form_mode = 'party_role_polling_station';
    $replacements = array(
      odin_get_municipality(variable_get('valhalla_settings_municipality')),
      $election->title,
      $election_date_str,
      $party->field_partinavn['und'][0]['value'],
      $role->field_description['und'][0]['value'],
      $role->field_meetingtime['und'][0]['value'],
      $polling_station->title,
    );
  }
  else {
    valghalla_external_server_signup_terminate_signup();
  }

  // Building a form.
  if (!isset($form_state['role_in_url'])) {
    if ($polling_station) {
      $available_roles = _valghalla_external_server_signup_get_available_roles($election->nid, $party->tid, $polling_station->nid);
    }
    else {
      $available_roles = _valghalla_external_server_signup_get_available_roles($election->nid, $party->tid);
    }

    $form_state['available_roles'] = $available_roles;

    // Role selector.
    $form['role_select'] = array(
      '#title' => t('Vælg rolle'),
      '#type' => 'select',
      '#options' => $available_roles,
      '#empty_option' => ('Vælg rolle'),
      '#empty_value' => 0,
      '#prefix' => '<div id="js-roles">',
      '#suffix' => '</div>',
      '#ajax' => array(
        'callback' => 'valghalla_external_server_signup_role_select_callback',
        'effect' => 'none',
      ),
    );

    $form['role_details'] = array(
      '#prefix' => '<div id="js-role-details">',
      '#suffix' => '</div>',
    );

    if (isset($form_state['values']) && isset($form_state['values']['role_select'])) {
      $role_selected = $form_state['values']['role_select'];
      $role = node_load($role_selected);
      $form_state['role'] = $role;

      $form['role_details']['#markup'] = _valghalla_external_server_signup_get_role_detail_html($role);
    }
  }

  if (!isset($form_state['polling_station_in_url'])) {
    if ($role) {
      $available_polling_stations = _valghalla_external_server_signup_get_available_polling_stations($election->nid, $party->tid, $role->nid);
    }
    else {
      $available_polling_stations = _valghalla_external_server_signup_get_available_polling_stations($election->nid, $party->tid);
    }

    $form_state['available_polling_stations'] = $available_polling_stations;

    $form['polling_station_select'] = array(
      '#title' => t('Vælg valgsted'),
      '#type' => 'select',
      '#options' => $available_polling_stations,
      '#empty_option' => t('Vælg valgsted'),
      '#empty_value' => 0,
      '#prefix' => '<div id="js-polling-stations">',
      '#suffix' => '</div>',
      '#ajax' => array(
        'callback' => 'valghalla_external_server_signup_polling_station_select_callback',
        'effect' => 'none',
      ),
    );

    if (isset($form_state['values']) && isset($form_state['values']['polling_station_select'])) {
      $polling_station_selected = $form_state['values']['polling_station_select'];
      $polling_station = node_load($polling_station_selected);
    }
  }

  $polling_station_details_markup = '';
  if ($polling_station) {
    $polling_station_details_markup = _valghalla_external_server_signup_get_polling_station_detail_html($polling_station);
  }

  if ($polling_station_details_markup === '') {
    $form['polling_station_details'] = array(
      '#prefix' => '<div id="js-polling-station-details" class="no-content">',
      '#suffix' => '</div>',
    );
  }
  else {
    $form['polling_station_details'] = array(
      '#prefix' => '<div id="js-polling-station-details">',
      '#suffix' => '</div>',
      '#markup' => $polling_station_details_markup,
    );
  }

  // Making the replacements.
  if ($form_mode) {
    $form['#upper_text'] = variable_get('valghalla_external_server_signup_text_' . $form_mode . '_upper');
    $form['#bottom_text'] = variable_get('valghalla_external_server_signup_text_' . $form_mode . '_bottom');
    $tokens = array_keys(_valghalla_external_server_signup_text_get_replacement_tokens($form_mode));
    $form['#upper_text'] = str_replace($tokens, $replacements, $form['#upper_text']);
    $form['#bottom_text'] = str_replace($tokens, $replacements, $form['#bottom_text']);
  }
  if (!empty($party->field_party_subsc_message)) {
    $form['#party_message'] = $party->field_party_subsc_message['und'][0]['value'];
  }

  $terms_agreement_default = t('Accepter at vi gemmer dine oplysninger.');
  $form['terms_agreement'] = array(
    '#type' => 'checkbox',
    '#title' => !empty($party->field_party_subsc_terms_text) ? $party->field_party_subsc_terms_text['und'][0]['value'] : $terms_agreement_default,
    '#required' => TRUE,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Tilmeld'),
    '#states' => array(
      'enabled' => array(
        ':input[name="terms_agreement"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['#theme'] = array('valghalla_external_server_signup_form');

  return $form;
}

/**
 * Ajax callback for role select.
 *
 * Updated the list of polling stations, and selected polling station details.
 *
 * @return mixed
 *   Polling station container element.
 */
function valghalla_external_server_signup_role_select_callback($form, &$form_state) {
  $commands = array();

  $role_selected = $form_state['values']['role_select'];
  $role = node_load($role_selected);

  // Updating the email and phone fields visibility.
  $form['email-container']['email']['#access'] = valghalla_external_server_signup_field_visibility($form_state, 'mail', $role->uuid);
  $commands[] = ajax_command_replace('#js-email-container', drupal_render($form['email-container']));

  $form['phone-container']['phone']['#access'] = valghalla_external_server_signup_field_visibility($form_state, 'sms', $role->uuid);
  $commands[] = ajax_command_replace('#js-phone-container', drupal_render($form['phone-container']));

  // Updating role details.
  $form['role_details']['#markup'] = ($role) ? _valghalla_external_server_signup_get_role_detail_html($role) : '';
  $commands[] = ajax_command_replace('#js-role-details', drupal_render($form['role_details']));

  if (!isset($form_state['polling_station_in_url'])) {
    $polling_station_selected = $form_state['values']['polling_station_select'];

    // Updating polling station select.
    if ($role_selected) {
      $psExists = FALSE;
      if ($polling_station_selected) {
        foreach ($form_state['available_polling_stations'] as $cons => $psList) {
          if (array_key_exists($polling_station_selected, $psList)) {
            $psExists = TRUE;
          }
        }
      }

      if (!$polling_station_selected || !$psExists) {
        $polling_station_selected = 0;
        $form['polling_station_select']['#value'] = $polling_station_selected;
      }
    }
    $commands[] = ajax_command_replace('#js-polling-stations', drupal_render($form['polling_station_select']));

    // Updating value in the form state.
    $form_state['values']['polling_station_select'] = $polling_station_selected;

    // Updating polling station details.
    if ($polling_station_selected) {
      $polling_station = node_load($polling_station_selected);
      $form['polling_station_details']['#markup'] = _valghalla_external_server_signup_get_polling_station_detail_html($polling_station);
    }
    else {
      $form['polling_station_details']['#markup'] = '';
    }

    $commands[] = ajax_command_replace('#js-polling-station-details', drupal_render($form['polling_station_details']));
  }

  return array('#type' => 'ajax', '#commands' => $commands);
}

/**
 * Ajax callback for polling station select.
 *
 * Updated the polling station details.
 *
 * @return mixed
 *   Polling station details element.
 */
function valghalla_external_server_signup_polling_station_select_callback($form, &$form_state) {
  $commands = array();

  $polling_station_selected = $form_state['values']['polling_station_select'];

  // Updating polling station details.
  if ($polling_station_selected) {
    $polling_station = node_load($polling_station_selected);
    $form['polling_station_details']['#markup'] = _valghalla_external_server_signup_get_polling_station_detail_html($polling_station);
  }
  else {
    $form['polling_station_details']['#markup'] = '';
  }
  $commands[] = ajax_command_replace('#js-polling-station-details', drupal_render($form['polling_station_details']));

  // Updating role select.
  if (!isset($form_state['role_in_url'])) {
    $role_selected = $form_state['values']['role_select'];
    if ($polling_station_selected) {
      if (!$role_selected || !array_key_exists($role_selected, $form_state['available_roles'])) {
        $role_selected = 0;
        $form['role_select']['#value'] = $role_selected;
      }
    }
    $commands[] = ajax_command_replace('#js-roles', drupal_render($form['role_select']));

    // Updating value in the form state.
    $form_state['values']['role_select'] = $role_selected;

    // Updating role details.
    $role = ($role_selected) ? node_load($role_selected) : NULL;
    $form['role_details']['#markup'] = ($role) ? _valghalla_external_server_signup_get_role_detail_html($role) : '';
    $commands[] = ajax_command_replace('#js-role-details', drupal_render($form['role_details']));
  }

  return array('#type' => 'ajax', '#commands' => $commands);
}

/**
 * Helper function.
 *
 * Cancels the subscription by redirecting user to front page
 * with a warning message.
 */
function valghalla_external_server_signup_terminate_signup() {
  // Throwing the warning and redirecting to the main page.
  drupal_set_message(t('Pladserne er desværre blevet optaget. Vælg evt. et andet valgsted.'), 'warning');
  drupal_goto();
}

/**
 * Validates the CPR in the form.
 *
 * Also changes the format of CPR, if needed.
 */
function valghalla_external_server_signup_signup_form_validate($form, &$form_state) {
  $cpr = $form_state['values']['cpr'];

  // Adding dash, if missing. E.g. 123456-7890.
  if (preg_match('/[0-9]{10}/', $cpr)) {
    $cpr = substr($cpr, 0, 6) . '-' . substr($cpr, 6, 4);
    $form_state['values']['cpr'] = $cpr;
  }

  if (!preg_match('/[0-9]{6}-[0-9]{4}/', $cpr)) {
    form_set_error('cpr', t('Wrong CPR format, correct format is 123456-7890'));
  }

  if ($form['email-container']['email']['#access']) {
    $email = $form_state['values']['email'];
    if (!valid_email_address($email)) {
      form_set_error('email', t('Wrong email format, test@gmail.com'));
    }
  }

  if ($form['phone-container']['phone']['#access']) {
    $phone = $form_state['values']['phone'];
    if (empty($phone)) {
      form_set_error('phone', t('Phone is empty'));
    }
    elseif (strlen($phone) > 12) {
      form_set_error('phone', t('Phone number is too long'));
    }
  }

  if (isset($form_state['values']['polling_station_select']) && $form_state['values']['polling_station_select'] === 0) {
    form_set_error('polling_station_select', t('The field %field is required.', array('%field' => 'Valgsted')));
  }

  if (isset($form_state['values']['role_select']) && $form_state['values']['role_select'] === 0) {
    form_set_error('role_select', t('The field %field is required.', array('%field' => 'Role')));
  }
}

/**
 * Create node for volunteer and adding to volunteer to post.
 */
function valghalla_external_server_signup_signup_form_submit($form, &$form_state) {
  $election_nid = $form_state['election']->nid;
  $party_tid = $form_state['party']->tid;
  $role_nid = isset($form_state['role']->nid) ? $form_state['role']->nid : $form_state['values']['role_select'];
  $polling_station_nid = isset($form_state['polling_station']) ? $form_state['polling_station']->nid : $form_state['values']['polling_station_select'];

  if ($polling_station_nid && $role_nid && $party_tid && $election_nid) {
    $cpr = $form_state['values']['cpr'];
    $cpr = valghalla_synch_node_export_get_encrypt($cpr);

    $volunteer_node = odin_load_volunteer_by_cpr($cpr);

    if (!$volunteer_node) {
      $volunteer_node = new stdClass();
      $volunteer_node->type = 'volunteers';
      $volunteer_node->language = LANGUAGE_NONE;
      node_object_prepare($volunteer_node);
      $volunteer_node->title = "New volunteer, CPR: " . $cpr;
    }

    if (!isset($volunteer_node->nid) || !odin_volunteer_has_post_on_election($volunteer_node->nid, $election_nid)) {
      $volunteer_node->status = 1;
      $volunteer_node->field_cpr_number[LANGUAGE_NONE][]['value'] = $cpr;
      $volunteer_node->field_external_signup[LANGUAGE_NONE][]['value'] = 1;
      $volunteer_node->field_party[LANGUAGE_NONE][0]['tid'] = $party_tid;

      if (isset($form_state['values']['email'])) {
        $email_encrypted = valghalla_synch_node_export_get_encrypt($form_state['values']['email']);
        $volunteer_node->field_email[LANGUAGE_NONE][]['email'] = $email_encrypted;
      }
      if (isset($form_state['values']['phone'])) {
        $phone_encrypted = valghalla_synch_node_export_get_encrypt($form_state['values']['phone']);
        $volunteer_node->field_phone[LANGUAGE_NONE][]['value'] = $phone_encrypted;
      }

      node_save($volunteer_node);
      $post_info = valghalla_volunteers_add_volunteer_to_post($volunteer_node->nid, $polling_station_nid, $role_nid, $party_tid, $election_nid, 1);
      $post = entity_load('field_collection_item', array($post_info['fcid']));

      if ($post) {
        $post = reset($post);
        $post->field_rsvp_comment[LANGUAGE_NONE][]['value'] = $form_state['values']['comment'];
        $post->save();
      }

      $form_state['redirect'] = 'valghalla/external-signup-success';
    }
    else {
      drupal_set_message(t('This volunteer already has a seat in the selected election'), 'warning');
    }
  }
}

/**
 * External server signup settings form.
 */
function valghalla_external_server_signup_settings_form($form, $form_state) {
  /* Party only START */
  $form['valghalla_external_server_signup_text_party_fs'] = array(
    '#type' => 'fieldset',
    '#title' => t('Party only texts'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['valghalla_external_server_signup_text_party_fs']['valghalla_external_server_signup_text_party_upper'] = array(
    '#title' => t('Party only upper text'),
    '#type' => 'textarea',
    '#default_value' => variable_get('valghalla_external_server_signup_text_party_upper', '<p>Du kan her tilmelde dig til !election_name den !election_time for !party_name.</p>
<p>Log ind med NemID i nedenstående formular for at fortsætte.</p>'),
  );
  $form['valghalla_external_server_signup_text_party_fs']['valghalla_external_server_signup_text_party_bottom'] = array(
    '#title' => t('Party only bottom text'),
    '#type' => 'textarea',
    '#default_value' => variable_get('valghalla_external_server_signup_text_party_bottom', '<p>Ved at aktivere tilmeld-knappen herunder, accepterer du samtidigt at !municipality registrerer CPR nummer som tilmeldt på ovenstående afstemningssted. Du skal møde på ovenstående adresse d. !election_time.</p>
<p>Du vil herefter modtage en bekræftelse, her står der mere om dine opgaver på valgdagen, hvornår du skal møde samt ovenstående navn på valgsted og adresse.</p>'),
  );
  $token_str = array();
  foreach (_valghalla_external_server_signup_text_get_replacement_tokens('party') as $token => $text) {
    $token_str[] = "<li>$token - $text</li>";
  }
  $form['valghalla_external_server_signup_text_party_fs'][] = array(
    '#type' => 'fieldset',
    '#title' => t('Replacement'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    0 => array(
      '#markup' => '<ul>' . implode('', $token_str) . '</ul>',
    ),
  );
  /* Party only END */

  /* Party & role START */
  $form['valghalla_external_server_signup_text_party_role_fs'] = array(
    '#type' => 'fieldset',
    '#title' => t('Party and role text'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['valghalla_external_server_signup_text_party_role_fs']['valghalla_external_server_signup_text_party_role_upper'] = array(
    '#title' => t('Party and role upper text'),
    '#type' => 'textarea',
    '#default_value' => variable_get('valghalla_external_server_signup_text_party_role_upper', '<p>Du kan her tilmelde dig til !election_name den !election_time for !party_name.</p>
<p>Du kan vælge mellem de valgsteder der har en ledig plads.</p>
<p>Log ind med NemID i nedenstående formular for at fortsætte.</p>'),
  );
  $form['valghalla_external_server_signup_text_party_role_fs']['valghalla_external_server_signup_text_party_role_bottom'] = array(
    '#title' => t('Party and role bottom text'),
    '#type' => 'textarea',
    '#default_value' => variable_get('valghalla_external_server_signup_text_party_role_bottom', '<p>Ved at aktivere tilmeld-knappen herunder, accepterer du samtidigt at !municipality registrerer CPR nummer som tilmeldt på ovenstående afstemningssted. Du skal møde på ovenstående adresse d. !election_time.</p>
<p>Du vil herefter modtage en bekræftelse, her står der mere om dine opgaver på valgdagen, hvornår du skal møde samt ovenstående navn på valgsted og adresse.</p>'),
  );
  $token_str = array();
  foreach (_valghalla_external_server_signup_text_get_replacement_tokens('party_role') as $token => $text) {
    $token_str[] = "<li>$token - $text</li>";
  }
  $form['valghalla_external_server_signup_text_party_role_fs'][] = array(
    '#type' => 'fieldset',
    '#title' => t('Replacement'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    0 => array(
      '#markup' => '<ul>' . implode('', $token_str) . '</ul>',
    ),
  );
  /* Party & role END */

  /* Party & polling station START */
  $form['valghalla_external_server_signup_text_party_polling_station_fs'] = array(
    '#type' => 'fieldset',
    '#title' => t('Party and polling_station text'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['valghalla_external_server_signup_text_party_polling_station_fs']['valghalla_external_server_signup_text_party_polling_station_upper'] = array(
    '#title' => t('Party and polling station upper text'),
    '#type' => 'textarea',
    '#default_value' => variable_get('valghalla_external_server_signup_text_party_polling_station_upper', '<p>Du kan her tilmelde dig til !election_name den !election_time for !party_name.</p>
<p>Du kan vælge en rolle blandt de ledige pladser !party_name er tildelt på !polling_station_name.</p>
<p>Log ind med NemID i nedenstående formular for at fortsætte.</p>'),
  );
  $form['valghalla_external_server_signup_text_party_polling_station_fs']['valghalla_external_server_signup_text_party_polling_station_bottom'] = array(
    '#title' => t('Party and polling station bottom text'),
    '#type' => 'textarea',
    '#default_value' => variable_get('valghalla_external_server_signup_text_party_polling_station_bottom', '<p>Ved at aktivere tilmeld-knappen herunder, accepterer du samtidigt at !municipality registrerer CPR nummer som tilmeldt som !role_name på afstemningsstedet !polling_station_name. Du skal møde på ovenstående adresse d. !election_time !role_meeting_time.</p>
<p>Du vil herefter modtage en bekræftelse, her står der mere om dine opgaver på valgdagen, hvornår du skal møde samt ovenstående navn på valgsted og adresse.</p>'),
  );
  $token_str = array();
  foreach (_valghalla_external_server_signup_text_get_replacement_tokens('party_polling_station') as $token => $text) {
    $token_str[] = "<li>$token - $text</li>";
  }
  $form['valghalla_external_server_signup_text_party_polling_station_fs'][] = array(
    '#type' => 'fieldset',
    '#title' => t('Replacement'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    0 => array(
      '#markup' => '<ul>' . implode('', $token_str) . '</ul>',
    ),
  );
  /* Party & polling station END */

  /* Party, role & polling station START */
  $form['valghalla_external_server_signup_text_party_role_polling_station_fs'] = array(
    '#type' => 'fieldset',
    '#title' => t('Party, role and polling station text'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['valghalla_external_server_signup_text_party_role_polling_station_fs']['valghalla_external_server_signup_text_party_role_polling_station_upper'] = array(
    '#title' => t('Party, role and polling station upper text'),
    '#type' => 'textarea',
    '#default_value' => variable_get('valghalla_external_server_signup_text_party_role_polling_station_upper', '<p>Du kan her tilmelde dig som !role_name på !polling_station_name ved !election_name den !election_time for !party_name.</p>
<p>Log ind med NemID i nedenstående formular for at fortsætte.</p>'),
  );
  $form['valghalla_external_server_signup_text_party_role_polling_station_fs']['valghalla_external_server_signup_text_party_role_polling_station_bottom'] = array(
    '#title' => t('Party, role and polling station bottom text'),
    '#type' => 'textarea',
    '#default_value' => variable_get('valghalla_external_server_signup_text_party_role_polling_station_bottom', '<p>Ved at aktivere tilmeld-knappen herunder, accepterer du samtidigt at !municipality registrerer CPR nummer som tilmeldt som !role_name på afstemningsstedet !polling_station_name. Du skal møde på ovenstående adresse d. !election_time !role_meeting_time.</p>
<p>Du vil herefter modtage en bekræftelse, her står der mere om dine opgaver på valgdagen, hvornår du skal møde samt ovenstående navn på valgsted og adresse.</p>'),
  );
  $token_str = array();
  foreach (_valghalla_external_server_signup_text_get_replacement_tokens('party_role_polling_station') as $token => $text) {
    $token_str[] = "<li>$token - $text</li>";
  }
  $form['valghalla_external_server_signup_text_party_role_polling_station_fs'][] = array(
    '#type' => 'fieldset',
    '#title' => t('Replacement'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    0 => array(
      '#markup' => '<ul>' . implode('', $token_str) . '</ul>',
    ),
  );
  /* Party, role & polling station END */

  return system_settings_form($form);
}

/**
 * Returns the visibility status for email or phone field.
 *
 * Used both on form rendering and the ajax call.
 *
 * @param mixed $form_state
 *   Form state.
 * @param string $propery_name
 *   Name of the property to check for.
 * @param string $role_uuid
 *   The UUID of the role, can be null.
 *
 * @return bool
 *   TRUE or FALSE.
 */
function valghalla_external_server_signup_field_visibility($form_state, $propery_name, $role_uuid = NULL) {
  $conf_export = $form_state['election_notif_conf_export'];

  if ($role_uuid && array_key_exists($role_uuid, $conf_export) && isset($conf_export[$role_uuid][$propery_name])) {
    return $conf_export[$role_uuid][$propery_name] === TRUE;
  }
  else {
    return $conf_export['general'][$propery_name] === TRUE;
  }
}

/**
 * External signup success page.
 */
function _external_signup_success_page() {
  drupal_set_title(t('Tilmeldt'));
  $output = '<p>' . t('Du kan nu lukke siden.') . '</p>';

  return $output;
}
