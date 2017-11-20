<?php
/**
 * @file
 *  Drupal Localize Fields module
 */


class LocalizeFields {

  /**
   * Variable 'localize_fields_usecontext' value when using translation context
   * with no non-context fallback.
   *
   * @var integer
   */
  const USE_CONTEXT = 1;

  /**
   * Variable 'localize_fields_usecontext' value when using translation context
   * and non-context as fallback.
   *
   * @var integer
   */
  const USE_CONTEXT_NONCONTEXT = 2;

  /**
   * Source language detection: use first enabled language as fallback instead
   * of English.
   *
   * Would be daft, but that may actually happen (according to this maintainer's
   * experience) if no i18n_string_source_language variable and English isn't
   * first language(?).
   *
   * @var boolean
   */
  const SOURCE_LANGUAGE_FALLBACK_FIRST_LANGUAGE = FALSE;

  /**
   * General context delimiter.
   *
   * @var string
   */
  const CONTEXT_DELIMITER = ':';

  /**
   * Context delimiter between bundle and field.
   *
   * @var string
   */
  const CONTEXT_DELIMITER_BUNDLE = '-';

  /**
   * Gets initialised by ::localize().
   *
   * @var integer
   */
  protected static $localize = -1;

  /**
   * Equivalent of conf var localize_fields_usecontext.
   *
   *  Values:
   *  0: no context
   *  1: context + fallback on no-context
   *  2: context only
   *
   * Gets initialised by ::localize().
   *
   * @var integer
   */
  protected static $useContext = -1;

  /**
   * @var string
   *
   * protected static $_userLanguage = 'en';
   */

  /**
   * @var array
   */
  protected static $entitiesRaw = array('"', "'");

  /**
   * Gets initialised by ::localize().
   *
   * @var array|NULL
   */
  protected static $entitiesEncoded;

  /**
   * Whether not to translate for the beneifit of other module's hook
   * implementations.
   *
   * Gets initialised by ::localize().
   *
   * @var boolean|integer|NULL
   */
  protected static $tentative;

  /**
   * The field_widget_form_alter sets this for the
   * preprocess_field_multiple_value_form as fallback when the latter can't
   * safely determine the (parent) entity type.
   *
   * @var string
   */
  protected static $lastKnownEntityType = '';
  /**
   * The field_widget_form_alter sets this for the
   * preprocess_field_multiple_value_form as fallback when the latter can't
   * safely determine the bundle.
   *
   * @var string
   */
  protected static $lastKnownBundle = '';

  /**
   * Establish whether we should translate labels at all.
   *
   * Also works as (very light) init method, if deciding that that label
   * translation should be done.
   *
   * @return integer
   *  Values 0|1; interprete as boolean.
   */
  public static function localize() {
    if (($localize = self::$localize) == -1) {
      $localize = 1;

      if (!empty($GLOBALS['language']->language)) {
        $userLanguage = $GLOBALS['language']->language;
      }
      // Definitely paranoid, but D7 language handling is tricky.
      elseif (!empty($GLOBALS['user']->language)) {
        $userLanguage = $GLOBALS['user']->language;
      }
      elseif (!($userLanguage = language_default('language'))) {
        $userLanguage = 'en';
      }

      // Establish source language by variable; fall back on English.
      if (!self::SOURCE_LANGUAGE_FALLBACK_FIRST_LANGUAGE) {
        $sourceLang = variable_get('i18n_string_source_language', 'en');
      }
      // Establish source language by variable; fall back on first enabled
      // language (daft, but what appears to happen if no variable).
      elseif (!($sourceLang = variable_get('i18n_string_source_language'))) {
        $languages = language_list();
        $sourceLang = '';
        // Assume that source language has to be enabled(?).
        foreach ($languages as $langCode => $props) {
          if ($props->enabled) {
            $sourceLang = $langCode;
            break;
          }
        }
      }
      if (!$sourceLang || $userLanguage == $sourceLang) {
        $localize = 0;
      }
      else {
        self::$useContext = variable_get('localize_fields_usecontext', LocalizeFields::USE_CONTEXT_NONCONTEXT);
        self::$entitiesEncoded = variable_get('localize_fields_entsencoded', array('&quot;', '&#039;'));
        self::$tentative = variable_get('localize_fields_tentative', 0);
      }
      self::$localize = $localize;
    }
    return $localize;
  }

