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

  // Field_electioninfo.
  // Finding field_electioninfo with non-valid host entity.
  $efq = new EntityFieldQuery();
  $efq->entityCondition('entity_type', 'field_collection_item');
  $efq->propertyCondition('field_name', 'field_electioninfo');
  $efq->addTag('ei_host_null');
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
  $efq->propertyCondition('archived', 0);
  $efq->addTag('ei_field_election_empty');
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
  $efq->propertyCondition('archived', 0);
  $efq->addTag('ei_field_post_role_empty');
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
  $efq->propertyCondition('archived', 0);
  $efq->addTag('ei_field_vlnt_station_empty');
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
  $efq->propertyCondition('archived', 0);
  $efq->addTag('ei_field_post_party_empty');
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
  $efq->addTag('vppsp_host_null');
  $result = $efq->execute();

  if (is_array($result['field_collection_item'])) {
    foreach ($result['field_collection_item'] as $fc) {
      $orphaned_fcs[] = $fc->item_id;
    }
  }

  // Field_volunteers_pr_pol_st_party.
  // Finding field_volunteers_pr_pol_st_party with non-valid
  // field_ppsp_polling_station.
  $efq = new EntityFieldQuery();
  $efq->entityCondition('entity_type', 'field_collection_item');
  $efq->propertyCondition('field_name', 'field_volunteers_pr_pol_st_party');
  $efq->addTag('vppsp_field_ppsp_polling_station_empty');
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
  $efq->addTag('vppsp_field_ppsp_party_empty');
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
