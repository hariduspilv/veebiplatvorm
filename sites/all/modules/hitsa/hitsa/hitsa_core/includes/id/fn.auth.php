<?php
/*

*** Version 2.1, 2015.09
Removed PEAR classes

*/
error_reporting(0);
ini_set('display_errors', '0');
date_default_timezone_set('Europe/Tallinn');
$_REQUEST['requestId'] = uniqid('example.auth.', true);

require_once __DIR__.'/include/conf.php';
require_once __DIR__.'/include/functions.php';
require_once __DIR__.'/include/DigiDocService.php';

session_start();

$dds = DigiDocService::Instance();

$stage="";
$tel_no = isset($_GET["telno"]) ? $_GET["telno"] : "";

$tel_no = trim($tel_no, "+");
$idcode = isset($_GET["idcode"]) ? $_GET["idcode"] : "";
$idcode = trim($idcode);
try{
	if ($tel_no!="") {
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
			"ReturnCertData" => false, 
			"ReturnRevocationData" => FALSE
		);

		$result = $dds->MobileAuthenticate($params);
		$sid=intval($result["Sesscode"]);
		$_SESSION["ChallengeID"]=$result["ChallengeID"];
		$_SESSION["UserIDCode"]=$result["UserIDCode"];
		$_SESSION["UserGivenname"]=$result["UserGivenname"];
		$_SESSION["UserSurname"]=$result["UserSurname"];
		$_SESSION["UserCountry"]=$result["UserCountry"];
		$stage="progress";

	} else {
		if (isset($_GET["sid"])) {
			$sid=intval($_GET["sid"]);
			$result=$dds->GetMobileAuthenticateStatus(array("Sesscode" => $sid, "WaitSignature" => false));
			$result['Status'] == 'USER_AUTHENTICATED' ? $stage="authenticated" :	$stage="progress";
		}
	}
} catch (Exception $e) {
	$code = $e->getCode();
	$message = (!!$code ? $code . ': ' : '') . $e->getMessage();
	debug_log($message);
	
	$errormsg = $message;
	$stage="error";
}
if( isset($_GET['checkStage']) ) {
    // Verificating PIN
    //
    if( $stage == 'error' ) {
        echo json_encode( array('error' => sprintf('<div class="alert alert-error"><p>%s &nbsp;&nbsp;<a href="page-autheticating.php"><b>Start again?</b></a></p></div>', $errormsg)) );
    } else {
        echo json_encode( array('stage' => $stage) );
    }

    exit();
}

if( $stage == 'error' ) {
    echo json_encode( array('error' => sprintf('<div class="alert alert-error"><p>%s</p></div>', $errormsg)) );
    exit();
}

if( $stage == 'authenticated' ) {
    echo json_encode( array('status' => 'OK') );
    exit();
}

if( $stage == 'progress' ) {
    echo json_encode( array_merge($_SESSION, array('timestamp' => date('D H:i', time()), 'sid' => $sid )) );
    exit();
}
