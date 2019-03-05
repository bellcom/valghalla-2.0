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

  // Looping through field_electioninfo fields collection.
  $efq = new EntityFieldQuery();
  $efq->entityCondition('entity_type', 'field_collection_item');
  $efq->propertyCondition('field_name', 'field_electioninfo');
  $result = $efq->execute();

  foreach ($result['field_collection_item'] as $fc) {
    $fc_loaded = entity_load_single('field_collection_item', $fc->item_id);

    // No valid host entity.
    if (!$fc_loaded->hostEntity()) {
      $orphaned_fcs[] = $fc_loaded;
      continue;
    }

    // Checking field_election relation.
    $field_election = field_get_items('field_collection_item', $fc_loaded, 'field_election');
    if ($field_election && is_array($field_election)) {
      $election_nid = $field_election[0]['target_id'];
      if (!node_load($election_nid)) {
        $orphaned_fcs[] = $fc_loaded;
        continue;
      }
    }

    // Checking field_post_role relation.
    $field_post_role = field_get_items('field_collection_item', $fc_loaded, 'field_post_role');
    if ($field_post_role && is_array($field_post_role)) {
      $role_nid = $field_post_role[0]['target_id'];
      if (!node_load($role_nid)) {
        $orphaned_fcs[] = $fc_loaded;
        continue;
      }
    }

    // Checking field_vlnt_station relation.
    $field_vlnt_station = field_get_items('field_collection_item', $fc_loaded, 'field_vlnt_station');
    if ($field_vlnt_station && is_array($field_vlnt_station)) {
      $polling_station_nid = $field_vlnt_station[0]['target_id'];
      if (!node_load($polling_station_nid)) {
        $orphaned_fcs[] = $fc_loaded;
        continue;
      }
    }

    // Checking field_post_party relation.
    $field_post_party = field_get_items('field_collection_item', $fc_loaded, 'field_post_party');
    if ($field_post_party && is_array($field_post_party)) {
      $party_tid = $field_post_party[0]['target_id'];
      if (!taxonomy_term_load($party_tid)) {
        $orphaned_fcs[] = $fc_loaded;
        continue;
      }
    }
  }

  // Looping through field_volunteers_pr_pol_st_party fields collection.
  $efq = new EntityFieldQuery();
  $efq->entityCondition('entity_type', 'field_collection_item');
  $efq->propertyCondition('field_name', 'field_volunteers_pr_pol_st_party');
  $result = $efq->execute();

  foreach ($result['field_collection_item'] as $fc) {
    $fc_loaded = entity_load_single('field_collection_item', $fc->item_id);

    // No valid host entity.
    if (!$fc_loaded->hostEntity()) {
      $orphaned_fcs[] = $fc_loaded;
      continue;
    }

    // Checking field_volunteers_pr_pol_st_party relation.
    $field_ppsp_polling_station = field_get_items('field_collection_item', $fc_loaded, 'field_ppsp_polling_station');
    if ($field_ppsp_polling_station && is_array($field_ppsp_polling_station)) {
      $polling_station_nid = $field_ppsp_polling_station[0]['nid'];
      if (!node_load($polling_station_nid)) {
        $orphaned_fcs[] = $fc_loaded;
        continue;
      }
    }

    // Checking field_ppsp_party relation.
    $field_ppsp_party = field_get_items('field_collection_item', $fc_loaded, 'field_ppsp_party');
    if ($field_ppsp_party && is_array($field_ppsp_party)) {
      $party_tid = $field_ppsp_party[0]['tid'];
      if (!taxonomy_term_load($party_tid)) {
        $orphaned_fcs[] = $fc_loaded;
        continue;
      }
    }
  }

  return $orphaned_fcs;
}
