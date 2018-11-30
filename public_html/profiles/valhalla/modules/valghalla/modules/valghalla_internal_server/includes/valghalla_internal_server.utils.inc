<?php

/**
 * Performs a validation on a single volunteer node.
 *
 * @param $volunteer_node
 *
 * @return array
 */
function valghalla_internal_server_validate_volunteer($volunteer_node) {
  $validationStatus = array(
    'valid' => TRUE,
    'errors' => array()
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

  //run validator
  $messages = valghalla_volunteer_validator_query_service('validate_cpr', $cpr, 'single');

  foreach ($messages as $message) {
    if ($message['status'] === FALSE) {
      $validationStatus['errors'][] = t('Det angivne CPR-nummer kan ikke valideres: @text', array('@text' => $message['text']));
      $validationStatus['valid'] = FALSE;
    }
  }

  if ($errors = valghalla_volunteer_validator_validate($volunteer_node, 'single')) {
    $validationStatus['errors'][] = t('Det angivne CPR-nummer kan ikke valideres: @text', array('@text' => $message['text']));
    $validationStatus['valid'] = FALSE;
  }

  return $validationStatus;
}

function valghalla_internal_server_volunteer_update_name_and_address($volunteer_node) {
  $cpr_field = field_get_items('node', $volunteer_node, 'field_cpr_number');
  $cpr = $cpr_field[0]['value'];

  $get_address_messages = valghalla_volunteer_validator_query_service('get_address', $cpr);
  $lang = $volunteer_node->language;

  foreach ($get_address_messages as $get_address_message) {
    if ($get_address_message['status']) {
      $volunteer_node->title = $get_address_message['name'];
      $volunteer_node->field_address_road[$lang][0]['value'] =  $get_address_message['road'];
      $volunteer_node->field_address_road_no[$lang][0]['value'] =  $get_address_message['road_no'];
      $volunteer_node->field_address_floor[$lang][0]['value'] =  $get_address_message['floor'];
      $volunteer_node->field_address_door[$lang][0]['value'] =  $get_address_message['door'];
      $volunteer_node->field_address_zipcode[$lang][0]['value'] =  $get_address_message['zipcode'];
      $volunteer_node->field_address_city[$lang][0]['value'] =  $get_address_message['city'];
      $volunteer_node->field_address_coname[$lang][0]['value'] =  $get_address_message['coname'];
      $volunteer_node->field_municipality['und'][0]['value'] =  $get_address_message['municipality'];

      node_save($volunteer_node);
    }
  }
}

function valghalla_internal_server_mark_invalid($volunteer_node, $messages = array()) {
  if ($volunteer_node->nid) {
    $data = array();
    $data['target_id'] = $volunteer_node->nid;
    $data['target_uuid'] = $volunteer_node->uuid;
    $data['timestamp'] = $_SERVER['REQUEST_TIME'];
    $data['message'] = implode('; ', $messages);

    db_insert('valghalla_internal_server_logs')
      ->fields($data)
      ->execute();
  }
}

function valghalla_internal_server_term_to_json($term) {
  $voc = taxonomy_vocabulary_machine_name_load($term->vocabulary_machine_name);
  unset($term->vocabulary_machine_name);
  $term->vid = $voc->vid;

  return drupal_json_encode($term);
}

function valghalla_internal_server_anonymize_node($node) {
  // Do the anonymization for volunteers only.
  if ($node->type == 'volunteers') {
    $node->title = 'Anonymized volunteer node';
    unset($node->field_address_bnummer);
    unset($node->field_address_city);
    unset($node->field_address_coname);
    unset($node->field_address_door);
    unset($node->field_address_floor);
    unset($node->field_address_road);
    unset($node->field_address_road_no);
    unset($node->field_address_zipcode);
    unset($node->field_cpr_valid_date);
    unset($node->field_email);
    unset($node->field_municipality);
    unset($node->field_phone);
    unset($node->field_phone2);
  }
  return $node;
}
