<?php
/**
 * @file
 * localize_fields_test.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function localize_fields_test_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'body'
  $field_bases['body'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(
      0 => 'node',
    ),
    'field_name' => 'body',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(),
    'translatable' => 0,
    'type' => 'text_with_summary',
  );

  // Exported field_base: 'field_lclzflds_bool_radio'
  $field_bases['field_lclzflds_bool_radio'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_lclzflds_bool_radio',
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        0 => 'Boolean list radio unselected LOCALIZE_FIELDS_UNTRANSLATED',
        1 => 'Boolean list radio selected LOCALIZE_FIELDS_UNTRANSLATED',
      ),
      'allowed_values_function' => '',
      'allowed_values_no_localization' => 0,
    ),
    'translatable' => 0,
    'type' => 'list_boolean',
  );

  // Exported field_base: 'field_lclzflds_date'
  $field_bases['field_lclzflds_date'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_lclzflds_date',
    'indexes' => array(),
    'locked' => 0,
    'module' => 'date',
    'settings' => array(
      'cache_count' => 4,
      'cache_enabled' => 0,
      'granularity' => array(
        'day' => 'day',
        'hour' => 'hour',
        'minute' => 'minute',
        'month' => 'month',
        'second' => 0,
        'year' => 'year',
      ),
      'timezone_db' => 'UTC',
      'todate' => '',
      'tz_handling' => 'site',
    ),
    'translatable' => 0,
    'type' => 'datetime',
  );

  // Exported field_base: 'field_lclzflds_date_to_multi'
  $field_bases['field_lclzflds_date_to_multi'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_lclzflds_date_to_multi',
    'indexes' => array(),
    'locked' => 0,
    'module' => 'date',
    'settings' => array(
      'cache_count' => 4,
      'cache_enabled' => 0,
      'granularity' => array(
        'day' => 'day',
        'hour' => 'hour',
        'minute' => 'minute',
        'month' => 'month',
        'second' => 0,
        'year' => 'year',
      ),
      'timezone_db' => 'UTC',
      'todate' => 'optional',
      'tz_handling' => 'site',
    ),
    'translatable' => 0,
    'type' => 'datetime',
  );

  // Exported field_base: 'field_lclzflds_decimal'
  $field_bases['field_lclzflds_decimal'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_lclzflds_decimal',
    'indexes' => array(),
    'locked' => 0,
    'module' => 'number',
    'settings' => array(
      'decimal_separator' => ',',
      'precision' => 10,
      'scale' => 2,
    ),
    'translatable' => 0,
    'type' => 'number_decimal',
  );

  // Exported field_base: 'field_lclzflds_fieldcol'
  $field_bases['field_lclzflds_fieldcol'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_lclzflds_fieldcol',
    'indexes' => array(
      'revision_id' => array(
        0 => 'revision_id',
      ),
    ),
    'locked' => 0,
    'module' => 'field_collection',
    'settings' => array(
      'hide_blank_items' => 1,
      'path' => '',
    ),
    'translatable' => 0,
    'type' => 'field_collection',
  );

  // Exported field_base: 'field_lclzflds_fieldcol_multi'
  $field_bases['field_lclzflds_fieldcol_multi'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_lclzflds_fieldcol_multi',
    'indexes' => array(
      'revision_id' => array(
        0 => 'revision_id',
      ),
    ),
    'locked' => 0,
    'module' => 'field_collection',
    'settings' => array(
      'hide_blank_items' => 1,
      'path' => '',
    ),
    'translatable' => 0,
    'type' => 'field_collection',
  );

  // Exported field_base: 'field_lclzflds_file'
  $field_bases['field_lclzflds_file'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_lclzflds_file',
    'indexes' => array(
      'fid' => array(
        0 => 'fid',
      ),
    ),
    'locked' => 0,
    'module' => 'file',
    'settings' => array(
      'display_default' => 0,
      'display_field' => 0,
      'uri_scheme' => 'public',
    ),
    'translatable' => 0,
    'type' => 'file',
  );

  // Exported field_base: 'field_lclzflds_file_multi'
  $field_bases['field_lclzflds_file_multi'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_lclzflds_file_multi',
    'indexes' => array(
      'fid' => array(
        0 => 'fid',
      ),
    ),
    'locked' => 0,
    'module' => 'file',
    'settings' => array(
      'display_default' => 0,
      'display_field' => 0,
      'uri_scheme' => 'public',
    ),
    'translatable' => 0,
    'type' => 'file',
  );

  // Exported field_base: 'field_lclzflds_image'
  $field_bases['field_lclzflds_image'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_lclzflds_image',
    'indexes' => array(
      'fid' => array(
        0 => 'fid',
      ),
    ),
    'locked' => 0,
    'module' => 'image',
    'settings' => array(
      'default_image' => 0,
      'uri_scheme' => 'public',
    ),
    'translatable' => 0,
    'type' => 'image',
  );

  // Exported field_base: 'field_lclzflds_image_multi'
  $field_bases['field_lclzflds_image_multi'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_lclzflds_image_multi',
    'indexes' => array(
      'fid' => array(
        0 => 'fid',
      ),
    ),
    'locked' => 0,
    'module' => 'image',
    'settings' => array(
      'default_image' => 0,
      'uri_scheme' => 'public',
    ),
    'translatable' => 0,
    'type' => 'image',
  );

  // Exported field_base: 'field_lclzflds_integer_encoded'
  $field_bases['field_lclzflds_integer_encoded'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_lclzflds_integer_encoded',
    'indexes' => array(),
    'locked' => 0,
    'module' => 'number',
    'settings' => array(),
    'translatable' => 0,
    'type' => 'number_integer',
  );

  // Exported field_base: 'field_lclzflds_integer_multi'
  $field_bases['field_lclzflds_integer_multi'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_lclzflds_integer_multi',
    'indexes' => array(),
    'locked' => 0,
    'module' => 'number',
    'settings' => array(),
    'translatable' => 0,
    'type' => 'number_integer',
  );

  // Exported field_base: 'field_lclzflds_list_bool'
  $field_bases['field_lclzflds_list_bool'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_lclzflds_list_bool',
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        0 => 'Boolean list unselected LOCALIZE_FIELDS_UNTRANSLATED',
        1 => 'Boolean list selected LOCALIZE_FIELDS_UNTRANSLATED',
      ),
      'allowed_values_function' => '',
      'allowed_values_no_localization' => 0,
    ),
    'translatable' => 0,
    'type' => 'list_boolean',
  );

  // Exported field_base: 'field_lclzflds_list_text'
  $field_bases['field_lclzflds_list_text'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_lclzflds_list_text',
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        'Alpha' => 'Alpha LOCALIZE_FIELDS_UNTRANSLATED',
        'Beta' => 'Beta LOCALIZE_FIELDS_UNTRANSLATED',
        'Gamma' => 'Gamma LOCALIZE_FIELDS_UNTRANSLATED',
      ),
      'allowed_values_function' => '',
      'allowed_values_no_localization' => 0,
    ),
    'translatable' => 0,
    'type' => 'list_text',
  );

  // Exported field_base: 'field_lclzflds_list_text_check'
  $field_bases['field_lclzflds_list_text_check'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_lclzflds_list_text_check',
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        'Alpha' => 'Alpha LOCALIZE_FIELDS_UNTRANSLATED',
        'Beta' => 'Beta LOCALIZE_FIELDS_UNTRANSLATED',
        'Gamma' => 'Gamma LOCALIZE_FIELDS_UNTRANSLATED',
      ),
      'allowed_values_function' => '',
      'allowed_values_no_localization' => 0,
    ),
    'translatable' => 0,
    'type' => 'list_text',
  );

  // Exported field_base: 'field_lclzflds_term'
  $field_bases['field_lclzflds_term'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_lclzflds_term',
    'indexes' => array(
      'tid' => array(
        0 => 'tid',
      ),
    ),
    'locked' => 0,
    'module' => 'taxonomy',
    'settings' => array(
      'allowed_values' => array(
        0 => array(
          'vocabulary' => 'lclzflds',
          'parent' => 0,
        ),
      ),
    ),
    'translatable' => 0,
    'type' => 'taxonomy_term_reference',
  );

  // Exported field_base: 'field_lclzflds_text'
  $field_bases['field_lclzflds_text'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_lclzflds_text',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  // Exported field_base: 'field_lclzflds_text_multi'
  $field_bases['field_lclzflds_text_multi'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_lclzflds_text_multi',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  // Exported field_base: 'field_lclzflds_textlong'
  $field_bases['field_lclzflds_textlong'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_lclzflds_textlong',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(),
    'translatable' => 0,
    'type' => 'text_long',
  );

  // Translatables created/updated by the Localize Fields (localize_fields) module.
  t('Boolean list radio unselected LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field:field_lclzflds_bool_radio:allowed_values'));
  t('Boolean list radio selected LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field:field_lclzflds_bool_radio:allowed_values'));
  t('Boolean list unselected LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field:field_lclzflds_list_bool:allowed_values'));
  t('Boolean list selected LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field:field_lclzflds_list_bool:allowed_values'));
  t('Alpha LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field:field_lclzflds_list_text:allowed_values'));
  t('Beta LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field:field_lclzflds_list_text:allowed_values'));
  t('Gamma LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field:field_lclzflds_list_text:allowed_values'));
  t('Alpha LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field:field_lclzflds_list_text_check:allowed_values'));
  t('Beta LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field:field_lclzflds_list_text_check:allowed_values'));
  t('Gamma LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field:field_lclzflds_list_text_check:allowed_values'));


  return $field_bases;
}
