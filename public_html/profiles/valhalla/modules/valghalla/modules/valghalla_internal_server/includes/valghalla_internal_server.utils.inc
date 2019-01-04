<?php

/**
 * @file
 * Valghalla_internal_server.utils.inc.
 */

/**
 * Performs a validation on a single volunteer node.
 *
 * @param mixed $volunteer_node
 *   Volunteer node.
 *
 * @return array
 *   Array with keys 'valid' - boolean, 'errors' - list of errors.
 */
function valghalla_internal_server_validate_volunteer($volunteer_node) {
  $validationStatus = array(
    'valid' => TRUE,
    'errors' => array(),
  );

  $cpr_field = field_get_items('node', $volunteer_node, 'field_cpr_number');
  $cpr = $cpr_field[0]['value'];

  // Check formatting.
  if (!valghalla_volunteer_validator_validate_format($cpr)) {
    $validationStatus['errors'][] = t('Det angivne CPR-nummer er ikke korrekt formatteret (f.eks. 123456-8910).');
    $validationStatus['valid'] = FALSE;
  }

  // Check for duplicates.
  if ($nid = valghalla_volunteer_validator_check_duplicates($cpr)) {
    if ($nid !== $volunteer_node->nid) {
      $validationStatus['errors'][] = t('Der er allerede oprettet en deltager med det angivne CPR-nummer');
      $validationStatus['valid'] = FALSE;
    }
  }

  // Run volunteer create validator.
  $messages = valghalla_volunteer_validator_query_service('validate_cpr', $cpr);

  // Run volunteer validator per last election.
  $field_electioninfo = field_get_items('node', $volunteer_node, 'field_electioninfo');
  if (!empty($field_electioninfo)) {
    $lastElement = end($field_electioninfo);
    $electionInfo = entity_load_single('field_collection_item', $lastElement['value']);

    // Getting election.
    $field_election = field_get_items('field_collection_item', $electionInfo, 'field_election');
    if (!empty($field_election)) {
      $election_nid = $field_election[0]['target_id'];
      $election = node_load($election_nid);
    }

    // Getting party.
    $field_post_party = field_get_items('field_collection_item', $electionInfo, 'field_post_party');
    if (!empty($field_post_party)) {
      $party_tid = $field_post_party[0]['target_id'];
      $party = taxonomy_term_load($party_tid);
    }
  }

  if ($election && $party) {
    $election_config = valghalla_volunteer_validator_get_election_config($election, $party);
    $messages = array_merge($messages, valghalla_volunteer_validator_query_service('validate_cpr_per_election', $cpr, $election_config));
  }

  foreach ($messages as $message) {
    if ($message['status'] === FALSE) {
      $validationStatus['errors'][] = t('Det angivne CPR-nummer kan ikke valideres: @text', array('@text' => $message['text']));
      $validationStatus['valid'] = FALSE;
    }
  }

  if ($errors = valghalla_volunteer_validator_validate($volunteer_node)) {
    $validationStatus['errors'][] = t('Det angivne CPR-nummer kan ikke valideres: @text', array('@text' => $message['text']));
    $validationStatus['valid'] = FALSE;
  }

  return $validationStatus;
}

/**
 * Marks volunteer as invalid.
 *
 * Does it by saving validation error messages into
 * valghalla_internal_server_logs table.
 *
 * @param mixed $volunteer_node
 *   Volunteer node.
 * @param array $messages
 *   Array of messages.
 */
function valghalla_internal_server_mark_invalid($volunteer_node, array $messages = array()) {
  if ($volunteer_node->nid) {
    $cpr_field = field_get_items('node', $volunteer_node, 'field_cpr_number');
    $cpr = $cpr_field[0]['value'];

    $data = array();
    $data['target_id'] = $volunteer_node->nid;
    $data['target_uuid'] = $volunteer_node->uuid;
    $data['cpr'] = $cpr;
    $data['timestamp'] = $_SERVER['REQUEST_TIME'];
    $data['message'] = serialize($messages);

    db_insert('valghalla_internal_server_logs')
      ->fields($data)
      ->execute();
  }
}

/**
 * Encodes term object as json string.
 *
 * @param mixed $term
 *   The term.
 *
 * @return string
 *   Encoded string.
 */
function valghalla_internal_server_term_to_json($term) {
  $voc = taxonomy_vocabulary_machine_name_load($term->vocabulary_machine_name);
  unset($term->vocabulary_machine_name);
  $term->vid = $voc->vid;

  return drupal_json_encode($term);
}

/**
 * Unsets the last selected seat from the volunteer.
 *
 * @param mixed $volunteer
 *   Volunteer node.
 */
function valghalla_internal_server_free_last_selected_seat($volunteer) {
  $field_electioninfo = field_get_items('node', $volunteer, 'field_electioninfo');

  if (!empty($field_electioninfo)) {
    $fc_field = end($field_electioninfo);
    if ($fc_field['value']) {
      $fc = entity_load_single('field_collection_item', $fc_field['value']);
      $fc->delete();
    }
  }
}

