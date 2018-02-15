<?php
/**
 * @file
 * Enables modules and site configuration for a standard site installation.
 */
include_once DRUPAL_ROOT . '/profiles/hitsa_school/hitsa_school.profile';

/**
 * Implements hook_form_FORM_ID_alter() for install_configure_form().
 *
 * Allows the profile to alter the site configuration form.
 */
function hitsa_vocational_form_install_configure_form_alter(&$form, $form_state) {
  // Pre-populate the site name with the server name.
  $form['site_information']['site_name']['#default_value'] = $_SERVER['SERVER_NAME'];
}

function hitsa_vocational_install_tasks() {
  return hitsa_school_install_tasks();
}

function hitsa_vocational_profile_details() {
  return hitsa_school_profile_details();
}