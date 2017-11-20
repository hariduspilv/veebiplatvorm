<?php
/**
 * @file
 *  Drupal Localize Fields module
 */

/**
 * Localize Fields settings.
 *
 * @param array $form
 * @param array &$form_state
 * @return array
 */
function _localize_fields_admin_form($form, &$form_state) {
  $form['#attributes'] = array(
    'autocomplete' => 'off',
    'class' => array('localize-fields-admin-form'),
  );
  $form['#attached']['css'][] = drupal_get_path('module', 'localize_fields') . '/css/localize_fields.admin.css';

  $form['localize_fields_help'] = array(
    '#type' => 'markup',
    '#markup' => '<p><b>' . l(t('About Localize Fields and it\'s drush script and sub modules', array(), array('context' => 'module:localize_fields')), 'admin/help/localize_fields', array('attributes' => array('target' => 'blank'))) . '</p></b>',
  );

  $form['localize_fields_usecontext'] = array(
    '#type' => 'radios',
    '#title' => t('Use translation context', array(), array('context' => 'module:localize_fields')),
    '#description' => t(
      'Also applies to drush localize-fields, unless given the --usecontext option which overrules.',
      array(), array('context' => 'module:localize_fields')
    ),
    '#default_value' => variable_get('localize_fields_usecontext', LocalizeFields::USE_CONTEXT_NONCONTEXT),
    '#options' => array(
      LocalizeFields::USE_CONTEXT_NONCONTEXT => t(
        'Yes, and fall back on non-context.',
        array(), array('context' => 'module:localize_fields')
      ),
      LocalizeFields::USE_CONTEXT => t(
        'Yes, no fallback. Clean and predictable, but not the right choice if you\'re only testing this module.',
        array(), array('context' => 'module:localize_fields')
      ),
      0 => t('No. And translations may get mixed up, just like ordinary translation.', array(), array('context' => 'module:localize_fields')),
    ),
  );

  $form['localize_fields_tentative'] = array(
    '#type' => 'checkbox',
    '#title' => t('Don\'t translate the label and/or description that gets passed to other widget alterers', array(), array('context' => 'module:localize_fields')),
    '#description' => t(
      'Localize Fields defaults to translate labels/descriptions of the $context arg passed to hook_field_widget_form_alter() implementations,!nlthus securing that other modules \'see\' translated labels/descriptions.!nlChecking this will break description translation (though only for field types which Token\'s replacement actually works for ;-).',
      array('!nl' => '<br/>'), array('context' => 'module:localize_fields')
    ),
    '#default_value' => variable_get('localize_fields_tentative', 0),
  );

  $form['localize_fields_source_add_row'] = array(
    '#type' => 'textfield',
    '#title' => t('Default source text of \'!add_row\' button labels', array('!add_row' => t('Add another item')), array('context' => 'module:localize_fields')),
    '#description' => t('For multi-valued fields.', array(), array('context' => 'module:localize_fields')),
    '#default_value' => variable_get('localize_fields_source_add_row', 'Add another item'),
    '#size' => 30,
  );

  // Add the UI module's fields.
  if (module_exists('localize_fields_ui')) {
    module_load_include('inc', 'localize_fields_ui', 'localize_fields_ui.admin');
    _localize_fields_ui_admin_form($form);
  }

  return system_settings_form($form);
}

/**
 *
 * @return array
 */
function _localize_fields_admin_copy_i18n_field_form() {
  return array(
    'copy_i18n_field_to' => array(
      '#title' => t('Copy translations to', array(), array('context' => 'module:localize_fields')),
      '#type' => 'radios',
      '#options' => array(
        'localize_fields' => t(
          'localize_fields (!human)',
          array(
            '!human' => t(
              'Localize Fields', array(), array('context' => 'module:localize_fields:module:localize_fields')
            )
          ),
          array('context' => 'module:localize_fields')
        ),
        'i18n_field' => t(
          'i18n_field (!human)',
          array(
            '!human' => t(
              'Field translation', array(), array('context' => 'module:localize_fields:module:i18n_field')
            )
          ),
          array('context' => 'module:localize_fields')
        ),
      ),
      '#default_value' => 'localize_fields',
    ),
    'submit' => array(
      '#type' => 'submit',
      '#value' => t('Copy translations', array(), array('context' => 'module:localize_fields')),
    ),
  );
}

/**
 * @param array $form
 * @param array &$form_state
 */
function _localize_fields_admin_copy_i18n_field_form_submit($form, &$form_state) {
  batch_set(localize_fields_copy_i18n_field_batch($form_state['values']['copy_i18n_field_to'] == 'i18n_field'));
}

