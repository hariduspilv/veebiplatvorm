<?php

function hitsa_contacts_import_form($form, &$form_state) {
  
  if (!isset($form_state['stage'])) $form_state['stage'] = 'upload_file';
  
  switch ($form_state['stage']) {
    case 'upload_file':
      $form['instuctions'] = array(
        '#markup' => t('<div>Here goes the contact import instructions.</div>'),
      );
      
      $form['upload'] = array(
        '#type' => 'file',
        '#title' => t('Choose a file'),
        '#title_display' => 'invisible',
        '#size' => 22,
      );
      
      $form['submit'] = array('#type' => 'submit', '#value' => t('Import'));
      break;
    case 'delete_missing':
      $form['instuctions'] = array(
        '#markup' => t('<h2>No match found for following contact nodes. <b>Would you like to delete these nodes?</b></h2>'),
      );
      
      $form['missing_nodes_table'] = hitsa_contacts_missing_nodes_table_form($form, $form_state);
      
      $form['submit'] = array('#type' => 'submit', '#value' => t('Delete'), '#submit' => array('hitsa_contacts_delete_missing_nodes'));
      $form['back'] = array('#type' => 'submit', '#value' => t('Go back'));
      break;
  }
  return $form;
}

function hitsa_contacts_import_form_validate($form, &$form_state) {

}

function hitsa_contacts_import_form_submit($form, &$form_state) {
  $file = file_save_upload('upload', array(
      'file_validate_extensions' => array('csv'),
      'file_validate_size' => array(1024*1024),
  ));
  
  // File upload failed
  if(empty($file) || !$file) {
    return;
  }

  $content = file_get_contents($file->uri);
  file_delete($file);
  
  $result = hitsa_contacts_import($content);
  
  if(!empty($result)) {
    // Contact nodes found in the system, which are not found in the import file.
    $form_state['stage'] = 'delete_missing';
    $form_state['missing_nodes'] = $result;
    $form_state['rebuild'] = TRUE;
  }
  drupal_set_message(t('Contact import finished successfully!'));
}

function hitsa_contacts_import($csv_content) {
  $csv_contacts = hitsa_contacts_parse_csv_file($csv_content);
  $existings_nodes = hitsa_contacts_get_existing_contact_nodes();
  
  foreach($csv_contacts as $csv_contact) {
    hitsa_contacts_create_update_contact($csv_contact, $existings_nodes);
  }
  
  return $existings_nodes;
}

function hitsa_contacts_get_existing_contact_nodes() {
  $result = &drupal_static(__FUNCTION__);
  
  if(!isset($result)) {
    $query = db_query('SELECT contact_id_value, entity_id FROM field_data_contact_id');
    $result = $query->fetchAllKeyed();
  }
  
  return $result;
}

function hitsa_contacts_parse_csv_file($csv_content) {
  $output = array();
  
  $contacts = explode("\n", $csv_content);
  
  foreach($contacts as $c) {
    $contact = explode("\t", $c);

    if(count($contact) !== 10) continue; // Faulty schema, skip contact
    
    $groups_string = explode('|', $contact[9]);
    $groups = array();
    foreach($groups_string as $g) {
      $g_parsed = explode(';', $g);
      
      if(count($g_parsed) !== 2) continue; // Faulty schema, skip group
      
      $groups[] = $g_parsed;
    }
    $contact[9] = $groups;
    $output[] = $contact;
  } 

  return $output;
}

