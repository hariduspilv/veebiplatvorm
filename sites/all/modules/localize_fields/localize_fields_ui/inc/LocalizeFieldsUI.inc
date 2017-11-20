<?php
/**
 * @file
 *  Drupal Localize Fields fields UI
 */

class LocalizeFieldsUI extends LocalizeFields {

  /**
   * We use the module's .module filename as translation source location.
   *
   * @var string
   */
  const LOCATION = 'localize_fields_ui.module';

  /**
   * @var string|NULL
   */
  protected static $sourceLanguage;

  /**
   * @var array
   */
  protected static $targetLanguages = array();

  /**
   * @var array
   */
  protected static $affectedLanguages = array(
    '_ALL_' => 0
  );

  /**
   * Establishes source language and target (optionally only enabled) languages.
   *
   * Translating to a language that isn't enabled should - at least theoretically - be possible.
   *
   * @param bool $enabled
   */
  protected static function getLanguages($enabled = FALSE) {
    $languages = language_list();

    // Establish source language by variable; fall back on English.
    if (!self::SOURCE_LANGUAGE_FALLBACK_FIRST_LANGUAGE) {
      $sourceLang = variable_get('i18n_string_source_language', 'en');
      unset($languages[$sourceLang]);
    }
    // Establish source language by variable; fall back on first enabled language (daft, but what appears to happen if no variable).
    elseif (!($sourceLang = variable_get('i18n_string_source_language'))) {
      $sourceLang = '';
      // Assume that source language has to be enabled(?).
      foreach ($languages as $langcode => $props) {
        if ($props->enabled) {
          $sourceLang = $langcode;
          break;
        }
      }
    }

    if ($sourceLang) {
      self::$sourceLanguage = $sourceLang;
      unset($languages[$sourceLang]);
      if ($enabled && $languages) {
        $remove = array();
        foreach ($languages as $langcode => $props) {
          if (!$props->enabled) {
            $remove[] = $langcode;
          }
        }
        if ($remove) {
          foreach ($remove as $langcode) {
            unset($languages[$langcode]);
          }
        }
      }
      // Possibly empty.
      self::$targetLanguages = $languages;
    }
  }

  /**
   * Helper for the form_alter.
   *
   * @see LocalizeFieldsUI::fieldUIFieldEditFormAlter()
   *
   * @param array &$form_instance
   *   $form['instance'] or $form['instance']['some bucket'] (= $form['instance']['settings'])
   * @param string $item
   * @param string $context
   */
  protected static function addInstanceTranslationFields(&$form_instance, $item, $context) {
    if (($targets = self::$targetLanguages)) {
      $source = array_key_exists('#default_value', $form_instance[$item]) ? $form_instance[$item]['#default_value'] : '';
      $fieldset = array(
        '#type' => 'fieldset',
        '#title' => t(
          'Translate !item',
          array('!item' => array_key_exists('#title', $form_instance[$item]) ? $form_instance[$item]['#title'] : ''),
          array('context' => 'module:localize_fields_ui')
        ),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
        '#attributes' => array(
          'class' => array(
            'localize-fields-ui',
          ),
        ),
        'item' => array(
          '#type' => 'hidden',
          '#default_value' => $item,
        ),
        'title' => array(
          '#type' => 'hidden',
          '#default_value' => $form_instance[$item]['#title'],
        ),
        'source_original' => array(
          '#type' => 'hidden',
          '#default_value' => $source,
        ),
        'context' => array(
          '#type' => 'hidden',
          '#default_value' => $contextFinal = !$context ? '' : ($context . $item),
        ),
      );
      if (array_key_exists('#weight', $form_instance[$item])) {
        $fieldset['#weight'] = $form_instance[$item]['#weight'] + 1;
      }

      // Cannot use t() or locale(), because they create the source if it doesn't exist (and there appears to be no non-crud alternative).
      $translations = array();
      if ($source !== '') {
        try {
          /*
           * SELECT trg.translation, trg.language
           * FROM locales_source AS src
           * JOIN locales_target AS trg ON (trg.lid = src.lid)
           * WHERE src.source = 'Whatever'
           * AND (src.context = 'da context' OR src.context = '')
           * AND trg.translation != ''
           * ORDER BY trg.language, scr.context
           */
          $query = db_select('locales_source', 'src');
          $query->leftJoin('locales_target', 'trg', 'trg.lid = src.lid');
          $query->fields('trg', array('translation', 'language'))
            ->condition('src.source', $source)
            ->condition('trg.translation', '', '!=');

          // Context + non-context fallback: list contextual before non-contextual.
          if (self::$useContext == self::USE_CONTEXT_NONCONTEXT) {
            $query->condition(db_or()->condition('src.context', $contextFinal)->condition('src.context', ''))
              ->orderBy('trg.language')
              ->orderBy('src.context', 'DESC'); // Non-empty before empty.
          }
          else {
            $query->condition('src.context', $contextFinal)
              ->orderBy('trg.language');
          }

          $allTranslations = $query->execute()->fetchAll();

          if ($allTranslations) {
            $fieldset['#collapsed'] = FALSE;
          }

          // Filter, get only one translation per language.
          $lastLang = NULL;
          foreach ($allTranslations as $translation) {
            if (($lang = $translation->language) != $lastLang) {
              $lastLang = $lang;
              $translations[$lang] = $translation->translation;
            }
            else {
              // Skip dupe translations (~ with vs. without context).
              continue;
            }
          }
          unset($allTranslations);
        }
        catch (PDOException $xc) {
          if (module_exists('inspect') && user_access('inspect log')) {
            inspect_trace(
              $xc,
              array(
                'category' => 'localize_fields_ui',
                'message' => 'Failed to add instance translation fields',
                'severity' => WATCHDOG_ERROR,
              )
            );
          }
          else {
            watchdog(
              'localize_fields_ui',
              __CLASS__ . '::' . __FUNCTION__ . ': Failed to add instance translation fields, error: @error.',
              array('@error' => $xc->getMessage()),
              WATCHDOG_ERROR
            );
          }
          drupal_set_message(
            t(
              'Failed to add field instance label translation fields, error: @error.',
              array('@error' => $xc->getMessage()),
              array('context' => 'module:localize_fields_ui')
            )
          );
          return;
        }
      }

      foreach ($targets as $targetLang => $langProps) {
        $fieldset[$targetLang] = array(
          '#type' => $form_instance[$item]['#type'],
          '#title' => t(
            '!lang_name (!lang_code: !lang_native)',
            array('!lang_code' => $targetLang, '!lang_name' => t($langProps->name), '!lang_native' => $langProps->native),
            array('context' => 'module:localize_fields_ui')
          ),
          '#default_value' => $source === '' || !$translations || !isset($translations[$targetLang]) ? '' : $translations[$targetLang],
        );
        if ($form_instance[$item]['#type'] == 'textarea') {
          if (!empty($form_instance[$item]['#rows'])) {
            $fieldset[$targetLang]['#rows'] = $form_instance[$item]['#rows'] - 1;
          }
          if (!empty($form_instance[$item]['#cols'])) {
            $fieldset[$targetLang]['#cols'] = $form_instance[$item]['#cols'];
          }
        }
      }
      $form_instance['localize_fields_ui__' . $item] = $fieldset;
    }
  }

