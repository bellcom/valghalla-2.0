<?php
/**
 * @file
 * valghalla_gdpr_dump.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function valghalla_gdpr_dump_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
