<?php

$view = new view();
$view->name = 'missing_updates';
$view->description = '';
$view->tag = 'default';
$view->base_table = 'availability';
$view->human_name = 'Missing updates';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'Missing updates';
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['access']['perm'] = 'view availability';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'none';
$handler->display->display_options['style_plugin'] = 'list';
$handler->display->display_options['row_plugin'] = 'fields';
/* Field: User: Name */
$handler->display->display_options['fields']['name']['id'] = 'name';
$handler->display->display_options['fields']['name']['table'] = 'users';
$handler->display->display_options['fields']['name']['field'] = 'name';
$handler->display->display_options['fields']['name']['label'] = '';
$handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
/* Field: Availability Record: Week commencing */
$handler->display->display_options['fields']['start_date']['id'] = 'start_date';
$handler->display->display_options['fields']['start_date']['table'] = 'availability';
$handler->display->display_options['fields']['start_date']['field'] = 'start_date';
$handler->display->display_options['fields']['start_date']['label'] = '';
$handler->display->display_options['fields']['start_date']['exclude'] = TRUE;
$handler->display->display_options['fields']['start_date']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['start_date']['date_format'] = 'custom';
$handler->display->display_options['fields']['start_date']['custom_date_format'] = '\'jS F Y\'';
$handler->display->display_options['fields']['start_date']['second_date_format'] = 'long';
/* Filter criterion: Field: Week (field_availability_week:a_fr) */
$handler->display->display_options['filters']['field_availability_week_a_fr']['id'] = 'field_availability_week_a_fr';
$handler->display->display_options['filters']['field_availability_week_a_fr']['table'] = 'field_data_field_availability_week';
$handler->display->display_options['filters']['field_availability_week_a_fr']['field'] = 'field_availability_week_a_fr';
$handler->display->display_options['filters']['field_availability_week_a_fr']['operator'] = 'empty';
/* Filter criterion: Availability Record: Week commencing */
$handler->display->display_options['filters']['start_date']['id'] = 'start_date';
$handler->display->display_options['filters']['start_date']['table'] = 'availability';
$handler->display->display_options['filters']['start_date']['field'] = 'start_date';
$handler->display->display_options['filters']['start_date']['exposed'] = TRUE;
$handler->display->display_options['filters']['start_date']['expose']['operator_id'] = 'start_date_op';
$handler->display->display_options['filters']['start_date']['expose']['label'] = 'Monday commencing week';
$handler->display->display_options['filters']['start_date']['expose']['description'] = 'Select the week';
$handler->display->display_options['filters']['start_date']['expose']['operator'] = 'start_date_op';
$handler->display->display_options['filters']['start_date']['expose']['identifier'] = 'start_date';
$handler->display->display_options['filters']['start_date']['expose']['remember_roles'] = array(
  2 => '2',
  5 => 0,
  4 => 0,
  3 => 0,
  1 => 0,
  6 => 0,
  7 => 0,
);

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page');
$handler->display->display_options['path'] = 'missing-updates';
$handler->display->display_options['menu']['type'] = 'normal';
$handler->display->display_options['menu']['title'] = 'Missing updates';
$handler->display->display_options['menu']['weight'] = '20';
$handler->display->display_options['menu']['context'] = 0;
$handler->display->display_options['menu']['context_only_inline'] = 0;
$translatables['missing_updates'] = array(
  t('Master'),
  t('Missing updates'),
  t('more'),
  t('Apply'),
  t('Reset'),
  t('Sort by'),
  t('Asc'),
  t('Desc'),
  t('Monday commencing week'),
  t('Select the week'),
  t('Page'),
);