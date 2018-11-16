<?php
/**
 * @file
 * valghalla_polling_station.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function valghalla_polling_station_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_adresse|node|polling_station|form';
  $field_group->group_name = 'group_adresse';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'polling_station';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_valgsted';
  $field_group->data = array(
    'label' => 'Adresse',
    'weight' => '22',
    'children' => array(
      0 => 'field_address_city',
      1 => 'field_address_door',
      2 => 'field_address_floor',
      3 => 'field_address_road',
      4 => 'field_address_road_no',
      5 => 'field_address_zipcode',
      6 => 'field_address_road2',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'label' => 'Adresse',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-adresse field-group-htab',
        'description' => '',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_adresse|node|polling_station|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_andet|node|polling_station|form';
  $field_group->group_name = 'group_andet';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'polling_station';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_valgsted';
  $field_group->data = array(
    'label' => 'Andet',
    'weight' => '25',
    'children' => array(
      0 => 'field_digital_election_list',
      1 => 'field_venue_skolekode',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'label' => 'Andet',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-andet field-group-htab',
        'description' => '',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_andet|node|polling_station|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_kontakter|node|polling_station|form';
  $field_group->group_name = 'group_kontakter';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'polling_station';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_valgsted';
  $field_group->data = array(
    'label' => 'Kontaktpersoner',
    'weight' => '24',
    'children' => array(
      0 => 'field_contact',
      1 => 'field_venue_contact',
      2 => 'field_venue_contact_name',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'label' => 'Kontaktpersoner',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-kontakter field-group-htab',
        'description' => '',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_kontakter|node|polling_station|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ressourcer|node|polling_station|form';
  $field_group->group_name = 'group_ressourcer';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'polling_station';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_valgsted';
  $field_group->data = array(
    'label' => 'Ressourcer',
    'weight' => '23',
    'children' => array(
      0 => 'field_venue_team_members',
      1 => 'field_venue_teams',
      2 => 'field_venue_bespisning_1',
      3 => 'field_venue_bespisning_2',
      4 => 'field_venue_booth_sides',
      5 => 'field_venue_booths',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'label' => 'Ressourcer',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-ressourcer field-group-htab',
        'description' => '',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_ressourcer|node|polling_station|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_valgsteder|node|polling_station|form';
  $field_group->group_name = 'group_valgsteder';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'polling_station';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_valgsted';
  $field_group->data = array(
    'label' => 'Valgsted',
    'weight' => '20',
    'children' => array(
      0 => 'field_constituency',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'label' => 'Valgsted',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_valgsteder|node|polling_station|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_valgsted|node|polling_station|form';
  $field_group->group_name = 'group_valgsted';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'polling_station';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Valgsted',
    'weight' => '2',
    'children' => array(
      0 => 'group_adresse',
      1 => 'group_andet',
      2 => 'group_deltagere',
      3 => 'group_kontakter',
      4 => 'group_ressourcer',
      5 => 'group_valgsteder',
    ),
    'format_type' => 'htabs',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(
        'classes' => '',
        'id' => '',
      ),
    ),
  );
  $field_groups['group_valgsted|node|polling_station|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Adresse');
  t('Andet');
  t('Kontaktpersoner');
  t('Ressourcer');
  t('Valgsted');

  return $field_groups;
}
