<?php
/**
 * @file
 * Enables modules and site configuration for a standard site installation.
 */

/**
 * Implements hook_form_FORM_ID_alter() for install_configure_form().
 *
 * Allows the profile to alter the site configuration form.
 */
function hitsa_school_form_install_configure_form_alter(&$form, $form_state) {
  // Pre-populate the site name with the server name.
  $form['site_information']['site_name']['#default_value'] = $_SERVER['SERVER_NAME'];
}


function hitsa_school_install_tasks() {
  $tasks['choose_school_type'] = array(
  'display_name' => st('Select school type'),
  'display' => TRUE,
  'type' => 'form',
  'run' => INSTALL_TASK_RUN_IF_NOT_COMPLETED,
  'function' => 'school_type_form',
  );
  
  $tasks['set_hitsa_defaults'] = array(
  'display_name' => st('Setting website default settings'),
  'display' => TRUE,
  'type' => 'normal',
  'run' => INSTALL_TASK_RUN_IF_NOT_COMPLETED,
  'function' => 'hitsa_set_system_defaults',
  );

  return $tasks;
}

function school_type_form($form, &$form_state) {
  $form = array();
  $form['school_type'] = array(
    '#type' => 'radios',
    '#title' => st('School type'),
    '#default_value' => 1,
    '#options' => array(1 => 'Kõrgkool/Kutsekool', 2 => 'Gümnaasium'),
    '#description' => st('Select the school type'),
  );
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => st('Save & Continue'),
  );
  
  return $form;
}

function school_type_form_submit($form, &$form_state) {
  $school_type = $form_state['values']['school_type'];
  //variable_set('hitsa_school_type', $school_type);
}

function hitsa_school_profile_details() {
  $details['language'] = "et";
  return $details;
}

function hitsa_set_system_defaults() {
  hitsa_set_default_language();
  hitsa_set_language_detection_rules();
}

function hitsa_set_default_language() {
  $langs = language_list(); // Note: No argument
  $langcode = 'et';
  variable_set('language_default', $langs[$langcode]);
  
  // Set default language settings
  db_update('languages')
    ->fields(array(
      'prefix' => 'en',
      'weight' => -9,
    ))
    ->condition('language',  'en')
    ->execute();
  
  // Disable "Language None" option
  module_load_include('inc', 'entity_translation', 'entity_translation.admin');
  entity_translation_settings_init('node', array('exclude_language_none' => TRUE));
}

function hitsa_set_language_detection_rules() {
  require_once DRUPAL_ROOT . '/includes/language.inc';
  
  $weighted_provider_list = array(
    1 => LOCALE_LANGUAGE_NEGOTIATION_URL,
    10 => LANGUAGE_NEGOTIATION_DEFAULT,
  );
  $all_negotiation_providers = language_negotiation_info();
  $negotiation = array();
  foreach ($weighted_provider_list as $weight => $id) {
    $negotation[$id] = $all_negotiation_providers[$id];
    $negotation[$id]['weight'] = $weight;
  }
  language_negotiation_set(LANGUAGE_TYPE_INTERFACE, $negotation);
}