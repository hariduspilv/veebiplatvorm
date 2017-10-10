<?php

/**
 * Implements hook_theme_registry_alter().
 */
function hitsa_articles_theme_registry_alter(&$theme_registry) {
  // Defined path to the current module.
  $module_path = drupal_get_path('module', 'hitsa_articles');
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

function hitsa_articles_theme() {
  $items = array();
  
  $items['news_page'] = array(
    'template' => 'hitsa-news-page',
    'path' => drupal_get_path('module', 'hitsa_articles') . '/templates',
    'variables' => array(
      'nodes' => NULL,
    ),
  );
  
  $items['hitsa_article_teaser'] = array(
    'template' => 'hitsa-article-teaser',
    'path' => drupal_get_path('module', 'hitsa_articles') . '/templates',
    'variables' => array(
      'node' => NULL,
      'author' => NULL,
    ),
  );
  
  $items['hitsa_important_article'] = array(
    'template' => 'hitsa-important-article',
    'path' => drupal_get_path('module', 'hitsa_articles') . '/templates',
    'variables' => array(
      'node' => NULL,
    ),
  );
  
  $items['hitsa_our_stories_block'] = array(
    'template' => 'hitsa-our-stories-block',
    'path' => drupal_get_path('module', 'hitsa_articles') . '/templates',
    'variables' => array(
      'node' => NULL,
    ),
  );
  
  return $items;
}

function hitsa_articles_preprocess_node(&$variables) {
  if($variables['node']->type === 'article') {
    // Get the category title based on article type.
    $all_fields = field_info_fields();
    $variables['article_types_list'] = list_allowed_values($all_fields['article_type']);
    
    // Get "More articles" block nodes
    $more_articles = hitsa_articles_get_more_articles_block_nodes($variables);
    $articles_rendered = array();
    foreach($more_articles as $article) {
      $author = user_load($article->uid);
      $articles_rendered[] = theme('hitsa_article_teaser', array('node' => $article, 'author' => $author));
    }
    $variables['more_articles'] = $articles_rendered;
    
    // Add "More articles" block title and link
    $article_type = !empty($variables['article_type'][0]['value']) ? $variables['article_type'][0]['value'] : 'news';
    
    $variables['more_articles_title'] = $article_type === 'our_stories' ? t('More stories') : t('More news');
    $link = $article_type === 'our_stories' ? url('our-stories') : url('news');
    $variables['more_articles_link'] = sprintf('<a href="%s" class="btn">%s</a>', $link, $article_type === 'our_stories' ? t('All stories') : t('All news'));
  }
}

function hitsa_articles_page_view($type) {
  $query = drupal_get_query_parameters();
  $query['article_type'] = $type;
  $query['range'] = array(0, 12);
  
  // Load academic years taxonomy
  $academic_years_vid = variable_get('hitsa_core_academic_years_vid');
  $academic_years = array_reverse(taxonomy_get_tree($academic_years_vid));
  
  // Load nodes
  $nids_array = hitsa_articles_query_content($query);
  if(!empty($nids_array['node'])) {
    $nodes = node_load_multiple(array_keys($nids_array['node']));
    
    // Sort and group the articles based on the academic year.
    $articles_grouped = array();

    foreach($nodes as $node) {
      $author = user_load($node->uid);
      if(!empty($node->academic_year[LANGUAGE_NONE][0]['tid'])) {
        $articles_grouped[$node->academic_year[LANGUAGE_NONE][0]['tid']][] = theme('hitsa_article_teaser', array('node' => $node, 'author' => $author));
      }
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

  return theme(
    'news_page',
    array(
      'nodes' => !empty($articles_grouped_sorted) ? $articles_grouped_sorted : array(),
      'academic_years' => $academic_years,
      'academic_year_keyed' => !empty($academic_years_keyed) ? $academic_years_keyed : array(),
      'authors' => !empty($authors) ? $authors : array(),
    )
  );
}