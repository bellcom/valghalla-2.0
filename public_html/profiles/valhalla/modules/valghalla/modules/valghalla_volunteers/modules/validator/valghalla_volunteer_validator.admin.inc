<?php

/**
 * Page callback for admin settings page.
 */
function valghalla_volunteer_validator_settings() {
  ctools_include('plugins');

  // CPR validation plugins.
  $plugins = ctools_get_plugins('valghalla_volunteer_validator', 'cpr_service');

  $services = array(
    'get_address' => t('Hent adresse'),
    'validate_cpr' => t('Valider CPR'),
  );

  $map_services = function (&$value, $key, $services) {
    $value = $services[$value];
  };

  foreach ($plugins as $id => $plugin) {
    $implements = array_intersect(array_keys($plugin), array_keys($services));
    array_walk($implements, $map_services, $services);

    $cpr_service_options[$id] = array(
      $plugin['label'],
      $plugin['description'],
      implode(', ', $implements),
      l(t('Indstillinger'), $plugin['config']),
    );
  }

  $form['valghalla_volunteer_validator_enable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Aktiver CPR validering'),
    '#default_value' => variable_get('valghalla_volunteer_validator_enable', FALSE),
  );

  $form['valghalla_volunteer_validator_get_address'] = array(
    '#type' => 'checkbox',
    '#title' => t('Aktiver automatisk indhentning af adresse'),
    '#default_value' => variable_get('valghalla_volunteer_validator_get_address', FALSE),
  );

  $form['valghalla_volunteer_validator_get_name'] = array(
    '#type' => 'checkbox',
    '#title' => t('Hent deltagerens navn fra CPR service. Kræver indhentning af adresse.'),
    '#default_value' => variable_get('valghalla_volunteer_validator_get_name', FALSE),
  );

  $form['valghalla_volunteer_validator_get_subscription_status'] = array(
    '#type' => 'checkbox',
    '#title' => t('Hent deltagerens Digital post tilmeldingstatus fra CPR service.'),
    '#default_value' => variable_get('valghalla_volunteer_validator_get_subscription_status', FALSE),
  );

  $header = ['CPR service', 'Beskrivelse', 'Understøtter', 'Valgmuligheder'];

  $form['valghalla_volunteer_validator_cpr_service'] = array(
    '#type' => 'tableselect',
    '#header' => $header,
    '#multiple' => TRUE,
    '#options' => $cpr_service_options,
    '#default_value' => variable_get('valghalla_volunteer_validator_cpr_service'),
    '#empty' => t('Der er ikke installeret nogen cpr services')
  );

  // "Regular validation plugins".
  $plugins = ctools_get_plugins('valghalla_volunteer_validator', 'validate');

  $services = array(
    'validate' => t('Valider deltager'),
  );

  $map_services = function (&$value, $key, $services) {
    $value = $services[$value];
  };

  foreach ($plugins as $id => $plugin) {
    $implements = array_intersect(array_keys($plugin), array_keys($services));
    array_walk($implements, $map_services, $services);

    $service_options[$id] = array(
      $plugin['label'],
      $plugin['description'],
      l(t('Indstillinger'), $plugin['config']),
    );
  }

  $form['validate_create'] = array(
    '#markup' => '<strong>Check deltagere ved oprettelse</strong>',
  );
  $form['validate_create_age'] = array(
    '#type' => 'checkbox',
    '#title' => t('Valider alder'),
    '#default_value' => variable_get('validate_create_age', FALSE),
  );
  $form['validate_create_municipality'] = array(
    '#type' => 'checkbox',
    '#title' => t('Valider bopæl i kommunen'),
    '#default_value' => variable_get('validate_create_municipality', FALSE),
  );
  $form['validate_create_citizenship'] = array(
    '#type' => 'checkbox',
    '#title' => t('Valider dansk statsborger'),
    '#default_value' => variable_get('validate_create_citizenship', FALSE),
  );
  $form['validate_create_civil_status'] = array(
    '#type' => 'checkbox',
    '#title' => t('Valider om person med personnummerer er levende'),
    '#default_value' => variable_get('validate_create_civil_status', FALSE),
  );

  $header = ['Plugin', 'Beskrivelse', 'Valgmuligheder'];

  $form['valghalla_volunteer_validator_services'] = array(
    '#type' => 'tableselect',
    '#header' => $header,
    '#multiple' => TRUE,
    '#options' => $service_options,
    '#default_value' => variable_get('valghalla_volunteer_validator_services'),
    '#empty' => t('Der er ikke installeret nogen validerings services'),
  );

  $form['bottom'] = array(
    '#type' => 'item',
    '#prefix' => '<a class="btn btn-link" href="/admin/valghalla/validator/batch/address">Opdater alle deltageres adresser</a></div>',
  );

  return system_settings_form($form);
}

