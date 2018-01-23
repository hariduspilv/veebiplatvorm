<?php

/**
* Implementation of hook_views_api().
*/
function hitsa_locations_views_api() {
  return array(
    'api' => 3.0,
    'path' => drupal_get_path('module', 'hitsa_locations'),
  );
}

/**
 * Implementation of hook_views_default_views().
 */
function hitsa_locations_views_default_views() {
  $view = new view();
  $view->name = 'hitsa_locations';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'HITSA Locations';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  
  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'veel';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer nodes';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Rakenda';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Lähtesta';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Sorteeri';
  $handler->display->display_options['exposed_form']['options']['sort_asc_label'] = 'Kasvavalt';
  $handler->display->display_options['exposed_form']['options']['sort_desc_label'] = 'Kahanevalt';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  /* Valdkond: Sisu: Pealkiri */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Valdkond: Sisu: Aadress */
  $handler->display->display_options['fields']['location_address']['id'] = 'location_address';
  $handler->display->display_options['fields']['location_address']['table'] = 'field_data_location_address';
  $handler->display->display_options['fields']['location_address']['field'] = 'location_address';
  $handler->display->display_options['fields']['location_address']['label'] = '';
  $handler->display->display_options['fields']['location_address']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['location_address']['type'] = 'text_plain';
  /* Valdkond: Sisu: Telefoninumber */
  $handler->display->display_options['fields']['phone_nr']['id'] = 'phone_nr';
  $handler->display->display_options['fields']['phone_nr']['table'] = 'field_data_phone_nr';
  $handler->display->display_options['fields']['phone_nr']['field'] = 'phone_nr';
  $handler->display->display_options['fields']['phone_nr']['label'] = '';
  $handler->display->display_options['fields']['phone_nr']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['phone_nr']['type'] = 'text_plain';
  /* Valdkond: Sisu: E-mail */
  $handler->display->display_options['fields']['e_mail']['id'] = 'e_mail';
  $handler->display->display_options['fields']['e_mail']['table'] = 'field_data_e_mail';
  $handler->display->display_options['fields']['e_mail']['field'] = 'e_mail';
  $handler->display->display_options['fields']['e_mail']['label'] = '';
  $handler->display->display_options['fields']['e_mail']['element_label_colon'] = FALSE;
  /* Valdkond: Sisu: Lahtiolekuaeg */
  $handler->display->display_options['fields']['location_visiting_hours']['id'] = 'location_visiting_hours';
  $handler->display->display_options['fields']['location_visiting_hours']['table'] = 'field_data_location_visiting_hours';
  $handler->display->display_options['fields']['location_visiting_hours']['field'] = 'location_visiting_hours';
  $handler->display->display_options['fields']['location_visiting_hours']['label'] = '';
  $handler->display->display_options['fields']['location_visiting_hours']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['location_visiting_hours']['type'] = 'text_plain';
  /* Valdkond: Sisu: Koordinaadid */
  $handler->display->display_options['fields']['location_coordinates']['id'] = 'location_coordinates';
  $handler->display->display_options['fields']['location_coordinates']['table'] = 'field_data_location_coordinates';
  $handler->display->display_options['fields']['location_coordinates']['field'] = 'location_coordinates';
  $handler->display->display_options['fields']['location_coordinates']['label'] = '';
  $handler->display->display_options['fields']['location_coordinates']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['location_coordinates']['click_sort_column'] = 'lat';
  /* Valdkond: Sisu: Parkimine */
  $handler->display->display_options['fields']['location_parking']['id'] = 'location_parking';
  $handler->display->display_options['fields']['location_parking']['table'] = 'field_data_location_parking';
  $handler->display->display_options['fields']['location_parking']['field'] = 'location_parking';
  $handler->display->display_options['fields']['location_parking']['label'] = '';
  $handler->display->display_options['fields']['location_parking']['element_label_colon'] = FALSE;
  /* Valdkond: Sisu: Transport */
  $handler->display->display_options['fields']['location_transport']['id'] = 'location_transport';
  $handler->display->display_options['fields']['location_transport']['table'] = 'field_data_location_transport';
  $handler->display->display_options['fields']['location_transport']['field'] = 'location_transport';
  $handler->display->display_options['fields']['location_transport']['label'] = '';
  $handler->display->display_options['fields']['location_transport']['element_label_colon'] = FALSE;
  /* Lühike kriteerium: Draggableviews: Kaal */
  $handler->display->display_options['sorts']['weight']['id'] = 'weight';
  $handler->display->display_options['sorts']['weight']['table'] = 'draggableviews_structure';
  $handler->display->display_options['sorts']['weight']['field'] = 'weight';
  $handler->display->display_options['sorts']['weight']['draggableviews_setting_view'] = 'hitsa_locations:page_1';
  $handler->display->display_options['sorts']['weight']['draggableviews_setting_new_items_bottom_list'] = 1;
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
    'contact_location' => 'contact_location',
  );
  
  /* Display: Locations */
  $handler = $view->new_display('block', 'Locations', 'locations_block');
  $handler->display->display_options['defaults']['cache'] = FALSE;
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '300';
  $handler->display->display_options['cache']['results_lifespan_custom'] = '0';
  $handler->display->display_options['cache']['output_lifespan'] = '300';
  $handler->display->display_options['cache']['output_lifespan_custom'] = '0';
  $handler->display->display_options['block_description'] = 'Locations';
  
  /* Display: Kohad - Sorteeri */
  $handler = $view->new_display('page', 'Kohad - Sorteeri', 'locations_sort');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Locations - Sort';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['columns'] = array(
    'nid' => 'nid',
    'title' => 'title',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'nid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['override'] = FALSE;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Valdkond: Sisu: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Valdkond: Draggableviews: Sisu */
  $handler->display->display_options['fields']['draggableviews']['id'] = 'draggableviews';
  $handler->display->display_options['fields']['draggableviews']['table'] = 'node';
  $handler->display->display_options['fields']['draggableviews']['field'] = 'draggableviews';
  $handler->display->display_options['fields']['draggableviews']['label'] = '';
  $handler->display->display_options['fields']['draggableviews']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['draggableviews']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['draggableviews']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['draggableviews']['draggableviews']['ajax'] = 0;
  /* Valdkond: Sisu: Pealkiri */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  $handler->display->display_options['path'] = 'admin/hitsa/locations/sort';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Kohad - Sorteeri';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  
  $views[$view->name] = $view;
  return $views;
}