/**
 * @param boolean $to_foreign
 *   Default: FALSE (~ copy from i18n_field to localize_fields).
 *   TRUE: copy from localize_fields to i18n_field.
 *
 * @return array
 */
function localize_fields_copy_i18n_field_batch($to_foreign = FALSE) {
  return array(
    'operations' => array(
      array('_localize_fields_copy_i18n_field_translations', array($to_foreign)),
    ),
    'finished' => '_localize_fields_copy_i18n_field_translations_finished',
    'title' => t('Copy i18n_field translations batch'),
    'init_message' => t('Copy i18n_field translations batch is starting.'),
    'progress_message' => t('Processed @current out of @total.'),
    'error_message' => t('Copy i18n_field translations batch encountered an error.'),
    'file' => drupal_get_path('module', 'localize_fields') . '/localize_fields.admin.inc',
  );
}

/**
 * Batch callback.
 *
 * @param boolean $to_foreign
 *   TRUE: copy from localize_fields to i18n_field.
 * @param array &$batch_context
 */
function _localize_fields_copy_i18n_field_translations($to_foreign, &$batch_context) {
  // In drush mode $batch_context is a descendant class of ArrayObject - not an array.
  // So do not do stuff like: $batch_context['sandbox'] = array(...).

  $drush = drupal_is_cli();

  $iteration_limit = 100;
  $time_limit_percent = 50;

  // Use db.locales_target.l10n_status column if it exists.
  $column_l10n_status = module_exists('features_translations');

  try {
    $delim = LocalizeFields::CONTEXT_DELIMITER;
    $location = 'localize_fields.module';

    // First call.
    if (empty($batch_context['sandbox'])) {
      $batch_context['finished'] = 0;
      $batch_context['sandbox']['iteration'] = 1;
      $batch_context['sandbox']['progress'] = 0;
      $batch_context['sandbox']['max'] = 0;
      $batch_context['sandbox']['sources'] = array();

      $batch_context['results']['sources_total'] = $batch_context['results']['sources_completed'] = $batch_context['results']['translations'] = 0;
      // We'll need that parameter value when reporting in the 'finished' function.
      $batch_context['results']['to_foreign'] = $to_foreign;

      // Find sources having any translation.
      /*
       * -- i18n_field -> localize_fields
       * SELECT DISTINCT src.lid
       * FROM locales_source AS src
       * JOIN locales_target as trg ON (trg.lid = src.lid)
       * WHERE src.textgroup = 'field'
       * AND trg.translation != ''
       * ORDER BY src.lid
       *
       * -- localize_fields -> i18n_field
       * SELECT DISTINCT src.lid
       * FROM locales_source AS src
       * JOIN locales_target as trg ON (trg.lid = src.lid)
       * WHERE src.textgroup = 'default'
       * AND (src.context LIKE ('field:%') OR src.context LIKE ('field_instance:%'))
       * AND trg.translation != ''
       * ORDER BY src.lid
       */
      $query = db_select('locales_source', 'src')
        ->distinct();
      $query->leftJoin('locales_target', 'trg', 'trg.lid = src.lid');
      $query->fields('src', array('lid', 'context', 'source'));
      if (!$to_foreign) {
        $query->condition('src.textgroup', 'field');
      }
      else {
        $query->condition('src.textgroup', 'default')
          ->condition(
            db_or()->condition('src.context', 'field' . $delim . '%', 'LIKE')->condition('src.context', 'field_instance' . $delim . '%', 'LIKE')
          );
      }
      $query->condition('trg.translation', '', '!=')
        ->orderBy('src.lid');
      $sources = $query->execute()->fetchAll();

      if (!$sources) {
        $batch_context['finished'] = 1;
        $batch_context['results'][] = $drush ? dt('No non-empty translations to copy.') : t('No non-empty translations to copy.');
        return;
      }

      $batch_context['sandbox']['sources'] =& $sources;
      $batch_context['sandbox']['max'] = $batch_context['results']['sources_total'] = count($sources);
    }
    // No more source_ids; unlikely, should have finished, but anyway.
    elseif (empty($batch_context['sandbox']['sources'])) {
      $batch_context['finished'] = 1;
      $batch_context['results'][] = $drush ? dt('Should already be finished.') : t('Should already be finished.');
      return;
    }
    else {
      $batch_context['sandbox']['iteration'] += 1;

      if ($batch_context['sandbox']['iteration'] > $iteration_limit) {
        $replacers = array('!n' => $iteration_limit);
        $batch_context['results'][] = $drush ? dt('Batch processing stopped because reached !n iterations limit.', $replacers) :
          t('Batch processing stopped because reached !n iterations limit.', $replacers);
        $batch_context['finished'] = 1;
        return;
      }

      $sources =& $batch_context['sandbox']['sources'];
    }

    $time_limit = 0;
    if (($max_duration = ini_get('max_execution_time'))) {
      $time_limit = REQUEST_TIME + floor($max_duration * $time_limit_percent / 100);
    }

    while ((!$time_limit || time() < $time_limit) && $sources) {
      $source = array_shift($sources);
      // If the target module translates a label having such context.
      if (($context = _localize_fields_i18n_field_context($source->context, $source->source, $to_foreign))) {
        $copy_targets = db_select('locales_target', 'trg')
          ->fields('trg', array('language', 'translation'))
          ->condition('lid', $source->lid)
          ->execute()
          ->fetchAllKeyed();

        // If there already exists a source having the 'new' context, we copy translation to that.
        $matching_source_id = db_select('locales_source', 'src')
          ->fields('src', array('lid'))
          ->condition('source', $source->source)
          ->condition('context', $context)
          ->execute()
          ->fetchField();
        if ($matching_source_id) {
          foreach ($copy_targets as $language => $translation) {
            db_merge('locales_target')
              ->key(array(
                'lid' => $matching_source_id,
                'language' => $language,
              ))
              ->fields(array(
                'translation' => $translation,
              ))
              ->execute();
            $batch_context['results']['translations'] += 1;
          }
        }
        else {
          // We do not create new sources for i18n_field, because i18n_field
          // discovers all field label sources upon enabling anyway.
          if (!$to_foreign) {
            $new_source_id = db_insert('locales_source')
              ->fields(array(
                'location' => $location,
                'source' => $source->source,
                'context' => $context,
              ))
              ->execute();
            foreach ($copy_targets as $language => $translation) {
              $fields = array(
                'lid' => $new_source_id,
                'translation' => $translation,
                'language' => $language,
              );
              if ($column_l10n_status) {
                $fields['l10n_status'] = 1;
              }
              db_insert('locales_target')
                ->fields($fields)
                ->execute();
              $batch_context['results']['translations'] += 1;
            }
            unset($fields);
          }
        }
      }
      $batch_context['sandbox']['progress'] += 1;
      $batch_context['results']['sources_completed'] += 1;
    }

    if ($batch_context['sandbox']['progress'] < $batch_context['sandbox']['max']) {
      $batch_context['finished'] = $batch_context['sandbox']['progress'] / $batch_context['sandbox']['max'];
    }
    else {
      $batch_context['finished'] = 1;
    }
  }
  catch (Exception $xc) {
    // Stop batch processing.
    $batch_context['finished'] = 1;

    // Tell ..._finished.
    $batch_context['results']['failed'] = TRUE;

    // Log.
    if ($drush) {
      $ms = !$to_foreign ? dt('Failed copying translations from i18n_field to localize_fields') :
        dt('Failed copying translations from localize_fields to i18n_field');
      drush_log($ms . '.', 'failed');
    }
    else {
      $ms = !$to_foreign ? t('Failed copying translations from i18n_field to localize_fields') :
        t('Failed copying translations from localize_fields to i18n_field');
      drupal_set_message($ms . '.', 'error');
    }
    if (module_exists('inspect') && user_access('inspect log')) {
      inspect_trace(
        $xc,
        array(
          'category' => 'localize_fields',
          'message' => $ms,
          'severity' => WATCHDOG_ERROR,
        )
      );
    }
    else {
      watchdog(
        'localize_fields',
        __CLASS__ . '::' . __FUNCTION__ . ': ' . $ms . ', error: @error.',
        array('@error' => $xc->getMessage()),
        WATCHDOG_ERROR
      );
    }
  }
}

