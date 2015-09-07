<?php
/**
 * @file
 * valghalla_polling_station.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function valghalla_polling_station_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'field_collection_item-field_volunteers_pr_party_1-field_party_list'
  $field_instances['field_collection_item-field_volunteers_pr_party_1-field_party_list'] = array(
    'bundle' => 'field_volunteers_pr_party_1',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'valhalla_field_party_volunteers_v3',
        'settings' => array(),
        'type' => 'party_volunteers_default_v3',
        'weight' => 4,
      ),
      'token' => array(
        'label' => 'inline',
        'module' => 'valhalla_field_party_volunteers_v3',
        'settings' => array(),
        'type' => 'party_volunteers_default_v3',
        'weight' => 4,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_party_list',
    'label' => 'Party',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'valhalla_field_party_volunteers_v3',
      'settings' => array(
        'available_parties' => array(),
      ),
      'type' => 'party_volunteers_standard_v3',
      'weight' => 0,
    ),
  );

  // Exported field_instance: 'field_collection_item-field_volunteers_pr_party_1-field_role_n2522'
  $field_instances['field_collection_item-field_volunteers_pr_party_1-field_role_n2522'] = array(
    'bundle' => 'field_volunteers_pr_party_1',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'valhalla_field_volunteers_roles',
        'settings' => array(),
        'type' => 'volunteers_roles_default',
        'weight' => 5,
      ),
      'token' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_role_n2522',
    'label' => 'Role',
    'required' => TRUE,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'valhalla_field_volunteers_roles',
      'settings' => array(),
      'type' => 'volunteers_roles_standart',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'field_collection_item-field_volunteers_pr_party_1-field_role_n2523'
  $field_instances['field_collection_item-field_volunteers_pr_party_1-field_role_n2523'] = array(
    'bundle' => 'field_volunteers_pr_party_1',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'valhalla_field_volunteers_roles',
        'settings' => array(),
        'type' => 'volunteers_roles_default',
        'weight' => 6,
      ),
      'token' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_role_n2523',
    'label' => 'Role',
    'required' => TRUE,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'valhalla_field_volunteers_roles',
      'settings' => array(),
      'type' => 'volunteers_roles_standart',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'field_collection_item-field_volunteers_pr_party_1-field_role_n2524'
  $field_instances['field_collection_item-field_volunteers_pr_party_1-field_role_n2524'] = array(
    'bundle' => 'field_volunteers_pr_party_1',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'valhalla_field_volunteers_roles',
        'settings' => array(),
        'type' => 'volunteers_roles_default',
        'weight' => 7,
      ),
      'token' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_role_n2524',
    'label' => 'Role',
    'required' => TRUE,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'valhalla_field_volunteers_roles',
      'settings' => array(),
      'type' => 'volunteers_roles_standart',
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'field_collection_item-field_volunteers_pr_party_1-field_role_n2525'
  $field_instances['field_collection_item-field_volunteers_pr_party_1-field_role_n2525'] = array(
    'bundle' => 'field_volunteers_pr_party_1',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'valhalla_field_volunteers_roles',
        'settings' => array(),
        'type' => 'volunteers_roles_default',
        'weight' => 8,
      ),
      'token' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_role_n2525',
    'label' => 'Role',
    'required' => TRUE,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'valhalla_field_volunteers_roles',
      'settings' => array(),
      'type' => 'volunteers_roles_standart',
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'field_collection_item-field_volunteers_pr_party_1-field_role_n2526'
  $field_instances['field_collection_item-field_volunteers_pr_party_1-field_role_n2526'] = array(
    'bundle' => 'field_volunteers_pr_party_1',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'valhalla_field_volunteers_roles',
        'settings' => array(),
        'type' => 'volunteers_roles_default',
        'weight' => 9,
      ),
      'token' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_role_n2526',
    'label' => 'Role',
    'required' => TRUE,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'valhalla_field_volunteers_roles',
      'settings' => array(),
      'type' => 'volunteers_roles_standart',
      'weight' => 5,
    ),
  );

  // Exported field_instance: 'field_collection_item-field_volunteers_pr_party_1-field_role_n2527'
  $field_instances['field_collection_item-field_volunteers_pr_party_1-field_role_n2527'] = array(
    'bundle' => 'field_volunteers_pr_party_1',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'valhalla_field_volunteers_roles',
        'settings' => array(),
        'type' => 'volunteers_roles_default',
        'weight' => 10,
      ),
      'token' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_role_n2527',
    'label' => 'Role',
    'required' => TRUE,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'valhalla_field_volunteers_roles',
      'settings' => array(),
      'type' => 'volunteers_roles_standart',
      'weight' => 6,
    ),
  );

  // Exported field_instance: 'field_collection_item-field_volunteers_pr_party_1-field_role_n2528'
  $field_instances['field_collection_item-field_volunteers_pr_party_1-field_role_n2528'] = array(
    'bundle' => 'field_volunteers_pr_party_1',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'valhalla_field_volunteers_roles',
        'settings' => array(),
        'type' => 'volunteers_roles_default',
        'weight' => 11,
      ),
      'token' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_role_n2528',
    'label' => 'Role',
    'required' => TRUE,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'valhalla_field_volunteers_roles',
      'settings' => array(),
      'type' => 'volunteers_roles_standart',
      'weight' => 7,
    ),
  );

  // Exported field_instance: 'field_collection_item-field_volunteers_pr_party_1-field_role_n2529'
  $field_instances['field_collection_item-field_volunteers_pr_party_1-field_role_n2529'] = array(
    'bundle' => 'field_volunteers_pr_party_1',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'valhalla_field_volunteers_roles',
        'settings' => array(),
        'type' => 'volunteers_roles_default',
        'weight' => 12,
      ),
      'token' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_role_n2529',
    'label' => 'Role',
    'required' => TRUE,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'valhalla_field_volunteers_roles',
      'settings' => array(),
      'type' => 'volunteers_roles_standart',
      'weight' => 8,
    ),
  );

  // Exported field_instance: 'field_collection_item-field_volunteers_pr_party_1-field_role_n2530'
  $field_instances['field_collection_item-field_volunteers_pr_party_1-field_role_n2530'] = array(
    'bundle' => 'field_volunteers_pr_party_1',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'valhalla_field_volunteers_roles',
        'settings' => array(),
        'type' => 'volunteers_roles_default',
        'weight' => 13,
      ),
      'token' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_role_n2530',
    'label' => 'Role',
    'required' => TRUE,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'valhalla_field_volunteers_roles',
      'settings' => array(),
      'type' => 'volunteers_roles_standart',
      'weight' => 9,
    ),
  );

  // Exported field_instance: 'node-polling_station-field_address_city'
  $field_instances['node-polling_station-field_address_city'] = array(
    'bundle' => 'polling_station',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_plain',
        'weight' => 17,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_address_city',
    'label' => 'By',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 23,
    ),
  );

  // Exported field_instance: 'node-polling_station-field_address_door'
  $field_instances['node-polling_station-field_address_door'] = array(
    'bundle' => 'polling_station',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_plain',
        'weight' => 18,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_address_door',
    'label' => 'Dør / Side',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 21,
    ),
  );

  // Exported field_instance: 'node-polling_station-field_address_floor'
  $field_instances['node-polling_station-field_address_floor'] = array(
    'bundle' => 'polling_station',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_plain',
        'weight' => 19,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_address_floor',
    'label' => 'Sal',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 20,
    ),
  );

  // Exported field_instance: 'node-polling_station-field_address_road'
  $field_instances['node-polling_station-field_address_road'] = array(
    'bundle' => 'polling_station',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_plain',
        'weight' => 20,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_address_road',
    'label' => 'Vej',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 18,
    ),
  );

  // Exported field_instance: 'node-polling_station-field_address_road2'
  $field_instances['node-polling_station-field_address_road2'] = array(
    'bundle' => 'polling_station',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 33,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_address_road2',
    'label' => 'Sted',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 17,
    ),
  );

  // Exported field_instance: 'node-polling_station-field_address_road_no'
  $field_instances['node-polling_station-field_address_road_no'] = array(
    'bundle' => 'polling_station',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_plain',
        'weight' => 21,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_address_road_no',
    'label' => 'Nummer',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 10,
      ),
      'type' => 'text_textfield',
      'weight' => 19,
    ),
  );

  // Exported field_instance: 'node-polling_station-field_address_zipcode'
  $field_instances['node-polling_station-field_address_zipcode'] = array(
    'bundle' => 'polling_station',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'number',
        'settings' => array(),
        'type' => 'number_unformatted',
        'weight' => 22,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_address_zipcode',
    'label' => 'Postnummer',
    'required' => 0,
    'settings' => array(
      'max' => 9999,
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 22,
    ),
  );

  // Exported field_instance: 'node-polling_station-field_constituency'
  $field_instances['node-polling_station-field_constituency'] = array(
    'bundle' => 'polling_station',
    'default_value' => array(
      0 => array(
        'nid' => 9,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'node_reference',
        'settings' => array(),
        'type' => 'node_reference_plain',
        'weight' => 8,
      ),
      'teaser' => array(
        'label' => 'inline',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_constituency',
    'label' => 'Valgkreds',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'node-polling_station-field_contact'
  $field_instances['node-polling_station-field_contact'] = array(
    'bundle' => 'polling_station',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Kontaktperson for valgets afvilking på selve valgdagen(e). Kan benyttes som flettefelt i mailskabeloner.',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_plain',
        'weight' => 5,
      ),
      'teaser' => array(
        'label' => 'inline',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_contact',
    'label' => 'Valgkontakt',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 15,
    ),
  );

  // Exported field_instance: 'node-polling_station-field_digital_election_list'
  $field_instances['node-polling_station-field_digital_election_list'] = array(
    'bundle' => 'polling_station',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 25,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_digital_election_list',
    'label' => 'Digital valgliste',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 1,
      ),
      'type' => 'options_onoff',
      'weight' => 8,
    ),
  );

  // Exported field_instance: 'node-polling_station-field_interntal_name'
  $field_instances['node-polling_station-field_interntal_name'] = array(
    'bundle' => 'polling_station',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 36,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_interntal_name',
    'label' => 'Internt navn',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'node-polling_station-field_role_weight'
  $field_instances['node-polling_station-field_role_weight'] = array(
    'bundle' => 'polling_station',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 18,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_role_weight',
    'label' => 'Valgsted Rækkefølge',
    'required' => FALSE,
    'settings' => array(
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'node-polling_station-field_venue_bespisning_1'
  $field_instances['node-polling_station-field_venue_bespisning_1'] = array(
    'bundle' => 'polling_station',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 2,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_decimal',
        'weight' => 31,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_venue_bespisning_1',
    'label' => 'Bespisning 1',
    'required' => 0,
    'settings' => array(
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 15,
    ),
  );

  // Exported field_instance: 'node-polling_station-field_venue_bespisning_2'
  $field_instances['node-polling_station-field_venue_bespisning_2'] = array(
    'bundle' => 'polling_station',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 2,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_decimal',
        'weight' => 32,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_venue_bespisning_2',
    'label' => 'Bespisning 2',
    'required' => 0,
    'settings' => array(
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 16,
    ),
  );

  // Exported field_instance: 'node-polling_station-field_venue_booth_sides'
  $field_instances['node-polling_station-field_venue_booth_sides'] = array(
    'bundle' => 'polling_station',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 2,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_decimal',
        'weight' => 35,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_venue_booth_sides',
    'label' => 'Stemmeboks sider',
    'required' => 0,
    'settings' => array(
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 14,
    ),
  );

  // Exported field_instance: 'node-polling_station-field_venue_booths'
  $field_instances['node-polling_station-field_venue_booths'] = array(
    'bundle' => 'polling_station',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 2,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_decimal',
        'weight' => 34,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_venue_booths',
    'label' => 'Stemmebokse',
    'required' => 0,
    'settings' => array(
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 13,
    ),
  );

  // Exported field_instance: 'node-polling_station-field_venue_contact'
  $field_instances['node-polling_station-field_venue_contact'] = array(
    'bundle' => 'polling_station',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_plain',
        'weight' => 7,
      ),
      'teaser' => array(
        'label' => 'inline',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_venue_contact',
    'label' => 'Andre kontaktoplysninger',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 17,
    ),
  );

  // Exported field_instance: 'node-polling_station-field_venue_contact_name'
  $field_instances['node-polling_station-field_venue_contact_name'] = array(
    'bundle' => 'polling_station',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_plain',
        'weight' => 6,
      ),
      'teaser' => array(
        'label' => 'inline',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_venue_contact_name',
    'label' => 'Lokalekontakt',
    'required' => 1,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 16,
    ),
  );

  // Exported field_instance: 'node-polling_station-field_venue_skolekode'
  $field_instances['node-polling_station-field_venue_skolekode'] = array(
    'bundle' => 'polling_station',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_plain',
        'weight' => 23,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_venue_skolekode',
    'label' => 'Skolekode',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 7,
    ),
  );

  // Exported field_instance: 'node-polling_station-field_venue_team_members'
  $field_instances['node-polling_station-field_venue_team_members'] = array(
    'bundle' => 'polling_station',
    'default_value' => array(
      0 => array(
        'value' => 5,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'number',
        'settings' => array(),
        'type' => 'number_unformatted',
        'weight' => 13,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_venue_team_members',
    'label' => 'Pladser per bord',
    'required' => 0,
    'settings' => array(
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 12,
    ),
  );

  // Exported field_instance: 'node-polling_station-field_venue_teams'
  $field_instances['node-polling_station-field_venue_teams'] = array(
    'bundle' => 'polling_station',
    'default_value' => array(
      0 => array(
        'value' => 5,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'number',
        'settings' => array(),
        'type' => 'number_unformatted',
        'weight' => 12,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_venue_teams',
    'label' => 'Borde',
    'required' => 0,
    'settings' => array(
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 11,
    ),
  );

  // Exported field_instance: 'node-polling_station-field_volunteers_pr_party_1'
  $field_instances['node-polling_station-field_volunteers_pr_party_1'] = array(
    'bundle' => 'polling_station',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'field_collection',
        'settings' => array(
          'add' => 'Add',
          'delete' => 'Delete',
          'description' => TRUE,
          'edit' => 'Edit',
          'view_mode' => 'full',
        ),
        'type' => 'field_collection_view',
        'weight' => 24,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_volunteers_pr_party_1',
    'label' => 'Deltagere pr. parti',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'field_collection',
      'settings' => array(),
      'type' => 'field_collection_embed',
      'weight' => 4,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Andre kontaktoplysninger');
  t('Bespisning 1');
  t('Bespisning 2');
  t('Borde');
  t('By');
  t('Digital valgliste');
  t('Dør / Side');
  t('Deltagere pr. parti');
  t('Internt navn');
  t('Kontaktperson for valgets afvilking på selve valgdagen(e). Kan benyttes som flettefelt i mailskabeloner.');
  t('Lokalekontakt');
  t('Nummer');
  t('Party');
  t('Pladser per bord');
  t('Postnummer');
  t('Role');
  t('Sal');
  t('Skolekode');
  t('Sted');
  t('Stemmeboks sider');
  t('Stemmebokse');
  t('Valgkontakt');
  t('Valgkreds');
  t('Valgsted Rækkefølge');
  t('Vej');

  return $field_instances;
}
