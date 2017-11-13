<?php

function hitsa_preprocess_page(&$variables) {
    if ($variables['is_front']) {
      $variables['page']['content']['system_main']['#access'] = FALSE;
    }
  if(module_exists('hitsa_core')) { // Add header and footer
    $variables['header'] = theme('hitsa_header');
    $variables['footer'] = theme('hitsa_footer');
  }
  
  // Include the front page template
  if(drupal_is_front_page()) {
    $variables['front_content'] = theme('hitsa_front_content');
  }
}

function hitsa_preprocess_hitsa_front_content(&$variables) {
  if(module_exists('hitsa_articles')) { // HITSA Articles module
    // Add the "Important article" block
    $query = array('article_type' => 'important', 'range' => array(0, 1));
    $important_nid = hitsa_articles_query_content($query);
    if(!empty($important_nid['node'])) {
      $article_nid = reset($important_nid['node']);
      $important_article = node_load($article_nid->nid);
      $variables['important_article'] = theme('hitsa_important_article', array('node' => $important_article));
    }
  
    // Add news block
    $variables['news_block'] = views_embed_view('hitsa_news', 'news_block');

    // Add our stories block
    $query = array('article_type' => 'our_stories', 'range' => array(0, 2));
    $our_stories_nids = hitsa_articles_query_content($query);
    
    if(!empty($our_stories_nids['node'])) {
      $our_stories_nodes = node_load_multiple(array_keys($our_stories_nids['node']));
      $authors = array();
      foreach($our_stories_nodes as $story_node) {
        $authors[$story_node->uid] = user_load($story_node->uid);
      }
      $variables['our_stories_block'] = theme('hitsa_our_stories_block', array('nodes' => $our_stories_nodes, 'authors' => $authors));
    }
  }
  if(module_exists('hitsa_events')){
    // $block = module_invoke('hitsa_events', 'block_view', 'fornt_page_training');
    
    // $variables['hitsa_training_events'] = render($block['content']);
    // $block = module_invoke('hitsa_events','block_view','fornt_page_events');
    // $variables['hitsa_front_events'] = render($block['content']);
  }
  if(module_exists('hitsa_logos')) { // HITSA Logos module
    // Add awards block
    $variables['awards_block'] = views_embed_view('hitsa_logos', 'awards_block');
  }
}

function hitsa_preprocess_views_view(&$vars) {
  if($vars['view']->name === 'hitsa_search') { // Search page
    $vars['search_query'] = !empty($vars['view']->exposed_input['query']) ? $vars['view']->exposed_input['query'] : '';
    $vars['result_count'] = $vars['view']->total_rows > 0 ? 
      format_plural($vars['view']->total_rows, '1 result found', '@count results found') : t('No results found');
  }
  //dpm($vars);
}

function hitsa_preprocess_views_view_unformatted(&$vars) {
  if($vars['view']->name === 'hitsa_search') {
    dpm($vars);
  }
}

/* Main menu render functions */
function hitsa_menu_tree__hitsa_main_menu($variables) {
  return '<ul class="header-nav_main">' . $variables['tree'] . '</ul>';
}

function hitsa_submenu_tree__hitsa_main_menu($variables) {
  $output = "";
  $output .= '<div class="header-nav_dropdown"><div class="inline"><div class="row"><div class="col-9">';
  $output .= '<h3>' . $variables['parent'] . '</h3>';
  $output .= '<div class="row">';
  
  foreach($variables['submenu'] as $submenu_column) {
    $output .= '<div class="col-4"><ul>';
    foreach($submenu_column as $submenu_link) {
      $output .= render($submenu_link);
    }
    $output .= '</ul></div>';
  }
  $output .= '</div></div></div></div></div>';
  return $output;
}

