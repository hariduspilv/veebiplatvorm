<?php

function hitsa_core_variable_info($options) {
  $variable = array();
  
  $variable['hitsa_fb_link'] = array(
    'title' => t('Facebook link'),
    'group' => 'general_variables',
  );
  $variable['period_title'] = array(
    'title' => t('Period title'),
    'localize' => TRUE,
    'group' => 'hitsa_core_translation_group',
  );
  // General Contact
  $variable['general_contact_name'] = array(
    'title' => t('Name of institution'),
    'group' => 'header_footer_variables',
  );
  $variable['general_contact_address'] = array(
    'title' => t('Address'),
    'group' => 'header_footer_variables',
  );
  $variable['general_contact_phone_nr'] = array(
    'title' => t('Phone Nr'),
    'group' => 'header_footer_variables',
  );
  $variable['general_contact_email'] = array(
    'title' => t('E-Mail'),
    'group' => 'header_footer_variables',
  );
  // Important contacts
  for($i = 1; $i < 5; $i++) {
    $variable['important_contact_name_' . $i] = array(
      'title' => t('Name'),
      'group' => 'header_footer_variables',
      'localize' => TRUE,
    );
    
    $variable['important_contact_phone_' . $i] = array(
      'title' => t('Phone Nr.'),
      'group' => 'header_footer_variables',
    );
  }
  
  $variable['hitsa_school_place_id'] = array(
    'title' => t('Place ID'),
    'group' => 'header_footer_variables',
  );
  $variable['footer_copyright_notice'] = array(
    'title' => t('Copyright Notice'),
    'group' => 'header_footer_variables',
  );
  $variable['hitsa_site_logo_fid'] = array(
    'title' => t('HITSA Site Logo FID'),
    'group' => 'header_footer_variables',
  );
  return $variable;
}

function hitsa_core_variable_group_info() {
  $groups['general_variables'] = array(
    'title' => t('General variables'),
    'access' => 'administer content',
    'path' => array('admin/hitsa/variables/general'),
  );
  
  $groups['header_footer_variables'] = array(
    'title' => t('Header & Footer variables'),
    'access' => 'administer content',
    'path' => array('admin/hitsa/variables/header_footer'),
  );
  
  $groups['hitsa_core_translation_group'] = array(
    'title' => t('Hitsa variables translation group'),
    'description' => t('Here will appear all hitsa variables that are translatable'),
    
  );
  
  return $groups;
}

function hitsa_core_variable_type_info() {
  $type['contact'] = array(
    'title' => t('Contact'),
    'multiple' => 'name',
    'type' => 'multiple',
  );
  
  return $type;
}

/* Site Logo Widget */
function hitsa_core_form_variable_group_form_alter(&$form, &$form_state) {
  if($form['#variable_group_form'] === 'header_footer_variables') {
    _hitsa_core_add_logo_upload_element($form, $form_state);
    
    // General contact fieldset
    $form['general_contact'] = array(
      '#type' => 'fieldset', 
      '#title' => t('General contact'), 
      '#weight' => 0, 
      '#collapsible' => FALSE, 
      '#collapsed' => FALSE,
    );
    // Move general contact fields under the fieldset.
    $form['general_contact']['general_contact_name'] = $form['general_contact_name'];
    $form['general_contact']['general_contact_address'] = $form['general_contact_address'];
    $form['general_contact']['general_contact_phone_nr'] = $form['general_contact_phone_nr'];
    $form['general_contact']['general_contact_email'] = $form['general_contact_email'];
    unset($form['general_contact_name']);
    unset($form['general_contact_address']);
    unset($form['general_contact_phone_nr']);
    unset($form['general_contact_email']);
    
    // Important contacts fieldset
    $form['important_contacts'] = array(
      '#type' => 'fieldset', 
      '#title' => t('Important contacts'), 
      '#weight' => 1,
      '#collapsible' => FALSE, 
      '#collapsed' => FALSE,
    );
    
    for($i = 1; $i < 5; $i++) {
      $form['important_contacts']['important_contact_name_' . $i] = $form['important_contact_name_' . $i];
      $form['important_contacts']['important_contact_phone_' . $i] = $form['important_contact_phone_' . $i];
      $form['important_contacts']['important_contact_name_' . $i]['#prefix'] = '<div class="contact-row">';
      $form['important_contacts']['important_contact_phone_' . $i]['#suffix'] = '</div>';
      unset($form['important_contact_name_' . $i]);
      unset($form['important_contact_phone_' . $i]);
    }
    drupal_add_css('.contact-row > * {display:inline-block;}', 'inline');
    
    // Gmap picker
    $form['gmap_picker'] = array(
      '#markup' => theme('gmap_picker'),
      '#weight' => 2,
    );
    
    // Hide the school place element
    $form['hitsa_school_place_id']['#attributes']['style'] = 'display:none;';
    $form['hitsa_school_place_id']['#title_display'] = 'invisible';
    $form['hitsa_school_place_id']['#theme_wrappers'] = array();
  }
}

function _hitsa_core_add_logo_upload_element(&$form, &$form_state) {
  $site_logo_fid = variable_get_value('hitsa_site_logo_fid');
  $file = file_load($site_logo_fid);
  
  if($file) {
    // Logo preview
    $form['hitsa_site_logo_preview'] = array(
      '#type' => 'item',
      '#title' => t('Site Logo'),
      '#markup' => '<img src="' . file_create_url($file->uri) . '"></img>',
      '#weight' => -100,
    );
  }
  
  // Logo upload
  $form['hitsa_site_logo_widget'] = array(
    '#name' => 'files[hitsa_site_logo]',
    '#title' => t('Upload Logo Image'),
    '#type' => 'file',
    '#weight' => -99,
  );
  $form['#validate'][] = 'hitsa_core_site_logo_validate';
  $form['#submit'][] = 'hitsa_core_site_logo_submit';

  // Hide FID field
  if(!empty($form['hitsa_site_logo_fid'])) {
    $form['hitsa_site_logo_fid']['#access'] = FALSE;
  }
}

function hitsa_core_site_logo_validate($form, &$form_state) {
  
  $validators = array(
   'file_validate_is_image' => array(),
   'file_validate_extensions' => array('png jpg jpeg'),
   'file_validate_size' => array(1024*1024),
  );
	
  // Save file as temporary
  $file = file_save_upload('hitsa_site_logo', $validators, 'public://', FILE_EXISTS_RENAME);
  
  if($file) {
    $form_state['files']['hitsa_site_logo_fid'] = $file;
  }
}

function hitsa_core_site_logo_submit($form, &$form_state) {
  // Permamently save the file.
  if(!empty($form_state['files']['hitsa_site_logo_fid'])) {
    $file = $form_state['files']['hitsa_site_logo_fid'];
    $file->status = FILE_STATUS_PERMANENT;
    $file = file_save($file);
    variable_set_value('hitsa_site_logo_fid', $file->fid);
  }
}