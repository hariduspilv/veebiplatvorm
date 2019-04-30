<?php
/**
 * Implements hook_views_api().
 */
function hitsa_rss_views_api() {

    list($module, $api) = func_get_args();
    if ($module == "views" && $api == "views_default") {
      return array("version" => "3.0");
    }
  }
  
  /** 
   * Implementation of hook_views_default_views().
   */
  function hitsa_rss_views_default_views() {
    foreach (glob(dirname(__FILE__) . "/views/*.inc") as $filename) {
        include_once($filename);
        $views[$view->name] = $view;
      }
      
      return $views;
  
  }