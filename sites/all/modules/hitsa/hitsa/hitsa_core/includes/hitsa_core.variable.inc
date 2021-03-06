<?php

function hitsa_core_variable_info($options) {
  $variable = array();

  $variable['hitsa_fb_link'] = array(
    'title' => t('Facebook link'),
    'group' => 'general_variables',
  );
  $variable['hitsa_fb_api_key'] = array(
    'title' => t('Facebook API key'),
    'group' => 'general_variables',
  );
  $variable['hitsa_google_api_key'] = array(
    'title' => t('Google API key'),
    'group' => 'general_variables',
    'default' => 'AIzaSyBQW5d3aaKFwt_7LaKW683Q8VAcJjv7SbU',
  );
  $variable['dds_endpoint_url'] = array(
    'title' => t('DigiDocService (Mobile ID) Endpoint URL'),
    'group' => 'general_variables',
    'description' =>
      'test-digidocservice - https://tsp.demo.sk.ee/' . '<br>' .
      'live-digidocservice (' . t('to get access, contact sales@sk.ee') . ') - https://digidocservice.sk.ee',
    'default' => 'https://tsp.demo.sk.ee/',
  );
  $variable['dds_service_name'] = array(
    'title' => t('DigiDocService (Mobile ID) Service Name'),
    'group' => 'general_variables',
    'description' => t('Will be displayed to users mobile phones screen during signing process'),
    'default' => 'Testimine',
  );
  $variable['hitsa_initial_path'] = array(
    'title' => t('Hitsa esialgne hosti nimi'),
    'group' => 'general_variables',
    'description' => t('Hitsa esialgne domeeni nimi ennem vahetamist peaks olema kujul sites/domeeninimi'),
  );
  $variable['period_title'] = array(
    'title' => t('Period title'),
    'localize' => TRUE,
    'group' => 'hitsa_core_translation_group',
  );
  // General Contact
  $variable['general_contact_name'] = array(
    'title' => t('Name of institution'),
    'group' => 'header_footer_variables',
  );
  $variable['general_contact_address'] = array(
    'title' => t('Address'),
    'group' => 'header_footer_variables',
  );
  $variable['general_contact_phone_nr'] = array(
    'title' => t('Phone Nr'),
    'group' => 'header_footer_variables',
  );
  $variable['general_contact_email'] = array(
    'title' => t('E-Mail'),
    'group' => 'header_footer_variables',
  );
  // Important contacts
  for($i = 1; $i < 5; $i++) {
    $variable['important_contact_name_' . $i] = array(
      'title' => t('Name'),
      'group' => 'header_footer_variables',
      'localize' => TRUE,
    );

    $variable['important_contact_phone_' . $i] = array(
      'title' => t('Phone Nr.'),
      'group' => 'header_footer_variables',
    );
  }

  // $variable['hitsa_school_place_id'] = array(
  //   'title' => t('Place ID'),
  //   'group' => 'header_footer_variables',
  // );
  // $variable['hitsa_school_place_coords'] = array(
  //   'title' => t('Place Coordinates'),
  //   'group' => 'header_footer_variables',
  // );
  $variable['footer_copyright_notice'] = array(
    'title' => t('Copyright Notice'),
    'group' => 'header_footer_variables',
  );
  $variable['footer_text_area_title'] = array(
    'title' => t('Footer text area title'),
    'group' => 'header_footer_variables',
  );
  $variable['footer_text_area'] = array(
    'title' => t('Footer text area'),
    'group' => 'header_footer_variables',
  );
  $variable['hitsa_site_logo_fid'] = array(
    'title' => t('HITSA Site Logo FID'),
    'group' => 'header_footer_variables',
  );
  $variable['hitsa_fp_image_fid'] = array(
    'title' => t('HITSA Front Page Image FID'),
    'group' => 'header_footer_variables',
  );
  $variable['hitsa_fp_image_height'] = array(
    'title' => t('Front Page Image Area Height'),
    'group' => 'header_footer_variables',
    'type' => 'number',
    'default' => 100,
    'description' => t('Allowed range: 50-100%'),
  );

   $variable['hitsa_maaamet_address'] = array(
     'title' => t('Maa ametist võetud aadress'),
     'description' => 'Kooli võimalikult täpne aadress, aadressi saab alati kontrollida maa ameti lehel <a target = "_blank" href="https://xgis.maaamet.ee/xgis2/page/app/maainfo">Maa amet</a>',
     'group' => 'header_footer_variables'
   );
   $variable['hitsa_maaamet_zoomlevel'] = array(
     'title' => t('Maa ametist võetud mõõtkava'),
     'description' => 'Kaarti suurendamise mõõde näeb kaardil vasakul nurgas, vaikeväärtus 1000 ',
     'group' => 'header_footer_variables',
     'default' => 1000,
   );
   $variable['hitsa_maaamet_comment'] = array(
     'title' => t('Maaameti koha kommentaar'),
     'description' => 'Kaardi koha kommetaar kuvatakse kui minnakse hiirega markeri peale',
     'group' => 'header_footer_variables'
   );

//////////Blokkide pealkirjad

  $variable['front_news_title'] = array(
    'title' => t('News title'),
    'group' => 'block_titles',
    'localize'=> TRUE,
    'default' => t('News'),
  );

  $variable['front_our_stories_title'] = array(
    'title' => t('Our stories title'),
    'group' => 'block_titles',
    'localize'=> TRUE,
    'default' => t('Our stories'),
  );

  $variable['front_events_title'] = array(
    'title' => t('Front page events title'),
    'group' => 'block_titles',
    'localize'=> TRUE,
  );

  $variable['front_catering_title'] = array(
    'title' => t('Front page catering title'),
    'group' => 'block_titles',
    'localize'=> TRUE,
  );

  $variable['front_services_title'] = array(
    'title' => t('Front page services title'),
    'group' => 'block_titles',
    'localize'=> TRUE,
  );

  $variable['front_gallery_title'] = array(
    'title' => t('Front page gallery title'),
    'group' => 'block_titles',
    'localize'=> TRUE,
    'default' => t('Gallery'),
  );

  $variable['footer_left_title'] = array(
    'title' => t('Footer left box title'),
    'group' => 'block_titles',
    'localize'=> TRUE,
    'default' => t('Partners'),
  );

  $variable['footer_middle_title'] = array(
    'title' => t('Footer middle box title'),
    'group' => 'block_titles',
    'localize'=> TRUE,
    'default' => t('General contact'),
  );

  $variable['front_confirmation_title'] = array(
    'title' => t('Front page confirmation box title'),
    'group' => 'block_titles',
    'localize'=> TRUE,
  );

  $variable['footer_right_title'] = array(
    'title' => t('Footer right box title'),
    'group' => 'block_titles',
    'localize'=> TRUE,
    'default' => t('Important contacts'),
  );

  $variable['contact_contact_us_title'] = array(
    'title' => t('Contact page contact title'),
    'group' => 'block_titles',
    'localize'=> TRUE,
    'default' => t('Contact us'),
  );
  $variable['period_title'] = array(
    'title' => t('Calendar right block title'),
    'group' => 'block_titles',
    'localize'=> TRUE,
  );
  return $variable;
}

