<?php
/***
 *   @file
 *   functions to set up two arrays to hold days of the week and periods of the day
 */
interface AvailabilityPeriodsInterface {
  	
  public function availabilityDays($format = 'hi');
  
  public function availabilityTimes($format = 'hi');
  
  public function availabilityDateCalc($week, $m_d);
  
}

class AvailabilityPeriods implements AvailabilityPeriodsInterface {
	
  public function availabilityDays($format = 'hi'){
  	return $this->availabilityPeriodsArray['days'][$format];
  }

  public function availabilityTimes($format = 'hi') {
    return $this->availabilityPeriodsArray['times'][$format];
  }
  
  public function availabilityDateCalc($week, $m_d){
  	$day_num = $week + $this->availabilityPeriodsArray['days']['num'][$m_d] * 24 * 60 * 60;
	return date( 'j' , $day_num );
  }
  
  protected $availabilityPeriodsArray;
  
  
  function __construct() {
  	$this->availabilityPeriodsArray = array(
	  'days' => array(
	    'hi' => array(
		  'mo' => 'Monday',
          'tu' => 'Tuesday',
          'we' => 'Wednesday',
          'th' => 'Thursday',
          'fr' => 'Friday',
		),
		'lo' => array(
		  'mo' => 'Mon',
          'tu' => 'Tue',
          'we' => 'Wed',
          'th' => 'Thur',
          'fr' => 'Fri',
		),
		'num' => array(
		  'mo' => 0,
          'tu' => 1,
          'we' => 2,
          'th' => 3,
          'fr' => 4,
		),
	  ),
	  'times' => array(
	    'hi' => array(
		  'm' => 'morning',
          'a' => 'afternoon',
          'e' => 'evening',
		),
		'lo' => array(
		  'm' => 'am',
          'a' => 'pm',
          'e' => 'eve',
		),
	  ),
	);
  }
}
