<?php

$view = new view();
$view->name = 'mediator_availability';
$view->description = '';
$view->tag = 'default';
$view->base_table = 'availability';
$view->human_name = 'Mediator Availability';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

$availability_settings= variable_get("availability_settings", array());
$start_limit = $availability_settings['availability_start_limit'];
$end_limit = $availability_settings['availability_end_limit'];

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'Mediator Availability';
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['group_by'] = TRUE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['access']['perm'] = 'view availability';
$handler->display->display_options['cache']['type'] = 'time';
$handler->display->display_options['cache']['results_lifespan'] = '1800';
$handler->display->display_options['cache']['results_lifespan_custom'] = '0';
$handler->display->display_options['cache']['output_lifespan'] = '3600';
$handler->display->display_options['cache']['output_lifespan_custom'] = '0';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = '10';
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
  'uid' => 'uid',
  'mo_m' => 'mo_m',
  'mo_a' => 'mo_a',
  'mo_e' => 'mo_e',
  'tu_m' => 'tu_m',
  'tu_a' => 'tu_a',
  'tu_e' => 'tu_e',
  'we_m' => 'we_m',
  'we_a' => 'we_a',
  'we_e' => 'we_e',
  'th_m' => 'th_m',
  'th_a' => 'th_a',
  'th_e' => 'th_e',
  'fr_m' => 'fr_m',
  'fr_a' => 'fr_a',
  'fr_e' => 'fr_e',
  'contextual_links' => 'contextual_links',
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
  'uid' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'mo_m' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'mo_a' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'mo_e' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'tu_m' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'tu_a' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'tu_e' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'we_m' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'we_a' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'we_e' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'th_m' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'th_a' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'th_e' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'fr_m' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'fr_a' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'fr_e' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'contextual_links' => array(
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
$handler->display->display_options['fields']['start_date']['alter']['alter_text'] = TRUE;
$handler->display->display_options['fields']['start_date']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['start_date']['date_format'] = 'custom';
$handler->display->display_options['fields']['start_date']['custom_date_format'] = 'jS F Y';
$handler->display->display_options['fields']['start_date']['second_date_format'] = 'long';
/* Field: COUNT(Availability Record: Uid) */
$handler->display->display_options['fields']['uid']['id'] = 'uid';
$handler->display->display_options['fields']['uid']['table'] = 'availability';
$handler->display->display_options['fields']['uid']['field'] = 'uid';
$handler->display->display_options['fields']['uid']['group_type'] = 'count';
$handler->display->display_options['fields']['uid']['exclude'] = TRUE;
$handler->display->display_options['fields']['uid']['element_label_colon'] = FALSE;
/* Field: SUM(Availability Record: Mo_m) */
$handler->display->display_options['fields']['mo_m']['id'] = 'mo_m';
$handler->display->display_options['fields']['mo_m']['table'] = 'availability';
$handler->display->display_options['fields']['mo_m']['field'] = 'mo_m';
$handler->display->display_options['fields']['mo_m']['group_type'] = 'sum';
$handler->display->display_options['fields']['mo_m']['label'] = 'Mon am';
$handler->display->display_options['fields']['mo_m']['alter']['path'] = 'mediator-availability/mo_m/[start_date]';
$handler->display->display_options['fields']['mo_m']['element_label_colon'] = FALSE;
/* Field: SUM(Availability Record: Mo_a) */
$handler->display->display_options['fields']['mo_a']['id'] = 'mo_a';
$handler->display->display_options['fields']['mo_a']['table'] = 'availability';
$handler->display->display_options['fields']['mo_a']['field'] = 'mo_a';
$handler->display->display_options['fields']['mo_a']['group_type'] = 'sum';
$handler->display->display_options['fields']['mo_a']['label'] = 'Mon pm';
$handler->display->display_options['fields']['mo_a']['alter']['path'] = 'mediator-availability/mo_a/[start_date]';
$handler->display->display_options['fields']['mo_a']['element_label_colon'] = FALSE;
/* Field: SUM(Availability Record: Mo_e) */
$handler->display->display_options['fields']['mo_e']['id'] = 'mo_e';
$handler->display->display_options['fields']['mo_e']['table'] = 'availability';
$handler->display->display_options['fields']['mo_e']['field'] = 'mo_e';
$handler->display->display_options['fields']['mo_e']['group_type'] = 'sum';
$handler->display->display_options['fields']['mo_e']['label'] = 'Mon eve';
$handler->display->display_options['fields']['mo_e']['alter']['path'] = 'mediator-availability/mo_e/[start_date]';
$handler->display->display_options['fields']['mo_e']['element_label_colon'] = FALSE;
/* Field: SUM(Availability Record: Tu_m) */
$handler->display->display_options['fields']['tu_m']['id'] = 'tu_m';
$handler->display->display_options['fields']['tu_m']['table'] = 'availability';
$handler->display->display_options['fields']['tu_m']['field'] = 'tu_m';
$handler->display->display_options['fields']['tu_m']['group_type'] = 'sum';
$handler->display->display_options['fields']['tu_m']['label'] = 'Tue am';
$handler->display->display_options['fields']['tu_m']['alter']['path'] = 'mediator-availability/tu_m/[start_date]';
$handler->display->display_options['fields']['tu_m']['element_label_colon'] = FALSE;
/* Field: SUM(Availability Record: Tu_a) */
$handler->display->display_options['fields']['tu_a']['id'] = 'tu_a';
$handler->display->display_options['fields']['tu_a']['table'] = 'availability';
$handler->display->display_options['fields']['tu_a']['field'] = 'tu_a';
$handler->display->display_options['fields']['tu_a']['group_type'] = 'sum';
$handler->display->display_options['fields']['tu_a']['label'] = 'Tue pm';
$handler->display->display_options['fields']['tu_a']['alter']['path'] = 'mediator-availability/tu_a/[start_date]';
$handler->display->display_options['fields']['tu_a']['element_label_colon'] = FALSE;
/* Field: SUM(Availability Record: Tu_e) */
$handler->display->display_options['fields']['tu_e']['id'] = 'tu_e';
$handler->display->display_options['fields']['tu_e']['table'] = 'availability';
$handler->display->display_options['fields']['tu_e']['field'] = 'tu_e';
$handler->display->display_options['fields']['tu_e']['group_type'] = 'sum';
$handler->display->display_options['fields']['tu_e']['label'] = 'Tue eve';
$handler->display->display_options['fields']['tu_e']['alter']['path'] = 'mediator-availability/tu_e/[start_date]';
$handler->display->display_options['fields']['tu_e']['element_label_colon'] = FALSE;
/* Field: SUM(Availability Record: We_m) */
$handler->display->display_options['fields']['we_m']['id'] = 'we_m';
$handler->display->display_options['fields']['we_m']['table'] = 'availability';
$handler->display->display_options['fields']['we_m']['field'] = 'we_m';
$handler->display->display_options['fields']['we_m']['group_type'] = 'sum';
$handler->display->display_options['fields']['we_m']['label'] = 'Wed am';
$handler->display->display_options['fields']['we_m']['alter']['path'] = 'mediator-availability/we_m/[start_date]';
$handler->display->display_options['fields']['we_m']['element_label_colon'] = FALSE;
/* Field: SUM(Availability Record: We_a) */
$handler->display->display_options['fields']['we_a']['id'] = 'we_a';
$handler->display->display_options['fields']['we_a']['table'] = 'availability';
$handler->display->display_options['fields']['we_a']['field'] = 'we_a';
$handler->display->display_options['fields']['we_a']['group_type'] = 'sum';
$handler->display->display_options['fields']['we_a']['label'] = 'Wed pm';
$handler->display->display_options['fields']['we_a']['alter']['path'] = 'mediator-availability/we_a/[start_date]';
$handler->display->display_options['fields']['we_a']['element_label_colon'] = FALSE;
/* Field: SUM(Availability Record: We_e) */
$handler->display->display_options['fields']['we_e']['id'] = 'we_e';
$handler->display->display_options['fields']['we_e']['table'] = 'availability';
$handler->display->display_options['fields']['we_e']['field'] = 'we_e';
$handler->display->display_options['fields']['we_e']['group_type'] = 'sum';
$handler->display->display_options['fields']['we_e']['label'] = 'Wed eve';
$handler->display->display_options['fields']['we_e']['alter']['path'] = 'mediator-availability/we_e/[start_date]';
$handler->display->display_options['fields']['we_e']['element_label_colon'] = FALSE;
/* Field: SUM(Availability Record: Th_m) */
$handler->display->display_options['fields']['th_m']['id'] = 'th_m';
$handler->display->display_options['fields']['th_m']['table'] = 'availability';
$handler->display->display_options['fields']['th_m']['field'] = 'th_m';
$handler->display->display_options['fields']['th_m']['group_type'] = 'sum';
$handler->display->display_options['fields']['th_m']['label'] = 'Thur am';
$handler->display->display_options['fields']['th_m']['alter']['path'] = 'mediator-availability/th_m/[start_date]';
$handler->display->display_options['fields']['th_m']['element_label_colon'] = FALSE;
/* Field: SUM(Availability Record: Th_a) */
$handler->display->display_options['fields']['th_a']['id'] = 'th_a';
$handler->display->display_options['fields']['th_a']['table'] = 'availability';
$handler->display->display_options['fields']['th_a']['field'] = 'th_a';
$handler->display->display_options['fields']['th_a']['group_type'] = 'sum';
$handler->display->display_options['fields']['th_a']['label'] = 'Thur pm';
$handler->display->display_options['fields']['th_a']['alter']['path'] = 'mediator-availability/th_a/[start_date]';
$handler->display->display_options['fields']['th_a']['element_label_colon'] = FALSE;
/* Field: SUM(Availability Record: Th_e) */
$handler->display->display_options['fields']['th_e']['id'] = 'th_e';
$handler->display->display_options['fields']['th_e']['table'] = 'availability';
$handler->display->display_options['fields']['th_e']['field'] = 'th_e';
$handler->display->display_options['fields']['th_e']['group_type'] = 'sum';
$handler->display->display_options['fields']['th_e']['label'] = 'Thur eve';
$handler->display->display_options['fields']['th_e']['alter']['path'] = 'mediator-availability/th_e/[start_date]';
$handler->display->display_options['fields']['th_e']['element_label_colon'] = FALSE;
/* Field: SUM(Availability Record: Fr_m) */
$handler->display->display_options['fields']['fr_m']['id'] = 'fr_m';
$handler->display->display_options['fields']['fr_m']['table'] = 'availability';
$handler->display->display_options['fields']['fr_m']['field'] = 'fr_m';
$handler->display->display_options['fields']['fr_m']['group_type'] = 'sum';
$handler->display->display_options['fields']['fr_m']['label'] = 'Fri am';
$handler->display->display_options['fields']['fr_m']['alter']['path'] = 'mediator-availability/fr_m/[start_date]';
/* Field: SUM(Availability Record: Fr_a) */
$handler->display->display_options['fields']['fr_a']['id'] = 'fr_a';
$handler->display->display_options['fields']['fr_a']['table'] = 'availability';
$handler->display->display_options['fields']['fr_a']['field'] = 'fr_a';
$handler->display->display_options['fields']['fr_a']['group_type'] = 'sum';
$handler->display->display_options['fields']['fr_a']['label'] = 'Fri pm';
$handler->display->display_options['fields']['fr_a']['alter']['path'] = 'mediator-availability/fr_a/[start_date]';
$handler->display->display_options['fields']['fr_a']['element_label_colon'] = FALSE;
/* Field: SUM(Availability Record: Fr_e) */
$handler->display->display_options['fields']['fr_e']['id'] = 'fr_e';
$handler->display->display_options['fields']['fr_e']['table'] = 'availability';
$handler->display->display_options['fields']['fr_e']['field'] = 'fr_e';
$handler->display->display_options['fields']['fr_e']['group_type'] = 'sum';
$handler->display->display_options['fields']['fr_e']['label'] = 'Fri eve';
$handler->display->display_options['fields']['fr_e']['alter']['path'] = 'mediator-availability/fr_e/[start_date]';
$handler->display->display_options['fields']['fr_e']['element_label_colon'] = FALSE;
/* Filter criterion: Availability Record: Week commencing */
$handler->display->display_options['filters']['start_date_1']['id'] = 'start_date_1';
$handler->display->display_options['filters']['start_date_1']['table'] = 'availability';
$handler->display->display_options['filters']['start_date_1']['field'] = 'start_date';
$handler->display->display_options['filters']['start_date_1']['operator'] = '<=';
$handler->display->display_options['filters']['start_date_1']['value']['value'] = '+' . ($end_limit + 8) . ' days';
$handler->display->display_options['filters']['start_date_1']['value']['type'] = 'offset';
$handler->display->display_options['filters']['start_date_1']['expose']['operator_id'] = 'start_date_1_op';
$handler->display->display_options['filters']['start_date_1']['expose']['label'] = 'Week commencing';
$handler->display->display_options['filters']['start_date_1']['expose']['operator'] = 'start_date_1_op';
$handler->display->display_options['filters']['start_date_1']['expose']['identifier'] = 'start_date_1';
/* Filter criterion: Availability Record: Week commencing */
$handler->display->display_options['filters']['start_date']['id'] = 'start_date';
$handler->display->display_options['filters']['start_date']['table'] = 'availability';
$handler->display->display_options['filters']['start_date']['field'] = 'start_date';
$handler->display->display_options['filters']['start_date']['operator'] = '>=';
$handler->display->display_options['filters']['start_date']['value']['value'] = '-' . $start_limit . ' days';
$handler->display->display_options['filters']['start_date']['value']['type'] = 'offset';

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page');
$handler->display->display_options['path'] = 'mediator-availability';
$handler->display->display_options['menu']['type'] = 'normal';
$handler->display->display_options['menu']['title'] = 'Mediator availability';
$handler->display->display_options['menu']['description'] = 'Table summarising mediator availability';
$handler->display->display_options['menu']['weight'] = '0';
$handler->display->display_options['menu']['context'] = 0;
$handler->display->display_options['menu']['context_only_inline'] = 0;
$translatables['mediator_availability'] = array(
  t('Master'),
  t('Mediator Availability'),
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
  t('Uid'),
  t('.'),
  t(','),
  t('Mon am'),
  t('Mon pm'),
  t('Mon eve'),
  t('Tue am'),
  t('Tue pm'),
  t('Tue eve'),
  t('Wed am'),
  t('Wed pm'),
  t('Wed eve'),
  t('Thur am'),
  t('Thur pm'),
  t('Thur eve'),
  t('Fri am'),
  t('Fri pm'),
  t('Fri eve'),
  t('Week commencing'),
  t('Page'),
);