  /**
   * Helper for the form_alter.
   *
   * @see LocalizeFields::fieldUIFieldEditFormAlter()
   *
   * @param array &$field_settings
   *   $form['field']['settings']]
   * @param string $context
   * @param boolean $hide
   * @param array|NULL $list_boolean_sources
   */
  protected static function addAllowedValuesTranslationFields(&$field_settings, $context, $hide, $list_boolean_sources = NULL) {
    if (($targets = self::$targetLanguages)) {
      $item = 'allowed_values';

      // Don't use translation of un-translated-marker if the translation is empty (paranoid).
      if (!($unTranslatedMarker = t('_NOT_TRANSLATED_', array(), array('context' => 'module:localize_fields_ui:not_translated_marker')))) {
        $unTranslatedMarker = '_NOT_TRANSLATED_';
      }

      if (!$list_boolean_sources) {
        $source = $field_settings[$item]['#default_value'];
        $sources = $field_settings[$item]['#field']['settings']['allowed_values'];
      }
      else {
        $source = '';
        $sources = $list_boolean_sources;
      }

      $fieldset = array(
        '#type' => 'fieldset',
        '#title' => t('Translate !label', array('!label' => t('Allowed values list')), array('context' => 'module:localize_fields_ui')),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
        '#attributes' => array(
          'class' => array(
            'localize-fields-ui',
            'localize-fields-ui-field-settings-allowed-values',
          ),
        ),
        'item' => array(
          '#type' => 'hidden',
          '#default_value' => $item,
        ),
        'title' => array(
          '#type' => 'hidden',
          '#default_value' => t('Allowed values list'),
        ),
        'source_original' => array(
          '#type' => 'hidden',
          '#default_value' => json_encode($sources),
        ),
        'context' => array(
          '#type' => 'hidden',
          '#default_value' => $contextFinal = !$context ? '' : ($context . $item),
        ),
      );
      if (array_key_exists('#weight', $field_settings[$item])) {
        $fieldset['#weight'] = $field_settings[$item]['#weight'] + 2; // After allowed_values_no_localization.
      }
      if ($hide) {
        $fieldset['#attributes']['style'] = array(
          'display:none;'
        );
      }

      // Cannot use t() or locale(), because they create the source if it doesn't exist (and there appears to be no non-crud alternative).
      $translations = array();
      if ($list_boolean_sources || $source !== '') {
        try {
          $query = db_select('locales_source', 'src');
          $query->leftJoin('locales_target', 'trg', 'trg.lid = src.lid');
          $query->fields('src', array('source'))
            ->fields('trg', array('translation', 'language'))
            ->condition('src.source', $sources, 'IN')
            ->condition('trg.translation', '', '!=');

          // Context + non-context fallback: list contextual before non-contextual.
          if (self::$useContext == self::USE_CONTEXT_NONCONTEXT) {
            $query->condition(db_or()->condition('src.context', $contextFinal)->condition('src.context', ''))
              ->orderBy('trg.language')
              ->orderBy('src.context', 'DESC'); // Non-empty before empty.
          }
          else {
            $query->condition('src.context', $contextFinal)
              ->orderBy('trg.language');
          }

          $allTranslations = $query->execute()->fetchAll();

          if ($allTranslations) {
            $fieldset['#collapsed'] = FALSE;
          }

          // Filter, get only one translation per language.
          $lastLang = NULL;
          foreach ($allTranslations as $translation) {
            if (($lang = $translation->language) != $lastLang) {
              $lastLang = $lang;
              $translations[$lang] = array();
            }
            if (!array_key_exists($translation->source, $translations[$lang])) {
              $translations[$lang][$translation->source] = $translation->translation;
            }
          }
          unset($allTranslations);
        }
        catch (PDOException $xc) {
          if (module_exists('inspect') && user_access('inspect log')) {
            inspect_trace(
              $xc,
              array(
                'category' => 'localize_fields_ui',
                'message' => 'Failed to add allowed_values translation fields',
                'severity' => WATCHDOG_ERROR,
              )
            );
          }
          else {
            watchdog(
              'localize_fields_ui',
              __CLASS__ . '::' . __FUNCTION__ . ': Failed to add allowed_values translation fields, error: @error.',
              array('@error' => $xc->getMessage()),
              WATCHDOG_ERROR
            );
          }
          drupal_set_message(
            t(
              'Failed to add field allowed_values label translation fields, error: @error.',
              array('@error' => $xc->getMessage()),
              array('context' => 'module:localize_fields_ui')
            )
          );
          return;
        }
      }

      foreach ($targets as $targetLang => $langProps) {
        $translated = '';
        if ($translations && array_key_exists($targetLang, $translations)) {
          $translations_by_lang =& $translations[$targetLang];
          foreach ($sources as $val => $src) {
            $translated .= ($translated ? "\n" : '') . $val . '|'
              . (array_key_exists($src, $translations_by_lang) ? $translations_by_lang[$src] : $unTranslatedMarker);
          }
          unset($translations_by_lang);
        }

        $fieldset[$targetLang] = array(
          '#type' => 'textarea',
          '#title' => t(
            '!lang_name (!lang_code: !lang_native)',
            array('!lang_code' => $targetLang, '!lang_name' => t($langProps->name), '!lang_native' => $langProps->native),
            array('context' => 'module:localize_fields_ui')
          ),
          '#default_value' => $translated,
        );
        if ($list_boolean_sources) {
          $fieldset[$targetLang]['#rows'] = 2;
        }
        elseif (!empty($field_settings[$item]['#rows'])) {
          $fieldset[$targetLang]['#rows'] = $field_settings[$item]['#rows'] - 1;
        }
        if (!empty($field_settings[$item]['#cols'])) {
          $fieldset[$targetLang]['#cols'] = $field_settings[$item]['#cols'];
        }
      }
      $field_settings['localize_fields_ui__' . $item] = $fieldset;
    }
  }

