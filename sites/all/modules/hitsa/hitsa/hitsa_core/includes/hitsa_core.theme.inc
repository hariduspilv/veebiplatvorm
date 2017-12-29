<?php

function hitsa_core_theme_registry_alter(&$theme_registry) {
  // Defined path to the current module.
  $module_path = drupal_get_path('module', 'hitsa_core');
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

/**
 * Implements hook_theme().
 */
function hitsa_core_theme() {
  $items['hitsa_front_content'] = array(
    'render element' => 'content',
    'template' => 'front',
    'path' => drupal_get_path('theme', 'hitsa') . '/templates/include',
  );
  
  $items['hitsa_header'] = array(
    'render element' => 'header',
    'template' => 'header',
    'path' => drupal_get_path('theme', 'hitsa') . '/templates/include',
  );
  
  $items['hitsa_header_mobile'] = array(
    'render element' => 'header',
    'template' => 'header-mobile',
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
  
  $items['service_menu_tree'] = array(
    'variables' => array(
      'element' => NULL,
    ),
  );
  
  $items['header_menu_tree'] = array(
    'render element' => 'tree',
  );
  
  $items['quicklinks_menu_tree'] = array(
    'render element' => 'tree',
  );
  
  $items['gmap_picker'] = array(
    'render element' => 'gmap',
    'template' => 'gmap-location-picker',
    'path' => drupal_get_path('module', 'hitsa_core') . '/theme',
  );
  
  $items['hitsa_search_result'] = array(
    'template' => 'search-result',
    'path' => drupal_get_path('module', 'hitsa_core') . '/templates/search',
    'variables' => array(
      'node' => NULL,
      'excerpt' => NULL,
      'mlid' => NULL,
    ),
  );
  
  $items['hitsa_sitemap'] = array(
    'template' => 'sitemap-page',
    'path' => drupal_get_path('module', 'hitsa_core') . '/templates',
    'variables' => array(
      'menu_tree' => NULL,
    ),
  );
  
  $items['hitsa_services_events'] = array(
    'template' => 'hitsa-services-events-block',
    'path' => drupal_get_path('theme', 'hitsa') . '/templates/block',
    'variables' => array(
      'events' => NULL,
      'services' => NULL,
    ),
  );
  
  $items['hitsa_search_page'] = array(
    'template' => 'hitsa-core-search-page',
    'path' => drupal_get_path('module', 'hitsa_core') . '/templates/search',
    'variables' => array(
      'result' => NULL,
      'category_filter' => NULL,
    ),
  );
  
  $items['hitsa_search_result'] = array(
    'template' => 'hitsa-core-search-result',
    'path' => drupal_get_path('module', 'hitsa_core') . '/templates/search',
    'variables' => array(
      'result_items' => NULL,
    ),
  );
  
  $items['hitsa_search_result_item'] = array(
    'template' => 'hitsa-core-search-result-item',
    'path' => drupal_get_path('module', 'hitsa_core') . '/templates/search',
    'variables' => array(
      'result_item' => NULL,
    ),
  );
  
  $items['hitsa_timetable'] = array(
    'template' => 'timetable',
    'path' => drupal_get_path('module', 'hitsa_core') . '/templates',
    'variables' => array(
      'result_item' => NULL,
    ),
  );
  
  $items['hitsa_login'] = array(
    'template' => 'login',
    'path' => drupal_get_path('module', 'hitsa_core') . '/templates',
    'variables' => array(
      'mobile_id_form' => NULL,
      'id_form' => NULL,
    ),
  );
  
  $items['hitsa_login_mobile_id_form'] = array(
    'render element' => 'form',
    'template' => 'login-mobile-id-form',
    'path' => drupal_get_path('module', 'hitsa_core') . '/templates',
  );
  
  return $items;
}

function hitsa_core_preprocess_webform_form(&$vars) {
  if(!empty($vars['form']['actions']['#attributes']['class'])) {
    unset($vars['form']['actions']['#attributes']['class']);
  }
}

function hitsa_core_preprocess_page(&$variables) {
  $variables['mobile_menu'] = theme('hitsa_header_mobile');
  if(drupal_is_front_page()) {
    // Front page specific additions
    if(module_exists('hitsa_articles')) {
      
    }
  }
  if(current_path() === 'login') {
    // For Mobile ID login
    drupal_add_js(drupal_get_path('module', 'hitsa_core') . '/includes/id/hitsa_core_check_status.js');
  }
}

/**
 * Implements hook_preprocess_HOOK().
 */
function hitsa_core_preprocess_hitsa_header(&$variables) {
  global $language;
  // Load main menu
  $hitsa_main_menu_name = variable_get('hitsa_main_menu_name');
  if(!empty($hitsa_main_menu_name)) {
    $main_menu = i18n_menu_localize_tree(menu_tree_all_data($hitsa_main_menu_name));
    $variables['main_menu'] = menu_tree_output($main_menu);
  }
  // Load header menu
  $hitsa_header_menu_name = variable_get('hitsa_header_menu_name');
  if(!empty($hitsa_header_menu_name)) {
    $header_menu = menu_tree_all_data($hitsa_header_menu_name);
    $variables['header_menu'] = menu_tree_output($header_menu);
    $variables['header_menu']['#theme_wrappers'] = array('header_menu_tree__hitsa_header_menu');
  }
  // Quicklinks menu
  $hitsa_quicklinks_menu_name = variable_get('hitsa_quicklinks_menu_name');
  if(!empty($hitsa_quicklinks_menu_name)) {
    $quicklinks_menu = menu_tree_all_data($hitsa_quicklinks_menu_name);
    $variables['quicklinks_menu'] = menu_tree_output($quicklinks_menu);
    $variables['quicklinks_menu']['#theme_wrappers'] = array('quicklinks_menu_tree__hitsa_quicklinks_menu');
  }
  // Language switcher
  $language_switcher = module_invoke('locale', 'block_view', 'language');
  if(!empty($language_switcher['content'])) {
    $variables['language_switcher'] = $language_switcher['content'];
  }
  // Main logo
  $site_logo_fid = variable_get_value('hitsa_site_logo_fid');
  $logo_file = file_load($site_logo_fid);
  if($logo_file) {
    $variables['site_logo'] = image_style_url('hitsa_core_logo', $logo_file->uri);
  }
}

/**
 * Implements hook_preprocess_HOOK().
 */
function hitsa_core_preprocess_hitsa_header_mobile(&$variables) {
  global $language;
  // Load main menu
  $hitsa_main_menu_name = variable_get('hitsa_main_menu_name');
  if(!empty($hitsa_main_menu_name)) {
    $main_menu = i18n_menu_localize_tree(menu_tree_all_data($hitsa_main_menu_name));
    $variables['main_menu_mobile'] = menu_tree_output($main_menu);
    $variables['main_menu_mobile']['#theme_wrappers'] = array('menu_tree__hitsa_main_menu_mobile');
  }
  // Quicklinks menu
  $hitsa_quicklinks_menu_name = variable_get('hitsa_quicklinks_menu_name');
  if(!empty($hitsa_quicklinks_menu_name)) {
    $quicklinks_menu = menu_tree_all_data($hitsa_quicklinks_menu_name);
    $variables['quicklinks_menu'] = menu_tree_output($quicklinks_menu);
    $variables['quicklinks_menu']['#theme_wrappers'] = array('quicklinks_menu_tree__hitsa_quicklinks_mobile_menu');
  }
  // Language switcher
  $language_switcher = module_invoke('hitsa_core', 'block_view', 'language_mobile');
  if(!empty($language_switcher['content'])) {
    $variables['language_switcher_mobile'] = $language_switcher['content'];
  }
  // Main logo
  $site_logo_fid = variable_get_value('hitsa_site_logo_fid');
  $logo_file = file_load($site_logo_fid);
  if($logo_file) {
    $variables['site_logo'] = image_style_url('hitsa_core_logo_mobile', $logo_file->uri);
  }
}

/**
 * Implements hook_preprocess_HOOK().
 */
function hitsa_core_preprocess_hitsa_footer(&$variables) {
  // Partners
  if(module_exists('hitsa_logos')) {
    $variables['partners'] = views_embed_view('hitsa_logos', 'partners_block');
  }
  
  // General Contact
  $general_contact_name = variable_get_value('general_contact_name');
  $general_contact_address = variable_get_value('general_contact_address');
  $general_contact_phone_nr = variable_get_value('general_contact_phone_nr');
  $general_contact_email = variable_get_value('general_contact_email');
  $variables['footer_general_contact'] = sprintf(
    '%s<br>%s<br>%s<br>%s',
    check_plain($general_contact_name), 
    check_plain($general_contact_address), 
    check_plain($general_contact_phone_nr), 
    spamspan(check_plain($general_contact_email))
  );
  
  // Important contacts
  $important_contacts = '';
  for($i = 1; $i < 5; $i++) {
    $ic_name = variable_get_value('important_contact_name_' . $i);
    $ic_phone_nr = variable_get_value('important_contact_phone_' . $i);
    if(!empty($ic_name) && !empty($ic_phone_nr)) {
      $important_contacts .= sprintf('<tr><td>%s</td><td>%s</td></tr>', check_plain($ic_name), check_plain($ic_phone_nr)); 
    }
  }
  $variables['important_contacts'] = $important_contacts;

  // Copyright notice
  $copyright_notice = variable_get_value('footer_copyright_notice');
  if(!empty($copyright_notice)) {
    $variables['copyright_notice'] = $copyright_notice;
  }
  // Footer menu
  $hitsa_footer_menu_name = variable_get('hitsa_footer_menu_name');
  if(!empty($hitsa_footer_menu_name)) {
    $footer_menu = menu_tree_all_data($hitsa_footer_menu_name);
    $variables['footer_menu'] = menu_tree_output($footer_menu);
  }
  
  // School Location Map
  $variables['google_api_key'] = variable_get_value('hitsa_google_api_key');
  $variables['hitsa_school_place_coords'] = variable_get_value('hitsa_school_place_coords');
}

function hitsa_core_menu_overview_form($variables) {
  $form = $variables['form'];

  drupal_add_tabledrag('menu-overview', 'match', 'parent', 'menu-plid', 'menu-plid', 'menu-mlid', TRUE, MENU_MAX_DEPTH - 1);
  drupal_add_tabledrag('menu-overview', 'order', 'sibling', 'menu-weight');

  $header = array(
    t('Menu link'),
    array('data' => t('Enabled'), 'class' => array('checkbox')),
    t('Weight'),
    array('data' => t('Operations'), 'colspan' => '3'),
  );

  $rows = array();
  foreach (element_children($form) as $mlid) {
    if (isset($form[$mlid]['hidden'])) {
      $element = &$form[$mlid];
      // Build a list of operations.
      $operations = array();
      foreach (element_children($element['operations']) as $op) {
        $operations[] = array('data' => drupal_render($element['operations'][$op]), 'class' => array('menu-operations'));
      }
      while (count($operations) < 2) {
        $operations[] = '';
      }

      // Add special classes to be used for tabledrag.js.
      $element['plid']['#attributes']['class'] = array('menu-plid');
      $element['mlid']['#attributes']['class'] = array('menu-mlid');
      $element['weight']['#attributes']['class'] = array('menu-weight');

      // Change the parent field to a hidden. This allows any value but hides the field.
      $element['plid']['#type'] = 'hidden';

      $row = array();
      $row[] = theme('indentation', array('size' => $element['#item']['depth'] - 1)) . drupal_render($element['title']);
      $row[] = array('data' => drupal_render($element['hidden']), 'class' => array('checkbox', 'menu-enabled'));
      $row[] = drupal_render($element['weight']) . drupal_render($element['plid']) . drupal_render($element['mlid']);
      $row = array_merge($row, $operations);

      $row = array_merge(array('data' => $row), $element['#attributes']);
      $row['class'][] = 'draggable';
      $rows[] = $row;
    }
  }
  $output = '';
  if (empty($rows)) {
    $rows[] = array(array('data' => $form['#empty_text'], 'colspan' => '7'));
  }
  $output .= theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'menu-overview')));
  $output .= drupal_render_children($form);
  
  return $output;
}

