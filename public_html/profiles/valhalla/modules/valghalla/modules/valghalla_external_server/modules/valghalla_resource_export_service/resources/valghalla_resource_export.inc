<?php
/**
 * The Valghalla resource definition.
 *
 * @return array
 */

function _valghalla_resource_export_resource_definition() {
  $resources['valghalla_resource_export'] = array(
    'operations' => array(
      // Retrieves the actual content based on uuid (node only). //TODO: add support for taxonomy_terms
      'retrieve' => array(
        'callback' => 'valghalla_resource_export_service_node_get_serialized',
        'args' => array(
          array(
            'name' => 'uuid',
            'optional' => FALSE,
            'source' => array('path' => 0),
            'type' => 'string',
            'description' => 'The uuid of the node to get',
          ),
        ),
        'access callback' => 'valghalla_resource_export_service_resource_access',//TODO: add custom permission
        'access arguments' => array('view'),
        'access arguments append' => TRUE,
      ),
      // Creates the actual content (node only).
      'create' => array(
        'file' => array('type' => 'inc', 'module' => 'valghalla_resource_export_service', 'name' => 'resources/valghalla_resource_export'),
        'callback' => 'valghalla_resource_export_node_create',
        'args' => array(
          array(
            'name' => 'params',
            'optional' => FALSE,
            'source' => 'data',
            'description' => 'Node export params.',
            'type' => 'string',
            'default value' => array(),
          ),
        ),
        'access callback' => 'valghalla_resource_export_service_resource_access',
        'access arguments' => array('create'),
        'access arguments append' => TRUE,
      ),
      // Deletes the queue item only that represents the the actual content (node or taxonomy_term).
      'delete' => array(
        'file' => array(
          'type' => 'inc',
          'module' => 'valghalla_resource_export_service',
          'name' => 'resources/valghalla_resource_export'
        ),
        'callback' => '_valghalla_resource_export_resource_delete',
        'args' => array(
          array(
            'name' => 'uuid',
            'optional' => FALSE,
            'source' => array('path' => 0),
            'type' => 'string',
          ),
        ),
        'access callback' => 'valghalla_resource_export_service_resource_access',//TODO: add custom permission
        'access arguments' => array('delete'),
        'access arguments append' => TRUE,
      ),
      // Indexes the queue items that represent the actual content (node or taxonomy_term).
      'index' => array(
        'file' => array('type' => 'inc', 'module' => 'valghalla_resource_export_service', 'name' => 'resources/valghalla_resource_export'),
        'help' => t('Return all Valghalla resources.'),
        'callback' => '_valghalla_resource_export_resource_index',
        'args' => array(
          array(
            'name' => 'page',
            'optional' => TRUE,
            'type' => 'int',
            'description' => 'The zero-based index of the page to get, defaults to 0.',
            'default value' => 0,
            'source' => array('param' => 'page'),
          ),
          array(
            'name' => 'fields',
            'optional' => TRUE,
            'type' => 'string',
            'description' => 'The fields to get.',
            'default value' => '*',
            'source' => array('param' => 'fields'),
          ),
          array(
            'name' => 'parameters',
            'optional' => TRUE,
            'type' => 'array',
            'description' => 'Parameters array',
            'default value' => array(),
            'source' => array('param' => 'parameters'),
          ),
          array(
            'name' => 'pagesize',
            'optional' => TRUE,
            'type' => 'int',
            'description' => 'Number of records to get per page.',
            'default value' => variable_get('services_node_index_page_size', 20),
            'source' => array('param' => 'pagesize'),
          ),
          array(
            'name' => 'options',
            'optional' => TRUE,
            'type' => 'array',
            'description' => 'Additional query options.',
            'default value' => array(),
            'source' => array('param' => 'options'),
          ),
        ),
        'access arguments' => array('access content'),//TODO: add custom permission
      ),
    ),
  );

  // Return the resources.
  return $resources;
}

/**
 * Creates or updates a node based on submitted values.
 *
 * Note that this function uses drupal_execute() to create new nodes,
 * which may require very specific formatting. The full implications of this
 * are beyond the scope of this comment block. The Googles are your friend.
 *
 * @param $params
 *   Array or params:
 *     $params['node_export_data'] = Node export data in string (any format).
 * @return
 *   An associative array contained the new node's nid and, if applicable,
 *   the fully qualified URI to this resource.
 *
 * @see node_export_import()
 */
function valghalla_resource_export_node_create($params) {
  module_load_include('inc', 'services', 'resources/node_resource');

  $nid = NULL;

  // Prepare and create/update a new node.
  $import = node_export_import($params['node_export_data']);

  if ($import['success']) {
    // We expect only one node to be imported.
    $nid  = reset($import['nids']);
  }

  // Return the node that was created.
  if ($nid) {
    $node = node_load($nid);
    // Remove the item from the queue, we don't want to be in the queue of pending changes.
    valghalla_synch_queue_remove_item($node->uuid);

    return _node_resource_retrieve($nid);
  } else {
    return $import['output'];
  }
}

/**
 * Delete a resource given its uuid.
 *
 * @param $uuid
 *   UUID of the resource we're deleting.
 * @return
 *   Boolean.
 */
function _valghalla_resource_export_resource_delete($uuid) {
  valghalla_synch_queue_remove_item($uuid);
  return TRUE;
}

/**
 * Return an array of optionally paged nids based on a set of criteria.
 *
 * An example request might look like
 *
 * http://domain/endpoint/node?fields=nid,vid&parameters[nid]=7&parameters[uid]=1
 *
 * This would return an array of objects with only nid and vid defined, where
 * nid = 7 and uid = 1.
 *
 * @param $page
 *   Page number of results to return (in pages of 20).
 * @param $fields
 *   The fields you want returned.
 * @param $parameters
 *   An array containing fields and values used to build a sql WHERE clause
 *   indicating items to retrieve.
 * @param $page_size
 *   Integer number of items to be returned.
 * @param $options
 *   Additional query options.
 * @return
 *   An array of node objects.
 *
 * @see _node_resource_index().
 */
function _valghalla_resource_export_resource_index($page, $fields, $parameters, $page_size, $options = array()) {
  // Nodes.
  $node_select = db_select('node', 't');
  $node_select = $node_select->addTag('node_access');

  // Adding connection to valghalla_external_server_synch_queue.
  $node_select->join('valghalla_synch_queue', 'queue', 'queue.target_id = t.nid');

  services_resource_build_index_query($node_select, $page, $fields, $parameters, $page_size, 'node', $options);

  if (!user_access('administer nodes')) {
    $node_select->condition('status', 1);
  }

  $results = services_resource_execute_index_query($node_select);
  $nodes = services_resource_build_index_list($results, 'node', 'nid');

  // Taxonomy terms.
  $taxonomy_select = db_select('taxonomy_term_data', 't');
  $taxonomy_select->join('taxonomy_term_hierarchy', 'tth', 't.tid = tth.tid');
  $taxonomy_select->fields('tth');

  // Adding connection to valghalla_external_server_synch_queue.
  $taxonomy_select->join('valghalla_synch_queue', 'queue', 'queue.target_id = t.tid');

  services_resource_build_index_query($taxonomy_select, $page, $fields, $parameters, $page_size, 'taxonomy_term', $options);
  $results = services_resource_execute_index_query($taxonomy_select);
  $terms = services_resource_build_index_list($results, 'taxonomy_term', 'tid');

  return array_merge($nodes, $terms);
}
