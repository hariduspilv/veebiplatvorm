<?php
/**
 * @file
 * Menu References views integration plugins.
 *
 */

/**
 * Implements hook_views_plugins().
 */
function menu_reference_views_plugins() {
  $plugins = array(
    'argument default' => array(
      'menu_trail' => array(
        'title' => t('Current page menu trail'),
        'handler' => 'menu_reference_plugin_argument_default_menu_trail',
      ),
    ),
  );

  return $plugins;
}

/**
 * Implements hook_field_views_data_alter().
 *
 * Add custom filter handler for menu reference fields.
 */
function menu_reference_field_views_data_alter(&$result, $field, $module) {
  // Change the filter handler.
  if ($module === 'menu_reference') {
    foreach ($result as $table => $data) {
      foreach ($data as $column => $value) {
        if (array_key_exists('filter', $value)) {
          $result[$table][$column]['filter']['handler'] = 'menu_references_filter_handler';
          $result[$table][$column]['filter']['allow empty'] = FALSE;
        }
      }
    }
  }
}
