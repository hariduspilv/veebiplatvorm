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
    'Name search' => array(
      'et' => 'Nime otsing'
    ),
    'Alumnus' => array(
      'et' => 'Vilistlased'
    ),
    'Searched person was not found'=> array(
      'et' => 'Otsitavat isikut ei leitud'
    ),
    'Generate files' =>array(
      'et' => 'Genereeri failid'
    ),
    'Media Folders' => array(
      'et' => 'Meedia Kaustad'
    ),
    'Scheme' => array(
      'et' => 'Skeem',
    ),
    'Audio' => array(
      'et' => 'Helifail'
    ),
    'YouTube videos' => array(
      'et' =>  'Youtube video'
    ),
    'Include subfolders in results' =>array(
      'et' =>  'Näita alamkaustasi tulemustes'
    ),
    'Create an archive of selected files' => array(
      'et' => 'Loo arhiiv valitud failidest'
    ),
    'Download file(s)' => array(
      'et' => 'Lae failid alla'
    ),
    'Select all items on this page' => array(
      'et' => 'Vali kõik failid avatud lehel'
    ),
    'Folders' => array(
      'et' => 'Kaustad'
    ),
    'Media Files' => array(
      'et' => 'Meedia Failid'
    ),
    'Edit selected'=> array(
      'et' => 'Muuda valitud'
    ),

    'Delete selected'=> array(
      'et' => 'Kustuta valitud'
    ),
    'Download selected' => array(
      'et' =>  'Lae alla valitud'
    ),
    'Media Basket' => array(
      'et' => 'Meedia korv'
    ),
    'Download files in Media Basket' => array(
      'et' => 'Lae Meedia korvis olevad failid alla'
    ),
    'Indicate that the selected files are permanent and should not be deleted'=>  array(
      'et' => 'Märgi, et valitud failid on igavesed ja ei tohkis ära kustutada'
    ),
    'scheme' => array(
      'et' => 'skeem'
    ),
    'Indicate that the selected files are temporary and should be removed during cron runs'=>array(
      'et' => 'Märgi et valitud failid on ajutised ja peaksid kustutatama kasutades croni'
    ),
    'Delete selected files'=> array(
      'et' => 'Kustuta valitud failid'
    ),
    'Edit selected files' =>  array(
      'et' => 'Muuda valitud faile'
    ),
    'Refresh YouTube information from source' => array(
      'et' => 'Uuenda YouTube informatsiooni'
    ),
    'Archive' => array(
      'et' => 'Arhiveeri'
    ),
  );
  module_load_include('inc','hitsa_translation_importer','/includes/hitsa_translation_importer.admin');
  hitsa_translations_importer_translations($words);
  drupal_flush_all_caches();
  return TRUE;
}
