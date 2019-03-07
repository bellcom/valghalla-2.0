<?php

/**
 * @file
 * Block add_volunteer_to_polling_station section.
 */

/**
 * All volunteers to pooling stationg form.
 */
function valhalla_add_volunteer_to_polling_station_form($form, &$form_state) {
  global $user, $language;

  $roles = array_flip($user->roles);

  $select = db_select('field_data_field_cpr_number', 'cn');
  $select->condition('cn.bundle', 'volunteers');
  $select->fields('cn', array('entity_id'));

  $postfix_party = FALSE;
  if (isset($roles['Partisekretær'])) {
    $user = user_load($user->uid);
    if (isset($user->field_party[$language->language][0]['tid'])) {
      $party_id = $user->field_party[$language->language][0]['tid'];
      $select->join('field_data_field_party', 'p', 'p.entity_id = cn.entity_id');
      $select->condition('p.field_party_tid', $party_id);
    }
  }
  elseif (isset($roles['Valgsekretær']) || isset($roles['administrator'])) {
    $postfix_party = TRUE;
  }

  $volunteer_node_ids = $select
    ->execute()
    ->fetchAll(PDO::FETCH_COLUMN);

  $volunteer_options = array(0 => t('Select'));
  $in_use = array();
  foreach (node_load_multiple($volunteer_node_ids, array(), TRUE) as $node) {
    $title = $node->title;
    if ($postfix_party && isset($node->field_party[$language->language][0]['tid'])) {
      $term = taxonomy_term_load($node->field_party[$language->language][0]['tid']);
      $title .= ' (' . $term->name . ')';
    }

    $volunteer_options[$node->nid] = $title;

    if (isset($node->field_polling_station[$language->language][0]['nid'])) {
      $in_use[$node->field_polling_station[$language->language][0]['nid']][$node->nid] = TRUE;
    }
  }
  $form = array();

  $constituencies = entity_load('node', FALSE, array('type' => 'constituency'));
  foreach ($constituencies as $constituency) {

    $select = db_select('node', 'n')
      ->fields('n', array('nid'))
      ->condition('n.type', 'polling_station')
      ->condition('n.status', 1)
      ->orderBy('n.title');
    $select->join('field_data_field_constituency', 'c', 'n.nid = c.entity_id');
    $select->condition('c.bundle', 'polling_station');
    $select->condition('c.field_constituency_nid', $constituency->nid);

    $polling_station_ids = $select
      ->execute()
      ->fetchAll(PDO::FETCH_COLUMN);

    $form['constituency_' . $constituency->nid] = array(
      '#type' => 'fieldset',
      '#title' => $constituency->title,
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    foreach (node_load_multiple($polling_station_ids, array(), TRUE) as $polling_station) {
      $form['constituency_' . $constituency->nid]['polling_station_' . $polling_station->nid] = array(
        '#type' => 'fieldset',
        '#tree' => TRUE,
        '#collapsible' => FALSE,
        '#title' => $polling_station->title,
      );
    }
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Opdatér'),
  );

  return $form;
}

/**
 * Submit handler for valhalla_add_volunteer_to_polling_station_form.
 */
function valhalla_add_volunteer_to_polling_station_form_submit($form, &$form_state) {
  global $language;

  foreach ($form_state['values'] as $field => $data) {
    if (substr($field, 0, 16) == 'polling_station_' && substr_count($field, '_') == 2) {
      $polling_station_id = array_pop(explode('_', $field));

      foreach ($data as $volunteer_id) {
        if ($volunteer_id > 0) {
          $node = node_load($volunteer_id);
          $node->field_polling_station[$language->language][0]['nid'] = $polling_station_id;
          node_save($node);

          $volunteers[$polling_station_id][] = $volunteer_id;
        }
      }
    }
  }

  foreach ($form_state['values'] as $field => $data) {
    if (substr($field, 0, 27) == 'polling_station_volunteers_') {
      $polling_station_id = array_pop(explode('_', $field));
      $polling_station_volunteers = explode(',', $data);

      $array = empty($volunteers[$polling_station_id]) ? array() : $volunteers[$polling_station_id];
      $diff = array_diff($polling_station_volunteers, $array);

      if ($diff) {
        foreach (node_load_multiple($diff, array(), TRUE) as $node) {
          $node->field_polling_station = array();
          node_save($node);
        }
      }
    }
  }

  drupal_set_message(t('Skemaet er nu opdateret.'));
}