/**
 * Generates the url for external signup.
 *
 * @param mixed $election
 *   Election node.
 * @param mixed $party
 *   Party taxonomy term.
 * @param mixed $role
 *   Role node, optional.
 * @param mixed $polling_station
 *   Polling station node, optional.
 *
 * @return string
 *   Generated subscribe url.
 */
function valghalla_internal_server_generate_external_subscribe_url($election, $party, $role = NULL, $polling_station = NULL) {
  $subscribe_url = '';
  if ($external_service_url = valghalla_internal_server_get_external_server_url()) {
    if ($election && $party) {
      // Adding election and party, mandatory params.
      $subscribe_url = $external_service_url . '/valghalla/external-signup?election=' . $election->uuid . '&party=' . $party->uuid;

      if ($role) {
        // Adding role.
        $subscribe_url .= '&role=' . $role->uuid;
      }
      if ($polling_station) {
        // Adding polling station.
        $subscribe_url .= '&pol_st=' . $polling_station->uuid;
      }
    }
  }

  return $subscribe_url;
}

/**
 * Gets an external server URL without any path, also adds port if present.
 *
 * Does not have a leading slash.
 *
 * @return string
 *   External server URL.
 *   E.g. http://valghalla.dk
 */
function valghalla_internal_server_get_external_server_url() {
  $external_server_url = '';
  if ($external_service_endpoint = variable_get('valghalla_external_server_endpoint')) {
    // Parsing our endpoint to remove any paths.
    $url_parts = parse_url($external_service_endpoint);
    $external_server_url = $url_parts['scheme'] . '://' . $url_parts['host'] . (isset($url_parts['port']) ? ':' . $url_parts['port'] : '');
  }

  return $external_server_url;
}

/**
 * Notifies volunteer about the last created seat, with status 'confirmed'.
 *
 * @param mixed $node
 *   Volunteer node.
 * @param mixed $previousNode
 *   Volunteer node previous version.
 */
function valghalla_internal_server_notify_volunteer_last_seat($node, $previousNode) {
  $electionInfo = NULL;

  $field_electioninfo = field_get_items('node', $node, 'field_electioninfo');
  if (!empty($field_electioninfo)) {
    $lastElement = end($field_electioninfo);
    $electionInfo = entity_load_single('field_collection_item', $lastElement['value']);
  }

  if ($electionInfo) {
    $forceType = NULL;

    // No previous node, meaning that volunteer is using subscription form.
    // In that case, the notification type is confirmed.
    if (!$previousNode) {
      $forceType = 'confirmed';
    }
    else {
      // If the size of current electionInfo is bigger, it means a new election
      // info has been added with positive reply.
      // In this case, the notification type is confirmed.
      $previousElectionInfo = field_get_items('node', $previousNode, 'field_electioninfo');
      if (empty($previousElectionInfo) || count($field_electioninfo) != count($previousElectionInfo)) {
        $forceType = 'confirmed';
      }
    }

    valghalla_volunteers_notify_volunteer($electionInfo, $forceType);
  }
}

/**
 * Deanonymizes the node.
 *
 * Does that by decrypting the CPR, email and phone fields.
 *
 * @param mixed $node
 *   The node to deanonymize.
 */
function valghalla_internal_server_deanonymize_node($node) {
  if ($node->type == 'volunteers') {
    $external_server_hash_salt = variable_get('valghalla_external_server_hash_salt');

    $cpr_field_language = field_language('node', $node, 'field_cpr_number');
    $cpr = $node->field_cpr_number[$cpr_field_language][0]['value'];

    // If CPR format fails, try decrypting it.
    if (!preg_match('/[0-9]{10}/', $cpr) && !preg_match('/[0-9]{6}-[0-9]{4}/', $cpr)) {
      $cpr = valghalla_synch_node_export_get_decrypt($cpr, $external_server_hash_salt);

      // Check the CPR format, after decryption.
      if (preg_match('/[0-9]{10}/', $cpr) || preg_match('/[0-9]{6}-[0-9]{4}/', $cpr)) {
        // Format passed, change the CPR in the node.
        $node->field_cpr_number[$cpr_field_language][0]['value'] = $cpr;
        $node->field_cpr_number[$cpr_field_language][0]['safe_value'] = $cpr;
      }
    }

    // Email field.
    $email_field_language = field_language('node', $node, 'field_email');
    if (isset($node->field_email[$email_field_language])) {
      $email = $node->field_email[$email_field_language][0]['email'];
      $email = valghalla_synch_node_export_get_decrypt($email, $external_server_hash_salt);
      $node->field_email[$email_field_language][0]['email'] = $email;
    }

    // Phone field.
    $phone_field_language = field_language('node', $node, 'field_phone');
    if (isset($node->field_phone[$phone_field_language])) {
      $phone = $node->field_phone[$phone_field_language][0]['value'];
      $phone = valghalla_synch_node_export_get_decrypt($phone, $external_server_hash_salt);
      $node->field_phone[$phone_field_language][0]['value'] = $phone;
    }
  }

  return $node;
}
