<?php

function hitsa_contacts_theme() {
  $items = array();
  
  $items['contacts_page'] = array(
    'render element' => 'page',
    'template' => 'hitsa-contacts-page',
    'path' => drupal_get_path('module', 'hitsa_contacts') . '/theme',
    'variables' => array(
      'nodes' => NULL,
      'contact_form' => NULL,
    ),
  );
  
  $items['contacts_page_contact_form'] = array(
    'render element' => 'form',
    'template' => 'hitsa-contact-form',
    'path' => drupal_get_path('module', 'hitsa_contacts') . '/theme',
  );
  
  return $items;
}

function hitsa_contacts_preprocess(&$vars, $hook) {
  switch($hook) {
    case 'views_view':
      if(!empty($vars['display_id']) && $vars['display_id'] === 'contacts_page') {
        // Get "Contact Us" form.
        $contact_us_webform_nid = variable_get('hitsa_contacts_contact_us_webform_nid');
        $contact_us_webform = module_invoke('webform', 'block_view', 'client-block-' . $contact_us_webform_nid);
        $vars['attachment_after'] = render($contact_us_webform['content']);
      }
      break;
  }
}