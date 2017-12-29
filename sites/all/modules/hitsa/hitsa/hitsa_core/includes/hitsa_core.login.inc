<?php

require_once __DIR__.'/id/include/conf.php';
require_once __DIR__.'/id/include/functions.php';
require_once __DIR__.'/id/include/DigiDocService.php';

function hitsa_core_id_login_form($form, &$form_state, $type) {
  
  $form['#login_type'] = $type;
  
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Username') . ':',
    '#required' => TRUE,
    '#weight' => -10,
    '#description' => t('* marked fields are required.')
  );
  
  $form['log_in'] = array(
    '#type' => 'submit',
    '#value' => t('Log in'),
    '#weight' => 0,
    '#attributes' => array(
      'class' => array('btn btn-filled sm-stretch'),
    ),
  );
  
  if($type === 'mobile') {
    $form['#theme'] = 'hitsa_login_mobile_id_form';
    
    $form['log_in']['#ajax'] = array(
      'callback' => 'hitsa_core_id_login_get_control_code',
      'wrapper' => 'hitsa-core-id-login-form-mobile',
      'method' => 'replace',
    );
    
    //$form['#attached']['js'] = array(drupal_get_path('module', 'hitsa_core') . '/includes/id/hitsa_core_check_status.js');
  }
  
  return $form;
}

function hitsa_core_id_login_form_submit($form, &$form_state) {
  // Do magic here
  $username = !empty($form_state['values']['name']) ? $form_state['values']['name'] : NULL;
  $login_type = $form['#login_type'];

  if($login_type === 'card') {
    hitsa_core_id_card_login($username);
  } else if($login_type === 'mobile') {
    hitsa_core_id_dds($form_state);
  }
}

function hitsa_core_id_card_login($username) {
    global $user;
    //@$_SERVER['REDIRECT_SSL_CLIENT_VERIFY'] = 'SUCCESS'; // REMOVE AFTER TESTING
    //@$_SERVER['REDIRECT_SSL_CLIENT_S_DN_CN']='PERE,EES,123456789'; // REMOVE AFTER TESTING
    if (!$user->uid) { // Anonymous user
      // @TODO: Testing this I found that the value was in REDIRECT_SSL_CLIENT_VERIFY instead of SSL_CLIENT_VERIFY, maybe should check both?
      if (@$_SERVER['REDIRECT_SSL_CLIENT_VERIFY'] == 'SUCCESS') {
            if ($_SERVER['REDIRECT_SSL_CLIENT_S_DN_CN']) {
                // Extract the ID Code from SSL_CLIENT_S_DN_CN
                list($lastname, $firstname, $id_code) = explode(',', $_SERVER['REDIRECT_SSL_CLIENT_S_DN_CN']);
                
                if($account = user_load_by_name($username) && !empty($account->field_personal_id_code)) { // User exists & ID code is set
                  $user_id_code = $account->field_personal_id_code[LANGUAGE_NONE][0]['value'];
                  if($id_code === $user_id_code) { // ID Code matches the user's ID code, log the user in.
                    $uid = array('uid' => $account->uid);
                    user_login_submit(array(), $uid);
                    drupal_goto('<front>');
                  } else {
                    drupal_set_message(t('Authentication failed!'), 'error');
                  }
                } else {
                  drupal_set_message(t('Authentication failed!'), 'error');
                }
            } else {
                // @TODO: ID code could also be extracted from another $_SERVER value
                // @TODO: Explain the error a bit better
                drupal_set_message(t('Authentication failed!'), 'error');
            }
      } else {
          drupal_set_message(t('Authentication failed!'), 'error');
      }
    }

    return '';
}

function hitsa_core_id_dds(&$form_state) {
  $dds = DigiDocService::Instance();
  
  $username = !empty($form_state['values']['name']) ? $form_state['values']['name'] : NULL;
  if($account = user_load_by_name($username)) {
    $tel_no = !empty($account->field_phone_nr) ? $account->field_phone_nr[LANGUAGE_NONE][0]['value'] : NULL;
    $idcode = !empty($account->field_personal_id_code) ? $account->field_personal_id_code[LANGUAGE_NONE][0]['value'] : NULL;
  }
  
  if(!empty($tel_no) && !empty($idcode)) {
    try{
    	$params = array(
    		"IDCode" => $idcode,
    		"CountryCode" => "", 
    		"PhoneNo" => $tel_no, 
    		"Language" => DDS_LANG,
    		"ServiceName" => DDS_MID_SERVICE_NAME,
    		"MessageToDisplay" => DDS_MID_INTRODUCTION_STRING, 
    		"SPChallenge" => getToken(10),
    		"MessagingMode" => "asynchClientServer", 
    		"AsyncConfiguration" => NULL, 
    		"ReturnCertData" => FALSE, 
    		"ReturnRevocationData" => FALSE
    	);
    	
    	$result = $dds->MobileAuthenticate($params);
    	
    	$form_state['mobile_authenticate'] = $result;
    	$form_state['mobile_authenticate']['user'] = $account->uid;
    	
    } catch (Exception $e) {
    	$code = $e->getCode();
    	$message = (!!$code ? $code . ': ' : '') . $e->getMessage();
    	watchdog('hitsa_core_id_login', $message);
    	$errormsg = $message;
    	$stage="error";
    }
  } else {
    drupal_set_message(t('Authentication failed!'), 'error');
  }
}

function hitsa_core_id_login_get_control_code($form, &$form_state) {
  // Mobile authentication
  if(!empty($form_state['mobile_authenticate']) && $form_state['mobile_authenticate']['Status'] === 'OK') {
    $challenge_id = $form_state['mobile_authenticate']['ChallengeID'];
    $form_state['challenge_id'] = $challenge_id;
    $form_state['rebuild'] = TRUE;
    
    // Show challenge ID
    if(!empty($challenge_id)) {
      $form['challenge_id'] = array(
        '#weight' => -5,
        '#markup' => sprintf('%s: <b>%s</b>', t('Control code'), $challenge_id),
      );
      
      $_SESSION['mobiil_id'] = $form_state['mobile_authenticate'];
      
      drupal_add_js(
        array(
          'hitsaMobileIdStatus' => array(
            'status' => 'ok',
            'status_ok' => t('Answer received!'),
          ),
        ), 'setting'
      );
    }
  }

  return $form;
}

function hitsa_core_check_id_status() {
  $dds = DigiDocService::Instance();
  
  $response = (object) array('status' => 'none');
  try{
    if (!empty($_SESSION['mobiil_id']['Sesscode'])) {
	  	$sid = intval($_SESSION['mobiil_id']['Sesscode']);
	  	$result = $dds->GetMobileAuthenticateStatus(array("Sesscode" => $sid, "WaitSignature" => false));
	  	$result['Status'] == 'USER_AUTHENTICATED' ? $stage="authenticated" :	$stage="progress";
	  	$response = (object) array('status' => $result['Status'], 'sid' => $sid);
	  	
	  	if($result['Status'] === 'USER_AUTHENTICATED') { // Log the user in
	  	  $uid = array('uid' => $_SESSION['mobiil_id']['user']);
        user_login_submit(array(), $uid);
	  	}
	  }
    
  } catch (Exception $e) {
    $code = $e->getCode();
	  $message = (!!$code ? $code . ': ' : '') . $e->getMessage();
  }
  
  drupal_json_output($response);
}