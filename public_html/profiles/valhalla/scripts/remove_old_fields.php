<?php
/**
 * @file
 * remove_old_fields.php
 *
 * This script should be run with `drush scr remove_old_fields`.
 * It removes fields no longer used for various contenttypes.
 */

// From roles nodes.
if ($instance = field_info_instance('node', 'field_diaet', 'roles')) {
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
