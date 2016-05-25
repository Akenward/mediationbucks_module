<?php

/** function to return definitions of field types required for the availability module
 *  @entity_type: is the entity type requiring the field.
 *  @return takes the form af an array of field arrays each keyed on the field type name
 */

function _availability_fields() {
  return array(
	'field_availability_week' => array(
	  'field_name' => 'field_availability_week',
      'type' => 'availability_week_data',
      'module' => 'availability_week',
      'active' => '1',
      'locked' => '0',
      'cardinality' => '1',
      'deleted' => '0',
      'translatable' => '0',
      'settings' => array(),
    ),
  );
}