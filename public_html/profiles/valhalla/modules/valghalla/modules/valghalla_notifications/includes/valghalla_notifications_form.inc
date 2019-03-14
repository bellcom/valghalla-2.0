<?php

/**
 * @file
 * Handles the form elements of valghalla_notifications.
 */

/**
 * Form for Step 1 create_template_node step.
 */
function valghalla_notifications_send_create_template_node($gateway_id) {
  $gateway = valghalla_notifications_gateway($gateway_id);
  if (empty($gateway)) {
    drupal_set_message('Sending gateway @gateway_id not found', array('@gateway_id' => $gateway_id));
    drupal_not_found();
  }
  module_load_include('inc', 'node', 'node.pages');
  return node_add($gateway['node_type']);
}

/**
 * Implements hook_form_alter().
 */
function valghalla_notifications_form_alter(&$form, &$form_state) {
  $form_ids = array();
  foreach (valghalla_notifications_gateways() as $gateway) {
    $form_ids[$gateway['node_type'] . '_node_form'] = $gateway;
  }
  if (!isset($form_ids[$form['#form_id']])) {
    return;
  }

  $gateway = $form_ids[$form['#form_id']];

  $form['#attributes']['class'][] = 'valghalla-notifications-send';
  drupal_add_js(drupal_get_path('module', 'valghalla_notifications') . '/js/valghalla_notifications.js');

  if (isset($form['body'])) {
    $form['body'] += array('#suffix' => '');
    $form['body']['#suffix'] = _valghalla_helper_get_volunteer_info_params('info') . $form['body']['#suffix'];
  }
  $url = current_path();

  $form['title']['#description'] = 'Beskeds interne navn i Valghalla, dette er ikke emnefeltet.';

  if (strpos($url, "valghalla/administration/send-message") === 0) {
    $form_state['storage']['valghalla_send_message'] = TRUE;

    valghalla_notifications_get_navigation_header($form, $form_state);
    $form['template'] = array(
      '#type' => 'select',
      '#weight' => -100,
      '#options' => valghalla_notifications_generate_options($gateway['id']),
      '#title' => t('Vælg en besked skabelon her:'),
      '#suffix' => '<p><strong>Eller opret en ny herunder:</strong></p>',
    );
  }

  if (isset($form_state['storage']['valghalla_send_message'])) {
    $form['options']['status']['#default_value'] = 1;
    $form['additional_settings']['#prefix'] = '<div style="display:none;">';
    $form['additional_settings']['#suffix'] = '</div>';
    $form['actions']['submit']['#submit'][] = 'valghalla_notifications_send_form_step';
    $form['actions']['submit']['#value'] = t('Next');
    hide($form['actions']['preview']);
  }
}

/**
 * Custom submit callback for notifications nodes.
 */
function valghalla_notifications_send_form_step(&$form, &$form_state) {
  $nid = $form_state['node']->nid;
  drupal_goto('valghalla/administration/sendto/' . $nid);
}

/**
 * Stage switch.
 *
 * Step 2 : get_recipients
 * Step 3 : send_confirm.
 */
function valghalla_notifications_send_message_form($form, &$form_state, $nid) {
  drupal_add_css(drupal_get_path('module', 'valghalla_notifications') . '/css/valghalla_notifications.css');
  drupal_add_js(drupal_get_path('module', 'valghalla_notifications') . '/js/valghalla_notifications.js');
  $form['#attributes']['class'][] = 'valghalla-notifications-send';

  if (!isset($form_state['storage']['stage'])) {
    $form_state['storage']['stage'] = 'get_recipients';
  }

  valghalla_notifications_get_navigation_header($form, $form_state);

  switch ($form_state['storage']['stage']) {
    case 'send_confirm':
      return valghalla_notifications_confirm_form($form, $form_state);

    default:
      return valghalla_notifications_recipients_form($form, $form_state, $nid);
  }
}

/**
 * Form for Step 2 get_recipients step.
 *
 * @see valghalla_notifications_send_message_form()
 */
function valghalla_notifications_recipients_form($form, &$form_state, $nid) {
  if (!is_numeric($nid) || !isset($nid)) {
    form_set_error('no_message', t("Ingen besked indhold."));
  }

  $node = node_load($nid);

  // Fetch gateway.
  $gateway = FALSE;
  foreach (valghalla_notifications_gateways() as $val) {
    if ($val['node_type'] == $node->type) {
      $gateway = $val;
    }
  }

  if (empty($gateway)) {
    drupal_set_message(t("Gateway fundet ikke."), 'error');
    return $form;
  }

  $gateway_id = $gateway['id'];
  $form_state['storage']['gateway_id'] = $gateway_id;

  $values = isset($form_state['multistep_values']['get_recipients']) ? $form_state['multistep_values']['get_recipients'] : array();
  module_load_include('inc', 'valghalla_volunteers');

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
      $description = ' <a class="form-submit" href="/valghalla/administration/send-message/' . $gateway_id . '">' . t('Add') . '</a>';
    }
  }
  else {
    $description = ' <a class="form-submit" href="/valghalla/administration/send-message/' . $gateway_id . '">' . t('Add') . '</a>';
  }

  $form['message_content']['valghalla_notifications_message_node_ID'] = array(
    '#title' => t('Valgt skabelon'),
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

  if (!empty($gateway_id)) {
    drupal_alter('notifications_' . $gateway_id . '_recipients_form', $form, $form_state);
  }

  $form['next'] = array(
    '#type' => 'submit',
    '#value' => t('Next'),
  );
  return $form;
}

