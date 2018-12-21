<?php

function hitsa_content_page_theme()
{
  $items['content_page_subpage_grid'] = array(
    'template' => 'content-page-subpage-grid',
    'path' => drupal_get_path('module', 'hitsa_content_page') . '/templates',
    'variables' => array(
      'nodes' => null,
      'titles' => null,
    ),
  );

  $items['content_page_subpage_list'] = array(
    'template' => 'content-page-subpage-list',
    'path' => drupal_get_path('module', 'hitsa_content_page') . '/templates',
    'variables' => array(
      'active_subpage' => null,
      'subpages' => null,
      'titles' => null,
    ),
  );

  $items['content_page_subpage_content'] = array(
    'template' => 'content-page-subpage-content',
    'path' => drupal_get_path('module', 'hitsa_content_page') . '/templates',
    'variables' => array(
      'subpage' => null,
    ),
  );

  $items['hitsa_content_page_teaser'] = array(
    'template' => 'hitsa-content-page-teaser',
    'path' => drupal_get_path('module', 'hitsa_content_page') . '/templates',
    'variables' => array(
      'subpage' => null,
      'placeholder_image_url' => hitsa_core_get_placeholder_image(),
    ),
  );

  $items['hitsa_service_teaser'] = array(
    'template' => 'hitsa-service-teaser',
    'path' => drupal_get_path('module', 'hitsa_content_page') . '/templates',
    'variables' => array(
      'node' => null,
    ),
  );

  $items['content_page_grid'] = array(
    'template' => 'hitsa-content-page',
    'path' => drupal_get_path('module', 'hitsa_content_page') . '/templates',
    'variables' => array(
      'nodes' => null,
      'search_placheholder' => null,
    ),
  );

  $items['content_output'] = array(
    'template' => 'hitsa-content-output',
    'path' => drupal_get_path('module', 'hitsa_content_page') . '/templates',
    'variables' => array(
      'nodes' => null,
      'pager' => null,
      'academic_year' => null,
    ),
  );

  return $items;
}

function hitsa_content_page_preprocess_node(&$variables)
{
  if ($variables['type'] === 'content_page') {
    if ($variables['view_mode'] === 'full') {
      if (!empty($variables['cp_type']) && $variables['cp_type'][0]['value'] === 'cp_service') {
        $more_services = hitsa_content_page_get_more_services_block_nodes($variables);
        $services_rendered = array();
        foreach ($more_services as $service) {
          $services_rendered[] = theme('hitsa_service_teaser', array('node' => $service));
        }
        $variables['more_services'] = $services_rendered;
        $variables['more_services_title'] = t('More services');
        $variables['more_services_link'] = '<a href="' . url('services') . '" class="btn sm-stretch">' . t('All services') . '</a>';
      }
      if(!empty($variables['field_contacts'])){
        if(function_exists('hitsa_curriculum_contacts')){
          $variables['contacts_block'] = hitsa_curriculum_contacts($variables['field_contacts']);
        }
      }
      // Add webform
      if (!empty($variables['cp_webform_ref'])) {
        $nid = $variables['cp_webform_ref'][0]['target_id'];
        $variables['webform'] = module_invoke('webform', 'block_view', 'client-block-' . $nid);
      }
      if (!empty($variables['cp_subpages']) && !empty($variables['cp_display_style'])) {
        $variables['subpages'] = hitsa_content_page_prepare_subpage_block($variables['cp_subpages'], $variables['cp_display_style'][0]['value']);
      }
      if (!empty($variables['cp_type']) && $variables['cp_type'][0]['value'] === 'cp_contacts') {
        if (module_exists('hitsa_contacts')) {
          $variables['contact_filter'] = hitsa_contacts_filter_widget($variables['nid']);
        }
      }
    }
  }
}

function hitsa_content_page_preprocess_content_page_grid(&$variables)
{
}

function hitsa_content_page_prepare_subpage_block($subpage_arrays, $display_style)
{
  $subpage_titles = array();
  $subpages = array();

  $active_subpage_pid = !empty(drupal_get_query_parameters()['subpage']) ? drupal_get_query_parameters()['subpage'] : null;
  foreach ($subpage_arrays as $delta => $subpage_array) {

    $subpage_paragraph = paragraphs_item_load($subpage_array['value']);
    $emw_paragraph = entity_metadata_wrapper('paragraphs_item', $subpage_paragraph);
    $subpage_titles[] = $emw_paragraph->subpage_title->value();

    if ($display_style === 'grid') {
      $subpages[$delta][] = theme('hitsa_content_page_teaser', array('subpage' => $emw_paragraph->value()));
    } else if ($display_style === 'tabbed') {
      if ($active_subpage_pid === $emw_paragraph->getIdentifier() || (empty($active_subpage_pid) && empty($subpages))) {
        $active_subpage = array('#theme' => 'content_page_subpage_content', 'subpage' => $emw_paragraph->value());
      }
      $subpages[$delta][] = $emw_paragraph->value();
    }
  }

  $output = '';
  switch ($display_style) {
    case 'grid':
      $output = theme('content_page_subpage_grid', array('nodes' => $subpages, 'titles' => $subpage_titles));
      break;
    case 'tabbed':
      $output = theme('content_page_subpage_list', array('active_subpage' => $active_subpage, 'subpages' => $subpages, 'titles' => $subpage_titles));
      break;
  }
  return $output;
}

