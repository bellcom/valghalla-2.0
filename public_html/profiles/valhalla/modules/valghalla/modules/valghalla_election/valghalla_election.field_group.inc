<?php

/**
 * @file
 * valghalla_election.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function valghalla_election_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_diaet|node|election|form';
  $field_group->group_name = 'group_diaet';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'election';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_election_tabs';
  $field_group->data = array(
    'label' => 'Diæt',
    'weight' => '8',
    'children' => array(),
    'format_type' => 'htab',
    'format_settings' => array(
      'label' => 'Diæt',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_diaet|node|election|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_election_tabs|node|election|form';
  $field_group->group_name = 'group_election_tabs';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'election';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Valg',
    'weight' => '5',
    'children' => array(
      0 => 'field_volunteers_pr_pol_st_party',
      1 => 'group_diaet',
      2 => 'group_general',
    ),
    'format_type' => 'htabs',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(
        'classes' => 'group-election-tabs field-group-htabs',
        'id' => '',
      ),
    ),
  );
  $field_groups['group_election_tabs|node|election|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_general|node|election|form';
  $field_group->group_name = 'group_general';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'election';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_election_tabs';
  $field_group->data = array(
    'label' => 'Generelt',
    'weight' => '6',
    'children' => array(
      0 => 'field_date',
      1 => 'field_election_mails_send',
      2 => 'field_election_status',
      3 => 'field_election_type',
      4 => 'field_polling_stations',
      5 => 'field_election_report_broadcast',
      6 => 'field_email_address',
      7 => 'title',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'label' => 'Generelt',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-general field-group-htab',
        'description' => '',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_general|node|election|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = TRUE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_settings|node|election|form';
  $field_group->group_name = 'group_settings';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'election';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_election_tabs';
  $field_group->data = array(
    'label' => 'Indstillinger',
    'weight' => '9',
    'children' => array(
      0 => 'field_election_report_broadcast',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-settings field-group-htab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_settings|node|election|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Diæt');
  t('Generelt');
  t('Indstillinger');
  t('Valg');

  return $field_groups;
}