/**
 * Page callback for activating batch operation
 */
function valghalla_volunteer_validator_batch($form, &$form_state, $arg) {
  $types = array(
      'address' => 'Hente alle deltageres adresser'
  );

  if ( !in_array($arg, array_keys($types)) ) {
    drupal_goto('admin/valghalla/validator');
  }
  $form['operation'] = array(
      '#type' => 'hidden',
      '#value' => $arg,
  );

  $form['#submit'][] = 'valghalla_volunteer_validator_batch_submit';

  $message = $types[$arg] . '?';

  return confirm_form($form, 'Opdater deltagere', 'admin/valghalla/validator', $message, t('Ja, fortsæt'), t('Annuller'));
}

/**
 * Implements hook_FORM_ID_submit().
 */
function valghalla_volunteer_validator_batch_submit(&$form, &$form_state) {
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
          ->entityCondition('bundle', 'volunteers');
  $nids = array_keys(reset($query->execute()));

  // Build operations array, handle 10 volunteer nodes, at the time
  $nid_chunks = array_chunk($nids, 10);
  foreach ($nid_chunks as $batch_nids) {
    $operations[] = array(
        'valghalla_volunteer_validator_batch_process', array($form_state['values']['operation'], $batch_nids)
    );
  }

  // Start batch
  batch_set(
          array(
              'title' => t('Behandler deltagere...'),
              'operations' => $operations,
              'finished' => 'valghalla_volunteer_validator_finished_batch',
              'file' => drupal_get_path('module', 'valghalla_volunteer_validator') . '/valghalla_volunteer_validator.admin.inc',
          )
  );
}

/**
 * Batch callback
 */
function valghalla_volunteer_validator_batch_process($op, $nids, &$context) {
  // Loop over nids in this batch
  foreach ($nids as $nid) {
    $node = node_load($nid);

    $cpr = FALSE;

    if ( $cpr_field = field_get_items('node', $node, 'field_cpr_number') ) {
      $cpr = $cpr_field[0]['value'];
    }

    $format_errors = array();
    if (!valghalla_volunteer_validator_validate_format($cpr)) {
      valghalla_volunteer_validator_reformat_cpr($cpr, $node);
      $context['results']['format_errors'][$nid] = array('nid' => $nid);
      continue;
    }

    $messages = valghalla_volunteer_validator_query_service('get_address', $cpr);

    foreach ($messages as $message) {
      // If the volunteer is not found in the CPR service, save the error.
      if ( $message['status'] === FALSE ) {
        $context['results']['address_errors'][$nid]['address'] = array('nid' => $nid, 'text' => $message['text']);
        continue;
      }

      // Map of volunteer fields and indexes on the message array.
      $field_map = array(
        'field_address_road' => 'road',
        'field_address_road_no' => 'road_no',
        'field_address_floor' => 'floor',
        'field_address_door' => 'door',
        'field_address_zipcode' => 'zipcode',
        'field_address_city' => 'city',
        'field_address_coname' => 'coname',
        'field_municipality' => 'municipality',
      );

      // Set the values on the node.
      foreach ($field_map as $field => $index) {
        $node->{$field}[$node->language][0]['value'] = trim($message[$index]);
      }
    }

    node_save($node);
  }
}