function hitsa_content_page_services_block()
{
  $services_menu_mlid = variable_get('hitsa_services_mlid');
  $output = '';
  
  if (!empty($services_menu_mlid)) {
    $tree = menu_tree_all_data('hitsa-main-menu');
    foreach ($tree as $child) {
      if ($child['link']['mlid'] == $services_menu_mlid) {
        $services_menu = $child;
        $no_services = true;
        foreach ($services_menu['below'] as $service_subtype) {
          if (!empty($service_subtype['below'])) {
            $no_services = false;
          }
        }
        if ($no_services) {
          // No active services, don't render the block.
          return '';
        }
        break;
      }
    }
  }
  if (!empty($services_menu)) {
    $services_menu_render = menu_tree_output($services_menu['below']);
    $services_menu_render['#theme_wrappers'] = array('menu_tree__hitsa_services_block');
    $output .= render($services_menu_render);
  }
  return $output;
}

function hitsa_content_page_service_page_view($filter = false)
{
  $query = drupal_get_query_parameters();
  $query['range'] = empty($query['range']) ? array(0, 12) : $query['range'];
  $query['pager'] = 12;
  $query['entity_type'] = 'node';
  $query['bundle'] = 'content_page';
  $query['cp_type'] = 'cp_service';
  $query['status'] = NODE_PUBLISHED;
  $query['order_by'] = array('parameter' => 'created', 'direction' => 'DESC');

  return hitsa_services_page_view($query);
}

function hitsa_services_page_view($query = array())
{
  if ($result = hitsa_content_page_query_content($query, true)) {
    $nids_array = !empty($result['content']) ? $result['content'] : null;
  }

  if (!empty($nids_array['node'])) {
    $nodes = node_load_multiple(array_keys($nids_array['node']));

    $services_grouped = array();


    // Group services by service type
    foreach ($nodes as $node) {
      if (!empty($node->cp_service_type)) {
        $services_grouped[$node->cp_service_type[LANGUAGE_NONE][0]['value']][] = $node;
      }
    }

    $field = field_info_field('cp_service_type');
    $service_types = list_allowed_values($field);

    foreach ($service_types as &$s_type) {
      $s_type = t($s_type);
    }

    $services_grouped = array_reverse($services_grouped);

    $services_output = '';
    foreach ($services_grouped as $type => $service_group) {
      $service_type = $service_types[$type];
      $services_output .= '<div class="row"><div class="col-12"><h3 id="' . $service_type . '"><span class="sm-hide">' . $service_type . '</span><span class="sm-show">' . $service_type . '</span></h3></div><!--/col-12--></div>';
      $services_output .= '<div class="row row-vertical-xl">';
      foreach ($service_group as $node) {
        $node_rendered = node_view($node);
        $services_output .= theme('hitsa_service_teaser', array('node' => $node));
      }
      $services_output .= '</div>';
    }

  }

  return theme(
    'content_page_grid',
    array(
      'output' => $services_output,
      'bundle' => 'content_page',
    )
  );
}

function hitsa_content_page_view($query = array(), $filter = false, $type = null)
{
  // Load academic years taxonomy
  $academic_years_vid = variable_get('hitsa_academic_years_vid');
  $academic_years = array_reverse(taxonomy_get_tree($academic_years_vid));

  // Load nodes
  if ($result = hitsa_content_page_query_content($query, true)) {
    $nids_array = !empty($result['content']) ? $result['content'] : null;
  }

  if (!empty($nids_array['node'])) {
    $nodes = node_load_multiple(array_keys($nids_array['node']));

    // Sort and group the content based on the academic year.
    $articles_grouped = array();

    foreach ($nodes as $node) {
      $author = user_load($node->uid);
      if (!empty($node->academic_year[LANGUAGE_NONE][0]['tid'])) {
        $articles_grouped[$node->academic_year[LANGUAGE_NONE][0]['tid']][] = theme('hitsa_content_page_teaser', array('node' => $node, 'author' => $author));
      }
      // TODO: Handle content without set academic year.
    }

    $articles_grouped_sorted = array();
    $academic_years_keyed = array();
    foreach ($academic_years as $academic_year) {
      $academic_years_keyed[$academic_year->tid] = $academic_year->name;
      if (isset($articles_grouped[$academic_year->tid])) {
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

  $output = theme(
    'content_output',
    array(
      'nodes' => !empty($articles_grouped_sorted) ? $articles_grouped_sorted : array(),
      'academic_year_keyed' => !empty($academic_years_keyed) ? $academic_years_keyed : array(),
      'authors' => !empty($authors) ? $authors : array(),
      'pager' => $pager,
      'bundle' => !empty($query['bundle']) ? $query['bundle'] : null,
    )
  );

  switch ($type) {
    case 'news':
      $search_placeholder = t('Search news');
      break;
    case 'gallery':
      $search_placeholder = t('Search gallery');
      break;
    default:
      $search_placeholder = t('Start typing');
      break;
  }

  if ($filter) {
    return $output;
  } else {
    return theme(
      'content_page_grid',
      array(
        'academic_years' => $academic_years,
        'output' => $output,
        'bundle' => !empty($query['bundle']) ? $query['bundle'] : null,
        'content_type' => !empty($query['article_type']) ? $query['article_type'] : $type,
        'search_placeholder' => $search_placeholder,
      )
    );
  }

}
