<?php
    function hitsa_core_event_settings(){
      
     return drupal_get_form('hitsa_core_event_settings_form');

    }
    
    function hitsa_core_event_settings_form($form,&$form_state){
      $form = array();
      $code = variable_get('period_title');
      
      $form['period_title'] = array(
        '#type' => 'textfield',
        '#title' => t('Time period title'),
        '#description' => t('Time period title that appears right of calendar'),
        '#default_value' => $code,
        '#size' => 255,
        '#required' => FALSE,
      );
      return system_settings_form($form);
    }