<?php
  
function availability_views_data_alter(&$data) {

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



