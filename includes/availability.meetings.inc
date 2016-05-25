<?php

module_load_include('module', 'availability_week');	

interface MeetingCommitmentsInterface {
  	
  public function listCommitments();
  
  public function periodCommitments($week, $slot);
  
}
class MeetingCommitments implements MeetingCommitmentsInterface{
  
  protected $meetings = array();
  
  protected $week;
  
  protected $slot;
  
  function __construct($uid = NULL, $date = NULL, $time = NULL) {  
  	$meeting_list = array();
  	$query = db_select('field_data_field_meeting', 'x');
    $query->innerJoin('field_data_field_meeting_date', 'd', 'x.field_meeting_target_id = d.entity_id');
    $query->innerJoin('node', 'm', 'x.field_meeting_target_id = m.nid');
    $query->addField('d', 'field_meeting_date_value', 'date');
	if ($date) {
	  $date1 = preg_replace('/(\+|-)\d\d:\d\d$/', '', date ( 'c' , $date ));
  	  $date2 = preg_replace('/(\+|-)\d\d:\d\d$/', '', date ( 'c' , $date + 7 * 24 * 60 * 60 ));
	  $query->having('(d.field_meeting_date_value BETWEEN :date1 AND :date2)', array(':date1' => $date1, ':date2' => $date2));
	}
    $query->addField('m', 'title');
    $query->innerJoin('field_data_field_mediator', 'r', 'r.entity_id = x.entity_id');
    $query->innerJoin('users', 'u' , 'u.uid = r.field_mediator_target_id');
    $query->addField('u', 'uid');
	if ($uid) {
	  $query->having('(u.uid = :uid)', array(':uid' => $uid));
	}
    $query->addField('u', 'name');
    $query->innerJoin('field_data_field_case_status', 's', 's.entity_id = x.entity_id');
    $query->innerJoin('taxonomy_term_data', 't1', 't1.tid = s.field_case_status_tid');
	$query->addField('t1', 'name', 'case_status');
    $query->having('(t1.name = :status)', array(':status' => 'Open'));
    $query->innerJoin('field_data_field_duration', 'l', 'l.entity_id = x.field_meeting_target_id');
    $query->innerJoin('taxonomy_term_data', 't2', 't2.tid = l.field_duration_tid');
    $query->addField('t2', 'name', 'duration');
    $result = $query->execute();
	while($record = $result->fetchAssoc()) {
      $meeting_list[] = $record;
    }
	$this->meetings = $meeting_list;
  }
  
  public function __destruct() {
  	$this->meetings = NULL;
	$this->week = NULL;
    $this->slot = NULL;
  }
  
  public function listCommitments() {
  	$string = '';
	
  	foreach ($this->meetings as $seq => $meeting) {
  	  $format_date = date_format(date_create($meeting['date']), 'l jS M \a\t H:i');
  	  $string .= '<p><span class = "meeting-title">' . $meeting['title'] . ': ' . '</span>' . 
  	    $format_date . ' for ' . $meeting['duration'] . '</p>';
  	}
	return $string;
  }

  public function periodCommitments($week, $slot) {
  	$this->week = $week;
	$this->slot = $slot;
  	$period_commitments = array_filter($this->meetings, array($this, '_filter_slot'));
  	return $period_commitments;
  }
  
  function _filter_slot($var) {
  	$availability_settings = variable_get("availability_settings", array());
	$day_of_week = substr($this->slot, 2, 2);
	$time_of_day = substr($this->slot, 0, 1);
	$periods = availability_periods_factory();
	$day_start = $this->week + 24 * 60 * 60 * $periods->availabilityDays('num')[$day_of_week];
	$day_end = $day_start + 24 * 60 * 60;
	$travel_time = $availability_settings['availability_travelling_time'];
  	$meeting_start = strtotime($var['date']);
	$meeting_end = strtotime('+ '.$var['duration'], $meeting_start);
	if ($travel_time) {
	  $meeting_start = strtotime('- '.$travel_time, $meeting_start);
	  $meeting_end = strtotime('+ '.$travel_time, $meeting_end);
	}
	$end_morning_parts = explode (':', $availability_settings['availability_end_morning']);
    $end_morning = $day_start + $end_morning_parts[0] * 3600 + $end_morning_parts[1] * 60;
	$end_afternoon_parts = explode (':', $availability_settings['availability_end_afternoon']);
	$end_afternoon = $day_start + $end_afternoon_parts[0] * 3600 + $end_afternoon_parts[1] * 60;
	if ($meeting_end < $day_start || $meeting_start > $day_end) {
	  return FALSE;
	}
	switch ($time_of_day){
	  case 'm':
		return $meeting_start <= $end_morning;
	  case 'a':
		return ($meeting_end >= $end_morning && $meeting_start <= $end_morning)
		  || ($meeting_start <= $end_afternoon && $meeting_end >= $end_afternoon);
	  default:
	    return $meeting_end >= $end_afternoon;
	}
  }
}