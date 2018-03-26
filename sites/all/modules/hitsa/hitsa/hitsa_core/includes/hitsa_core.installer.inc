<?php

function hitsa_core_installer($module, $type) {
  // Check for available functions
  foreach(_hitsa_core_installer_types() as $installer_type) {
    if(function_exists('_' . $module . '_' . $installer_type)) {
      $installer_input = '_' . $module . '_' . $installer_type;

      if($type === 'install') {
        $installer_function = 'hitsa_core_add_' . $installer_type;
        //print_r('Adding: ' . $installer_type . "\n");
      } else if($type === 'uninstall') {
        $installer_function = 'hitsa_core_delete_' . $installer_type;
        //print_r('Removing: ' . $installer_type . "\n");
      } else {
        return;
      }
      if(function_exists($installer_function)) $installer_function($installer_input(), $module);
    }
  }
}

function _hitsa_core_installer_types() {
  return array(
    'vocabularies',
    'paragraphs',
    'fields',
    'field_instances',
    'field_groups',
    'menus',
    'menu_links',
    'date_formats',
    'image_styles',
    'roles',
    'nodes',
    'path_aliases',
  );
}

/*
* Fields
*/
function hitsa_core_add_fields($installed_fields = array(), $module = NULL) {
  foreach ($installed_fields as $field) {
    if (!empty($field['field_name']) && $field['field_name']=='field_school_selections') {
      module_load_include('module','hitsa_core','hitsa_core');
      $school_type = hitsa_core_get_school_type();
      if ($school_type == 2) {
          $subtypes = array(
              'specialities' => 'Speciality',
              'elective-courses' => 'Elective courses',
              'accommodation' => 'Accommodation',
              'hobby-activity' => 'Hobby activity',
              'sport-facilities' => 'Sport facilities',
              'training-scholarships' => 'Training Scholarships',
              'e-course' => 'E-Course',
              'ordered-trainings' => 'Ordered trainings',
              'certification-exams' => 'Certification exams',
              'cooperation-and-partners' => 'Cooperation and projects',
          );
      } elseif ($school_type == 1) {
          $subtypes = array(
              'subject-fields' => 'Subject field',
              'boarding-school' => 'Boarding school',
              'hobby-groups' => 'Hobby Groups',
              'sport' => 'Sport',
              'cooperation' => 'Cooperation',
          );
      }
      $subtypes['vacancies'] = 'Vacancies';
      $subtypes['catering'] = 'Catering';
      $subtypes['publications'] = 'Publications';
      $subtypes['preparatory-courses'] = 'Preparatory courses';
      $subtypes['publications'] = 'Publications';
      $subtypes['elective-subjects'] = 'Elective subjects';
      $field['settings']['allowed_values'] = $subtypes;
    }
    $field['locked'] = !empty($field['locked']) ? $field['locked'] : TRUE;
    field_create_field($field);
  }
}

function hitsa_core_add_field_instances($installed_instances = array(), $module = NULL) {
  foreach ($installed_instances as $field_instance) {
    $field_instance['entity_type'] = !empty($field_instance['entity_type']) ? $field_instance['entity_type'] : 'node';
    field_create_instance($field_instance);
  }
}

function hitsa_core_delete_fields($installed_fields = array(), $module = NULL) {

  foreach (array_keys($installed_fields) as $field) {
    field_delete_field($field);
  }
}

function hitsa_core_delete_field_instances($installed_instances = array(), $module = NULL) {
  foreach($installed_instances as $installed_instance) {
    $instances = field_info_instances($installed_instance['entity_type'], $installed_instance['bundle']);
    foreach ($instances as $instance_name => $field_instance) {
      field_delete_instance($field_instance, FALSE);
    }
  }
}

/**
 * Field groups
 */
function hitsa_core_add_field_groups($installed_field_groups = array(), $module = NULL) {
  foreach($installed_field_groups as $installed_field_group) {
    field_group_group_save($installed_field_group);
  }
}

function hitsa_core_delete_field_groups($installed_field_groups = array(), $module = NULL) {
  foreach($installed_field_groups as $installed_field_group) {
    field_group_group_export_delete($installed_field_group);
  }
}

