<?php

/**
  * View for showing potential availability updates not yet received for the selected period
 */
$view = new view();
$view->name = 'missing_updates';
$view->description = '';
$view->tag = 'default';
$view->base_table = 'updates';
$view->human_name = 'Missing Updates';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'Missing Updates';
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['access']['perm'] = 'view availability';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = '0';
$handler->display->display_options['pager']['options']['offset'] = '0';
$handler->display->display_options['pager']['options']['id'] = '0';
$handler->display->display_options['pager']['options']['quantity'] = '9';
$handler->display->display_options['style_plugin'] = 'list';
$handler->display->display_options['row_plugin'] = 'fields';
/* Field: Update Record: Mediator_name */
$handler->display->display_options['fields']['mediator_name']['id'] = 'mediator_name';
$handler->display->display_options['fields']['mediator_name']['table'] = 'updates';
$handler->display->display_options['fields']['mediator_name']['field'] = 'mediator_name';
$handler->display->display_options['fields']['mediator_name']['label'] = '';
$handler->display->display_options['fields']['mediator_name']['element_label_colon'] = FALSE;
/* Field: Update Record: Week commencing */
$handler->display->display_options['fields']['start_date']['id'] = 'start_date';
$handler->display->display_options['fields']['start_date']['table'] = 'updates';
$handler->display->display_options['fields']['start_date']['field'] = 'start_date';
$handler->display->display_options['fields']['start_date']['label'] = '';
$handler->display->display_options['fields']['start_date']['exclude'] = TRUE;
$handler->display->display_options['fields']['start_date']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['start_date']['date_format'] = 'short';
$handler->display->display_options['fields']['start_date']['second_date_format'] = 'long';
/* Sort criterion: Global: Random */
$handler->display->display_options['sorts']['random']['id'] = 'random';
$handler->display->display_options['sorts']['random']['table'] = 'views';
$handler->display->display_options['sorts']['random']['field'] = 'random';
$handler->display->display_options['sorts']['random']['expose']['label'] = 'Random';
/* Filter criterion: Update Record: Report_status */
$handler->display->display_options['filters']['report_status']['id'] = 'report_status';
$handler->display->display_options['filters']['report_status']['table'] = 'updates';
$handler->display->display_options['filters']['report_status']['field'] = 'report_status';
$handler->display->display_options['filters']['report_status']['value']['value'] = '0';
/* Filter criterion: Update Record: Week commencing */
$handler->display->display_options['filters']['start_date']['id'] = 'start_date';
$handler->display->display_options['filters']['start_date']['table'] = 'updates';
$handler->display->display_options['filters']['start_date']['field'] = 'start_date';
$handler->display->display_options['filters']['start_date']['value']['value'] = '0';
$handler->display->display_options['filters']['start_date']['exposed'] = TRUE;
$handler->display->display_options['filters']['start_date']['expose']['operator_id'] = 'start_date_op';
$handler->display->display_options['filters']['start_date']['expose']['label'] = 'Monday commencing week';
$handler->display->display_options['filters']['start_date']['expose']['description'] = 'Select the week';
$handler->display->display_options['filters']['start_date']['expose']['operator'] = 'start_date_op';
$handler->display->display_options['filters']['start_date']['expose']['identifier'] = 'start_date';
$handler->display->display_options['filters']['start_date']['expose']['remember_roles'] = array(
  2 => '2',
  3 => 0,
  4 => 0,
  5 => 0,
  6 => 0,
  1 => 0,
);

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page');
$handler->display->display_options['path'] = 'missing-updates';
$handler->display->display_options['menu']['type'] = 'normal';
$handler->display->display_options['menu']['title'] = 'Missing updates';
$handler->display->display_options['menu']['description'] = 'Mediators with missed updates';
$handler->display->display_options['menu']['weight'] = '0';
$handler->display->display_options['menu']['context'] = 0;
$handler->display->display_options['menu']['context_only_inline'] = 0;
$translatables['missing_updates'] = array(
  t('Master'),
  t('Missing Updates'),
  t('more'),
  t('Apply'),
  t('Reset'),
  t('Sort by'),
  t('Asc'),
  t('Desc'),
  t('Items per page'),
  t('- All -'),
  t('Offset'),
  t('« first'),
  t('‹ previous'),
  t('next ›'),
  t('last »'),
  t('Random'),
  t('Monday commencing week'),
  t('Select the week'),
  t('Page'),
);
