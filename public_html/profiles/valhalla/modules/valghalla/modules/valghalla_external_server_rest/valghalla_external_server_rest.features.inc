<?php

/**
 * @file
 * valghalla_external_server_rest.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function valghalla_external_server_rest_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "services" && $api == "services") {
    return array("version" => "3");
  }
}