  /**
   * Does NOT check for '' nor all-digits source - callers must do that.
   *
   * @param string $source
   * @param string $context
   * @param boolean $encoded
   * @return string
   */
  protected static function translateInternal($source, $context, $encoded = FALSE) {
    $useContext = self::$useContext;

    $translated = !$useContext ? t($source) : t($source, array(), array('context' => $context));

    if ($translated == $source) {
      if ($encoded && strpos($source, '&') !== FALSE) {
        // We do deliberately not use Drupal decode_entities() nor PHP
        // html_entity_decode(), because we want full control and only work on
        // specific entities.

        // If the label actually was encoded...
        if (($decoded = str_replace(self::$entitiesEncoded, self::$entitiesRaw, $source)) != $source) {
          if (($translated_decoded = !$useContext ? t($decoded) : t($decoded, array(), array('context' => $context))) != $source) {
            // Re-encode after translation.
            return str_replace(self::$entitiesRaw, self::$entitiesEncoded, $translated_decoded);
          }
          // Fallback on no-context.
          elseif ($useContext == self::USE_CONTEXT_NONCONTEXT && ($translated_decoded = t($decoded)) != $source) {
            // Re-encode after translation.
            return str_replace(self::$entitiesRaw, self::$entitiesEncoded, $translated_decoded);
          }
        }
        elseif ($useContext == self::USE_CONTEXT_NONCONTEXT) { // ~ Fallback on no-context.
          return t($source);
        }
      }
      elseif ($useContext == self::USE_CONTEXT_NONCONTEXT) { // ~ Fallback on no-context.
        return t($source);
      }
    }

    return $translated;
  }

  /**
   * Translates a string taking possible translation context and possible
   * encoding of single/double quotes into consideration.
   *
   * Utility method, for non-standard form manipulation.
   *
   * Check this module's help or settings page for context patterns, or use the
   * ::context() method.
   * The context argument should not be empty if this module is set to use
   * context + no non-context fallback (check settings page).
   *
   * @code
   * $label = LocalizeFields::translate(
   *   'whatever',
   *   array(),
   *   LocalizeFields::context('some_node_type', 'some_field_name', 'label')
   * );
   * @endcode
   *
   * @param string $source
   * @param array $args
   *  Ignored; args in field labels, description etc. aren't applicable (nor in
   *  core).
   * @param string $context
   *
   * @return string
   */
  public static function translate($source, $args = array(), $context = '') {
    if (($localize = self::$localize) == -1) { // Save a method call if possible.
      $localize = self::localize();
    }
    if (!$localize || !$source || ctype_digit('' . $source)) {
      return '' . $source;
    }
    // We need context if module set to use context + no non-context fallback.
    if (!$context && self::$useContext == self::USE_CONTEXT) {
      $ms = 'Needs non-empty context when module localize_fields\'s \'Use translation context\' setting is context + no non-context fallback';
      if (module_exists('inspect') && user_access('inspect log')) {
        inspect_trace(
          NULL,
          array(
            'category' => 'localize_fields',
            'message' => $ms,
            'severity' => WATCHDOG_WARNING,
          )
        );
      }
      else {
        watchdog(
          'localize_fields',
          __CLASS__ . '::' . __FUNCTION__ . ': ' . $ms . ', source[@source].',
          array('@source' => $source),
          WATCHDOG_WARNING
        );
      }

      // For what it's worth.
      return t($source);
    }

    // We don't want to bother folks with question about whether the source is
    // encoded; let's just assume it is.
    return self::translateInternal($source, $context, TRUE);
  }

  /**
   * Get translation context.
   *
   * Utility method, normally not be needed.
   *
   * @param string $bundle
   *   Empty if field base property, like allowed_values.
   * @param string $field_name
   * @param string $property
   *
   * @return string
   *   Empty if non-contextual module setting.
   */
  public static function context($bundle, $field_name, $property) {
    if (self::$localize == -1) { // Save a method call if possible.
      self::localize();
    }
    if (self::$useContext) {
      $cntxtDelim = self::CONTEXT_DELIMITER;

      // Check for field base properties (allowed_values) to rule out stupid
      // errors.
      if (!$bundle
        || $property == 'allowed_values'
      ) {
        return 'field' . $cntxtDelim . $field_name . $cntxtDelim . $property;
      }
      return 'field_instance' . $cntxtDelim . $bundle . self::CONTEXT_DELIMITER_BUNDLE . $field_name . $cntxtDelim . $property;
    }
    return '';
  }

