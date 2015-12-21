<?php
/**
 * @file
 * valghalla_user_tools.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function valghalla_user_tools_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: navigation_online-vejledning:http://valghalla.franz.bellcom.dk/
  $menu_links['navigation_online-vejledning:http://valghalla.franz.bellcom.dk/'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'http://valghalla.franz.bellcom.dk/',
    'router_path' => '',
    'link_title' => 'Online vejledning',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'navigation_online-vejledning:http://valghalla.franz.bellcom.dk/',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -42,
    'customized' => 1,
    'parent_identifier' => 'navigation_administration:valghalla/administration',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Online vejledning');


  return $menu_links;
}