/*
* Vocabularies
*/
function hitsa_core_add_vocabularies($installed_vocabularies = array(), $module = NULL) {
  // Create vocabulary
  foreach ($installed_vocabularies as $v) {
    taxonomy_vocabulary_save($v['vocabulary']);

    $vocab = taxonomy_vocabulary_machine_name_load($v['vocabulary']->machine_name);
    if($vocab) {
      variable_set('hitsa_' . $vocab->machine_name . '_vid' , $vocab->vid);
    }
    if(!empty($v['terms']) && $vocab) {
      // Add generic terms
      foreach($v['terms'] as $term) {
        $term->vid = $vocab->vid;
        taxonomy_term_save($term);
      }
    }
  }
}

function hitsa_core_delete_vocabularies($installed_vocabularies = array(), $module = NULL) {
  foreach ($installed_vocabularies as $v) {
    if(!empty($v['vocabulary'])) {
      $vocab = taxonomy_vocabulary_machine_name_load($v['vocabulary']->machine_name);
      variable_del('hitsa_' . $vocab->machine_name . '_vid');
      taxonomy_vocabulary_delete($vocab->vid);
    }
  }
}

/*
* Nodes
*/
function hitsa_core_add_nodes($installed_nodes = array(), $module = NULL) {
  $lang_list = language_list();
  $nid_array = array();

  foreach ($installed_nodes as $node_data) {

    if(is_array($node_data['title'])) { // Multilang nodes
      $tnid = NULL;
      $translation_set = i18n_translation_set_create('menu_link');
      foreach($node_data['title'] as $lang => $title) { // Split into separate language nodes.
        if(!isset($lang_list[$lang])) continue; // Skip disabled languages.

        $node_t = $node_data;
        $node_t['title'] = $title;

        $node = (object) $node_t;
        node_object_prepare($node);
        $node->language = $lang;

        $node->menu['link_title'] = $title;
        $node->menu['enabled'] = 1;
        if(empty($tnid)) {
          node_save($node);
          $tnid = $node->nid; // Set initial tnid.
        }

        $node->tnid = $tnid;
        $node->path['pathauto'] = "1";

        $node->status = 1; // Published by default.
        if($lang=='et'){
          $node->status = 1;
        }
        // Content pages
        if($node_data['type'] === 'content_page') {
          if(!empty($node_data['cp_type'])) {
            $cp_type = $node_data['cp_type'];
            $node->cp_type = array(
              LANGUAGE_NONE => array(
                0 => array(
                  'value' => $cp_type,
                ),
              ),
            );
          }
        }

        node_save($node);
        // Add to menu translation set
        if(!empty($node->menu['mlid'])) {
          $item = menu_link_load($node->menu['mlid']);
          $item['language'] = $lang;
          $translation_set->add_item($item, $lang);
          $item['i18n_tsid'] = $translation_set->tsid;
          $item['customized'] = 1;
          menu_link_save($item);
        }
      }
      $translation_set->save();
    } else {
      $node = (object) $node_data;
      node_object_prepare($node);
      $node->language = !empty($node_data['language']) ? $node_data['language'] : 'et';
      node_save($node);
    }
    if(!empty($node->nid)) {
      $nid_array[] = $node->nid;
    }
  }
  variable_set($module . '_installed_nodes', $nid_array);
}

function hitsa_core_delete_nodes($content_type, $module = NULL) {
  if($installed_nodes = variable_get($module . '_installed_nodes')) { // Delete module specific nodes.
    node_delete_multiple($installed_nodes);
    variable_del($module . '_installed_nodes');
  }
  if(is_string($content_type)) { // Delete module defined content type.
    $sql = 'SELECT nid FROM {node} n WHERE n.type = :type';
    $result = db_query($sql, array(':type' => $content_type));
    $node_ids = array();
    foreach ($result as $row) {
      $node_ids[] = $row->nid;
    }
    node_delete_multiple($node_ids); // Delete all nodes
    node_type_delete($content_type); // Delete content type
  }
}

/*
* Paragraphs
*/
function hitsa_core_add_paragraphs($installed_paragraphs = array(), $module = NULL) {
  foreach ($installed_paragraphs as $bundle) {
    paragraphs_bundle_save($bundle);
  }
}

function hitsa_core_delete_paragraphs($installed_paragraphs = array(), $module = NULL) {
  foreach (array_keys($installed_paragraphs) as $bundle) {
    paragraphs_bundle_delete($bundle);
  }
}


/*
* Menus
*/
function hitsa_core_add_menus($installed_menus = array(), $module = NULL) {
  foreach ($installed_menus as $key => $menu) {
    menu_save($menu);
    variable_set($key . '_name', $menu['menu_name']);
  }
}