/**
 * Form for Step 3 send_confirm step.
 *
 * @see valghalla_notifications_send_message_form()
 */
function valghalla_notifications_confirm_form($form, &$form_state) {
  global $language;

  $values = isset($form_state['multistep_values']['get_recipients']) ? $form_state['multistep_values']['get_recipients'] : array();
  $volunteers_fcids = valghalla_notifications_get_recipients($values);

  $gateway = valghalla_notifications_gateway($form_state['storage']['gateway_id']);
  if (empty($gateway) && $values['valghalla_notifications_message_node_ID'] != 'invite') {
    drupal_set_message(t('Gateway blev fundet ikke.'), 'error');
    return $form;
  }
  $count = 0;
  $volunteers_list = "";
  $send_list_to = array();
  foreach (entity_load('field_collection_item', $volunteers_fcids) as $volunteer_item) {
    $volunteer_node = $volunteer_item->hostEntity();
    $to = '';
    if (function_exists($gateway['send_to_callback'])) {
      $to = call_user_func($gateway['send_to_callback'], $volunteer_node);
    }
    $recipients = $volunteer_node->title . ($to ? (" (" . $to . ")") : '');
    $fc_id = $values['valghalla_notifications_message_node_ID'] . "/" . $volunteer_item->item_id;
    if ($values['valghalla_notifications_message_node_ID'] == 'invite') {
      $fc_id .= '/' . $values['election_nid'];
    }
    // Add link to preview.
    $prefix = " <a class='js-show-volunteer-message' id='" . $fc_id . "' href='#'>";
    $recipients = $prefix . $recipients . "</a>";
    if ($volunteers_list == "") {
      $volunteers_list .= $recipients;
      $send_list_to[$volunteer_node->nid] = $to;
    }
    else {
      $volunteers_list .= ", ";
      $volunteers_list .= $recipients;

      // TODO duplicate send to data.
      $send_list_to[$volunteer_node->nid] = $to;
    }
    $count += 1;
  }
  $form['confirm_message_node'] = array(
    '#title' => t('Besked indhold'),
    '#type' => 'fieldset',
    '#description' => t('Klik på navnet for at se besked for den modtager'),
  );
  $form['confirm_message_node']['js_message_body'] = array(
    '#type' => 'item',
    '#prefix' => '<div class="js-volunteer-preview-message well">',
    '#markup' => '',
    "#suffix" => "</div>",
  );
  $form['confirm_info'] = array(
    '#title' => t('Er du sikker på du vil udsende besked til @count modtagere ?', array('@count' => $count)),
    '#type' => 'fieldset',
    '#description' => $volunteers_list,
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
    'valghalla_sendlist_array' => $send_list_to,
    'valghalla_sendlist_acount' => $count,
  );

  return $form;
}

/**
 * Get all the recipients data.
 */
function valghalla_notifications_get_recipients($values) {
  global $language;
  module_load_include('inc', 'valhalla_volunteers');

  if (isset($values['invitation']) && $values['invitation'] === TRUE) {
    $volunteer_query = new EntityFieldQuery();
    $volunteer_query->entityCondition('entity_type', 'field_collection_item')
      ->entityCondition('bundle', 'field_electioninfo')
      ->propertyCondition('archived', 0)
      ->fieldCondition('field_post_role', 'target_id', 'NULL', '!=')
      ->fieldCondition('field_election', 'target_id', $values['election_nid']);

    // Ensure that messages are going to be send to volunteers
    // on polling stations that are active.
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
          $rsvp_field = field_get_items('field_collection_item', $fc, 'field_rsvp');
        }

        if (isset($polling_stations[$polling_station_nid]) && (empty($rsvp_field[0]['value']) || $rsvp_field[0]['value'] == '0')) {
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
      ->entityCondition('bundle', 'field_electioninfo')
      ->propertyCondition('archived', 0);

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
    $result = array_keys(array_shift($query_result));
  }

  foreach (entity_load('field_collection_item', $result) as $volunteer_item) {
    $volunteer_node = $volunteer_item->hostEntity();
    if (!isset($volunteer_node)) {
      continue;
    }
    if (!valghalla_notifications_volunteer_no_notification($volunteer_node)) {
      $volunteer_fcids[] = $volunteer_item->item_id;
    }
  }

  return $volunteer_fcids;
}

/**
 * Send invitation form.
 */
function valghalla_notifications_send_invitation_form($form, &$form_state, $election_nid) {
  drupal_add_css(drupal_get_path('module', 'valghalla_notifications') . '/css/valghalla_notifications.css');
  drupal_add_js(drupal_get_path('module', 'valghalla_notifications') . '/js/valghalla_notifications.js');
  $form['#attributes']['class'][] = 'valghalla-notifications-send';
  $form_state['multistep_values']['get_recipients']['invitation'] = TRUE;
  $form_state['multistep_values']['get_recipients']['election_nid'] = $election_nid;
  $form_state['multistep_values']['get_recipients']['valghalla_notifications_message_node_ID'] = 'invite';

  // Gateway will be defained depend on election settings.
  $form_state['storage']['gateway_id'] = FALSE;
  return valghalla_notifications_confirm_form($form, $form_state);
}