  /**
   * Translates fields' labels, descriptions etc.
   *
   * Used by hook_field_widget_form_alter() implementation.
   *
   * Is executed right before hook_preprocess_field_multiple_value_form() and
   * before hook_form_alter().
   *
   * @param array $element
   * @param array $form_state
   * @param array &$context
   */
  public static function fieldWidgetFormAlter(&$element, &$form_state, &$context) {
    if (($localize = self::$localize) == -1) { // Save a method call if possible.
      $localize = self::localize();
    }
    if (!$localize || empty($context['field']['type'])) {
      return;
    }
    $cntxtDelim = self::CONTEXT_DELIMITER;

    // Refer original label and description - to make other module's
    // hook_field_widget_form_alter() implementations 'see' translated labels
    // (unless 'tentative').
    $sourceLabel = $sourceDescription = '';
    if (!self::$tentative) {
      if (!empty($context['instance']['label'])) {
        $sourceLabel =& $context['instance']['label'];
      }
      if (!empty($context['instance']['description'])) {
        $sourceDescription =& $context['instance']['description'];
      }
    }
    else {
      if (!empty($context['instance']['label'])) {
        $sourceLabel = $context['instance']['label'];
      }
      if (!empty($context['instance']['description'])) {
        $sourceDescription = $context['instance']['description'];
      }
    }

    $field_name = $context['field']['field_name'];
    $field_type = $context['field']['type'];

    // Set these for preprocess_field_multiple_value_form as fallbacks.
    self::$lastKnownEntityType = $context['instance']['entity_type'];
    self::$lastKnownBundle = $bundle = $context['instance']['bundle'];

    $context_field = 'field' . $cntxtDelim . $field_name . $cntxtDelim;
    $context_instance = 'field_instance' . $cntxtDelim . $bundle . self::CONTEXT_DELIMITER_BUNDLE
      . $field_name . $cntxtDelim;

    // File fields are pretty non-standard.
    $file_cardinalitySingle = FALSE;

    // These might be used more than once.
    $filtered_translated_label = $filtered_translated_description = '';

    // Find the array listing labels.
    if (array_key_exists('value', $element) && array_key_exists('#title', $element['value'])) {
      /*
       * text and number_ fields have a #title in a value bucket.
       *
       * Their single row instances' ['value']['#title'] is non-empty (and that
       * one is used in widget rendering and validation),
       * whereas any/multiple rows instances' ['value']['#title'] is empty.
       *
       * Their single row instances also #title in in root; it's usually not
       * used but let's play it safe.
       *
       * Single row instance:
       * #title: (string) >>Native title<<
       * value: (array) {
       * . #title: (string) >>Native title<<
       * }
       *
       * Any/multiple row instance:
       * value: (array) {
       * . #title: (string) >><<
       * }
       *
       * NB: sometimes single row instances have the same structure as
       * any/multiple row instance.
       * Don't really know what affects/controls the structure.
       */
      $props =& $element['value'];

      // text and number_ fields single row instances got #title in root too;
      // it's usually not used but let's play it safe.
      if (array_key_exists('#title', $element)) {
        if ($sourceLabel) {
          $element['#title'] = $filtered_translated_label = check_plain(
            $sourceLabel = self::translateInternal($sourceLabel, $context_instance . 'label', TRUE)
          );
        }
        if ($sourceDescription && array_key_exists('#description', $element)) {
          $element['#description'] = $filtered_translated_description = field_filter_xss(
            $sourceDescription = self::translateInternal($sourceDescription, $context_instance . 'description', FALSE)
          );
        }
      }
    }
    elseif (array_key_exists('#title', $element)) {
      // list_ types.
      $props =& $element;
    }
    elseif (array_key_exists(0, $element) && array_key_exists('#title', $element[0])) {
      // Single instance file has no props in $element root.
      $file_cardinalitySingle = TRUE;
      $props =& $element[0];
    }
    else {
      // Unsupported element structure.
      return;
    }

    // For some field types we translate the label/description in a non-generic
    // manner.
    $genericTranslateLabel = $genericTranslateDescription = TRUE;

    // Most field types require that we prepend a custom validate function
    // to secure translation during validation.
    $preValidate = TRUE;

    switch ($field_type) {
      // These are all covered by the general behaviour, and may be tested via
      // the localize_fields_test Features module.
      // case 'text':
      // case 'text_long':
      // case 'text_with_summary':
      // case 'taxonomy_term_reference':
      // case 'date':
      // case 'datetime':
      // case 'datestamp':
      // case 'field_collection':
      //   break;

      case 'number_integer':
      case 'number_decimal':
      case 'number_float':
        // Prefix/suffixes are not encoded in form rendering.
        if (array_key_exists('#field_prefix', $props) && ($source = $props['#field_prefix']) !== '') {
          $props['#field_prefix'] = field_filter_xss(
            self::translateInternal($source, $context_instance . 'prefix', FALSE)
          );
        }
        if (array_key_exists('#field_suffix', $props) && ($source = $props['#field_suffix']) !== '') {
          $props['#field_suffix'] = field_filter_xss(
            self::translateInternal($source, $context_instance . 'suffix', FALSE)
          );
        }
        break;

      case 'list_boolean':
      case 'list_text':
      case 'list_integer':
      case 'list_decimal':
      case 'list_float':
        // @todo: Support custom list types by switch'ing over widget type and
        // filter off auto-complete fields by their widget type (on of the text
        // widgets) leaving only 'real' list types to this algo.
        if (!empty($context['field']['settings']['allowed_values'])) {
          // Context is field name only, because options are a field_base
          // property.
          $context_options = $context_field . 'allowed_values';

          // list_boolean that uses the 'on' value as field label
          // - except when nested in a field_collection (sic!).
          if ($props['#title']
            && isset($context['instance']['widget']['settings']['display_label'])
            && !$context['instance']['widget']['settings']['display_label']
          ) {
            $genericTranslateLabel = FALSE;
            $props['#title'] = check_plain(
              // Option labels are not encoded in form rendering.
              $sourceLabel = self::translateInternal($props['#title'], $context_options, FALSE)
            );
          }

          // Translate option labels - unless flagged 'off'.
          if (empty($context['field']['settings']['allowed_values_no_localization'])
            && array_key_exists('#options', $props) && !empty($props['#options'])
          ) {
            foreach ($props['#options'] as &$label) {
              // Option labels could easily be integers. Decimals on the other
              // hand may have to be translated because of the decimal separator.
              if ($label && !ctype_digit('' . $label)) {
                $label = field_filter_xss(
                  // Option labels are not encoded in form rendering.
                  self::translateInternal($label, $context_options, FALSE)
                );
              }
            }
            unset($label); // Iteration ref.
          }
        }
        break;

      case 'file':
      case 'image':
        // Doesn't need our pre validator.
        $preValidate = FALSE;
        // Multi instance file fields have title and description on instances as
        // well as the overall field.
        // And the title of such instances are used by core field validation.
        if (!$file_cardinalitySingle) {
          $limit = 100;
          for ($i = 0; $i < $limit; ++$i) {
            if (array_key_exists($i, $element)) {
              if ($sourceLabel && array_key_exists('#title', $element[$i])) {
                $element[$i]['#title'] = $filtered_translated_label ? $filtered_translated_label :
                  ($filtered_translated_label = check_plain(
                    $sourceLabel = self::translateInternal($sourceLabel, $context_instance . 'label', TRUE)
                  ));
              }
              if ($sourceDescription && array_key_exists('#description', $element[$i])) {
                $element[$i]['#description'] = $filtered_translated_description ? $filtered_translated_description :
                  ($filtered_translated_description = field_filter_xss(
                    $sourceDescription = self::translateInternal($sourceDescription, $context_instance . 'description', FALSE)
                  ));
              }
            }
            else {
              break;
            }
          }
        }
        // Single instance (cardinality:1) file fields' #description
        // get file size and extensions info appended prior to this phase.
        elseif (array_key_exists('#description', $props) && $sourceDescription
          && ($source = $props['#description']) && strpos($source, '<br')
        ) {
          $genericTranslateDescription = FALSE;
          $a = explode('<br', $source);
          $a[0] = field_filter_xss(
            $sourceDescription = self::translateInternal($sourceDescription, $context_instance . 'description', FALSE)
          );
          $props['#description'] = join('<br', $a);
        }
        break;
      // field_collection is called 'field_collection' in this context.
    }

    // All types has a label (at least here; because of the initial process
    // of finding the right element array).
    if ($genericTranslateLabel && $sourceLabel) {
      $props['#title'] = $filtered_translated_label ? $filtered_translated_label :
        ($filtered_translated_label = check_plain(
          $sourceLabel = self::translateInternal($sourceLabel, $context_instance . 'label', TRUE)
        ));
    }

    // Most types has a description.
    if ($genericTranslateDescription && $sourceDescription && array_key_exists('#description', $props)) {
      $props['#description'] = $filtered_translated_description ? $filtered_translated_description :
        ($filtered_translated_description = field_filter_xss(
          $sourceDescription = self::translateInternal($sourceDescription, $context_instance . 'description', FALSE)
        ));
    }

    // Most types need custom validator (which only translates).
    if ($preValidate && array_key_exists('#element_validate', $props)
      && !in_array('localize_fields_pre_element_validate', $props['#element_validate'])
    ) {
      array_unshift($props['#element_validate'], 'localize_fields_pre_element_validate');
    }
  }

