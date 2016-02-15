<?php

$view = new view();
$view->name = 'case_list';
$view->description = '';
$view->tag = 'default';
$view->base_table = 'node';
$view->human_name = 'Case List';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'Mediation Case List';
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['access']['perm'] = 'view availability';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = '10';
$handler->display->display_options['style_plugin'] = 'default';
$handler->display->display_options['row_plugin'] = 'fields';
$handler->display->display_options['row_options']['inline'] = array(
  'field_reference' => 'field_reference',
  'title' => 'title',
);
$handler->display->display_options['row_options']['separator'] = '-';
/* Field: Content: Reference */
$handler->display->display_options['fields']['field_reference']['id'] = 'field_reference';
$handler->display->display_options['fields']['field_reference']['table'] = 'field_data_field_reference';
$handler->display->display_options['fields']['field_reference']['field'] = 'field_reference';
$handler->display->display_options['fields']['field_reference']['label'] = 'Case';
$handler->display->display_options['fields']['field_reference']['element_label_colon'] = FALSE;
/* Field: Content: Title */
$handler->display->display_options['fields']['title']['id'] = 'title';
$handler->display->display_options['fields']['title']['table'] = 'node';
$handler->display->display_options['fields']['title']['field'] = 'title';
$handler->display->display_options['fields']['title']['label'] = '';
$handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
$handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
/* Sort criterion: Content: Post date */
$handler->display->display_options['sorts']['created']['id'] = 'created';
$handler->display->display_options['sorts']['created']['table'] = 'node';
$handler->display->display_options['sorts']['created']['field'] = 'created';
$handler->display->display_options['sorts']['created']['order'] = 'DESC';
/* Filter criterion: Content: Published */
$handler->display->display_options['filters']['status']['id'] = 'status';
$handler->display->display_options['filters']['status']['table'] = 'node';
$handler->display->display_options['filters']['status']['field'] = 'status';
$handler->display->display_options['filters']['status']['value'] = 1;
$handler->display->display_options['filters']['status']['group'] = 1;
$handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
/* Filter criterion: Content: Type */
$handler->display->display_options['filters']['type']['id'] = 'type';
$handler->display->display_options['filters']['type']['table'] = 'node';
$handler->display->display_options['filters']['type']['field'] = 'type';
$handler->display->display_options['filters']['type']['value'] = array(
  'mediation_case' => 'mediation_case',
);
/* Filter criterion: Content: Case status (field_case_status) */
$handler->display->display_options['filters']['field_case_status_tid']['id'] = 'field_case_status_tid';
$handler->display->display_options['filters']['field_case_status_tid']['table'] = 'field_data_field_case_status';
$handler->display->display_options['filters']['field_case_status_tid']['field'] = 'field_case_status_tid';
$handler->display->display_options['filters']['field_case_status_tid']['value'] = array(
  4 => '4',
);
$handler->display->display_options['filters']['field_case_status_tid']['exposed'] = TRUE;
$handler->display->display_options['filters']['field_case_status_tid']['expose']['operator_id'] = 'field_case_status_tid_op';
$handler->display->display_options['filters']['field_case_status_tid']['expose']['label'] = 'Case status';
$handler->display->display_options['filters']['field_case_status_tid']['expose']['operator'] = 'field_case_status_tid_op';
$handler->display->display_options['filters']['field_case_status_tid']['expose']['identifier'] = 'field_case_status_tid';
$handler->display->display_options['filters']['field_case_status_tid']['expose']['remember'] = TRUE;
$handler->display->display_options['filters']['field_case_status_tid']['expose']['multiple'] = TRUE;
$handler->display->display_options['filters']['field_case_status_tid']['expose']['remember_roles'] = array(
  2 => 0,
  3 => '3',
  4 => '4',
  1 => 0,
  5 => 0,
  6 => 0,
);
$handler->display->display_options['filters']['field_case_status_tid']['type'] = 'select';
$handler->display->display_options['filters']['field_case_status_tid']['vocabulary'] = 'case_status';

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page');
$handler->display->display_options['path'] = 'case-list';
$handler->display->display_options['menu']['type'] = 'normal';
$handler->display->display_options['menu']['title'] = 'Case list';
$handler->display->display_options['menu']['weight'] = '0';
$handler->display->display_options['menu']['context'] = 0;
$handler->display->display_options['menu']['context_only_inline'] = 0;
