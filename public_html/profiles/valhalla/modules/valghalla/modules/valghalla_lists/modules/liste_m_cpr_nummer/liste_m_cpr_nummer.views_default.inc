<?php
/**
 * @file
 * liste_m_cpr_nummer.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function liste_m_cpr_nummer_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'liste_valgsted_m_cpr';
  $view->description = 'Liste(kvitteringsliste) for valgsted';
  $view->tag = 'valghalla, list';
  $view->base_table = 'node';
  $view->human_name = 'Liste valgsted m cpr';
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
  $handler->display->display_options['style_options']['grouping'] = '';
  $handler->display->display_options['style_options']['columns'] = array(
    'field_label' => 'field_label',
    'field_polling_station_post' => 'field_polling_station_post',
    'entity_id_6' => 'entity_id_6',
    'nid' => 'nid',
    'title' => 'title',
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
    'field_cpr_number' => 'field_cpr_number',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'field_label' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'field_polling_station_post' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'entity_id_6' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'nid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'entity_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'entity_id_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'entity_id_2' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'entity_id_3' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'entity_id_4' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'entity_id_5' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'entity_id_7' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'entity_id_8' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'entity_id_9' => array(
      'align' => '',
      'separator' => '',
    ),
    'nothing' => array(
      'align' => '',
      'separator' => '',
    ),
    'field_cpr_number' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
  );
  /* Forbindelse: Indhold: Taksonomitermer på node */
  $handler->display->display_options['relationships']['term_node_tid']['id'] = 'term_node_tid';
  $handler->display->display_options['relationships']['term_node_tid']['table'] = 'node';
  $handler->display->display_options['relationships']['term_node_tid']['field'] = 'term_node_tid';
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
  /* Felt: Indhold: CPR Number */
  $handler->display->display_options['fields']['field_cpr_number']['id'] = 'field_cpr_number';
  $handler->display->display_options['fields']['field_cpr_number']['table'] = 'field_data_field_cpr_number';
  $handler->display->display_options['fields']['field_cpr_number']['field'] = 'field_cpr_number';
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
  /* Felt: Indhold: City */
  $handler->display->display_options['fields']['entity_id']['id'] = 'entity_id';
  $handler->display->display_options['fields']['entity_id']['table'] = 'field_data_field_address_city';
  $handler->display->display_options['fields']['entity_id']['field'] = 'field_address_city';
  $handler->display->display_options['fields']['entity_id']['label'] = 'field_address_door';
  $handler->display->display_options['fields']['entity_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['entity_id']['hide_empty'] = TRUE;
  /* Felt: Indhold: Door / Side */
  $handler->display->display_options['fields']['entity_id_1']['id'] = 'entity_id_1';
  $handler->display->display_options['fields']['entity_id_1']['table'] = 'field_data_field_address_door';
  $handler->display->display_options['fields']['entity_id_1']['field'] = 'field_address_door';
  $handler->display->display_options['fields']['entity_id_1']['label'] = 'field_address_door';
  $handler->display->display_options['fields']['entity_id_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['entity_id_1']['hide_empty'] = TRUE;
  /* Felt: Indhold: Floor */
  $handler->display->display_options['fields']['entity_id_2']['id'] = 'entity_id_2';
  $handler->display->display_options['fields']['entity_id_2']['table'] = 'field_data_field_address_floor';
  $handler->display->display_options['fields']['entity_id_2']['field'] = 'field_address_floor';
  $handler->display->display_options['fields']['entity_id_2']['label'] = 'field_address_floor';
  $handler->display->display_options['fields']['entity_id_2']['exclude'] = TRUE;
  $handler->display->display_options['fields']['entity_id_2']['hide_empty'] = TRUE;
  /* Felt: Indhold: Address */
  $handler->display->display_options['fields']['entity_id_3']['id'] = 'entity_id_3';
  $handler->display->display_options['fields']['entity_id_3']['table'] = 'field_data_field_address_road';
  $handler->display->display_options['fields']['entity_id_3']['field'] = 'field_address_road';
  $handler->display->display_options['fields']['entity_id_3']['label'] = 'field_address_road';
  $handler->display->display_options['fields']['entity_id_3']['exclude'] = TRUE;
  $handler->display->display_options['fields']['entity_id_3']['hide_empty'] = TRUE;
  /* Felt: Indhold: House no. */
  $handler->display->display_options['fields']['entity_id_4']['id'] = 'entity_id_4';
  $handler->display->display_options['fields']['entity_id_4']['table'] = 'field_data_field_address_road_no';
  $handler->display->display_options['fields']['entity_id_4']['field'] = 'field_address_road_no';
  $handler->display->display_options['fields']['entity_id_4']['label'] = 'field_address_road_no';
  $handler->display->display_options['fields']['entity_id_4']['exclude'] = TRUE;
  $handler->display->display_options['fields']['entity_id_4']['hide_empty'] = TRUE;
  /* Felt: Indhold: Zip code */
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
  /* Felt: Felt: Begræns adgang til følgende valgsteder */
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
  /* Felt: Indhold: Polling Station post */
  $handler->display->display_options['fields']['field_polling_station_post']['id'] = 'field_polling_station_post';
  $handler->display->display_options['fields']['field_polling_station_post']['table'] = 'field_data_field_polling_station_post';
  $handler->display->display_options['fields']['field_polling_station_post']['field'] = 'field_polling_station_post';
  $handler->display->display_options['fields']['field_polling_station_post']['label'] = 'Placering';
  $handler->display->display_options['fields']['field_polling_station_post']['type'] = 'number_unformatted';
  $handler->display->display_options['fields']['field_polling_station_post']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 1,
  );
  /* Felt: Global: Tilpasset tekst */
  $handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
  $handler->display->display_options['fields']['nothing_1']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_1']['label'] = 'Kvittering';
  /* Sorteringskriterie: Felt: Status (field_rsvp) */
  $handler->display->display_options['sorts']['field_rsvp_value']['id'] = 'field_rsvp_value';
  $handler->display->display_options['sorts']['field_rsvp_value']['table'] = 'field_data_field_rsvp';
  $handler->display->display_options['sorts']['field_rsvp_value']['field'] = 'field_rsvp_value';
  /* Sorteringskriterie: Ord i ordforråd: Navn */
  $handler->display->display_options['sorts']['name']['id'] = 'name';
  $handler->display->display_options['sorts']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['sorts']['name']['field'] = 'name';
  $handler->display->display_options['sorts']['name']['relationship'] = 'term_node_tid';
  /* Sorteringskriterie: Indhold: Titel */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  /* Kontekstuelt filter: Felt: Begræns adgang til følgende valgsteder (field_polling_station) */
  $handler->display->display_options['arguments']['field_polling_station_nid']['id'] = 'field_polling_station_nid';
  $handler->display->display_options['arguments']['field_polling_station_nid']['table'] = 'field_data_field_polling_station';
  $handler->display->display_options['arguments']['field_polling_station_nid']['field'] = 'field_polling_station_nid';
  $handler->display->display_options['arguments']['field_polling_station_nid']['default_action'] = 'access denied';
  $handler->display->display_options['arguments']['field_polling_station_nid']['exception']['title'] = 'Alle';
  $handler->display->display_options['arguments']['field_polling_station_nid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_polling_station_nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_polling_station_nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_polling_station_nid']['summary_options']['items_per_page'] = '25';
  /* Filterkriterie: Indhold: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'volunteers' => 'volunteers',
  );
  $handler->display->display_options['filters']['type']['group'] = '0';
  /* Filterkriterie: Felt: Begræns adgang til følgende valgsteder (field_polling_station) */
  $handler->display->display_options['filters']['field_polling_station_nid']['id'] = 'field_polling_station_nid';
  $handler->display->display_options['filters']['field_polling_station_nid']['table'] = 'field_data_field_polling_station';
  $handler->display->display_options['filters']['field_polling_station_nid']['field'] = 'field_polling_station_nid';
  $handler->display->display_options['filters']['field_polling_station_nid']['operator'] = 'not empty';
  $handler->display->display_options['filters']['field_polling_station_nid']['group'] = '0';
  /* Filterkriterie: Indhold: Polling Station post (field_polling_station_post) */
  $handler->display->display_options['filters']['field_polling_station_post_value']['id'] = 'field_polling_station_post_value';
  $handler->display->display_options['filters']['field_polling_station_post_value']['table'] = 'field_data_field_polling_station_post';
  $handler->display->display_options['filters']['field_polling_station_post_value']['field'] = 'field_polling_station_post_value';
  $handler->display->display_options['filters']['field_polling_station_post_value']['operator'] = '>=';
  $handler->display->display_options['filters']['field_polling_station_post_value']['value']['value'] = '1';
  $handler->display->display_options['filters']['field_polling_station_post_value']['group'] = '0';

  /* Display: Kvitteringsliste m CPR */
  $handler = $view->new_display('page', 'Kvitteringsliste m CPR', 'page_2');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Kvitteringsliste';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Overskrift: Global: View-område */
  $handler->display->display_options['header']['view']['id'] = 'view';
  $handler->display->display_options['header']['view']['table'] = 'views';
  $handler->display->display_options['header']['view']['field'] = 'view';
  $handler->display->display_options['header']['view']['view_to_insert'] = 'valgsted:ctools_context_1';
  $handler->display->display_options['header']['view']['inherit_arguments'] = TRUE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Felt: Indhold: Label */
  $handler->display->display_options['fields']['field_label']['id'] = 'field_label';
  $handler->display->display_options['fields']['field_label']['table'] = 'field_data_field_label';
  $handler->display->display_options['fields']['field_label']['field'] = 'field_label';
  $handler->display->display_options['fields']['field_label']['label'] = 'Rolle';
  $handler->display->display_options['fields']['field_label']['element_label_colon'] = FALSE;
  /* Felt: Indhold: Polling Station post */
  $handler->display->display_options['fields']['field_polling_station_post']['id'] = 'field_polling_station_post';
  $handler->display->display_options['fields']['field_polling_station_post']['table'] = 'field_data_field_polling_station_post';
  $handler->display->display_options['fields']['field_polling_station_post']['field'] = 'field_polling_station_post';
  $handler->display->display_options['fields']['field_polling_station_post']['label'] = 'Placering';
  $handler->display->display_options['fields']['field_polling_station_post']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_polling_station_post']['type'] = 'number_unformatted';
  $handler->display->display_options['fields']['field_polling_station_post']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 1,
  );
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
  /* Felt: Indhold: City */
  $handler->display->display_options['fields']['entity_id']['id'] = 'entity_id';
  $handler->display->display_options['fields']['entity_id']['table'] = 'field_data_field_address_city';
  $handler->display->display_options['fields']['entity_id']['field'] = 'field_address_city';
  $handler->display->display_options['fields']['entity_id']['label'] = 'field_address_door';
  $handler->display->display_options['fields']['entity_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['entity_id']['hide_empty'] = TRUE;
  /* Felt: Indhold: Door / Side */
  $handler->display->display_options['fields']['entity_id_1']['id'] = 'entity_id_1';
  $handler->display->display_options['fields']['entity_id_1']['table'] = 'field_data_field_address_door';
  $handler->display->display_options['fields']['entity_id_1']['field'] = 'field_address_door';
  $handler->display->display_options['fields']['entity_id_1']['label'] = 'field_address_door';
  $handler->display->display_options['fields']['entity_id_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['entity_id_1']['hide_empty'] = TRUE;
  /* Felt: Indhold: Floor */
  $handler->display->display_options['fields']['entity_id_2']['id'] = 'entity_id_2';
  $handler->display->display_options['fields']['entity_id_2']['table'] = 'field_data_field_address_floor';
  $handler->display->display_options['fields']['entity_id_2']['field'] = 'field_address_floor';
  $handler->display->display_options['fields']['entity_id_2']['label'] = 'field_address_floor';
  $handler->display->display_options['fields']['entity_id_2']['exclude'] = TRUE;
  $handler->display->display_options['fields']['entity_id_2']['hide_empty'] = TRUE;
  /* Felt: Indhold: Address */
  $handler->display->display_options['fields']['entity_id_3']['id'] = 'entity_id_3';
  $handler->display->display_options['fields']['entity_id_3']['table'] = 'field_data_field_address_road';
  $handler->display->display_options['fields']['entity_id_3']['field'] = 'field_address_road';
  $handler->display->display_options['fields']['entity_id_3']['label'] = 'field_address_road';
  $handler->display->display_options['fields']['entity_id_3']['exclude'] = TRUE;
  $handler->display->display_options['fields']['entity_id_3']['hide_empty'] = TRUE;
  /* Felt: Indhold: House no. */
  $handler->display->display_options['fields']['entity_id_4']['id'] = 'entity_id_4';
  $handler->display->display_options['fields']['entity_id_4']['table'] = 'field_data_field_address_road_no';
  $handler->display->display_options['fields']['entity_id_4']['field'] = 'field_address_road_no';
  $handler->display->display_options['fields']['entity_id_4']['label'] = 'field_address_road_no';
  $handler->display->display_options['fields']['entity_id_4']['exclude'] = TRUE;
  $handler->display->display_options['fields']['entity_id_4']['hide_empty'] = TRUE;
  /* Felt: Indhold: Zip code */
  $handler->display->display_options['fields']['entity_id_5']['id'] = 'entity_id_5';
  $handler->display->display_options['fields']['entity_id_5']['table'] = 'field_data_field_address_zipcode';
  $handler->display->display_options['fields']['entity_id_5']['field'] = 'field_address_zipcode';
  $handler->display->display_options['fields']['entity_id_5']['label'] = 'Adresse';
  $handler->display->display_options['fields']['entity_id_5']['exclude'] = TRUE;
  $handler->display->display_options['fields']['entity_id_5']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['entity_id_5']['alter']['text'] = '[entity_id_3] [entity_id_4]  [entity_id_2] [entity_id_1], [entity_id_5] [entity_id]';
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
  /* Felt: Indhold: CPR Number */
  $handler->display->display_options['fields']['field_cpr_number']['id'] = 'field_cpr_number';
  $handler->display->display_options['fields']['field_cpr_number']['table'] = 'field_data_field_cpr_number';
  $handler->display->display_options['fields']['field_cpr_number']['field'] = 'field_cpr_number';
  /* Felt: Indhold: Diæt */
  $handler->display->display_options['fields']['field_diaet']['id'] = 'field_diaet';
  $handler->display->display_options['fields']['field_diaet']['table'] = 'field_data_field_diaet';
  $handler->display->display_options['fields']['field_diaet']['field'] = 'field_diaet';
  $handler->display->display_options['fields']['field_diaet']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_diaet']['alter']['text'] = '790';
  $handler->display->display_options['fields']['field_diaet']['empty'] = '790';
  $handler->display->display_options['fields']['field_diaet']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 1,
  );
  /* Felt: Global: Tilpasset tekst */
  $handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
  $handler->display->display_options['fields']['nothing_1']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_1']['label'] = 'Kvittering';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sorteringskriterie: Ord i ordforråd: Navn */
  $handler->display->display_options['sorts']['name']['id'] = 'name';
  $handler->display->display_options['sorts']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['sorts']['name']['field'] = 'name';
  /* Sorteringskriterie: Indhold: Polling Station post (field_polling_station_post) */
  $handler->display->display_options['sorts']['field_polling_station_post_value']['id'] = 'field_polling_station_post_value';
  $handler->display->display_options['sorts']['field_polling_station_post_value']['table'] = 'field_data_field_polling_station_post';
  $handler->display->display_options['sorts']['field_polling_station_post_value']['field'] = 'field_polling_station_post_value';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['filter_groups']['groups'] = array(
    1 => 'AND',
    2 => 'AND',
  );
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filterkriterie: Indhold: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'volunteers' => 'volunteers',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filterkriterie: Felt: Begræns adgang til følgende valgsteder (field_polling_station) */
  $handler->display->display_options['filters']['field_polling_station_nid']['id'] = 'field_polling_station_nid';
  $handler->display->display_options['filters']['field_polling_station_nid']['table'] = 'field_data_field_polling_station';
  $handler->display->display_options['filters']['field_polling_station_nid']['field'] = 'field_polling_station_nid';
  $handler->display->display_options['filters']['field_polling_station_nid']['operator'] = 'not empty';
  $handler->display->display_options['filters']['field_polling_station_nid']['group'] = 1;
  /* Filterkriterie: Indhold: Polling Station post (field_polling_station_post) */
  $handler->display->display_options['filters']['field_polling_station_post_value']['id'] = 'field_polling_station_post_value';
  $handler->display->display_options['filters']['field_polling_station_post_value']['table'] = 'field_data_field_polling_station_post';
  $handler->display->display_options['filters']['field_polling_station_post_value']['field'] = 'field_polling_station_post_value';
  $handler->display->display_options['filters']['field_polling_station_post_value']['operator'] = '>=';
  $handler->display->display_options['filters']['field_polling_station_post_value']['value']['value'] = '1';
  $handler->display->display_options['filters']['field_polling_station_post_value']['group'] = 1;
  $handler->display->display_options['path'] = 'node/%/valgstederm2';

  /* Display: Valgstyrere og tilforordnede */
  $handler = $view->new_display('page', 'Valgstyrere og tilforordnede', 'page_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Valgstyrere og tilforordnede';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Overskrift: Global: View-område */
  $handler->display->display_options['header']['view']['id'] = 'view';
  $handler->display->display_options['header']['view']['table'] = 'views';
  $handler->display->display_options['header']['view']['field'] = 'view';
  $handler->display->display_options['header']['view']['view_to_insert'] = 'valgsted:ctools_context_1';
  $handler->display->display_options['header']['view']['inherit_arguments'] = TRUE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Felt: Indhold: Label */
  $handler->display->display_options['fields']['field_label']['id'] = 'field_label';
  $handler->display->display_options['fields']['field_label']['table'] = 'field_data_field_label';
  $handler->display->display_options['fields']['field_label']['field'] = 'field_label';
  $handler->display->display_options['fields']['field_label']['label'] = 'Rolle';
  $handler->display->display_options['fields']['field_label']['element_label_colon'] = FALSE;
  /* Felt: Indhold: Polling Station post */
  $handler->display->display_options['fields']['field_polling_station_post']['id'] = 'field_polling_station_post';
  $handler->display->display_options['fields']['field_polling_station_post']['table'] = 'field_data_field_polling_station_post';
  $handler->display->display_options['fields']['field_polling_station_post']['field'] = 'field_polling_station_post';
  $handler->display->display_options['fields']['field_polling_station_post']['label'] = 'Placering';
  $handler->display->display_options['fields']['field_polling_station_post']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_polling_station_post']['type'] = 'number_unformatted';
  $handler->display->display_options['fields']['field_polling_station_post']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 1,
  );
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
  /* Felt: Indhold: City */
  $handler->display->display_options['fields']['entity_id']['id'] = 'entity_id';
  $handler->display->display_options['fields']['entity_id']['table'] = 'field_data_field_address_city';
  $handler->display->display_options['fields']['entity_id']['field'] = 'field_address_city';
  $handler->display->display_options['fields']['entity_id']['label'] = 'field_address_door';
  $handler->display->display_options['fields']['entity_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['entity_id']['hide_empty'] = TRUE;
  /* Felt: Indhold: Door / Side */
  $handler->display->display_options['fields']['entity_id_1']['id'] = 'entity_id_1';
  $handler->display->display_options['fields']['entity_id_1']['table'] = 'field_data_field_address_door';
  $handler->display->display_options['fields']['entity_id_1']['field'] = 'field_address_door';
  $handler->display->display_options['fields']['entity_id_1']['label'] = 'field_address_door';
  $handler->display->display_options['fields']['entity_id_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['entity_id_1']['hide_empty'] = TRUE;
  /* Felt: Indhold: Floor */
  $handler->display->display_options['fields']['entity_id_2']['id'] = 'entity_id_2';
  $handler->display->display_options['fields']['entity_id_2']['table'] = 'field_data_field_address_floor';
  $handler->display->display_options['fields']['entity_id_2']['field'] = 'field_address_floor';
  $handler->display->display_options['fields']['entity_id_2']['label'] = 'field_address_floor';
  $handler->display->display_options['fields']['entity_id_2']['exclude'] = TRUE;
  $handler->display->display_options['fields']['entity_id_2']['hide_empty'] = TRUE;
  /* Felt: Indhold: Address */
  $handler->display->display_options['fields']['entity_id_3']['id'] = 'entity_id_3';
  $handler->display->display_options['fields']['entity_id_3']['table'] = 'field_data_field_address_road';
  $handler->display->display_options['fields']['entity_id_3']['field'] = 'field_address_road';
  $handler->display->display_options['fields']['entity_id_3']['label'] = 'field_address_road';
  $handler->display->display_options['fields']['entity_id_3']['exclude'] = TRUE;
  $handler->display->display_options['fields']['entity_id_3']['hide_empty'] = TRUE;
  /* Felt: Indhold: House no. */
  $handler->display->display_options['fields']['entity_id_4']['id'] = 'entity_id_4';
  $handler->display->display_options['fields']['entity_id_4']['table'] = 'field_data_field_address_road_no';
  $handler->display->display_options['fields']['entity_id_4']['field'] = 'field_address_road_no';
  $handler->display->display_options['fields']['entity_id_4']['label'] = 'field_address_road_no';
  $handler->display->display_options['fields']['entity_id_4']['exclude'] = TRUE;
  $handler->display->display_options['fields']['entity_id_4']['hide_empty'] = TRUE;
  /* Felt: Indhold: Zip code */
  $handler->display->display_options['fields']['entity_id_5']['id'] = 'entity_id_5';
  $handler->display->display_options['fields']['entity_id_5']['table'] = 'field_data_field_address_zipcode';
  $handler->display->display_options['fields']['entity_id_5']['field'] = 'field_address_zipcode';
  $handler->display->display_options['fields']['entity_id_5']['label'] = 'Adresse';
  $handler->display->display_options['fields']['entity_id_5']['exclude'] = TRUE;
  $handler->display->display_options['fields']['entity_id_5']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['entity_id_5']['alter']['text'] = '[entity_id_3] [entity_id_4]  [entity_id_2] [entity_id_1], [entity_id_5] [entity_id]';
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
  /* Felt: Felt: Begræns adgang til følgende valgsteder */
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
  /* Felt: Indhold: CPR Number */
  $handler->display->display_options['fields']['field_cpr_number']['id'] = 'field_cpr_number';
  $handler->display->display_options['fields']['field_cpr_number']['table'] = 'field_data_field_cpr_number';
  $handler->display->display_options['fields']['field_cpr_number']['field'] = 'field_cpr_number';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sorteringskriterie: Ord i ordforråd: Navn */
  $handler->display->display_options['sorts']['name']['id'] = 'name';
  $handler->display->display_options['sorts']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['sorts']['name']['field'] = 'name';
  /* Sorteringskriterie: Indhold: Polling Station post (field_polling_station_post) */
  $handler->display->display_options['sorts']['field_polling_station_post_value']['id'] = 'field_polling_station_post_value';
  $handler->display->display_options['sorts']['field_polling_station_post_value']['table'] = 'field_data_field_polling_station_post';
  $handler->display->display_options['sorts']['field_polling_station_post_value']['field'] = 'field_polling_station_post_value';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['filter_groups']['groups'] = array(
    1 => 'AND',
    2 => 'AND',
  );
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filterkriterie: Indhold: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'volunteers' => 'volunteers',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filterkriterie: Felt: Begræns adgang til følgende valgsteder (field_polling_station) */
  $handler->display->display_options['filters']['field_polling_station_nid']['id'] = 'field_polling_station_nid';
  $handler->display->display_options['filters']['field_polling_station_nid']['table'] = 'field_data_field_polling_station';
  $handler->display->display_options['filters']['field_polling_station_nid']['field'] = 'field_polling_station_nid';
  $handler->display->display_options['filters']['field_polling_station_nid']['operator'] = 'not empty';
  $handler->display->display_options['filters']['field_polling_station_nid']['group'] = 1;
  /* Filterkriterie: Indhold: Polling Station post (field_polling_station_post) */
  $handler->display->display_options['filters']['field_polling_station_post_value']['id'] = 'field_polling_station_post_value';
  $handler->display->display_options['filters']['field_polling_station_post_value']['table'] = 'field_data_field_polling_station_post';
  $handler->display->display_options['filters']['field_polling_station_post_value']['field'] = 'field_polling_station_post_value';
  $handler->display->display_options['filters']['field_polling_station_post_value']['operator'] = '>=';
  $handler->display->display_options['filters']['field_polling_station_post_value']['value']['value'] = '1';
  $handler->display->display_options['filters']['field_polling_station_post_value']['group'] = 1;
  $handler->display->display_options['path'] = 'node/%/valgstederm';
  $translatables['liste_valgsted_m_cpr'] = array(
    t('Defaults'),
    t('mere'),
    t('Udfør'),
    t('Gendan'),
    t('Sortér efter'),
    t('Stigende'),
    t('Faldende'),
    t('term'),
    t('Nid'),
    t('Navn'),
    t('CPR Number'),
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
    t('Placering'),
    t('Kvittering'),
    t('Alle'),
    t('Kvitteringsliste m CPR'),
    t('Kvitteringsliste'),
    t('Rolle'),
    t('Adresse'),
    t('[entity_id_3] [entity_id_4]  [entity_id_2] [entity_id_1], [entity_id_5] [entity_id]'),
    t('Diæt'),
    t('790'),
    t('Valgstyrere og tilforordnede'),
  );
  $export['liste_valgsted_m_cpr'] = $view;

  $view = new view();
  $view->name = 'liste_valgsteder_m_cpr';
  $view->description = 'Liste over valgsteder, linker til lister m. cpr';
  $view->tag = 'valghalla, list';
  $view->base_table = 'node';
  $view->human_name = 'Liste Valgsteder m cpr';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['css_class'] = 'valgsteder';
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
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = 'Elementer pr. side';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- Alle -';
  $handler->display->display_options['pager']['options']['expose']['offset_label'] = 'Forskydning';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« første';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ forrige';
  $handler->display->display_options['pager']['options']['tags']['next'] = 'næste ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = 'sidste »';
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['style_options']['grouping'] = 'entity_id_9';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['inline'] = array(
    'entity_id_3' => 'entity_id_3',
    'entity_id_6' => 'entity_id_6',
    'entity_id_7' => 'entity_id_7',
  );
  $handler->display->display_options['row_options']['hide_empty'] = TRUE;
  /* Felt: Indhold: Titel */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Felt: Indhold: Body */
  $handler->display->display_options['fields']['entity_id']['id'] = 'entity_id';
  $handler->display->display_options['fields']['entity_id']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['entity_id']['field'] = 'body';
  $handler->display->display_options['fields']['entity_id']['label'] = 'indhold';
  /* Felt: Indhold: Valgkontakt */
  $handler->display->display_options['fields']['entity_id_3']['id'] = 'entity_id_3';
  $handler->display->display_options['fields']['entity_id_3']['table'] = 'field_data_field_contact';
  $handler->display->display_options['fields']['entity_id_3']['field'] = 'field_contact';
  /* Felt: Felt: Parti */
  $handler->display->display_options['fields']['entity_id_5']['id'] = 'entity_id_5';
  $handler->display->display_options['fields']['entity_id_5']['table'] = 'field_data_field_party';
  $handler->display->display_options['fields']['entity_id_5']['field'] = 'field_party';
  /* Felt: Indhold: Andre kontaktoplysninger */
  $handler->display->display_options['fields']['entity_id_6']['id'] = 'entity_id_6';
  $handler->display->display_options['fields']['entity_id_6']['table'] = 'field_data_field_venue_contact';
  $handler->display->display_options['fields']['entity_id_6']['field'] = 'field_venue_contact';
  /* Felt: Indhold: Lokalekontakt */
  $handler->display->display_options['fields']['entity_id_7']['id'] = 'entity_id_7';
  $handler->display->display_options['fields']['entity_id_7']['table'] = 'field_data_field_venue_contact_name';
  $handler->display->display_options['fields']['entity_id_7']['field'] = 'field_venue_contact_name';
  /* Felt: Indhold: Valgkreds */
  $handler->display->display_options['fields']['entity_id_9']['id'] = 'entity_id_9';
  $handler->display->display_options['fields']['entity_id_9']['table'] = 'field_data_field_constituency';
  $handler->display->display_options['fields']['entity_id_9']['field'] = 'field_constituency';
  /* Sorteringskriterie: Indhold: Titel */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  /* Kontekstuelt filter: Indhold: Type */
  $handler->display->display_options['arguments']['type']['id'] = 'type';
  $handler->display->display_options['arguments']['type']['table'] = 'node';
  $handler->display->display_options['arguments']['type']['field'] = 'type';
  $handler->display->display_options['arguments']['type']['exception']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['type']['exception']['title'] = 'Alle';
  $handler->display->display_options['arguments']['type']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['type']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['type']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['type']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['type']['validate_options']['types'] = array(
    'polling_station' => 'polling_station',
  );
  /* Filterkriterie: Indhold: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'polling_station' => 'polling_station',
  );
  $handler->display->display_options['filters']['type']['group'] = '0';

  /* Display: Side m  CPR */
  $handler = $view->new_display('page', 'Side m  CPR', 'page_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Lister Valghalla med CPR numre';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    3 => '3',
    8 => '8',
  );
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'nid' => 'nid',
    'title' => 'title',
    'title_1' => 'title_1',
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
    'title_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Felt: Indhold: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Felt: Indhold: Titel */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Valgstyrere og tilforordnede';
  $handler->display->display_options['fields']['title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['path'] = 'node/[nid]/valgstederm';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Felt: Indhold: Titel */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'node';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['label'] = 'Kvitteringslister for diæter';
  $handler->display->display_options['fields']['title_1']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['title_1']['alter']['path'] = 'node/[nid]/valgstederm2';
  $handler->display->display_options['fields']['title_1']['link_to_node'] = FALSE;
  $handler->display->display_options['path'] = 'valhalla_lists/valgstederm';
  $translatables['liste_valgsteder_m_cpr'] = array(
    t('Defaults'),
    t('mere'),
    t('Udfør'),
    t('Gendan'),
    t('Sortér efter'),
    t('Stigende'),
    t('Faldende'),
    t('Elementer pr. side'),
    t('- Alle -'),
    t('Forskydning'),
    t('« første'),
    t('‹ forrige'),
    t('næste ›'),
    t('sidste »'),
    t('indhold'),
    t('Valgkontakt'),
    t('Parti'),
    t('Andre kontaktoplysninger'),
    t('Lokalekontakt'),
    t('Valgkreds'),
    t('Alle'),
    t('Side m  CPR'),
    t('Lister Valghalla med CPR numre'),
    t('Valgstyrere og tilforordnede'),
    t('Kvitteringslister for diæter'),
  );
  $export['liste_valgsteder_m_cpr'] = $view;

  return $export;
}
