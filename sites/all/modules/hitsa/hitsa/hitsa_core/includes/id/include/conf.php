<?php
               
/**
 * DDS digidoc endpoint URL
 * NB! Change this when going Live
 */
 //define('DDS_ENDPOINT_URL', 'https://digidocservice.sk.ee');       //live-digidocservice (to get access, contact sales@sk.ee)
define('DDS_ENDPOINT_URL', variable_get_value('dds_endpoint_url'));    //test-digidocservice
/**
 * Service name for the MID services in DDS (Will be displayed to users mobile phones screen during signing process)
 */
define('DDS_MID_SERVICE_NAME', variable_get_value('dds_service_name'));

/**
 * Explanatory message for the MID services in DDS. (Will be displayed to users mobile phones screen during signing
 * process)
 */
define('DDS_MID_INTRODUCTION_STRING', '');

/**
 * Directory where the uploaded files are copied and temporary files stored. SHOULD END WITH A DIRECTORY_SEPARATOR!!!
 */
define('UPLOAD_DIRECTORY', realpath(__DIR__ . DIRECTORY_SEPARATOR . '..') . DIRECTORY_SEPARATOR . 'tmp' . DIRECTORY_SEPARATOR);

/**
 * Default language used in MID transactions
 * Possible values: EST / ENG / RUS
 */
define('DDS_LANG', 'ENG');

/**
 * If this is set to TRUE, then all SOAP envelopes used for communication with DigiDocService are logged.
 */
define('LOG_ALL_DDS_REQUESTS_RESPONSES', false);
?>
