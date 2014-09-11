<?php
/**
 * @file
 * liste_beskeder.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function liste_beskeder_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'Beskeder';
  $view->description = '';
  $view->tag = 'valghalla, list';
  $view->base_table = 'node';
  $view->human_name = 'Liste Beskeder';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Deltagere der ikke har svaret';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'mere';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'valghalla view no-reply list';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Udfør';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Gendan';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Sortér efter';
  $handler->display->display_options['exposed_form']['options']['sort_asc_label'] = 'Stigende';
  $handler->display->display_options['exposed_form']['options']['sort_desc_label'] = 'Faldende';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = 'Elementer pr. side';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- Alle -';
  $handler->display->display_options['pager']['options']['expose']['offset_label'] = 'Forskydning';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« første';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ forrige';
  $handler->display->display_options['pager']['options']['tags']['next'] = 'næste ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = 'sidste »';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'timestamp' => 'timestamp',
    'title' => 'title',
    'field_rsvp_1' => 'timestamp',
    'field_rsvp_comment_1' => 'title',
    'last_updated' => 'last_updated',
    'field_party' => 'timestamp',
    'field_vlnt_station' => 'title',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'timestamp' => array(
      'align' => '',
      'separator' => ' / ',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '<br />',
      'empty_column' => 0,
    ),
    'field_rsvp_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_rsvp_comment_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'last_updated' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_party' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_vlnt_station' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Forbindelse: Indhold: Valginfo (field_electioninfo) */
  $handler->display->display_options['relationships']['field_electioninfo_value']['id'] = 'field_electioninfo_value';
  $handler->display->display_options['relationships']['field_electioninfo_value']['table'] = 'field_data_field_electioninfo';
  $handler->display->display_options['relationships']['field_electioninfo_value']['field'] = 'field_electioninfo_value';
  $handler->display->display_options['relationships']['field_electioninfo_value']['delta'] = '-1';
  /* Felt: Indhold: Har nyt indhold */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'history';
  $handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['label'] = 'Status';
  $handler->display->display_options['fields']['timestamp']['element_label_colon'] = FALSE;
  /* Felt: Indhold: Titel */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Felt: Felt: Status */
  $handler->display->display_options['fields']['field_rsvp_1']['id'] = 'field_rsvp_1';
  $handler->display->display_options['fields']['field_rsvp_1']['table'] = 'field_data_field_rsvp';
  $handler->display->display_options['fields']['field_rsvp_1']['field'] = 'field_rsvp';
  $handler->display->display_options['fields']['field_rsvp_1']['relationship'] = 'field_electioninfo_value';
  /* Felt: Field collection item: Valgsted */
  $handler->display->display_options['fields']['field_vlnt_station']['id'] = 'field_vlnt_station';
  $handler->display->display_options['fields']['field_vlnt_station']['table'] = 'field_data_field_vlnt_station';
  $handler->display->display_options['fields']['field_vlnt_station']['field'] = 'field_vlnt_station';
  $handler->display->display_options['fields']['field_vlnt_station']['relationship'] = 'field_electioninfo_value';
  $handler->display->display_options['fields']['field_vlnt_station']['label'] = '';
  $handler->display->display_options['fields']['field_vlnt_station']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_vlnt_station']['settings'] = array(
    'link' => 1,
  );
  /* Felt: Felt: Status besked */
  $handler->display->display_options['fields']['field_rsvp_comment_1']['id'] = 'field_rsvp_comment_1';
  $handler->display->display_options['fields']['field_rsvp_comment_1']['table'] = 'field_data_field_rsvp_comment';
  $handler->display->display_options['fields']['field_rsvp_comment_1']['field'] = 'field_rsvp_comment';
  $handler->display->display_options['fields']['field_rsvp_comment_1']['relationship'] = 'field_electioninfo_value';
  $handler->display->display_options['fields']['field_rsvp_comment_1']['label'] = 'Besked';
  $handler->display->display_options['fields']['field_rsvp_comment_1']['element_label_colon'] = FALSE;
  /* Felt: Indhold: Opdateret/kommenteret dato */
  $handler->display->display_options['fields']['last_updated']['id'] = 'last_updated';
  $handler->display->display_options['fields']['last_updated']['table'] = 'node_comment_statistics';
  $handler->display->display_options['fields']['last_updated']['field'] = 'last_updated';
  $handler->display->display_options['fields']['last_updated']['label'] = 'Opdateret';
  $handler->display->display_options['fields']['last_updated']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['last_updated']['date_format'] = 'time ago';
  /* Felt: Felt: Parti */
  $handler->display->display_options['fields']['field_party']['id'] = 'field_party';
  $handler->display->display_options['fields']['field_party']['table'] = 'field_data_field_party';
  $handler->display->display_options['fields']['field_party']['field'] = 'field_party';
  $handler->display->display_options['fields']['field_party']['hide_alter_empty'] = FALSE;
  /* Sorteringskriterie: Indhold: Opdateringsdato */
  $handler->display->display_options['sorts']['changed']['id'] = 'changed';
  $handler->display->display_options['sorts']['changed']['table'] = 'node';
  $handler->display->display_options['sorts']['changed']['field'] = 'changed';
  $handler->display->display_options['sorts']['changed']['order'] = 'DESC';
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
  /* Filterkriterie: Indhold: Udgivet */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 0;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filterkriterie: Indhold: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'volunteers' => 'volunteers',
  );
  /* Filterkriterie: Felt: Status besked (field_rsvp_comment) */
  $handler->display->display_options['filters']['field_rsvp_comment_value']['id'] = 'field_rsvp_comment_value';
  $handler->display->display_options['filters']['field_rsvp_comment_value']['table'] = 'field_data_field_rsvp_comment';
  $handler->display->display_options['filters']['field_rsvp_comment_value']['field'] = 'field_rsvp_comment_value';
  $handler->display->display_options['filters']['field_rsvp_comment_value']['relationship'] = 'field_electioninfo_value';
  $handler->display->display_options['filters']['field_rsvp_comment_value']['operator'] = 'longerthan';
  $handler->display->display_options['filters']['field_rsvp_comment_value']['value'] = '1';

  /* Display: Beskeder */
  $handler = $view->new_display('page', 'Beskeder', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'valghalla view messages list';
  $handler->display->display_options['path'] = 'valghalla_lists/beskeder';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Beskeder';
  $handler->display->display_options['menu']['description'] = 'Deltagernes RSVP';
  $handler->display->display_options['menu']['weight'] = '2';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: Deltagere der ikke har svaret */
  $handler = $view->new_display('page', 'Deltagere der ikke har svaret', 'page_1');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filterkriterie: Indhold: Udgivet */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 0;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filterkriterie: Indhold: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'volunteers' => 'volunteers',
  );
  /* Filterkriterie: Felt: Status (field_rsvp) */
  $handler->display->display_options['filters']['field_rsvp_value']['id'] = 'field_rsvp_value';
  $handler->display->display_options['filters']['field_rsvp_value']['table'] = 'field_data_field_rsvp';
  $handler->display->display_options['filters']['field_rsvp_value']['field'] = 'field_rsvp_value';
  $handler->display->display_options['filters']['field_rsvp_value']['relationship'] = 'field_electioninfo_value';
  $handler->display->display_options['filters']['field_rsvp_value']['operator'] = 'not';
  $handler->display->display_options['filters']['field_rsvp_value']['value'] = array(
    1 => '1',
    2 => '2',
    3 => '3',
  );
  $handler->display->display_options['path'] = 'valghalla_lists/no_reply';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Deltagere der ikke har svaret';
  $handler->display->display_options['menu']['description'] = 'Liste over deltagere der endnu ikke har svaret';
  $handler->display->display_options['menu']['weight'] = '3';
  $handler->display->display_options['menu']['context'] = 0;
  $translatables['Beskeder'] = array(
    t('Master'),
    t('Deltagere der ikke har svaret'),
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
    t('field collection item from field_electioninfo'),
    t('Status'),
    t('Besked'),
    t('Opdateret'),
    t('Parti'),
    t('Alle'),
    t('Beskeder'),
  );
  $export['Beskeder'] = $view;

  return $export;
}
