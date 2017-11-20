<?php
/**
 * @file
 *  Drupal Localize Fields module
 */

/**
 * Implementation of hook_drush_command().
 *
 * @return array
 */
function localize_fields_drush_command() {
  $items = array(
    'localize-fields' => array(
      'description' => 'Makes all labels etc. of Features modules\' field and field_group files below arg path translatable, optionally using translation contexts to prevent translation mix-ups.',
      'arguments' => array(
        'path' => 'Path to ancestor directory of the Features modules\' files to convert.',
      ),
      'options' => array(
        'test' => 'Features modules\' files won\'t be overwritten but instead copied to private files dir, and database changes will be simulated.',
        'usecontext' => 'Override the site\'s \'Use translation context\' settings (check /admin/config/regional/localize_fields).',
        'removeempty' => 'Remove translation sources having same source text as a field (but no translation) when there actually exists a non-empty translation. Risky if some translation deliberately is empty.',
      ),
      'examples' => array(
        'drush localize-fields sites/all/modules/custom --test --usecontext --removeempty' => ' ',
      ),
      'aliases' => array(),
    )
  );
  // Make this function usable in non-drush context.
  if (defined('DRUSH_BOOTSTRAP_DRUPAL_FULL')) {
    $items['localize-fields']['bootstrap'] = DRUSH_BOOTSTRAP_DRUPAL_FULL;
  }

  return $items;
}

/**
 * @param string $path
 */
