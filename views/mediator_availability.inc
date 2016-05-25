<?php

$view = new view();
$view->name = 'mediator_availability';
$view->description = '';
$view->tag = 'default';
$view->base_table = 'availability';
$view->human_name = 'Mediator availability';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'Mediator availability';
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['access']['perm'] = 'view availability';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'some';
$handler->display->display_options['pager']['options']['items_per_page'] = '30';
$handler->display->display_options['style_plugin'] = 'table';
$handler->display->display_options['style_options']['grouping'] = array(
  0 => array(
    'field' => 'start_date',
    'rendered' => 0,
    'rendered_strip' => 0,
  ),
);
$handler->display->display_options['style_options']['row_class_special'] = FALSE;
$handler->display->display_options['style_options']['columns'] = array(
  'start_date' => 'start_date',
  'field_availability_week' => 'field_availability_week',
);
$handler->display->display_options['style_options']['default'] = 'start_date';
$handler->display->display_options['style_options']['info'] = array(
  'start_date' => array(
    'sortable' => 1,
    'default_sort_order' => 'desc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'field_availability_week' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
);
$handler->display->display_options['style_options']['override'] = FALSE;
/* Field: Availability Record: Week commencing */
$handler->display->display_options['fields']['start_date']['id'] = 'start_date';
$handler->display->display_options['fields']['start_date']['table'] = 'availability';
$handler->display->display_options['fields']['start_date']['field'] = 'start_date';
$handler->display->display_options['fields']['start_date']['label'] = '';
$handler->display->display_options['fields']['start_date']['exclude'] = TRUE;
$handler->display->display_options['fields']['start_date']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['start_date']['date_format'] = 'custom';
$handler->display->display_options['fields']['start_date']['custom_date_format'] = 'jS F Y';
$handler->display->display_options['fields']['start_date']['second_date_format'] = 'long';
/* Field: Field: Week */
$handler->display->display_options['fields']['field_availability_week']['id'] = 'field_availability_week';
$handler->display->display_options['fields']['field_availability_week']['table'] = 'field_data_field_availability_week';
$handler->display->display_options['fields']['field_availability_week']['field'] = 'field_availability_week';
$handler->display->display_options['fields']['field_availability_week']['label'] = '';
$handler->display->display_options['fields']['field_availability_week']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['field_availability_week']['click_sort_column'] = 'notes';
$handler->display->display_options['fields']['field_availability_week']['type'] = 'availability_week_row';

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page');
$handler->display->display_options['path'] = 'mediator-availability';
$handler->display->display_options['menu']['type'] = 'normal';
$handler->display->display_options['menu']['title'] = 'Mediator availability';
$handler->display->display_options['menu']['weight'] = '0';
$handler->display->display_options['menu']['context'] = 0;
$handler->display->display_options['menu']['context_only_inline'] = 0;
$translatables['mediator_availability'] = array(
  t('Master'),
  t('Mediator availability'),
  t('more'),
  t('Apply'),
  t('Reset'),
  t('Sort by'),
  t('Asc'),
  t('Desc'),
  t('Page'),
);