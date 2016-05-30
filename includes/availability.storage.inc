<?php

module_load_include('module', 'availability_week');

interface AvailabilityStorageInterface {
  	
  public function availabilityRetrieveEntity($date = NULL);
  
  public function availabilitySaveEntity($form, $form_state, $repeat_weeks = 0);
  
  public function availabilityHousekeeping();
  
}
class AvailabilityStorage implements AvailabilityStorageInterface {
  
  protected $context;
	
  function __construct($context){
  	$this->context = $context;
  }
			
  public function availabilitySaveEntity($form, $form_state, $repeat_weeks = 0) {
	$entity = $form_state['availability_current_entity'];
	$monday = $this->context->availabilityCurrentMonday();
	$report = array();
	$items = array();
	$instance = field_info_instance('availability', 'field_availability_week', 'availability');
    $field = field_info_field_by_id($instance['field_id']);
	field_default_extract_form_values('availability', $entity, $field, $instance, LANGUAGE_NONE, $items, $form, $form_state);
	$e_wrapper = entity_metadata_wrapper('availability', $entity);
	foreach($items as $delta => $item){
	  $e_wrapper->field_availability_week->set($item);
	}
	$report[] = entity_save('availability', $entity);
	for ($i=1; $i<=$repeat_weeks; $i++) {
	  $monday->modify('+1 week');
	  $entity = $this -> availabilityRetrieveEntity($monday);
	  $e_wrapper = entity_metadata_wrapper('availability', $entity);
	  foreach($items as $delta => $item){
	    $e_wrapper->field_availability_week->set($item);
	  }
	  $report[] = entity_save('availability', $entity);
	}
	return $report;
  }
		
  public function availabilityRetrieveEntity($date = NULL) {
  	$mediator_uid = $this->context->availabilityCurrentMediator()->uid;
	if ($date) {
	  $date_stamp = $date->format('U') ;
	}
	else {
	  $date_stamp = $this->context->availabilityCurrentMonday()->format('U') ;
	}
	$query = new EntityFieldQuery;
    $dvids = $query
      ->entityCondition('entity_type', 'availability')
      ->propertyCondition('uid', $mediator_uid)
      ->propertyCondition('start_date', $date_stamp)
	  ->propertyOrderBy('start_date', 'DESC')
      ->execute();
	  
    if (sizeof($dvids) > 0 && sizeof($dvids['availability']) > 0) {
      reset($dvids['availability']);
	  $entities = entity_load('availability', array(key($dvids['availability'])));
	  reset($entities);
	  $vid = key($entities);
	  $entity = $entities[$vid];
	  $entity->is_new = FALSE;
    }
	else {
	  $entity = $this->_blank_availability_record($mediator_uid, $date_stamp);
	  $entity->is_new = TRUE;
	}
	return $entity;
  }
  
  public function availabilityHousekeeping() {
  	$date_stamp = $this->context->availabilityExpiryDate()->format("U");
  	$query = new EntityFieldQuery;
    $dvids = $query
      ->entityCondition('entity_type', 'availability')
      ->propertyCondition('start_date', $date_stamp, '<')
      ->execute();
	if (sizeof($dvids) > 0 && sizeof($dvids['availability']) > 0) {
      $report = entity_delete_multiple('availability', array_keys($dvids['availability']));
	  $number = count(array_keys($dvids['availability']));
	  if ($report === FALSE) {
	  	watchdog('availability', 'Failure to delete expired availability records in Cron run.', array(), WATCHDOG_ERROR);
	  }
	  else {
	  	watchdog('availability', $number . ' expired availability records deleted by Cron.', array(), WATCHDOG_INFO);
	  }
	}
	// Check if there are availability records set up for each week in the current range for the correct number of live mediators
	// If not, check each individual mediator for that week and create a new record for any that are missing.  These new records
	// will not have field_availability week set so we can use this field set/unset to report on updates. 
	
	// Count the number of live mediators
	$query = new EntityFieldQuery;
    $duids = $query
      ->entityCondition('entity_type', 'user')
      ->propertyCondition('status', 1)
      ->execute();
	  
	if (isset($duids['user']) >= 1 && count($duids['user']) >= 1) {
	  $results = entity_load('user', array_keys($duids['user']));
      $mediators = array_filter($results, array($this,'_test_mediator'));
      $number_of_mediators = count($mediators);
    }
    else {
	  $mediators = array();
	  $number_of_mediators = 0;
	}
	// Loop through the weeks in range
	foreach ($this->context->availabilityCurrentWeeks() as $monday) {
	  $report = array();
	  $query = new EntityFieldQuery;
      $dvids = $query
        ->entityCondition('entity_type', 'availability')
        ->propertyCondition('start_date', $monday->format('U'))
        ->execute();
	  $number_of_records = (isset($dvids['availability'])) ? count($dvids['availability']) : 0 ;
	  // Compare the number of live mediator records with number of availability records for the week
	  // and go into a detailed check if there is a shortfall.  If there are more records than mediators,
	  // then mediator records have been closed.
	  if ($number_of_records < $number_of_mediators) {
		// Loop through the live mediators testing whether they have a record for the week we're checking 
	    foreach ($mediators as $mediator) {
	      $query = new EntityFieldQuery;
	  	  $daids = $query
            ->entityCondition('entity_type', 'availability')
            ->propertyCondition('start_date', $monday->format('U'))
		    ->propertyCondition('uid', $mediator->uid)
            ->execute();
		  
		  // If there is not a record, create one with no field_availability_week value and save it
		  if (empty($daids)) {
		  	$availability_entity = $this->_blank_availability_record($mediator->uid, $monday->format('U'), TRUE);
			$availability_entity->is_new = TRUE;
			$report[] = entity_save('availability', $availability_entity);
		  }
	    }
		watchdog('availability', count($report) . 
		  ' new blank availability records created by Cron for week commencing ' . 
			$monday->format('l, jS M'), array(), WATCHDOG_INFO);
	  }
	}
  }
  
  protected function _blank_availability_record($mediator_uid, $date_stamp, $no_week = FALSE) {
  	$periods = availability_periods_factory();
  	$values = array(
      'uid' => $mediator_uid,
      'start_date' => $date_stamp,
    );
	
	$entity = entity_create('availability', $values);
	if (!$no_week) {
      $e_wrapper = entity_metadata_wrapper('availability', $entity);
	
	  $field_values = array();
      foreach ($periods -> availabilityTimes() as $m_t => $m_time) {
  	    foreach ($periods -> availabilityDays() as $m_d => $m_day) {
  	      $field_values[$m_t.'_'.$m_d] = 2;
        }
      }
	  $field_values['notes'] = '';
      $e_wrapper->field_availability_week->set($field_values);
	}
	return $entity;
  }
  
  protected function _test_mediator($test_user) {
  if (in_array('mediator', $test_user->roles)) {
  	return true;
  }
  else {
    return false;
  }
}
		
}
	