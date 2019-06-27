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
  if ($variables['type'] === 'event') {
    $dates = $variables['event_date'][0];
    $variables['start_date'] = date('d', $dates['value']);
    if ($dates['value'] != $dates['value2']) {
      $variables['end_date'] = format_date($dates['value'], 'custom', 'd. ' . t('M'));
    }
    if (!empty($variables['field_event_type'])) {
      $have_event = FALSE;
      $have_training = FALSE;
      foreach ($variables['field_event_type'] as $type_event) {
        if ($type_event['value'] == 'event') {
          $have_event = TRUE;
        }
        elseif ($type_event['value'] == 'training'){
          $have_training = TRUE;
        }
      }
      $variables['event_tags_correct'] = '';
      if ($have_training==TRUE) {
        if (!empty($variables['field_training_tags'])) {
          foreach ($variables['field_training_tags'] as $training_tag) {
            $variables['event_tags_correct'] .= empty($variables['event_tags_correct']) ? $training_tag['entity']->name : ', ' .
              $training_tag['entity']->name;
          }
        }
      }
      if($have_event==TRUE){
        if (!empty($variables['event_tags'])) {
          foreach ($variables['event_tags'] as $event_tag) {
            $variables['event_tags_correct'] .= empty($variables['event_tags_correct']) ? $event_tag['taxonomy_term']->name : ', ' .
              $event_tag['taxonomy_term']->name;
          }
        }
      }
      if (!empty($variables['field_pictures'])) {
        foreach ($variables['field_pictures'] as $pic_key => $field_picture) {
          $variables['field_pictures'][$pic_key] = hitsa_core_generate_single_image_figure($field_picture);
        }
      }
      if(!empty($variables['field_contacts'])){
        $variables['field_contacts'] = hitsa_curriculum_contacts($variables['field_contacts']);
      }
      if (!empty($variables['locations'])) {
        $locations = '';
        foreach ($variables['locations'] as $location) {
          $locations .= empty($locations) ? $location['taxonomy_term']->name : ', ' .
            $location['taxonomy_term']->name;
        }
        if (!empty($locations)) {
          $variables['locations'] = $locations;
        }
        else {
          unset($variables['locations']);
        }
      }
//      krumo($variables);
    }
  }
  if(!empty($variables['body'])){
    $current_host = $_SERVER['HTTP_HOST'];
    $inital_url = variable_get('hitsa_initial_path');

    if(!empty($inital_url)) {
      $variables['body_no_table'] = '';
      foreach ($variables['body'] as $body_key => $body_value) {
        $variables['body'][$body_key]['safe_value'] = str_replace($inital_url, $current_host, $body_value['safe_value']);
        $variables['body'][$body_key]['safe_summary'] = str_replace($inital_url, $current_host, $body_value['safe_summary']);
        $new_summary = $body_value['safe_summary'];
        $new_summary = htmlentities($new_summary);
        $new_summary = str_replace(' ','',$new_summary);
        $new_summary = str_replace( '&nbsp','',strval($new_summary));
        $new_summary = str_replace( '<p>','',strval($new_summary));
        $new_summary = str_replace( "</p>",'',strval($new_summary));
        $new_summary = str_replace( '&lt;','',strval($new_summary));
        $new_summary = str_replace( 'p&gt;','',strval($new_summary));
        $new_summary = str_replace( ';/','',strval($new_summary));
        $new_summary = rtrim($new_summary);
        $new_summary = trim($new_summary);
        if(empty($new_summary)){
          $variables['body'][$body_key]['safe_summary']='';
        }

        $tables = '';
        $doc_summary = new DOMDocument();
        $decoded_summary = utf8_decode($body_value['summary']);
        $doc_summary->loadHTML($decoded_summary);
        $doc_summary->preserveWhiteSpace = false;
        $table  = $doc_summary->getElementsByTagName('table');
        $i=0;
        foreach ($table as $part){
          $tables.='<table>';
          $rows = $part->getElementsByTagName('tr');
          foreach ($rows as $row){
            $tables.='<tr>';
            $cols = $row->getElementsByTagName('td');
            foreach ($cols as $col){
              $value = $col->nodeValue;
              $tables.='<td>'.$value.'</td>';
            }
            $tables.='</tr>';
          }
          $tables.='</table>';
        }

        $xpath_summary = new DOMXPath($doc_summary);
        foreach ($xpath_summary->query('//table') as $summary) {
          $summary->parentNode->removeChild($summary);
        }
        $summary_no_table = $doc_summary->saveHTML();
        $summary_no_table= str_replace('<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN" "http://www.w3.org/TR/REC-html40/loose.dtd">
<html><body>','',$summary_no_table);
        $summary_no_table = str_replace('</body></html>','',$summary_no_table);
        $summary_no_table = str_replace('&nbsp', '', strval( $summary_no_table));
        $summary_no_table = str_replace('<p>', '', strval( $summary_no_table));
        $summary_no_table = str_replace("</p>", '', strval( $summary_no_table));
        $summary_no_table = str_replace(";", '', strval( $summary_no_table));
        $summary_no_table = trim($summary_no_table);
        if(empty($summary_no_table)){
          $variables['only_table'] = true;
        }
        $variables['body'][$body_key]['safe_summary']=str_replace('<table','<table class="sm-hide" ',$variables['body'][$body_key]['safe_summary']);
        $variables['body'][$body_key]['safe_value']=str_replace('<table','<table class="sm-hide" ',$variables['body'][$body_key]['safe_value']);
        if (strpos($variables['body'][$body_key]['safe_summary'], '<table') !== false) {
          $variables['header_table']= true;
        }

        $doc = new DOMDocument();
        $decoded = utf8_decode($body_value['value']);
        $doc->loadHTML($decoded);
        $doc->preserveWhiteSpace = false;
        $table  = $doc->getElementsByTagName('table');
//        $tables = '';
        $i=0;
        foreach ($table as $part){
          $tables.='<table>';
          $rows = $part->getElementsByTagName('tr');
          foreach ($rows as $row){
            $tables.='<tr>';
            $cols = $row->getElementsByTagName('td');
            foreach ($cols as $col){
              $value = $col->nodeValue;
              $tables.='<td>'.$value.'</td>';
            }
            $tables.='</tr>';
          }
          $tables.='</table>';

        }
        if(!empty($tables)){
          $variables['tables'] = $tables;
        }
        $xpath = new DOMXPath($doc);
        foreach ($xpath->query('//table') as $node) {
          $node->parentNode->removeChild($node);
        }
        $body_no_table = $doc->saveHTML();
        $body_no_table_original = $body_no_table;
      }

    }
    $body_no_table= str_replace('<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN" "http://www.w3.org/TR/REC-html40/loose.dtd">
<html><body>','',$body_no_table);
    $body_no_table = str_replace('</body></html>','',$body_no_table);
    $body_no_table = str_replace('&nbsp', '', strval( $body_no_table));
    $body_no_table = str_replace('<p>', '', strval( $body_no_table));
    $body_no_table = str_replace("</p>", '', strval( $body_no_table));
    $body_no_table = str_replace(";", '', strval( $body_no_table));
    $body_no_table = trim($body_no_table);
    if(empty($body_no_table)){
      $variables['mobile_body'][$body_key]['safe_value'] = '';
      $variables['mobile_body'][$body_key]['value'] = '';
    }
    else{
      $body_no_table = $body_no_table_original;
      $body_no_table= str_replace('<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN" "http://www.w3.org/TR/REC-html40/loose.dtd">
<html><body>','',$body_no_table);
      $body_no_table = str_replace('</body></html>','',$body_no_table);

      $body_no_table = str_replace('&nbsp;', '', strval( $body_no_table));

    }
    if(strlen($body_no_table)>1000){
      $your_desired_width = 1000;
        $break_point = mb_strrpos(mb_substr($body_no_table, 0, $your_desired_width,'UTF-8'), ' ');
        $start = mb_substr($body_no_table, 0, $break_point,'UTF-8');
        $end = mb_substr($body_no_table, $break_point,  mb_strlen($body_no_table,'UTF-8'));
        $start = utf8_encode($start);
        $end = utf8_encode($end);
        $variables['start'] = $start;
        $variables['end']=$end;
    }
    else{
      $variables['start'] = $body_no_table;
    }
    if(!empty($tables)){
      if(!empty($variables['end'])) {
        $variables['end'] .= $tables;
      }
      else{
        $variables['end']=$tables;
      }
    }
  }
  if ($variables['type'] === 'content_page') {
    if ($variables['view_mode'] === 'full') {
      if(!empty($variables['field_catering_file'])){
        $catering_array = array();
        foreach($variables['field_catering_file'] as $catering_file){
          $file = $catering_file['uri'];
          $file_url = file_create_url($file);
          if(empty($catering_file['title'])){
            $name = $catering_file['filename'];
          }
          else{
            $name = $catering_file['title'];
          }
          $catering_array[] = array( 'url' => $file_url,'name' => $name);
        }
        $variables['field_catering_file'] = $catering_array;
      }
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
      if(!empty($variables['cp_image'])){
          $variables['image_from_template'] = hitsa_core_generate_single_image_figure($variables['cp_image'][0]);
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
          $variables['contact_filter'] =  hitsa_contacts_filter_widget($variables['nid']);
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