  /**
   * Adds translation fields to field instance settings forms.
   *
   * And prepends submit function, which removes all translation fields again - before the form reaches standard submit function.
   *
   * Implements hook_form_FORM_ID_alter() for field_ui_field_edit_form.
   *
   * @see field_ui_field_edit_form().
   * @see localize_fields_form_field_ui_field_edit_form_alter()
   *
   * @param &$form
   * @param &$form_state
   */
  public static function fieldUIFieldEditFormAlter(&$form, &$form_state) {

    // Do nothing unless there exist other languages than the source language.
    self::getLanguages();
    $sourceLang = self::$sourceLanguage;
    $targetLangs = self::$targetLanguages;
    if ($sourceLang && $targetLangs) {

      // Turn off field autocompletion.
      $form['#attributes']['autocomplete'] = 'off';

      // Attach styles.
      $form['#attached']['css'][] = drupal_get_path('module', 'localize_fields_ui') . '/css/field-ui-field-edit-form.css';

      $bundle = $form['#instance']['bundle'];
      $field_name = $form['#instance']['field_name'];
      $field_type = $form['#field']['type'];

      self::$useContext = $useContext = variable_get('localize_fields_usecontext', LocalizeFields::USE_CONTEXT_NONCONTEXT);

      if ($useContext) {
        $cntxtDelim = self::CONTEXT_DELIMITER;
        $context = 'field_instance' . $cntxtDelim . $bundle . self::CONTEXT_DELIMITER_BUNDLE . $field_name . $cntxtDelim;
      }
      else {
        $context = '';
      }


      // field_instance.

      // Label and description.
      if (array_key_exists('label', $form['instance'])) {
        self::addInstanceTranslationFields($form['instance'], 'label', $context);
      }
      if (array_key_exists('description', $form['instance'])) {
        self::addInstanceTranslationFields($form['instance'], 'description', $context);
      }

      // Prefix/suffix.
      if (array_key_exists('settings', $form['instance']) && !empty($form['instance']['settings'])) {
        if (array_key_exists('prefix', $form['instance']['settings'])) {
          self::addInstanceTranslationFields($form['instance']['settings'], 'prefix', $context);
        }
        if (array_key_exists('suffix', $form['instance']['settings'])) {
          self::addInstanceTranslationFields($form['instance']['settings'], 'suffix', $context);
        }
      }


      // field.

      if (!empty($form['field']['settings'])) {
        $field_settings =& $form['field']['settings'];

        // list type fields.
        if (array_key_exists('allowed_values', $field_settings)
          && in_array($field_type, array('list_boolean', 'list_text', 'list_integer', 'list_decimal', 'list_float'))
        ) {
          // Checking for supported list_ type is the safest.
          // And localize_field already only supports translation of 'allowed_values' for these simple core list_ field types;
          // see LocalizeFields::fieldWidgetFormAlter() and LocalizeFields::fieldAttachViewAlter().
          //
          // If we were more bold, we could do
          // && empty($field_settings['allowed_values']['#tree'])
          // which effectively would rule out types like 'taxonomy_term_reference'.
          // But then again, non-core list types may have all sorts of structural compositions, that cannot be predicted and handled.

          $list_boolean_sources = NULL;
          // type: list_boolean.
          if ($form['#field']['type'] == 'list_boolean'
            || (!empty($field_settings['allowed_values']['#type'])
            && $field_settings['allowed_values']['#type'] == 'value'
          )) {
            $list_boolean_sources = array(
              1 => $form['#field']['settings']['allowed_values'][1],
              0 => $form['#field']['settings']['allowed_values'][0],
            );
          }

          // The field settings flag 'allowed_values_no_localization' ought not to collide with other,
          // and field _value_ translation is flagged with 'translatable' (in field settings' root).
          if (empty($field_settings['allowed_values_no_localization'])) {

            // We have to _get_ the value from field_info_field(), because non-standard field settings do not 'automagically'
            // appear in field_ui's form.
            $fieldInfo = field_info_field($field_name);
            $allowed_values_no_localization = empty($fieldInfo['settings']['allowed_values_no_localization']) ? 0 : 1;
            unset($fieldInfo);
            // However, don't have to do anything out of the ordinary to _save_ it to field settings,
            // because the setting actually gets saved just by submitting the form.

            $field_settings['allowed_values_no_localization'] = array(
              '#type' => 'checkbox',
              '#title' => t('Don\'t translate allowed values\' labels', array(), array('context' => 'module:localize_fields_ui')),
              '#attributes' => array(
                // General form #attributes may already do this, but here it's critical.
                'autocomplete' => 'off',
                // This is not rocket science.
                'onclick' => 'jQuery(\'fieldset.localize-fields-ui-field-settings-allowed-values\')[this.checked ? \'hide\' : \'show\']();',
              ),
              '#default_value' => $allowed_values_no_localization,
            );
            if (!$list_boolean_sources) {
              $field_settings['allowed_values_no_localization']['#description'] = t(
                'Translating a long list of options adds a performance hit. And if all labels are numeric integers then the translator will ignore them anyway.',
                array(), array('context' => 'module:localize_fields_ui')
              );
            }
            elseif (!self::$useContext) {
              $field_settings['allowed_values_no_localization']['#description'] = t(
                'Beware of translating generic phrases like \'Yes\' and \'No\' to something non-generic,!breakwhen module localize_fields\'s \'Use translation context\' setting is \'No\'.!breakWithout translation context the scope is global.',
                array('!break' => '<br/>'), array('context' => 'module:localize_fields_ui')
              );
            }
            if (array_key_exists('#weight', $field_settings['allowed_values'])) {
              $field_settings['allowed_values_no_localization']['#weight'] = $field_settings['allowed_values']['#weight'] + 1;
            }
          }
          else {
            $allowed_values_no_localization = $field_settings['allowed_values_no_localization']['#default_value'];
          }

          if ($useContext) {
            $cntxtDelim = self::CONTEXT_DELIMITER;
            $context = 'field' . $cntxtDelim . $field_name . $cntxtDelim;
          }
          else {
            $context = '';
          }

          // allowed_values.
          self::addAllowedValuesTranslationFields($field_settings, $context, $allowed_values_no_localization, $list_boolean_sources);
        }
        // Non-list field types.
        else {
          // 'Add another item' button label.
          if (!empty($form['field']['cardinality'])) {
            $field_settings['add_row_localization_source'] = array(
              '#type' => 'textfield',
              '#title' => t('Source text of \'!add_row\' button label', array('!add_row' => t('Add another item')), array('context' => 'module:localize_fields_ui')),
              '#description' => t(
                'Only applicable if \'!cardinality\' isn\'t 1 (one).<br>Actually means adding another <em>row</em>.',
                array('!cardinality' => t('Number of values')),
                array('context' => 'module:localize_fields_ui')
              ),
              '#default_value' => isset($form['#field']['settings']['add_row_localization_source']) ?
                $form['#field']['settings']['add_row_localization_source'] :
                variable_get('localize_fields_source_add_row', 'Add another item'),
              '#required' => FALSE,
              // Hopefully right after the cardinality select field.
              '#weight' => -1,
            );
            // @todo: Make it translatable here, in field UI.
          }
        }

        unset($field_settings); // Simple ref.
      }

      // General info.
      $form['field']['localize_fields_ui'] = array(
        '#tree' => TRUE,
        '#type' => 'fieldset',
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
        '#attributes' => array(
          'style' => array(
            'display:none',
          ),
        ),
        'bundle' => array(
          '#type' => 'hidden',
          '#default_value' => $bundle,
        ),
        'field_name' => array(
          '#type' => 'hidden',
          '#default_value' => $field_name,
        ),
        'source_language' => array(
          '#type' => 'hidden',
          '#default_value' => $sourceLang,
        ),
        'target_languages' => array(
          '#type' => 'hidden',
          '#default_value' => join(',', array_keys($targetLangs)),
        ),
      );
    }

    // Prepend our submit handler; we need to get in and remove our fields, otherwise they end up in the field instance' settings in db.
    array_unshift($form['#submit'], 'localize_fields_ui_field_ui_field_edit_form_submit');
  }

