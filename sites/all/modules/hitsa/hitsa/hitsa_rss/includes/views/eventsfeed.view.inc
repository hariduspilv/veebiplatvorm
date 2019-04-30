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
$handler->display->display_options['row_plugin'] = 'node';
/* Valdkond: Sisu: Pealkiri */
$handler->display->display_options['fields']['title']['id'] = 'title';
$handler->display->display_options['fields']['title']['table'] = 'node';
$handler->display->display_options['fields']['title']['field'] = 'title';
$handler->display->display_options['fields']['title']['label'] = '';
$handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
$handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
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

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page');
$handler->display->display_options['path'] = 's-ndmuste-feed';

/* Display: Feed */
$handler = $view->new_display('feed', 'Feed', 'feed');
$handler->display->display_options['pager']['type'] = 'some';
$handler->display->display_options['pager']['options']['items_per_page'] = '20';
$handler->display->display_options['pager']['options']['offset'] = '0';
$handler->display->display_options['style_plugin'] = 'rss';
$handler->display->display_options['row_plugin'] = 'node_rss';
$handler->display->display_options['path'] = 'events-feed.xml';
$handler->display->display_options['displays'] = array(
  'default' => 'default',
  'page' => 'page',
);
