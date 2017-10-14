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
      'nodes' => NULL,
      'titles' => NULL,
    ),
  );
  
  $items['content_page_subpage_content'] = array(
    'template' => 'content-page-subpage-content',
    'path' => drupal_get_path('module', 'hitsa_content_page') . '/templates',
    'variables' => array(
      'node' => NULL,
    ),
  );
  
  $items['hitsa_content_page_teaser'] = array(
    'template' => 'hitsa-content-page-teaser',
    'path' => drupal_get_path('module', 'hitsa_content_page') . '/templates',
    'variables' => array(
      'node' => NULL,
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
  $subpage_intermediate_titles = array();
  $subpage_nodes = array();
  
  $active_subpage_nid = !empty(drupal_get_query_parameters()['subpage']) ? drupal_get_query_parameters()['subpage'] : NULL;
  foreach($subpage_arrays as $delta => $subpage_array) {
    $subpage_paragraph = paragraphs_item_load($subpage_array['value']);
    $emw_paragraph = entity_metadata_wrapper('paragraphs_item', $subpage_paragraph);
    $subpage_intermediate_titles[] = $emw_paragraph->cp_intermediate_title->value();
    
    foreach($emw_paragraph->cp_subpage_ref_nid->getIterator() as $node) {
      if($display_style === 'grid') {
        $subpage_nodes[$delta][] = theme('hitsa_content_page_teaser', array('node' => $node->value()));
      } else if($display_style === 'tabbed') {
        if($active_subpage_nid === $node->getIdentifier() || (empty($active_subpage_nid) && empty($subpage_nodes))) {
          $active_subpage_node = array('#theme' => 'content_page_subpage_content', 'node' => $node->value());
        }
        $subpage_nodes[$delta][] = $node->value();
      }
    }
  }

  $output = '';
  switch($display_style) {
    case 'grid':
      $output = theme('content_page_subpage_grid', array('nodes' => $subpage_nodes, 'titles' => $subpage_intermediate_titles));
      break;
    case 'tabbed':
      $output = theme('content_page_subpage_list', array('active_node' => $active_subpage_node, 'nodes' => $subpage_nodes, 'titles' => $subpage_intermediate_titles));
      break;
  }
  return $output;
}