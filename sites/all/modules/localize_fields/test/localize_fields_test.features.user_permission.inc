<?php
/**
 * @file
 * localize_fields_test.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function localize_fields_test_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create localize_fields_test content'.
  $permissions['create localize_fields_test content'] = array(
    'name' => 'create localize_fields_test content',
    'roles' => array(
      'localize_fields_test_editor' => 'localize_fields_test_editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own localize_fields_test content'.
  $permissions['delete own localize_fields_test content'] = array(
    'name' => 'delete own localize_fields_test content',
    'roles' => array(
      'localize_fields_test_editor' => 'localize_fields_test_editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own localize_fields_test content'.
  $permissions['edit own localize_fields_test content'] = array(
    'name' => 'edit own localize_fields_test content',
    'roles' => array(
      'localize_fields_test_editor' => 'localize_fields_test_editor',
    ),
    'module' => 'node',
  );

  return $permissions;
}
