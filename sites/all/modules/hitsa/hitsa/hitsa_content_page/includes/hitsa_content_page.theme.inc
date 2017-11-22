<?php

function hitsa_content_page_theme() {
  $items['content_page_subpage_grid'] = array(
    'template' => 'content-page-subpage-grid',
    'path' => drupal_get_path('module', 'hitsa_content_page') . '/templates',
    'variables' => array(
      'nodes' => NULL,
      'titles' => NULL,
    ),
  );
  
  $items['content_page_subpage_list'] = array(
    'template' => 'content-page-subpage-list',
    'path' => drupal_get_path('module', 'hitsa_content_page') . '/templates',
    'variables' => array(
      'active_subpage' => NULL,
      'subpages' => NULL,
      'titles' => NULL,
    ),
  );
  
  $items['content_page_subpage_content'] = array(
    'template' => 'content-page-subpage-content',
    'path' => drupal_get_path('module', 'hitsa_content_page') . '/templates',
    'variables' => array(
      'subpage' => NULL,
    ),
  );
  
  $items['hitsa_content_page_teaser'] = array(
    'template' => 'hitsa-content-page-teaser',
    'path' => drupal_get_path('module', 'hitsa_content_page') . '/templates',
    'variables' => array(
      'subpage' => NULL,
    ),
  );
  
  return $items;
}

function hitsa_content_page_preprocess_node(&$variables) {
  if($variables['type'] === 'content_page') {
    if($variables['view_mode'] === 'full') {
      // Add webform
      if(!empty($variables['cp_webform_ref'])) {
        $nid = $variables['cp_webform_ref'][0]['target_id'];
        $variables['webform'] = module_invoke('webform', 'block_view', 'client-block-' . $nid);
      }
      if(!empty($variables['cp_subpages']) && !empty($variables['cp_display_style'])) {
        $variables['subpages'] = hitsa_content_page_prepare_subpage_block($variables['cp_subpages'], $variables['cp_display_style'][0]['value']);
      }
      
    }
  }
}

function hitsa_content_page_prepare_subpage_block($subpage_arrays, $display_style) {
  $subpage_titles = array();
  $subpages = array();
  
  $active_subpage_pid = !empty(drupal_get_query_parameters()['subpage']) ? drupal_get_query_parameters()['subpage'] : NULL;
  foreach($subpage_arrays as $delta => $subpage_array) {
    
    $subpage_paragraph = paragraphs_item_load($subpage_array['value']);
    $emw_paragraph = entity_metadata_wrapper('paragraphs_item', $subpage_paragraph);
    $subpage_titles[] = $emw_paragraph->subpage_title->value();
    
    if($display_style === 'grid') {
      $subpages[$delta][] = theme('hitsa_content_page_teaser', array('subpage' => $emw_paragraph->value()));
    } else if($display_style === 'tabbed') {
      if($active_subpage_pid === $emw_paragraph->getIdentifier() || (empty($active_subpage_pid) && empty($subpages))) {
        $active_subpage = array('#theme' => 'content_page_subpage_content', 'subpage' => $emw_paragraph->value());
      }
      $subpages[$delta][] = $emw_paragraph->value();
    }
  }
  
  $output = '';
  switch($display_style) {
    case 'grid':
      $output = theme('content_page_subpage_grid', array('nodes' => $subpages, 'titles' => $subpage_titles));
      break;
    case 'tabbed':
      $output = theme('content_page_subpage_list', array('active_subpage' => $active_subpage, 'subpages' => $subpages, 'titles' => $subpage_titles));
      break;
  }
  return $output;
}

function hitsa_content_page_services_block() {
  $services_menu_mlid = variable_get('hitsa_services_mlid');
  
  $output = '';
  
  if(!empty($services_menu_mlid)) {
    $tree = menu_tree_all_data('hitsa-main-menu');
    foreach($tree as $child) {
      if($child['link']['mlid'] == $services_menu_mlid){
        $services_menu = $child;
        break;
      }
    }
  }
  $services_menu_render = menu_tree_output($services_menu['below']);
  $services_menu_render['#theme_wrappers'] = array('menu_tree__hitsa_services_block');
  
  $output .= render($services_menu_render);
  return $output;
}