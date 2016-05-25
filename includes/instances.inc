<?php

/** function to return definitions of new field instances required by the availability entity
 *  @entity_type: is the node type.
 *  @return takes the form af an array of field instance arrays each keyed on the field type name
 */
 
function _availability_instances() {
  return array(
    'field_availability_week' => array(
      'field_name' => 'field_availability_week',
      'entity_type' => 'availability',
      'bundle' => 'availability',
      'deleted' => '0',
      'label' => 'Week',
      'widget' => array(
        'type' => 'availability_week_table',
        'weight' => '10',
        'settings' => array(),
        'module' => 'availability_week',
      ),
      'display' => array(
        'default' => array(
          'label' => 'above',
          'type' => 'availability_week_print',
          'settings' => array(),
          'module' => 'availability_week',
          'weight' => 1,
        ),
        'teaser' => array(
          'type' => 'hidden',
          'label' => 'above',
          'settings' => array(),
          'weight' => 0,
        ),
      ),
      'required' => FALSE,
      'description' => '',
      'default_value' => NULL,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
    ),
  );
}
