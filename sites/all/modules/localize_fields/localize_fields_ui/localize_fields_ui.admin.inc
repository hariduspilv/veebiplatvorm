<?php
/**
 * @file
 *  Drupal Localize Fields UI module
 */

/**
 * Localize Fields UI settings.
 *
 * @see _localize_fields_ui_admin_form_submit()
 *
 * @param array &$form
 *
 * @return array
 */
function _localize_fields_ui_admin_form(&$form) {
  $form['localize_fields_ui'] = array(
    '#type' => 'fieldset',
    '#title' => t('Field user interface', array(), array('context' => 'module:localize_fields_ui')),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    'localize_fields_ui_clear_cache' => array(
      '#type' => 'checkbox',
      '#title' => t(
        'Clear translation cache for affected languages for every change in the Field user interface',
        array(), array('context' => 'module:localize_fields_ui')
      ),
      '#description' => t(
        'Not advisable for a high traffic live site, but otherwise a translation editor won\'t be able to test/confirm changes until the cache is cleared.<br/>If un-checked, the editor may check the next option (and press \'Save configuration\') at the end of work.',
        array('!break' => '<br/>'),
        array('context' => 'module:localize_fields_ui')
      ),
      '#default_value' => variable_get('localize_fields_ui_clear_cache', 1),
    ),
    'localize_fields_ui_clear_cache_now' => array(
      '#type' => 'checkbox',
      '#title' => t(
        'Clear translation cache of all languages !emphnow!_emph!',
        array('!emph' => '<em>', '!_emph' => '</em>'),
        array('context' => 'module:localize_fields_ui')
      ),
      '#default_value' => 0,
    ),
    'localize_fields_ui_log_changes' => array(
      '#type' => 'select',
      '#title' => t('Log and display translation changes', array(), array('context' => 'module:localize_fields_ui')),
      '#options' => array(
        0 => t('Don\'t log nor display', array(), array('context' => 'module:localize_fields_ui')),
        1 => t('Log only', array(), array('context' => 'module:localize_fields_ui')),
        2 => t('Log and display', array(), array('context' => 'module:localize_fields_ui')),
      ),
      // Default to log, because it may ease debugging.
      '#default_value' => variable_get('localize_fields_ui_log_changes', 1),
    ),
  );

  $form['#submit'][] = '_localize_fields_ui_admin_form_submit';
}
