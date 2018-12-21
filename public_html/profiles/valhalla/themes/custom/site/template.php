<?php

/**
 * @file
 * Main theme functionality.
 */

/**
 * Implements template_preprocess_html().
 */
function site_preprocess_html(&$variables) {
  $theme_path = path_to_theme();

  // Add javascript files.
  drupal_add_js($theme_path . '/dist/javascripts/modernizr.js',
    [
      'type' => 'file',
      'scope' => 'footer',
      'group' => JS_LIBRARY,
    ]);
  drupal_add_js($theme_path . '/dist/javascripts/app.js',
    [
      'type' => 'file',
      'scope' => 'footer',
      'group' => JS_THEME,
    ]);

  // Add fonts from Google fonts API.
  drupal_add_css('https://fonts.googleapis.com/css?family=Raleway:400,700',
    ['type' => 'external']);
}

/**
 * Implements hook_preprocess_page().
 */
function site_preprocess_page(&$variables) {
  $current_theme = variable_get('theme_default', 'none');
  $primary_navigation_name = variable_get('menu_main_links_source', 'main-menu');

  // Overriding the one set by mother theme, as we want to limit the
  // number of levels shown.
  $variables['theme_path'] = base_path() . drupal_get_path('theme', $current_theme);

  // Navigation.
  $variables['flexy_navigation__primary'] = _bellcom_generate_menu($primary_navigation_name, 'flexy_navigation', FALSE, 1);
  $variables['menu_slinky__main_menu'] = _bellcom_generate_menu('main-menu', 'slinky-custom', TRUE);

  // Tabs.
  $variables['tabs_primary'] = $variables['tabs'];
  $variables['tabs_secondary'] = $variables['tabs'];
  unset($variables['tabs_primary']['#secondary']);
  unset($variables['tabs_secondary']['#primary']);

  // Navigations.
  $variables['valghalla_participants']['navigation'] = valghalla_bs_theme_navbarmenu('valghalla/deltagere');
  $variables['valghalla_administration']['navigation'] = valghalla_bs_theme_navbarmenu('valghalla/administration');
  $variables['valghalla_lists']['navigation'] = valghalla_bs_theme_navbarmenu('valghalla_lists');
  $variables['admin_valghalla']['navigation'] = valghalla_bs_theme_navbarmenu('admin/valghalla');

  // Election party switcher.
  $variables['election_party_switcher'] = module_invoke('valghalla', 'block_view', 'election_party_switcher');
}

/**
 * Implements template_preprocess_node.
 */
function site_preprocess_node(&$variables) {
  $node = $variables['node'];

  // Optionally, run node-type-specific preprocess functions, like
  // foo_preprocess_node_page() or foo_preprocess_node_story().
  $function_node_type = __FUNCTION__ . '__' . $node->type;
  $function_view_mode = __FUNCTION__ . '__' . $variables['view_mode'];

  if (function_exists($function_node_type)) {
    $function_node_type($variables);
  }

  if (function_exists($function_view_mode)) {
    $function_view_mode($variables);
  }
}

/**
 * Implements template_preprocess_taxonomy_term().
 */
function site_preprocess_taxonomy_term(&$variables) {
  $term = $variables['term'];
  $view_mode = $variables['view_mode'];
  $vocabulary_machine_name = $variables['vocabulary_machine_name'];

  // Add taxonomy-term--view_mode.tpl.php suggestions.
  $variables['theme_hook_suggestions'][] = 'taxonomy_term__' . $view_mode;

  // Make "taxonomy-term--TERMTYPE--VIEWMODE.tpl.php" templates
  // available for terms.
  $variables['theme_hook_suggestions'][] = 'taxonomy_term__' . $vocabulary_machine_name . '__' . $view_mode;

  // Optionally, run node-type-specific preprocess functions,
  // like foo_preprocess_taxonomy_term_page()
  // or foo_preprocess_taxonomy_term_story().
  $function_taxonomy_term_type = __FUNCTION__ . '__' . $vocabulary_machine_name;
  $function_view_mode = __FUNCTION__ . '__' . $view_mode;

  if (function_exists($function_taxonomy_term_type)) {
    $function_taxonomy_term_type($variables);
  }

  if (function_exists($function_view_mode)) {
    $function_view_mode($variables);
  }
}

/**
 * Genereate navbar menu.
 */
function valghalla_bs_theme_navbarmenu($path) {
  $parent = menu_link_get_preferred($path);

  $parameters = array(
    'active_trail' => array($parent['plid']),
    'only_active_trail' => FALSE,
    'min_depth' => $parent['depth'] + 1,
    'max_depth' => $parent['depth'] + 1,
    'conditions' => array('plid' => $parent['mlid']),
  );

  $children = menu_build_tree($parent['menu_name'], $parameters);

  $tree_output = menu_tree_output($children);

  $items = array();

  foreach ($tree_output as $item_id => $item_data) {

    if (is_numeric($item_id) && is_array($item_data)) {
      $items[] = array(
        'class' => 'flexy-navigation__item__dropdown-menu__item',
        'data' => l($item_data['#title'], $item_data['#href'], array(
          'attributes' => $item_data['#attributes'],
          'html'       => TRUE,
        )
        ),
      );
    }
  }

  $menu = theme('item_list', array(
    'items' => $items,
    'type' => 'ul',
    'attributes' => array(
      'class' => 'flexy-navigation__item__dropdown-menu',
    ),
  ));

  $toggle = '<a href="#">' . $parent['link_title'] . '</a>';

  if ($menu) {
    return $toggle . $menu;
  }
}

