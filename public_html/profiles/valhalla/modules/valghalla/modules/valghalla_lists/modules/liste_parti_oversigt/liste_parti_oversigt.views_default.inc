<?php

/**
 * @file
 * liste_parti_oversigt.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function liste_parti_oversigt_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'partioversigt';
  $view->description = '';
  $view->tag = 'valghalla, list';
  $view->base_table = 'node';
  $view->human_name = 'Liste partioversigt';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'mere';
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Udfør';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Gendan';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Sortér efter';
  $handler->display->display_options['exposed_form']['options']['sort_asc_label'] = 'Stigende';
  $handler->display->display_options['exposed_form']['options']['sort_desc_label'] = 'Faldende';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'nid' => 'nid',
    'title' => 'title',
    'field_cpr_number' => 'field_cpr_number',
    'entity_id_6' => 'entity_id_6',
    'entity_id' => 'entity_id',
    'entity_id_1' => 'entity_id_1',
    'entity_id_2' => 'entity_id_2',
    'entity_id_3' => 'entity_id_3',
    'entity_id_4' => 'entity_id_4',
    'entity_id_5' => 'entity_id_5',
    'entity_id_7' => 'entity_id_7',
    'entity_id_8' => 'entity_id_8',
    'entity_id_9' => 'entity_id_9',
    'nothing' => 'nothing',
    'nothing_1' => 'nothing_1',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'nid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_cpr_number' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'entity_id_6' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'entity_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'entity_id_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'entity_id_2' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'entity_id_3' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'entity_id_4' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'entity_id_5' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'entity_id_7' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'entity_id_8' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'entity_id_9' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nothing' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nothing_1' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Forbindelse: Indhold: Taksonomitermer på node */
  $handler->display->display_options['relationships']['term_node_tid']['id'] = 'term_node_tid';
  $handler->display->display_options['relationships']['term_node_tid']['table'] = 'node';
  $handler->display->display_options['relationships']['term_node_tid']['field'] = 'term_node_tid';
  /* Forbindelse: Indhold: Valginfo (field_electioninfo) */
  $handler->display->display_options['relationships']['field_electioninfo_value']['id'] = 'field_electioninfo_value';
  $handler->display->display_options['relationships']['field_electioninfo_value']['table'] = 'field_data_field_electioninfo';
  $handler->display->display_options['relationships']['field_electioninfo_value']['field'] = 'field_electioninfo_value';
  $handler->display->display_options['relationships']['field_electioninfo_value']['delta'] = '-1';
  /* Felt: Indhold: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['link_to_node'] = TRUE;
  /* Felt: Indhold: Titel */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Navn';
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Felt: Indhold: CPR Nummer */
  $handler->display->display_options['fields']['field_cpr_number']['id'] = 'field_cpr_number';
  $handler->display->display_options['fields']['field_cpr_number']['table'] = 'field_data_field_cpr_number';
  $handler->display->display_options['fields']['field_cpr_number']['field'] = 'field_cpr_number';
  $handler->display->display_options['fields']['field_cpr_number']['label'] = 'CPR nummer';
  $handler->display->display_options['fields']['field_cpr_number']['exclude'] = TRUE;
  /* Felt: Felt: Parti */
  $handler->display->display_options['fields']['entity_id_6']['id'] = 'entity_id_6';
  $handler->display->display_options['fields']['entity_id_6']['table'] = 'field_data_field_party';
  $handler->display->display_options['fields']['entity_id_6']['field'] = 'field_party';
  $handler->display->display_options['fields']['entity_id_6']['element_type'] = '0';
  $handler->display->display_options['fields']['entity_id_6']['element_label_type'] = '0';
  $handler->display->display_options['fields']['entity_id_6']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['entity_id_6']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['entity_id_6']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['entity_id_6']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['entity_id_6']['type'] = 'taxonomy_term_reference_plain';
  /* Felt: Indhold: By */
  $handler->display->display_options['fields']['entity_id']['id'] = 'entity_id';
  $handler->display->display_options['fields']['entity_id']['table'] = 'field_data_field_address_city';
  $handler->display->display_options['fields']['entity_id']['field'] = 'field_address_city';
  $handler->display->display_options['fields']['entity_id']['label'] = 'field_address_door';
  $handler->display->display_options['fields']['entity_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['entity_id']['hide_empty'] = TRUE;
  /* Felt: Indhold: Dør / Side */
  $handler->display->display_options['fields']['entity_id_1']['id'] = 'entity_id_1';
  $handler->display->display_options['fields']['entity_id_1']['table'] = 'field_data_field_address_door';
  $handler->display->display_options['fields']['entity_id_1']['field'] = 'field_address_door';
  $handler->display->display_options['fields']['entity_id_1']['label'] = 'field_address_door';
  $handler->display->display_options['fields']['entity_id_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['entity_id_1']['hide_empty'] = TRUE;
  /* Felt: Indhold: Sal */
  $handler->display->display_options['fields']['entity_id_2']['id'] = 'entity_id_2';
  $handler->display->display_options['fields']['entity_id_2']['table'] = 'field_data_field_address_floor';
  $handler->display->display_options['fields']['entity_id_2']['field'] = 'field_address_floor';
  $handler->display->display_options['fields']['entity_id_2']['label'] = 'field_address_floor';
  $handler->display->display_options['fields']['entity_id_2']['exclude'] = TRUE;
  $handler->display->display_options['fields']['entity_id_2']['hide_empty'] = TRUE;
  /* Felt: Indhold: Vej */
  $handler->display->display_options['fields']['entity_id_3']['id'] = 'entity_id_3';
  $handler->display->display_options['fields']['entity_id_3']['table'] = 'field_data_field_address_road';
  $handler->display->display_options['fields']['entity_id_3']['field'] = 'field_address_road';
  $handler->display->display_options['fields']['entity_id_3']['label'] = 'field_address_road';
  $handler->display->display_options['fields']['entity_id_3']['exclude'] = TRUE;
  $handler->display->display_options['fields']['entity_id_3']['hide_empty'] = TRUE;
  /* Felt: Indhold: Nummer */
  $handler->display->display_options['fields']['entity_id_4']['id'] = 'entity_id_4';
  $handler->display->display_options['fields']['entity_id_4']['table'] = 'field_data_field_address_road_no';
  $handler->display->display_options['fields']['entity_id_4']['field'] = 'field_address_road_no';
  $handler->display->display_options['fields']['entity_id_4']['label'] = 'field_address_road_no';
  $handler->display->display_options['fields']['entity_id_4']['exclude'] = TRUE;
  $handler->display->display_options['fields']['entity_id_4']['hide_empty'] = TRUE;
  /* Felt: Indhold: Postnummer */
  $handler->display->display_options['fields']['entity_id_5']['id'] = 'entity_id_5';
  $handler->display->display_options['fields']['entity_id_5']['table'] = 'field_data_field_address_zipcode';
  $handler->display->display_options['fields']['entity_id_5']['field'] = 'field_address_zipcode';
  $handler->display->display_options['fields']['entity_id_5']['label'] = 'field_address_zipcode';
  $handler->display->display_options['fields']['entity_id_5']['exclude'] = TRUE;
  $handler->display->display_options['fields']['entity_id_5']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['entity_id_5']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 1,
  );
  /* Felt: Indhold: Telefon */
  $handler->display->display_options['fields']['entity_id_7']['id'] = 'entity_id_7';
  $handler->display->display_options['fields']['entity_id_7']['table'] = 'field_data_field_phone';
  $handler->display->display_options['fields']['entity_id_7']['field'] = 'field_phone';
  $handler->display->display_options['fields']['entity_id_7']['exclude'] = TRUE;
  $handler->display->display_options['fields']['entity_id_7']['element_type'] = '0';
  $handler->display->display_options['fields']['entity_id_7']['element_label_type'] = 'span';
  $handler->display->display_options['fields']['entity_id_7']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['entity_id_7']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['entity_id_7']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['entity_id_7']['type'] = 'text_plain';
  /* Felt: Indhold: Telefon 2 */
  $handler->display->display_options['fields']['entity_id_8']['id'] = 'entity_id_8';
  $handler->display->display_options['fields']['entity_id_8']['table'] = 'field_data_field_phone2';
  $handler->display->display_options['fields']['entity_id_8']['field'] = 'field_phone2';
  $handler->display->display_options['fields']['entity_id_8']['exclude'] = TRUE;
  $handler->display->display_options['fields']['entity_id_8']['hide_empty'] = TRUE;
  /* Felt: Felt: Valgsted */
  $handler->display->display_options['fields']['entity_id_9']['id'] = 'entity_id_9';
  $handler->display->display_options['fields']['entity_id_9']['table'] = 'field_data_field_polling_station';
  $handler->display->display_options['fields']['entity_id_9']['field'] = 'field_polling_station';
  $handler->display->display_options['fields']['entity_id_9']['label'] = 'valgsted';
  $handler->display->display_options['fields']['entity_id_9']['exclude'] = TRUE;
  $handler->display->display_options['fields']['entity_id_9']['element_type'] = 'span';
  $handler->display->display_options['fields']['entity_id_9']['element_label_type'] = 'span';
  $handler->display->display_options['fields']['entity_id_9']['element_wrapper_type'] = 'span';
  $handler->display->display_options['fields']['entity_id_9']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['entity_id_9']['type'] = 'node_reference_plain';
  /* Felt: Global: Tilpasset tekst */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<div>
<h4>[title] ([entity_id_6] )</h4>
<div>[entity_id_3] [entity_id_4] [entity_id_2] [entity_id_1]<br />
</div>
</div>';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
  /* Felt: Global: Tilpasset tekst */
  $handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
  $handler->display->display_options['fields']['nothing_1']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_1']['label'] = 'Kvittering';
  /* Sorteringskriterie: Field collection item: Status (field_rsvp) */
  $handler->display->display_options['sorts']['field_rsvp_value']['id'] = 'field_rsvp_value';
  $handler->display->display_options['sorts']['field_rsvp_value']['table'] = 'field_data_field_rsvp';
  $handler->display->display_options['sorts']['field_rsvp_value']['field'] = 'field_rsvp_value';
  $handler->display->display_options['sorts']['field_rsvp_value']['relationship'] = 'field_electioninfo_value';
  /* Sorteringskriterie: Ord i ordforråd: Navn */
  $handler->display->display_options['sorts']['name']['id'] = 'name';
  $handler->display->display_options['sorts']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['sorts']['name']['field'] = 'name';
  $handler->display->display_options['sorts']['name']['relationship'] = 'term_node_tid';
  /* Sorteringskriterie: Indhold: Titel */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  /* Kontekstuelt filter: Felt: Valgsted (field_polling_station) */
  $handler->display->display_options['arguments']['field_polling_station_nid']['id'] = 'field_polling_station_nid';
  $handler->display->display_options['arguments']['field_polling_station_nid']['table'] = 'field_data_field_polling_station';
  $handler->display->display_options['arguments']['field_polling_station_nid']['field'] = 'field_polling_station_nid';
  $handler->display->display_options['arguments']['field_polling_station_nid']['exception']['title'] = 'Alle';
  $handler->display->display_options['arguments']['field_polling_station_nid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_polling_station_nid']['summary']['format'] = 'default_summary';
  /* Filterkriterie: Indhold: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'volunteers' => 'volunteers',
  );
  $handler->display->display_options['filters']['type']['group'] = '0';
  /* Filterkriterie: Field collection item: Valgsted (field_vlnt_station) */
  $handler->display->display_options['filters']['field_vlnt_station_target_id']['id'] = 'field_vlnt_station_target_id';
  $handler->display->display_options['filters']['field_vlnt_station_target_id']['table'] = 'field_data_field_vlnt_station';
  $handler->display->display_options['filters']['field_vlnt_station_target_id']['field'] = 'field_vlnt_station_target_id';
  $handler->display->display_options['filters']['field_vlnt_station_target_id']['relationship'] = 'field_electioninfo_value';
  $handler->display->display_options['filters']['field_vlnt_station_target_id']['operator'] = '>=';
  $handler->display->display_options['filters']['field_vlnt_station_target_id']['value']['value'] = '1';

  /* Display: Partioversigt */
  $handler = $view->new_display('panel_pane', 'Partioversigt', 'panel_pane_4');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'valghalla view party-overview list';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'nid' => 'nid',
    'entity_id_6' => 'entity_id_6',
    'title' => 'title',
    'entity_id_7' => 'entity_id_7',
    'entity_id_8' => 'entity_id_8',
    'entity_id' => 'entity_id',
    'entity_id_1' => 'entity_id_1',
    'entity_id_2' => 'entity_id_2',
    'entity_id_3' => 'entity_id_3',
    'entity_id_4' => 'entity_id_4',
    'entity_id_5' => 'entity_id_5',
    'entity_id_9' => 'entity_id_9',
    'field_vlnt_station' => 'field_vlnt_station',
    'field_post_role' => 'field_post_role',
    'nothing' => 'nothing',
    'field_post_party' => 'field_post_party',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'nid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'entity_id_6' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'entity_id_7' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'entity_id_8' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'entity_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'entity_id_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'entity_id_2' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'entity_id_3' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'entity_id_4' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'entity_id_5' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'entity_id_9' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_vlnt_station' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_post_role' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nothing' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_post_party' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Felt: Indhold: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['link_to_node'] = TRUE;
  /* Felt: Felt: Parti */
  $handler->display->display_options['fields']['entity_id_6']['id'] = 'entity_id_6';
  $handler->display->display_options['fields']['entity_id_6']['table'] = 'field_data_field_party';
  $handler->display->display_options['fields']['entity_id_6']['field'] = 'field_party';
  $handler->display->display_options['fields']['entity_id_6']['label'] = '';
  $handler->display->display_options['fields']['entity_id_6']['element_type'] = '0';
  $handler->display->display_options['fields']['entity_id_6']['element_label_type'] = '0';
  $handler->display->display_options['fields']['entity_id_6']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['entity_id_6']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['entity_id_6']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['entity_id_6']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['entity_id_6']['type'] = 'taxonomy_term_reference_plain';
  /* Felt: Indhold: Titel */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Navn';
  /* Felt: Telefon */
  $handler->display->display_options['fields']['entity_id_7']['id'] = 'entity_id_7';
  $handler->display->display_options['fields']['entity_id_7']['table'] = 'field_data_field_phone';
  $handler->display->display_options['fields']['entity_id_7']['field'] = 'field_phone';
  $handler->display->display_options['fields']['entity_id_7']['ui_name'] = 'Telefon';
  $handler->display->display_options['fields']['entity_id_7']['exclude'] = TRUE;
  $handler->display->display_options['fields']['entity_id_7']['element_type'] = '0';
  $handler->display->display_options['fields']['entity_id_7']['element_label_type'] = '0';
  $handler->display->display_options['fields']['entity_id_7']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['entity_id_7']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['entity_id_7']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['entity_id_7']['type'] = 'text_plain';
  /* Felt: Indhold: Telefon 2 */
  $handler->display->display_options['fields']['entity_id_8']['id'] = 'entity_id_8';
  $handler->display->display_options['fields']['entity_id_8']['table'] = 'field_data_field_phone2';
  $handler->display->display_options['fields']['entity_id_8']['field'] = 'field_phone2';
  $handler->display->display_options['fields']['entity_id_8']['exclude'] = TRUE;
  $handler->display->display_options['fields']['entity_id_8']['alter']['text'] = '/ [entity_id_8]';
  $handler->display->display_options['fields']['entity_id_8']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['entity_id_8']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['entity_id_8']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['entity_id_8']['hide_empty'] = TRUE;
  /* Felt: Indhold: By */
  $handler->display->display_options['fields']['entity_id']['id'] = 'entity_id';
  $handler->display->display_options['fields']['entity_id']['table'] = 'field_data_field_address_city';
  $handler->display->display_options['fields']['entity_id']['field'] = 'field_address_city';
  $handler->display->display_options['fields']['entity_id']['label'] = 'field_address_door';
  $handler->display->display_options['fields']['entity_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['entity_id']['hide_empty'] = TRUE;
  /* Felt: Indhold: Dør / Side */
  $handler->display->display_options['fields']['entity_id_1']['id'] = 'entity_id_1';
  $handler->display->display_options['fields']['entity_id_1']['table'] = 'field_data_field_address_door';
  $handler->display->display_options['fields']['entity_id_1']['field'] = 'field_address_door';
  $handler->display->display_options['fields']['entity_id_1']['label'] = 'field_address_door';
  $handler->display->display_options['fields']['entity_id_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['entity_id_1']['hide_empty'] = TRUE;
  /* Felt: Indhold: Sal */
  $handler->display->display_options['fields']['entity_id_2']['id'] = 'entity_id_2';
  $handler->display->display_options['fields']['entity_id_2']['table'] = 'field_data_field_address_floor';
  $handler->display->display_options['fields']['entity_id_2']['field'] = 'field_address_floor';
  $handler->display->display_options['fields']['entity_id_2']['label'] = 'field_address_floor';
  $handler->display->display_options['fields']['entity_id_2']['exclude'] = TRUE;
  $handler->display->display_options['fields']['entity_id_2']['hide_empty'] = TRUE;
  /* Felt: Indhold: Vej */
  $handler->display->display_options['fields']['entity_id_3']['id'] = 'entity_id_3';
  $handler->display->display_options['fields']['entity_id_3']['table'] = 'field_data_field_address_road';
  $handler->display->display_options['fields']['entity_id_3']['field'] = 'field_address_road';
  $handler->display->display_options['fields']['entity_id_3']['label'] = 'field_address_road';
  $handler->display->display_options['fields']['entity_id_3']['exclude'] = TRUE;
  $handler->display->display_options['fields']['entity_id_3']['hide_empty'] = TRUE;
  /* Felt: Indhold: Nummer */
  $handler->display->display_options['fields']['entity_id_4']['id'] = 'entity_id_4';
  $handler->display->display_options['fields']['entity_id_4']['table'] = 'field_data_field_address_road_no';
  $handler->display->display_options['fields']['entity_id_4']['field'] = 'field_address_road_no';
  $handler->display->display_options['fields']['entity_id_4']['label'] = 'field_address_road_no';
  $handler->display->display_options['fields']['entity_id_4']['exclude'] = TRUE;
  $handler->display->display_options['fields']['entity_id_4']['hide_empty'] = TRUE;
  /* Felt: Indhold: Postnummer */
  $handler->display->display_options['fields']['entity_id_5']['id'] = 'entity_id_5';
  $handler->display->display_options['fields']['entity_id_5']['table'] = 'field_data_field_address_zipcode';
  $handler->display->display_options['fields']['entity_id_5']['field'] = 'field_address_zipcode';
  $handler->display->display_options['fields']['entity_id_5']['label'] = 'field_address_zipcode';
  $handler->display->display_options['fields']['entity_id_5']['exclude'] = TRUE;
  $handler->display->display_options['fields']['entity_id_5']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['entity_id_5']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 1,
  );
  /* Felt: Felt: Valgsted */
  $handler->display->display_options['fields']['entity_id_9']['id'] = 'entity_id_9';
  $handler->display->display_options['fields']['entity_id_9']['table'] = 'field_data_field_polling_station';
  $handler->display->display_options['fields']['entity_id_9']['field'] = 'field_polling_station';
  $handler->display->display_options['fields']['entity_id_9']['label'] = '';
  $handler->display->display_options['fields']['entity_id_9']['exclude'] = TRUE;
  $handler->display->display_options['fields']['entity_id_9']['element_type'] = 'span';
  $handler->display->display_options['fields']['entity_id_9']['element_label_type'] = 'span';
  $handler->display->display_options['fields']['entity_id_9']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['entity_id_9']['element_wrapper_type'] = 'span';
  $handler->display->display_options['fields']['entity_id_9']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['entity_id_9']['type'] = 'node_reference_plain';
  $handler->display->display_options['fields']['entity_id_9']['delta_offset'] = '0';
  /* Felt: Field collection item: Valgsted */
  $handler->display->display_options['fields']['field_vlnt_station']['id'] = 'field_vlnt_station';
  $handler->display->display_options['fields']['field_vlnt_station']['table'] = 'field_data_field_vlnt_station';
  $handler->display->display_options['fields']['field_vlnt_station']['field'] = 'field_vlnt_station';
  $handler->display->display_options['fields']['field_vlnt_station']['relationship'] = 'field_electioninfo_value';
  $handler->display->display_options['fields']['field_vlnt_station']['label'] = 'valgsted';
  $handler->display->display_options['fields']['field_vlnt_station']['settings'] = array(
    'link' => 1,
  );
  /* Felt: Field collection item: Rolle */
  $handler->display->display_options['fields']['field_post_role']['id'] = 'field_post_role';
  $handler->display->display_options['fields']['field_post_role']['table'] = 'field_data_field_post_role';
  $handler->display->display_options['fields']['field_post_role']['field'] = 'field_post_role';
  $handler->display->display_options['fields']['field_post_role']['relationship'] = 'field_electioninfo_value';
  $handler->display->display_options['fields']['field_post_role']['settings'] = array(
    'link' => 0,
  );
  /* Felt: Global: Tilpasset tekst */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<div>
<h4>[title] ([entity_id_6] )</h4>
<span calss="mobile">[entity_id_7] [entity_id_8]
</span>
</div>';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
  /* Felt: Field collection item: Parti plads */
  $handler->display->display_options['fields']['field_post_party']['id'] = 'field_post_party';
  $handler->display->display_options['fields']['field_post_party']['table'] = 'field_data_field_post_party';
  $handler->display->display_options['fields']['field_post_party']['field'] = 'field_post_party';
  $handler->display->display_options['fields']['field_post_party']['relationship'] = 'field_electioninfo_value';
  $handler->display->display_options['fields']['field_post_party']['label'] = 'Pladsen tilhører (parti)';
  $handler->display->display_options['fields']['field_post_party']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sorteringskriterie: Field collection item: Valgsted (field_vlnt_station) */
  $handler->display->display_options['sorts']['field_vlnt_station_target_id']['id'] = 'field_vlnt_station_target_id';
  $handler->display->display_options['sorts']['field_vlnt_station_target_id']['table'] = 'field_data_field_vlnt_station';
  $handler->display->display_options['sorts']['field_vlnt_station_target_id']['field'] = 'field_vlnt_station_target_id';
  $handler->display->display_options['sorts']['field_vlnt_station_target_id']['relationship'] = 'field_electioninfo_value';
  /* Sorteringskriterie: Field collection item: Status (field_rsvp) */
  $handler->display->display_options['sorts']['field_rsvp_value']['id'] = 'field_rsvp_value';
  $handler->display->display_options['sorts']['field_rsvp_value']['table'] = 'field_data_field_rsvp';
  $handler->display->display_options['sorts']['field_rsvp_value']['field'] = 'field_rsvp_value';
  /* Sorteringskriterie: Indhold: Titel */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Kontekstuelt filter: Felt: Parti (field_party) */
  $handler->display->display_options['arguments']['field_party_tid']['id'] = 'field_party_tid';
  $handler->display->display_options['arguments']['field_party_tid']['table'] = 'field_data_field_party';
  $handler->display->display_options['arguments']['field_party_tid']['field'] = 'field_party_tid';
  $handler->display->display_options['arguments']['field_party_tid']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['field_party_tid']['exception']['title'] = 'Alle';
  $handler->display->display_options['arguments']['field_party_tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_party_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_party_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_party_tid']['summary_options']['items_per_page'] = '25';
  /* Kontekstuelt filter: Field collection item: Valg (field_election) */
  $handler->display->display_options['arguments']['field_election_target_id']['id'] = 'field_election_target_id';
  $handler->display->display_options['arguments']['field_election_target_id']['table'] = 'field_data_field_election';
  $handler->display->display_options['arguments']['field_election_target_id']['field'] = 'field_election_target_id';
  $handler->display->display_options['arguments']['field_election_target_id']['relationship'] = 'field_electioninfo_value';
  $handler->display->display_options['arguments']['field_election_target_id']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_election_target_id']['exception']['title'] = 'Alle';
  $handler->display->display_options['arguments']['field_election_target_id']['default_argument_type'] = 'php';
  $handler->display->display_options['arguments']['field_election_target_id']['default_argument_options']['code'] = 'return $_SESSION[\'election_nid\'];';
  $handler->display->display_options['arguments']['field_election_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_election_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_election_target_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['allow']['use_pager'] = 0;
  $handler->display->display_options['allow']['items_per_page'] = 0;
  $handler->display->display_options['allow']['offset'] = 0;
  $handler->display->display_options['allow']['link_to_view'] = 0;
  $handler->display->display_options['allow']['more_link'] = 0;
  $handler->display->display_options['allow']['path_override'] = 0;
  $handler->display->display_options['allow']['title_override'] = 0;
  $handler->display->display_options['allow']['exposed_form'] = 0;
  $handler->display->display_options['allow']['fields_override'] = 0;
  $handler->display->display_options['argument_input'] = array(
    'field_party_tid' => array(
      'type' => 'user',
      'context' => 'entity:user.field_polling_station',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'Felt: Parti (field_party)',
    ),
  );
  $translatables['partioversigt'] = array(
    t('Defaults'),
    t('mere'),
    t('Udfør'),
    t('Gendan'),
    t('Sortér efter'),
    t('Stigende'),
    t('Faldende'),
    t('term'),
    t('field collection item from field_electioninfo'),
    t('Nid'),
    t('Navn'),
    t('CPR nummer'),
    t('Parti'),
    t('field_address_door'),
    t('field_address_floor'),
    t('field_address_road'),
    t('field_address_road_no'),
    t('field_address_zipcode'),
    t('Telefon'),
    t('Telefon 2'),
    t('valgsted'),
    t('<div>
<h4>[title] ([entity_id_6] )</h4>
<div>[entity_id_3] [entity_id_4] [entity_id_2] [entity_id_1]<br />
</div>
</div>'),
    t('Kvittering'),
    t('Alle'),
    t('Partioversigt'),
    t('/ [entity_id_8]'),
    t('Rolle'),
    t('<div>
<h4>[title] ([entity_id_6] )</h4>
<span calss="mobile">[entity_id_7] [entity_id_8]
</span>
</div>'),
    t('Pladsen tilhører (parti)'),
    t('View panes'),
  );
  $export['partioversigt'] = $view;

  return $export;
}
