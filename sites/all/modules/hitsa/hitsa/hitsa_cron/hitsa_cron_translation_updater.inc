<?php

function hitsa_cron_update_translations()
{

  $updates = [
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',
    '10',
    '11',
    '12',
    '13',
    '14',
    '15',
    '16',
    '17',
    '18',
    '19',
    '20',
    '21',
    '22'


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

function hitsa_cron_trans_up_1()
{
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
    'Searched person was not found' => array(
      'et' => 'Otsitavat isikut ei leitud'
    ),
    'Generate files' => array(
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
      'et' => 'Youtube video'
    ),
    'Include subfolders in results' => array(
      'et' => 'Näita alamkaustasi tulemustes'
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
    'Edit selected' => array(
      'et' => 'Muuda valitud'
    ),

    'Delete selected' => array(
      'et' => 'Kustuta valitud'
    ),
    'Download selected' => array(
      'et' => 'Lae alla valitud'
    ),
    'Media Basket' => array(
      'et' => 'Meedia korv'
    ),
    'Download files in Media Basket' => array(
      'et' => 'Lae Meedia korvis olevad failid alla'
    ),
    'Indicate that the selected files are permanent and should not be deleted' => array(
      'et' => 'Märgi, et valitud failid on igavesed ja ei tohkis ära kustutada'
    ),
    'scheme' => array(
      'et' => 'skeem'
    ),
    'Indicate that the selected files are temporary and should be removed during cron runs' => array(
      'et' => 'Märgi et valitud failid on ajutised ja peaksid kustutatama kasutades croni'
    ),
    'Delete selected files' => array(
      'et' => 'Kustuta valitud failid'
    ),
    'Edit selected files' => array(
      'et' => 'Muuda valitud faile'
    ),
    'Refresh YouTube information from source' => array(
      'et' => 'Uuenda YouTube informatsiooni'
    ),
    'Archive' => array(
      'et' => 'Arhiveeri'
    ),
  );
  module_load_include('inc', 'hitsa_translation_importer', '/includes/hitsa_translation_importer.admin');
  hitsa_translations_importer_translations($words);
  drupal_flush_all_caches();
  return TRUE;
}

function hitsa_cron_trans_up_2()
{
  $words = array(
    'Front Page Image' => array(
      'et' => 'Esilehe pilt kuvatud',
    ),
    'Upload Logo Image' => array(
      'et' => 'Lehe logo',
    ),
    'Upload Front Page Image' => array(
      'et' => 'Lae üles esilehe pilt',
    ),

    'Contact page contact title' => array(
      'et' => 'Kontakti lehe kontakti pealkiri',
    ),
    'Footer right box title' => array(
      'et' => 'Jaluse parema ploki pealkiri',
    ),
    'Front page confirmation box title' => array(
      'et' => 'Esilehe tunnustuste ploki pealkiri',
    ),
    'Footer middle box title' => array(
      'et' => 'Jaluse keskmise ploki pealkiri',
    ),
    'Footer left box title' => array(
      'et' => 'Jaluse vasaku ploki pealkiri',
    ),
    'Front page gallery title' => array(
      'et' => 'Esilehe galerii pealkiri',
    ),
    'Front page services title' => array(
      'et' => 'Esilehe teenuste pealkiri',
    ),
    'Front page catering title' => array(
      'et' => 'Esilehe toitlustuse ploki pealkiri',
    ),
    'Front page events title' => array(
      'et' => 'Esilehe sündmuste pealkiri',
    ),
    'Our stories title' => array(
      'et' => 'Meie lood pealkiri esilehel',
    ),
    'Period title shown in calendar' => array(
      'et' => 'Vaheaegade ploki pealkiri kalendris',
    ),
    'Footer text area' => array(
      'et' => 'Jaluse tekstiala',
    ),
    'Footer text area title' => array(
      'et' => 'Jaluse tekstiala pealkiri',
    ),
    'Copyright Notice' => array(
      'et' => 'Kasutusõiguste märkus',
    ),
    'Phone Nr' => array(
      'et' => 'Telefoni number',
    ),
    'Name of institution' => array(
      'et' => 'Asutuse nimi',
    ),
    'multilingual' => array(
      'et' => 'mitmekeelne'
    ),
    'Front page hero banner maximum file size 10MB' => array(
      'et' => 'Esilehe bänneri maksimaalne faili suurus on 10MB'
    ),
    'Cooperation' => array(
      'et' => 'Koostöö'
    ),
    'Search for an event' => array(
      'et' => 'Otsi sündmust',
      'ru' => 'Поиск события'
    ),
  );

  module_load_include('inc', 'hitsa_translation_importer', '/includes/hitsa_translation_importer.admin');
  hitsa_translations_importer_translations($words);
  drupal_flush_all_caches();
  return TRUE;
}
function hitsa_cron_trans_up_3(){
  $words = array(
    'Calendar right block title' => array(
      'et' => 'Kalendri parema ploki pealkiri',
    ),
  );

  module_load_include('inc', 'hitsa_translation_importer', '/includes/hitsa_translation_importer.admin');
  hitsa_translations_importer_translations($words);
  drupal_flush_all_caches();
  return TRUE;
}
function hitsa_cron_trans_up_4(){
  $words = array(
    'Searchable event' => array(
      'et' => 'Otsitav sündmus',
    ),
    'Content Page Style' =>array(
      'et' => 'Sisulehe tüüp'
    ),
  );

  module_load_include('inc', 'hitsa_translation_importer', '/includes/hitsa_translation_importer.admin');
  hitsa_translations_importer_translations($words);
  drupal_flush_all_caches();
  return TRUE;
}
function hitsa_cron_trans_up_5(){
  $words = array(
    'Previous events' => array(
      'et' => 'Möödunud sündmused',
    ),
  );

  module_load_include('inc', 'hitsa_translation_importer', '/includes/hitsa_translation_importer.admin');
  hitsa_translations_importer_translations($words);
  drupal_flush_all_caches();
  return TRUE;
}
function hitsa_cron_trans_up_6(){
  $words = array(
    'January' => array(
      'et' => 'jaanuar',
    ),
    'February' => array(
      'et' => 'veebruar',
    ),
    'March' => array(
      'et' => 'märts',
    ),
    'April' => array(
      'et' => 'aprill',
    ),
    'May' => array(
      'et' => 'mai',
    ),
    'June' => array(
      'et' => 'juuni',
    ),
    'July' => array(
      'et' => 'juuli',
    ),
    'August' => array(
      'et' => 'august',
    ),
    'September' => array(
      'et' => 'september',
    ),
    'October' => array(
      'et' => 'oktoober',
    ),
    'November' => array(
      'et' => 'november',
    ),
    'December' => array(
      'et' => 'detsember'
    ),
  );
  module_load_include('inc', 'hitsa_translation_importer', '/includes/hitsa_translation_importer.admin');
  hitsa_translations_importer_translations($words,'Long month name');
  drupal_flush_all_caches();
  return TRUE;
}
function hitsa_cron_trans_up_7(){
  $words = array(
    'Õppetöö' => array(
      'en' => 'Studies',
    ),

  );
  $taxonomy = taxonomy_vocabulary_machine_name_load('hitsa_event_tags');
    $taxonomy_tree = taxonomy_get_tree($taxonomy->vid);
    $allowed = array();
    foreach ($taxonomy_tree as $term) {
        if($term->name=='Õppetöö'){
          $tid = $term->tid;
        }
    }
  module_load_include('inc', 'hitsa_translation_importer', '/includes/hitsa_translation_importer.admin');
  if(!empty($tid)){
      hitsa_translations_importer_translations($words,'term:'.$tid.':name');
      drupal_flush_all_caches();
      return TRUE;
  }
}
function hitsa_cron_trans_up_8(){
  $words = array(
    'Test failed, please make sure you use your keywords in the body but not too often.' => array(
      'et'=> 'Test ebaõnnestus, veenduge, et teie võtmesõna esineks, kuid mitte liiga tihti',
    ),
    'Test failed, please make sure your images contain an alternative text.' => array(
      'et' => 'Test ebaõnnestus, veenduge et teie pilt sisaldaks alampealkirja.'
    ),
    'Test failed, please make sure your links contain a title attribute.' => array(
      'et' => 'Test ebaõnnestus, veenduge et teie link sisaldaks tiitel atribuuti.'
    ),
    'Test failed, place your keywords early in your node title.' => array(
      'et'=>'Test ebaõnnestus veenduge, et võtmesõna oleks pealkirjas võimalikult alguses'
    ),
    'Passed' => array(
      'et'=>'Õnnestus'
    ),
    'Failed' => array(
      'et'=>'Ebaõnnestus'
    ),
    'Usage of keywords in node titles' => array(
      'et'=>'Võtmesõna kasutus pealkirjas'
    ),
    'Keyword density in the body' => array(
      'et'=> 'Võtmesõna tihedus sisus'
    )
  );
  module_load_include('inc', 'hitsa_translation_importer', '/includes/hitsa_translation_importer.admin');
  hitsa_translations_importer_translations($words);
  drupal_flush_all_caches();
}
function hitsa_cron_trans_up_9(){
  $words = array(
    'Previous events' => array(
      'et'=> 'Möödunud sündmused',
      'ru' => 'Прошедшие события',
    ),
    'Tomorrow' => array(
      'et' => 'Homme',
      'ru' => 'Завтра'
    ),
  );
  module_load_include('inc', 'hitsa_translation_importer', '/includes/hitsa_translation_importer.admin');
  hitsa_translations_importer_translations($words);
  drupal_flush_all_caches();
}
function hitsa_cron_trans_up_10(){
  $words = array(
    'Searchable event' => array(
      'et'=> 'Otsi sündmust',
      'ru' => 'Ищи мероприятие',
    ),
  );
  module_load_include('inc', 'hitsa_translation_importer', '/includes/hitsa_translation_importer.admin');
  hitsa_translations_importer_translations($words);
  drupal_flush_all_caches();
}
function hitsa_cron_trans_up_11(){
  $words = array(
    'SEO Check Results' => array(
      'et'=> 'SEO testi tulemused',
    ),
    'Rule' => array(
      'et'=> 'Reegel',
    ),
    'Achieved' => array(
      'et'=> 'Saavutatud',
    ),
  );
  module_load_include('inc', 'hitsa_translation_importer', '/includes/hitsa_translation_importer.admin');
  hitsa_translations_importer_translations($words);
  drupal_flush_all_caches();
}
function hitsa_cron_trans_up_12(){
  $words = array(
    'Filter trainings' => array(
      'et'=> 'Filtreeri koolitusi',
      'ru' => 'Oбучение фильтра'
    ),
  );
  module_load_include('inc', 'hitsa_translation_importer', '/includes/hitsa_translation_importer.admin');
  hitsa_translations_importer_translations($words);
  drupal_flush_all_caches();
}
function hitsa_cron_trans_up_13(){
  $words = array(
    'Test passed.' => array(
      'et'=> 'Test õnnestus',
    ),
  );
  module_load_include('inc', 'hitsa_translation_importer', '/includes/hitsa_translation_importer.admin');
  hitsa_translations_importer_translations($words);
  drupal_flush_all_caches();
}

function hitsa_cron_trans_up_14(){
  $words = array(
    'Calendar view' => array(
      'et'=> 'Kalendrivaade',
    ),
  );
  module_load_include('inc', 'hitsa_translation_importer', '/includes/hitsa_translation_importer.admin');
  hitsa_translations_importer_translations($words);
  drupal_flush_all_caches();
  return TRUE;
}
function hitsa_cron_trans_up_15(){
  $words = array(
    'January' => array(
      'et' => 'jaanuar',
    ),
    'February' => array(
      'et' => 'veebruar',
    ),
    'March' => array(
      'et' => 'märts',
    ),
    'April' => array(
      'et' => 'aprill',
    ),
    'May' => array(
      'et' => 'mai',
    ),
    'June' => array(
      'et' => 'juuni',
    ),
    'July' => array(
      'et' => 'juuli',
    ),
    'August' => array(
      'et' => 'august',
    ),
    'September' => array(
      'et' => 'september',
    ),
    'October' => array(
      'et' => 'oktoober',
    ),
    'November' => array(
      'et' => 'november',
    ),
    'December' => array(
      'et' => 'detsember'
    ),
  );
  module_load_include('inc', 'hitsa_translation_importer', '/includes/hitsa_translation_importer.admin');
  hitsa_translations_importer_translations($words,'Long month name');
  drupal_flush_all_caches();
  return TRUE;
}

function hitsa_cron_trans_up_16(){
  $words = array(
    'Extra information' => array(
      'et'=> 'Lisainfo',
    ),
  );
  module_load_include('inc', 'hitsa_translation_importer', '/includes/hitsa_translation_importer.admin');
  hitsa_translations_importer_translations($words);
  drupal_flush_all_caches();
  return TRUE;
}
function hitsa_cron_trans_up_17(){
  $words = array(
    'Organizers' => array(
      'et' => 'Korraldajad',
    ),
    'Organizer' => array(
      'et' => 'Korraldaja'
    ),
    'Project manager' => array(
      'et' =>  'Projektijuht'
    ),
  );
  module_load_include('inc', 'hitsa_translation_importer', '/includes/hitsa_translation_importer.admin');
  hitsa_translations_importer_translations($words);
  return TRUE;
}
function hitsa_cron_trans_up_18(){
  $words = array(
    'Trainers' => array(
      'et' => 'Koolitajad',
    ),
    'Trainer' => array(
      'et' => 'Koolitaja'
    ),
  );
  module_load_include('inc', 'hitsa_translation_importer', '/includes/hitsa_translation_importer.admin');
  hitsa_translations_importer_translations($words);
  return TRUE;
}
function hitsa_cron_trans_up_19(){
  $words = array(
    'Previous events' => array(
      'et' => 'Möödunud sündmused',
    ),
  );
  module_load_include('inc', 'hitsa_translation_importer', '/includes/hitsa_translation_importer.admin');
  hitsa_translations_importer_translations($words);
  return TRUE;
}
function hitsa_cron_trans_up_20(){
  $words = array(
    'December' => array(
      'et' => 'Detsember',
    ),
  );
  module_load_include('inc', 'hitsa_translation_importer', '/includes/hitsa_translation_importer.admin');
  hitsa_translations_importer_translations($words,'Long month name');
  return TRUE;
}
function hitsa_cron_trans_up_21(){
  $words = array(
    'December' => array(
      'et' => 'Detsember',
    ),
  );
  module_load_include('inc', 'hitsa_translation_importer', '/includes/hitsa_translation_importer.admin');
  hitsa_translations_importer_translations($words);
  return TRUE;
}
function hitsa_cron_trans_up_22(){
  $words = array(
    'December' => array(
      'et' => 'detsember',
    ),
  );
  module_load_include('inc', 'hitsa_translation_importer', '/includes/hitsa_translation_importer.admin');
  hitsa_translations_importer_translations($words);
  $words = array(
    'December' => array(
      'et' => 'detsember',
    ),
  );
  module_load_include('inc', 'hitsa_translation_importer', '/includes/hitsa_translation_importer.admin');
  hitsa_translations_importer_translations($words,'Long month name');
  return TRUE;
}
