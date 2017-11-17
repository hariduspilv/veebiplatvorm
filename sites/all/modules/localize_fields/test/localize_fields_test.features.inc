<?php
/**
 * @file
 * localize_fields_test.features.inc
 */

/**
 * Implements hook_node_info().
 */
function localize_fields_test_node_info() {
  $items = array(
    'localize_fields_test' => array(
      'name' => t('Localize Fields test'),
      'base' => 'node_content',
      'description' => t('Test translation of field labels.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
