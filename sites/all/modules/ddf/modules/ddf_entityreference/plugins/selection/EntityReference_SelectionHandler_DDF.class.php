<?php

/**
 * Entity handler for Views.
 */
class EntityReference_SelectionHandler_DDF extends EntityReference_SelectionHandler_Views {

  private $entity_type = NULL;
  private static $controlling_field_values = array();

  public static function storeControllingFieldValues($values, $entity_type, $entity) {
    $entity_id = 0;
    if (!is_null($entity)) {
      list($entity_id,,) = entity_extract_ids($entity_type, $entity);
      if (empty($entity_id)) {
        $entity_id = 0;
      }
    }
    self::$controlling_field_values[$entity_type][$entity_id] = array();
    foreach ($values as $key => $value) {
      self::$controlling_field_values[$entity_type][$entity_id][$key] = $value;
    }
  }

  /**
   * Implements EntityReferenceHandler::getInstance().
   */
  public static function getInstance($field, $instance = NULL, $entity_type = NULL, $entity = NULL) {
    return new EntityReference_SelectionHandler_DDF($field, $instance, $entity_type, $entity);
  }

  protected function __construct($field, $instance, $entity_type, $entity) {
    $this->field = $field;
    $this->instance = $instance;
    $this->entity_type = $entity_type;
    $this->entity = $entity;
    // Get the entity token type of the entity type.
    $entity_info = entity_get_info($entity_type);
    $this->entity_type_token = isset($entity_info['token type']) ? $entity_info['token type'] : $entity_type;
  }

  /**
   * Implements EntityReferenceHandler::settingsForm().
   */
  public static function settingsForm($field, $instance) {
    $form = parent::settingsForm($field, $instance);

    if (isset($form['view']['args'])) {
      $master_fields = array();
      $other_instances = field_info_instances($instance['entity_type'], $instance['bundle']);
      foreach ($other_instances as $other_instance) {
        if ($other_instance['field_name'] == $instance['field_name']) {
          continue;
        }
        if (($other_instance['widget']['type'] != 'options_select') && ($other_instance['widget']['type'] != 'options_buttons')) {
          continue;
        }
        $other_field = field_info_field($other_instance['field_name']);
        if ($other_field['cardinality'] != 1) {
          continue;
        }
        if (($other_field['type'] === 'entityreference') || (count($other_field['columns']) === 1)) {
          $master_fields[$other_instance['field_name']] = htmlspecialchars($other_instance['label']);
        }
      }
      if (!empty($master_fields)) {
        $dynamic_token_list = '';
        foreach ($master_fields as $master_field_name => $master_field_label) {
          $dynamic_token_list .= '<strong>{' . $master_field_name . '}</strong> - ' . $master_field_label . '<br />';
        }
        $form['view']['dynamic_help'] = array(
          '#type' => 'item',
          '#title' => t('Dynamic arguments'),
          '#description' =>
            t('The list of entities that can be referenced can depend on the current values of other fields. When the user changes these fields, the list is rebuilt.'),
          '#markup' => t('The following dynamic tokens can be used as view arguments:') . '<br />' . $dynamic_token_list,
        );
      }
    }

    return $form;
  }

  /**
   * Implements EntityReferenceHandler::getReferencableEntities().
   */
  public function getReferencableEntities($match = NULL, $match_operator = 'CONTAINS', $limit = 0) {
    $display_name = $this->field['settings']['handler_settings']['view']['display_name'];
    $args = $this->handleArgs($this->field['settings']['handler_settings']['view']['args']);
    $args = $this->handleDynamicArgs($args);
    $result = array();
    if ($this->initializeView($match, $match_operator, $limit)) {
      // Get the results.
      $result = $this->view->execute_display($display_name, (!array_filter($args) ? array() : $args));
    }

    $return = array();
    if ($result) {
      $target_type = $this->field['settings']['target_type'];
      $entities = entity_load($target_type, array_keys($result));
      foreach ($entities as $entity) {
        list($id,, $bundle) = entity_extract_ids($target_type, $entity);
        $return[$bundle][$id] = $result[$id];
      }
    }
    return $return;
  }

  public function validateReferencableEntities(array $ids) {
    $display_name = $this->field['settings']['handler_settings']['view']['display_name'];
    $args = $this->handleArgs($this->field['settings']['handler_settings']['view']['args']);
    $args = $this->handleDynamicArgs($args);
    $result = array();
    if ($this->initializeView(NULL, 'CONTAINS', 0, $ids)) {
      // Get the results.
      $entities = $this->view->execute_display($display_name, $args);
      if (is_null($entities)) {
        $entities = array();
      }
      $result = array_keys($entities);
    }
    return $result;
  }

  /**
   * Handles arguments for views.
   *
   * Replaces tokens using token_replace().
   *
   * @param array $args
   *   Usually $this->field['settings']['handler_settings']['view']['args'].
   *
   * @return array
   *   The arguments to be send to the View.
   */
  protected function handleArgs($args) {
    // Parameters for token_replace().
    $data = array();
    $options = array('clear' => TRUE);

    if ($this->entity) {
      $data = array($this->entity_type_token => $this->entity);
    }
    // Replace tokens for each argument.
    foreach ($args as $key => $arg) {
      $args[$key] = token_replace($arg, $data, $options);
    }
    return $args;
  }

  protected function handleDynamicArgs($args) {
    $dynamic_args = array();
    foreach ($args as $key => $arg) {
      $matches = array();
      if (preg_match('/^\{([^{}]+)\}$/', $arg, $matches)) {
        $dynamic_args[$key] = $matches[1];
      }
    }
    if (empty($dynamic_args)) {
      return $args;
    }

    $entity_id = 0;
    if (!is_null($this->entity)) {
      list($entity_id,,) = entity_extract_ids($this->entity_type, $this->entity);
      if (empty($entity_id)) {
        $entity_id = 0;
      }
    }

    foreach ($dynamic_args as $key => $field_name) {
      $field = field_info_field($field_name);
      if (!$field) {
        $args[$key] = '';
        continue;
      }
      // Workaround for possible Entity reference weirdness with field columns.
      $columns = ($field['type'] === 'entityreference') ? array('target_id') : array_keys($field['columns']);

      if (count($columns) != 1) {
        $args[$key] = '';
        continue;
      }

      $column = $columns[0];
      if ((isset(self::$controlling_field_values[$this->entity_type][$entity_id]))
          && (array_key_exists($field_name, self::$controlling_field_values[$this->entity_type][$entity_id]))) {
        $args[$key] = self::$controlling_field_values[$this->entity_type][$entity_id][$field_name];
      }
      elseif (isset($this->entity->{$field_name})) {
        foreach ($this->entity->{$field_name} as $values) {
          foreach ($values as $value) {
            if (!is_array($value)) {
              $args[$key] = $value;
            }
            elseif (array_key_exists($column, $value)) {
              $args[$key] = $value[$column];
            }
          }
        }
      }
      else {
        $args[$key] = '';
        $instance = field_info_instance($this->instance['entity_type'], $field_name, $this->instance['bundle']);
        $default_values = field_get_default_value($this->instance['entity_type'], $this->entity, $field, $instance);
        if (!empty($default_values)) {
          foreach ($default_values as $value) {
            if (array_key_exists($column, $value)) {
              $args[$key] = $value[$column];
            }
          }
        }
      }
    }
    return $args;
  }

}
