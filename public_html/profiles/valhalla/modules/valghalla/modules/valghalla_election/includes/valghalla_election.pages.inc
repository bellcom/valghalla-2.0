<?php

/**
 * @file
 * Valghalla_election.pages.inc.
 */

/**
 * Builds seats form for polling station form.
 */
function valghalla_election_handle_seats_form($form, &$form_state, $polling_station_nid) {
  $election_nid = $_SESSION['election_nid'];
  $election = node_load($election_nid);

  $polling_station = node_load($polling_station_nid);

  drupal_set_title(t('Handle seats for polling station') . ' ' . $polling_station->title);

  $field_volunteers_pr_pol_st_party = field_get_items('node', $election, 'field_volunteers_pr_pol_st_party');
  if (!empty($field_volunteers_pr_pol_st_party)) {
    foreach ($field_volunteers_pr_pol_st_party as $fc_id) {
      $fc_entities = entity_load('field_collection_item', array($fc_id['value']));
      $fc = reset($fc_entities);

      if ($fc) {
        $field_ppsp_polling_station = field_get_items('field_collection_item', $fc, 'field_ppsp_polling_station');
        if (!empty($field_ppsp_polling_station) && $field_ppsp_polling_station[0]['nid'] == $polling_station_nid) {
          $form[$fc_id['value']] = array();

          $fc_form = array();
          $fc_form_state = array();

          $langcode = entity_language('field_collection_item', $fc);
          field_attach_form('field_collection_item', $fc, $fc_form, $fc_form_state, $langcode);

          // It is very important to unset parents, otherwise the received
          // values will be collapsed.
          unset($fc_form['#parents']);
          $form[$fc_id['value']] = $fc_form;

          $form[$fc_id['value']]['field_ppsp_party']['#disabled'] = 'disabled';
          $form[$fc_id['value']]['field_ppsp_polling_station']['#access'] = FALSE;
        }
      }
    }
  }

  $form['#tree'] = TRUE;

  $form[] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
 * Form valghalla_election_handle_seats_form validate.
 * 
 * Uses valghalla_election_field_volunteers_pr_pol_st_party_form_validate for
 * actual validation, but gracefully handles the reassignment of the errors to
 * correct fields.
 */
function valghalla_election_handle_seats_form_validate($form, &$form_state) {
  $all_form_errors = array();

  foreach ($form as $entity_id => $entity_form_values) {
    if (isset($entity_form_values['#entity'])) {
      $entity_form_state = array(
        'values' => $form_state['values'][$entity_id]
      );

      // Getting form errors.
      valghalla_election_field_volunteers_pr_pol_st_party_form_validate($entity_form_values, $entity_form_state);
      $errors = form_get_errors();

      // Clear form errors.
      form_clear_error();

      foreach ($entity_form_values as $entity_field_key => $entity_field) {
        // If this is a field, check if we need to put some errors.
        if (strpos($entity_field_key, 'field_') === 0) {
          if (array_key_exists($entity_field_key, $errors)) {
            $all_form_errors["$entity_id][$entity_field_key"] = $errors[$entity_field_key];
            unset($errors[$entity_field_key]);
          }
        }
      }

      // Saving other errors for future.
      if (!empty($errors)) {
        $all_form_errors += $errors;
      }
    }
  }

  // Clear error messages.
  drupal_get_messages('error');

  // Setting the errors.
  foreach ($all_form_errors as $el => $error) {
    form_set_error($el, $error);
  }
}

/**
 * Form valghalla_election_handle_seats_form submit.
 *
 * Saving field collection.
 */
function valghalla_election_handle_seats_form_submit($form, $form_state) {
  foreach ($form as $entity_id => $entity_form_values) {
    if (isset($entity_form_values['#entity'])) {
      $fc = $entity_form_values['#entity'];
      foreach ($form_state['values'][$entity_id] as $key => $value) {
        $fc->{$key} = $value;
      }
      $fc->save();
    }
  }
}
