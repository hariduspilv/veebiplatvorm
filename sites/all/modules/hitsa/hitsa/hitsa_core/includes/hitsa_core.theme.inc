<?php

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
  
  $items['gmap_picker'] = array(
    'render element' => 'gmap',
    'template' => 'gmap-location-picker',
    'path' => drupal_get_path('module', 'hitsa_core') . '/theme',
  );
  
  return $items;
}

function hitsa_core_preprocess_webform_form(&$vars) {
  if(!empty($vars['form']['actions']['#attributes']['class'])) {
    unset($vars['form']['actions']['#attributes']['class']);
  }
}

function hitsa_core_preprocess_page(&$variables) {
  if(drupal_is_front_page()) {
    // Front page specific additions
    if(module_exists('hitsa_articles')) {
      
    }
  }
}

/**
 * Implements hook_preprocess_HOOK().
 */
function hitsa_core_preprocess_hitsa_header(&$variables) {
  // Load main menu
  $hitsa_main_menu_name = variable_get('hitsa_main_menu_name');
  if(!empty($hitsa_main_menu_name)) {
    $main_menu = menu_tree_all_data($hitsa_main_menu_name);
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
    '%s<br>%s<br>%s<br><a href="mailto:%s">%s</a>',
    check_plain($general_contact_name), 
    check_plain($general_contact_address), 
    check_plain($general_contact_phone_nr), 
    check_plain($general_contact_email), 
    check_plain($general_contact_email)
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
}