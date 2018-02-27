<?php
function hitsa_translations_importer_settings()
{

    return drupal_get_form('hitsa_translations_importer_settings_form');
}

function hitsa_translations_importer_settings_form($form, &$form_state)
{
    $form = array();
    $code = variable_get('period_title');
    $form['tranlsation_file'] = array(
        '#name' => 'translations_file',
        '#type' => 'managed_file',
        '#upload_location' => 'public://translations/',
        '#title' => t('Choose a file'),
        '#weight' => -10,
        '#upload_validators' => array(
            'file_validate_extensions' => array('csv xlsx txt'),
          ),
    );
    $form['import'] = array(
    '#type' => 'submit',
    '#title' => t('Import translations'),
    '#value' => 'Import translations',
    '#name' => 'import_translations',
    '#submit' => array('hitsa_translations_importer_settings_form_submit'),
    '#validate' => array('hitsa_translations_importer_settings_form_validate'),
    '#size' => 255,
    '#required' => false,
    );
    return $form;
}

function hitsa_translations_importer_settings_form_submit($form, &$form_state)
{
    if (!empty($form_state['values'])) {
        if (!empty($form_state['values']['tranlsation_file'])) {
            $file_id = $form_state['values']['tranlsation_file'];
            $loaded_file = file_load($file_id);
            $read_text = file_get_contents($loaded_file->uri);
            $data = array_map("str_getcsv", preg_split('/\r*\n+|\r+/', $read_text));
            $translatable_array=array();
    
            foreach ($data as $translate_key => $translate_value) {
    
    
                if (!empty($translate_value[1])) {
                    //dpm(t($translate_value[1]));
                    $translatable_array[$translate_value[1]] = array(
                    'et' => (!empty($translate_value[0]))?$translate_value[0]:'',
                    'ru' => (!empty($translate_value[2]))?$translate_value[2]:'',
                    );
                    $lower_eng = (!empty($translate_value[1]))?mb_strtolower($translate_value[1]):'';
                    //dpm(t($lower_eng));
                    $lower_est = (!empty($translate_value[0]))?mb_strtolower($translate_value[0]):'';
                    $lower_ru = (!empty($translate_value[2]))?mb_strtolower($translate_value[2]):'';
    
                    $translatable_array[$lower_eng] = array(
                        'et' => (!empty($lower_est))?$lower_est:'',
                        'ru' => (!empty($lower_ru))?$lower_ru:'',
                        );
    
                    $lower_eng = (!empty($lower_eng))?str_replace(' ','-',$lower_eng):'';
                    //dpm(t($lower_eng));
                    $lower_est = (!empty($lower_est))?str_replace(' ','-',$lower_est):'';
                    $lower_ru = (!empty($lower_ru))?str_replace(' ','-',$lower_ru):'';
    
                    $translatable_array[$lower_eng] = array(
                        'et' => (!empty($lower_est))?$lower_est:'',
                        'ru' => (!empty($lower_ru))?$lower_ru:'',
                        );
    
                    $first_eng = (!empty($translate_value[1]))?ucfirst(strtolower($translate_value[1])):'';
                    //dpm(($first_eng));
                    $first_est = (!empty($translate_value[0]))?ucfirst($translate_value[0]):'';
                    $first_ru = (!empty($translate_value[2]))?ucfirst($translate_value[2]):'';
                    $translatable_array[$first_eng] = array(
                        'et' => (!empty($first_est))?$first_est:'',
                        'ru' => (!empty($first_ru))?$first_ru:'',
                    );
    
                }
            }
                    foreach ($translatable_array as $translatable_key => $translatable){
                        foreach($translatable as $test_key => $test){
                            if(empty($test)){
                                unset($translatable_array[$translatable_key][$test_key]);
                            }
                        }
                    }
            if (!empty($translatable_array)) {
                if (is_array($translatable_array)) {
                    hitsa_translations_importer_translations($translatable_array);
                }
            }
        }
    }
    

}
function hitsa_translations_importer_settings_form_validate($form, &$form_state)
{
    return true;
}
function hitsa_translations_importer_translations($translations)
{   
    if (!empty($translations)) {
        foreach ($translations as $string => $values) {
            $source = db_query('SELECT lid, source, context, textgroup, location FROM {locales_source} WHERE source = :string', array(':string' => $string))->fetchObject();
            if (!$source) {
                watchdog('update_hook', 'Translation of string "%string" failed.', array('%string' => $string));
                continue;
            }

            foreach ($values as $langcode => $translated) {
                $translation = db_query('SELECT translation FROM {locales_target} WHERE lid = :lid AND language = :language', array(':lid' => $source->lid, ':language' => $langcode))->fetchField();
                if (is_string($translation)) {
                    db_update('locales_target')
                    ->fields(array('translation' => $translated))
                    ->condition('lid', $source->lid)
                    ->condition('language', $langcode)
                    ->execute();
                } else {
                    db_insert('locales_target')
                    ->fields(
                        array(
                        'lid' => $source->lid,
                        'translation' => $translated,
                        'language' => $langcode,
                        )
                    )
                    ->execute();
                }
            }
        }
    }
}
