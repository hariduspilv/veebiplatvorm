<?php
/**
 * @file
 * Views plugin for argument default value.
 */

/**
 * Default argument plugin to return current page menu trail.
 */
class menu_reference_plugin_argument_default_menu_trail extends views_plugin_argument_default {
  function option_definition() {
    $options = parent::option_definition();
    $options['allowed_menu'] = array('default' => '');
    $options['depth'] = array('default' => 9);
    $options['include_front'] = array('default' => TRUE);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['allowed_menu'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Allowed menus'),
      '#options' => menu_get_menus(TRUE),
      '#default_value' => is_array($this->options['allowed_menu']) ? array_filter($this->options['allowed_menu']) : array(),
      '#description' => t('Determine menu reference only in selected options. If you don\'t choose any option all available menus will be used to determine active trail.'),
    );
    $form['depth'] = array(
      '#type' => 'select',
      '#title' => t('Depth'),
      '#options' => array(0 => t('0 (only current item)'), 1 => 1, 2 => 2, 3 => 3, 4 => 4, 5 => 5, 6 => 6, 7 => 7, 8 => 8, 9 => 9),
      '#default_value' => $this->options['depth'],
      '#description' => t('Set how deep in active trail should be menu reference determined. (Default: <em>9</em>, up to deepest level in menu hierarchy)'),
    );
    $form['include_front'] = array(
      '#type' => 'checkbox',
      '#title' => t('Include front page link in active trail'),
      '#default_value' => $this->options['include_front'],
      '#description' => t('Check this option if you want to include front page link in active menu trail to determine menu reference.'),
    );
  }

  function get_argument() {
    $allowed_menu = is_array($this->options['allowed_menu']) ? array_filter($this->options['allowed_menu']) : array();
    $depth = $this->options['depth'];
    $include_front = $this->options['include_front'];
    $current_path = $_GET['q'];
    $menu_links = $this->get_menu_links_by_path($current_path, $allowed_menu);

    $mlids_priority = array();
    foreach ($menu_links as $link) {
      $mlids_priority[0][] = $link->mlid;
      for($l = $depth; $l > 0; $l--) {
        $key = 'p' . $l;
        if($link->{$key} > 0 && $link->mlid != $link->{$key}) {
          $mlids_priority[$l][] = $link->{$key};
        }
      }
    }

    if ($include_front) {
      $menu_front_links = $this->get_menu_links_by_path('<front>', $allowed_menu);
      foreach ($menu_front_links as $link) {
        $mlids_priority[99][] = $link->mlid;
      }
    }

    $mlids = array();
    foreach ($mlids_priority as $set) {
      foreach ($set as $item) {
        $mlids[] = $item;
      }
    }

    foreach ($mlids as $key => $value) {
      $result = db_select($this->argument->table)
               ->fields($this->argument->table, array($this->argument->field))
               ->condition($this->argument->field, $value, '=')
               ->execute()
               ->fetchAssoc();
      if (empty($result[$this->argument->field])) {
        unset($mlids[$key]);
      }
    }

    if(!empty($mlids)) {
      reset($mlids);
      return current($mlids);
    } else {
      return NULL;
    }
  }

  function get_menu_links_by_path($path, $allowed_menu = array()) {
    static $menu_links_by_path;

    if (isset($menu_links_by_path[$path])) {
      $result = $menu_links_by_path[$path];
    } else {
      $query = db_select('menu_links')
        ->fields('menu_links', array('mlid', 'p1', 'p2', 'p3', 'p4', 'p5', 'p6', 'p7', 'p8', 'p9'))
        ->condition('link_path', $path, '=')
        ->orderBy('mlid', 'DESC');

      if(!empty($allowed_menu)) {
        $query->condition('menu_name', $allowed_menu, 'IN');
      }

      $result = $menu_links_by_path[$path] = $query->execute()->fetchAll();
    }

    return $result;
  }
}
