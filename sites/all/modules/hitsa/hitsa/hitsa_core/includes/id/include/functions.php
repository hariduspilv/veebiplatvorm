<?php

/**
 * Logging helper method. Logging that is done through this method can be turned of by setting the constant
 * LOGGING_ON to FALSE.
 *
 * @param $message - Message to be logged.
 */
	function debug_log ($message) {
		error_log('[' . $_REQUEST['requestId'] . '] [' . session_id() . '] ' . $message);
	}

    function generateRandomString($length) {
		$characters = '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ';
		$charactersLength = strlen($characters);
		$randomString = "";
		for ($i = 0; $i < $length; $i++) {
			$randomString .= $characters[rand(0, $charactersLength - 1)];
		}
		return $randomString;
	}

    function getToken($length){
		$token = "";
		$token=strToHex(generateRandomString($length));
		return $token;
    }
	
	function strToHex($string){
		$hex = '';
		for ($i=0; $i<strlen($string); $i++){
			$ord = ord($string[$i]);
			$hexCode = dechex($ord);
			$hex .= substr('0'.$hexCode, -2);
		}
		return strToUpper($hex);
	}
	
	function hexToStr($hex){
		$string='';
		for ($i=0; $i < strlen($hex)-1; $i+=2){
			$string .= chr(hexdec($hex[$i].$hex[$i+1]));
		}
		return $string;
	}