<?php
/**
 * @file
 * localize_fields_test.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function localize_fields_test_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance:
  // 'field_collection_item-field_lclzflds_fieldcol-field_lclzflds_date_to_multi'
  $field_instances['field_collection_item-field_lclzflds_fieldcol-field_lclzflds_date_to_multi'] = array(
    'bundle' => 'field_lclzflds_fieldcol',
    'deleted' => 0,
    'description' => 'Multiple dates to dates help LOCALIZE_FIELDS_UNTRANSLATED',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'date',
        'settings' => array(
          'format_type' => 'long',
          'fromto' => 'both',
          'multiple_from' => '',
          'multiple_number' => '',
          'multiple_to' => '',
        ),
        'type' => 'date_default',
        'weight' => 4,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_lclzflds_date_to_multi',
    'label' => 'Multiple dates to dates LOCALIZE_FIELDS_UNTRANSLATED',
    'required' => 1,
    'settings' => array(
      'default_value' => 'blank',
      'default_value2' => 'same',
      'default_value_code' => '',
      'default_value_code2' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'date',
      'settings' => array(
        'increment' => 15,
        'input_format' => 'm/d/Y - H:i:s',
        'input_format_custom' => '',
        'label_position' => 'above',
        'text_parts' => array(),
        'year_range' => '-3:+3',
      ),
      'type' => 'date_popup',
      'weight' => 5,
    ),
  );

  // Exported field_instance:
  // 'field_collection_item-field_lclzflds_fieldcol-field_lclzflds_fieldcol_multi'
  $field_instances['field_collection_item-field_lclzflds_fieldcol-field_lclzflds_fieldcol_multi'] = array(
    'bundle' => 'field_lclzflds_fieldcol',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Multiple field collections help LOCALIZE_FIELDS_UNTRANSLATED',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'field_collection',
        'settings' => array(
          'add' => 'Add',
          'delete' => 'Delete',
          'description' => TRUE,
          'edit' => 'Edit',
          'view_mode' => 'full',
        ),
        'type' => 'field_collection_view',
        'weight' => 2,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_lclzflds_fieldcol_multi',
    'label' => 'Multiple field collections LOCALIZE_FIELDS_UNTRANSLATED',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'field_collection',
      'settings' => array(),
      'type' => 'field_collection_embed',
      'weight' => 6,
    ),
  );

  // Exported field_instance:
  // 'field_collection_item-field_lclzflds_fieldcol-field_lclzflds_file'
  $field_instances['field_collection_item-field_lclzflds_fieldcol-field_lclzflds_file'] = array(
    'bundle' => 'field_lclzflds_fieldcol',
    'deleted' => 0,
    'description' => 'File help: [current-date:short] LOCALIZE_FIELDS_UNTRANSLATED',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'file',
        'settings' => array(),
        'type' => 'file_default',
        'weight' => 3,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_lclzflds_file',
    'label' => 'File LOCALIZE_FIELDS_UNTRANSLATED',
    'required' => 1,
    'settings' => array(
      'description_field' => 0,
      'file_directory' => '',
      'file_extensions' => 'txt',
      'max_filesize' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'file',
      'settings' => array(
        'progress_indicator' => 'throbber',
      ),
      'type' => 'file_generic',
      'weight' => 4,
    ),
  );

  // Exported field_instance:
  // 'field_collection_item-field_lclzflds_fieldcol-field_lclzflds_integer_multi'
  $field_instances['field_collection_item-field_lclzflds_fieldcol-field_lclzflds_integer_multi'] = array(
    'bundle' => 'field_lclzflds_fieldcol',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Multiple integers help LOCALIZE_FIELDS_UNTRANSLATED',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_integer',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_lclzflds_integer_multi',
    'label' => 'Multiple integers LOCALIZE_FIELDS_UNTRANSLATED',
    'required' => 1,
    'settings' => array(
      'max' => 10,
      'min' => 1,
      'prefix' => 'Multiple integers prefix LOCALIZE_FIELDS_UNTRANSLATED',
      'suffix' => 'Multiple integers suffix LOCALIZE_FIELDS_UNTRANSLATED',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 1,
    ),
  );

  // Exported field_instance:
  // 'field_collection_item-field_lclzflds_fieldcol-field_lclzflds_list_bool'
  $field_instances['field_collection_item-field_lclzflds_fieldcol-field_lclzflds_list_bool'] = array(
    'bundle' => 'field_lclzflds_fieldcol',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Boolean list help: [current-date:short] LOCALIZE_FIELDS_UNTRANSLATED',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 5,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_lclzflds_list_bool',
    'label' => 'Boolean list LOCALIZE_FIELDS_UNTRANSLATED',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => 2,
    ),
  );

  // Exported field_instance:
  // 'field_collection_item-field_lclzflds_fieldcol-field_lclzflds_list_text_check'
  $field_instances['field_collection_item-field_lclzflds_fieldcol-field_lclzflds_list_text_check'] = array(
    'bundle' => 'field_lclzflds_fieldcol',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Text list checkboxes help: [current-date:short] LOCALIZE_FIELDS_UNTRANSLATED',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 6,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_lclzflds_list_text_check',
    'label' => 'Text list checkboxes LOCALIZE_FIELDS_UNTRANSLATED',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => 3,
    ),
  );

  // Exported field_instance:
  // 'field_collection_item-field_lclzflds_fieldcol-field_lclzflds_text'
  $field_instances['field_collection_item-field_lclzflds_fieldcol-field_lclzflds_text'] = array(
    'bundle' => 'field_lclzflds_fieldcol',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Text help: [current-date:short] LOCALIZE_FIELDS_UNTRANSLATED',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_lclzflds_text',
    'label' => 'Text LOCALIZE_FIELDS_UNTRANSLATED',
    'required' => 1,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 0,
    ),
  );

  // Exported field_instance:
  // 'field_collection_item-field_lclzflds_fieldcol_multi-field_lclzflds_decimal'
  $field_instances['field_collection_item-field_lclzflds_fieldcol_multi-field_lclzflds_decimal'] = array(
    'bundle' => 'field_lclzflds_fieldcol_multi',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Decimal help: [current-date:short] LOCALIZE_FIELDS_UNTRANSLATED',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 2,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_decimal',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_lclzflds_decimal',
    'label' => 'Decimal LOCALIZE_FIELDS_UNTRANSLATED',
    'required' => 1,
    'settings' => array(
      'max' => 10,
      'min' => 1,
      'prefix' => 'Decimal prefix LOCALIZE_FIELDS_UNTRANSLATED',
      'suffix' => 'Decimal suffix LOCALIZE_FIELDS_UNTRANSLATED',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 2,
    ),
  );

  // Exported field_instance:
  // 'field_collection_item-field_lclzflds_fieldcol_multi-field_lclzflds_image_multi'
  $field_instances['field_collection_item-field_lclzflds_fieldcol_multi-field_lclzflds_image_multi'] = array(
    'bundle' => 'field_lclzflds_fieldcol_multi',
    'deleted' => 0,
    'description' => 'Multiple images help: [current-date:short] LOCALIZE_FIELDS_UNTRANSLATED',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'image',
        'settings' => array(
          'image_link' => '',
          'image_style' => '',
        ),
        'type' => 'image',
        'weight' => 2,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_lclzflds_image_multi',
    'label' => 'Multiple images LOCALIZE_FIELDS_UNTRANSLATED',
    'required' => 1,
    'settings' => array(
      'alt_field' => 0,
      'default_image' => 0,
      'file_directory' => '',
      'file_extensions' => 'png gif jpg jpeg',
      'max_filesize' => '',
      'max_resolution' => '',
      'min_resolution' => '',
      'title_field' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'image',
      'settings' => array(
        'preview_image_style' => 'thumbnail',
        'progress_indicator' => 'throbber',
      ),
      'type' => 'image_image',
      'weight' => 6,
    ),
  );

  // Exported field_instance:
  // 'field_collection_item-field_lclzflds_fieldcol_multi-field_lclzflds_text_multi'
  $field_instances['field_collection_item-field_lclzflds_fieldcol_multi-field_lclzflds_text_multi'] = array(
    'bundle' => 'field_lclzflds_fieldcol_multi',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Multiple texts help LOCALIZE_FIELDS_UNTRANSLATED',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_lclzflds_text_multi',
    'label' => 'Multiple texts LOCALIZE_FIELDS_UNTRANSLATED',
    'required' => 1,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'node-localize_fields_test-body'
  $field_instances['node-localize_fields_test-body'] = array(
    'bundle' => 'localize_fields_test',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Body help: [current-date:short] LOCALIZE_FIELDS_UNTRANSLATED',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 20,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'body',
    'kk_field_description_tooltip_disabled' => 0,
    'label' => 'Body LOCALIZE_FIELDS_UNTRANSLATED',
    'required' => 0,
    'settings' => array(
      'display_summary' => 0,
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 2,
        'summary_rows' => 5,
      ),
      'type' => 'text_textarea_with_summary',
      'weight' => 1,
    ),
  );

  // Exported field_instance:
  // 'node-localize_fields_test-field_lclzflds_bool_radio'
  $field_instances['node-localize_fields_test-field_lclzflds_bool_radio'] = array(
    'bundle' => 'localize_fields_test',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Boolean list radio help: [current-date:short] LOCALIZE_FIELDS_UNTRANSLATED',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 17,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_lclzflds_bool_radio',
    'label' => 'Boolean list radio LOCALIZE_FIELDS_UNTRANSLATED',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => 7,
    ),
  );

  // Exported field_instance: 'node-localize_fields_test-field_lclzflds_date'
  $field_instances['node-localize_fields_test-field_lclzflds_date'] = array(
    'bundle' => 'localize_fields_test',
    'deleted' => 0,
    'description' => 'Date help: [current-date:short] LOCALIZE_FIELDS_UNTRANSLATED',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'date',
        'settings' => array(
          'format_type' => 'long',
          'fromto' => 'both',
          'multiple_from' => '',
          'multiple_number' => '',
          'multiple_to' => '',
        ),
        'type' => 'date_default',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_lclzflds_date',
    'label' => 'Date LOCALIZE_FIELDS_UNTRANSLATED',
    'required' => 1,
    'settings' => array(
      'default_value' => 'blank',
      'default_value2' => 'same',
      'default_value_code' => '',
      'default_value_code2' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'date',
      'settings' => array(
        'increment' => 15,
        'input_format' => 'Y-m-d H:i:s',
        'input_format_custom' => '',
        'label_position' => 'above',
        'text_parts' => array(),
        'year_range' => '-3:+3',
      ),
      'type' => 'date_popup',
      'weight' => 14,
    ),
  );

  // Exported field_instance: 'node-localize_fields_test-field_lclzflds_decimal'
  $field_instances['node-localize_fields_test-field_lclzflds_decimal'] = array(
    'bundle' => 'localize_fields_test',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Decimal help: [current-date:short] LOCALIZE_FIELDS_UNTRANSLATED',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 2,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_decimal',
        'weight' => 3,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_lclzflds_decimal',
    'label' => 'Decimal LOCALIZE_FIELDS_UNTRANSLATED',
    'required' => 1,
    'settings' => array(
      'max' => 10,
      'min' => 1,
      'prefix' => 'Decimal prefix LOCALIZE_FIELDS_UNTRANSLATED',
      'suffix' => 'Decimal puffix LOCALIZE_FIELDS_UNTRANSLATED',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 4,
    ),
  );

  // Exported field_instance:
  // 'node-localize_fields_test-field_lclzflds_fieldcol'
  $field_instances['node-localize_fields_test-field_lclzflds_fieldcol'] = array(
    'bundle' => 'localize_fields_test',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Field collection help: [current-date:short] LOCALIZE_FIELDS_UNTRANSLATED',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'field_collection',
        'settings' => array(
          'add' => 'Add',
          'delete' => 'Delete',
          'description' => TRUE,
          'edit' => 'Edit',
          'view_mode' => 'full',
        ),
        'type' => 'field_collection_view',
        'weight' => 10,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_lclzflds_fieldcol',
    'label' => 'Field collection LOCALIZE_FIELDS_UNTRANSLATED',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'field_collection',
      'settings' => array(),
      'type' => 'field_collection_embed',
      'weight' => 16,
    ),
  );

  // Exported field_instance:
  // 'node-localize_fields_test-field_lclzflds_fieldcol_multi'
  $field_instances['node-localize_fields_test-field_lclzflds_fieldcol_multi'] = array(
    'bundle' => 'localize_fields_test',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Multiple \'field collections\' "help" LOCALIZE_FIELDS_UNTRANSLATED',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'field_collection',
        'settings' => array(
          'add' => 'Add',
          'delete' => 'Delete',
          'description' => TRUE,
          'edit' => 'Edit',
          'view_mode' => 'full',
        ),
        'type' => 'field_collection_view',
        'weight' => 13,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_lclzflds_fieldcol_multi',
    'label' => 'Multiple \'field\' "collections" LOCALIZE_FIELDS_UNTRANSLATED',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'field_collection',
      'settings' => array(),
      'type' => 'field_collection_embed',
      'weight' => 17,
    ),
  );

  // Exported field_instance: 'node-localize_fields_test-field_lclzflds_file'
  $field_instances['node-localize_fields_test-field_lclzflds_file'] = array(
    'bundle' => 'localize_fields_test',
    'deleted' => 0,
    'description' => 'File help: [current-date:short] LOCALIZE_FIELDS_UNTRANSLATED',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'file',
        'settings' => array(),
        'type' => 'file_default',
        'weight' => 8,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_lclzflds_file',
    'label' => 'File LOCALIZE_FIELDS_UNTRANSLATED',
    'required' => 1,
    'settings' => array(
      'description_field' => 0,
      'file_directory' => '',
      'file_extensions' => 'txt',
      'max_filesize' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'file',
      'settings' => array(
        'progress_indicator' => 'throbber',
      ),
      'type' => 'file_generic',
      'weight' => 11,
    ),
  );

  // Exported field_instance:
  // 'node-localize_fields_test-field_lclzflds_file_multi'
  $field_instances['node-localize_fields_test-field_lclzflds_file_multi'] = array(
    'bundle' => 'localize_fields_test',
    'deleted' => 0,
    'description' => 'Multiple files help: [current-date:short] LOCALIZE_FIELDS_UNTRANSLATED',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'file',
        'settings' => array(),
        'type' => 'file_default',
        'weight' => 16,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_lclzflds_file_multi',
    'label' => 'Multiple files LOCALIZE_FIELDS_UNTRANSLATED',
    'required' => 1,
    'settings' => array(
      'description_field' => 0,
      'file_directory' => '',
      'file_extensions' => 'txt',
      'max_filesize' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'file',
      'settings' => array(
        'progress_indicator' => 'throbber',
      ),
      'type' => 'file_generic',
      'weight' => 12,
    ),
  );

  // Exported field_instance: 'node-localize_fields_test-field_lclzflds_image'
  $field_instances['node-localize_fields_test-field_lclzflds_image'] = array(
    'bundle' => 'localize_fields_test',
    'deleted' => 0,
    'description' => 'Image help: [current-date:short] LOCALIZE_FIELDS_UNTRANSLATED',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'image',
        'settings' => array(
          'image_link' => '',
          'image_style' => '',
        ),
        'type' => 'image',
        'weight' => 6,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_lclzflds_image',
    'label' => 'Image LOCALIZE_FIELDS_UNTRANSLATED',
    'required' => 1,
    'settings' => array(
      'alt_field' => 0,
      'default_image' => 0,
      'file_directory' => '',
      'file_extensions' => 'png gif jpg jpeg',
      'max_filesize' => '',
      'max_resolution' => '',
      'min_resolution' => '',
      'title_field' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'image',
      'settings' => array(
        'preview_image_style' => 'thumbnail',
        'progress_indicator' => 'throbber',
      ),
      'type' => 'image_image',
      'weight' => 9,
    ),
  );

  // Exported field_instance:
  // 'node-localize_fields_test-field_lclzflds_image_multi'
  $field_instances['node-localize_fields_test-field_lclzflds_image_multi'] = array(
    'bundle' => 'localize_fields_test',
    'deleted' => 0,
    'description' => 'Multiple images help: [current-date:short] LOCALIZE_FIELDS_UNTRANSLATED',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'image',
        'settings' => array(
          'image_link' => '',
          'image_style' => '',
        ),
        'type' => 'image',
        'weight' => 15,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_lclzflds_image_multi',
    'label' => 'Multiple images LOCALIZE_FIELDS_UNTRANSLATED',
    'required' => 1,
    'settings' => array(
      'alt_field' => 0,
      'default_image' => 0,
      'file_directory' => '',
      'file_extensions' => 'png gif jpg jpeg',
      'max_filesize' => '',
      'max_resolution' => '',
      'min_resolution' => '',
      'title_field' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'image',
      'settings' => array(
        'preview_image_style' => 'thumbnail',
        'progress_indicator' => 'throbber',
      ),
      'type' => 'image_image',
      'weight' => 10,
    ),
  );

  // Exported field_instance:
  // 'node-localize_fields_test-field_lclzflds_integer_encoded'
  $field_instances['node-localize_fields_test-field_lclzflds_integer_encoded'] = array(
    'bundle' => 'localize_fields_test',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Integer with \'HTML\' "escaped" description',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_integer',
        'weight' => 19,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_lclzflds_integer_encoded',
    'label' => 'Integer with \'HTML\' "escaped" label',
    'required' => 1,
    'settings' => array(
      'max' => 10,
      'min' => 1,
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 15,
    ),
  );

  // Exported field_instance:
  // 'node-localize_fields_test-field_lclzflds_integer_multi'
  $field_instances['node-localize_fields_test-field_lclzflds_integer_multi'] = array(
    'bundle' => 'localize_fields_test',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Multiple integers help LOCALIZE_FIELDS_UNTRANSLATED',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_integer',
        'weight' => 14,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_lclzflds_integer_multi',
    'label' => 'Multiple integers LOCALIZE_FIELDS_UNTRANSLATED',
    'required' => 1,
    'settings' => array(
      'max' => 10,
      'min' => 1,
      'prefix' => 'Integer prefix LOCALIZE_FIELDS_UNTRANSLATED',
      'suffix' => 'Integer suffix LOCALIZE_FIELDS_UNTRANSLATED',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 5,
    ),
  );

  // Exported field_instance:
  // 'node-localize_fields_test-field_lclzflds_list_bool'
  $field_instances['node-localize_fields_test-field_lclzflds_list_bool'] = array(
    'bundle' => 'localize_fields_test',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => 'Boolean list help: [current-date:short] LOCALIZE_FIELDS_UNTRANSLATED',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_lclzflds_list_bool',
    'label' => 'Boolean list LOCALIZE_FIELDS_UNTRANSLATED',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 0,
      ),
      'type' => 'options_onoff',
      'weight' => 6,
    ),
  );

  // Exported field_instance:
  // 'node-localize_fields_test-field_lclzflds_list_text'
  $field_instances['node-localize_fields_test-field_lclzflds_list_text'] = array(
    'bundle' => 'localize_fields_test',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Text list help: [current-date:short] LOCALIZE_FIELDS_UNTRANSLATED',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 7,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_lclzflds_list_text',
    'label' => 'Text list LOCALIZE_FIELDS_UNTRANSLATED',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 8,
    ),
  );

  // Exported field_instance: 'node-localize_fields_test-field_lclzflds_term'
  $field_instances['node-localize_fields_test-field_lclzflds_term'] = array(
    'bundle' => 'localize_fields_test',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Term reference help: [current-date:short] LOCALIZE_FIELDS_UNTRANSLATED',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 9,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_lclzflds_term',
    'label' => 'Term reference LOCALIZE_FIELDS_UNTRANSLATED',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'taxonomy',
      'settings' => array(
        'autocomplete_path' => 'taxonomy/autocomplete',
        'size' => 60,
      ),
      'type' => 'taxonomy_autocomplete',
      'weight' => 13,
    ),
  );

  // Exported field_instance: 'node-localize_fields_test-field_lclzflds_text'
  $field_instances['node-localize_fields_test-field_lclzflds_text'] = array(
    'bundle' => 'localize_fields_test',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Text help: [current-date:short] LOCALIZE_FIELDS_UNTRANSLATED',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 4,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_lclzflds_text',
    'label' => 'Text LOCALIZE_FIELDS_UNTRANSLATED',
    'required' => 1,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 1,
    ),
  );

  // Exported field_instance:
  // 'node-localize_fields_test-field_lclzflds_text_multi'
  $field_instances['node-localize_fields_test-field_lclzflds_text_multi'] = array(
    'bundle' => 'localize_fields_test',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Multiple texts help LOCALIZE_FIELDS_UNTRANSLATED',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 11,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_lclzflds_text_multi',
    'label' => 'Multiple texts LOCALIZE_FIELDS_UNTRANSLATED',
    'required' => 1,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 2,
    ),
  );

  // Exported field_instance:
  // 'node-localize_fields_test-field_lclzflds_textlong'
  $field_instances['node-localize_fields_test-field_lclzflds_textlong'] = array(
    'bundle' => 'localize_fields_test',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Long text help: [current-date:short] LOCALIZE_FIELDS_UNTRANSLATED',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 5,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_lclzflds_textlong',
    'label' => 'Long text LOCALIZE_FIELDS_UNTRANSLATED',
    'required' => 1,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 1,
      ),
      'type' => 'text_textarea',
      'weight' => 3,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.

  // Translatables created/updated by the Localize Fields (localize_fields) module.
  t('Multiple dates to dates LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:field_lclzflds_fieldcol-field_lclzflds_date_to_multi:label'));
  t('Multiple dates to dates help LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:field_lclzflds_fieldcol-field_lclzflds_date_to_multi:description'));
  t('Multiple field collections LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:field_lclzflds_fieldcol-field_lclzflds_fieldcol_multi:label'));
  t('Multiple field collections help LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:field_lclzflds_fieldcol-field_lclzflds_fieldcol_multi:description'));
  t('File LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:field_lclzflds_fieldcol-field_lclzflds_file:label'));
  t('File help: [current-date:short] LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:field_lclzflds_fieldcol-field_lclzflds_file:description'));
  t('Multiple integers LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:field_lclzflds_fieldcol-field_lclzflds_integer_multi:label'));
  t('Multiple integers help LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:field_lclzflds_fieldcol-field_lclzflds_integer_multi:description'));
  t('Multiple integers prefix LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:field_lclzflds_fieldcol-field_lclzflds_integer_multi:prefix'));
  t('Multiple integers suffix LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:field_lclzflds_fieldcol-field_lclzflds_integer_multi:suffix'));
  t('Boolean list LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:field_lclzflds_fieldcol-field_lclzflds_list_bool:label'));
  t('Boolean list help: [current-date:short] LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:field_lclzflds_fieldcol-field_lclzflds_list_bool:description'));
  t('Text list checkboxes LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:field_lclzflds_fieldcol-field_lclzflds_list_text_check:label'));
  t('Text list checkboxes help: [current-date:short] LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:field_lclzflds_fieldcol-field_lclzflds_list_text_check:description'));
  t('Text LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:field_lclzflds_fieldcol-field_lclzflds_text:label'));
  t('Text help: [current-date:short] LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:field_lclzflds_fieldcol-field_lclzflds_text:description'));
  t('Decimal LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:field_lclzflds_fieldcol_multi-field_lclzflds_decimal:label'));
  t('Decimal help: [current-date:short] LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:field_lclzflds_fieldcol_multi-field_lclzflds_decimal:description'));
  t('Decimal prefix LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:field_lclzflds_fieldcol_multi-field_lclzflds_decimal:prefix'));
  t('Decimal suffix LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:field_lclzflds_fieldcol_multi-field_lclzflds_decimal:suffix'));
  t('Multiple images LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:field_lclzflds_fieldcol_multi-field_lclzflds_image_multi:label'));
  t('Multiple images help: [current-date:short] LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:field_lclzflds_fieldcol_multi-field_lclzflds_image_multi:description'));
  t('Multiple texts LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:field_lclzflds_fieldcol_multi-field_lclzflds_text_multi:label'));
  t('Multiple texts help LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:field_lclzflds_fieldcol_multi-field_lclzflds_text_multi:description'));
  t('Body LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:localize_fields_test-body:label'));
  t('Body help: [current-date:short] LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:localize_fields_test-body:description'));
  t('Boolean list radio LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:localize_fields_test-field_lclzflds_bool_radio:label'));
  t('Boolean list radio help: [current-date:short] LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:localize_fields_test-field_lclzflds_bool_radio:description'));
  t('Date LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:localize_fields_test-field_lclzflds_date:label'));
  t('Date help: [current-date:short] LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:localize_fields_test-field_lclzflds_date:description'));
  t('Decimal LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:localize_fields_test-field_lclzflds_decimal:label'));
  t('Decimal help: [current-date:short] LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:localize_fields_test-field_lclzflds_decimal:description'));
  t('Decimal prefix LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:localize_fields_test-field_lclzflds_decimal:prefix'));
  t('Decimal puffix LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:localize_fields_test-field_lclzflds_decimal:suffix'));
  t('Field collection LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:localize_fields_test-field_lclzflds_fieldcol:label'));
  t('Field collection help: [current-date:short] LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:localize_fields_test-field_lclzflds_fieldcol:description'));
  t('Multiple \'field\' "collections" LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:localize_fields_test-field_lclzflds_fieldcol_multi:label'));
  t('Multiple \'field collections\' "help" LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:localize_fields_test-field_lclzflds_fieldcol_multi:description'));
  t('File LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:localize_fields_test-field_lclzflds_file:label'));
  t('File help: [current-date:short] LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:localize_fields_test-field_lclzflds_file:description'));
  t('Multiple files LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:localize_fields_test-field_lclzflds_file_multi:label'));
  t('Multiple files help: [current-date:short] LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:localize_fields_test-field_lclzflds_file_multi:description'));
  t('Image LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:localize_fields_test-field_lclzflds_image:label'));
  t('Image help: [current-date:short] LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:localize_fields_test-field_lclzflds_image:description'));
  t('Multiple images LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:localize_fields_test-field_lclzflds_image_multi:label'));
  t('Multiple images help: [current-date:short] LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:localize_fields_test-field_lclzflds_image_multi:description'));
  t('Integer with \'HTML\' "escaped" label', array(), array('context' => 'field_instance:localize_fields_test-field_lclzflds_integer_encoded:label'));
  t('Integer with \'HTML\' "escaped" description', array(), array('context' => 'field_instance:localize_fields_test-field_lclzflds_integer_encoded:description'));
  t('Multiple integers LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:localize_fields_test-field_lclzflds_integer_multi:label'));
  t('Multiple integers help LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:localize_fields_test-field_lclzflds_integer_multi:description'));
  t('Integer prefix LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:localize_fields_test-field_lclzflds_integer_multi:prefix'));
  t('Integer suffix LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:localize_fields_test-field_lclzflds_integer_multi:suffix'));
  t('Boolean list LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:localize_fields_test-field_lclzflds_list_bool:label'));
  t('Boolean list help: [current-date:short] LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:localize_fields_test-field_lclzflds_list_bool:description'));
  t('Text list LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:localize_fields_test-field_lclzflds_list_text:label'));
  t('Text list help: [current-date:short] LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:localize_fields_test-field_lclzflds_list_text:description'));
  t('Term reference LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:localize_fields_test-field_lclzflds_term:label'));
  t('Term reference help: [current-date:short] LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:localize_fields_test-field_lclzflds_term:description'));
  t('Text LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:localize_fields_test-field_lclzflds_text:label'));
  t('Text help: [current-date:short] LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:localize_fields_test-field_lclzflds_text:description'));
  t('Multiple texts LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:localize_fields_test-field_lclzflds_text_multi:label'));
  t('Multiple texts help LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:localize_fields_test-field_lclzflds_text_multi:description'));
  t('Long text LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:localize_fields_test-field_lclzflds_textlong:label'));
  t('Long text help: [current-date:short] LOCALIZE_FIELDS_UNTRANSLATED', array(), array('context' => 'field_instance:localize_fields_test-field_lclzflds_textlong:description'));


  return $field_instances;
}