  /**
   * Translates instance wrapper label and description when any/more values
   * (cardinality not 1).
   *
   * Implements hook_preprocess_HOOK().
   * Implements hook_preprocess_field_multiple_value_form().
   *
   * Is executed right after hook_field_widget_form_alter().
   *
   * @see localize_fields_preprocess_field_multiple_value_form()
   *
   * @param array &$variables
   */
  public static function preprocessFieldMultipleValueForm(&$variables) {
    if (($localize = self::$localize) == -1) { // Save a method call if possible.
      $localize = self::localize();
    }
    if (!$localize) {
      return;
    }

    if (!empty($variables['element'][0])) {
      $element =& $variables['element'];

      if ((!empty($element['#title']) || !empty($element['#description']))
        && !empty($element['#field_name'])
      ) {
        $field_name = $element['#field_name'];

        // The hardest part is finding entity type and bundle.
        if (!empty($element[0]['#entity_type'])
          && !empty($element[0]['#bundle'])
        ) {
          $entity_type = $element[0]['#entity_type'];
          $bundle = $element[0]['#bundle'];
        }
        // Number fields haven't got entity type and bundle on
        // $variables['element'][0].
        elseif (!empty($element[0]['value']['#entity_type'])
          && !empty($element[0]['value']['#bundle'])
        ) {
          $entity_type = $element[0]['value']['#entity_type'];
          $bundle = $element[0]['value']['#bundle'];
        }
        else {
          unset($element); // Clear ref.
          return;
        }

        // field_collection is called 'field_collection_item' in this context.
        // field_collection_item always reports itself as bundle.
        if ($bundle == $field_name) {
          if (!empty($variables['element']['#field_parents'][0])) {
            $bundle = $variables['element']['#field_parents'][0];
          }
          // field_collection_item will also reports it's parent as itself
          // when attached directly to entity/node (not nested in another
          // field collection).
          if ($bundle == $field_name) {
            // Use the fallbacks set by the field_widget_form_alter.
            // The reason this works is that the field collection itself always
            // gets processed after it's children - thus the last field that set
            // these properties must be attached directly to the root entity/node.
            $entity_type = self::$lastKnownEntityType;
            $bundle = self::$lastKnownBundle;
          }
        }
        $instanceInfo = field_info_instance($entity_type, $field_name, $bundle);
        if ($instanceInfo) {
          $context_instance = 'field_instance' . self::CONTEXT_DELIMITER . $bundle . self::CONTEXT_DELIMITER_BUNDLE
            . $field_name. self::CONTEXT_DELIMITER;

          if (!empty($instanceInfo['label'])) {
            $element['#title'] = check_plain(
              self::translateInternal($instanceInfo['label'], $context_instance . 'label', TRUE)
            );
          }
          if (!empty($instanceInfo['description'])) {
            $element['#description'] = field_filter_xss(
              self::translateInternal($instanceInfo['description'], $context_instance . 'description', FALSE)
            );
          }
        }
        // 'Add another item' button label, if multi-cardinal.
        if (!empty($element['add_more']['#value'])) {
          $fieldInfo = field_info_field($field_name);
          if ($fieldInfo && !empty($fieldInfo['settings']['add_row_localization_source'])) {
            $element['add_more']['#value'] = field_filter_xss(
              self::translateInternal(
                $fieldInfo['settings']['add_row_localization_source'],
                'field' . self::CONTEXT_DELIMITER  . $field_name . self::CONTEXT_DELIMITER . 'add_row',
                FALSE
              )
            );
          }
        }
      }
      unset($element); // Clear ref.
    }
    // There's another description in $variables['element'][0]['#description']
    // but haven't found a field type that gets that one rendered.
  }