function hitsa_menu_link__hitsa_main_menu($variables) {
  $element = $variables['element'];
  $sub_menu = '';
  $element['#attributes']['class'] = array();
  if ($element['#below']) {
    $children_mids = array_fill_keys(element_children($element['#below']), TRUE);
    $children = array();
    foreach($element['#below'] as $key => $el) {
      if(isset($children_mids[$key])) {
        $children[$key] = $el;
      }
    }
    $children_split = array_chunk($children, 5);
    $sub_menu = theme('submenu_tree__hitsa_main_menu', array('submenu' => $children_split, 'parent' => $element['#title']));
  } else if($element['#href'] === '<front>' && $element['#original_link']['depth'] === '1') {
    // Hide first level main menu elements without set link and children.
    return '';
  }
  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

/* Header menu render functions */
function hitsa_header_menu_tree__hitsa_header_menu($variables) {
  return '<ul class="bullet-links">' . $variables['tree']['#children'] . '</ul>';
}

/* Quicklinks menu render functions */
function hitsa_quicklinks_menu_tree__hitsa_quicklinks_menu($variables) {
  $fb_link = variable_get_value('hitsa_fb_link');
  
  $fb_link_item = '';
  if(!empty($fb_link)) {
    $fb_link_item = sprintf('<li><a href="%s" target="_blank" class="before-facebook-circle"></a></li>', check_url($fb_link));
  }
  
  return '<ul class="header-quicklinks">' . $variables['tree']['#children'] . $fb_link_item . '</ul>';
}

/* Language switcher render functions */
function hitsa_links__locale_block($variables) {
  $links = $variables['links'];
  $attributes = $variables['attributes'];
  $heading = $variables['heading'];
  global $language_url;
  $output = '';

  if (count($links) > 0) {
    // Treat the heading first if it is present to prepend it to the
    // list of links.
    if (!empty($heading)) {
      if (is_string($heading)) {
        // Prepare the array that will be used when the passed heading
        // is a string.
        $heading = array(
          'text' => $heading,
          // Set the default level of the heading.
          'level' => 'h2',
        );
      }
      $output .= '<' . $heading['level'];
      if (!empty($heading['class'])) {
        $output .= drupal_attributes(array('class' => $heading['class']));
      }
      $output .= '>' . check_plain($heading['text']) . '</' . $heading['level'] . '>';
    }

    $output .= '<ul class="header-quicklinks">';

    $num_links = count($links);
    $i = 1;

    foreach ($links as $key => $link) {
      $class = array($key);

      // Add first, last and active classes to the list of links to help out
      // themers.
      if ($i == 1) {
        $class[] = 'first';
      }
      if ($i == $num_links) {
        $class[] = 'last';
      }
      if (isset($link['href']) && ($link['href'] == $_GET['q'] || ($link['href'] == '<front>' && drupal_is_front_page()))
         && (empty($link['language']) || $link['language']->language == $language_url->language)) {
        $class[] = 'active';
      }
      $output .= '<li' . drupal_attributes(array('class' => $class)) . '>';

      if (isset($link['href'])) {
        $link['title'] = _hitsa_language_abbreviations($link['language']->language);
        
        // Pass in $link as $options, they share the same keys.
        $output .= l($link['title'], $link['href'], $link);
      }
      elseif (!empty($link['title'])) {
        // Some links are actually not links, but we wrap these in <span> for
        // adding title and class attributes.
        if (empty($link['html'])) {
          $link['title'] = check_plain($link['title']);
        }
        $span_attributes = '';
        if (isset($link['attributes'])) {
          $span_attributes = drupal_attributes($link['attributes']);
        }
        $output .= '<span' . $span_attributes . '>' . $link['title'] . '</span>';
      }

      $i++;
      $output .= "</li>\n";
    }
    
    // WIP : Add Global Search
    $output .= '<li><form method="get" action="' . url('search') . '">
                <div class="header-search"><input type="text" name="query" placeholder="' . t('Search') .'">
                <button></button></div></form></li>';

    $output .= '</ul>';
  }

  return $output;
}

function _hitsa_language_abbreviations($lang) {
  switch($lang) {
    case 'et':
      return 'EST';
    case 'ru':
      return 'RUS';
    case 'en':
      return 'ENG';
    default:
      return $lang;
  }
}

/* Footer menu render functions */
function hitsa_menu_tree__hitsa_footer_menu($variables) {
  $links = array();
  foreach($variables['#tree'] as $key => $link) {
    if(substr($key, 0, 1) === '#') continue;
    $links[] = render($link);
  }
  $links_tree = implode(' | ', $links);
  return '<p>' . $links_tree . '</p>';
}

function hitsa_menu_link__hitsa_footer_menu($variables) {
  $element = $variables['element'];
  $sub_menu = '';

  if ($element['#below']) {
    $sub_menu = drupal_render($element['#below']);
  }
  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  return $output . $sub_menu;
}

function hitsa_preprocess_menu_link(&$variables) {
  $hook = $variables['theme_hook_original'];
  
  switch($hook) {
    case 'menu_link__hitsa_header_menu':
      if(isset($variables['element']['#attributes']['class'])) unset($variables['element']['#attributes']['class']);
      break;
  }
}

/* Webform Theme Wrappers */
function hitsa_webform_element($variables) {
  $element = $variables['element'];

  $output = '<div class="col-12"><div ' . drupal_attributes($element['#wrapper_attributes']) . '>' . "\n";
  $prefix = isset($element['#field_prefix']) ? '<span class="field-prefix">' . webform_filter_xss($element['#field_prefix']) . '</span> ' : '';
  $suffix = isset($element['#field_suffix']) ? ' <span class="field-suffix">' . webform_filter_xss($element['#field_suffix']) . '</span>' : '';

  // Generate description for above or below the field.
  $above = !empty($element['#webform_component']['extra']['description_above']);
  $description = array(
    FALSE => '',
    TRUE => !empty($element['#description']) ? ' <div class="form-item_disclaimer">' . $element['#description'] . "</div>\n" : '',
  );

  // If #children does not contain an element with a matching @id, do not
  // include @for in the label.
  if (strpos($element['#children'], ' id="' . $variables['element']['#id'] . '"') === FALSE) {
    $variables['element']['#id'] = NULL;
  }

  switch ($element['#title_display']) {
    case 'inline':
      $output .= $description[$above];
      $description[$above] = '';
      // FALL THRU.
    case 'before':
    case 'invisible':
      $output .= ' ' . theme('form_element_label', $variables);
      $output .= ' ' . $description[$above] . $prefix . $element['#children'] . $suffix . "\n";
      break;

    case 'after':
      $output .= ' ' . $description[$above] . $prefix . $element['#children'] . $suffix;
      $output .= ' ' . theme('form_element_label', $variables) . "\n";
      break;

    case 'none':
    case 'attribute':
      // Output no label and no required marker, only the children.
      $output .= ' ' . $description[$above] . $prefix . $element['#children'] . $suffix . "\n";
      break;
  }

  $output .= $description[!$above];
  $output .= "</div></div>\n";

  return $output;
}

function hitsa_form_element_label($variables) {
  $element = $variables['element'];
  // This is also used in the installer, pre-database setup.
  $t = get_t();

  // If title and required marker are both empty, output no label.
  if ((!isset($element['#title']) || $element['#title'] === '') && empty($element['#required'])) {
    return '';
  }

  // If the element is required, a required marker is appended to the label.
  $required = !empty($element['#required']) ? theme('form_required_marker', array('element' => $element)) : '';

  $title = filter_xss_admin($element['#title']);

  $attributes = array();
  // Style the label as class option to display inline with the element.
  if ($element['#title_display'] == 'after') {
    $attributes['class'] = 'option';
  }
  // Show label only to screen readers to avoid disruption in visual flows.
  elseif ($element['#title_display'] == 'invisible') {
    $attributes['class'] = 'element-invisible';
  }
  if(!empty($attributes['class'])) {
    $attributes['class'] .= ' form-item_title';
  } else {
    $attributes['class'] = 'form-item_title';
  }

  if (!empty($element['#id'])) {
    $attributes['for'] = $element['#id'];
  }
  if($element['#type'] === 'checkbox') {
    return '<span class="label-title">' . $title . '</span>';
  } else {
    // The leading whitespace helps visually separate fields from inline labels.
    return ' <div' . drupal_attributes($attributes) . '>' . $t('!title !required', array('!title' => $title, '!required' => $required)) . "</div>\n";
  }
}

function hitsa_form_element($variables) {
  $element = &$variables['element'];
  // This function is invoked as theme wrapper, but the rendered form element
  // may not necessarily have been processed by form_builder().
  $element += array(
    '#title_display' => 'before',
  );

  // Add element #id for #type 'item'.
  if (isset($element['#markup']) && !empty($element['#id'])) {
    $attributes['id'] = $element['#id'];
  }
  // Add element's #type and #name as class to aid with JS/CSS selectors.
  $attributes['class'] = array('form-item');
  if (!empty($element['#type'])) {
    $attributes['class'][] = 'form-type-' . strtr($element['#type'], '_', '-');
  }
  if (!empty($element['#name'])) {
    $attributes['class'][] = 'form-item-' . strtr($element['#name'], array(' ' => '-', '_' => '-', '[' => '-', ']' => ''));
  }
  // Add a class for disabled elements to facilitate cross-browser styling.
  if (!empty($element['#attributes']['disabled'])) {
    $attributes['class'][] = 'form-disabled';
  }
  
  if($element['#type'] === 'checkbox') {
    $attributes['class'][] = 'customCheckbox';
    $output = '<label><span' . drupal_attributes($attributes) . '>' . "\n";
  } else {
    $output = '<div' . drupal_attributes($attributes) . '>' . "\n";
  }
  

  // If #title is not set, we don't display any label or required marker.
  if (!isset($element['#title'])) {
    $element['#title_display'] = 'none';
  }
  $prefix = isset($element['#field_prefix']) ? '<span class="field-prefix">' . $element['#field_prefix'] . '</span> ' : '';
  $suffix = isset($element['#field_suffix']) ? ' <span class="field-suffix">' . $element['#field_suffix'] . '</span>' : '';
  
  switch ($element['#title_display']) {
    case 'before':
    case 'invisible':
      $output .= ' ' . theme('form_element_label', $variables);
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;

    case 'after':
        $output .= ' ' . $prefix . $element['#children'] . $suffix;
        if($element['#type'] !== 'checkbox') {
          $output .= ' ' . theme('form_element_label', $variables) . "\n";
        }
        
      break;

    case 'none':
    case 'attribute':
      // Output no label and no required marker, only the children.
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;
  }

  if (!empty($element['#description'])) {
    $output .= '<div class="description">' . $element['#description'] . "</div>\n";
  }
  
  if($element['#type'] === 'checkbox') {
    $output .= "</span>" . theme('form_element_label', $variables) . "\n" . "</label>\n";
  } else {
    $output .= "</div>\n";
  }

  return $output;
}

function hitsa_button($variables) {
  $element = $variables['element'];
  $element['#attributes']['type'] = 'submit';
  element_set_attributes($element, array('id', 'name', 'value'));

  $element['#attributes']['class'][] = 'form-' . $element['#button_type'];
  $element['#attributes']['class'][] = 'btn btn-filled'; // HITSA Form element
  if (!empty($element['#attributes']['disabled'])) {
    $element['#attributes']['class'][] = 'form-button-disabled';
  }
  
  return '<input' . drupal_attributes($element['#attributes']) . ' />';
}

function hitsa_container($variables) {
  $element = $variables['element'];
  // Ensure #attributes is set.
  $element += array('#attributes' => array());
  $element['#attributes']['class'][] = 'col-12'; // HITSA Form element
  
  // Special handling for form elements.
  if (isset($element['#array_parents'])) {
    // Assign an html ID.
    if (!isset($element['#attributes']['id'])) {
      $element['#attributes']['id'] = $element['#id'];
    }
    // Add the 'form-wrapper' class.
    $element['#attributes']['class'][] = 'form-wrapper';
  }
  
  return '<div' . drupal_attributes($element['#attributes']) . '>' . $element['#children'] . '</div>';
}

function hitsa_textarea($variables) {
  $element = $variables['element'];
  element_set_attributes($element, array('id', 'name', 'cols', 'rows'));
  _form_set_class($element, array('form-textarea'));

  $wrapper_attributes = array(
    'class' => array('form-textarea-wrapper'),
  );

  // Add resizable behavior.
  if (!empty($element['#resizable'])) {
    drupal_add_library('system', 'drupal.textarea');
    $wrapper_attributes['class'][] = 'resizable';
  }

  //$output = '<div' . drupal_attributes($wrapper_attributes) . '>';
  $output = '<textarea' . drupal_attributes($element['#attributes']) . '>' . check_plain($element['#value']) . '</textarea>';
  //$output .= '</div>';
  return $output;
}

function hitsa_webform_email($variables) {
  $element = $variables['element'];

  // This IF statement is mostly in place to allow our tests to set type="text"
  // because SimpleTest does not support type="email".
  if (!isset($element['#attributes']['type'])) {
    $element['#attributes']['type'] = 'email';
  }

  // Convert properties to attributes on the element if set.
  foreach (array('id', 'name', 'value', 'size') as $property) {
    if (isset($element['#' . $property]) && $element['#' . $property] !== '') {
      $element['#attributes'][$property] = $element['#' . $property];
    }
  }
  _form_set_class($element, array('form-text', 'form-email'));

  return '<input' . drupal_attributes($element['#attributes']) . ' />';
}

function hitsa_checkbox($variables) {
  $element = $variables['element'];
  $element['#attributes']['type'] = 'checkbox';
  element_set_attributes($element, array('id', 'name', '#return_value' => 'value'));

  // Unchecked checkbox has #value of integer 0.
  if (!empty($element['#checked'])) {
    $element['#attributes']['checked'] = 'checked';
  }
  _form_set_class($element, array('form-checkbox'));

  return '<input' . drupal_attributes($element['#attributes']) . ' /><span class="check"></span>';
}