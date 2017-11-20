<?php
/**
 * @file
 * localize_fields_test.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function localize_fields_test_user_default_roles() {
  $roles = array();

  // Exported role: localize_fields_test_editor.
  $roles['localize_fields_test_editor'] = array(
    'name' => 'localize_fields_test_editor',
    'weight' => 3,
  );

  return $roles;
}