/**
 * Last revision editor.
 */
function valhalla_bs_last_editor($node) {
  if (isset($node->revision_uid)) {
    $uid = $node->revision_uid;
  }
  else {
    $uid = $node->uid;
  }

  $account = user_load($uid);

  if (user_access('access user profiles')) {
    return l($account->name, 'user/' . $account->uid);
  }
  return $account->name;
}

/**
 * Helper function for generating content.
 */
function _theme_generate_mail($node) {
  if ($field = field_get_items('node', $node, 'field_email')) {
    return l($field[0]['email'], 'mailto:' . $field[0]['email']);
  }
  return '';
}

/**
 * Helper function for generating content.
 */
function _theme_generate_address($node) {
  $address = '';

  if ($field = field_get_items('node', $node, 'field_address_road')) {
    $address .= $field[0]['value'] . ' ';
  }

  if ($field = field_get_items('node', $node, 'field_address_road_no')) {
    $address .= $field[0]['value'] . ', ';
  }

  if ($field = field_get_items('node', $node, 'field_address_floor')) {
    $address .= $field[0]['value'] . ' ';
  }

  if ($field = field_get_items('node', $node, 'field_address_door')) {
    $address .= $field[0]['value'] . ', ';
  }

  if ($field = field_get_items('node', $node, 'field_address_zipcode')) {
    $address .= $field[0]['value'] . ' ';
  }

  if ($field = field_get_items('node', $node, 'field_address_city')) {
    $address .= $field[0]['value'];
  }

  return $address;
}

/**
 * Helper function for generating content.
 */
function _theme_generate_phone($node) {
  if ($field = field_get_items('node', $node, 'field_phone')) {
    return $field[0]['value'];
  }

  return '';
}

/**
 * Helper function for generating content.
 */
function _theme_generate_no_mail($node) {
  if ($field = field_get_items('node', $node, 'field_no_mail')) {
    if ($field[0]['value']) {
      return '<b>Deltageren er fritaget for digital post</b>';
    }
  }

  return '';
}

/**
 * Helper function for generating content.
 */
function _theme_generate_cpr($node) {
  if ($field = field_get_items('node', $node, 'field_cpr_number')) {
    $cpr = $field[0]['value'];
  }

  $age = _valghalla_helper_get_age_from_cpr($cpr);
  $age = ' (' . $age . ' år)';

  if (user_access('see all psn numbers')) {
    return $cpr . $age;
  }

  return substr($cpr, 0, 6) . $age;
}

/**
 * Helper function for generating content.
 */
function _theme_generate_election_info($node) {
  $output = '';

  if ($fields = field_get_items('node', $node, 'field_electioninfo')) {

    foreach ($fields as $data) {
      $fc = field_collection_item_load($data['value']);

      // Election.
      if ($field = field_get_items('field_collection_item', $fc, 'field_election')) {
        if ($field[0]['entity']) {
          $_node = $field[0]['entity'];
          $election = $_node->title;
        }
      }

      // Polling station.
      if ($field = field_get_items('field_collection_item', $fc, 'field_vlnt_station')) {
        if ($field[0]['entity']) {
          $_node = $field[0]['entity'];
          $polling_station = l($_node->title, 'volunteers/station/' . $_node->nid);
        }
      }

      // Post role.
      if ($field = field_get_items('field_collection_item', $fc, 'field_post_role')) {
        if ($field[0]['entity']) {
          $_node = $field[0]['entity'];
          $role_title = $_node->title;

          if ($field = field_get_items('node', $_node, 'field_description')) {
            $role_description = $field[0]['value'];
          }
        }
      }

      // Party.
      if ($field = field_get_items('field_collection_item', $fc, 'field_post_party')) {
        if ($field[0]['entity']) {
          $_term = $field[0]['entity'];
          $party = $_term->name;
        }
      }

      // Status.
      $rsvp = '';
      if ($field = field_get_items('field_collection_item', $fc, 'field_rsvp')) {
        $rsvp_map = array(
          0 => 'Ikke svaret',
          1 => 'Ja',
          2 => 'Nej',
          3 => 'Aldrig',
        );
        $rsvp = $rsvp_map[$field[0]['value']];
      }

      $rsvp_comment = '';
      if ($field = field_get_items('field_collection_item', $fc, 'field_rsvp_comment')) {
        $rsvp_comment = $field[0]['value'];
      }
      if ($field = field_get_items('field_collection_item', $fc, 'field_token')) {
        $rsvp_link = l(t('(skift status)'), 'volunteers/rsvp/' . $field[0]['value']);
      }

      $output .= '
        <h3>' . $election . '</h3>
        <table class="table">
          </tr>
            <td>Valgsted:</td>
            <td>' . $polling_station . '</td>
          </tr>
          </tr>
            <td>Rolle:</td>
            <td>' . $role_title . ' / ' . $role_description . '</td>
          </tr>
          </tr>
            <td>Parti:</td>
            <td>' . $party . '</td>
          </tr>
          </tr>
            <td>Status:</td>
            <td>' . $rsvp . ' ' . $rsvp_link . '</td>
          </tr>
          </tr>
            <td>Status kommentar:</td>
            <td><i>' . $rsvp_comment . '</i></td>
          </tr>
        </table>
        <br /><br />
        ';
    }
  }

  return $output;
}