  /**
   * Translates Date fields' 'Field-name Start date' and 'Field-name End date'
   * labels.
   *
   * Used by hook_field_date_combo_process_alter() implementation.
   *
   * @param array &$element
   */
  public static function dateComboProcessAlter(&$element) {
    if (($localize = self::$localize) == -1) { // Save a method call if possible.
      $localize = self::localize();
    }
    if (!$localize) {
      return;
    }

    // The field label is already translated in another place - in the root of
    // $element.
    $filtered_translated_label = $element['#title'];

    $items = array('value', 'value2');
    foreach ($items as $item) {
      if (array_key_exists($item, $element)) {
        // ['value']['#instance']['label']
        if (array_key_exists('#instance', $element[$item]) && array_key_exists('label', $element[$item]['#instance'])
          && ($source = $element[$item]['#instance']['label'])
        ) {
          // The label on the row is not translated yet.
          $element[$item]['#instance']['label'] = $filtered_translated_label;

          // ['value']['#date_title'] is label + 'start date'|'end date'
          if (array_key_exists('#date_title', $element[$item])
            && ($item_label = $element[$item]['#date_title']) && strpos($item_label, $source) !== FALSE
          ) {
            $element[$item]['#date_title'] = field_filter_xss(
              str_replace($source, $filtered_translated_label, $item_label)
            );
          }
        }
      }
    }
  }

  /**
   * Custom element validator which performs no validation but translates the
   * labels used in element validation by field types having an
   * #element_validate function.
   *
   *  Examples of #element_validate implementations:
   *  - number: number_field_widget_validate()
   *  - date: date_combo_validate()
   *
   * NB: number_field_widget_validate() checks for invalid chars.
   *
   * Does not translate the instance' description.
   *
   * For Date fields, Implementing hook_date_combo_pre_validate_alter() would
   * _seem_ the right way to do this.
   * But date_combo_validate() fetches instance properties (like labels)
   * _before_ invoking the date_combo_pre_validate_alter hook.
   * Thus changes in a hook_date_combo_pre_validate_alter() would have no effect.
   *
   * Attaching this validator is another challenge, Date disregards for instance
   * implementations of hook_element_info_alter();
   * Date simply overrides (resets) the info in date_field_widget_form().
   * So this custom validator is attached (prepended) in our
   * hook_field_widget_form_alter() implementation instead.
   *
   * @see number_field_widget_validate()
   *
   * @param array $element
   * @param array &$form_state
   */
  public static function preElementValidate($element, &$form_state) {
    if (($localize = self::$localize) == -1) { // Save a method call if possible.
      $localize = self::localize();
    }
    if (!$localize) {
      return;
    }

    // Non-standard field types may have weird structure - let's not break
    // things further.
    if (!isset($element['#field_parents']) || empty($element['#field_name']) || empty($element['#language'])) {
      return;
    }
    $field_name = $element['#field_name'];

    // Change the element by changing its' properties in $form_state.
    $field_state = field_form_get_state($element['#field_parents'], $field_name, $element['#language'], $form_state);

    if (array_key_exists('instance', $field_state) && array_key_exists('label', $field_state['instance'])
      && ($source = $field_state['instance']['label'])
    ) {
      $cntxtDelim = self::CONTEXT_DELIMITER;

      // Not escaped with check_plain() due to double encoding.
      $field_state['instance']['label'] = self::translateInternal(
        $source,
        'field_instance' . $cntxtDelim . $element['#bundle'] . self::CONTEXT_DELIMITER_BUNDLE . $field_name . $cntxtDelim . 'label',
        TRUE
      );

      field_form_set_state($element['#field_parents'], $field_name, $element['#language'], $form_state, $field_state);
    }
  }

