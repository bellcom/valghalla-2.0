<?php

/**
 * Node clone batch definition.
 *
 * @param $uuids
 *
 * @return array
 */
function valghalla_internal_server_batch_clone($uuids) {
  drupal_set_message(t('Preparing to clone @num node(s).', array('@num' => count($uuids))));

  $operations = array();
  for ($i = 0; $i < count($uuids); $i++) {
    $operations[] = array(
      'valghalla_internal_server_batch_clone_op',
      array(
        $uuids[$i],
        t('(Cloning operation @operation)', array('@operation' => $i)),
      )
    );
  }
  $batch = array(
    'operations' => $operations,
    'title' => t('Processing cloning'),
    'init_message' => t('Cloning is starting.'),
    'progress_message' => t('Processed @current out of @total.'),
    'error_message' => t('Cloning has encountered an error.'),
    'finished' => 'valghalla_internal_server_batch_clone_finished',
  );

  return $batch;
}

/**
 * Node clone batch operation.
 * Clones the node locally.
 *
 * @param $uuid
 * @param $operation_details
 * @param $context
 */
function valghalla_internal_server_batch_clone_op($uuid, $operation_details, &$context) {
  // Load node local data we are about to clone.
  $existingNode = NULL;
  $entities = entity_uuid_load('node', array($uuid));
  if (!empty($entities) && is_array($entities)) {
    $existingNode = reset($entities);
  }

  // Report progress.
  if ($existingNode) {
    $context['message'] = t('Cloning node %title', array('%title' => $existingNode->title));
  }
  else {
    $context['message'] = t('Cloning new node', array());
  }

  // Actual webservice call.
  $ws = new ExternalWebservice();
  $data = $ws->exportByUuid($uuid);

  // We got the node export data.
  if (strpos($data, 'node_export_serialize') === 0) {
    // Prepare and create a new node.
    $import = node_export_import($data);
    if ($import['success']) {
      // We expect only one node to be imported.
      $nid = reset($import['nids']);
      $node = node_load($nid);

      // Remove the item from the queue, we don't want to push it after the update.
      valghalla_synch_queue_remove_item($node->uuid);

      // Fetch name and address
      valghalla_internal_server_volunteer_update_name_and_address($node);

      // Handle validation.
      $validationStatus = valghalla_internal_server_validate_volunteer($node);

      //$validationStatus['valid'] = TRUE;//TODO: remove
      if ($validationStatus['valid']) {
        $context['results'][] = array(
          'message' => t('Node "@title" imported into <a href="@link">@title</a>.', array(
            '@title' => $node->title,
            '@link' => url('node/' . $nid)
          )),
          'type' => 'status'
        );

        //TODO: notify volunteer
      }
      else {
        valghalla_internal_server_mark_invalid($node, $validationStatus['errors']);

        $context['results'][] = array(
          'message' => t('Node "@title" imported into <a href="@link">@title</a>. But failed validation. Messages: @messages', array(
            '@title' => $node->title,
            '@link' => url('node/' . $nid),
            '@messages' => implode('; ', $validationStatus['errors'])
          )),
          'type' => 'status'
        );

        //TODO: free seat
      }

      // Delete the item from queue on the external server.
      $ws->removeFromQueueByUuid($uuid);
    }
  }
  else {
    // Report the problem.
    if ($existingNode) {
      $context['results'][] = array(
        'message' => t('Node "@title" import failed. Message: @message', array(
          '@title' => $existingNode->title,
          '@message' => $data,
        )),
        'type' => 'warning'
      );
    }
    else {
      $context['results'][] = array(
        'message' => t('Node "@uuid" import failed. Message: @message', array(
          '@uuid' => $uuid,
          '@message' => $data,
        )),
        'type' => 'warning'
      );
    }
  }
}

/**
 * Batch finished callback for clone operation.
 *
 * @param $success
 * @param $results
 * @param $operations
 */
