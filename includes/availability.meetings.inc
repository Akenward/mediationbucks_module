<?php

interface MeetingCommitmentsInterface {
  	
  public function listCommitments();
  
}
class MeetingCommitments implements MeetingCommitmentsInterface{
	
  protected $meetings = array();
  
  function __construct($uid = NULL, $date = NULL, $time = NULL) {
  	$date1 = preg_replace('/(\+|-)\d\d:\d\d$/', '', date ( 'c' , $date ));
  	$date2 = preg_replace('/(\+|-)\d\d:\d\d$/', '', date ( 'c' , $date + 7 * 24 * 60 * 60 ));
  	$meeting_list = array();
  	$query = db_select('field_data_field_meeting', 'x');
    $query->innerJoin('field_data_field_meeting_date', 'd', 'x.field_meeting_target_id = d.entity_id');
    $query->innerJoin('node', 'm', 'x.field_meeting_target_id = m.nid');
    $query->addField('d', 'field_meeting_date_value', 'date');
	if ($date) {
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
  	$this->meetings = null;
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
  
  public function loadMeeting($meeting) {
  	module_load_include('inc', 'availability', 'includes/availability.period');
    module_load_include('module', 'entity');
	
  	if (!isset ($meeting['date']) || !isset($meeting['title']) || !isset($meeting['uid']) || !isset($meeting['name']) || !isset($meeting['duration'])) {
      return false;
    }
	else {
	  $this->meetings[] = $meeting;
	  return true;
	}
  }
  public function checkPeriod($monday, $d, $t, $travel = true) {
  	$availability_settings= variable_get("availability_settings", array());
  	$mediators = array();
  	$date = dateConvert($monday, $d);
	if ($travel) {
  	  $margin = $availability_settings['availability_travelling_time'];
  	}
	else {
	  $margin = '0 hours';
	}
  	foreach ($this->meetings as $meeting) {
  	  if (substr($meeting['date'],0,10) == $date->format('Y-m-d')) {
  	  	$end_date = date('Y-m-d H.i.s', strtotime($meeting['date'] . ' + ' . $meeting['duration'] . ' + ' . $margin));
		$start_date = date('Y-m-d H.i.s', strtotime($meeting['date'] . ' - ' . $margin));
  	  	if (dateCompare($start_date, $t) || dateCompare($end_date, $t)) {
  	  	  $date_text = date('Y-m-d', strtotime($meeting['date']));
		  $time_text = date('H:i', strtotime($meeting['date']));
			
		  $mediators[]= array(
		    'uid' => $meeting['uid'],
		    'title' => $meeting['title'],
		    'name' => $meeting['name'],
		    'date' => $date_text,
		    'time' => $time_text,
		  );
  	    }
      }  
	}
	return $mediators;
  }
  function dateCompare($date_string, $t) {
    $availability_settings= variable_get("availability_settings", array());
    module_load_include('inc', 'availability', 'includes/availability');
    $time_hours = substr($date_string, 11, 2);
	$time_minutes = substr($date_string, 14, 2);
	$time = $time_hours + $time_minutes/60;
	$end_morning = explode(':', $availability_settings['availability_end_morning']);
	$end_morning_hours = $end_morning[0] + $end_morning[1]/60;
	$end_afternoon = explode(':', $availability_settings['availability_end_afternoon']);
	$end_afternoon_hours = $end_afternoon[0] + $end_afternoon[1]/60;
	if ($time <= $end_morning_hours && $t == 'm')  {
      return TRUE;
	}
  	if ($time >= $end_morning_hours && $time <= $end_afternoon_hours && $t == 'a') {
  	  return TRUE;
  	}
	if ($time >= $end_afternoon_hours && $t == 'e') {
	  return TRUE;
	}
	return FALSE;
  }
}