function hitsa_core_delete_menus($installed_menus = array(), $module = NULL) {
  foreach ($installed_menus as $key => $menu) {
    $m = menu_load($menu['menu_name']);
    menu_delete($m);
    variable_del($key . '_name');
  }
}

/*
* Menu links
*/
function hitsa_core_add_menu_links($installed_menu_links = array(), $module = NULL) {
  $menu_mlids = array();
  foreach ($installed_menu_links as $link) {
    $menu_type = NULL;
    if(isset($link['hitsa_menu_type'])) {
      $menu_type = $link['hitsa_menu_type'];
      unset($link['hitsa_menu_type']);
    }
    $mlid = menu_link_save($link);
    if($mlid) {
      $menu_mlids[] = $mlid;
    }
    if(isset($menu_type) && $mlid) {
      variable_set("hitsa_" . $menu_type . "_mlid", $mlid);
    }
  }
  if(!empty($menu_mlids)) {
    variable_set($module . '_mlids', $menu_mlids);
  }
}

function hitsa_core_delete_menu_links($installed_menu_links = array(), $module = NULL) {
  $menu_mlids = variable_get($module . '_mlids');
  if(!empty($menu_mlids)) {
    foreach($menu_mlids as $mlid) {
      menu_link_delete($mlid);
    }
  }
  variable_del($module . '_mlids');
  foreach ($installed_menu_links as $link) {
    if($link['hitsa_menu_type']) {
      $menu_type = $link['hitsa_menu_type'];
      variable_del("hitsa_" . $menu_type . "_mlid");
    }
  }
}


/*
* Date formats
*/
function hitsa_core_add_date_formats($installed_date_formats = array(), $module = NULL) {
  foreach($installed_date_formats as $date_format) {
    db_insert('date_formats')->fields($date_format['format_array'])->execute();
    db_insert('date_format_type')->fields($date_format['type_array'])->execute();

    variable_set('date_format_' . $date_format['type_array']['type'], $date_format['format_array']['format']);
  }
}

function hitsa_core_delete_date_formats($installed_date_formats = array(), $module = NULL) {
  foreach($installed_date_formats as $date_format) {
    db_delete('date_formats')->condition('format', $date_format['format_array'])->execute();
    db_delete('date_format_type')->condition('type', $date_format['type_array']['type'])->execute();

    variable_del('date_format_' . $date_format['type_array']['type']);
  }
}

/*
* Image styles
*/
function hitsa_core_add_image_styles($installed_image_styles = array(), $module = NULL) {
  foreach($installed_image_styles as $style_array) {
    $style = image_style_save($style_array['style']);
    // Add effects
    if(!empty($style_array['effect'])) {
      $effect = $style_array['effect'];
      $effect['isid'] = $style['isid'];
      image_effect_save($effect);
    } else if(!empty($style_array['effects'])) {
      $effects = $style_array['effects'];
      foreach($effects as $effect) {
        $effect['isid'] = $style['isid'];
        image_effect_save($effect);
      }
    }
  }
}

function hitsa_core_delete_image_styles($installed_image_styles = array(), $module = NULL) {
  foreach($installed_image_styles as $style_array) {
    $style = image_style_load($style_array['style']['name']);
    image_style_delete($style);
  }
}

/**
 * User roles
 */
function hitsa_core_add_roles($installed_roles = array(), $module = NULL) {
  module_load_include('module', 'user');
  foreach($installed_roles as $name => $permissions) {
    $role = new stdClass();
    $role->name = $name;
    user_role_save($role);

    if($role = user_role_load_by_name($name)) {
      $rid = $role->rid;
      user_role_grant_permissions($rid, $permissions);
    }
  }
}

function hitsa_core_delete_roles($installed_roles = array(), $module = NULL) {
  foreach($installed_roles as $name => $permissions) {
    user_role_delete($name);
  }
}

/**
 * Path aliases
 */
function hitsa_core_add_path_aliases($installed_path_aliases = array(), $module = NULL) {
  foreach($installed_path_aliases as $path => $alias_set) {
    foreach($alias_set as $lang => $path_alias) {
      $alias_array = array('source' => $path, 'alias' => $path_alias, 'language' => $lang);
      path_save($alias_array);
    }
  }
}

function hitsa_core_delete_path_aliases($installed_path_aliases = array(), $module = NULL) {
}
