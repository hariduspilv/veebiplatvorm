<?php

function hitsa_alumnus_add_fields()
{
  foreach (hitsa_alumnus_field_bases() as $field) {

    $field_test = field_info_field($field['field_name']);
    if (empty($field_test)) {
      field_create_field($field);
    }
  }

  foreach (hitsa_alumnus_field_instances() as $field_instance) {
    if (empty(field_info_instance($field_instance['entity_type'], $field_instance['field_name'], $field_instance['bundle']))) {
      field_create_instance($field_instance);
    }
  }
}
function hitsa_alumnus_field_bases()
{
  $field_bases = array();

  // Exported field_base: 'field_extra_information'.
  $field_bases['field_extra_information'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_extra_information',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'entity_translation_sync' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'text_long',
  );

  // Exported field_base: 'field_full_name'.
  $field_bases['field_full_name'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_full_name',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'add_row_localization_source' => 'Add another item',
      'entity_translation_sync' => FALSE,
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  // Exported field_base: 'field_order_number'.
  $field_bases['field_order_number'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_order_number',
    'indexes' => array(),
    'locked' => 0,
    'module' => 'number',
    'settings' => array(
      'entity_translation_sync' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'number_integer',
  );

  // Exported field_base: 'field_person'.
  $field_bases['field_person'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_person',
    'indexes' => array(),
    'locked' => 0,
    'module' => 'paragraphs',
    'settings' => array(
      'entity_translation_sync' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'paragraphs',
  );

  return $field_bases;

}
function hitsa_alumnus_field_instances()
{
  $field_instances = array();

  // Exported field_instance: 'node-alumnus-field_order_number'.
  $field_instances['node-alumnus-field_order_number'] = array(
    'bundle' => 'alumnus',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => 'Siia sisestada lennu number või järjekorra number. <br>
Mida suurem number seda eespool seda kuvatakse.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => '',
        ),
        'type' => 'number_integer',
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
    'field_name' => 'field_order_number',
    'label' => 'Lennu nr/Järjekorra number',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'max' => 20000,
      'min' => 0,
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 42,
    ),
  );

  // Exported field_instance: 'node-alumnus-field_person'.
  $field_instances['node-alumnus-field_person'] = array(
    'bundle' => 'alumnus',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'paragraphs',
        'settings' => array(
          'view_mode' => 'full',
        ),
        'type' => 'paragraphs_view',
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
    'field_name' => 'field_person',
    'label' => 'Inimene',
    'required' => 0,
    'settings' => array(
      'add_mode' => 'button',
      'allowed_bundles' => array(
        'alumnus_person' => 'alumnus_person',
        'catering_food_by_day' => -1,
        'contacts' => -1,
        'contacts_department' => -1,
        'description' => -1,
        'jobs' => -1,
        'reception_time' => -1,
        'subpage' => -1,
        'table' => -1,
      ),
      'bundle_weights' => array(
        'alumnus_person' => 2,
        'catering_food_by_day' => 3,
        'contacts' => 4,
        'contacts_department' => 5,
        'description' => 6,
        'jobs' => 7,
        'reception_time' => 8,
        'subpage' => 9,
        'table' => 10,
      ),
      'default_edit_mode' => 'open',
      'entity_translation_sync' => FALSE,
      'title' => 'Inimene',
      'title_multiple' => 'Inimesed',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'paragraphs',
      'settings' => array(),
      'type' => 'paragraphs_embed',
      'weight' => 41,
    ),
  );

  // Exported field_instance:
  // 'paragraphs_item-alumnus_person-field_extra_information'.
  $field_instances['paragraphs_item-alumnus_person-field_extra_information'] = array(
    'bundle' => 'alumnus_person',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 2,
      ),
      'paragraphs_editor_preview' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'paragraphs_item',
    'field_name' => 'field_extra_information',
    'label' => 'Lisainfo',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'maxlength_js' => '',
        'maxlength_js_enforce' => 0,
        'maxlength_js_label' => 'Content limited to @limit characters, remaining: <strong>@remaining</strong>',
        'maxlength_js_truncate_html' => 0,
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'paragraphs_item-alumnus_person-field_full_name'.
  $field_instances['paragraphs_item-alumnus_person-field_full_name'] = array(
    'bundle' => 'alumnus_person',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 3,
      ),
      'paragraphs_editor_preview' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'paragraphs_item',
    'field_name' => 'field_full_name',
    'label' => 'Täisnimi',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'maxlength_js' => 0,
        'maxlength_js_label' => 'Content limited to @limit characters, remaining: <strong>@remaining</strong>',
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 0,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Inimene');
  t('Lennu nr/Järjekorra number');
  t('Lisainfo');
  t('Siia sisestada lennu number või järjekorra number. <br>
Mida suurem number seda eespool seda kuvatakse.');
  t('Täisnimi');

  return $field_instances;
}