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
  $variable['footer_general_contact'] = array(
    'title' => t('General Contact'),
    'localize' => TRUE,
    'type' => 'text_format',
    'group' => 'header_footer_variables',
  );
  $variable['footer_important_contact'] = array(
    'title' => t('Important Contacts'),
    'localize' => TRUE,
    'type' => 'text_format',
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

/* Site Logo Widget */
function hitsa_core_form_variable_group_form_alter(&$form, &$form_state) {
  if($form['#variable_group_form'] === 'header_footer_variables') {
    $form['hitsa_site_logo_widget'] = array(
      '#title' => t('Logo Image'),
      '#type' => 'managed_file',
      '#default_value' => variable_get('image_example_image_fid', ''),
      '#weight' => -100,
    );
    //$form['#submit'][] = 'hitsa_core_site_logo_submit';
  }
  
}

function hitsa_core_site_logo_submit(&$form, &$form_state) {
  dpm($form_state);
}