  /**
   * Helper for the form submit.
   *
   * @see LocalizeFieldsUI::fieldUIFieldEditFormSubmit()
   *
   * @throws PDOException
   *   Propagated.
   *
   * @param array &$input
   * @param array &$values
   *
   * @return array
   *   List of messages.
   */
  protected static function translateItems(&$input, &$values) {
    // Use db.locales_target.l10n_status column if it exists.
    $column_l10n_status = module_exists('features_translations');

    /*
     * We have to remove all the fields added during form_alter,
     * otherwise their values get written to database field_config/field_config_instance.
     */
    $removeFields = array();

    $messages = array();

    foreach ($values as $key => $props) {
      if (strpos($key, 'localize_fields_ui__') === 0) {
        $removeFields[] = $key;

        $item = $props['item'];

        // The item may not exist any more, due to some other form_alter.
        if (array_key_exists($item, $values)) {
          $source_original = $props['source_original'];
          $context = $props['context'];

          $source = $values[$item];

          $title = $props['title'];
          $messages[$title] = array();

          // If source has changed then we have to remove the original source and it's translations.
          // But only if context is turned on, because we can only find a translation source safely
          // by context - a non-contextual might be used elsewhere.
          if ($source_original !== '' && $source !== $source_original) {
            if ($context) {
              // Delete source + translations.
              // We look for more than one source, just in case there's dupes (clean up mess).
              if (($source_ids = db_select('locales_source', 'src')
                ->fields('src', array('lid'))
                ->condition('source', $source_original)
                ->condition('context', $context)
                ->execute()
                ->fetchCol())
              ) {
                db_delete('locales_target')
                  ->condition('lid', $source_ids, 'IN')
                  ->execute();
                db_delete('locales_source')
                  ->condition('lid', $source_ids, 'IN')
                  ->execute();
                // Caches of obsolete sources/translations don't affect the field UI,
                // but they do affect the general translation UI.
                // 2 ~ existing sources/targets affected.
                self::$affectedLanguages['_ALL_'] = 2;
              }
              $messages[$title][] = t(
                'removed source and translations of old source \'!source\'',
                array('!source' => $source_original),
                array('context' => 'module:localize_fields_ui')
              );
            }
            else {
              $messages[$title][] = t(
                'skipped removing source and translations of old source \'!source\' because fields localization is set to non-contextual',
                array('!source' => $source_original),
                array('context' => 'module:localize_fields_ui')
              );
            }
          }

          // Do nothing if empty source (or integer).
          if ($source && !ctype_digit('' . $source)) {
            // Remove these, because then all the other buckets are [language code] => [translation].
            unset($props['item'], $props['title'], $props['source_original'], $props['context']);

            // Get source id if source already exists.
            // We just get the first one; cannot clean up in this phase.
            $source_id = db_select('locales_source', 'src')
              ->fields('src', array('lid'))
              ->condition('source', $source)
              ->condition('context', $context)
              ->execute()
              ->fetchField();

            // Make list of non-empty vs. empty translations.
            $translations_nonEmpty = $languages_empty = array();
            foreach ($props as $targetLang => $translation) {
              if ($translation !== '') {
                $translations_nonEmpty[$targetLang] = $translation;
              }
              else {
                $languages_empty[] = $targetLang;
              }
            }
            unset($props); // Not used any more.

            // Source already exists: remove empty translations (if context!) and insert/update non-empties
            if ($source_id) {
              if ($languages_empty) {
                if ($context) {
                  db_delete('locales_target')
                    ->condition('lid', $source_id)
                    ->condition('language', $languages_empty, 'IN')
                    ->execute();
                  foreach ($languages_empty as $targetLang) {
                    self::$affectedLanguages[$targetLang] = 2;
                  }
                  $messages[$title][] = t(
                    'removed translations (if any) for language(s): !targets',
                    array('!targets' => join(', ', $languages_empty)),
                    array('context' => 'module:localize_fields_ui')
                  );
                }
                else {
                  $messages[$title][] = t(
                    'skipped removing empty translations because fields localization is set to non-contextual',
                    array(),
                    array('context' => 'module:localize_fields_ui')
                  );
                }
              }
              unset($languages_empty);

              if ($translations_nonEmpty) {
                $inserts = $updates = array();
                foreach ($translations_nonEmpty as $targetLang => $translation) {
                  $existing = db_select('locales_target', 'trg')
                    ->fields('trg', array('translation'))
                    ->condition('lid', $source_id)
                    ->condition('language', $targetLang)
                    ->execute()
                    ->fetchField();

                  if ($existing !== $translation) {
                    if ($existing === FALSE) {
                      $fields = array(
                        'lid' => $source_id,
                        'translation' => $translation,
                        'language' => $targetLang,
                      );
                      if ($column_l10n_status) {
                        $fields['l10n_status'] = 1;
                      }
                      db_insert('locales_target')
                        ->fields($fields)
                        ->execute();
                      $inserts[] = $targetLang;
                    }
                    else {
                      db_update('locales_target')
                        ->fields(array(
                          'translation' => $translation,
                        ))
                        ->condition('lid', $source_id)
                        ->condition('language', $targetLang)
                        ->execute();
                      $updates[] = $targetLang;
                    }

                    self::$affectedLanguages[$targetLang] = 2;
                  }
                  /* A merge would be much simpler (and safer), but result in unnecessary db activity and misleading feedbach to user.
                   * db_merge('locales_target')
                   *   ->key(array(
                   *     'lid' => $source_id,
                   *     'language' => $targetLang,
                   *   ))
                   *   ->fields(array(
                   *     'translation' => $translation,
                   *   ))
                   *   ->execute();
                   */
                }
                if ($updates) {
                  $messages[$title][] = t(
                    'updated translations for language(s): !targets',
                    array('!targets' => join(', ', $updates)),
                    array('context' => 'module:localize_fields_ui')
                  );
                }
                if ($inserts) {
                  $messages[$title][] = t(
                    'created translations for language(s): !targets',
                    array('!targets' => join(', ', $inserts)),
                    array('context' => 'module:localize_fields_ui')
                  );
                }
              }
            }
            // New source.
            else {
              $source_id = db_insert('locales_source')
                ->fields(array(
                  'location' => self::LOCATION,
                  'source' => $source,
                  'context' => $context,
                ))
                ->execute();

              // Ignore empty translations; don't create empty translations ;-).
              if ($translations_nonEmpty) {
                foreach ($translations_nonEmpty as $targetLang => $translation) {
                  $fields = array(
                    'lid' => $source_id,
                    'translation' => $translation,
                    'language' => $targetLang,
                  );
                  if ($column_l10n_status) {
                    $fields['l10n_status'] = 1;
                  }
                  db_insert('locales_target')
                    ->fields($fields)
                    ->execute();

                  if (empty(self::$affectedLanguages[$targetLang])) {
                    // 1 ~ new source + translation won't affect cache,
                    // because the source doesn't exist in the cache (right ;-).
                    self::$affectedLanguages[$targetLang] = 1;
                  }
                }
                $messages[$title][] = t(
                  'created translations for language(s): !targets',
                  array('!targets' => join(', ', array_keys($translations_nonEmpty))),
                  array('context' => 'module:localize_fields_ui')
                );
              }
            }
          }
          if (empty($messages[$title])) {
            unset($messages[$title]);
          }
        }
      }
    }
    // Shan't be saved to db.field_config/field_config_instance.
    foreach ($removeFields as $key) {
      unset($input[$key], $values[$key]);
    }

    return $messages;
  }

