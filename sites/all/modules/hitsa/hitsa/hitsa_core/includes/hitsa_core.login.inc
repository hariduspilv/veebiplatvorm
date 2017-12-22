<?php

function hitsa_core_id_login_form($form, &$form_state, $type) {
  
  $form['#login_type'] = $type;
  
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Username') . ':',
    '#required' => TRUE,
    '#description' => t('* marked fields are required.')
  );
  
  $form['log_in'] = array(
    '#type' => 'submit',
    '#value' => t('Log in'),
    '#attributes' => array(
      'class' => array('btn btn-filled sm-stretch'),
    ),
  );
  
  return $form;
}

function hitsa_core_id_login_form_submit($form, &$form_state) {
  // Do magic here
}

function hitsa_core_forms($form_id, $args) {
  $forms = array();
  
  if (strncmp($form_id, 'hitsa_core_id_login_form_', 25) === 0) {
    $argument = str_replace('hitsa_core_id_login_form_', '', $form_id);
    $forms[$form_id] = array(
      'callback' => 'hitsa_core_id_login_form',
      'callback arguments' => array(
        $argument,
      ),
    );
  }
  return $forms;
}