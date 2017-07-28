<?php
/**
 * @file
 * valghalla_tfa.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function valghalla_tfa_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'setup own tfa'.
  $permissions['setup own tfa'] = array(
    'name' => 'setup own tfa',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'tfa_basic',
  );

  return $permissions;
}