function drush_localize_fields($path = '') {
  $success = TRUE;
  $overwrite = FALSE;

  drush_print(' ');

  // Get context delimiter.
  if (!class_exists('LocalizeFields')) {
    if (!file_exists('LocalizeFields.inc')) {
      drush_log(dt('Can\'t find class !class nor file !file.', array('!class' => 'LocalizeFields', '!file' => 'LocalizeFields.inc')), 'error');
      return;
    }
    require('LocalizeFields.inc');
    if (!class_exists('LocalizeFields')) {
      drush_log(dt('Can\'t find file !file.', array('!file' => 'LocalizeFields.inc')), 'error');
      return;
    }
  }
  $cntxtDelim = LocalizeFields::CONTEXT_DELIMITER;

  if (!module_exists('locale')) {
    drush_log(dt('The locale module must be installed.'), 'error');
    return;
  }

  $test = drush_get_option('test', FALSE);
  if ($test) {
    drush_print(dt('In test mode') . ':', 2);
    drush_print(dt('- converted copies of the Features files will be written to private://drush/localize_fields'), 2);
    drush_print(dt('- all database changes are simulations') . "\n", 2);
  }
  else {
    $overwrite = TRUE;
  }

  $output_dir = '';
  if (!$overwrite) {
    // Set up output dir, if it doesnt exist.
    if (!drupal_strlen($output_dir = variable_get('file_private_path', ''))) {
      drush_log(dt('Private files directory not defined, check variable file_private_path, or in GUI: /admin/config/media/file-system'), 'error');
      return;
    }
    if (!is_dir($output_dir .= '/drush/localize_fields') && !mkdir($output_dir, 0775, TRUE)) {
      drush_log(dt('Output dir [!dir] doesnt exist and cannot be created.', array('!dir' => $output_dir)), 'error');
      return;
    }
  }

  // Establish and check path to find Features files in.
  $dir = $path;
  $document_root = DRUPAL_ROOT;
  $cli_working_dir = !empty($_SERVER['PWD']) ? $_SERVER['PWD'] : '';
  if (!($os_nix = DIRECTORY_SEPARATOR == '/')) {
    // Replace Windows directory separators.
    $dir = str_replace('\\', '/', $dir);
    $document_root = str_replace('\\', '/', $document_root);
    $cli_working_dir = str_replace('\\', '/', $cli_working_dir);
  }
  // Remove trailing slash.
  if ($dir{strlen($dir) - 1} == '/') {
    $dir = substr($dir, 0, strlen($dir) - 1);
  }
  // Absolute?
  if ($dir{0} === '/' || (!$os_nix && preg_match('/^[a-zA-Z]:\//', $dir))) {
    if (!file_exists($dir)) {
      drush_log(dt('Bad path argument, that absolute dir doesnt exist - saw path[' . $dir . '].'), 'error');
      return;
    }
  }
  // Relative.
  else {
    if (!($resolved = realpath($cli_working_dir . '/' . $dir))) {
      drush_log(dt('Bad path argument, that relative dir doesnt exist - saw path[' . $dir . '].'), 'error');
      return;
    }
    $dir = $os_nix ? $resolved : str_replace('\\', '/', $resolved);
  }
  // Working outside current site's document root is forbidden.
  if (stripos($dir, $document_root . '/') !== 0) {
    drush_log(dt('This script is not allowed to work outside current site\'s document root - saw path[' . $dir . '].'), 'error');
    return;
  }
  if (!is_dir($dir)) {
    drush_log(dt('Bad path argument, that file isnt a directory - saw path[' . $dir . '].'), 'error');
    return;
  }
  drush_log(dt('Will work in dir and sub dirs of: !dir', array('!dir' => $dir)), 'status');

  $use_context = drush_get_option('usecontext', 'nully');
  $remove_empty = FALSE;
  if ($use_context === 'nully') {
    $use_context = variable_get('localize_fields_usecontext', LocalizeFields::USE_CONTEXT_NONCONTEXT);
  }
  if ($use_context) {
    drush_log(dt('Will use translation context - t()s will get context argument.'), 'status');
  }
  else {
    drush_log(dt('Will NOT use translation context. You may override by using the --usecontext option.'), 'warning');

    if (!($remove_empty = drush_get_option('removeempty', 0))) {
      drush_log(dt('And will NOT remove possibly overshadowing sources that equals fields\' sources, but have no translations. You may override by using the --removeempty option.'), 'status');
    }
    else {
      drush_log(dt('However - will remove possibly overshadowing sources that equals fields\' sources, but have no translations.'), 'status');
    }

    if (!drush_confirm(dt('Do you really want to continue, without translation context?'))) {
      drush_log(dt('Aborting.'));
    }
  }

  // Escaping.
  $escape_needles = array("\n", "'");
  $escape_substitutes = array('\\n', '\\\'');

  // Find all the Features files under path.
  // Details:
  // - skip .features.inc (the content type file): Features automatically insert t()s directly around the sentences, and it translation works.
  // - .field_group.inc: Find label and description, and add them t()'d to bottom of file (we don't translate field_group).
  // - .features.field_base.inc: Find list_ type options, and add them t()'d to bottom of file.
  // - .features.field_instance.inc: Find number_ type prefix/suffix, and add them t()'d to bottom of file.

  //  Find all the features files under path.
  $list = array();
  _localize_fields_list_files($list, $dir);
  if (!$list) {
    drush_log(dt('Aborted: Found no .features.field_base.inc, .features.field_instance.inc, .field_group.inc, .features.field_group.inc files.'), 'warning');
    return;
  }

  drush_print(' ');
  drush_print('Will update database tables locales_source and locales_target.');
  drush_print('A list of database changes will be logged to watchdog.');
  drush_print(' ');
  // List files for confirmation.
  $filenames = array_keys($list);
  $confirm_list = array();
  $current_module = '_impossible_.';
  $index_modules = -1;
  foreach ($filenames as $filename) {
    if (strpos($filename, $current_module) !== 0) {
      $current_module = substr($filename, 0, strpos($filename, '.')) . '.';
      $confirm_list[(++$index_modules)] = $filename;
    }
    else {
      $confirm_list[$index_modules] .= ' ..' . substr($filename, strpos($filename, '.'));
    }
  }
  unset($filenames);
  drush_print(dt('Will work on these files:'));
  foreach ($confirm_list as $filenames) {
    drush_print($filenames, 2);
  }
  drush_print(' ');

  if (!$test) {
    if (!drush_confirm(dt('Do you really want to continue?'))) {
      drush_log(dt('Aborting.'));
      return;
    }
    drush_print(' ');
  }
  else {
    drush_print(dt('Do you really want to continue?'));
    drush_print(dt('- Aye, it\'s just a test...' . "\n"));
  }

  // Use db.locales_target.l10n_status column if it exists.
  $column_l10n_status = module_exists('features_translations');

  $no_work_files = array();
  $identical_files = array();
  $work_files = array();
  $files_completed = array();

  $inspections = array();

  try {
    foreach ($list as $filename => $path) {
      // Find type.
      if (strpos($filename, '.field_base.inc')) {
        $type = 'field_base';
      }
      elseif (strpos($filename, '.field_instance.inc')) {
        $type = 'field_instance';
      }
      elseif (strpos($filename, '.field_group.inc')) {
        $type = 'field_group';
      }
      else {
        drush_log(dt('Unsupported Features file[' . $path . '].'), 'error');
        break;
      }

      // Read file and get rid of carriage returns.
      $original = file_get_contents($path);
      $output = str_replace("\r", '', $original);

      // Find first function.
      $matches = array();
      if (!preg_match('/\nfunction\ ?([a-z\d\_]+)[\ \(]/', $output, $matches) || empty($matches[1])) {
        drush_log(dt('Cant find any function in file[' . $path . '].'), 'error');
        return;
      }
      $function = $matches[1];

      // Find sources.
      switch ($type) {
        case 'field_base':
          $sources = _localize_fields_type_field_base($path, $function);
          break;
        case 'field_instance':
          $sources = _localize_fields_type_field_instance($path, $function);
          break;
        case 'field_group':
          $sources = _localize_fields_type_field_group($path, $function);
          break;
        default:
          drush_log(dt('Unsupported Features file type[' . $type . '].'), 'error');
          return;
      }

      if ($sources) {
        $ts = array();
        $sources_distinct = array();
        $sources_to_db = array();
        foreach ($sources as $props) {
          // NB: field_group items have no context.
          $context = $props['context'];
          foreach ($props['sources'] as $key => $src) {
            if (is_array($src)) {
              // List options.
              foreach ($src as $item) {
                // We don't translate integers, whereas decimals may have to be translated because of the decimal separator.
                if ($item && !ctype_digit('' . $item)) {
                  $source = str_replace($escape_needles, $escape_substitutes, $item);
                  // Don't update in db if no context at all (field_group).
                  if ($context) {
                    $sources_distinct[] = $source;
                    $sources_to_db[] = array($source, !$context ? '' : $context . $cntxtDelim . $key);
                  }
                  $ts[] = 't' . "('" . $source . "'"
                    . (!$use_context || !$context ? '' : (", array(), array('context' => '" . $context . $cntxtDelim . $key . "')")) . ');';
                }
              }
            }
            elseif ($src && !ctype_digit('' . $src)) {
              $source = str_replace($escape_needles, $escape_substitutes, $src);
              // Don't update in db if no context at all (field_group).
              if ($context) {
                $sources_distinct[] = $source;
                $sources_to_db[] = array($source, !$context ? '' : $context . $cntxtDelim . $key);
              }
              $ts[] = 't' . "('" . $source . "'"
                . (!$use_context || !$context ? '' : (", array(), array('context' => '" . $context . $cntxtDelim . $key . "')")) . ');';
            }
          }
        }

        // DB operations.
        // Not using context: remove context, if/when matching sources with matching context exist.
        // Using context: clone a source + target and add context to source (and user must clean up afterwards using the Potx module).
        // Location is unreliable, so we don't search by that.
        if ($sources_to_db) {
          $existing_sources = db_select('locales_source', 'src')
            ->fields('src', array('lid', 'location', 'source', 'context'))
            ->condition('textgroup', 'default')
            ->condition('source', $sources_distinct, 'IN')
            ->orderBy('source')
            // Context ascending, for the sake of usecontext + no match.
            ->orderBy('context')
            ->execute()
            ->fetchAllAssoc('lid');

          if ($existing_sources) {
            $inspections[] = 'Sources exist in database for file: ' . $filename . '.';

            $existing_source_ids = array_keys($existing_sources);
            // Using context, or remove possibly overshadowing empty sources: we need the targets too.
            $existing_targets = array(); // IDE.
            if ($use_context || $remove_empty) {
              $existing_targets = db_select('locales_target', 'trg')
                ->fields('trg', array('lid', 'translation', 'language'))
                ->condition('lid', $existing_source_ids, 'IN')
                ->condition('plural', 0)
                ->execute()
                ->fetchAll();
              if ($existing_targets) {
                $inspections[] = '...and targets exist.';
              }
            }

            // Make a copy of db sources that is searchable by source.
            $existing_sources_search = array();
            foreach ($existing_sources as $source_id => $props) {
              $existing_sources_search[$source_id] = $props->source;
            }

            foreach ($sources_to_db as $src_cntxt) {
              $source = $src_cntxt[0];
              $context = $src_cntxt[1];

              // There may be more db sources matching a source, if context was used previously.
              $matching_source_ids = array();
              $match_found = FALSE;

              if (($source_id = array_search($source, $existing_sources_search, TRUE))) {
                // Find all db sources that match source.
                $copy_sources_search = $existing_sources_search;
                $matching_source_ids[] = $source_id;
                unset($copy_sources_search[$source_id]);
                while(($source_id = array_search($source, $copy_sources_search, TRUE))) {
                  $matching_source_ids[] = $source_id;
                  unset($copy_sources_search[$source_id]);
                }
                foreach ($matching_source_ids as $source_id) {
                  if ($existing_sources[$source_id]->context === $context) {
                    $match_found = $source_id; // Save it for !$use_context && $remove_empty.
                    if (!$use_context) {
                      // Remove context.
                      if (!$test) {
                        db_update('locales_source')
                          ->fields(array(
                            'context' => '',
                          ))
                          ->condition('lid', $source_id, '=')
                          ->execute();
                      }
                      $inspections[] = '- updated (cleared) context of db source: context [' . $context . '], source >>' . $source . '<<.';
                    }
                    else {
                      // Use context: found a match, no more work to do, continue to next source.
                      continue 2;
                    }
                    break;
                  }
                }
                // Get rid of overshadowing empty translations.
                if ($remove_empty) {
                  foreach ($matching_source_ids as $source_id) {
                    if ((!$match_found || ($source_id != $match_found))
                      // Empty context, and location indicating a t() that was found on-the-fly (not pre-declared in code source of core or a module).
                      && $existing_sources[$source_id]->context === ''
                      && $existing_sources[$source_id]->location !== ''
                      && $existing_sources[$source_id]->location{0} == '/' // A url.
                    ) {
                      $removable_source = TRUE;
                      foreach ($existing_targets as $props) {
                        // A translation exists, thus we can't remove source.
                        if ($props->lid == $source_id && $props->translation !== '') {
                          $removable_source = FALSE;
                          break;
                        }
                      }
                      if ($removable_source) {
                        if (!$test) {
                          db_delete('locales_source')
                            ->condition('lid', $source_id, '=')
                            ->execute();
                        }
                        $inspections[] = '- deleted possibly overshadowing (no translation) for db source: context [' . $context . '], source >>' . $source . '<<.';
                      }

                      // There may actually be more than one (sic!).
                    }
                  }
                }
                // Set context on existing translation.
                elseif (!$match_found
                  && $use_context
                ) {
                  // Find first having same location (file only, disregarding line number), and having only one location.
                  foreach ($matching_source_ids as $source_id) {
                    if ($existing_sources[$source_id]->context === ''
                      && strpos($existing_sources[$source_id]->location, $filename . ':') === 0
                      && strpos($existing_sources[$source_id]->location, ' ') === FALSE
                    ) {
                      $match_found = TRUE;
                      // Set context.
                      if (!$test) {
                        db_update('locales_source')
                          ->fields(array(
                            'context' => $context,
                          ))
                          ->condition('lid', $source_id, '=')
                          ->execute();
                      }
                      $inspections[] = '- updated (set) context of db source: context [' . $context . '], source >>' . $source . '<<.';

                      // We only do this once.
                      break;
                    }
                  }
                  if (!$match_found) {
                    // Find the first having a translation, and preferring empty context (see $existing_targets orderBy('context') ascending).
                    foreach ($matching_source_ids as $source_id) {
                      // Check if there's any targets at all.
                      $any_matching_targets = FALSE;
                      foreach ($existing_targets as $props) {
                        if ($props->lid == $source_id && $props->translation !== '') {
                          $any_matching_targets = TRUE;
                          break;
                        }
                      }
                      if ($any_matching_targets) {
                        // Insert dupe source, that has context.
                        $new_source_id = ''; // IDE.
                        if (!$test) {
                          $new_source_id = db_insert('locales_source')
                            ->fields(array(
                              'location' => $filename . ':0',
                              'source' => $source,
                              'context' => $context,
                            ))
                            ->execute();
                        }
                        $inspections[] = '- new source: context [' . $context . '], source >>' . $source . '<<.';
                        // Insert dupe targets, for every language
                        foreach ($existing_targets as $props) {
                          if ($props->lid == $source_id && $props->translation !== '') {
                            if (!$test) {
                              $fields = array(
                                'lid' => $new_source_id,
                                'translation' => $props->translation,
                                'language' => $props->language,
                              );
                              if ($column_l10n_status) {
                                $fields['l10n_status'] = 1;
                              }
                              db_insert('locales_target')
                                ->fields($fields)
                                ->execute();
                            }
                            $inspections[] = '- new (cloned) target: language [' . $props->language . '], source >>' . $props->translation . '<<.';
                          }
                        }

                        break;
                      }
                    }
                  }
                }
              }
            }
          }
          else {
            // Do nothing.
            $inspections[] = 'No sources exist in database for file: ' . $filename . '.';
          }
        }

        // Filing.
        if ($ts) {
          $comment = '// Translatables created/updated by the Localize Fields (localize_fields) module.';
          array_unshift($ts, $comment);
          // Remove this module's comment.
          $needle = '/\n\n?\ *' . preg_quote($comment, '/') . '/'; // Double? \n fixes that our lines tend to move down one line for every file write.
          if (preg_match($needle, $output)) {
            $output = preg_replace($needle, '', $output);
          }
          // Remove existing t()'s at end of file.
          $needle = '/\n\ *t\(\'.+\'\)?\);/ms'; // Multiline and lazy.
          if (preg_match($needle, $output)) {
            $output = preg_replace($needle, '', $output);
          }
          // Find end of file.
          $needle = '/(\n\ *)return \$([a-zA-Z\d_]+);\ *\n\n?\}\ *\n?/';
          if (!preg_match($needle, $output)) {
            drush_log(dt('Can\'t find return/end of file in file[' . $path . '].'), 'error');
            continue; // Skip.
          }
          else {
            $output = preg_replace($needle, '  ' . join("\n  ", $ts) . "\n\n" . '$1return \$$2;' . "\n}\n", $output);
          }

          // No actual changes?
          if (strlen($output) == strlen($original) && $output == $original) {
            $identical_files[] = $filename;
          }
          else {
            $work_files[] = $filename;
            if (!$overwrite) {
              file_put_contents($output_dir . '/' . $filename, $output);
            }
            else {
              file_put_contents($path, $output);
            }
          }
        }
        else {
          $no_work_files[] = $filename;
        }
      }
      $files_completed[] = $filename;
    }
  }
  catch (Exception $xc) {
    $success = FALSE;
    watchdog(
      'localize_fields',
      'Extraction of localization sources failed: @error_message',
      array('@error_message' => $xc->getMessage()),
      WATCHDOG_ERROR
    );
    drush_log(dt('Failed, error: @error', array('@error' => $xc->getMessage())), 'error');
  }

  if ($inspections) {
    $nl = module_exists('dblog') ? '<br>' : ' ';
    watchdog(
      'localize_fields',
      'Extraction of localization sources, db operations:' . $nl . join($nl, $inspections),
      array(),
      WATCHDOG_INFO
    );
  }

  if ($no_work_files) {
    drush_print(
      dt('These !n files contained no translatable labels:!files',
        array('!n' => count($no_work_files), '!files' => "\n  " . join("\n  ", $no_work_files))) . "\n"
    );
  }

  if ($identical_files) {
    drush_print(
      dt('These !n files needed no file changes, but may have resulted in database changes (check log):!files',
        array('!n' => count($identical_files), '!files' => "\n  " . join("\n  ", $identical_files))) . "\n"
    );
  }

  if ($work_files) {
    if (!$overwrite) {
      drush_print(
        dt('These !n files got t()ed in copies filed to private files sub dir [!dir]:!files',
          array('!n' => count($work_files), '!files' => "\n  " . join("\n  ", $work_files), '!dir' => count($output_dir))) . "\n"
      );
    }
    else {
      drush_print(
        dt('These !n files got t()ed and overwritten!files',
          array('!n' => count($work_files), '!files' => "\n  " . join("\n  ", $work_files))) . "\n"
      );
    }
  }

  if (!$success) {
    $files_remaining = array_diff(array_keys($list), $files_completed);
    drush_log(
      dt('These !n files were not completed:!files',
        array('!n' => count($files_remaining), '!files' => "\n  " . join("\n  ", $files_remaining))),
      'warning'
    );
  }

  if ($success) {
    if (!$test) {
      cache_clear_all('locale:', 'cache', TRUE);
    }
    drush_log(dt('Cleared translation cache for all languages.'), 'ok');
  }

  drush_log(
    dt(
      '!testFeatures files translation extraction !succeeded.',
      array('!test' => !$test? '' : '(test) ', '!succeeded' => $success ? 'succeeded' : 'failed')
    ),
    $success ? 'success' : 'failed'
  );

  if (!module_exists('localize_fields')) {
    drush_log(dt('Field label translation will only work if the localize_fields module is enabled.'), 'warning');
  }
}

