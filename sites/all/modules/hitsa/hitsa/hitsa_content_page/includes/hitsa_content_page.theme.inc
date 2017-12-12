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
  
  $items['hitsa_service_teaser'] = array(
    'template' => 'hitsa-service-teaser',
    'path' => drupal_get_path('module', 'hitsa_content_page') . '/templates',
    'variables' => array(
      'node' => NULL,
    ),
  );
  
  $items['content_page_grid'] = array(
    'template' => 'hitsa-content-page',
    'path' => drupal_get_path('module', 'hitsa_content_page') . '/templates',
    'variables' => array(
      'nodes' => NULL,
    ),
  );
  
  $items['content_output'] = array(
    'template' => 'hitsa-content-output',
    'path' => drupal_get_path('module', 'hitsa_content_page') . '/templates',
    'variables' => array(
      'nodes' => NULL,
      'pager' => NULL,
      'academic_year' => NULL,
    ),
  );
  
  return $items;
}

function hitsa_content_page_preprocess_node(&$variables) {
  if($variables['type'] === 'content_page') {
    if($variables['view_mode'] === 'full') {
      if(!empty($variables['cp_type']) && $variables['cp_type'][0]['value'] === 'cp_service') {
        $more_services = hitsa_content_page_get_more_services_block_nodes($variables);
        $services_rendered = array();
        foreach($more_services as $service) {
          $services_rendered[] = theme('hitsa_service_teaser', array('node' => $service));
        }
        $variables['more_services'] = $services_rendered;
        $variables['more_services_title'] = t('More services');
      }
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

function hitsa_content_page_preprocess_content_page_grid(&$variables) {
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

function hitsa_content_page_view($query = array(), $filter = FALSE, $type = NULL) {
  // Load academic years taxonomy
  $academic_years_vid = variable_get('hitsa_academic_years_vid');
  $academic_years = array_reverse(taxonomy_get_tree($academic_years_vid));
  
  // Load nodes
  if($result = hitsa_content_page_query_content($query, TRUE)) {
    $nids_array = !empty($result['content']) ? $result['content'] : NULL;
  }

  if(!empty($nids_array['node'])) {
    $nodes = node_load_multiple(array_keys($nids_array['node']));
    
    // Sort and group the content based on the academic year.
    $articles_grouped = array();

    foreach($nodes as $node) {
      $author = user_load($node->uid);
      if(!empty($node->academic_year[LANGUAGE_NONE][0]['tid'])) {
        $articles_grouped[$node->academic_year[LANGUAGE_NONE][0]['tid']][] = theme('hitsa_content_page_teaser', array('node' => $node, 'author' => $author));
      }
      // TODO: Handle content without set academic year. 
    }
    
    $articles_grouped_sorted = array();
    $academic_years_keyed = array();
    foreach($academic_years as $academic_year) {
      $academic_years_keyed[$academic_year->tid] = $academic_year->name;
      if(isset($articles_grouped[$academic_year->tid])) {
        $articles_grouped_sorted[$academic_year->tid] = array_merge($articles_grouped[$academic_year->tid]);
      }
    }

  }

  // Pager
  $quantity = ceil($result['count'] / 12);
  
  $per_page = 12;
  $current_page = pager_default_initialize($result['count'], 12);

  $pager = hitsa_pager(
    array(
      'tags' => array(),
      'element' => 0,
      'parameters' => array(),
      'quantity' => $quantity,
      'pager_current' => !empty($query['page']) ? $query['page'] : 1
    )
  );

  $output = theme('content_output',
    array(
      'nodes' => !empty($articles_grouped_sorted) ? $articles_grouped_sorted : array(),
      'academic_year_keyed' => !empty($academic_years_keyed) ? $academic_years_keyed : array(),
      'authors' => !empty($authors) ? $authors : array(),
      'pager' => $pager,
      'bundle' => !empty($query['bundle']) ? $query['bundle'] : NULL,
    )
  );

  
  if($filter) {
    return $output;
  } else {
    return theme(
      'content_page_grid',
      array(
        'academic_years' => $academic_years,
        'output' => $output,
        'bundle' => !empty($query['bundle']) ? $query['bundle'] : NULL,
        'content_type' => $type,
      )
    );
  }
  
}