  /**
   * Helper for the form submit.
   *
   * @see LocalizeFieldsUI::fieldUIFieldEditFormSubmit()
   *
   * @throws PDOException
   *   Propagated.
   *
   * @param array $props
   *   allowed_values fieldset.
   * @param array $allowedValues
   *   allowed_values list.
   *
   * @return array
   *   List of messages.
   */
  protected static function translateAllowedValues($props, $allowedValues) {
    // Use db.locales_target.l10n_status column if it exists.
    $column_l10n_status = module_exists('features_translations');

    $messages = array();

    // Don't use translation of un-translated-marker if the translation is empty (paranoid).
    if (!($unTranslatedMarker = t('_NOT_TRANSLATED_', array(), array('context' => 'module:localize_fields_ui:not_translated_marker')))) {
      $unTranslatedMarker = '_NOT_TRANSLATED_';
    }

    $sources_original = json_decode($props['source_original'], TRUE);

    $context = $props['context'];

    $title = $props['title'];
    $messages[$title] = array();

    // If source has changed then we have to remove the original source and it's translations.
    // But only if context is turned on, because we can only find a translation source safely
    // by context - a non-contextual might be used elsewhere.
    if ($sources_original && ($obsoletes = array_diff($sources_original, $allowedValues))) {
      if ($context) {
        // Delete source + translations.
        if (($source_ids = db_select('locales_source', 'src')
          ->fields('src', array('lid'))
          ->condition('source', $obsoletes, 'IN')
          ->condition('context', $context)
          ->execute()
          ->fetchCol())
        ) {
          db_delete('locales_target')
            ->condition('lid', $source_ids, 'IN')
            ->execute();
          db_delete('locales_source')
            ->condition('lid', $source_ids, 'IN')
            ->execute();
          // Caches of obsolete sources/translations don't affect the field UI,
          // but they do affect the general translation UI.
          // 2 ~ existing sources/targets affected.
          self::$affectedLanguages['_ALL_'] = 2;
        }
        $messages[$title][] = t(
          'removed source and translations of old sources \'!sources\'',
          array('!sources' => join('\', \'', $obsoletes)),
          array('context' => 'module:localize_fields_ui')
        );
      }
      else {
        $messages[$title][] = t(
          'skipped removing source and translations of old sources \'!sources\' because fields localization is set to non-contextual',
          array('!sources' => join('\', \'', $obsoletes)),
          array('context' => 'module:localize_fields_ui')
        );
      }
    }

    // Do nothing if empty source (or integers).
    $removeIntegers = array();
    foreach ($allowedValues as $source) {
      if (ctype_digit('' . $source)) {
        $removeIntegers[] = $source;
      }
    }
    if ($removeIntegers) {
      $allowedValues = array_diff($allowedValues, $removeIntegers);
      $messages[$title][] = t(
        'skipped translating some allowed_values because their labels in the source language were integers',
        array(),
        array('context' => 'module:localize_fields_ui')
      );
    }

    if ($allowedValues) {
      // Remove these, because then all the other buckets are [language code] => [translation].
      unset($props['item'], $props['title'], $props['source_original'], $props['context']);

      $sources = array();
      foreach ($props as $targetLang => &$translation) {
        if (($translation = trim($translation)) !== '' && ($translation = explode("\n", str_replace("\r", '', $translation)))) {
          foreach ($translation as $option) {
            if (($sourceByValue = trim($option)) !== '' && ($pos = strpos($sourceByValue, '|')) && $pos < strlen($sourceByValue) - 1) {
              $sourceByValue = explode('|', $sourceByValue);
              if (array_key_exists($value = $sourceByValue[0], $allowedValues)
                && $sourceByValue[1] !== $unTranslatedMarker
              ) {
                if (!array_key_exists($allowedValues[$value], $sources)) {
                  $sources[$allowedValues[$value]] = array(
                    $targetLang => $sourceByValue[1]
                  );
                }
                else {
                  $sources[$allowedValues[$value]][$targetLang] = $sourceByValue[1];
                }
              }
            }
          }
        }
      }
      unset($translation); // Iteration ref.

      if ($sources) {
        // Remove empty translations (if context!) and insert/update non-empties.
        $removables = array();
        if ($context) {
          $targetLangs = array_keys($props);
          foreach ($allowedValues as $source) {
            if (!array_key_exists($source, $sources)) {
              $removables[$source] = $targetLangs;
            }
            else {
              foreach ($targetLangs as $targetLang) {
                if (!array_key_exists($targetLang, $sources[$source])) {
                  if (!array_key_exists($source, $removables)) {
                    $removables[$source] = array($targetLang);
                  }
                  else {
                    $removables[$source][] = $targetLang;
                  }
                }
              }
            }
          }
        }
        else {
          $messages[$title][] = t(
            'skipped removing empty translations because fields localization is set to non-contextual',
            array(),
            array('context' => 'module:localize_fields_ui')
          );
        }

        $deletes = $inserts = $updates = array();

        foreach ($sources as $source => $translations) {
          // Get source id if source already exists.
          // We just get the first one; cannot clean up in this phase.
          if (($source_id = db_select('locales_source', 'src')
            ->fields('src', array('lid'))
            ->condition('source', $source)
            ->condition('context', $context)
            ->execute()
            ->fetchField())
          ) {
            if ($removables && array_key_exists($source, $removables)) {
              db_delete('locales_target')
                ->condition('lid', $source_id)
                ->condition('language', $removables[$source], 'IN')
                ->execute();
              foreach ($removables[$source] as $targetLang) {
                $deletes[$targetLang] = TRUE;
                self::$affectedLanguages[$targetLang] = 2;
              }
            }

            if (!($existingByLangs = db_select('locales_target', 'trg')
              ->fields('trg', array('language'))
              ->condition('lid', $source_id)
              ->condition('language', array_keys($translations), 'IN')
              ->execute()
              ->fetchCol())
            ) {
              foreach ($translations as $targetLang => $translation) {
                $fields = array(
                  'lid' => $source_id,
                  'translation' => $translation,
                  'language' => $targetLang,
                );
                if ($column_l10n_status) {
                  $fields['l10n_status'] = 1;
                }
                db_insert('locales_target')
                  ->fields($fields)
                  ->execute();
                $inserts[$targetLang] = TRUE;
                self::$affectedLanguages[$targetLang] = 2;
              }
            }
            else {
              foreach ($translations as $targetLang => $translation) {
                if (!in_array($targetLang, $existingByLangs)) {
                  $fields = array(
                    'lid' => $source_id,
                    'translation' => $translation,
                    'language' => $targetLang,
                  );
                  if ($column_l10n_status) {
                    $fields['l10n_status'] = 1;
                  }
                  db_insert('locales_target')
                    ->fields($fields)
                    ->execute();
                  $inserts[$targetLang] = TRUE;
                }
                else {
                  db_update('locales_target')
                    ->fields(array(
                      'translation' => $translation,
                    ))
                    ->condition('lid', $source_id)
                    ->condition('language', $targetLang)
                    ->execute();
                  $updates[$targetLang] = TRUE;
                }
                self::$affectedLanguages[$targetLang] = 2;
              }
            }
            /* A merge would be much simpler (and safer), but result in unnecessary db activity and misleading feedbach to user.
             * foreach ($translations as $targetLang => $translation) {
             *   db_merge('locales_target')
             *     ->key(array(
             *       'lid' => $source_id,
             *       'language' => $targetLang,
             *     ))
             *     ->fields(array(
             *       'translation' => $translation,
             *     ))
             *     ->execute();
             * }
             */
          }
          // New source.
          else {
            $source_id = db_insert('locales_source')
              ->fields(array(
                'location' => self::LOCATION,
                'source' => $source,
                'context' => $context,
              ))
              ->execute();
            foreach ($translations as $targetLang => $translation) {
              $fields = array(
                'lid' => $source_id,
                'translation' => $translation,
                'language' => $targetLang,
              );
              if ($column_l10n_status) {
                $fields['l10n_status'] = 1;
              }
              db_insert('locales_target')
                ->fields($fields)
                ->execute();
              $inserts[$targetLang] = TRUE;

              if (empty(self::$affectedLanguages[$targetLang])) {
                // 1 ~ new source + translation won't affect cache,
                // because the source doesn't exist in the cache (right ;-).
                self::$affectedLanguages[$targetLang] = 1;
              }
            }
          }
        }
        if ($deletes) {
          $messages[$title][] = t(
            'removed some empty translations (if any) for language(s): !targets',
            array('!targets' => join(', ', array_keys($deletes))),
            array('context' => 'module:localize_fields_ui')
          );
        }
        if ($updates) {
          $messages[$title][] = t(
            'updated some translations for language(s): !targets',
            array('!targets' => join(', ', array_keys($updates))),
            array('context' => 'module:localize_fields_ui')
          );
        }
        if ($inserts) {
          $messages[$title][] = t(
            'created some translations for language(s): !targets',
            array('!targets' => join(', ', array_keys($inserts))),
            array('context' => 'module:localize_fields_ui')
          );
        }
      }
    }
    if (empty($messages[$title])) {
      unset($messages[$title]);
    }

    return $messages;
  }

