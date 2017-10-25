<?php
/**
 * @file
 * Views filter handler
 */

class menu_references_filter_handler extends views_handler_filter_in_operator {
  var $value_form_type = 'select';
  var $value_options = NULL;

  function construct() {
    parent::construct();
    $this->value_title = t('Menu items');
    $this->value_options = NULL;
  }

  function init(&$view, &$options) {
    parent::init($view, $options);

    // Filter compatibility
     if ($this->operator == '!=') {
      $this->operator = 'not in';
    } else {
      $this->operator = 'in';
    }
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['include_childrens'] = array('default' => FALSE);
    return $options;
  }

  function get_value_options() {
    if (isset($this->value_options)) {
      return;
    }

    if (isset($this->definition['options callback']) && is_callable($this->definition['options callback'])) {
      if (isset($this->definition['options arguments']) && is_array($this->definition['options arguments'])) {
        $this->value_options = call_user_func_array($this->definition['options callback'], $this->definition['options arguments']);
      }
      else {
        $this->value_options = call_user_func($this->definition['options callback']);
      }
    }
    else {
      $menu_list = menu_get_menus(TRUE);
      // Get the allowed menues from the field settings.
      $field_settings = field_info_field($this->definition['field_name']);
      $allowed_menus = array_filter($field_settings['settings']['allowed_menus']);
      $options = array();
      foreach ($allowed_menus as $menu) {
        $options[$menu_list[$menu]] = menu_reference_get_menu_hierarchy($menu);
      }

      $this->value_options = $options;
    }
    return $this->value_options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['include_childrens'] = array(
      '#type' => 'checkbox',
      '#title' => t('Include childrens'),
      '#description' => t('Enable to include child items of selected item(s) in view results.'),
      '#default_value' => $this->options['include_childrens'],
    );
  }

  function value_form(&$form, &$form_state) {
    $form['value'] = array();
    $options = array();

    $this->get_value_options();
    $options += $this->value_options;

    $default_value = (array) $this->value;

    $which = 'all';
    if (!empty($form['operator'])) {
      $source = ($form['operator']['#type'] == 'radios') ? 'radio:options[operator]' : 'edit-options-operator';
    }
    if (!empty($form_state['exposed'])) {
      $identifier = $this->options['expose']['identifier'];

      if (empty($this->options['expose']['use_operator']) || empty($this->options['expose']['operator_id'])) {
        // Exposed and locked.
        $which = in_array($this->operator, $this->operator_values(1)) ? 'value' : 'none';
      }
      else {
        $source = 'edit-' . drupal_html_id($this->options['expose']['operator_id']);
      }

      if (!empty($this->options['expose']['reduce'])) {
        $options = $this->reduce_value_options();

        if (!empty($this->options['expose']['multiple']) && empty($this->options['expose']['required'])) {
          $default_value = array();
        }
      }

      if (empty($this->options['expose']['multiple'])) {
        if (empty($this->options['expose']['required']) && (empty($default_value) || !empty($this->options['expose']['reduce']))) {
          $default_value = 'All';
        }
        elseif (empty($default_value)) {
          $keys = array_keys($options);
          $default_value = array_shift($keys);
        }
        else {
          $copy = $default_value;
          $default_value = array_shift($copy);
        }
      }
    }

    if ($which == 'all' || $which == 'value') {

      if (!empty($form_state['exposed']) && !isset($form_state['input'][$identifier])) {
        $default_value = !empty($default_value) ? $default_value : 'All';
        $form_state['input'][$identifier] = $default_value;
      }

      $form['value'] = array(
        '#type' => 'select',
        '#title' => $this->value_title,
        '#multiple' => TRUE,
        '#size' => 10,
        '#options' => $options,
        '#default_value' => $default_value,
      );

      if ($which == 'all') {
        if (empty($form_state['exposed']) && (in_array($this->value_form_type, array('checkbox', 'checkboxes', 'radios', 'select')))) {
          $form['value']['#prefix'] = '<div id="edit-options-value-wrapper">';
          $form['value']['#suffix'] = '</div>';
        }
        $form['value']['#dependency'] = array($source => $this->operator_values(1));
      }
    }
  }

  function query() {
    $this->value = isset($this->value['value']) ? array($this->value['value']) : $this->value;

    // Get all the subchild mlids if option is set.
    if (!empty($this->options['include_childrens'])) {

      // Get the menues.
      $field_settings = field_info_field($this->definition['field_name']);
      $allowed_menus = array_filter($field_settings['settings']['allowed_menus']);

      foreach ($allowed_menus as $machine_name) {
        $tmp_values = array();
        foreach ($this->value as $value) {
          $childs = menu_reference_get_all_menu_children($value, $machine_name);
          $tmp_values = array_merge($tmp_values, $childs);
        }
        $this->value = array_merge($this->value, $tmp_values);
      }
      // Remove duplicate mlids.
      $this->value = array_unique($this->value);
    }

    $info = $this->operators();
    if (!empty($info[$this->operator]['method'])) {
      $this->{$info[$this->operator]['method']}();
    }
  }


  function admin_summary() {
    if (method_exists($this, 'is_a_group') && $this->is_a_group()) {
      return t('grouped');
    }
    if (!empty($this->options['exposed'])) {
      return t('exposed');
    }
    $info = $this->operators();

    $this->get_value_options();

    if (!is_array($this->value)) {
      return;
    }

    $operator = check_plain($info[$this->operator]['short']);
    $values = '';
    if (in_array($this->operator, $this->operator_values(1))) {
      $flat_options = form_options_flatten($this->value_options, TRUE);

      // Remove every element which is not known.
      foreach ($this->value as $value) {
        if (!isset($flat_options[$value])) {
          unset($this->value[$value]);
        }
      }

      // Choose different kind of ouput for 0, a single and multiple values.
      if (count($this->value) == 0) {
        $values = t('Unknown');
      }
      elseif (count($this->value) == 1) {
        // If any, use the 'single' short name of the operator instead.
        if (isset($info[$this->operator]['short_single'])) {
          $operator = check_plain($info[$this->operator]['short_single']);
        }

        $keys = $this->value;
        $value = array_shift($keys);

        if (isset($flat_options[$value])) {
          $values = check_plain($value);
        }
        else {
          $values = '';
        }
      }
      else {
        foreach ($this->value as $value) {
          if ($values !== '') {
            $values .= ', ';
          }
          if (drupal_strlen($values) > 8) {
            $values .= '...';
            break;
          }
          if (isset($flat_options[$value])) {
            $values .= check_plain($value);
          }
        }
      }
    }

    return $operator . (($values !== '') ? ' ' . $values : '');
  }
}
