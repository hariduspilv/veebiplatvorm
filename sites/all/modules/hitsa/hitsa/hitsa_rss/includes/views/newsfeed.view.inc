<?php
$view = new view();
$view->name = 'uudise_feed';
$view->description = '';
$view->tag = 'default';
$view->base_table = 'node';
$view->human_name = 'Uudise feed';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'Uudise feed';
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['use_more_text'] = 'veel';
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['exposed_form']['options']['submit_button'] = 'Rakenda';
$handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Lähtesta';
$handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Sorteeri';
$handler->display->display_options['exposed_form']['options']['sort_asc_label'] = 'Kasvavalt';
$handler->display->display_options['exposed_form']['options']['sort_desc_label'] = 'Kahanevalt';
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = '10';
$handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = 'Kirjeid lehel';
$handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- Kõik -';
$handler->display->display_options['pager']['options']['expose']['offset_label'] = 'Nihe';
$handler->display->display_options['pager']['options']['tags']['first'] = '« esimene';
$handler->display->display_options['pager']['options']['tags']['previous'] = '‹ eelmine';
$handler->display->display_options['pager']['options']['tags']['next'] = 'järgmine ›';
$handler->display->display_options['pager']['options']['tags']['last'] = 'viimane »';
$handler->display->display_options['style_plugin'] = 'default';
$handler->display->display_options['row_plugin'] = 'fields';
/* Valdkond: Sisu: Pealkiri */
$handler->display->display_options['fields']['title']['id'] = 'title';
$handler->display->display_options['fields']['title']['table'] = 'node';
$handler->display->display_options['fields']['title']['field'] = 'title';
$handler->display->display_options['fields']['title']['label'] = '';
$handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
$handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
$handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
/* Valdkond: Sisu: Body */
$handler->display->display_options['fields']['body_1']['id'] = 'body_1';
$handler->display->display_options['fields']['body_1']['table'] = 'field_data_body';
$handler->display->display_options['fields']['body_1']['field'] = 'body';
$handler->display->display_options['fields']['body_1']['label'] = '';
$handler->display->display_options['fields']['body_1']['element_label_colon'] = FALSE;
/* Valdkond: Sisu: Pictures */
$handler->display->display_options['fields']['subpage_images']['id'] = 'subpage_images';
$handler->display->display_options['fields']['subpage_images']['table'] = 'field_data_subpage_images';
$handler->display->display_options['fields']['subpage_images']['field'] = 'subpage_images';
$handler->display->display_options['fields']['subpage_images']['label'] = '';
$handler->display->display_options['fields']['subpage_images']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['subpage_images']['click_sort_column'] = 'fid';
$handler->display->display_options['fields']['subpage_images']['type'] = 'enclosure';
$handler->display->display_options['fields']['subpage_images']['settings'] = array(
  'image_style' => 'hitsa_gallery_image_full',
);
$handler->display->display_options['fields']['subpage_images']['delta_limit'] = '1';
$handler->display->display_options['fields']['subpage_images']['delta_offset'] = '0';
/* Valdkond: Sisu: Author */
$handler->display->display_options['fields']['gallery_author']['id'] = 'gallery_author';
$handler->display->display_options['fields']['gallery_author']['table'] = 'field_data_gallery_author';
$handler->display->display_options['fields']['gallery_author']['field'] = 'gallery_author';
$handler->display->display_options['fields']['gallery_author']['label'] = '';
$handler->display->display_options['fields']['gallery_author']['element_label_colon'] = FALSE;
/* Valdkond: Sisu: Link */
$handler->display->display_options['fields']['view_node']['id'] = 'view_node';
$handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
$handler->display->display_options['fields']['view_node']['field'] = 'view_node';
$handler->display->display_options['fields']['view_node']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['view_node']['alter']['absolute'] = TRUE;
/* Lühike kriteerium: Sisu: Postituse kuupäev */
$handler->display->display_options['sorts']['created']['id'] = 'created';
$handler->display->display_options['sorts']['created']['table'] = 'node';
$handler->display->display_options['sorts']['created']['field'] = 'created';
$handler->display->display_options['sorts']['created']['order'] = 'DESC';
/* Filtri kriteeriumid: Sisu: Avaldatud */
$handler->display->display_options['filters']['status']['id'] = 'status';
$handler->display->display_options['filters']['status']['table'] = 'node';
$handler->display->display_options['filters']['status']['field'] = 'status';
$handler->display->display_options['filters']['status']['value'] = 1;
$handler->display->display_options['filters']['status']['group'] = 1;
$handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
/* Filtri kriteeriumid: Sisu: Tüüp */
$handler->display->display_options['filters']['type']['id'] = 'type';
$handler->display->display_options['filters']['type']['table'] = 'node';
$handler->display->display_options['filters']['type']['field'] = 'type';
$handler->display->display_options['filters']['type']['value'] = array(
  'article' => 'article',
);
/* Filtri kriteeriumid: Sisu: Keel */
$handler->display->display_options['filters']['language']['id'] = 'language';
$handler->display->display_options['filters']['language']['table'] = 'node';
$handler->display->display_options['filters']['language']['field'] = 'language';
$handler->display->display_options['filters']['language']['value'] = array(
  '***CURRENT_LANGUAGE***' => '***CURRENT_LANGUAGE***',
);

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page');
$handler->display->display_options['path'] = 'uudise-feed';

/* Display: Feed */
$handler = $view->new_display('feed', 'Feed', 'feed');
$handler->display->display_options['pager']['type'] = 'some';
$handler->display->display_options['pager']['options']['items_per_page'] = '20';
$handler->display->display_options['pager']['options']['offset'] = '0';
$handler->display->display_options['style_plugin'] = 'rss_fields';
$handler->display->display_options['style_options']['channel'] = array(
  'core' => array(
    'views_rss_core' => array(
      'description' => '',
      'language' => '',
      'category' => '',
      'image' => '',
      'copyright' => '',
      'managingEditor' => '',
      'webMaster' => '',
      'generator' => '',
      'docs' => '',
      'cloud' => '',
      'ttl' => '',
      'skipHours' => '',
      'skipDays' => '',
    ),
  ),
);
$handler->display->display_options['style_options']['item'] = array(
  'core' => array(
    'views_rss_core' => array(
      'title' => 'title',
      'link' => 'view_node',
      'description' => 'body_1',
      'author' => 'gallery_author',
      'category' => '',
      'comments' => '',
      'enclosure' => 'subpage_images',
      'guid' => '',
      'pubDate' => '',
    ),
  ),
);
$handler->display->display_options['style_options']['feed_settings'] = array(
  'absolute_paths' => 1,
  'feed_in_links' => 0,
);
$handler->display->display_options['path'] = 'uudise-feed.xml';
$handler->display->display_options['displays'] = array(
  'default' => 'default',
  'page' => 'page',
);