  /**
   * Translates, and then removes all translation fields to prevent that they get saved to database field_config/field_config_instance.
   *
   * @param array &$form_state
   */
  public static function fieldUIFieldEditFormSubmit(&$form_state) {
    // If our general info fields exist.
    if (!empty($form_state['input']['field']['localize_fields_ui'])) {
      try {
        /*
         * We have to remove all the fields added during form_alter,
         * otherwise their values get written to database field_config/field_config_instance.
         */

        $messages = array();

        $input_field =& $form_state['input']['field'];
        $values_field =& $form_state['values']['field'];

        // Get the general info.
        $general =& $values_field['localize_fields_ui'];
        $bundle = $general['bundle'];
        $field_name = $general['field_name'];
        /*
         * We don't need these two properties in current implementation.
         * self::$sourceLanguage = $general['source_language'];
         * $targetLangs = explode(',', $general['target_languages']);
         */
        unset($general); // Clear ref.

        // Shan't be saved to db.field_config_instance.
        unset($input_field['localize_fields_ui'], $values_field['localize_fields_ui']);


        // field_instance.

        $input_instance =& $form_state['input']['instance'];
        $values_instance =& $form_state['values']['instance'];

        $t_instance = t('Instance label translations', array(), array('context' => 'module:localize_fields_ui'));

        // translateItems() removes the fields added during form_alter.
        $messages[$t_instance] = self::translateItems($input_instance, $values_instance);

        // Instance settings.
        if (!empty($input_instance['settings'])) {
          $input_instance_settings =& $form_state['input']['instance']['settings'];
          $values_instance_settings =& $form_state['values']['instance']['settings'];
          // translateItems() removes the fields added during form_alter.
          $messages[$t_instance] += self::translateItems($input_instance_settings, $values_instance_settings);
          unset($input_instance_settings, $values_instance_settings); // Clear refs.
        }

        unset($input_instance, $values_instance); // Clear refs.


        // field.
        $t_field = t('Field label translations', array(), array('context' => 'module:localize_fields_ui'));

        $messages[$t_field] = array();

        // allowed_values, unless their localization turned off.
        if (empty($values_field['settings']['allowed_values_no_localization'])
          && !empty($values_field['settings']['localize_fields_ui__allowed_values'])
        ) {
          $messages[$t_field] +=
            self::translateAllowedValues(
              $values_field['settings']['localize_fields_ui__allowed_values'],
              $values_field['settings']['allowed_values']
            );
        }

        // Shan't be saved to db.field_config.
        unset(
          $input_field['settings']['localize_fields_ui__allowed_values'],
          $values_field['settings']['localize_fields_ui__allowed_values']
        );

        unset($input_field, $values_field); // Clear refs.


        // Clear locale translation cache(s) to prevent 'ghost' translations
        // in the field UI and the general translation UI.
        if (variable_get('localize_fields_ui_clear_cache', 1)) {
          if (self::$affectedLanguages['_ALL_'] == 2) {
            cache_clear_all('locale:', 'cache', TRUE);
            $messages['clear_cache'] = t('Cleared translation cache of all languages.', array(), array('context' => 'module:localize_fields_ui'));
          }
          else {
            unset(self::$affectedLanguages['_ALL_']);
            $clearedLanguages = array();
            foreach (self::$affectedLanguages as $targetLanguage => $createOrUpdate) {
              // 2 ~ existing sources/targets affected.
              if ($createOrUpdate == 2) {
                cache_clear_all('locale:' . $targetLanguage, 'cache');
                $clearedLanguages[] = $targetLanguage;
              }
            }
            $messages['clear_cache'] = t(
              'Cleared translation cache of languages: !languages.',
              array('!languages' => join(', ', $clearedLanguages)),
              array('context' => 'module:localize_fields_ui')
            );
          }
        }


        // Report changes.
        if ($messages) {
          // 0: no | 1: log only | 2: log + drupal_set_message().
          // Default to log, because it may ease debugging.
          $logChanges = variable_get('localize_fields_ui_log_changes', 1);

          if ($logChanges) {
            $nl_log = module_exists('dblog') ? '<br/>' : ' ';
            $message = $log = '';
            if (!empty($messages[$t_instance])) {
              $message .= $t_instance . ':';
              $log .= $t_instance . ' (' . t(
                  'bundle: !bundle, field: !field_name',
                  array('!bundle' => $bundle, '!field_name' => $field_name),
                  array('context' => 'module:localize_fields_ui')
                ) . '):';
              foreach ($messages[$t_instance] as $title => $lines) {
                $message .= '<br/>• ' . $title;
                $log .= $nl_log . '• ' . $title;
                foreach ($lines as $line) {
                  $message .= '<br/>- ' . $line;
                  $log .= $nl_log . '- ' . $line;
                }
              }
            }
            if (!empty($messages[$t_field])) {
              $message .= (!$message ? '' : '<br/>') . $t_field . ':';
              $log .= (!$log ? '' : $nl_log) . $t_field . ' (' . t(
                  'field: !field_name',
                  array('!field_name' => $field_name),
                  array('context' => 'module:localize_fields_ui')
                ) . '):';
              foreach ($messages[$t_field] as $title => $lines) {
                $message .= '<br/>• ' . $title;
                $log .= $nl_log . '• ' . $title;
                foreach ($lines as $line) {
                  $message .= '<br/>- ' . $line;
                  $log .= $nl_log . '- ' . $line;
                }
              }
            }
            if (!empty($messages['clear_cache'])) {
              $message .= (!$message ? '' : '<br/>') . $messages['clear_cache'];
              $log .= (!$log ? '' : $nl_log) . $messages['clear_cache'];
            }
            if ($logChanges > 1 && $message) {
              drupal_set_message($message);
            }
            if ($log) {
              watchdog(
                'localize_fields_ui',
                $log,
                array(),
                WATCHDOG_INFO
              );
            }
          }
        }
      }
      catch (Exception $xc) {
        if (module_exists('inspect') && user_access('inspect log')) {
          inspect_trace(
            $xc,
            array(
              'category' => 'localize_fields_ui',
              'message' => 'Failed to translate a field label',
              'severity' => WATCHDOG_ERROR,
            )
          );
        }
        else {
          watchdog(
            'localize_fields_ui',
            __CLASS__ . '::' . __FUNCTION__ . ': Failed to translate a field label, error: @error.',
            array('@error' => $xc->getMessage()),
            WATCHDOG_ERROR
          );
        }
        drupal_set_message(
          t(
            'Failed to translate a field label, error: @error.',
            array('@error' => $xc->getMessage()),
            array('context' => 'module:localize_fields_ui')
          )
        );
      }
    }
  }
}
