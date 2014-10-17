<?php
/**
 * @file
 * valghalla_user_tools.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function valghalla_user_tools_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'indholdsfiltre';
  $view->description = '';
  $view->tag = 'valghalla,user_tools';
  $view->base_table = 'node';
  $view->human_name = 'Find deltager';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Find deltager';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'mere';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'view volunteers';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Udfør';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Gendan';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Sortér efter';
  $handler->display->display_options['exposed_form']['options']['sort_asc_label'] = 'Stigende';
  $handler->display->display_options['exposed_form']['options']['sort_desc_label'] = 'Faldende';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = 'Antal elementer';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- Alle -';
  $handler->display->display_options['pager']['options']['expose']['offset_label'] = 'Forskydning';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« første';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ forrige';
  $handler->display->display_options['pager']['options']['tags']['next'] = 'næste ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = 'sidste »';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'changed' => 'changed',
    'status' => 'status',
    'term_node_tid' => 'term_node_tid',
    'language' => 'language',
    'clone_node' => 'edit_node',
    'edit_node' => 'edit_node',
    'field_type' => 'field_type',
  );
  $handler->display->display_options['style_options']['default'] = 'title';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'changed' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'term_node_tid' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'language' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'clone_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_node' => array(
      'align' => '',
      'separator' => '/',
      'empty_column' => 0,
    ),
    'field_type' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  /* Felt: Indhold: Titel */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Felt: Indhold: CPR Number */
  $handler->display->display_options['fields']['field_cpr_number']['id'] = 'field_cpr_number';
  $handler->display->display_options['fields']['field_cpr_number']['table'] = 'field_data_field_cpr_number';
  $handler->display->display_options['fields']['field_cpr_number']['field'] = 'field_cpr_number';
  $handler->display->display_options['fields']['field_cpr_number']['label'] = 'CPR nummer';
  /* Felt: Indhold: Opdateringsdato */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'node';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['date_format'] = 'custom';
  $handler->display->display_options['fields']['changed']['custom_date_format'] = 'd.m.y';
  /* Felt: Indhold: Udgivet */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'node';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['not'] = 0;
  /* Felt: Indhold: Redigér-link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = 'Redigér';
  /* Felt: Felt: Parti */
  $handler->display->display_options['fields']['field_party']['id'] = 'field_party';
  $handler->display->display_options['fields']['field_party']['table'] = 'field_data_field_party';
  $handler->display->display_options['fields']['field_party']['field'] = 'field_party';
  $handler->display->display_options['fields']['field_party']['type'] = 'taxonomy_term_reference_plain';
  /* Sorteringskriterie: Indhold: Oprettelsesdato */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Kontekstuelt filter: Felt: Parti (field_party) */
  $handler->display->display_options['arguments']['field_party_tid']['id'] = 'field_party_tid';
  $handler->display->display_options['arguments']['field_party_tid']['table'] = 'field_data_field_party';
  $handler->display->display_options['arguments']['field_party_tid']['field'] = 'field_party_tid';
  $handler->display->display_options['arguments']['field_party_tid']['exception']['title'] = 'Alle';
  $handler->display->display_options['arguments']['field_party_tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_party_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_party_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_party_tid']['summary_options']['items_per_page'] = '25';
  /* Filterkriterie: Indhold: Titel */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';
  $handler->display->display_options['filters']['title']['group'] = 1;
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Navn';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    8 => 0,
  );
  /* Filterkriterie: Indhold: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'volunteers' => 'volunteers',
  );
  $handler->display->display_options['filters']['type']['expose']['operator_id'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['label'] = 'Type';
  $handler->display->display_options['filters']['type']['expose']['operator'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['identifier'] = 'type';
  $handler->display->display_options['filters']['type']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    5 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filterkriterie: Felt: Parti (field_party) */
  $handler->display->display_options['filters']['field_party_tid']['id'] = 'field_party_tid';
  $handler->display->display_options['filters']['field_party_tid']['table'] = 'field_data_field_party';
  $handler->display->display_options['filters']['field_party_tid']['field'] = 'field_party_tid';
  $handler->display->display_options['filters']['field_party_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_party_tid']['expose']['operator_id'] = 'field_party_tid_op';
  $handler->display->display_options['filters']['field_party_tid']['expose']['label'] = 'Parti';
  $handler->display->display_options['filters']['field_party_tid']['expose']['operator'] = 'field_party_tid_op';
  $handler->display->display_options['filters']['field_party_tid']['expose']['identifier'] = 'field_party_tid';
  $handler->display->display_options['filters']['field_party_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    5 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['filters']['field_party_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_party_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_party_tid']['vocabulary'] = 'partier';
  /* Filterkriterie: Indhold: CPR Number (field_cpr_number) */
  $handler->display->display_options['filters']['field_cpr_number_value']['id'] = 'field_cpr_number_value';
  $handler->display->display_options['filters']['field_cpr_number_value']['table'] = 'field_data_field_cpr_number';
  $handler->display->display_options['filters']['field_cpr_number_value']['field'] = 'field_cpr_number_value';
  $handler->display->display_options['filters']['field_cpr_number_value']['operator'] = 'contains';
  $handler->display->display_options['filters']['field_cpr_number_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_cpr_number_value']['expose']['operator_id'] = 'field_cpr_number_value_op';
  $handler->display->display_options['filters']['field_cpr_number_value']['expose']['label'] = 'CPR nummer';
  $handler->display->display_options['filters']['field_cpr_number_value']['expose']['operator'] = 'field_cpr_number_value_op';
  $handler->display->display_options['filters']['field_cpr_number_value']['expose']['identifier'] = 'field_cpr_number_value';
  $handler->display->display_options['filters']['field_cpr_number_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    5 => 0,
    3 => 0,
    4 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'valghalla/deltagere/alle';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Find deltager';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $translatables['indholdsfiltre'] = array(
    t('Master'),
    t('Find deltager'),
    t('mere'),
    t('Udfør'),
    t('Gendan'),
    t('Sortér efter'),
    t('Stigende'),
    t('Faldende'),
    t('Antal elementer'),
    t('- Alle -'),
    t('Forskydning'),
    t('« første'),
    t('‹ forrige'),
    t('næste ›'),
    t('sidste »'),
    t('CPR nummer'),
    t('Opdateringsdato'),
    t('Udgivet'),
    t('Redigér'),
    t('Parti'),
    t('Alle'),
    t('Navn'),
    t('Type'),
    t('Page'),
  );
  $export['indholdsfiltre'] = $view;

  $view = new view();
  $view->name = 'mail_templates';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Mail skabeloner';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Mail skabeloner';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'mere';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Udfør';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Gendan';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Sortér efter';
  $handler->display->display_options['exposed_form']['options']['sort_asc_label'] = 'Stigende';
  $handler->display->display_options['exposed_form']['options']['sort_desc_label'] = 'Faldende';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = 'Antal elementer';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- Alle -';
  $handler->display->display_options['pager']['options']['expose']['offset_label'] = 'Forskydning';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« første';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ forrige';
  $handler->display->display_options['pager']['options']['tags']['next'] = 'næste ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = 'sidste »';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Overskrift: Global: Tekstområde */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '<a class="btn btn-success" href="/valghalla/administration/sendmail">Opret ny skabelon</a>';
  $handler->display->display_options['header']['area']['format'] = 'filtered_html';
  /* Felt: Indhold: Titel */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Felt: Indhold: Emne */
  $handler->display->display_options['fields']['field_subject']['id'] = 'field_subject';
  $handler->display->display_options['fields']['field_subject']['table'] = 'field_data_field_subject';
  $handler->display->display_options['fields']['field_subject']['field'] = 'field_subject';
  /* Felt: Indhold: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = 'Brødtekst';
  $handler->display->display_options['fields']['body']['alter']['strip_tags'] = TRUE;
  $handler->display->display_options['fields']['body']['type'] = 'text_trimmed';
  $handler->display->display_options['fields']['body']['settings'] = array(
    'trim_length' => '200',
  );
  /* Felt: Indhold: Redigér-link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  /* Sorteringskriterie: Indhold: Oprettelsesdato */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filterkriterie: Indhold: Udgivet */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filterkriterie: Indhold: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'email' => 'email',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'valghalla/administration/mail-skabeloner';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Mail skabeloner';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $translatables['mail_templates'] = array(
    t('Master'),
    t('Mail skabeloner'),
    t('mere'),
    t('Udfør'),
    t('Gendan'),
    t('Sortér efter'),
    t('Stigende'),
    t('Faldende'),
    t('Antal elementer'),
    t('- Alle -'),
    t('Forskydning'),
    t('« første'),
    t('‹ forrige'),
    t('næste ›'),
    t('sidste »'),
    t('<a class="btn btn-success" href="/valghalla/administration/sendmail">Opret ny skabelon</a>'),
    t('Emne'),
    t('Brødtekst'),
    t('Redigér-link'),
    t('Page'),
  );
  $export['mail_templates'] = $view;

  $view = new view();
  $view->name = 'parti_oversigt';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'taxonomy_term_data';
  $view->human_name = 'Parti oversigt';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Parti oversigt';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'mere';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Udfør';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Gendan';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Sortér efter';
  $handler->display->display_options['exposed_form']['options']['sort_asc_label'] = 'Stigende';
  $handler->display->display_options['exposed_form']['options']['sort_desc_label'] = 'Faldende';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = 'Antal elementer';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- Alle -';
  $handler->display->display_options['pager']['options']['expose']['offset_label'] = 'Forskydning';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« første';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ forrige';
  $handler->display->display_options['pager']['options']['tags']['next'] = 'næste ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = 'sidste »';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'name' => 'name',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Overskrift: Global: Tekstområde */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '<a class="btn btn-success" href="/admin/structure/taxonomy/partier/add?destination=valghalla/administration/partier">Tilføj parti</a>';
  $handler->display->display_options['header']['area']['format'] = 'filtered_html';
  /* Felt: Ord i ordforråd: Navn */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_taxonomy'] = TRUE;
  /* Felt: Ord i ordforråd: Fuldt partinavn */
  $handler->display->display_options['fields']['field_partinavn']['id'] = 'field_partinavn';
  $handler->display->display_options['fields']['field_partinavn']['table'] = 'field_data_field_partinavn';
  $handler->display->display_options['fields']['field_partinavn']['field'] = 'field_partinavn';
  /* Felt: Ord i ordforråd: Link til redigering af term */
  $handler->display->display_options['fields']['edit_term']['id'] = 'edit_term';
  $handler->display->display_options['fields']['edit_term']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['edit_term']['field'] = 'edit_term';
  /* Filterkriterie: Ordforråd: Internt navn */
  $handler->display->display_options['filters']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['filters']['machine_name']['field'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['value'] = array(
    'partier' => 'partier',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'valghalla/administration/partier';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Parti oversigt';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $translatables['parti_oversigt'] = array(
    t('Master'),
    t('Parti oversigt'),
    t('mere'),
    t('Udfør'),
    t('Gendan'),
    t('Sortér efter'),
    t('Stigende'),
    t('Faldende'),
    t('Antal elementer'),
    t('- Alle -'),
    t('Forskydning'),
    t('« første'),
    t('‹ forrige'),
    t('næste ›'),
    t('sidste »'),
    t('<a class="btn btn-success" href="/admin/structure/taxonomy/partier/add?destination=valghalla/administration/partier">Tilføj parti</a>'),
    t('Fuldt partinavn'),
    t('Link til redigering af term'),
    t('Page'),
  );
  $export['parti_oversigt'] = $view;

  $view = new view();
  $view->name = 'roles';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Rolle oversigt';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Rolle oversigt';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'mere';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Udfør';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Gendan';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Sortér efter';
  $handler->display->display_options['exposed_form']['options']['sort_asc_label'] = 'Stigende';
  $handler->display->display_options['exposed_form']['options']['sort_desc_label'] = 'Faldende';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = 'Antal elementer';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- Alle -';
  $handler->display->display_options['pager']['options']['expose']['offset_label'] = 'Forskydning';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« første';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ forrige';
  $handler->display->display_options['pager']['options']['tags']['next'] = 'næste ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = 'sidste »';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Overskrift: Global: Tekstområde */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '<a class="btn btn-success" href="/node/add/roles?destination=valghalla/administration/roller">Tilføj rolle</a>';
  $handler->display->display_options['header']['area']['format'] = 'filtered_html';
  /* Felt: Indhold: Titel */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Felt: Indhold: Description */
  $handler->display->display_options['fields']['field_description']['id'] = 'field_description';
  $handler->display->display_options['fields']['field_description']['table'] = 'field_data_field_description';
  $handler->display->display_options['fields']['field_description']['field'] = 'field_description';
  $handler->display->display_options['fields']['field_description']['label'] = 'Beskrivelse';
  /* Felt: Indhold: Mødetidspunkt */
  $handler->display->display_options['fields']['field_meetingtime']['id'] = 'field_meetingtime';
  $handler->display->display_options['fields']['field_meetingtime']['table'] = 'field_data_field_meetingtime';
  $handler->display->display_options['fields']['field_meetingtime']['field'] = 'field_meetingtime';
  /* Felt: Indhold: Timer */
  $handler->display->display_options['fields']['field_role_hours']['id'] = 'field_role_hours';
  $handler->display->display_options['fields']['field_role_hours']['table'] = 'field_data_field_role_hours';
  $handler->display->display_options['fields']['field_role_hours']['field'] = 'field_role_hours';
  /* Felt: Indhold: Redigér-link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  /* Sorteringskriterie: Indhold: Oprettelsesdato */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filterkriterie: Indhold: Udgivet */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filterkriterie: Indhold: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'roles' => 'roles',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'valghalla/administration/roller';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Rolle oversigt';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $translatables['roles'] = array(
    t('Master'),
    t('Rolle oversigt'),
    t('mere'),
    t('Udfør'),
    t('Gendan'),
    t('Sortér efter'),
    t('Stigende'),
    t('Faldende'),
    t('Antal elementer'),
    t('- Alle -'),
    t('Forskydning'),
    t('« første'),
    t('‹ forrige'),
    t('næste ›'),
    t('sidste »'),
    t('<a class="btn btn-success" href="/node/add/roles?destination=valghalla/administration/roller">Tilføj rolle</a>'),
    t('Beskrivelse'),
    t('Mødetidspunkt'),
    t('Timer'),
    t('Redigér-link'),
    t('Page'),
  );
  $export['roles'] = $view;

  $view = new view();
  $view->name = 'valgsteder';
  $view->description = '';
  $view->tag = '';
  $view->base_table = 'node';
  $view->human_name = 'Valgsteder';
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
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Udfør';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Gendan';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Sortér efter';
  $handler->display->display_options['exposed_form']['options']['sort_asc_label'] = 'Stigende';
  $handler->display->display_options['exposed_form']['options']['sort_desc_label'] = 'Faldende';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = 'Antal elementer';
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
  /* Felt: Handler mangler eller er i stykker */
  $handler->display->display_options['fields']['entity_id_2']['id'] = 'entity_id_2';
  $handler->display->display_options['fields']['entity_id_2']['table'] = 'field_data_field_chairman';
  $handler->display->display_options['fields']['entity_id_2']['field'] = 'field_chairman';
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
  /* Felt: Handler mangler eller er i stykker */
  $handler->display->display_options['fields']['entity_id_8']['id'] = 'entity_id_8';
  $handler->display->display_options['fields']['entity_id_8']['table'] = 'field_data_field_volunteers_pr_party';
  $handler->display->display_options['fields']['entity_id_8']['field'] = 'field_volunteers_pr_party';
  /* Felt: Indhold: Valgkreds */
  $handler->display->display_options['fields']['entity_id_9']['id'] = 'entity_id_9';
  $handler->display->display_options['fields']['entity_id_9']['table'] = 'field_data_field_constituency';
  $handler->display->display_options['fields']['entity_id_9']['field'] = 'field_constituency';
  /* Felt: Handler mangler eller er i stykker */
  $handler->display->display_options['fields']['entity_id_10']['id'] = 'entity_id_10';
  $handler->display->display_options['fields']['entity_id_10']['table'] = 'field_data_field_dig_election';
  $handler->display->display_options['fields']['entity_id_10']['field'] = 'field_dig_election';
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

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block_1');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['style_options']['grouping'] = 'entity_id_9';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Felt: Indhold: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_type'] = 'h4';
  $handler->display->display_options['fields']['nid']['element_label_type'] = '0';
  $handler->display->display_options['fields']['nid']['element_wrapper_type'] = '0';
  /* Felt: Handler mangler eller er i stykker */
  $handler->display->display_options['fields']['entity_id_2']['id'] = 'entity_id_2';
  $handler->display->display_options['fields']['entity_id_2']['table'] = 'field_data_field_chairman';
  $handler->display->display_options['fields']['entity_id_2']['field'] = 'field_chairman';
  $handler->display->display_options['fields']['entity_id_2']['label'] = 'field_chairman';
  $handler->display->display_options['fields']['entity_id_2']['exclude'] = TRUE;
  /* Felt: Felt: Parti */
  $handler->display->display_options['fields']['entity_id_5']['id'] = 'entity_id_5';
  $handler->display->display_options['fields']['entity_id_5']['table'] = 'field_data_field_party';
  $handler->display->display_options['fields']['entity_id_5']['field'] = 'field_party';
  $handler->display->display_options['fields']['entity_id_5']['label'] = 'field_party';
  $handler->display->display_options['fields']['entity_id_5']['exclude'] = TRUE;
  /* Felt: Indhold: Valgkreds */
  $handler->display->display_options['fields']['entity_id_9']['id'] = 'entity_id_9';
  $handler->display->display_options['fields']['entity_id_9']['table'] = 'field_data_field_constituency';
  $handler->display->display_options['fields']['entity_id_9']['field'] = 'field_constituency';
  $handler->display->display_options['fields']['entity_id_9']['label'] = '';
  $handler->display->display_options['fields']['entity_id_9']['exclude'] = TRUE;
  $handler->display->display_options['fields']['entity_id_9']['element_label_type'] = '0';
  $handler->display->display_options['fields']['entity_id_9']['element_wrapper_type'] = 'h3';
  $handler->display->display_options['fields']['entity_id_9']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['entity_id_9']['type'] = 'node_reference_plain';
  /* Felt: Indhold: Titel */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['path'] = 'volunteers/station/[nid]';
  $handler->display->display_options['fields']['title']['element_label_type'] = '0';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_wrapper_type'] = 'h4';
  $handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Felt: Indhold: Digital valgliste */
  $handler->display->display_options['fields']['field_digital_election_list']['id'] = 'field_digital_election_list';
  $handler->display->display_options['fields']['field_digital_election_list']['table'] = 'field_data_field_digital_election_list';
  $handler->display->display_options['fields']['field_digital_election_list']['field'] = 'field_digital_election_list';
  $handler->display->display_options['fields']['field_digital_election_list']['exclude'] = TRUE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sorteringskriterie: Indhold: Titel */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filterkriterie: Indhold: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'polling_station' => 'polling_station',
  );

  /* Display: Side m  CPR */
  $handler = $view->new_display('page', 'Side m  CPR', 'page_1');
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
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['style_options']['grouping'] = 'entity_id_9';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['inline'] = array(
    'title' => 'title',
    'entity_id' => 'entity_id',
    'entity_id_2' => 'entity_id_2',
    'entity_id_3' => 'entity_id_3',
    'entity_id_5' => 'entity_id_5',
    'entity_id_6' => 'entity_id_6',
    'entity_id_7' => 'entity_id_7',
    'entity_id_8' => 'entity_id_8',
    'entity_id_9' => 'entity_id_9',
  );
  $handler->display->display_options['row_options']['separator'] = ' / ';
  $handler->display->display_options['row_options']['hide_empty'] = TRUE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Felt: Indhold: Digital valgliste */
  $handler->display->display_options['fields']['field_digital_election_list']['id'] = 'field_digital_election_list';
  $handler->display->display_options['fields']['field_digital_election_list']['table'] = 'field_data_field_digital_election_list';
  $handler->display->display_options['fields']['field_digital_election_list']['field'] = 'field_digital_election_list';
  $handler->display->display_options['fields']['field_digital_election_list']['label'] = '';
  $handler->display->display_options['fields']['field_digital_election_list']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_digital_election_list']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_digital_election_list']['alter']['text'] = '<div class="icon-digital-valglist">&nbsp;</div>';
  $handler->display->display_options['fields']['field_digital_election_list']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_digital_election_list']['element_default_classes'] = FALSE;
  /* Felt: Indhold: Titel */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['text'] = '[title] [field_digital_election_list]';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Felt: Indhold: Body */
  $handler->display->display_options['fields']['entity_id']['id'] = 'entity_id';
  $handler->display->display_options['fields']['entity_id']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['entity_id']['field'] = 'body';
  $handler->display->display_options['fields']['entity_id']['label'] = 'indhold';
  $handler->display->display_options['fields']['entity_id']['exclude'] = TRUE;
  /* Felt: Handler mangler eller er i stykker */
  $handler->display->display_options['fields']['entity_id_2']['id'] = 'entity_id_2';
  $handler->display->display_options['fields']['entity_id_2']['table'] = 'field_data_field_chairman';
  $handler->display->display_options['fields']['entity_id_2']['field'] = 'field_chairman';
  /* Felt: Indhold: Valgkontakt */
  $handler->display->display_options['fields']['entity_id_3']['id'] = 'entity_id_3';
  $handler->display->display_options['fields']['entity_id_3']['table'] = 'field_data_field_contact';
  $handler->display->display_options['fields']['entity_id_3']['field'] = 'field_contact';
  $handler->display->display_options['fields']['entity_id_3']['exclude'] = TRUE;
  /* Felt: Felt: Parti */
  $handler->display->display_options['fields']['entity_id_5']['id'] = 'entity_id_5';
  $handler->display->display_options['fields']['entity_id_5']['table'] = 'field_data_field_party';
  $handler->display->display_options['fields']['entity_id_5']['field'] = 'field_party';
  $handler->display->display_options['fields']['entity_id_5']['exclude'] = TRUE;
  /* Felt: Indhold: Andre kontaktoplysninger */
  $handler->display->display_options['fields']['entity_id_6']['id'] = 'entity_id_6';
  $handler->display->display_options['fields']['entity_id_6']['table'] = 'field_data_field_venue_contact';
  $handler->display->display_options['fields']['entity_id_6']['field'] = 'field_venue_contact';
  $handler->display->display_options['fields']['entity_id_6']['exclude'] = TRUE;
  /* Felt: Indhold: Lokalekontakt */
  $handler->display->display_options['fields']['entity_id_7']['id'] = 'entity_id_7';
  $handler->display->display_options['fields']['entity_id_7']['table'] = 'field_data_field_venue_contact_name';
  $handler->display->display_options['fields']['entity_id_7']['field'] = 'field_venue_contact_name';
  $handler->display->display_options['fields']['entity_id_7']['exclude'] = TRUE;
  /* Felt: Handler mangler eller er i stykker */
  $handler->display->display_options['fields']['entity_id_8']['id'] = 'entity_id_8';
  $handler->display->display_options['fields']['entity_id_8']['table'] = 'field_data_field_volunteers_pr_party';
  $handler->display->display_options['fields']['entity_id_8']['field'] = 'field_volunteers_pr_party';
  $handler->display->display_options['fields']['entity_id_8']['exclude'] = TRUE;
  /* Felt: Indhold: Valgkreds */
  $handler->display->display_options['fields']['entity_id_9']['id'] = 'entity_id_9';
  $handler->display->display_options['fields']['entity_id_9']['table'] = 'field_data_field_constituency';
  $handler->display->display_options['fields']['entity_id_9']['field'] = 'field_constituency';
  $handler->display->display_options['fields']['entity_id_9']['exclude'] = TRUE;
  $handler->display->display_options['path'] = 'valgsteder';

  /* Display: Side u CPR */
  $handler = $view->new_display('page', 'Side u CPR', 'page_2');
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
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['style_options']['grouping'] = 'entity_id_9';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['inline'] = array(
    'title' => 'title',
    'entity_id' => 'entity_id',
    'entity_id_2' => 'entity_id_2',
    'entity_id_3' => 'entity_id_3',
    'entity_id_5' => 'entity_id_5',
    'entity_id_6' => 'entity_id_6',
    'entity_id_7' => 'entity_id_7',
    'entity_id_8' => 'entity_id_8',
    'entity_id_9' => 'entity_id_9',
    'entity_id_10' => 'entity_id_10',
  );
  $handler->display->display_options['row_options']['separator'] = ' / ';
  $handler->display->display_options['row_options']['hide_empty'] = TRUE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Felt: Indhold: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Felt: Indhold: Digital valgliste */
  $handler->display->display_options['fields']['field_digital_election_list']['id'] = 'field_digital_election_list';
  $handler->display->display_options['fields']['field_digital_election_list']['table'] = 'field_data_field_digital_election_list';
  $handler->display->display_options['fields']['field_digital_election_list']['field'] = 'field_digital_election_list';
  $handler->display->display_options['fields']['field_digital_election_list']['label'] = '';
  $handler->display->display_options['fields']['field_digital_election_list']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_digital_election_list']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_digital_election_list']['alter']['text'] = '<span class="icon-digital-valglist">&nbsp;</span>';
  $handler->display->display_options['fields']['field_digital_election_list']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_digital_election_list']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_digital_election_list']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_digital_election_list']['empty_zero'] = TRUE;
  /* Felt: Indhold: Titel */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['text'] = '<a href="/valgsted_oversigt/valgsted/[nid]">[title] [field_digital_election_list]</a>
