<?php
    function hitsa_bulk_upload_icons(){
        return drupal_get_form('hitsa_bulk_upload_form');
    }

    function hitsa_bulk_upload_form($form,&$form_state){
        $form = drupal_get_form('file_entity_add_upload_multiple');
        $form['upload']['#upload_validators']['file_validate_extensions'][0] = 'svg';
        
        $form['upload']['#upload_location']="public://svg_icons/";
        $form['#submit'][0] = 'hitsa_bulk_upload_form_submit';

        return $form;
    }

    function hitsa_bulk_upload_form_submit($form,&$form_state){

        $upload_location = !empty($form['upload']['#upload_location']) ?
            $form['upload']['#upload_location'] . '/' :
            variable_get('file_default_scheme', 'public') . '://';

        // Ensure writable destination directory for the files.
        file_prepare_directory($upload_location, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS);

        // We can't use file_save_upload() because of
        // http://www.jacobsingh.name/content/tight-coupling-no-not.
        foreach ($form_state['values']['upload'] as $uploaded_file) {
            if ($uploaded_file['status'] == 'done') {
            $source = $uploaded_file['tmppath'];
            $destination = file_stream_wrapper_uri_normalize($upload_location . $uploaded_file['name']);
            // Rename it to its original name, and put it in its final home.
            // Note - not using file_move here because if we call file_get_mime
            // (in file_uri_to_object) while it has a .tmp extension, it horks.
            $destination = file_unmanaged_move($source, $destination, FILE_EXISTS_REPLACE);

            $file = file_uri_to_object($destination);
            $file->status = FILE_STATUS_PERMANENT;
            file_save($file);

            $form_state['files'][$file->fid] = $file;
            }
            else {
            // @todo: move this to element validate or something.
            form_set_error('pud', t('The specified file %name could not be uploaded.', array('%name' => $uploaded_file['name'])));
            }
        }

        // Redirect to the file edit page.
        if (file_entity_access('update', $file) && module_exists('media_bulk_upload')) {
            $destination = array();
            if (isset($_GET['destination'])) {
            $destination = drupal_get_destination();
            unset($_GET['destination']);
            }
            elseif (user_access('administer files')) {
            $destination = array('destination' => 'admin/content/file');
            }
            $form_state['redirect'] = array('admin/content/file/edit-multiple/' . implode(' ', array_keys($form_state['files'])), array('query' => $destination));
        }
        else {
            $form_state['redirect'] = user_access('administer files') ? 'admin/content/file' : '<front>';
        }

        // Clear the page and block caches.
        cache_clear_all();
        $file_list = scandir("public://svg_icons");
        unset($file_list[0]);
        unset($file_list[1]);
        $conf_path = conf_path();
        $conf_path = str_replace('sites/', '', $conf_path);
        if ($conf_path!='default') {
            $site_theme_location = 'sites/'.$conf_path.'/themes/hitsa/static/dev/glyphs';
        } else {
            $site_theme_location=false;
        }
        $new_list_values = array();
        foreach($file_list as $file_name){
            $new_name = preg_replace('/[0-9]+/', '', $file_name);
            $new_name = str_replace('-','',$new_name);
            $new_name = str_replace('.svg','',$new_name);
            $new_name = ucfirst($new_name);
            $new_list_values[str_replace('.svg','',$file_name)] = $new_name;
            $file_content = file_get_contents('public://svg_icons/'.$file_name);
            if(!$site_theme_location){
                break;
            }
            $file =fopen($site_theme_location.'/'.$file_name, 'w');
            fwrite($file, $file_content);
            fclose($file);
        }
        var_dump(shell_exec('cd '.$_SERVER['DOCUMENT_ROOT'].'/'.'sites'.'/'.$conf_path.'/themes/hitsa/static && grunt compile 2>&1'));
        $field = field_info_field('field_icon_choice');
        // $field['settings']['allowed_values']+=
        $list_array = array_merge($field['settings']['allowed_values'],$new_list_values);
        $field['settings']['allowed_values'] = $list_array;
        field_update_field($field);
        drupal_set_message('Icons uploaded and should be usable in fields','status');
        drupal_goto('admin/appearance/hitsa_bulk_upload_icons');
        
    }