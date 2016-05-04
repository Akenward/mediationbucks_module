<?php

module_load_include('module', 'availability_week');

interface AvailabilityStorageInterface {
  	
  public function availabilityRetrieveEntity($date = NULL);
  
  public function availabilitySaveEntity($form, $form_state, $repeat_weeks = 0);
  
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
  
  protected function _blank_availability_record($mediator_uid, $date_stamp) {
  	$periods = availability_periods_factory();
  	$values = array(
      'uid' => $mediator_uid,
      'start_date' => $date_stamp,
    );
	
	$entity = entity_create('availability', $values);
    $e_wrapper = entity_metadata_wrapper('availability', $entity);
	$field_values = array();
    foreach ($periods -> availabilityTimes() as $m_t => $m_time) {
  	  foreach ($periods -> availabilityDays() as $m_d => $m_day) {
  	    $field_values[$m_t.'_'.$m_d] = 2;
      }
    }
	$field_values['notes'] = '';
    $e_wrapper->field_availability_week->set($field_values);
	return $entity;
  }
		
}
	