function valghalla_internal_server_batch_clone_finished($success, $results, $operations) {
  if ($success) {
    // Counting successful.
    $successCount = 0;
    foreach ($results as $result) {
      if ($result['type'] === 'status') {
        $successCount++;
      }
    }

    drupal_set_message(t('@successCount out of @totalCount node(s) have been cloned.', array(
      '@successCount' => $successCount,
      '@totalCount' => count($results)
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

/**
 * Resource push batch definition.
 *
 * @param $items
 *
 * @return array
 */
function valghalla_internal_server_batch_push($items) {
  drupal_set_message(t('Preparing to push @num resources(s) . ', array('@num' => count($items))));

  $operations = array();
  for ($i = 0; $i < count($items); $i++) {
    $operations[] = array(
      'valghalla_internal_server_batch_push_op',
      array(
        $items[$i],
        t('(Push operation @operation)', array('@operation' => $i)),
      )
    );
  }
  $batch = array(
    'operations' => $operations,
    'title' => t('Processing push'),
    'init_message' => t('Push is starting . '),
    'progress_message' => t('Processed @current out of @total . '),
    'error_message' => t('Push has encountered an error . '),
    'finished' => 'valghalla_internal_server_batch_push_finished',
  );

  return $batch;
}

/**
 * Resource push batch operation.
 * Pushed the resource to the external server, upon success removes the item from a synch queue.
 *
 * @param $item
 * @param $operation_details
 * @param $context
 */
function valghalla_internal_server_batch_push_op($item, $operation_details, &$context) {
  $existingItem = NULL;
  $entities = entity_uuid_load($item->type, array($item->target_uuid));
  if (!empty($entities) && is_array($entities)) {
    $existingItem = reset($entities);
  }

  if ($existingItem) {
    $ws = new ExternalWebservice();

    if ($item->type == 'taxonomy_term') {
      // Report progress.
      $context['message'] = t('Pushing taxonomy term @title', array('@title' => $existingItem->name));

      // Actual webservice call.
      $result = $ws->pushTerm($existingItem);
      if ($result === 1) {
        $context['results'][] = array(
          'message' => t('Term "@title" is successfully pushed and created on external server', array(
            '@title' => $existingItem->name,
          )),
          'type' => 'status'
        );

        valghalla_synch_queue_remove_item($existingItem->uuid);
      } elseif ($result === 2) {
        $context['results'][] = array(
          'message' => t('Term "@title" is successfully pushed and updated on external server', array(
            '@title' => $existingItem->name,
          )),
          'type' => 'status'
        );

        valghalla_synch_queue_remove_item($existingItem->uuid);
      } else {
        $context['results'][] = array(
          'message' => t('Term "@title" push failed, message: @message', array(
            '@title' => $existingItem->name,
            '@message' => implode(' ', $result)
          )),
          'type' => 'warning'
        );
      }
    } elseif ($item->type == 'node') {
      // Report progress.
      $context['message'] = t('Pushing node @title', array('@title' => $existingItem->title));

      // Anonymize the content.
      $existingItem = valghalla_internal_server_anonymize_node($existingItem);

      // Exporting with serialize formatter.
      $export = node_export(intval($existingItem->nid), 'serialize');
      $data = $export['output'];

      // Actual webservice call.
      $result = $ws->pushNodeSerialized($data);

      // Operation was successful.
      if ($result->nid) {
        $context['results'][] = array(
          'message' => t('Node "@title" is successfully pushed, and its remote nid is @rnid', array(
            '@title' => $existingItem->title,
            '@rnid' => $result->nid
          )),
          'type' => 'status'
        );

        valghalla_synch_queue_remove_item($existingItem->uuid);
      }
      else {
        $context['results'][] = array(
          'message' => t('Node "@title" push failed, message: @message', array(
            '@title' => $existingItem->title,
            '@message' => implode(' ', $result)
          )),
          'type' => 'warning'
        );
      }
    }
  }
}

/**
 * Batch finished callback for push operation.
 *
 * @param $success
 * @param $results
 * @param $operations
 */
function valghalla_internal_server_batch_push_finished($success, $results, $operations) {
  if ($success) {
    // Counting successful.
    $successCount = 0;
    foreach ($results as $result) {
      if ($result['type'] === 'status') {
        $successCount++;
      }
    }

    drupal_set_message(t('@successCount out of @totalCount node(s) have been committed.', array(
      '@successCount' => $successCount,
      '@totalCount' => count($results)
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
