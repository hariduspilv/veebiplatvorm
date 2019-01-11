<?php

 function hitsa_cron_update_translations(){

   $updates = [
     '1'
  ];
  if (!empty($updates)) {
    $updated = variable_get('hitsa_translations_updated');
    $updated = explode(',', $updated);
    foreach ($updates as $update) {
      $to_update = TRUE;
      foreach ($updated as $uptodate) {
        if (strval($update) == strval($uptodate)) {
          $to_update = FALSE;
          break;
        }
      }
      if ($to_update) {
        $function_name = 'hitsa_cron_trans_up_' . strval($update);
        if (function_exists($function_name)) {
          $update_status = call_user_func($function_name, $update);
          if ($update_status) {
            $updatedd = variable_get('hitsa_translations_updated');
            if (empty($updatedd)) {
              variable_set('hitsa_translations_updated', $update);
            } else {
              variable_set('hitsa_translations_updated', $updatedd . ',' . $update);
            }
          }
        }
      }
    }
  }

 }
function hitsa_cron_trans_up_1(){
  $string_to_translate = 'Education';
  $translation = locale($string_to_translate);
// 1 Stringi puhul totoab nii muidu tuleb loop teha
  $words = array(
    'Education' => array(
      'et' => 'Haridus',
    ),
  );
  module_load_include('inc','hitsa_translation_importer','/includes/hitsa_translation_importer.admin');
  hitsa_translations_importer_translations($words);
  drupal_flush_all_caches();
}
