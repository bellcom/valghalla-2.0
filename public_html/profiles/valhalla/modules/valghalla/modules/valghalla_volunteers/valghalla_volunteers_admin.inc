<?php
/**
 * Reset volunteers confirmation form
 *
 * @author Thomas Thune Hansen <tth@bellcom.dk>
 */
function valghalla_volunteers_reset(){
  $type = arg(4);

  $types = array(
    'pos' => t('pladser'),
    'rsvp' => t('svar'),
  );

  $form['operation'] = array(
    '#type' => 'hidden',
    '#value' => $type
  );

  $form['#submit'][] = 'valghalla_volunteers_reset_submit';

  $message = t('Er du sikker på at du ønsker at slette alle tilforordenes ') . $types[$type] . '?';

  return confirm_form($form, 'Nulstil deltagere', 'admin/valghalla/', $message, t('Ja, fortsæt'), t('Annuller'));
}

/**
 *
 * @author Thomas Thune Hansen <tth@bellcom.dk>
 */
function valghalla_volunteers_reset_submit(&$form, &$form_state){
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'volunteers');
  $nids = array_keys(reset($query->execute()));

  // Build operations array, handle 10 volunteer nodes, at the time
  $nid_chunks = array_chunk($nids, 10);
  foreach($nid_chunks as $batch_nids){
    $operations[] = array(
      'valghalla_volunteers_reset_batch', array($form_state['values']['operation'], $batch_nids)
    );
  }

  // Start batch
  batch_set(
    array(
      'title' => t('Nulstil deltagere'),
      'operations' => $operations,
      'finished' => 'valghalla_volunteers_reset_finished_batch',
      'file' => drupal_get_path('module', 'valghalla_volunteers') .'/valghalla_volunteers_admin.inc',
    )
  );
}

/**
 * Batch callback
 *
 * @author Thomas Thune Hansen <tth@bellcom.dk>
 */
function valghalla_volunteers_reset_batch($op, $nids, &$context){
  // Loop over nids in this batch
  foreach($nids as $nid){
    $node = node_load($nid);

    // Reset what the user has chosen $op
    switch($op){
      case 'pos':
          $node->field_polling_station_post = array();
        break;

      case 'rsvp':
          $node->field_rsvp = array();
          $node->field_rsvp_comment = array();
        break;
    }

    node_save($node);
  }
}

/**
 * Batch finished callback
 *
 * @author Thomas Thune Hansen <tth@bellcom.dk>
 */
function valghalla_volunteers_reset_finished_batch($success, $results, $operations){
  if($success){
    drupal_set_message(t('Deltagerne er nu nulstillet'));
    drupal_goto('admin/valghalla');
  }
}


function valghalla_volunteers_admin_start_election_form($form, &$form_state, $xtras) {
  $form['info'] = array(
    '#type' => 'item',
    '#title' => t('Så starter vi.'),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Importér'),
  );

  return $form;
}
