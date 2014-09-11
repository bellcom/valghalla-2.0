<?php
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
