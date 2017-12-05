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
    'template' => 'hitsa-content-page-teaser',
    'path' => drupal_get_path('module', 'hitsa_content_page') . '/templates',
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
  
  $items['hitsa_news_output'] = array(
    'template' => 'hitsa-news-output',
    'path' => drupal_get_path('module', 'hitsa_articles') . '/templates',
    'variables' => array(
      'nodes' => NULL,
      'pager' => NULL,
      'academic_year' => NULL,
    ),
  );
  
  return $items;
}

function hitsa_articles_preprocess_node(&$variables) {
  if($variables['node']->type === 'article') {
    if($variables['view_mode'] === 'full') {
      // Get the category title based on article type.
      $all_fields = field_info_fields();
      $variables['article_types_list'] = list_allowed_values($all_fields['article_type']);
      
      foreach($variables['article_types_list'] as &$type) {
        $type = t($type);
      }
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
      
      // Set author and publish date
      $author = user_load($variables['uid']);
      if(!empty($author->name)) {
        $variables['author_name'] = $author->name;
      }
      
      // Video thumbnail
      if(!empty($variables['article_video'])) {
        $video_id = preg_replace('/.*:\/\/v\//', '', $variables['article_video'][0]['uri']);
        $type = str_replace('video/', '', $variables['article_video'][0]['filemime']);

        $file_directory = 'sites/default/files/media-' . $type .'/' . $video_id . '.jpg';
        if(file_exists(getcwd() . '/' . $file_directory)) {
          global $base_url;
          $file_url = file_create_url($file_directory);
          $variables['video_thumbnail'] = $file_url;
        }
      }
    }
  }
}

function hitsa_articles_preprocess_block(&$variables) {
  if($variables['block_html_id'] === 'block-views-hitsa-logos-awards-block'
    || $variables['block_html_id'] === 'block-hitsa-articles-hitsa-our-stories'
  ) {
    $variables['elements']['#theme_wrappers'] = array();
  }
}

function hitsa_articles_page_view($type, $filter = FALSE) {
  $query = drupal_get_query_parameters();
  $query['article_type'] = empty($query['article_type']) ? $type : $query['article_type'];
  $query['range'] = empty($query['range']) ? array(0, 12) : $query['range'];
  $query['pager'] = 12;
  $query['entity_type'] = 'node';
  $query['bundle'] = 'article';
  $query['status'] = NODE_PUBLISHED;
  $query['order_by'] = array('parameter' => 'created', 'direction' => 'DESC');
  
  return hitsa_content_page_view($query, $filter, 'news');
}