/**
 * Batch finished callback
 *
 * @author Thomas Thune Hansen <tth@bellcom.dk>
 */
function valghalla_volunteer_validator_finished_batch($success, $results, $operations) {
  if ( $success ) {

    $format_errors = '';

    foreach ($results['format_errors'] as $error) {
      $format_errors .= '<a target="_blank" href="/node/' . $error['nid'] . '/edit">' . $error['nid'] . '</a>, ';
    }

    $address_errors = '';
    foreach ($results['address_errors'] as $nid => $errors) {
      foreach ($errors as $error) {
        $address_errors .= '<a target="_blank" href="/node/' . $error['nid'] . '/edit">' . $error['nid'] . '</a>: ' . $error['text'] . '<br>';
      }
    }

    $validate_errors = '';
    foreach ($results['validate_errors'] as $nid => $errors) {
      foreach ($errors as $error) {
        $validate_errors .= '<a target="_blank" href="/node/' . $nid . '/edit">' . $nid . '</a>: ' . $error['text'] . '<br>';
      }
    }

    // Messages
    drupal_set_message('Handlingen blev gennemført');

    if ( strlen($format_errors) ) {
      drupal_set_message('Følgende deltagere (id\'er) har ugyldigt CPR-nummer: ' . $format_errors, 'warning');
    }

    if ( strlen($address_errors) ) {
      drupal_set_message('Der kunne ikke hentes adresser på følgende deltagere:' . '<br>' . $address_errors, 'warning');
    }

    if ( strlen($validate_errors) ) {
      drupal_set_message('Følgende deltagere kunne ikke valideres:' . '<br>' . $validate_errors, 'warning');
    }

    drupal_goto('admin/valghalla/validator');
  }
}

/**
 * Page callback for validate batch operation.
 */
function valghalla_volunteer_validator_validate_batch($form, &$form_state, $el_nid = FALSE) {
  $election = node_load($el_nid);
  if (empty($election)) {
    $form['message'] = array(
      '#markup' => 'Valg fundet ikke.',
    );
    return $form;
  }

  // Get election volunteers.
  $volunteer_query = new EntityFieldQuery();
  $volunteer_query->entityCondition('entity_type', 'field_collection_item')
    ->entityCondition('bundle', 'field_electioninfo')
    ->propertyCondition('archived', 0)
    ->fieldCondition('field_election', 'target_id', $election->nid);

  $query_result = $volunteer_query->execute();
  $fcids = array_shift($query_result);

  if (empty($fcids)) {
    $form['message'] = array(
      '#markup' => t('Deltagere blev fundet ikke til @election valget', array('@election' => $election->title)),
    );
    return $form;
  }

  $form_state['storage']['fcids'] = $fcids;
  $form_state['storage']['election'] = $election;

  $form['#submit'][] = 'valghalla_volunteer_validator_validate_batch_submit';
  $message = t('Validere @count deltagere?', array('@count' => count($fcids)));

  return confirm_form($form,
    t('Validate @election valget deltagere', array('@election' => $election->title)),
    'admin/valghalla/validator',
    $message,
    t('Ja, fortsæt'),
    t('Annuller')
  );
}

/**
 * Implements hook_FORM_ID_submit().
 */
function valghalla_volunteer_validator_validate_batch_submit(&$form, &$form_state) {
  $election = $form_state['storage']['election'];
  $fcids = $form_state['storage']['fcids'];

  // Build operations array, handle 10 volunteer nodes, at the time.
  $fcids_chunks = array_chunk($fcids, 10);

  foreach ($fcids_chunks as $batch_fcids) {
    $operations[] = array(
      'valghalla_volunteer_validator_validate_batch_process',
      array($election, $batch_fcids),
    );
  }

  // Start batch.
  batch_set(
    array(
      'title' => t('Behandler deltagere...'),
      'operations' => $operations,
      'finished' => 'valghalla_volunteer_validator_finished_validate_batch',
      'file' => drupal_get_path('module', 'valghalla_volunteer_validator') . '/valghalla_volunteer_validator.admin.inc',
    )
  );
}