  /**
   * Translates error messages created by implementations of
   * hook_field_validate().
   *
   * Also corrects decimal separator in decimals and floats.
   *
   * NB: number_field_validate() checks min/max.
   *
   * See https://drupal.org/node/1283718.
   *
   * Used by hook_field_attach_validate() implementation.
   *
   *
   * @see number_field_validate()
   *
   * @param array $entity
   * @param array &$errors
   */
  public static function fieldAttachValidate($entity, &$errors) {
    if (($localize = self::$localize) == -1) { // Save a method call if possible.
      $localize = self::localize();
    }
    if (!$localize) {
      return;
    }
    $cntxtDelim = self::CONTEXT_DELIMITER;

    $context_instance = '';
    // Find bundle.
    if (!empty($entity->form_id) && !empty($entity->type) && empty($entity->field_name)) {
      $context = 'field_instance' . $cntxtDelim . $entity->type . self::CONTEXT_DELIMITER_BUNDLE;
    }
    elseif (!empty($entity->field_name)) {
      // Bundle is (field_collection) field_name.
      $context = 'field_instance' . $cntxtDelim . $entity->field_name . self::CONTEXT_DELIMITER_BUNDLE;
    }
    else {
      // Awful.
      if (module_exists('inspect') && user_access('inspect log')) {
        inspect(
          array(
            'entity' => $entity,
            'errors' => $errors,
          ),
          array(
            'depth' => 2,
            'category' => 'localize_fields',
            'message' => 'Can\'t find bundle equiv. property of entity',
            'severity' => WATCHDOG_WARNING,
          )
        );
      }
      else {
        watchdog(
          'localize_fields',
          __CLASS__ . '::' . __FUNCTION__ . ': Can\'t find bundle equiv. property of entity, erring field names: @field_names.',
          array('@field_names' => array_keys($errors)),
          WATCHDOG_WARNING
        );
      }

      return;
    }

    $lenPlaceholderStart = strlen($placeholderStart = '<em class="placeholder">');
    $lenPlaceholderEnd = strlen($placeholderEnd = '</em>');

    // $errors['some_field_name']['und'][0][0]['message']
    foreach ($errors as $field_name => $errors_byValueLanguage) {
      if ($context) {
        $context_instance = $context . $field_name . $cntxtDelim . 'label';
      }

      $decimal_separator = NULL;

      foreach ($errors_byValueLanguage as $language => $errors_byInstance) {
        foreach ($errors_byInstance as $instance => $errorList) {
          foreach ($errorList as $index => $error) {
            // error [
            //   'error': 'number_min',
            //   'message': '<em class="placeholder">The field label</em>: the value may be no less than <em class="placeholder">0.01</em>.'
            // ]
            if (!empty($error['message'])) {
              $message = $error['message'];
              // Do it thrice, because there may be more placeholders.
              for ($i = 0; $i < 3; ++$i) {
                if (($start = strpos($message, $placeholderStart)) !== FALSE && ($end = strpos($message, $placeholderEnd))) {
                  $start += $lenPlaceholderStart;
                  $msStart = str_replace($placeholderStart, '!PLACEHOLDER', substr($message, 0, $start));
                  $ms = substr($message, $start, $end - $start);
                  // Replace decimal separator...
                  if (is_numeric($ms)) {
                    if (strpos($ms, '.') !== FALSE) {
                      if (!$decimal_separator) {
                        $field_settings = field_info_field($field_name);
                        $decimal_separator = !empty($field_settings['settings']['decimal_separator']) ?
                          $field_settings['settings']['decimal_separator'] : '.';
                        unset($field_settings);
                      }
                      if ($decimal_separator != '.') {
                        $ms = str_replace('.', $decimal_separator, $ms);
                      }
                    }
                  }
                  // ...translate.
                  else {
                    // Not escaped with check_plain() due to double encoding.
                    $ms = self::translateInternal($ms, $context_instance, TRUE);
                  }
                  $message = $msStart
                    . $ms
                    . str_replace($placeholderEnd, '!_PLACEHOLDER', substr($message, $end, $lenPlaceholderEnd))
                    . substr($message, $end + $lenPlaceholderEnd);
                }
              }
              $message = str_replace(array('!PLACEHOLDER', '!_PLACEHOLDER'), array($placeholderStart, $placeholderEnd), $message);
              $errors[$field_name][$language][$instance][$index]['message'] = $message;
            }
          }
        }
      }
    }
  }

