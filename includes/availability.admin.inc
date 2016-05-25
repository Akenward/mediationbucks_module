<?php

function availability_admin_settings($form, &$form_state) {
  $availability_settings= variable_get("availability_settings", array());
  $form['availability_cycle_settings'] = array(
    '#type'=> 'fieldset',
    '#title' => t('Cycle Parameters'),
    '#description' => t('Parameters for the availability recording cycle'),
    '#collapsible' => TRUE,
	'#collapsed' => FALSE,
    );
  $form['availability_cycle_settings']['availability_start_limit'] = array(
    '#type' => 'textfield',
    '#title' => t('Earliest start week'),
    '#size' => 10,
    '#description' => t('Minimum days back from today for start of first week shown'),
    '#default_value' => empty($availability_settings['availability_start_limit']) ? '3' : $availability_settings['availability_start_limit'],
    '#required' => TRUE,
  );
  $form['availability_cycle_settings']['availability_end_limit'] = array(
    '#type' => 'textfield',
    '#title' => t('Latest end week'),
    '#size' => 10,
    '#description' => t('Minimum days ahead from today for start of last week shown'),
    '#default_value' => empty($availability_settings['availability_end_limit']) ? '10' : $availability_settings['availability_end_limit'],
    '#required' => TRUE,
  );
  $form['availability_cycle_settings']['availability_default_week'] = array(
    '#type' => 'textfield',
    '#title' => t('Default week'),
    '#size' => 10,
    '#description' => t('Minimum days ahead for start of default week'),
    '#default_value' => empty($availability_settings['availability_default_week']) ? '3' : $availability_settings['availability_default_week'],
    '#required' => TRUE,
  );
  $form['availability_cycle_settings']['availability_delete_week'] = array(
    '#type' => 'textfield',
    '#title' => t('Delete week'),
    '#size' => 10,
    '#description' => t('Minimum days back for start of week to be deleted'),
    '#default_value' => empty($availability_settings['availability_delete_week']) ? '10' : $availability_settings['availability_delete_week'],
    '#required' => TRUE,
  );
  $form['availability_timing_settings'] = array(
    '#type'=> 'fieldset',
    '#title' => t('Timing Parameters'),
    '#description' => t('Parameters for times of day, week and duration'),
    '#collapsible' => TRUE,
	'#collapsed' => FALSE,
    );
  $form['availability_timing_settings']['availability_end_morning'] = array(
    '#type' => 'textfield',
    '#title' => t('Morning ends'),
    '#size' => 10,
    '#description' => t('End of the morning period using 24-hour clock'),
    '#default_value' => empty($availability_settings['availability_end_morning']) ? '12:00' : $availability_settings['availability_end_morning'],
    '#required' => TRUE,
   );
   $form['availability_timing_settings']['availability_end_afternoon'] = array(
    '#type' => 'textfield',
    '#title' => t('Afternoon ends'),
    '#size' => 10,
    '#description' => t('End of the afternoon period using 24-hour clock'),
    '#default_value' => empty($availability_settings['availability_end_afternoon']) ? '18:00' : $availability_settings['availability_end_afternoon'],
    '#required' => TRUE,
   );
   $form['availability_timing_settings']['availability_travelling_time'] = array(
    '#type' => 'textfield',
    '#title' => t('Travelling time'),
    '#size' => 10,
    '#description' => t('Minimum time period to allow between meetings e.g. "1 hour" or "45 minutes"'),
    '#default_value' => empty($availability_settings['availability_travelling_time']) ? '90 mins' : $availability_settings['availability_travelling_time'],
    '#required' => TRUE,
  );
  $form['availability_timing_settings']['availability_prompt_day'] = array(
    '#type' => 'textfield',
    '#title' => t('Day for prompt'),
    '#size' => 10,
    '#description' => t('Day of the week to send a prompt to mediators for an update on their availability'),
    '#default_value' => empty($availability_settings['availability_prompt_day']) ? 'Friday' : $availability_settings['availability_prompt_day'],
    '#required' => TRUE,
  );
  $form['availability_advanced_settings'] = array(
    '#type'=> 'fieldset',
    '#title' => t('Advanced Settings'),
    '#description' => t('Settings for optional functionality'),
    '#collapsible' => TRUE,
	'#collapsed' => TRUE,
    );
  $form['availability_advanced_settings']['availability_exit_protection'] = array(
    '#type' => 'checkbox',
    '#title' => t('Exit protection'),
    '#description' => t('Prompt the user if leaving "My availability" form with unsaved data'),
    '#default_value' => empty($availability_settings['availability_exit_protection']) ? 'unchecked' : $availability_settings['availability_exit_protection'],
    );
  $form['availability_advanced_settings']['availability_weekly_reminder'] = array(
    '#type' => 'checkbox',
    '#title' => t('Reminder email'),
    '#description' => t('Send a weekly reminder email to mediators with link to the site'),
    '#default_value' => empty($availability_settings['availability_weekly_reminder']) ? 'unchecked' : $availability_settings['availability_weekly_reminder'],
    );
  $form['availability_advanced_settings']['availability_email_subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Email subject'),
    '#size' => 60,
    '#description' => t('Subject line for the weekly reminder email - the list of available tokens is available below'),
    '#default_value' => empty($availability_settings['availability_email_subject']) ? '' : $availability_settings['availability_email_subject'],
    '#required' => TRUE,
  );
  $form['availability_advanced_settings']['availability_email_body'] = array(
    '#type' => 'textarea',
    '#title' => t('Email body'),
    '#cols' => 60,
    '#rows' => 7,
    '#description' => t('Body lines for the weekly reminder email - the list of available tokens is available below.'),
    '#default_value' => empty($availability_settings['availability_email_body']) ? '' : $availability_settings['availability_email_body'],
    '#required' => TRUE,
  );
  $form['availability_advanced_settings']['availability_replacement_tokens'] = array(
    '#type' => 'markup',
    '#title' => t('Relacement tokens'),
    '#description' => 'List of tokens and the value that will be replaced in the email',
    '#markup' => t('[week_commencing] = start date for the week, [site_link] = link containing the web address of the site for on-line reporting'),
  );
  $form['#submit'][] = 'availability_admin_settings_submit';
  return system_settings_form($form);
}