<!--<a href="/node/[nid]/valgstederU">[title] [field_digital_election_list]</a>-->';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Felt: Indhold: Body */
  $handler->display->display_options['fields']['entity_id']['id'] = 'entity_id';
  $handler->display->display_options['fields']['entity_id']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['entity_id']['field'] = 'body';
  $handler->display->display_options['fields']['entity_id']['label'] = 'indhold';
  $handler->display->display_options['fields']['entity_id']['exclude'] = TRUE;
  /* Felt: Handler mangler eller er i stykker */
  $handler->display->display_options['fields']['entity_id_2']['id'] = 'entity_id_2';
  $handler->display->display_options['fields']['entity_id_2']['table'] = 'field_data_field_chairman';
  $handler->display->display_options['fields']['entity_id_2']['field'] = 'field_chairman';
  /* Felt: Indhold: Valgkontakt */
  $handler->display->display_options['fields']['entity_id_3']['id'] = 'entity_id_3';
  $handler->display->display_options['fields']['entity_id_3']['table'] = 'field_data_field_contact';
  $handler->display->display_options['fields']['entity_id_3']['field'] = 'field_contact';
  $handler->display->display_options['fields']['entity_id_3']['exclude'] = TRUE;
  /* Felt: Felt: Parti */
  $handler->display->display_options['fields']['entity_id_5']['id'] = 'entity_id_5';
  $handler->display->display_options['fields']['entity_id_5']['table'] = 'field_data_field_party';
  $handler->display->display_options['fields']['entity_id_5']['field'] = 'field_party';
  $handler->display->display_options['fields']['entity_id_5']['exclude'] = TRUE;
  /* Felt: Indhold: Andre kontaktoplysninger */
  $handler->display->display_options['fields']['entity_id_6']['id'] = 'entity_id_6';
  $handler->display->display_options['fields']['entity_id_6']['table'] = 'field_data_field_venue_contact';
  $handler->display->display_options['fields']['entity_id_6']['field'] = 'field_venue_contact';
  $handler->display->display_options['fields']['entity_id_6']['exclude'] = TRUE;
  /* Felt: Indhold: Lokalekontakt */
  $handler->display->display_options['fields']['entity_id_7']['id'] = 'entity_id_7';
  $handler->display->display_options['fields']['entity_id_7']['table'] = 'field_data_field_venue_contact_name';
  $handler->display->display_options['fields']['entity_id_7']['field'] = 'field_venue_contact_name';
  $handler->display->display_options['fields']['entity_id_7']['exclude'] = TRUE;
  /* Felt: Handler mangler eller er i stykker */
  $handler->display->display_options['fields']['entity_id_8']['id'] = 'entity_id_8';
  $handler->display->display_options['fields']['entity_id_8']['table'] = 'field_data_field_volunteers_pr_party';
  $handler->display->display_options['fields']['entity_id_8']['field'] = 'field_volunteers_pr_party';
  $handler->display->display_options['fields']['entity_id_8']['exclude'] = TRUE;
  /* Felt: Indhold: Valgkreds */
  $handler->display->display_options['fields']['entity_id_9']['id'] = 'entity_id_9';
  $handler->display->display_options['fields']['entity_id_9']['table'] = 'field_data_field_constituency';
  $handler->display->display_options['fields']['entity_id_9']['field'] = 'field_constituency';
  $handler->display->display_options['fields']['entity_id_9']['exclude'] = TRUE;
  $handler->display->display_options['path'] = 'valgstederU';
  $translatables['valgsteder'] = array(
    t('Defaults'),
    t('mere'),
    t('Udfør'),
    t('Gendan'),
    t('Sortér efter'),
    t('Stigende'),
    t('Faldende'),
    t('Antal elementer'),
    t('- Alle -'),
    t('Forskydning'),
    t('« første'),
    t('‹ forrige'),
    t('næste ›'),
    t('sidste »'),
    t('indhold'),
    t('Handler i stykker field_data_field_chairman.field_chairman'),
    t('Valgkontakt'),
    t('Parti'),
    t('Andre kontaktoplysninger'),
    t('Lokalekontakt'),
    t('Handler i stykker field_data_field_volunteers_pr_party.field_volunteers_pr_party'),
    t('Valgkreds'),
    t('Handler i stykker field_data_field_dig_election.field_dig_election'),
    t('Alle'),
    t('Block'),
    t('Nid'),
    t('field_chairman'),
    t('field_party'),
    t('Digital valgliste'),
    t('Side m  CPR'),
    t('<div class="icon-digital-valglist">&nbsp;</div>'),
    t('[title] [field_digital_election_list]'),
    t('Side u CPR'),
    t('<span class="icon-digital-valglist">&nbsp;</span>'),
    t('<a href="/valgsted_oversigt/valgsted/[nid]">[title] [field_digital_election_list]</a>
<!--<a href="/node/[nid]/valgstederU">[title] [field_digital_election_list]</a>-->'),
  );
  $export['valgsteder'] = $view;

  return $export;
}
