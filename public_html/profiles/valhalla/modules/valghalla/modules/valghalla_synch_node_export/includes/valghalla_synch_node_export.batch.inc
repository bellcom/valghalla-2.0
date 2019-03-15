<?php

/**
 * @file
 * Valghalla_synch_node_export.batch.inc.
 */

/**
 * Field collection delete batch definition.
 *
 * @param mixed $fc_items
 *   Array of loaded field collection items.
 *
 * @return array
 *   Batch definition.
 */
function valghalla_synch_node_export_batch_delete_orphaned_fcs($fc_items) {
  if (count($fc_items)) {
    drupal_set_message(t('Deleting @num field collection items(s).', array('@num' => count($fc_items))));
  }
  else {
    drupal_set_message(t('No orphaned field collection items were found.'));
  }

  $operations = array();
  for ($i = 0; $i < count($fc_items); $i++) {
    $operations[] = array(
      'valghalla_synch_node_export_batch_delete_orphaned_fc_op',
      array(
        $fc_items[$i],
        t('(Deletion operation @operation)', array('@operation' => $i)),
      ),
    );
  }
  $batch = array(
    'operations' => $operations,
    'title' => t('Processing deleting'),
    'init_message' => t('Deletion is starting.'),
    'progress_message' => t('Deleted @current out of @total.'),
    'error_message' => t('Deletion has encountered an error.'),
    'finished' => 'valghalla_synch_node_export_batch_delete_orphaned_fcs_finished',
  );

  return $batch;
}

/**
 * Field collection item delete operation.
 *
 * Deletes field collection item.
 *
 * @param mixed $fc_item
 *   Loaded field collection item.
 * @param mixed $operation_details
 *   Details of operation.
 * @param mixed $context
 *   Array for context.
 */
function valghalla_synch_node_export_batch_delete_orphaned_fc_op($fc_item, $operation_details, &$context) {
  // Report progress.
  $context['message'] = t('Deleting field_collection item @fc_item_id', array('@fc_item_id' => $fc_item));

  $fc_loaded = entity_load_single('field_collection_item', $fc_item);
  if (!empty($fc_loaded)) {
    $fc_loaded->delete();
  }

  $context['results'][] = array(
    'message' => t('Deleted field_collection item "@fc_item_id"', array('@fc_item_id' => $fc_item)),
    'type' => 'status',
  );

}

/**
 * Batch finished callback for delete operation.
 *
 * @param bool $success
 *   Status.
 * @param mixed $results
 *   Array of result messages.
 * @param mixed $operations
 *   Array of operation messages.
 */
function valghalla_synch_node_export_batch_delete_orphaned_fcs_finished($success, $results, $operations) {
  if ($success) {
    // Counting successful.
    $successCount = 0;
    foreach ($results as $result) {
      if ($result['type'] === 'status') {
        $successCount++;
      }
    }

    drupal_set_message(t('@successCount out of @totalCount field collection item(s) have been deleted.', array(
      '@successCount' => $successCount,
      '@totalCount' => count($results),
    )));

    foreach ($results as $result) {
      drupal_set_message($result['message'], $result['type']);
    }
  }
  else {
    // An error occurred.
    // $operations contains the operations that remained unprocessed.
    $error_operation = reset($operations);

    drupal_set_message(
      t('An error occurred while processing {
      @operation
} with arguments : @args',
        array(
          '@operation' => $error_operation[0],
          '@args' => print_r($error_operation[0], TRUE),
        )
      ),
      'error'
    );
  }
}