/**
 * Finds names and paths (path/filename) of all relevant Features files in a directory, recursively.
 *
 *  Details:
 *  - skip .features.inc (content type file): Features automatically insert t()s directly around the sentences, and core translation works.
 *  - (.features)?.field_group.inc: Find label and description, and add them t()'d (without context) to bottom of file (not translated by FLF; core translation works).
 *  - .features.field_base.inc: Find list_ type options, and add them t()'d to bottom of file.
 *  - .features.field_instance.inc: Find number_ type prefix/suffix, and add them t()'d to bottom of file.
 *
 * @param array   &$list
 * @param string  $dir
 * @param integer $depth_max
 *  - default: 5
 * @param integer $depth
 *  - default: zero
 *
 * @return void
 */
function _localize_fields_list_files(&$list, $dir, $depth_max = 5, $depth = 0) {
  if ((++$depth) > $depth_max) {
    return;
  }
  $le = count($sub_list = scandir($dir));
  for ($i = 0; $i < $le; $i++) {
    $item = $sub_list[$i];
    if ($item != '.' && $item != '..') {
      if (is_dir($dir . '/' . $item)) {
        _localize_fields_list_files($list, $dir . '/' . $item, $depth_max, $depth);
      }
      elseif (preg_match('/^.+\.(features\.field_base|features\.field_instance|field_group|features\.field_group)\.inc$/', $item)) {
        $list[$item] = $dir . '/' . $item;
      }
    }
  }
}

