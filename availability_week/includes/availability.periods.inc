<?php
/***
 *   @file
 *   functions to set up two arrays to hold days of the week and periods of the day
 */
interface AvailabilityPeriodsInterface {
  	
  public function availabilityDays();
  
  public function availabilityTimes();
  
}

class AvailabilityPeriods implements AvailabilityPeriodsInterface {
	
  function availabilityDays(){
    return array(
      'mo' => 'Monday',
      'tu' => 'Tuesday',
      'we' => 'Wednesday',
      'th' => 'Thursday',
      'fr' => 'Friday',
    );
  }

  function availabilityTimes() {
    return array(
      'm' => 'morning',
      'a' => 'afternoon',
      'e' => 'evening',
    );
  }
}
