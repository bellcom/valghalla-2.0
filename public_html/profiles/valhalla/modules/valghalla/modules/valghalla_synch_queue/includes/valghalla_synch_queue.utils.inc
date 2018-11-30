<?php

function valghalla_synch_queue_add_item($resource) {
  $data = array();
  if ($resource->nid) {
    $data['target_id'] = $resource->nid;
    $data['type'] = 'node';
    $data['changed'] = $resource->changed;
  }
  elseif (($resource->tid)) {
    $data['target_id'] = $resource->tid;
    $data['type'] = 'taxonomy_term';
    $data['changed'] = $_SERVER['REQUEST_TIME'];
  }

  if ($data['target_id']) {
    $data['target_uuid'] = $resource->uuid;

    if (valghalla_synch_queue_load_item($data['target_uuid'])) {
      db_update('valghalla_synch_queue')
        ->fields($data)
        ->condition('target_uuid', $data['target_uuid'])
        ->execute();
    }
    else {
      db_insert('valghalla_synch_queue')
        ->fields($data)
        ->execute();
    }
  }
}

function valghalla_synch_queue_remove_item($uuid) {
  db_delete('valghalla_synch_queue')
    ->condition('target_uuid', $uuid)
    ->execute();
}


function valghalla_synch_queue_get_items_ordered() {
  $itemsOrdered = array();

  // Taxonomy terms do not have any relationship, safe to push them as they are.
  $query = db_select('valghalla_synch_queue', 'v')
    ->fields('v')
    ->condition('type', 'taxonomy_term');
  $taxonomy_terms = $query->execute()->fetchAll();
  $itemsOrdered = array_merge($itemsOrdered, $taxonomy_terms);

  // Correct node order is: Role, Constituency, Polling station, Election, Volunteer
  $contentTypes = array('roles', 'constituency', 'polling_station', 'election', 'volunteers');

  foreach($contentTypes as $type) {
    $query = db_select('valghalla_synch_queue', 'v')
      ->fields('v');

    $query->join('node', 'n', 'n.nid = v.target_id');
    $query->condition('v.type', 'node')
      ->condition('n.type', $type);

    $nodes = $query->execute()->fetchAll();
    $itemsOrdered = array_merge($itemsOrdered, $nodes);
  }

  return $itemsOrdered;
}

/**
 * Loads queue item from local table.
 *
 * @param $uuid
 *
 * @return mixed
 * @see valghalla_synch_queue_load_items
 */
function valghalla_synch_queue_load_item($uuid) {
  $items = valghalla_synch_queue_load_items(array($uuid));
  if (!empty($items) && is_array($items)) {
    return reset($items);
  }
}

/**
 * Loads queue item from local table.
 *
 * @param array $uuids
 * @param array $conditions
 *
 * @return mixed
 */
function valghalla_synch_queue_load_items($uuids = array(), $conditions = array()) {
  $query = db_select('valghalla_synch_queue', 'v')
    ->fields('v');

  if (!empty($uuids)) {
    $query->condition('target_uuid', $uuids, 'IN');
  }
  if (!empty($conditions)) {
    foreach ($conditions as $contidionKey => $condition) {
      $query->condition($contidionKey, $condition);
    }
  }

  $result = $query->execute()->fetchAll();

  return $result;
}