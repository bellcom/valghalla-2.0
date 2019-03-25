<?php

/**
 * @file
 * Cleanup script to remove data from db that can harm production environment.
 *
 * To run script call command: drush ev "include_once '../scripts/cleanup.php';"
 * from sites directory.
 *
 * To allow script do the cleanup add to your setting.php following line:
 * $conf['is_development_environment'] = TRUE;
 *
 * !!! ATTENTION: This script will delete volunteer nodes !!!
 */

if (!variable_get('is_development_environment')) {
  drupal_set_message('This script allowed to run only on development environment.');
  return;
}

// Removing volunteers.
$query = new EntityFieldQuery();
$res = $query->entityCondition('entity_type', 'node')->entityCondition('bundle', 'volunteers')->execute();
if (!empty($res['node'])) {
  node_delete_multiple(array_keys($res['node']));
}

// Resetting external server values.
variable_del('valghalla_external_server_endpoint');
variable_del('valghalla_external_server_hash_salt');
variable_del('valghalla_external_server_user');
variable_del('valghalla_external_server_password');

// Resetting eboks settings.
variable_del('valghalla_eboks_serviceagreementuuid');
variable_del('valghalla_eboks_wsdl');
variable_del('valghalla_eboks_useruuid');
variable_del('valghalla_eboks_sys_id');
variable_del('valghalla_eboks_materiale_id_dp');
variable_del('valghalla_eboks_materiale_id_nemsms');
variable_del('valghalla_eboks_certfile_passphrase');

// Resetting computopics settings.
variable_del('valghalla_sms_computopic_user');
variable_del('valghalla_sms_computopic_pass');
