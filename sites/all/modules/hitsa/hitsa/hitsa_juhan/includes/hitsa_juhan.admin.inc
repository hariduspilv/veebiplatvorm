<?php
function hitsa_juhan_settings(){

  return drupal_get_form('hitsa_juhan_settings_form');

}

function hitsa_juhan_settings_form($form,&$form_state){
  $form = array();

  $code = variable_get('juhan_api_key');
  $form['juhan_api_key'] = array(
    '#type'=> 'textfield',
    '#title' => 'Juhan api key',
    '#default_value' => $code,
  );
  $form['update'] = array(
    '#type' => 'submit',
    '#value' => 'Uuenda juhani koolitusi',
    '#submit' => array('hitsa_juhan_update_submit')
  );
  return system_settings_form($form);
}
function hitsa_juhan_update_submit($form,&$form_state){
  if($form_state['clicked_button'] == 'Uuenda juhani koolitusi'){
    hitsa_juhan_get_trainings();
  }
}