function availability_admin_settings_validate($form_id, $form_values) {
    $i = $form_values['values']['availability_start_limit'];
	if (!is_numeric($i) || $i < 1 || $i != round($i)) {
	  form_set_error('availability_start_limit', t('Enter an integer greater than zero'));
	}
    $i = $form_values['values']['availability_end_limit'];
	if (!is_numeric($i) || $i < 1 || $i != round($i)) {
	  form_set_error('availability_end_limit', t('Enter an integer greater than zero'));
	}
	$i = $form_values['values']['availability_default_week'];
	if (!is_numeric($i) || $i < 1 || $i != round($i)) {
	  form_set_error('availability_default_week', t('Enter an integer greater than zero'));
	}
	$i = $form_values['values']['availability_delete_week'];
	if (!is_numeric($i) || $i < 1 || $i != round($i)) {
	  form_set_error('availability_delete_week', t('Enter an integer greater than zero'));
	}
	if ($form_values['values']['availability_default_week'] > $form_values['values']['availability_end_limit']) {
	  form_set_error('availability_end_limit', t('Latest end week must be more than default week'));
	}
    if ($form_values['values']['availability_delete_week'] < $form_values['values']['availability_start_limit'] + 7) {
	  form_set_error('availability_delete_week', t('Delete week must be at least 7 days earlier than earliest start week'));
	}
    $timing = explode(':', $form_values['values']['availability_end_morning']);
	if (!isset($timing[0]) || !isset($timing[1]) || isset($timing[2]) || !is_numeric($timing[0]) || $timing[0] < 0 || $timing[0] != round($timing[0]) || !is_numeric($timing[1]) || $timing[1] < 0 || $timing[1] != round($timing[1])) {
	  form_set_error('availability_end_morning', t('Use format hh:mm where hh and mm are positive integers'));
	}
    $timing = explode(':', $form_values['values']['availability_end_afternoon']);
	if (!isset($timing[0]) || !isset($timing[1]) || isset($timing[2]) || !is_numeric($timing[0]) || $timing[0] < 0 || $timing[0] != round($timing[0]) || !is_numeric($timing[1]) || $timing[1] < 0 || $timing[1] != round($timing[1])) {
	  form_set_error('availability_end_afternoon', t('Use format hh:mm where hh and mm are positive integers'));
	}
	$interval = explode(' ', $form_values['values']['availability_travelling_time']);
	if (!isset($interval[0]) || !isset($interval[1]) || isset($interval[2]) || !is_numeric($interval[0]) || $interval[0] < 1 || $interval[0] != round($interval[0]) || !in_array($interval[1], array('hour', 'hours', 'minute', 'minutes'))) {
	  form_set_error('availability_travelling_time', t('Use format "n hour(s)" or "n minute(s)" where n is a positive integer'));
	}
	if (!in_array(strtolower($form_values['values']['availability_prompt_day']), array('monday', 'tuesday', 'wednesday', 'thursday', 'friday', 'saturday', 'sunday'), FALSE)) {
	  form_set_error('availability_prompt_day', t('The prompt day must be a day for the week (unabbreviated)'));
	}
}

function availability_admin_settings_submit($form, &$form_state) {
  $availability_settings= variable_get("availability_settings", array());
  $availability_settings['availability_start_limit'] = trim($form_state['values']['availability_start_limit']);
  $availability_settings['availability_end_limit'] = trim($form_state['values']['availability_end_limit']);
  $availability_settings['availability_default_week'] = trim($form_state['values']['availability_default_week']);
  $availability_settings['availability_delete_week'] = trim($form_state['values']['availability_delete_week']);
  $availability_settings['availability_end_morning'] = trim($form_state['values']['availability_end_morning']);
  $availability_settings['availability_end_afternoon'] = trim($form_state['values']['availability_end_afternoon']);
  $availability_settings['availability_travelling_time'] = trim($form_state['values']['availability_travelling_time']);
  $availability_settings['availability_prompt_day'] = trim(strtolower($form_state['values']['availability_prompt_day']));
  $availability_settings['availability_exit_protection'] = ($form_state['values']['availability_exit_protection']);
  $availability_settings['availability_weekly_reminder'] = ($form_state['values']['availability_weekly_reminder']);
  $availability_settings['availability_email_subject'] = trim($form_state['values']['availability_email_subject']);
  $availability_settings['availability_email_body'] = trim($form_state['values']['availability_email_body']);
  variable_set("availability_settings", $availability_settings);
}