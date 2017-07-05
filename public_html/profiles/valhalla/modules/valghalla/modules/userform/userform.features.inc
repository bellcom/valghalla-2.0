<?php
/**
 * @file
 * userform.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function userform_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  if ($module == "rel" && $api == "rel") {
    return array("version" => "1");
  }
}
