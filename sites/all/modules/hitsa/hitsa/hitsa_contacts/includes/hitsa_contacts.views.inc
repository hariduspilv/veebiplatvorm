<?php

/**
* Implementation of hook_views_api().
*/
function hitsa_contacts_views_api() {
  return array(
    'api' => 3.0,
    'path' => drupal_get_path('module', 'hitsa_contacts'),
  );
}

/**
 * Implementation of hook_views_default_views().
 */
function hitsa_contacts_views_default_views() {
  // Contact page
  $view = new view();
  $view->name = 'hitsa_contacts';
  $view->description = '';
  $view->tag = 'hitsa';
  $view->base_table = 'node';
  $view->human_name = 'HITSA Contacts';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  
  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Contact';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'job_department',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  /* Field: Content: Image */
  $handler->display->display_options['fields']['contact_image']['id'] = 'contact_image';
  $handler->display->display_options['fields']['contact_image']['table'] = 'field_data_contact_image';
  $handler->display->display_options['fields']['contact_image']['field'] = 'contact_image';
  $handler->display->display_options['fields']['contact_image']['label'] = '';
  $handler->display->display_options['fields']['contact_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['contact_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['contact_image']['settings'] = array(
    'image_style' => 'large',
    'image_link' => '',
  );
  /* Field: Content: Department */
  $handler->display->display_options['fields']['job_department']['id'] = 'job_department';
  $handler->display->display_options['fields']['job_department']['table'] = 'field_data_job_department';
  $handler->display->display_options['fields']['job_department']['field'] = 'job_department';
  $handler->display->display_options['fields']['job_department']['label'] = '';
  $handler->display->display_options['fields']['job_department']['exclude'] = TRUE;
  $handler->display->display_options['fields']['job_department']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['job_department']['settings'] = array(
    'bypass_access' => 0,
    'link' => 0,
  );
  /* Field: Content: First name */
  $handler->display->display_options['fields']['first_name']['id'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['table'] = 'field_data_first_name';
  $handler->display->display_options['fields']['first_name']['field'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['label'] = '';
  $handler->display->display_options['fields']['first_name']['element_label_colon'] = FALSE;
  /* Field: Content: Last name */
  $handler->display->display_options['fields']['last_name']['id'] = 'last_name';
  $handler->display->display_options['fields']['last_name']['table'] = 'field_data_last_name';
  $handler->display->display_options['fields']['last_name']['field'] = 'last_name';
  $handler->display->display_options['fields']['last_name']['label'] = '';
  $handler->display->display_options['fields']['last_name']['element_label_colon'] = FALSE;
  /* Field: Content: Job Position */
  $handler->display->display_options['fields']['job_position']['id'] = 'job_position';
  $handler->display->display_options['fields']['job_position']['table'] = 'field_data_job_position';
  $handler->display->display_options['fields']['job_position']['field'] = 'job_position';
  $handler->display->display_options['fields']['job_position']['label'] = '';
  $handler->display->display_options['fields']['job_position']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['job_position']['settings'] = array(
    'bypass_access' => 0,
    'link' => 0,
  );
  $handler->display->display_options['fields']['job_position']['delta_offset'] = '0';
  /* Field: Content: Phone Nr. */
  $handler->display->display_options['fields']['phone_nr']['id'] = 'phone_nr';
  $handler->display->display_options['fields']['phone_nr']['table'] = 'field_data_phone_nr';
  $handler->display->display_options['fields']['phone_nr']['field'] = 'phone_nr';
  $handler->display->display_options['fields']['phone_nr']['label'] = '';
  $handler->display->display_options['fields']['phone_nr']['element_label_colon'] = FALSE;
  /* Field: Content: E-Mail */
  $handler->display->display_options['fields']['e_mail']['id'] = 'e_mail';
  $handler->display->display_options['fields']['e_mail']['table'] = 'field_data_e_mail';
  $handler->display->display_options['fields']['e_mail']['field'] = 'e_mail';
  $handler->display->display_options['fields']['e_mail']['label'] = '';
  $handler->display->display_options['fields']['e_mail']['element_label_colon'] = FALSE;
  /* Field: Content: Additional info */
  $handler->display->display_options['fields']['additional_info']['id'] = 'additional_info';
  $handler->display->display_options['fields']['additional_info']['table'] = 'field_data_additional_info';
  $handler->display->display_options['fields']['additional_info']['field'] = 'additional_info';
  $handler->display->display_options['fields']['additional_info']['label'] = '';
  $handler->display->display_options['fields']['additional_info']['element_label_colon'] = FALSE;
  /* Field: Content: Contact CV */
  $handler->display->display_options['fields']['contact_cv']['id'] = 'contact_cv';
  $handler->display->display_options['fields']['contact_cv']['table'] = 'field_data_contact_cv';
  $handler->display->display_options['fields']['contact_cv']['field'] = 'contact_cv';
  $handler->display->display_options['fields']['contact_cv']['label'] = '';
  $handler->display->display_options['fields']['contact_cv']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['contact_cv']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['contact_cv']['type'] = 'file_url_plain';
  $handler->display->display_options['fields']['contact_cv']['settings'] = array(
    'text' => 'Download [file:name]',
  );
  /* Sort criterion: Content: Department (job_department) */
  $handler->display->display_options['sorts']['job_department_target_id']['id'] = 'job_department_target_id';
  $handler->display->display_options['sorts']['job_department_target_id']['table'] = 'field_data_job_department';
  $handler->display->display_options['sorts']['job_department_target_id']['field'] = 'job_department_target_id';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'contact' => 'contact',
  );
  /* Filter criterion: Global: Combine fields filter */
  $handler->display->display_options['filters']['combine']['id'] = 'combine';
  $handler->display->display_options['filters']['combine']['table'] = 'views';
  $handler->display->display_options['filters']['combine']['field'] = 'combine';
  $handler->display->display_options['filters']['combine']['operator'] = 'contains';
  $handler->display->display_options['filters']['combine']['exposed'] = TRUE;
  $handler->display->display_options['filters']['combine']['expose']['operator_id'] = 'combine_op';
  $handler->display->display_options['filters']['combine']['expose']['label'] = 'Otsitav isik';
  $handler->display->display_options['filters']['combine']['expose']['operator'] = 'combine_op';
  $handler->display->display_options['filters']['combine']['expose']['identifier'] = 'name';
  $handler->display->display_options['filters']['combine']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  $handler->display->display_options['filters']['combine']['fields'] = array(
    'first_name' => 'first_name',
    'last_name' => 'last_name',
  );
  /* Filter criterion: Content: Job Position (job_position) */
  $handler->display->display_options['filters']['job_position_target_id']['id'] = 'job_position_target_id';
  $handler->display->display_options['filters']['job_position_target_id']['table'] = 'field_data_job_position';
  $handler->display->display_options['filters']['job_position_target_id']['field'] = 'job_position_target_id';
  $handler->display->display_options['filters']['job_position_target_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['job_position_target_id']['expose']['operator_id'] = 'job_position_target_id_op';
  $handler->display->display_options['filters']['job_position_target_id']['expose']['label'] = 'Eriala';
  $handler->display->display_options['filters']['job_position_target_id']['expose']['operator'] = 'job_position_target_id_op';
  $handler->display->display_options['filters']['job_position_target_id']['expose']['identifier'] = 'job_position';
  $handler->display->display_options['filters']['job_position_target_id']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  
  /* Display: Contact Page */
  $handler = $view->new_display('page', 'Contact Page', 'contacts_page');
  $handler->display->display_options['path'] = 'contact';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Contact';
  $handler->display->display_options['menu']['weight'] = '10';
  $handler->display->display_options['menu']['name'] = 'hitsa-main-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  $views[$view->name] = $view;
  return $views;
}