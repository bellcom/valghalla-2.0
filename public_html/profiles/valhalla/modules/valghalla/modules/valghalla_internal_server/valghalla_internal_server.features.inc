<?php
/**
 * @file
 * valghalla_internal_server.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function valghalla_internal_server_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "monolog" && $api == "monolog") {
    return array("version" => "1");
  }
}
