<?php
/**
 * @file
 * This configuration file will be copied across into CKFinder upon enable.
 */

wysiwyg_ckeditor_ckfinder_bridge_boot();

$config['LicenseName'] = variable_get('ckfinder_licence_name', '');
$config['LicenseKey'] = variable_get('ckfinder_licence_key', '');

$_base_url = variable_get('ckfinder_files_location', '/sites/default/files/');
$_base_dir = DRUPAL_ROOT . variable_get('ckfinder_files_location', '/sites/default/files/');

$config['Thumbnails'] = array(
  'url' => $_base_url . '_thumbs',
  'directory' => $_base_dir . '_thumbs',
  'enabled' => TRUE,
  'directAccess' => FALSE,
  'maxWidth' => 100,
  'maxHeight' => 100,
  'bmpSupported' => FALSE,
  'quality' => 80);

/**
 * Set the maximum size of uploaded images. If an uploaded image is larger, it
 * gets scaled down proportionally. Set to 0 to disable this feature.
 */
$config['Images'] = array(
  'maxWidth' => 1600,
  'maxHeight' => 1200,
  'quality' => 80);

/**
 * RoleSessionVar : the session variable name that CKFinder must use to retrieve
 * the "role" of the current user. The "role", can be used in the
 * "AccessControl" settings (below in this page).
 *
 * To be able to use this feature, you must initialize the session data by
 * uncommenting the following "session_start()" call.
 */
$config['RoleSessionVar'] = 'CKFinder_UserRole';

/**
 * AccessControl : used to restrict access or features to specific folders.
 *
 * Many "AccessControl" entries can be added. All attributes are optional.
 * Subfolders inherit their default settings from their parents' definitions.
 *
 * - The "role" attribute accepts the special '*' value, which means
 * "everybody".
 * - The "resourceType" attribute accepts the special value '*', which
 * means "all resource types".
 */

$config['AccessControl'][] = array(
  'role' => '*',
  'resourceType' => '*',
  'folder' => '/',
  'folderView' => TRUE,
  'folderCreate' => TRUE,
  'folderRename' => TRUE,
  'folderDelete' => TRUE,
  'fileView' => TRUE,
  'fileUpload' => TRUE,
  'fileRename' => TRUE,
  'fileDelete' => TRUE);

/**
 * ResourceType : defines the "resource types" handled in CKFinder. A resource
 * type is nothing more than a way to group files under different paths,
 * each one having different configuration settings.
 *
 * Each resource type name must be unique.
 *
 * When loading CKFinder, the "type" querystring parameter can be used to
 * display a specific type only. If "type" is omitted in the URL, the
 * "DefaultResourceTypes" settings is used (may contain the resource type names
 * separated by a comma). If left empty, all types are loaded.
 *
 * maxSize is defined in bytes, but shorthand notation may be also used.
 * Available options are: G, M, K (case insensitive).
 * 1M equals 1048576 bytes (one Megabyte), 1K equals 1024 bytes (one Kilobyte),
 * 1G equals one Gigabyte. Example: 'maxSize' => "8M",
 */
$config['DefaultResourceTypes'] = '';

$config['ResourceType'][] = array(
  'name' => 'Files',
  'url' => $_base_url . 'files',
  'directory' => $_base_dir . 'files',
  'maxSize' => 0,
  'allowedExtensions' => '7z,aiff,asf,avi,bmp,csv,doc,docx,fla,flv,gif,gz,gzip,jpeg,jpg,mid,mov,mp3,mp4,mpc,mpeg,mpg,ods,odt,pdf,png,ppt,pptx,pxd,qt,ram,rar,rm,rmi,rmvb,rtf,sdc,sitd,swf,sxc,sxw,tar,tgz,tif,tiff,txt,vsd,wav,wma,wmv,xls,xlsx,zip',
  'deniedExtensions' => '');

$config['ResourceType'][] = array(
  'name' => 'Images',
  'url' => $_base_url . 'images',
  'directory' => $_base_dir . 'images',
  'maxSize' => "16M",
  'allowedExtensions' => 'bmp,gif,jpeg,jpg,png,avi,iso,mp3',
  'deniedExtensions' => '');

$config['ResourceType'][] = array(
  'name' => 'Flash',
  'url' => $_base_url . 'flash',
  'directory' => $_base_dir . 'flash',
  'maxSize' => 0,
  'allowedExtensions' => 'swf,flv',
  'deniedExtensions' => '');

/**
 * Due to security issues with Apache modules, it is recommended to leave the
 * following setting enabled.
 *
 * How does it work? Suppose the following:
 *
 * - If "php" is on the denied extensions list, a file named foo.php cannot be
 * uploaded.
 * - If "rar" (or any other) extension is allowed, one can upload a file named
 * foo.rar.
 * - The file foo.php.rar has "rar" extension so, in theory, it can be also
 * uploaded.
 *
 * In some conditions Apache can treat the foo.php.rar file just like any PHP
 * script and execute it.
 *
 * If CheckDoubleExtension is enabled, each part of the file name after a dot is
 * checked, not only the last part. In this way, uploading foo.php.rar would be
 * denied, because "php" is on the denied extensions list.
 */
