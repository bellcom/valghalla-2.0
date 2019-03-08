<?php

/**
 * @file
 * Utils code for the valghalla volunteers module.
 */

/**
 * Helper function to get volunteers.
 */
function valghalla_volunteers_get_assigned_volunteers($election_nid = NULL, $polling_station_nid = NULL, $party_tid = NULL, $role_nid = NULL) {
  $query_result = valghalla_volunteers_get_fc_electioninfo($election_nid, $polling_station_nid, $party_tid, $role_nid);
  $result = array_shift($query_result);

  foreach ($result as $fc_id => $fc_row) {
    $query = db_select('field_collection_item', 'fci');
    $query->condition('fci.field_name ', 'field_electioninfo');
    $query->fields('fci', array('item_id'));

    $query->join('field_data_field_electioninfo', 'fei', 'fci.item_id = fei.field_electioninfo_value');
    $query->fields('fei', array('entity_id'));

    $query->join('node', 'nv', 'nv.nid = fei.entity_id');
    $query->fields('nv', array('title'));

    $query->join('field_data_field_election', 'fe', 'fci.item_id = fe.entity_id');
    $query->fields('fe', array('field_election_target_id'));

    $query->join('field_data_field_vlnt_station', 'fvs', 'fci.item_id = fvs.entity_id');
    $query->fields('fvs', array('field_vlnt_station_target_id'));

    $query->join('field_data_field_post_role', 'fpr', 'fci.item_id = fpr.entity_id');
    $query->fields('fpr', array('field_post_role_target_id'));

    $query->join('field_data_field_post_party', 'fpp', 'fci.item_id = fpp.entity_id');
    $query->fields('fpp', array('field_post_party_target_id'));

    $query->condition('fci.item_id ', $fc_id);
    $res = $query->execute()->fetchAll();
    $volunteers_fc[$fc_id] = empty($res) ? NULL : reset($res);
  }
  return $volunteers_fc;
}

/**
 * Generates tabled of assigned volunteers.
 */
function valghalla_volunteers_assigned($election_nid, $polling_station_nid, $party_tid, $role_nid) {
  $volunteers_fc = valghalla_volunteers_get_assigned_volunteers($election_nid, $polling_station_nid, $party_tid, $role_nid);

  $header = array(
    'FC id',
    'Navn',
    'Valget',
    'Valgsted',
    'Patri',
    'Role',
    'Action',
  );
  $rows = array();

  foreach ($volunteers_fc as $fc_id => $fc) {
    $election = node_load($fc->field_election_target_id);
    $pooling_station = node_load($fc->field_vlnt_station_target_id);
    $party = taxonomy_term_load($fc->field_post_party_target_id);
    $role = node_load($fc->field_post_role_target_id);
    $row = array(
      $fc_id,
      empty($fc->title) ? NULL : l($fc->title, 'node/' . $fc->entity_id . '/edit', array('query' => array('destination' => current_path()))),
      empty($election) ? NULL : $election->title,
      empty($pooling_station) ? NULL : $pooling_station->title,
      empty($party) ? NULL : $party->name,
      empty($role) ? NULL : $role->title,
      l(t('Delete'), 'volunteers/cleanup-fc/' . $fc_id, array('query' => array('destination' => current_path()))),
    );
    $rows[$fc_id] = $row;
  }

  return theme('table', array('header' => $header, 'rows' => $rows));
}

/**
 * Remove broken volunteers.
 */
function valghalla_volunteers_remove_broken($form, &$form_state, $fc_id) {
  $fc = entity_load_single('field_collection_item', $fc_id);
  if (empty($fc)) {
    return array('#markup' => t('Field collection with id %fc_id is empty.', array('%fc_id' => $fc_id)));
  }

  $volunteer = $fc->hostEntity();
  $election = field_get_items('field_collection_item', $fc, 'field_election');
  $post_role = field_get_items('field_collection_item', $fc, 'field_post_role');
  $post_party = field_get_items('field_collection_item', $fc, 'field_post_party');
  $vlnt_station = field_get_items('field_collection_item', $fc, 'field_vlnt_station');

  if (!empty($volunteer)
    && !empty($election) && !empty(node_load($election[0]['target_id']))
    && !empty($post_role) && !empty(node_load($post_role[0]['target_id']))
    && !empty($post_party) && !empty(taxonomy_term_load($post_party[0]['target_id']))
    && !empty($vlnt_station) && !empty(node_load($vlnt_station[0]['target_id']))) {
    $form['warning'] = array(
      '#type' => 'item',
      '#prefix' => '<strong>',
      '#suffix' => '</strong>',
      '#markup' => t("This field collection doesn't seems to be broken. Are you sure?"),
    );
  }
  else {
    $form['warning'] = array(
      '#type' => 'item',
      '#markup' => t("This field collection looks broken."),
    );
  }

  $form['fc_id'] = array(
    '#type' => 'hidden',
    '#value' => $fc_id,
  );
  $form['#submit'][] = 'valghalla_volunteers_remove_broken_submit';
  $message = t('You are going to delete field collection %fc_id that bind volunteer%volunteer_text to election place.', array(
    '%fc_id' => $fc_id,
    '%volunteer_text' => empty($volunteer->title) ? '' : (' for volunteer ' . $volunteer->title),
  ));

  return confirm_form($form, 'Remove broken field collection', '<front>', $message);
}

/**
 * Remove broken volunteers submit action.
 */
function valghalla_volunteers_remove_broken_submit(&$form, &$form_state) {
  if ($form_state['values']['confirm']) {
    $fc_id = $form_state['values']['fc_id'];
    $fc = entity_load_single('field_collection_item', $fc_id);
    $fc->delete();

    $message = t('Field collection %fc_id has been deleted as broken.', array('%fc_id' => $fc_id));
    watchdog('content', $message, array());
    drupal_set_message($message);
  }
}

function valghalla_volunteers_get_fc_electioninfo($condition = array()) {
  // Total assigned for role.
  $volunteer_query = new EntityFieldQuery();
  $volunteer_query->entityCondition('entity_type', 'field_collection_item')
    ->entityCondition('bundle', 'field_electioninfo')
    ->propertyCondition('archived', 0);

  if ($election_nid) {
    $volunteer_query->fieldCondition('field_election', 'target_id', $election_nid);
  }
  if ($polling_station_nid) {
    $volunteer_query->fieldCondition('field_vlnt_station', 'target_id', $polling_station_nid);
  }
  if ($party_tid) {
    $volunteer_query->fieldCondition('field_post_party', 'target_id', $party_tid);
  }
  if ($role_nid) {
    $volunteer_query->fieldCondition('field_post_role', 'target_id', $role_nid);
  }

  return $volunteer_query->execute();
}