function hitsa_core_variable_group_info() {
  $groups['general_variables'] = array(
    'title' => t('General variables'),
    'access' => 'administer hitsa page settings',
    'path' => array('admin/hitsa/variables/general'),
  );
  $groups['block_titles'] = array(
    'title' => t('Block titles'),
    'access' => 'administer hitsa page settings',
    'path' => array('admin/hitsa/variables/general'),
  );

  $groups['header_footer_variables'] = array(
    'title' => t('Header & Footer variables'),
    'access' => 'administer hitsa page settings',
    'path' => array('admin/hitsa/variables/header_footer'),
  );

  $groups['hitsa_core_translation_group'] = array(
    'title' => t('Hitsa variables translation group'),
    'access' => 'administer hitsa page settings',
    'description' => t('Here will appear all hitsa variables that are translatable'),
  );

  return $groups;
}

function hitsa_core_variable_type_info() {
  $type['contact'] = array(
    'title' => t('Contact'),
    'multiple' => 'name',
    'type' => 'multiple',
  );

  return $type;
}

/* Site Logo Widget */
function hitsa_core_form_variable_group_form_alter(&$form, &$form_state) {
  if($form['#variable_group_form'] === 'header_footer_variables') {
    _hitsa_core_add_logo_upload_element($form, $form_state); // Site Logo
    _hitsa_core_add_fp_image_upload_element($form, $form_state); // FP Image
    // General contact fieldset
    $form['general_contact'] = array(
      '#type' => 'fieldset',
      '#title' => t('General contact'),
      '#weight' => 0,
      '#collapsible' => FALSE,
      '#collapsed' => FALSE,
    );
    // Move general contact fields under the fieldset.
    $form['general_contact']['general_contact_name'] = $form['general_contact_name'];
    $form['general_contact']['general_contact_address'] = $form['general_contact_address'];
    $form['general_contact']['general_contact_phone_nr'] = $form['general_contact_phone_nr'];
    $form['general_contact']['general_contact_email'] = $form['general_contact_email'];
    unset($form['general_contact_name']);
    unset($form['general_contact_address']);
    unset($form['general_contact_phone_nr']);
    unset($form['general_contact_email']);

    // Important contacts fieldset
    $form['important_contacts'] = array(
      '#type' => 'fieldset',
      '#title' => t('Important contacts'),
      '#weight' => 1,
      '#collapsible' => FALSE,
      '#collapsed' => FALSE,
    );

    for($i = 1; $i < 5; $i++) {
      $form['important_contacts']['important_contact_name_' . $i] = $form['important_contact_name_' . $i];
      $form['important_contacts']['important_contact_phone_' . $i] = $form['important_contact_phone_' . $i];
      $form['important_contacts']['important_contact_name_' . $i]['#prefix'] = '<div class="contact-row">';
      $form['important_contacts']['important_contact_phone_' . $i]['#suffix'] = '</div>';
      unset($form['important_contact_name_' . $i]);
      unset($form['important_contact_phone_' . $i]);
    }
    if(isset($form['footer_text_area'])){
      $form['footer_text_area']['#type'] = 'text_format';
      $text_area_content = variable_get('footer_text_area');
      if(!empty($text_area_content['value'])){
        $area_value = $text_area_content['value'];
      }
      else{
        $area_value='';
      }
      $form['footer_text_area']['#default_value'] = $area_value;
      $form['#submit'][] = 'footer_text_area_submit';
    }

    $form['#submit'][] = 'footer_map_submit';
    drupal_add_css('.contact-row > * {display:inline-block;} .img-stretch {max-width: 100%;}', 'inline');

    // Gmap picker
    // $form['gmap_picker'] = array(
    //   '#markup' => theme('gmap_picker'),
    //   '#weight' => 2,
    // );

    // // Hide the school place element
    // $form['hitsa_school_place_id']['#attributes']['style'] = 'display:none;';
    // $form['hitsa_school_place_id']['#title_display'] = 'invisible';
    // $form['hitsa_school_place_id']['#theme_wrappers'] = array();
    // // Hide the school coords element
    // $form['hitsa_school_place_coords']['#attributes']['style'] = 'display:none;';
    // $form['hitsa_school_place_coords']['#title_display'] = 'invisible';
    // $form['hitsa_school_place_coords']['#theme_wrappers'] = array();

    // Front page hero banner height
    if(isset($form['hitsa_fp_image_height'])) {
      //dpm($form);
      $form['hitsa_fp_image_height']['#attributes'] = array(
        ' type' => 'number',
        ' min' => 50,
        ' max' => 100,
      );
      $form['hitsa_fp_image_height']['#field_suffix'] = '<span class="field-suffix">%</span>';

      $form['hitsa_fp_image_height']['#weight'] = $form['hitsa_fp_image_widget']['#weight'] + 1;
    }
  }
  if($form['#variable_group_form'] === 'general_variables') {
    _hitsa_core_add_favicon_upload_element($form, $form_state);
  }
}