/**
 * Finds translatables of a field_base file.
 *
 * @param $path_file
 * @param $function
 * @return array|boolean
 */
function _localize_fields_type_field_base($path_file, $function) {
  require($path_file);
  if (!function_exists($function)) {
    drush_log(dt('Failed to include file[!path_file], or function[!function] doesnt exist.',
      array('!path_file' => $path_file, '!function' => $function)), 'error');
    return FALSE;
  }
  $cntxtDelim = LocalizeFields::CONTEXT_DELIMITER;

  $field_bases = $function();
  $sources = array();
  foreach ($field_bases as $field_name => $props) {
    if ($props['module'] == 'list') {
      // The field settings flag 'allowed_values_no_localization' ought not to collide with other,
      // and field _value_ translation is flagged with 'translatable' (in field settings' root).
      if (empty($props['settings']['allowed_values_no_localization'])) {
        $sources[$field_name] = array(
          'context' => 'field' . $cntxtDelim . $field_name,
          'sources' => array(
            'allowed_values' => $props['settings']['allowed_values'],
          ),
        );
      }
      else {
        drush_log('Skipped extracting allowed_values of field [' . $field_name . '] because has \'allowed_values_no_localization\' flag.', 'status');
      }
    }
    else {
      // 'Add another item' button label, if multi-cardinal.
      if (!empty($props['cardinality']) && $props['cardinality'] != 1) {
        $sources[$field_name] = array(
          'context' => 'field' . $cntxtDelim . $field_name,
          'sources' => array(
            'add_row' => !empty($props['settings']['add_row_localization_source']) ?
              $props['settings']['add_row_localization_source'] : variable_get('localize_fields_source_add_row', 'Add another item'),
          ),
        );
      }
    }
  }
  return $sources;
}

