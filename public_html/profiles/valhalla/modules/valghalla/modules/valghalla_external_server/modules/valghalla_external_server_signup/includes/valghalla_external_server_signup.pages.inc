<?php

/**
 * @file
 * Valghalla_external_server_signup.pages.inc.
 */

/**
 * Builds signup form.
 */
function valghalla_external_server_signup_signup_form($form, &$form_state) {
  // Getting election and party from state or URL.
  $election = isset($form_state['election']) ? $form_state['election'] : NULL;
  if (!$election) {
    $election = _valghalla_external_server_signup_fetch_entity_from_url('election', 'node');
    $form_state['election'] = $election;
  }
  $party = isset($form_state['party']) ? $form_state['party'] : NULL;
  if (!$party) {
    $party = _valghalla_external_server_signup_fetch_entity_from_url('party', 'taxonomy_term');
    $form_state['party'] = $party;
  }

  if (!$election || !$party) {
    valghalla_external_server_signup_terminate_signup();
  }

  // Getting role, polling station from form state or URL.
  $role = isset($form_state['role']) ? $form_state['role'] : NULL;
  if (!$role) {
    $role = _valghalla_external_server_signup_fetch_entity_from_url('role', 'node');

    if ($role) {
      $form_state['role'] = $role;
      $form_state['role_in_url'] = TRUE;
    }
  }
  $polling_station = isset($form_state['polling_station']) ? $form_state['polling_station'] : NULL;
  if (!$polling_station) {
    $polling_station = _valghalla_external_server_signup_fetch_entity_from_url('pol_st', 'node');

    if ($polling_station) {
      $form_state['polling_station'] = $polling_station;
      $form_state['polling_station_in_url'] = TRUE;
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
  );

  $form['comment'] = array(
    '#type' => 'textarea',
    '#rows' => 5,
    '#attributes' => array(
      'placeholder' => 'Skriv evt. en kommentar her',
    ),
    '#access' => !empty($party->field_party_subsc_accept_comment) ? $party->field_party_subsc_accept_comment['und'][0]['value'] : FALSE,
  );

  if (!isset($form_state['role_in_url']) && !isset($form_state['polling_station_in_url'])) {
    $form_mode = 'party';
    $replacements = array(
      $election->title,
      $election_date_str,
      $party->name,
    );
  }
  elseif (isset($form_state['role_in_url']) && !isset($form_state['polling_station_in_url'])) {
    $form_mode = 'party_role';
    $replacements = array(
      $election->title,
      $election_date_str,
      $party->name,
      $role->title,
      $election_date_str . ' kl. ' . $role->field_meetingtime['und'][0]['value'],
    );

  }
  elseif (isset($form_state['role_in_url']) && isset($form_state['polling_station_in_url'])) {
    $form_mode = 'party_role_polling_station';
    $replacements = array(
      $election->title,
      $election_date_str,
      $party->name,
      $role->title,
      $election_date_str . ' kl. ' . $role->field_meetingtime['und'][0]['value'],
      $polling_station->title,
    );
  }
  else {
    valghalla_external_server_signup_terminate_signup();
  }

  // Building a form.
  if (!isset($form_state['role_in_url'])) {
    $available_roles = _valghalla_external_server_signup_get_available_roles($election->nid, $party->tid);
    if (empty($available_roles)) {
      valghalla_external_server_signup_terminate_signup();
    }

    $form_state['available_roles'] = $available_roles;
    $form['role_select'] = array(
      '#type' => 'select',
      '#options' => $available_roles,
      '#ajax' => array(
        'callback' => 'valghalla_external_server_signup_role_select_callback',
        'wrapper' => 'js-polling-stations-container',
        'method' => 'replace',
        'effect' => 'fade',
      ),
    );

    $role_selected = NULL;
    if (isset($form_state['values']) && isset($form_state['values']['role_select'])) {
      $role_selected = $form_state['values']['role_select'];
    }
    else {
      reset($available_roles);
      $role_selected = key($available_roles);
    }
    $role = node_load($role_selected);
    $form_state['role'] = $role;
  }

  $form['polling_stations_container'] = array(
    '#type' => 'container',
    '#prefix' => '<div id="js-polling-stations-container">',
    '#suffix' => '</div>',
  );

  if (!isset($form_state['polling_station_in_url'])) {
    if ($role) {
      $available_polling_stations = _valghalla_external_server_signup_get_available_polling_stations($election->nid, $role->nid);
      $form_state['available_polling_stations'] = $available_polling_stations;

      $form['polling_stations_container']['polling_station_select'] = array(
        '#type' => 'select',
        '#options' => $available_polling_stations,
        '#prefix' => '<div id="js-polling-stations">',
        '#suffix' => '</div>',
        '#ajax' => array(
          'callback' => 'valghalla_external_server_signup_polling_station_select_callback',
          'wrapper' => 'js-polling-station-details',
          'method' => 'replace',
          'effect' => 'fade',
        ),
      );

      $polling_station_selected = NULL;
      if (isset($form_state['values']) && isset($form_state['values']['polling_station_select'])) {
        $polling_station_selected = $form_state['values']['polling_station_select'];
      }
      else {
        $first_polling_station = reset($available_polling_stations);
        // We are getting the list mapped by constituencies. Pop the first one.
        $polling_station_selected = key($first_polling_station);
      }

      $polling_station = node_load($polling_station_selected);
    }
  }

  if ($polling_station) {
    $form['polling_stations_container']['polling_station_details'] = array(
      '#prefix' => '<div id="js-polling-station-details">',
      '#suffix' => '</div>',
      '#markup' => _valghalla_external_server_signup_get_polling_station_detail_html($polling_station),
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

  $terms_agreement_default = 'Accepter at vi gemmer dine oplysninger.';
  $form['terms_agreement'] = array(
    '#type' => 'checkbox',
    '#title' => !empty($party->field_party_subsc_terms_text) ? $party->field_party_subsc_terms_text['und'][0]['value'] : $terms_agreement_default,
    '#required' => TRUE,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Subscribe'),
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
  $first_polling_station = reset($form_state['available_polling_stations']);
  $polling_station_selected = key($first_polling_station);
  $form['polling_stations_container']['polling_station_select']['#value'] = $polling_station_selected;

  $polling_station = node_load($polling_station_selected);

  $form['polling_stations_container']['polling_station_details']['#markup'] = _valghalla_external_server_signup_get_polling_station_detail_html($polling_station);

  return $form['polling_stations_container'];
}

/**
 * Ajax callback for polling station select.
 *
 * Updated the polling station details.
 *
 * @return mixed
 *   Polling station details element.
 */
function valghalla_external_server_signup_polling_station_select_callback($form, $form_state) {
  return $form['polling_stations_container']['polling_station_details'];
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
 * Create node for volunteer and adding to volunteer to post.
 */
function valghalla_external_server_signup_signup_form_submit($form, $form_state) {
  $election_nid = $form_state['election']->nid;
  $party_tid = $form_state['party']->tid;
  $role_nid = ($form_state['role']->nid) ? $form_state['role']->nid : $role_nid = $form_state['values']['role_select'];
  $polling_station_nid = ($form_state['polling_station']) ? $form_state['polling_station']->nid : $form_state['values']['polling_station_select'];

  if ($polling_station_nid && $role_nid && $party_tid && $election_nid) {
    $volunteer_node = new stdClass();
    $volunteer_node->type = 'volunteers';
    $volunteer_node->language = LANGUAGE_NONE;
    node_object_prepare($volunteer_node);
    $volunteer_node->status = 1;

    $cpr = $form_state['values']['cpr'];
    $volunteer_node->title = "New volunteer, CPR: " . $cpr;

    $volunteer_node->field_cpr_number[LANGUAGE_NONE][]['value'] = $cpr;
    $volunteer_node->field_external_signup[LANGUAGE_NONE][]['value'] = 1;

    node_save($volunteer_node);
    $post_info = valghalla_volunteers_add_volunteer_to_post($volunteer_node->nid, $polling_station_nid, $role_nid, $party_tid, $election_nid, 1);
    $post = entity_load('field_collection_item', array($post_info['fcid']));
    if ($post) {
      $post = reset($post);
      $post->field_rsvp_comment[LANGUAGE_NONE][]['value'] = $form_state['values']['comment'];
      $post->save();
    }
  }
}

/**
 * External server signup settings form.
 */
function valghalla_external_server_signup_settings_form($form, $form_state) {
  $form['valghalla_external_server_signup_text_party_fs'] = array(
    '#type' => 'fieldset',
    '#title' => t('Party only texts'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['valghalla_external_server_signup_text_party_fs']['valghalla_external_server_signup_text_party_upper'] = array(
    '#title' => t('Party only upper text'),
    '#type' => 'textarea',
    '#default_value' => variable_get('valghalla_external_server_signup_text_party_upper'),
  );
  $form['valghalla_external_server_signup_text_party_fs']['valghalla_external_server_signup_text_party_bottom'] = array(
    '#title' => t('Party only bottom text'),
    '#type' => 'textarea',
    '#default_value' => variable_get('valghalla_external_server_signup_text_party_bottom'),
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

  $form['valghalla_external_server_signup_text_party_role_fs'] = array(
    '#type' => 'fieldset',
    '#title' => t('Party and role text'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['valghalla_external_server_signup_text_party_role_fs']['valghalla_external_server_signup_text_party_role_upper'] = array(
    '#title' => t('Party and role upper text'),
    '#type' => 'textarea',
    '#default_value' => variable_get('valghalla_external_server_signup_text_party_role_upper'),
  );
  $form['valghalla_external_server_signup_text_party_role_fs']['valghalla_external_server_signup_text_party_role_bottom'] = array(
    '#title' => t('Party and role bottom text'),
    '#type' => 'textarea',
    '#default_value' => variable_get('valghalla_external_server_signup_text_party_role_bottom'),
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

  $form['valghalla_external_server_signup_text_party_role_polling_station_fs'] = array(
    '#type' => 'fieldset',
    '#title' => t('Party, role and polling station text'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['valghalla_external_server_signup_text_party_role_polling_station_fs']['valghalla_external_server_signup_text_party_role_polling_station_upper'] = array(
    '#title' => t('Party, role and polling station upper text'),
    '#type' => 'textarea',
    '#default_value' => variable_get('valghalla_external_server_signup_text_party_role_polling_station_upper'),
  );
  $form['valghalla_external_server_signup_text_party_role_polling_station_fs']['valghalla_external_server_signup_text_party_role_polling_station_bottom'] = array(
    '#title' => t('Party, role and polling station bottom text'),
    '#type' => 'textarea',
    '#default_value' => variable_get('valghalla_external_server_signup_text_party_role_polling_station_bottom'),
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

  return system_settings_form($form);
}
