<?php
/**
 * Import page
 */
function hitsa_color_page()
{
    return drupal_get_form('hitsa_color_change_form');
}

/**
 * Form for color change
 */
function hitsa_color_change_form($form, &$form_state)
{
    $site_theme_location = 'sites/all/themes/hitsa/static/dev/site-theme.less';
    $conf_path = conf_path();
    $conf_path = str_replace('sites/', '', $conf_path);
    if ($conf_path!='default') {
        $site_theme_location = 'sites/'.$conf_path.'/themes/hitsa/static/dev/site-theme.less';
    }
    if (file_exists($site_theme_location)) {
        // if(!file_exists($site_theme_location)){
        // 	drupal_set_message('Vajalikku faili ei eksisteeri');
        // 	break;
        // }
        $my_color = file_get_contents($site_theme_location);
        if (empty($my_color)) {
            drupal_set_message('Vajalikku faili ei eksisteeri');
        }
        $form_state['storage']['file_content'] = $my_color;
        $file_content = explode(';', $my_color);
        foreach ($file_content as $site_theme_row) {
            if (empty($site_theme_row)) {
                continue;
            } elseif (strlen($site_theme_row)==1) {
                continue;
            }
            $row_value = explode(':', $site_theme_row);
            $row_value[0] = preg_replace( "/\r|\n/", "", $row_value[0] );
            $form_state['storage']['classes'][]=$row_value[0];
            $description = '';
            if ($row_value[0]=='highlight-1') {
                $description = 'Lehe põhivärvitoon, millest genereeritakse ülejäänud värvitoonid';
            }
            if (strpos($row_value[0], 'border-radius')!=false) {
                $description = 'Nuppude raadius 999px tähendab ümarat 0px tähendab kandilist 0px-80px tähendab kandilist nuppu ümarate nurkadega';
            }
            if (strpos($row_value[0], 'block-border-radius')!=false) {
                $description = 'Kastide raadius 2pxi tähendab ümarat 0pxi tähendab kandilist 0px-80px tähendab kandilist nuppu ümarate nurkadega';
            }

            $form[$row_value[0]] = array(
                '#title'=> $row_value[0] . ':',
                '#type' => 'textfield',
                '#size' => 10,
                '#id' => $row_value[0],
                '#name' => $row_value[0],
                '#description' => $description,
                '#default_value' => $row_value[1],
            );
        }
        if (!empty($my_color)) {
            $form['submit'] = array(
                '#submit' => array('hitsa_import_js','hitsa_import_css','hitsa_color_change'),
                '#type' => 'submit',
                '#value' => t('Vaheta värvi')
            );
            $form['import_css'] = array(
              '#submit' => array('hitsa_import_css'),
              '#attributes'=>array(
                'style' => 'display:none',
              ),
              '#type' => 'submit',
              '#value' =>'import_css',
            );
        }   
        return $form;
    } else {
        drupal_set_message('Vajalikku faili ei eksisteeri');
    }
}