function _hitsa_core_add_logo_upload_element(&$form, &$form_state) {
  $site_logo_fid = variable_get_value('hitsa_site_logo_fid');
  $file = $site_logo_fid !== NULL ? file_load($site_logo_fid) : FALSE;

  if($file) {
    // Logo preview
    $form['hitsa_site_logo_preview'] = array(
      '#type' => 'item',
      '#title' => t('Site Logo'),
      '#markup' => '<img class="img-stretch" src="' . file_create_url($file->uri) . '"></img>',
      '#weight' => -100,
    );
  }

  // Logo upload
  $form['hitsa_site_logo_widget'] = array(
    '#name' => 'files[hitsa_site_logo]',
    '#title' => t('Upload Logo Image'),
    '#type' => 'file',
    '#weight' => -99,
  );
  $form['#validate'][] = 'hitsa_core_site_logo_validate';
  $form['#submit'][] = 'hitsa_core_site_logo_submit';

  // Hide FID field
  if(!empty($form['hitsa_site_logo_fid'])) {
    $form['hitsa_site_logo_fid']['#access'] = FALSE;
  }
}

function hitsa_core_site_logo_validate($form, &$form_state) {

  $validators = array(
   'file_validate_is_image' => array(),
   'file_validate_extensions' => array('png jpg jpeg'),
   'file_validate_size' => array(1024*1024),
  );

  // Save file as temporary
  $file = file_save_upload('hitsa_site_logo', $validators, 'public://', FILE_EXISTS_RENAME);

  if($file) {
    $form_state['files']['hitsa_site_logo_fid'] = $file;
  }
}

function hitsa_core_site_logo_submit($form, &$form_state) {
  // Permamently save the file.
  if(!empty($form_state['files']['hitsa_site_logo_fid'])) {
    $file = $form_state['files']['hitsa_site_logo_fid'];
    $file->status = FILE_STATUS_PERMANENT;
    $file = file_save($file);
    variable_set_value('hitsa_site_logo_fid', $file->fid);
  }
}

