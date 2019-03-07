<?php

/**
 * @file
 * Utils code for the valghalla volunteers module.
 */

/**
 * Helper function to get volunteers.
 */
function valghalla_volunteers_get_assigned_volunteers($election_nid = NULL, $polling_station_nid = NULL, $party_tid = NULL, $role_nid = NULL) {
  // Total assigned for role.
  $volunteer_query = new EntityFieldQuery();
  $volunteer_query->entityCondition('entity_type', 'field_collection_item')
    ->entityCondition('bundle', 'field_electioninfo')
    ->propertyCondition('archived', 0)
    ->fieldCondition('field_election', 'target_id', $election_nid)
    ->fieldCondition('field_vlnt_station', 'target_id', $polling_station_nid)
    ->fieldCondition('field_post_role', 'target_id', $role_nid);

  $volunteer_query->fieldCondition('field_post_party', 'target_id', $party_tid);
  $query_result = $volunteer_query->execute();
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
    );
    $rows[$fc_id] = $row;
  }

  return theme('table', array('header' => $header, 'rows' => $rows));
}