/**
 * Batch finished.
 *
 * @param boolean $success
 *   TRUE unless PHP error(s) encountered.
 * @param array $results
 * @param array $operations
 */
function _localize_fields_copy_i18n_field_translations_finished($success, $results, $operations) {
  $drush = drupal_is_cli();

  if (!empty($results['failed'])) {
    $success = FALSE;
    unset($results['failed']);
  }

  $to_foreign = $results['to_foreign'];
  $total = $results['sources_total'];
  $completed = $results['sources_completed'];
  $translations = $results['translations'];
  unset($results['to_foreign'], $results['sources_total'], $results['sources_completed'], $results['translations']);

  $replacers = array('!total' => $total, '!completed' => $completed, '!translations' => $translations);

  if ($drush) {
    if ($results) {
      drush_print(dt('Results:') . "\n- " . join("\n- ", $results));
    }
  }
  else {
    if ($results) {
      drupal_set_message(t('Results:') . '<br/>- ' . join('<br/>- ', $results));
    }
  }

  // Clear translation cache of all languages (safer).
  $cc_ms = '';
  if ($translations) {
    cache_clear_all('locale:', 'cache', TRUE);
    if ($drush) {
      $cc_ms = "\n" . dt('Cleared translation cache of all languages.');
    }
    else {
      $cc_ms = '<br/>' . t('Cleared translation cache of all languages.');
    }
  }

  if ($success) {
    if ($drush) {
      $ms = !$to_foreign ?
        dt('Succeeded copying/updating !translations translations of !completed sources from i18n_field to localize_fields.', $replacers) :
        dt('Succeeded copying/updating !translations translations of !completed sources from localize_fields to i18n_field.', $replacers);
      drush_print($ms . $cc_ms);
    }
    else {
      $ms = !$to_foreign ?
        t('Succeeded copying/updating !translations translations of !completed sources from i18n_field to localize_fields.', $replacers) :
        t('Succeeded copying/updating !translations translations of !completed sources from localize_fields to i18n_field.', $replacers);
      drupal_set_message($ms . $cc_ms);
    }
  }
  else {
    if ($drush) {
      $ms = !$to_foreign ?
        dt('Failed - copyed !completed of !total sources from i18n_field to localize_fields.', $replacers) :
        dt('Failed - copyed !completed of !total sources from localize_fields to i18n_field.', $replacers);
      drush_log($ms . $cc_ms, 'failed');
    }
    else {
      $ms = !$to_foreign ?
        t('Failed - copyed !completed of !total sources from i18n_field to localize_fields.', $replacers) :
        t('Failed - copyed !completed of !total sources from localize_fields to i18n_field.', $replacers);
      drupal_set_message($ms . $cc_ms, 'error');
    }
  }
  watchdog(
    'localize_fields',
    $ms,
    array(),
    $success ? WATCHDOG_INFO : WATCHDOG_ERROR
  );
}