function _hitsa_core_add_fp_image_upload_element(&$form, &$form_state) {
  $site_logo_fid = variable_get_value('hitsa_fp_image_fid');

  $file = $site_logo_fid !== NULL ? file_load($site_logo_fid) : FALSE;

  if($file) {
    // FP Image preview
    $form['hitsa_fp_image_preview'] = array(
      '#type' => 'item',
      '#title' => t('Front Page Image'),
      '#markup' => '<img class="img-stretch" src="' . file_create_url($file->uri) . '"></img>',
      '#weight' => -98,
    );
  }

  // FP Image upload
  $form['hitsa_fp_image_widget'] = array(
    '#name' => 'files[hitsa_fp_image]',
    '#title' => t('Upload Front Page Image'),
    '#description' => t('Front page hero banner maximum file size 10MB'),
    '#type' => 'file',
    '#weight' => -97,
  );
  $form['#validate'][] = 'hitsa_core_fp_image_validate';
  $form['#submit'][] = 'hitsa_core_fp_image_submit';

  // Hide FID field
  if(!empty($form['hitsa_fp_image_fid'])) {
    $form['hitsa_fp_image_fid']['#access'] = FALSE;
  }
}

function hitsa_core_fp_image_validate($form, &$form_state) {

  $validators = array(
   'file_validate_is_image' => array(),
   'file_validate_extensions' => array('png jpg jpeg'),
   'file_validate_size' => array(1024*1024*10),
  );

  // Save file as temporary
  $file = file_save_upload('hitsa_fp_image', $validators, 'public://', FILE_EXISTS_RENAME);

  if($file) {
    $form_state['files']['hitsa_fp_image_fid'] = $file;
  }
}

function hitsa_core_fp_image_submit($form, &$form_state) {
  // Permamently save the file.
  if(!empty($form_state['files']['hitsa_fp_image_fid'])) {
    $file = $form_state['files']['hitsa_fp_image_fid'];
    $file->status = FILE_STATUS_PERMANENT;
    $file = file_save($file);
    variable_set_value('hitsa_fp_image_fid', $file->fid);
  }
}

// Favicon upload
function _hitsa_core_add_favicon_upload_element(&$form, &$form_state) {
  $theme_settings = variable_get('theme_hitsa_settings', array());

  $form_state['theme_settings'] = $theme_settings;

  $form['favicon'] = array(
    '#type' => 'fieldset',
    '#title' => t('Favicon'),
    '#weight' => -1,
  );

  if(!empty($theme_settings['favicon_path']) && file_exists($theme_settings['favicon_path'])) {
    // FP Image preview
    $form['favicon']['preview'] = array(
      '#type' => 'item',
      '#title' => t('Current'),
      '#markup' => '<img src="' . file_create_url($theme_settings['favicon_path']) . '"></img>',
      '#weight' => -98,
    );
  }

  // Favicon Image upload
  $form['favicon']['upload'] = array(
    '#name' => 'files[hitsa_favicon]',
    '#title' => t('Upload new'),
    '#type' => 'file',
    '#weight' => -97,
  );

  $form['#validate'][] = 'hitsa_core_favicon_validate';
  $form['#submit'][] = 'hitsa_core_favicon_submit';
}

function hitsa_core_favicon_validate($form, &$form_state) {
  $validators = array(
   'file_validate_extensions' => array('ico'),
   'file_validate_size' => array(1024*10),
  );
  // File uploaded
  if($file = file_save_upload('hitsa_favicon', $validators, 'public://', FILE_EXISTS_RENAME)) {
    $form_state['favicon_uploaded'] = $file;
  }
}

function hitsa_core_favicon_submit($form, &$form_state) {
  if(!empty($form_state['favicon_uploaded'])) {
    $favicon = $form_state['favicon_uploaded'];

    $favicon->status = 1;
    file_save($favicon);
    $theme_settings = $form_state['theme_settings'];

    $favicon_settings = array(
      'default_favicon' => 0,
      'fid' => $favicon-> fid,
      'toggle_favicon' => 1,
      'favicon_path' => $favicon->uri,
      'favicon_mimetype' => $favicon->filemime,
    );

    $theme_settings = array_merge($theme_settings, $favicon_settings);
    variable_set('theme_hitsa_settings', $theme_settings);
  }
}
function footer_text_area_submit($form,&$form_state){
  if(!empty($form_state['values']['footer_text_area'])){
    variable_set('footer_text_area',$form_state['values']['footer_text_area']);
  }
}
function footer_map_submit($form,&$form_state){

  if(!empty($form_state)){
    if(!empty($form_state['input'])) {
      if(!empty($form_state['input'][ 'hitsa_maaamet_address'])){
        hitsa_core_get_coordinates($form_state[ 'input']['hitsa_maaamet_address'],'footer');
      }
      else{
        hitsa_core_clear_map('hitsa_maaamet_json_footer');
      }
    }
  }
}
