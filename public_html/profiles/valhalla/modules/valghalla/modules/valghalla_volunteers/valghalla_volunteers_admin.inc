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

  return confirm_form($form, 'Nulstil frivillige', 'admin/valghalla/', $message, t('Ja, fortsæt'), t('Annuller'));
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
      'title' => t('Nulstil frivillige'),
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
    drupal_set_message(t('De frivillige er nu nulstillet'));
    drupal_goto('admin/valghalla');
  }
}

function valghalla_volunteers_admin_import_form($form, &$form_state) {

  $form['#attributes'] = array('enctype' => "multipart/form-data");
  $form['import'] = array(
    '#type' => 'fieldset',
    '#title' => t('Importér nye frivillige'),
  );
  $form['import']['upload'] = array(
    '#type' => 'file',
  );
  $form['import']['truncate'] = array(
    '#type' => 'checkbox',
    '#title' => t('Slet alle tilforordnede før de importen.'),
  );
  $form['import']['note'] = array(
    '#type' => 'item',
    '#title' => t('Note'),
    '#description' => '<p>'.t('Hvis du vælger at slette alle tilforordnede før importen, vil al information om disse gå tabt.').'</p>',
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Importér'),
  );

  return $form;
}

function valghalla_volunteers_admin_import_form_validate($form, &$form_state) {
  $validators = array('file_validate_extensions' => array('csv'));
  $file = file_save_upload('upload', $validators);

  if (FALSE == $file) {
    form_set_error('import][upload', t('Mangler en gyldig csv fil.'));
  } else {
    $form_state['file object'] = $file;
  }
}

function valghalla_volunteers_admin_import_form_submit($form, &$form_state) {
  global $language;

  module_load_include('inc', 'valghalla_volunteers', 'valghalla_volunteers');

  /**
   * handle truncate request
   */
  if ($form_state['values']['truncate'] == 1) {
    $nids = db_select('node', 'n')
      ->fields('n', array('nid'))
      ->condition('type', 'volunteers', '=')
      ->execute()
      ->fetchAll(PDO::FETCH_COLUMN)
    ;
    node_delete_multiple($nids);
  }

  $import = _valghalla_helter_parse_csv_import($form_state['file object']);

  if ($import) {
    drupal_set_message(t('Impotren oprettede @added og opdaterede @updated tilforordnede.', array('@added' => $import['added'], '@updated' => $import['updated'])));

    if ($import['failed']) {
      $msg = '<p>'.t('Følgende CPR numre er ikke gyldige.').'</p><ul>';
      foreach ($import['failed'] as $cpr => $name) {
        $msg .= '<li>' .  $name . ' ' . $cpr .'</li>';
      }
      $msg .= '</ul>';
      drupal_set_message($msg, 'error');
    }
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
