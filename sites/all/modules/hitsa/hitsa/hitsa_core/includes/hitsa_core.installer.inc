<?php

function hitsa_core_installer($module, $type) {
  // Check for available functions
  foreach(_hitsa_core_installer_types() as $installer_type) {
    if(function_exists('_' . $module . '_' . $installer_type)) {
      $installer_input = '_' . $module . '_' . $installer_type;
      if($type === 'install') {
        $installer_function = 'hitsa_core_add_' . $installer_type;
      } else if($type === 'uninstall') {
        $installer_function = 'hitsa_core_delete_' . $installer_type;
      } else {
        return;
      }
      if(function_exists($installer_function)) $installer_function($installer_input());
    }
  }
}

function hitsa_core_delete_nodes($content_type) {
  $sql = 'SELECT nid FROM {node} n WHERE n.type = :type';
  $result = db_query($sql, array(':type' => $content_type));
  $node_ids = array();
  foreach ($result as $row) {
    $node_ids[] = $row->nid;
  }
  node_delete_multiple($node_ids); // Delete all nodes
  node_type_delete($content_type); // Delete content type
}

function _hitsa_core_installer_types() {
  return array(
    'vocabularies',
    'paragraphs',
    'fields',
    'field_instances',
    'menus',
    'menu_links',
    'date_formats',
    'image_styles',
    'roles',
  );
}

/*
* Fields
*/
function hitsa_core_add_fields($installed_fields = array()) {
  foreach ($installed_fields as $field) {
    field_create_field($field);
  }
}

function hitsa_core_add_field_instances($installed_instances = array()) {
  foreach ($installed_instances as $field_instance) {
    $field_instance['entity_type'] = !empty($field_instance['entity_type']) ? $field_instance['entity_type'] : 'node';
    field_create_instance($field_instance);
  }
}

function hitsa_core_delete_fields($installed_fields = array()) {
  foreach (array_keys($installed_fields) as $field) {
      field_delete_field($field);
  }
}

function hitsa_core_delete_field_instances($installed_instances = array()) {
  foreach($installed_instances as $installed_instance) {
    $instances = field_info_instances($installed_instance['entity_type'], $installed_instance['bundle']);
    foreach ($instances as $instance_name => $field_instance) {
      field_delete_instance($field_instance, FALSE);
    }
  }
}

/*
* Vocabularies
*/
function hitsa_core_add_vocabularies($installed_vocabularies = array()) {
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

function hitsa_core_delete_vocabularies($installed_vocabularies = array()) {
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
function hitsa_core_add_nodes($installed_nodes = array()) {
  $lang_list = language_list();
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
        
        if(empty($tnid)) {
          node_save($node);
          $tnid = $node->nid; // Set initial tnid.
        }
        
        $node->tnid = $tnid;
        
        $node->status = 0; // Unpublished by default.
        node_save($node);
        
        // Add to menu translation set
        if(!empty($node->menu['mlid'])) {
          $item = menu_link_load($node->menu['mlid']);
          $translation_set->add_item($item, $lang);
          $item['i18n_tsid'] = $translation_set->tsid;
          menu_link_save($item);
        }
      }
      $translation_set->save(TRUE);
    } else {
      $node = (object) $node_data;
      node_object_prepare($node);
      $node->language = !empty($node_data['language']) ? $node_data['language'] : 'et';
      node_save($node);
    }
  }
}

/*
* Paragraphs
*/
function hitsa_core_add_paragraphs($installed_paragraphs = array()) {
  foreach ($installed_paragraphs as $bundle) {
    paragraphs_bundle_save($bundle);
  }
}

function hitsa_core_delete_paragraphs($installed_paragraphs = array()) {
  foreach (array_keys($installed_paragraphs) as $bundle) {
    paragraphs_bundle_delete($bundle);
  }
}


/*
* Menus
*/
function hitsa_core_add_menus($installed_menus = array()) {
  foreach ($installed_menus as $key => $menu) {
    menu_save($menu);
    variable_set($key . '_name', $menu['menu_name']);
  }
}

function hitsa_core_delete_menus($installed_menus = array()) {
  foreach ($installed_menus as $key => $menu) {
    $m = menu_load($menu['menu_name']);
    menu_delete($m);
    variable_del($key . '_name');
  }
}

/*
* Menu links
*/
function hitsa_core_add_menu_links($installed_menu_links = array()) {
  foreach ($installed_menu_links as $link) {
    menu_link_save($link);
  }
}

function hitsa_core_delete_menu_links($installed_menu_links = array()) {
  foreach ($installed_menu_links as $link) {
    menu_link_delete(NULL, $link['link_path']);
  }
}


/*
* Date formats
*/
function hitsa_core_add_date_formats($installed_date_formats = array()) {
  foreach($installed_date_formats as $date_format) {
    db_insert('date_formats')->fields($date_format['format_array'])->execute();
    db_insert('date_format_type')->fields($date_format['type_array'])->execute();
 
    variable_set('date_format_' . $date_format['type_array']['type'], $date_format['format_array']['format']);
  }
}

function hitsa_core_delete_date_formats($installed_date_formats = array()) {
  foreach($installed_date_formats as $date_format) {
    db_delete('date_formats')->condition('format', $date_format['format_array'])->execute();
    db_delete('date_format_type')->condition('type', $date_format['type_array']['type'])->execute();
    
    variable_del('date_format_' . $date_format['type_array']['type']);
  }
}

/*
* Image styles
*/
function hitsa_core_add_image_styles($installed_image_styles = array()) {
  foreach($installed_image_styles as $style_array) {
    $style = image_style_save($style_array['style']);
    $effect = $style_array['effect'];
    $effect['isid'] = $style['isid'];
    image_effect_save($effect);
  }
}

function hitsa_core_delete_image_styles($installed_image_styles = array()) {
  foreach($installed_image_styles as $style_array) {
    $style = image_style_load($style_array['style']['name']);
    image_style_delete($style);
  }
}

/**
 * User roles
 */
function hitsa_core_add_roles($installed_roles = array()) {
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

function hitsa_core_delete_roles($installed_roles = array()) {
  foreach($installed_roles as $name => $permissions) {
    user_role_delete($name);
  }
}