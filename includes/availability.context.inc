<?php

interface AvailabilityContextInterface {
  	
  public function availabilityCurrentMediator();
  
  public function availabilityCurrentMonday();
  
  public function setCurrentMediator($mediator);
  
  public function nextMonday();
  
  public function previousMonday();
  
  public function inRange($week);
  
}
class AvailabilityContext implements AvailabilityContextInterface{
	
  protected $mediator;
  
  protected $monday;
  
  protected $date_limits;
  
  function __construct (){
  	global $user;
  	$this->mediator = $user;
	$this->date_limits = $this->_date_limits();
	$this->monday = $this->date_limits['default'];
  }
  
  public function availabilityCurrentMediator() {
  	return (clone $this->mediator);
  }
  
  public function availabilityCurrentMonday() {
  	return (clone $this->monday);
  }
  
  public function setCurrentMediator($mediator) {
  	$this->mediator = $mediator;
  }
  
  public function nextMonday() {
  	if ($this->date_limits['upper']->difference($this->monday, 'days')) {
  	  $this->monday = $this->monday->modify('+1 week');
	  return TRUE;
	}
	else {
	  return FALSE;
    }
  }
  
  public function previousMonday(){
    if ($this->monday->difference($this->date_limits['lower'], 'days')) {
  	  $this->monday = $this->monday->modify('-1 week');
	  return TRUE;
	}
	else {
	  return FALSE;
    }
  }
  
  public function inRange($week) {
  	return ($week >= $this->date_limits['lower']->format('U') &&
  	  $week <= $this->date_limits['upper']->format('U'));
  }
	
  protected function _date_limits() {
	$availability_settings= variable_get("availability_settings", array());
    if (sizeof($availability_settings) < 1) {
  	  $availability_settings = array (
  	    'availability_start_limit' => '3',
  	    'availability_delete_week' => '10',
  	    'availability_default_week' => '3',
  	    'availability_end_limit' => '17',
  	  );
    }
  $date_today =  new DateObject('now');
  $date_limits['lower'] = clone($date_today);
  date_modify($date_limits['lower'], '+1 Monday');
  do {
    date_modify($date_limits['lower'], '-1 week');
  }  while ($date_limits['lower']->diff($date_today)->format('%R%a') < $availability_settings['availability_start_limit']);
  $date_limits['delete'] = clone($date_limits['lower']);
  do {
  	date_modify($date_limits['delete'], '-1 week');
  } while ($date_limits['delete']->diff($date_today)->format('%R%a') < $availability_settings['availability_delete_week']);
  $date_limits['default'] = clone($date_limits['lower']);
  do {
  	date_modify($date_limits['default'], '+1 week');
	
  } while ($date_today->diff($date_limits['default'])->format('%R%a')  < $availability_settings['availability_default_week']);
  $date_limits['upper'] = clone($date_limits['default']);
  do {
  	date_modify($date_limits['upper'], '+1 week');
  } while ($date_today->diff($date_limits['upper'])->format('%R%a') < $availability_settings['availability_end_limit']);
  return $date_limits;
  }
}