/**
 * @param string $context
 * @param string $source
 *   Non-empty if copying to i18n_field.
 * @param boolean $to_foreign
 *   Default: FALSE (~ copy from i18n_field to localize_fields).
 *   TRUE: copy from localize_fields to i18n_field.
 *
 * @return string
 *   Empty: context can't be resolved or isnt usable.
 */
function _localize_fields_i18n_field_context($context, $source = '', $to_foreign = FALSE) {
  static $markers = array(
    'base' => 'field',
    'instance' => 'field_instance',
    'delim' => LocalizeFields::CONTEXT_DELIMITER,
    'delim_bundle' => LocalizeFields::CONTEXT_DELIMITER_BUNDLE,
  );

  if ($context !== '') {
    if (!$to_foreign) {
      $parts = explode(':', $context);
      $le = count($parts);
      if ($le == 3) {
        // Instance.
        if ($parts[2] === 'label' || $parts[2] === 'description') {
          return $markers['instance'] . $markers['delim'] . $parts[1] . $markers['delim_bundle'] . $parts[0] . $markers['delim'] . $parts[2];
        }
        // Field.
        if ($parts[1] === '#allowed_values') {
          return $markers['base'] . $markers['delim'] . $parts[0] . $markers['delim'] . 'allowed_values';
        }
        // i18n offers translation of properties 'setting_add'/'setting_delete' which we don't know what's used for;
        // they are _not_ multi-row field instance settings (like 'Add' another file)
      }
    }
    else {
      // Instance.
      if (strpos($context, $markers['instance'] . $markers['delim']) === 0) {
        return preg_replace(
          '/^([^\\' . $markers['delim_bundle'] . ']+)\\' . $markers['delim_bundle'] . '([^\\' . $markers['delim'] . ']+)' . $markers['delim'] . '/',
          '$2:$1:',
          substr($context, strlen($markers['instance'] . $markers['delim']))
        );
      }
      // Field.
      if ($source !== '' && strpos($context, $markers['base'] . $markers['delim']) === 0 && strpos($context, $markers['delim'] . 'allowed_values')) {
        $field_name = str_replace($markers['delim'] . 'allowed_values', '', substr($context, strlen($markers['base'] . $markers['delim'])));
        $field_info = field_info_field($field_name);
        if (!empty($field_info['settings']['allowed_values_no_localization'])
          || empty($field_info['settings']['allowed_values'])
        ) {
          return '';
        }
        if (($value = array_search($source, $field_info['settings']['allowed_values'], TRUE)) !== '') {
          return $field_name . ':#allowed_values:' . $value;
        }
        // localize_fields translates (numeric) prefix and suffix; i18n_field doesn't.
      }
    }
  }
  return '';
}