$config['CheckDoubleExtension'] = TRUE;

/**
 * If you have iconv enabled (visit http://php.net/iconv for more information),
 * you can use this directive to specify the encoding of file names in your
 * system. Acceptable values can be found at:
 * http://www.gnu.org/software/libiconv/
 *
 * Examples:
 * $config['FilesystemEncoding'] = 'CP1250';
 * $config['FilesystemEncoding'] = 'ISO-8859-2';
 */
$config['FilesystemEncoding'] = 'UTF-8';

/**
 * Perform additional checks for image files
 * if set to TRUE, validate image size
 */
$config['SecureImageUploads'] = TRUE;

/**
 * Indicates that the file size (maxSize) for images must be checked only
 * after scaling them. Otherwise, it is checked right after uploading.
 */
$config['CheckSizeAfterScaling'] = TRUE;

/**
 * For security, HTML is allowed in the first Kb of data for files having the
 * following extensions only.
 */
$config['HtmlExtensions'] = array('html', 'htm', 'xml', 'js');

/**
 * Folders to not display in CKFinder, no matter their location.
 * No paths are accepted, only the folder name.
 * The * and ? wildcards are accepted.
 */
$config['HideFolders'] = array(".svn", "CVS");

/**
 * Files to not display in CKFinder, no matter their location.
 * No paths are accepted, only the file name, including extension.
 * The * and ? wildcards are accepted.
 */
$config['HideFiles'] = array(".*");

/**
 * After file is uploaded, sometimes it is required to change its permissions
 * so that it was possible to access it at the later time.
 * If possible, it is recommended to set more restrictive permissions,
 * like 0755. Set to 0 to disable this feature.
 * Note: not needed on Windows-based servers.
 */
$config['ChmodFiles'] = variable_get('chmod_files', '0777');

/**
 * See comments above.
 * Used when creating folders that does not exist.
 */
$config['ChmodFolders'] = variable_get('chmod_folders', '0755');

/**
 * Force ASCII names for files and folders.
 * will be automatically converted to ASCII letters.
 */
$config['ForceAscii'] = FALSE;


include_once "plugins/imageresize/plugin.php";
include_once "plugins/fileeditor/plugin.php";

$config['plugin_imageresize']['smallThumb'] = '90x90';
$config['plugin_imageresize']['mediumThumb'] = '120x120';
$config['plugin_imageresize']['largeThumb'] = '180x180';

/**
 * Check Authentication Function.
 *
 * -- Do not remove this line. Required by wysiwyg_ckeditor_ckfinder_bridge module --
 */
function CheckAuthentication() {
  static $authenticated;
  if (!isset($authenticated)) {
    $boot = wysiwyg_ckeditor_ckfinder_bridge_boot();
    if ($boot) {
      global $user;
      $authenticated = user_access('allow CKFinder file uploads') || ($user->uid === 1);
    }
  }
  return $authenticated;
}

/**
 * Run bootstrap.
 */
function wysiwyg_ckeditor_ckfinder_bridge_boot() {

  $return = FALSE;
  if (!empty($_SERVER['SCRIPT_FILENAME'])) {
    $drupal_path = dirname(dirname(dirname(dirname($_SERVER['SCRIPT_FILENAME']))));
    if (!file_exists($drupal_path . '/includes/bootstrap.inc')) {
      $drupal_path = dirname(dirname(dirname($_SERVER['SCRIPT_FILENAME'])));
      $depth = 2;
      do {
        $drupal_path = dirname($drupal_path);
        $depth++;
      } while (!($bootstrap_file_found = file_exists($drupal_path . '/includes/bootstrap.inc')) && $depth < 10);
    }
  }

  if (!isset($bootstrap_file_found) || !$bootstrap_file_found) {
    $drupal_path = '../../../../..';
    if (!file_exists($drupal_path . '/includes/bootstrap.inc')) {
      $drupal_path = '../..';
      do {
        $drupal_path .= '/..';
        $depth = substr_count($drupal_path, '..');
      } while (!($bootstrap_file_found = file_exists($drupal_path . '/includes/bootstrap.inc')) && $depth < 10);
    }
  }

  if (!isset($bootstrap_file_found) || $bootstrap_file_found) {
    $current_cwd = getcwd();
    chdir($drupal_path);
    if (!defined('DRUPAL_ROOT')) {
      define('DRUPAL_ROOT', $drupal_path);
    }
    require_once './includes/bootstrap.inc';
    drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);
    chdir($current_cwd);
    $return = TRUE;
  }

  return $return;
}
