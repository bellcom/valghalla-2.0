<?php
/**
 * @file
 * valghalla_permissions.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function valghalla_permissions_user_default_roles() {
  $roles = array();

  // Exported role: Brevstemme administrator.
  $roles['Brevstemme administrator'] = array(
    'name' => 'Brevstemme administrator',
    'weight' => 5,
  );

  // Exported role: Partisekretær.
  $roles['Partisekretær'] = array(
    'name' => 'Partisekretær',
    'weight' => 3,
  );

  // Exported role: Valgsekretær.
  $roles['Valgsekretær'] = array(
    'name' => 'Valgsekretær',
    'weight' => 4,
  );

  // Exported role: admin.
  $roles['admin'] = array(
    'name' => 'admin',
    'weight' => 2,
  );

  return $roles;
}
