<?php

$view = new view();
$view->name = 'meetings';
$view->description = '';
$view->tag = 'default';
$view->base_table = 'node';
$view->human_name = 'Meetings';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'Case meetings';
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
  'title_1' => 'title_1',
  'title' => 'title',
  'field_meeting_date' => 'field_meeting_date',
  'field_meeting_type' => 'field_meeting_type',
);
/* Relationship: Entity Reference: Referencing entity */
$handler->display->display_options['relationships']['reverse_field_meeting_node']['id'] = 'reverse_field_meeting_node';
$handler->display->display_options['relationships']['reverse_field_meeting_node']['table'] = 'node';
$handler->display->display_options['relationships']['reverse_field_meeting_node']['field'] = 'reverse_field_meeting_node';
/* Field: Content: Reference */
$handler->display->display_options['fields']['field_reference']['id'] = 'field_reference';
$handler->display->display_options['fields']['field_reference']['table'] = 'field_data_field_reference';
$handler->display->display_options['fields']['field_reference']['field'] = 'field_reference';
$handler->display->display_options['fields']['field_reference']['relationship'] = 'reverse_field_meeting_node';
$handler->display->display_options['fields']['field_reference']['label'] = '';
$handler->display->display_options['fields']['field_reference']['alter']['alter_text'] = TRUE;
$handler->display->display_options['fields']['field_reference']['alter']['text'] = '<br>Case [field_reference]';
$handler->display->display_options['fields']['field_reference']['element_label_colon'] = FALSE;
/* Field: Content: Title */
$handler->display->display_options['fields']['title_1']['id'] = 'title_1';
$handler->display->display_options['fields']['title_1']['table'] = 'node';
$handler->display->display_options['fields']['title_1']['field'] = 'title';
$handler->display->display_options['fields']['title_1']['relationship'] = 'reverse_field_meeting_node';
$handler->display->display_options['fields']['title_1']['label'] = '';
$handler->display->display_options['fields']['title_1']['alter']['alter_text'] = TRUE;
$handler->display->display_options['fields']['title_1']['alter']['text'] = '[title_1]<br>';
$handler->display->display_options['fields']['title_1']['element_label_colon'] = FALSE;
/* Field: Content: Title */
$handler->display->display_options['fields']['title']['id'] = 'title';
$handler->display->display_options['fields']['title']['table'] = 'node';
$handler->display->display_options['fields']['title']['field'] = 'title';
$handler->display->display_options['fields']['title']['label'] = '';
$handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
$handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
/* Field: Content: Meeting date */
$handler->display->display_options['fields']['field_meeting_date']['id'] = 'field_meeting_date';
$handler->display->display_options['fields']['field_meeting_date']['table'] = 'field_data_field_meeting_date';
$handler->display->display_options['fields']['field_meeting_date']['field'] = 'field_meeting_date';
$handler->display->display_options['fields']['field_meeting_date']['label'] = '';
$handler->display->display_options['fields']['field_meeting_date']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['field_meeting_date']['settings'] = array(
  'format_type' => 'short',
  'fromto' => 'both',
  'multiple_number' => '',
  'multiple_from' => '',
  'multiple_to' => '',
);
/* Field: Content: Meeting type */
$handler->display->display_options['fields']['field_meeting_type']['id'] = 'field_meeting_type';
$handler->display->display_options['fields']['field_meeting_type']['table'] = 'field_data_field_meeting_type';
$handler->display->display_options['fields']['field_meeting_type']['field'] = 'field_meeting_type';
$handler->display->display_options['fields']['field_meeting_type']['label'] = '';
$handler->display->display_options['fields']['field_meeting_type']['alter']['alter_text'] = TRUE;
$handler->display->display_options['fields']['field_meeting_type']['alter']['text'] = '([field_meeting_type])';
$handler->display->display_options['fields']['field_meeting_type']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['field_meeting_type']['type'] = 'taxonomy_term_reference_plain';
/* Sort criterion: Content: Meeting date (field_meeting_date) */
$handler->display->display_options['sorts']['field_meeting_date_value']['id'] = 'field_meeting_date_value';
$handler->display->display_options['sorts']['field_meeting_date_value']['table'] = 'field_data_field_meeting_date';
$handler->display->display_options['sorts']['field_meeting_date_value']['field'] = 'field_meeting_date_value';
$handler->display->display_options['sorts']['field_meeting_date_value']['order'] = 'DESC';
$handler->display->display_options['sorts']['field_meeting_date_value']['expose']['label'] = 'Meeting date (field_meeting_date)';
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
  'meeting' => 'meeting',
);

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page');
$handler->display->display_options['path'] = 'meetings-list';
$handler->display->display_options['menu']['type'] = 'normal';
$handler->display->display_options['menu']['title'] = 'Meeting list';
$handler->display->display_options['menu']['description'] = 'Listing of all scheduled mediation meetings';
$handler->display->display_options['menu']['weight'] = '0';
$handler->display->display_options['menu']['context'] = 0;
$handler->display->display_options['menu']['context_only_inline'] = 0;