function hitsa_core_login_page() {
  drupal_page_is_cacheable(FALSE);
  $id_login_form = drupal_get_form('hitsa_core_id_login_form_card');
  $mobile_id_login_form = drupal_get_form('hitsa_core_id_login_form_mobile');
  return theme('hitsa_login', array('mobile_id_form' => $mobile_id_login_form, 'id_form' => $id_login_form));
}

function hitsa_core_search_page($filter = FALSE) {
  $query = drupal_get_query_parameters();
  if(!empty($query['query'])) {
    $search = hitsa_core_search($query);
    
    $results = $search['results'];
    $result_count = count($results);
    $results_rendered = array();
    $authors = array();
    foreach($results as $result) {
      $results_rendered[$result['entity']->type][] = theme('hitsa_search_result_item', array('result_item' => $result));
      $authors[$result['entity']->uid] = $result['entity']->uid;
    }
    
    $node_types = node_type_get_types();
    $bundle_filter = array();
    foreach($results_rendered as $bundle => $results) {
      $bundle_filter[$bundle] = $node_types[$bundle]->name;
    }
    
    $result_output = theme('hitsa_search_result', array('result_items' => $results_rendered, 'bundles' => $bundle_filter));
    
    if($filter) {
      print $result_output;
      exit;
    }
  }
  return theme('hitsa_search_page', 
  array(
    'bundle_filter' => !empty($bundle_filter) ? $bundle_filter : NULL, 
    'result_output' => !empty($result_output) ? $result_output : t('No results found!'), 
    'search_query' => !empty($query['query']) ? $query['query'] : NULL,
    'result_count' => !empty($result_count) ? $result_count : 0,
  ));
}