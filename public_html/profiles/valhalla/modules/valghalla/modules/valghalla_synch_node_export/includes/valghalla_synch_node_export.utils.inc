<?php

/**
 * @file
 * Valghalla_synch_node_export.utils.inc.
 */

/**
 * Finds orphaned field collection items.
 *
 * Finds all the field collection items that have orphaned dependency or do not
 * have a valid host entity.
 */
function valgahalla_synch_node_export_find_orphaned_fc_items() {
  $orphaned_fcs = array();

  // Getting all elections.
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'election');
  $result = $query->execute();
  if (isset($result['node'])) {
    $all_election_ids = array_keys($result['node']);
  }

  // Getting all polling stations.
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'polling_station');
  $result = $query->execute();
  if (isset($result['node'])) {
    $all_polling_stations_ids = array_keys($result['node']);
  }

  // Getting all roles.
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'roles');
  $result = $query->execute();
  if (isset($result['node'])) {
    $all_roles_ids = array_keys($result['node']);
  }

  // Getting parties.
  $party_vocab = taxonomy_vocabulary_machine_name_load('partier');
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'taxonomy_term')
    ->propertyCondition('vid', $party_vocab->vid);
  $result = $query->execute();
  if (isset($result['taxonomy_term'])) {
    $all_parties_ids = array_keys($result['taxonomy_term']);
  }

  // Field_electioninfo.
  // Finding field_electioninfo with non-valid host entity.
  $efq = new EntityFieldQuery();
  $efq->entityCondition('entity_type', 'field_collection_item');
  $efq->propertyCondition('field_name', 'field_electioninfo');
  $efq->addTag('veine');
  $result = $efq->execute();

  if (is_array($result['field_collection_item'])) {
    foreach ($result['field_collection_item'] as $fc) {
      $orphaned_fcs[] = $fc->item_id;
    }
  }

  // Field_electioninfo.
  // Finding field_electioninfo with non-valid field_election.
  $efq = new EntityFieldQuery();
  $efq->entityCondition('entity_type', 'field_collection_item');
  $efq->propertyCondition('field_name', 'field_electioninfo');
  $efq->fieldCondition('field_election', 'target_id', $all_election_ids, 'NOT IN');
  $result = $efq->execute();

  if (is_array($result['field_collection_item'])) {
    foreach ($result['field_collection_item'] as $fc) {
      $orphaned_fcs[] = $fc->item_id;
    }
  }

  // Field_electioninfo.
  // Finding field_electioninfo with non-valid field_post_role.
  $efq = new EntityFieldQuery();
  $efq->entityCondition('entity_type', 'field_collection_item');
  $efq->propertyCondition('field_name', 'field_electioninfo');
  $efq->fieldCondition('field_post_role', 'target_id', $all_roles_ids, 'NOT IN');
  $result = $efq->execute();

  if (is_array($result['field_collection_item'])) {
    foreach ($result['field_collection_item'] as $fc) {
      $orphaned_fcs[] = $fc->item_id;
    }
  }

  // Field_electioninfo.
  // Finding field_electioninfo with non-valid field_vlnt_station.
  $efq = new EntityFieldQuery();
  $efq->entityCondition('entity_type', 'field_collection_item');
  $efq->propertyCondition('field_name', 'field_electioninfo');
  $efq->fieldCondition('field_vlnt_station', 'target_id', $all_polling_stations_ids, 'NOT IN');
  $result = $efq->execute();

  if (is_array($result['field_collection_item'])) {
    foreach ($result['field_collection_item'] as $fc) {
      $orphaned_fcs[] = $fc->item_id;
    }
  }

  // Field_electioninfo.
  // Finding field_electioninfo with non-valid field_post_party.
  $efq = new EntityFieldQuery();
  $efq->entityCondition('entity_type', 'field_collection_item');
  $efq->propertyCondition('field_name', 'field_electioninfo');
  $efq->fieldCondition('field_post_party', 'target_id', $all_parties_ids, 'NOT IN');
  $result = $efq->execute();

  if (is_array($result['field_collection_item'])) {
    foreach ($result['field_collection_item'] as $fc) {
      $orphaned_fcs[] = $fc->item_id;
    }
  }

  // Field_volunteers_pr_pol_st_party.
  // Finding field_volunteers_pr_pol_st_party with non-valid host entity.
  $efq = new EntityFieldQuery();
  $efq->entityCondition('entity_type', 'field_collection_item');
  $efq->propertyCondition('field_name', 'field_volunteers_pr_pol_st_party');
  $efq->addTag('vvppspne');
  $result = $efq->execute();

  if (is_array($result['field_collection_item'])) {
    foreach ($result['field_collection_item'] as $fc) {
      $orphaned_fcs[] = $fc->item_id;
    }
  }

  // Field_volunteers_pr_pol_st_party.
  // Finding field_volunteers_pr_pol_st_party with non-valid field_ppsp_polling_station.
  $efq = new EntityFieldQuery();
  $efq->entityCondition('entity_type', 'field_collection_item');
  $efq->propertyCondition('field_name', 'field_volunteers_pr_pol_st_party');
  $efq->fieldCondition('field_ppsp_polling_station', 'nid', $all_polling_stations_ids, 'NOT IN');
  $result = $efq->execute();

  if (is_array($result['field_collection_item'])) {
    foreach ($result['field_collection_item'] as $fc) {
      $orphaned_fcs[] = $fc->item_id;
    }
  }

  // Field_volunteers_pr_pol_st_party.
  // Finding field_volunteers_pr_pol_st_party with non-valid field_ppsp_party.
  $efq = new EntityFieldQuery();
  $efq->entityCondition('entity_type', 'field_collection_item');
  $efq->propertyCondition('field_name', 'field_volunteers_pr_pol_st_party');
  $efq->fieldCondition('field_ppsp_party', 'tid', $all_parties_ids, 'NOT IN');
  $result = $efq->execute();

  if (is_array($result['field_collection_item'])) {
    foreach ($result['field_collection_item'] as $fc) {
      $orphaned_fcs[] = $fc->item_id;
    }
  }

  $orphaned_fcs = array_unique($orphaned_fcs);
  reset($orphaned_fcs);
  sort($orphaned_fcs);

  return $orphaned_fcs;
}
