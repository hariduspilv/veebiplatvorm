<?php

function hitsa_contacts_form($form, &$form_state) {
  $form['contact_search'] = array(
    '#type' => 'textfield',
    '#title' => t('Search for person'),
    '#attributes' => array(
      'placeholder' => t('Name'),
    ),
  );
  
  $form['job_position'] = array(
    '#type' => 'select',
    '#title' => t('Job position'),
    '#options' => array('0' => 'ok'),
  );
  
  $form['submit'] = array(
    '#type' => 'submit', 
    '#value' => t('Search')
  );
  
  return $form;
}

function hitsa_contacts_form_validate($form, &$form_state) {
  
}

function hitsa_contacts_form_submit($form, &$form_state) {
  
}