  /**
   * Translates field view labels, and corrects decimal separator of
   * decimals/floats.
   *
   * Used by hook_field_attach_view_alter() implementation.
   *
   * @param array &$output
   * @param array $context
   */
  public static function fieldAttachViewAlter(&$output, $context) {
    if (($localize = self::$localize) == -1) { // Save a method call if possible.
      $localize = self::localize();
    }
    if (!$localize) {
      return;
    }
    $cntxtDelim = self::CONTEXT_DELIMITER;

    // Find entity type, for field_info_instance() look-ups.
    if (!empty($context['entity_type'])) {
      $entity_type = $context['entity_type'];
    }
    elseif (!empty($output['#entity_type'])) {
      $entity_type = $output['#entity_type'];
    }
    else {
      // Abort if only partially implemented custom entity type which fails to
      // provide basic info.
      return;
    }

    // Find bundle, for translation context and field_info_instance() look-ups.
    $bundle = NULL;
    if (!empty($context['entity']) && is_object($context['entity'])) {
      // If entity type: field_collection_item.
      // Try field_name before type, because a misleading type could exist.
      if (!empty($context['entity']->field_name)) {
        $bundle = $context['entity']->field_name;
      }
      // If node etc.
      elseif (!empty($context['entity']->type)) {
        $bundle = $context['entity']->type;
      }
    }
    if (!$bundle) {
      if (!empty($output['#bundle'])) {
        $bundle = $output['#bundle'];
      }
      else {
        // Abort if only partially implemented custom entity type which fails to
        // provide basic info.
        return;
      }
    }
    // The bundle found may be array in a view.
    if (!is_string($bundle)) {
      return;
    }

    $context = 'field_instance' . $cntxtDelim . $bundle . self::CONTEXT_DELIMITER_BUNDLE;

    foreach ($output as $field_name => &$field) {
      if (is_array($field) && !empty($field['#field_type'])) {
        $context_instance = $context . $field_name . $cntxtDelim;
        if (!empty($field['#title'])) {
          // Not escaped with check_plain() due to double encoding.
          $field['#title'] = self::translateInternal($field['#title'], $context_instance . 'label', TRUE);
        }
        switch ($field['#field_type']) {
          case 'list_boolean':
          case 'list_text':
          case 'list_integer':
          case 'list_decimal':
          case 'list_float':
            // Translate option labels.
            // Is a field_base property.
            $fieldInfo = field_info_field($field_name);
            $translateOptions = empty($fieldInfo['settings']['allowed_values_no_localization']);
            unset($fieldInfo);
            if ($translateOptions) {
              $context_options = 'field' . $cntxtDelim . $field_name . $cntxtDelim . 'allowed_values';
              $limit = 1000;
              for ($i = 0; $i < $limit; ++$i) {
                if (array_key_exists($i, $field)) {
                  // Options could easily be integers. Decimals on the other
                  // hand may have to be translated because of the decimal
                  // separator.
                  if (!empty($field[$i]['#markup']) && !ctype_digit($markup = '' . $field[$i]['#markup'])) {
                    // Option labels are not encoded when markup.
                    // Not escaped with field_filter_xss() due to double encoding.
                    $field[$i]['#markup'] = self::translateInternal($markup, $context_options, FALSE);
                  }
                }
                else {
                  break; // Iter.
                }
              }
            }
            break; // Switch.
          case 'number_integer':
            // Translate prefix and/or suffix.
            $firstRow = TRUE;
            $prefixLength = $suffixLength = 0;
            $prefix = $suffix = '';
            $limit = 100;
            for ($i = 0; $i < $limit; ++$i) {
              if (array_key_exists($i, $field) && !empty($field[$i]['#markup'])) {
                if ($firstRow) {
                  $firstRow = FALSE;
                  if (!is_numeric($markup = $field[$i]['#markup'])) {
                    $instanceInfo = field_info_instance($entity_type, $field_name, $bundle);
                    if (($prefix = empty($instanceInfo['settings']['prefix']) ? '' : $instanceInfo['settings']['prefix'])) {
                      $prefixLength = strlen($prefix);
                      // Not escaped with field_filter_xss() due to double encoding.
                      $prefix = self::translateInternal($prefix, $context_instance . 'prefix', FALSE);
                    }
                    if (($suffix = empty($instanceInfo['settings']['suffix']) ? '' : $instanceInfo['settings']['suffix'])) {
                      $suffixLength = strlen($suffix);
                      // Not escaped with field_filter_xss() due to double encoding.
                      $suffix = self::translateInternal($suffix, $context_instance . 'suffix', FALSE);
                    }
                    unset($instanceInfo);
                    if ($prefixLength || $suffixLength) {
                      $field[$i]['#markup'] = $prefix . substr($markup, $prefixLength, strlen($markup) - ($prefixLength + $suffixLength)) . $suffix;
                    }
                    else {
                      // Don't work on any row. An error really, because the
                      // markup content should be numeric if no prefix or suffix.
                      break; // Iter.
                    }
                  }
                  else {
                    // No prefix or suffix: nothing to do.
                    break; // Iter.
                  }
                }
                // Won't get here unless there's a prefix or suffix.
                else {
                  $markup = $field[$i]['#markup'];
                  $field[$i]['#markup'] = $prefix . substr($markup, $prefixLength, strlen($markup) - ($prefixLength + $suffixLength)) . $suffix;
                }
              }
              else {
                // No more rows, or definitely no prefix/suffix.
                break; // Iter.
              }
            }
            break; // Switch.
          case 'number_decimal':
          case 'number_float':
            // Replace decimal separator if not dot.
            $fieldInfo = field_info_field($field_name);
            $decimal_separator = !empty($fieldInfo['settings']['decimal_separator']) ? $fieldInfo['settings']['decimal_separator'] : '.';
            unset($fieldInfo);
            // Translate prefix and/or suffix.
            $firstRow = TRUE;
            $prefixLength = $suffixLength = 0;
            $prefix = $suffix = '';
            $limit = 100;
            for ($i = 0; $i < $limit; ++$i) {
              if (array_key_exists($i, $field) && array_key_exists('#markup', $field[$i])) {
                // Do this only once.
                if ($firstRow) {
                  $firstRow = FALSE;
                  if (!is_numeric($markup = $field[$i]['#markup'])) {
                    $instanceInfo = field_info_instance($entity_type, $field_name, $bundle);
                    if (($prefix = empty($instanceInfo['settings']['prefix']) ? '' : $instanceInfo['settings']['prefix'])) {
                      $prefixLength = strlen($prefix);
                      // Not escaped with field_filter_xss() due to double encoding.
                      $prefix = self::translateInternal($prefix, $context_instance . 'prefix', FALSE);
                    }
                    if (($suffix = empty($instanceInfo['settings']['suffix']) ? '' : $instanceInfo['settings']['suffix'])) {
                      $suffixLength = strlen($suffix);
                      // Not escaped with field_filter_xss() due to double encoding.
                      $suffix = self::translateInternal($suffix, $context_instance . 'suffix', FALSE);
                    }
                    unset($instanceInfo);
                    if ($prefixLength || $suffixLength) {
                      $value = substr($markup, $prefixLength, strlen($markup) - ($prefixLength + $suffixLength));
                      if ($decimal_separator != '.') {
                        $value = str_replace('.', $decimal_separator, $value);
                      }
                      $field[$i]['#markup'] = $prefix . $value . $suffix;
                    }
                    elseif ($decimal_separator != '.') {
                      $field[$i]['#markup'] = str_replace('.', $decimal_separator, $markup);
                    }
                    else {
                      // Nothing to do for any row.
                      break; // Iter.
                    }
                  }
                  elseif ($decimal_separator != '.') {
                    $field[$i]['#markup'] = str_replace('.', $decimal_separator, $markup);
                  }
                  else {
                    // Nothing to do for any row.
                    break; // Iter.
                  }
                }
                // Won't get here unless there's a prefix or suffix, or decimal
                // separator must be fixed.
                else {
                  $markup = $field[$i]['#markup'];
                  if ($prefixLength || $suffixLength) {
                    $value = substr($markup, $prefixLength, strlen($markup) - ($prefixLength + $suffixLength));
                    if ($decimal_separator != '.') {
                      $value = str_replace('.', $decimal_separator, $value);
                    }
                    $field[$i]['#markup'] = $prefix . $value . $suffix;
                  }
                  else {
                    $field[$i]['#markup'] = str_replace('.', $decimal_separator, $markup);
                  }
                }
              }
              else {
                // No more rows, or a row misses #markup bucket (then an error).
                break; // Iter.
              }
            }
            break; // Switch.
          case 'field_collection':
          default:
            // Multi-value'd field_collection displays description.
            if (!empty($field['#suffix']) && strpos($field['#suffix'], 'field-collection-description')) {
              $matches = array();
              $pattern = '/(<div[^>]+field\-collection\-description[^>]+>)([^<]+)(<\/div>)/';
              preg_match($pattern, $field['#suffix'], $matches);
              if ($matches && !empty($matches[3])
                && ($instanceInfo = field_info_instance($entity_type, $field_name, $bundle))
                && !empty($instanceInfo['description'])
              ) {
                // Not escaped with field_filter_xss() due to double encoding.
                $translatedDescription = self::translateInternal($instanceInfo['description'], $context_instance . 'description', FALSE);
                if ($translatedDescription != $instanceInfo['description']) {
                  $field['#suffix'] = preg_replace($pattern, '$1' . $translatedDescription . '$3', $field['#suffix']);
                }
              }
              unset($matches);
            }
            break;
        }
      }
    }
    unset($field); // Iteration ref
  }

}
