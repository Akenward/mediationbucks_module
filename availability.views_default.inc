<?php
  
/**
 *  Implements hook_views_default_views to load views code held as .inc files in views sub-folder
 */
function availability_views_default_views() {
  // Check for all view files in views directory
  $files = file_scan_directory(drupal_get_path('module', 'availability') . '/views', '/.*\.inc$/');
  $views = array();
  // Add each view to list of views
  foreach ($files as $filepath => $file) {
    require $filepath;
    if (isset($view)) {
      $views[$view->name] = $view;
    }
  }

  // Return array of default views.
  return $views;
}

/**
 *  Implements hook_views_data_alter to set up entity relationships
 */  
function availability_views_data_alter(&$data) {
  dpm($data);

  // Join the availability table to the users table via the uid key	
  $data['users']['table']['join'] = array(
    'availability' => array(
      'left_field' => 'uid',
      'field' => 'uid',
    ),
    'updates' => array(
      'left_field' => 'uid',
      'field' => 'uid',
    ),
  );
  
  $data['availability']['start_date'] = array(
    'is date' => TRUE,
    'title' => t('Week commencing'),
    'help' => t('Monday commencing week'),

    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),

    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_date',
    ),
  );
  
  $data['updates']['start_date'] = array(
    'is date' => TRUE,
    'title' => t('Week commencing'),
    'help' => t('Monday commencing week'),

    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_date',
    ),
  );
}



