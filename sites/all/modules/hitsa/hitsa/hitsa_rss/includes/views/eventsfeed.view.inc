<?php
$view = new view();
$view->name = 's_ndmuste_feed';
$view->description = '';
$view->tag = 'default';
$view->base_table = 'node';
$view->human_name = 'Sündmuste feed';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'Sündmuste feed';
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
/* Valdkond: Sisu: Body */
$handler->display->display_options['fields']['body']['id'] = 'body';
$handler->display->display_options['fields']['body']['table'] = 'field_data_body';
$handler->display->display_options['fields']['body']['field'] = 'body';
$handler->display->display_options['fields']['body']['label'] = '';
$handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
/* Valdkond: Sisu: Body */
$handler->display->display_options['fields']['body_1']['id'] = 'body_1';
$handler->display->display_options['fields']['body_1']['table'] = 'field_data_body';
$handler->display->display_options['fields']['body_1']['field'] = 'body';
$handler->display->display_options['fields']['body_1']['label'] = 'Kirjeldus';
$handler->display->display_options['fields']['body_1']['element_label_colon'] = FALSE;
/* Valdkond: Sisu: Date */
$handler->display->display_options['fields']['event_date_2']['id'] = 'event_date_2';
$handler->display->display_options['fields']['event_date_2']['table'] = 'field_data_event_date';
$handler->display->display_options['fields']['event_date_2']['field'] = 'event_date';
$handler->display->display_options['fields']['event_date_2']['label'] = '';
$handler->display->display_options['fields']['event_date_2']['alter']['strip_tags'] = TRUE;
$handler->display->display_options['fields']['event_date_2']['element_type'] = '0';
$handler->display->display_options['fields']['event_date_2']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['event_date_2']['element_default_classes'] = FALSE;
$handler->display->display_options['fields']['event_date_2']['settings'] = array(
  'format_type' => 'custom',
  'custom_date_format' => 'd.m.Y H:i',
  'fromto' => 'both',
  'multiple_number' => '',
  'multiple_from' => '',
  'multiple_to' => '',
  'show_remaining_days' => 0,
);
/* Valdkond: Sisu: Author */
$handler->display->display_options['fields']['gallery_author']['id'] = 'gallery_author';
$handler->display->display_options['fields']['gallery_author']['table'] = 'field_data_gallery_author';
$handler->display->display_options['fields']['gallery_author']['field'] = 'gallery_author';
$handler->display->display_options['fields']['gallery_author']['label'] = 'Autor';
/* Valdkond: Sisu: Location */
$handler->display->display_options['fields']['locations']['id'] = 'locations';
$handler->display->display_options['fields']['locations']['table'] = 'field_data_locations';
$handler->display->display_options['fields']['locations']['field'] = 'locations';
$handler->display->display_options['fields']['locations']['label'] = 'Koht';
$handler->display->display_options['fields']['locations']['element_default_classes'] = FALSE;
$handler->display->display_options['fields']['locations']['type'] = 'i18n_taxonomy_term_reference_plain';
$handler->display->display_options['fields']['locations']['settings'] = array(
  'view_mode' => 'token',
  'links' => 1,
  'use_content_language' => 1,
);
/* Valdkond: Sisu: Pictures */
$handler->display->display_options['fields']['field_pictures']['id'] = 'field_pictures';
$handler->display->display_options['fields']['field_pictures']['table'] = 'field_data_field_pictures';
$handler->display->display_options['fields']['field_pictures']['field'] = 'field_pictures';
$handler->display->display_options['fields']['field_pictures']['label'] = 'PILDID';
$handler->display->display_options['fields']['field_pictures']['click_sort_column'] = 'fid';
$handler->display->display_options['fields']['field_pictures']['type'] = 'enclosure';
$handler->display->display_options['fields']['field_pictures']['settings'] = array(
  'image_style' => '',
);
$handler->display->display_options['fields']['field_pictures']['delta_limit'] = '1';
$handler->display->display_options['fields']['field_pictures']['delta_offset'] = '0';
/* Valdkond: Sisu: Pealkiri */
$handler->display->display_options['fields']['title']['id'] = 'title';
$handler->display->display_options['fields']['title']['table'] = 'node';
$handler->display->display_options['fields']['title']['field'] = 'title';
$handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
/* Valdkond: Sisu: Tee */
$handler->display->display_options['fields']['path']['id'] = 'path';
$handler->display->display_options['fields']['path']['table'] = 'node';
$handler->display->display_options['fields']['path']['field'] = 'path';
$handler->display->display_options['fields']['path']['absolute'] = TRUE;
/* Valdkond: Sisu: Date */
$handler->display->display_options['fields']['event_date']['id'] = 'event_date';
$handler->display->display_options['fields']['event_date']['table'] = 'field_data_event_date';
$handler->display->display_options['fields']['event_date']['field'] = 'event_date';
$handler->display->display_options['fields']['event_date']['label'] = '';
$handler->display->display_options['fields']['event_date']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['event_date']['type'] = 'date_plain';
$handler->display->display_options['fields']['event_date']['settings'] = array(
  'format_type' => 'custom',
  'custom_date_format' => 'U',
  'fromto' => 'value2',
  'multiple_number' => '',
  'multiple_from' => '',
  'multiple_to' => '',
  'show_remaining_days' => 0,
);
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
  'event' => 'event',
);
/* Filtri kriteeriumid: Sisu: Keel */
$handler->display->display_options['filters']['language']['id'] = 'language';
$handler->display->display_options['filters']['language']['table'] = 'node';
$handler->display->display_options['filters']['language']['field'] = 'language';
$handler->display->display_options['filters']['language']['value'] = array(
  '***CURRENT_LANGUAGE***' => '***CURRENT_LANGUAGE***',
);
/* Filtri kriteeriumid: Sisu: Date - end date (event_date:value2) */
$handler->display->display_options['filters']['event_date_value2']['id'] = 'event_date_value2';
$handler->display->display_options['filters']['event_date_value2']['table'] = 'field_data_event_date';
$handler->display->display_options['filters']['event_date_value2']['field'] = 'event_date_value2';
$handler->display->display_options['filters']['event_date_value2']['operator'] = '>';
$handler->display->display_options['filters']['event_date_value2']['granularity'] = 'hour';
$handler->display->display_options['filters']['event_date_value2']['form_type'] = 'date_text';
$handler->display->display_options['filters']['event_date_value2']['default_date'] = 'Now';
$handler->display->display_options['filters']['event_date_value2']['year_range'] = '-0:+10';

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page');
$handler->display->display_options['path'] = 'events-feed';

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
      'link' => 'path',
      'description' => 'body',
      'author' => 'gallery_author',
      'category' => 'locations',
      'comments' => '',
      'enclosure' => 'field_pictures',
      'guid' => 'title',
      'pubDate' => 'event_date_2',
    ),
  ),
);
$handler->display->display_options['style_options']['feed_settings'] = array(
  'absolute_paths' => 1,
  'feed_in_links' => 0,
);
$handler->display->display_options['path'] = 'events-feed.xml';
$handler->display->display_options['displays'] = array(
  'default' => 'default',
  'page' => 'page',
);

