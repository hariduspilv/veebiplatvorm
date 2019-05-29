<?php

/**
 * @file
 * Create (manually or scheduled) and restore backups of your Drupal MySQL
 * database with an option to exclude table data (e.g. cache_*)
 */

/**
 * Function to update all basic things.
 * Also updates the catering block so it appears where needed.
 */
  function hitsa_core_up_1() {
  $blocks_list = db_select('block', 'b');
  $blocks_list->fields('b');
  $blocks_list->condition('module', 'hitsa_catering');
  $blocks_list->condition('status', 1);
  $blocks_list->condition('pages', '', '!=');
  $results = $blocks_list->execute();
  while ($block = $results->fetchAssoc()) {
    if (!empty($block['pages']) && $block['status'] == 1) {
      $pages = "catering\ncatering-0\ncatering/*\ntoitlustamine\ntoitlustamine-0\ntoitlustamine/*\ncontent/toitlustamine\ncontent/toitlustamine/*\npitanie\npitanie-0\npitanie/*\nпитание";
      db_update('block')
        ->fields(array(
          'pages' => $pages,
        ))
        ->condition('bid', $block['bid'], '=')
        ->execute();
    }
  }
  $main_menu_tree = menu_tree_all_data('hitsa-main-menu');
  $main_menu_links = array();
  foreach ($main_menu_tree as $link) {
    $main_menu_links[$link['link']['title']] = $link;
  }
  if (isset($main_menu_links['Student Life'])) {
    foreach ($main_menu_links['Student Life']['below'] as $link_key => $link) {
      if (!empty($link['link'])) {
        if ($link['link']['link_title'] == 'Catering') {
          if (strpos($link['link']['link_path'], 'node/') !== FALSE) {
            $path_alias = (drupal_get_path_alias($link['link']['link_path']));
            if (strpos($path_alias, 'catering-') !== FALSE) {
              $alias = array(
                'source' => $link['link']['link_path'],
                'alias' => 'catering',
              );
              path_save($alias);
            }
          }
        }
      }
    }
  }
  return TRUE;
  }
  function hitsa_core_up_2(){
    $check_existing = drupal_lookup_path('source','catering');
    $main_menu_tree = menu_tree_all_data('hitsa-main-menu');
    $main_menu_links = array();
    foreach ($main_menu_tree as $link) {
      $main_menu_links[$link['link']['title']] = $link;
    }
    if (isset($main_menu_links['Student Life'])) {
      foreach ($main_menu_links['Student Life']['below'] as $link_key => $link) {
        if (!empty($link['link'])) {
          if ($link['link']['link_title'] == 'Catering') {
            if (strpos($link['link']['link_path'], 'node/') !== FALSE) {
              $path_alias = (drupal_get_path_alias($link['link']['link_path']));

              if (strpos($path_alias, 'catering-') !== FALSE) {
                $alias = array(
                  'source' => $link['link']['link_path'],
                  'alias' => 'catering',
                );
                path_save($alias);
              }
            }
          }
        }
      }
    }
    return TRUE;
  }
  function hitsa_core_up_3(){
    drupal_flush_all_caches();
    drupal_flush_all_caches();
    return TRUE;
  }
 function hitsa_core_up_4(){
    drupal_flush_all_caches();
    drupal_flush_all_caches();
    return TRUE;
  }
