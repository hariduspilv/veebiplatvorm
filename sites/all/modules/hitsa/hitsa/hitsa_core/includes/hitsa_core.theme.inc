<?php

/**
 * Implements hook_theme().
 */
function hitsa_core_theme() {
  $items['hitsa_header'] = array(
    'render element' => 'header',
    'template' => 'header',
    'path' => drupal_get_path('theme', 'hitsa') . '/templates/include',
  );
  
  $items['hitsa_footer'] = array(
    'render element' => 'footer',
    'template' => 'footer',
    'path' => drupal_get_path('theme', 'hitsa') . '/templates/include',
  );
  
  $items['submenu_tree'] = array(
    'variables' => array(
      'submenu' => NULL,
      'parent' => NULL,
    ),
  );
  
  $items['header_menu_tree'] = array(
    'render element' => 'tree',
  );
  
  $items['quicklinks_menu_tree'] = array(
    'render element' => 'tree',
  );
  
  return $items;
}

function hitsa_core_preprocess_webform_form(&$vars) {
  if(!empty($vars['form']['actions']['#attributes']['class'])) {
    unset($vars['form']['actions']['#attributes']['class']);
  }
}