/**
 * Validation batch callback.
 */
function valghalla_volunteer_validator_validate_batch_process($election, $fcids, &$context) {
  // Loop over fcids in this batch.
  foreach ($fcids as $fcid) {
    $fc = entity_load_single('field_collection_item', $fcid->item_id);
    $volunteer = $fc->hostEntity();
    $cpr = FALSE;

    if ($cpr_field = field_get_items('node', $volunteer, 'field_cpr_number')) {
      $cpr = $cpr_field[0]['value'];
    }

    if (!valghalla_volunteer_validator_validate_format($cpr)) {
      valghalla_volunteer_validator_reformat_cpr($cpr, $volunteer);
      $context['results']['format_errors'][$volunteer->nid] = array('nid' => $volunteer->nid);
      continue;
    }

    // Getting party.
    $field_post_party = field_get_items('field_collection_item', $fc, 'field_post_party');
    if (!empty($field_post_party)) {
      $party_tid = $field_post_party[0]['target_id'];
      $party = taxonomy_term_load($party_tid);
    }

    if (empty($election) || empty($party)) {
      continue;
    }

    $election_config = valghalla_volunteer_validator_get_election_config($election, $party);
    $messages = valghalla_volunteer_validator_query_service('validate_cpr_per_election', $cpr, $election_config);

    $field_election_date = field_get_items('node', $election, 'field_date');
    if (!empty($field_election_date[0]['value'])) {
      $context = array_merge(array('election_date' => $field_election_date[0]['value']), $election_config);
      $messages = array_merge($messages, valghalla_volunteer_validator_validate_service('validate_per_election', $cpr, $context));
    }

    // Collect invalid volunteers messages.
    foreach ($messages as $message) {
      if ($message['status'] === FALSE) {
        $context['results']['validate_errors'][$volunteer->nid]['cpr'] = array('nid' => $volunteer->nid, 'text' => $message['text']);
      }
    }
  }
}

/**
 * Validate batch finished callback.
 */
function valghalla_volunteer_validator_finished_validate_batch($success, $results, $operations) {
  if ($success) {
    $format_errors = '';
    foreach ($results['format_errors'] as $error) {
      $format_errors .= '<a target="_blank" href="/node/' . $error['nid'] . '/edit">' . $error['nid'] . '</a>, ';
    }

    $validate_errors = '';
    foreach ($results['validate_errors'] as $nid => $errors) {
      foreach ($errors as $error) {
        $validate_errors .= '<a target="_blank" href="/node/' . $nid . '/edit">' . $nid . '</a>: ' . $error['text'] . '<br>';
      }
    }

    // Messages.
    drupal_set_message('Handlingen blev gennemført');

    if (strlen($format_errors)) {
      drupal_set_message('Følgende deltagere (id\'er) har ugyldigt CPR-nummer: ' . $format_errors, 'warning');
    }

    if (strlen($validate_errors)) {
      drupal_set_message('Følgende deltagere kunne ikke valideres:' . '<br>' . $validate_errors, 'warning');
    }

    drupal_goto('valghalla/administration/valg');
  }
}

/**
 * CPR reformat function.
 *
 * @param string $cpr
 *   CPR value.
 * @param object $node
 *   Volunteer node object.
 *
 * @throws Exception
 */
function valghalla_volunteer_validator_reformat_cpr($cpr, $node) {
  if (strlen($cpr) == 10) {
    return;
  }

  $reformatted = implode('-', str_split($cpr, 6));
  if (!valghalla_volunteer_validator_validate_format($reformatted)) {
    return;
  }

  $node_wrapper = entity_metadata_wrapper('node', $node);
  $node_wrapper->field_cpr_number = $reformatted;
  node_save($node);
}
