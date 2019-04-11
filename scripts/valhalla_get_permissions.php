<?php

/**
 * @file
 * Script fetching permissions for specified roles.
 *
 * As result script generates csv files per role in specified directory.
 */

$script_dir = dirname(__FILE__) . DIRECTORY_SEPARATOR;

// Drupal root directory.
$drupal_root = realpath($script_dir . '../public_html');

// Report directory.
$report_dir = realpath($script_dir . '../role-permissions');

// List of Roles that should be checked.
$roles = array(
  'administrator' => 'administrator',
  'anonym bruger' => 'anonymous user',
  'godkendt bruger' => 'authenticated user',
  'Partisekretær' => 'Partisekretær',
  'Valgsekretær' => 'Valgsekretær',
);

$sites_dir = $drupal_root . DIRECTORY_SEPARATOR . 'sites';
if (!file_exists($report_dir)) {
  die("Report dir in not exist.\n");
}

// Scaning sites directory to get drupal instances.
$sites = array();
foreach (scandir($drupal_root . DIRECTORY_SEPARATOR . 'sites') as $path) {
  if (file_exists($sites_dir . DIRECTORY_SEPARATOR . $path . DIRECTORY_SEPARATOR . 'settings.php')) {
    $sites[] = $path;
  }
}

// Getting drush runtime path.
$res = execute('which drush');
$drush = end($res);

// SQL query that fetchs permissions.
// Query should get as response one-dimensional array.
$permissions_sql = "SELECT rp.permission FROM role LEFT JOIN role_permission AS rp ON role.rid = rp.rid WHERE role.name = '!role';";

// Fetching permissions.
$permissions = array();
$site_permissions = array();
foreach ($roles as $role_key => $role) {
  foreach ($sites as $site) {
    $res = drush_command('sql-query "' . str_replace('!role', $role, $permissions_sql) . '"', $site);
    if (empty($res)) {
      continue;
    }

    $permissions += $res;
    $site_permissions[$site][$role] = $res;
  }
}
ksort($permissions);

// Generating csv reports.
foreach ($roles as $role_key => $role) {
  $file_path = $report_dir . DIRECTORY_SEPARATOR . $role_key . '.csv';
  if (file_exists($file_path)) {
    unlink($file_path);
  }
  $file = fopen($file_path, 'w');
  fputcsv($file, array_merge(array("Permission\Host"), $sites));
  foreach ($permissions as $permission) {
    $row = array();
    foreach ($sites as $site) {
      if (!empty($site_permissions[$site][$role]) && in_array($permission, $site_permissions[$site][$role])) {
        $row[] = '1';
      }
      else {
        $row[] = '0';
      }
    }
    fputcsv($file, array_merge(array($permission), $row));
  }
  fclose($file);
}

/**
 * Execute wrapper function for drush.
 *
 * @param string $drush_command
 *   Drush command.
 * @param string $host
 *   Host name.
 *
 * @return mixed
 *   response data from execute function.
 */
function drush_command($drush_command, $host = 'default') {
  global $drush, $drupal_root;
  $command = $drush . ' --root=' . $drupal_root . ' --uri=http://' . $host . ' ' . $drush_command;
  return execute($command, $host);
}

/**
 * Execute wrapper function.
 *
 * @param string $command
 *   Command to execute.
 * @param string $host
 *   Host name.
 *
 * @return mixed
 *   Response from exec function or error string.
 */
function execute($command, $host = 'default') {
  exec($command, $op, $return_var);
  if ($return_var > 0) {
    echo 'ERROR ' . $host . ' ' . end($op) . "\n";
  }
  return $op;
}