/**
*Save file
*/
function hitsa_color_change($form, &$form_state)
{
    //dpm($form_state['input']);
    //dpm($form_state['storage']['classes']);
    $output = '';
    $cmd = '';
    foreach ($form_state['storage']['classes'] as $class) {
        //dpm($class);
        if (!empty($form_state['values'][$class])) {
            $output .= $class . ':' . $form_state['values'][$class] . ';';
        }
    }

    //exec($_SERVER['DOCUMENT_ROOT'].'/sites/all/themes/hitsa/static/Gruntfile.js');
    //putenv('PATH=' . getenv('PATH') . '/home/ubuntu/nodejs /home/ubuntu/workspace/sites/all/themes/hitsa/static/Gruntfile.js');
    //exec(' cd /sites/all/themes/hitsa/static && grunt 2>&1');
    //exec('C:\Program Files (x86)\Ampps\www\hitsa\sites\all\themes\hitsa\static\Gruntfile.js');
    //exec('cd sites/all/themes/hitsa/static/Gruntfile.js');
    //var_dump(shell_exec('cd C:\"Program Files (x86)"/Ampps/www/hitsa/sites/all/themes/hitsa/static/ && C:/Program Files/nodejs C:/Program Files/nodejs/grunt 2>&1 /dev/null'));
    //$cmd .= 'cd..';
    //$cmd .= 'cd..';
    //$cmd .= 'cd C:\Program Files (x86)"/Ampps/www/hitsa/sites/all/themes/hitsa/static ';
    //$cmd .= 'grunt watch';
    //var_dump(shell_exec($cmd));

    $site_theme_location = 'sites/all/themes/hitsa/static/dev/site-theme.less';
    $conf_path = conf_path();
    $conf_path = str_replace('sites/', '', $conf_path);
    if ($conf_path!='default') {
        $site_theme_location = 'sites/'.$conf_path.'/themes/hitsa/static/dev/site-theme.less';
    } else {
        $conf_path = 'all';
        $site_theme_location = 'sites/'.$conf_path.'/themes/hitsa/static/dev/site-theme.less';
    }
    $file =fopen($site_theme_location, 'w');
    fwrite($file, $output);
    fclose($file);

    var_dump(shell_exec('cd '.$_SERVER['DOCUMENT_ROOT'].'/'.'sites'.'/'.$conf_path.'/themes/hitsa/static && grunt compile 2>&1'));
    //$file = file_save_data($output, 'private://'. 'site-theme.less',FILE_EXISTS_REPLACE);
    return $file;
}
function hitsa_import_js($form,&$form_state){
    
    $files = array(
        'device.min.js',
        'fastclick.js',
        'jquery-1.10.2.min.js',
        'jquery.daterangepicker.js',
        'jquery.filter.js',
        'jquery.functions.js',
        'jquery.gallery.js',
        'jquery.modal.js',
        'jquery.sumoselect.min.js',
        'map.js',
        'moment.min.js',
        'swiper.jquery.js',
        'tooltipster.bundle.js',
        'translations.js',
        'wpm.js'
      );
    $files_location = 'sites/all/themes/hitsa/static/dev/js';
    $conf_path = conf_path();
    $conf_path = str_replace('sites/', '', $conf_path);
    if ($conf_path!='default') {
        $site_theme_location = 'sites/'.$conf_path.'/themes/hitsa/static/dev/js';
    } else {
        $site_theme_location=false;
    }
    foreach ($files as $key => $file_name) {
        $file_content = file_get_contents($files_location.'/'.$file_name);
        if (!empty($file_content)) {
            if (!$site_theme_location) {
                break;
            }
            $file =fopen($site_theme_location.'/'.$file_name, 'w');
            fwrite($file, $file_content);
            fclose($file);
        }
    }
}
function hitsa_import_css($form, &$form_state)
{
    $files = array(
        'article.less','build.less','buttons.less','elements.less','footer.less','form.less','grid.less','header.less','print.less','reset.less','responsive.less','sumoSelect.less','swiper.less','theme.less','tooltipster.bundle.less'
      );
    $files_location = 'sites/all/themes/hitsa/static/dev/styles';
    $conf_path = conf_path();
    $conf_path = str_replace('sites/', '', $conf_path);
    if ($conf_path!='default') {
        $site_theme_location = 'sites/'.$conf_path.'/themes/hitsa/static/dev/styles';
    } else {
        $site_theme_location=false;
    }
    foreach ($files as $key => $file_name) {
        $file_content = file_get_contents($files_location.'/'.$file_name);
        if (!empty($file_content)) {
            if (!$site_theme_location) {
                break;
            }
            $file =fopen($site_theme_location.'/'.$file_name, 'w');
            fwrite($file, $file_content);
            fclose($file);
        }
    }
}
function hitsa_import_css_update()
{
    $files = array(
        'article.less','build.less','buttons.less','elements.less','footer.less','form.less','grid.less','header.less','print.less','reset.less','responsive.less','sumoSelect.less','swiper.less','theme.less','tooltipster.bundle.less'
      );
    $files_location = 'sites/all/themes/hitsa/static/dev/styles';
    $conf_path = conf_path();
    $conf_path = str_replace('sites/', '', $conf_path);
    if ($conf_path!='default') {
        $site_theme_location = 'sites/'.$conf_path.'/themes/hitsa/static/dev/styles';
    } else {
        $site_theme_location=false;
    }
    foreach ($files as $key => $file_name) {
        $file_content = file_get_contents($files_location.'/'.$file_name);
        if (!empty($file_content)) {
            if (!$site_theme_location) {
                break;
            }
            $file =fopen($site_theme_location.'/'.$file_name, 'w');
            fwrite($file, $file_content);
            fclose($file);
        }
    }
    $conf_path = conf_path();
    $conf_path = str_replace('sites/', '', $conf_path);
    var_dump(shell_exec('cd '.$_SERVER['DOCUMENT_ROOT'].'/'.'sites'.'/'.$conf_path.'/themes/hitsa/static && grunt compile 2>&1'));
}