/**
 * Finds translatables of a field_instance file.
 *
 * @param $path_file
 * @param $function
 * @return array|boolean
 */
function _localize_fields_type_field_instance($path_file, $function) {
  require($path_file);
  if (!function_exists($function)) {
    drush_log(dt('Failed to include file[!path_file], or function[!function] doesnt exist.',
      array('!path_file' => $path_file, '!function' => $function)), 'error');
    return FALSE;
  }
  $cntxtDelim = LocalizeFields::CONTEXT_DELIMITER;
  $cntxtDelimBundle = LocalizeFields::CONTEXT_DELIMITER_BUNDLE;

  $field_instances = $function();
  $sources = array();
  foreach ($field_instances as $key_path => $props) {
    $sources[$key_path] = array(
      'context' => 'field_instance' . $cntxtDelim . $props['bundle'] . $cntxtDelimBundle . $props['field_name'],
      'sources' => array(
        'label' => $props['label'],
        'description' => $props['description'],
      ),
    );
    if (!empty($props['settings'])) {
      if (array_key_exists('prefix', $props['settings'])) {
        $sources[$key_path]['sources']['prefix'] = $props['settings']['prefix'];
      }
      if (array_key_exists('suffix', $props['settings'])) {
        $sources[$key_path]['sources']['suffix'] = $props['settings']['suffix'];
      }
    }
  }
  return $sources;
}

/**
 * Finds translatables of a field_group file.
 *
 * @param $path_file
 * @param $function
 * @return array|boolean
 */
function _localize_fields_type_field_group($path_file, $function) {
  require($path_file);
  if (!function_exists($function)) {
    drush_log(dt('Failed to include file[!path_file], or function[!function] doesnt exist.',
      array('!path_file' => $path_file, '!function' => $function)), 'error');
    return FALSE;
  }

  $field_group = $function();
  $sources = array();
  foreach ($field_group as $key_path => $props) {
    $sources[$key_path] = array(
      'context' => '', // Don't use context, because won't be translated by this module.
      'sources' => array(
        'label' => $props->data['label'],
      ),
    );
    if (!empty($props->data['format_settings']['instance_settings'])) {
      if (array_key_exists('description', $props->data['format_settings']['instance_settings'])) {
        $sources[$key_path]['sources']['description'] = $props->data['format_settings']['instance_settings']['description'];
      }
    }
  }
  return $sources;
}
