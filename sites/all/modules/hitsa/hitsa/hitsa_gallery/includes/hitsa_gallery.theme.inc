<?php

/**
 * Implements hook_theme_registry_alter().
 */
function hitsa_gallery_theme_registry_alter(&$theme_registry) {
  // Defined path to the current module.
  $module_path = drupal_get_path('module', 'hitsa_gallery');
  // Find all .tpl.php files in this module's folder recursively.
  $template_file_objects = drupal_find_theme_templates($theme_registry, '.tpl.php', $module_path);
  // Iterate through all found template file objects.
  foreach ($template_file_objects as $key => $template_file_object) {
    // If the template has not already been overridden by a theme.
    if (!isset($theme_registry[$key]['theme path']) || !preg_match('#/themes/#', $theme_registry[$key]['theme path'])) {
      // Alter the theme path and template elements.
      $theme_registry[$key]['theme path'] = $module_path;
      $theme_registry[$key] = array_merge($theme_registry[$key], $template_file_object);
      $theme_registry[$key]['type'] = 'module';
    }
  }
}

function hitsa_gallery_theme() {
  $items = array();
  
  $items['gallery_grid'] = array(
    'render element' => 'grid',
  );
  
  return $items;
}

function hitsa_gallery_preprocess_node(&$variables) {
  if($variables['view_mode'] === 'full' && $variables['type'] === 'gallery') {
    if(!empty($variables['content']['gallery_images'])) {
      $variables['content']['gallery_images']['#theme'] = 'gallery_grid';
    }
  }
}

function hitsa_gallery_page_view($filter = FALSE) {
  $query = drupal_get_query_parameters();
  $query['range'] = empty($query['range']) ? array(0, 12) : $query['range'];
  $query['pager'] = 12;
  $query['entity_type'] = 'node';
  $query['bundle'] = 'gallery';
  $query['status'] = NODE_PUBLISHED;
  $query['order_by'] = array('parameter' => 'created', 'direction' => 'DESC');
  
  return hitsa_content_page_view($query, $filter, 'gallery');
}