function hitsa_contacts_create_update_contact($contact_array, &$existings_nodes) {
  global $user;
  
  $contact_id = $contact_array[0];
  if(isset($existings_nodes[$contact_id])) {
    // Node exists, update existing node
    $node = node_load($existings_nodes[$contact_id]);
    unset($existings_nodes[$contact_id]);
  } else {
    // New node, create 
    $node = new stdClass();
    $node->title = "Contact"; // We'll set the actual title using a presave function.
    $node->type = "contact";
    node_object_prepare($node);
    $node->uid = $user->uid;
    $node->status = 1;
    // TODO: Should manually added nodes account for missing contact id?*/
  }
  
  $emw_node = entity_metadata_wrapper('node', $node);
  
  /* String input */
  $emw_node->contact_id = $contact_array[0]; // Contact ID
  $emw_node->first_name = $contact_array[1]; // First name
  $emw_node->last_name = $contact_array[2]; // Last name
  $emw_node->phone_nr = $contact_array[4]; // Phone Nr.
  $emw_node->e_mail = $contact_array[5]; // E-Mail
  //$emw_node->additional_info = $contact_array[6]; // Additional info
  $emw_node->reception_times = explode('|', $contact_array[7]); // Reception times
  $emw_node->contact_cv = array('url' => $contact_array[8]); // CV Link
  
  /* Taxonomy input */
  // Job position
  $job_position_term = taxonomy_get_term_by_name($contact_array[3], 'contacts_job_position');
  if(!empty($job_position_term)) {
    $emw_node->job_position = reset($job_position_term);
  } else {
    // Create new taxonomy term
    $job_position_voc = taxonomy_vocabulary_machine_name_load('contacts_job_position');
    $job_position_tid = _create_taxonomy_term($contact_array[3], $job_position_voc->vid);
    // Set new taxonomy term
    $emw_node->job_position = $job_position_tid;
  }
  
  $emw_node->contact_departments = array();
  $emw_node->save();
  
  // Department
  if(!empty($contact_array[9])) {
    $jd_array = $contact_array[9];
    $job_deparments = array();
    foreach($jd_array as $jd) {
      $entity = entity_create('paragraphs_item', array('field_name' => 'contact_departments', 'bundle' => 'contacts_department'));
      $entity->setHostEntity('node', $emw_node->value());
      $entity->save();
      
      $emw_entity = entity_metadata_wrapper('paragraphs_item', $entity);
      
      // Weight
      $emw_entity->department_weight = $jd[1];
      
      // Department taxonomy term
      $department_term = taxonomy_get_term_by_name($jd[0], 'contacts_department');
      if(!empty($department_term)) {
        $emw_entity->job_department = reset($department_term);
      } else {
        // Create new taxonomy term
        $department_voc = taxonomy_vocabulary_machine_name_load('contacts_department');
        $department_tid = _create_taxonomy_term($jd[0], $department_voc->vid);
        // Set new taxonomy term
        $emw_entity->job_department = $department_tid;
      }
      $emw_entity->save();
    }
  }
}

function hitsa_contacts_missing_nodes_table_form($form, $form_state) {
  $element = array();
  if(!empty($form_state['missing_nodes'])) {
    $missing_nodes = node_load_multiple($form_state['missing_nodes']);
    
    $header = array(
    'contact_id' => array('data' => t('ID')),
    'title' => array('data' => t('Name')),
    'edit_link' => array('data' => NULL),
    );
    
    $options = array();
    foreach($missing_nodes as $node) {
      $options[$node->nid] = array(
        'contact_id' => !empty($node->contact_id[LANGUAGE_NONE][0]['value']) ? $node->contact_id[LANGUAGE_NONE][0]['value'] : '',
        'title' => $node->title,
        'edit_link' => '<a target="_blank" href="' . url('node/' . $node->nid . '/edit') . '">' . t('Edit') . '</a>',
      );
    }
    
    $element = array(
      '#type' => 'tableselect',
      '#header' => $header,
      '#options' => $options,
      '#empty' => t('No content available.'),
    );
  }
  return $element;
}

function hitsa_contacts_delete_missing_nodes($form, &$form_state) {
  if(!empty($form_state['values']['missing_nodes_table'])) {
    $nids = $form_state['values']['missing_nodes_table'];
    
    $delete_nids = array();
    foreach($nids as $nid) {
      if(!empty($nid)) $delete_nids[] = $nid;
    }
    if(!empty($delete_nids)) {
      // Delete the selected nodes
      node_delete_multiple($delete_nids);
      drupal_set_message(t('Nodes successfully deleted!'));
    }
  }
}

/**
 * Create a taxonomy term and return the tid.
 */
function _create_taxonomy_term($name, $vid) {
  $term = new stdClass();
  $term->name = $name;
  $term->vid = $vid;
  taxonomy_term_save($term);
  return $term->tid;
}