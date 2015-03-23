<?php
/**
 * @file
 * remove_old_fields.php
 *
 * This script should be run with `drush scr remove_old_fields`.
 * It removes fields no longer used for various contenttypes.
 */

// From polling_station nodes.
if ($instance = field_info_instance('node', 'field_party', 'polling_station')) {
  field_delete_instance($instance);
}

if ($instance = field_info_instance('node', 'field_chairman', 'polling_station')) {
  field_delete_instance($instance);
}

if ($instance = field_info_instance('node', 'field_volunteers_pr_party', 'polling_station')) {
  field_delete_instance($instance);
}

if ($group = field_group_load_field_group('group_parties', 'node', 'polling_station', 'form')) {
  ctools_include('export');
  field_group_group_export_delete($group, FALSE);
}

if ($group = field_group_load_field_group('group_address', 'node', 'polling_station', 'form')) {
  ctools_include('export');
  field_group_group_export_delete($group, FALSE);
}

// From election nodes.
if ($instance = field_info_instance('node', 'body', 'election')) {
  field_delete_instance($instance);
}

// From constituency nodes.
if ($instance = field_info_instance('node', 'field_ansvarlig', 'constituency')) {
  field_delete_instance($instance);
}

if ($instance = field_info_instance('node', 'field_secretary', 'constituency')) {
  field_delete_instance($instance);
}

// From roles nodes.
if ($instance = field_info_instance('node', 'field_diaet', 'roles')) {
  field_delete_instance($instance);
}

if ($instance = field_info_instance('node', 'field_invitation', 'roles')) {
  field_delete_instance($instance);
}

if ($instance = field_info_instance('node', 'field_reminder', 'roles')) {
  field_delete_instance($instance);
}

if ($instance = field_info_instance('node', 'field_rsvp_yes', 'roles')) {
  field_delete_instance($instance);
}

if ($instance = field_info_instance('node', 'field_rsvp_no', 'roles')) {
  field_delete_instance($instance);
}

if ($instance = field_info_instance('node', 'field_rsvp_never', 'roles')) {
  field_delete_instance($instance);
}

// From volutneer nodes.
if ($instance = field_info_instance('node', 'field_token', 'volunteers')) {
  field_delete_instance($instance);
}

if ($instance = field_info_instance('node', 'field_rsvp', 'volunteers')) {
  field_delete_instance($instance);
}

if ($instance = field_info_instance('node', 'field_rsvp_comment', 'volunteers')) {
  field_delete_instance($instance);
}
