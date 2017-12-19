<?php

function hitsa_process_html_tag(&$vars) {
  $el = &$vars['element'];
 
  // Remove type="..." and CDATA prefix/suffix.
  unset($el['#attributes']['type'], $el['#value_prefix'], $el['#value_suffix']);
 
  // Remove media="all" but leave others unaffected.
  if (isset($el['#attributes']['media']) && $el['#attributes']['media'] === 'all') {
    unset($el['#attributes']['media']);
  }
}
function hitsa_preprocess_page(&$variables)
{
    $google_api_key = !empty($key = variable_get_value('hitsa_google_api_key')) ? '&key=' . $key : '';
    drupal_add_js('https://maps.google.com/maps/api/js?sensor=false' . $google_api_key, 'external');
    if ($variables['is_front']) {
        $variables['page']['content']['system_main']['#access'] = FALSE;
    }
    if (module_exists('hitsa_core')) { // Add header and footer
        $variables['header'] = theme('hitsa_header');
        $variables['footer'] = theme('hitsa_footer');
    }

    // Include the front page template
    if (drupal_is_front_page()) {
        $variables['front_content'] = theme('hitsa_front_content');
    }
    if (isset($variables['node'])) {

        // Ref suggestions cuz it's stupid long.
        $suggests = &$variables['theme_hook_suggestions'];

        // Get path arguments.
        $args = arg();
        // Remove first argument of "node".
        unset($args[0]);

        // Set type.
        $type = "page__type_{$variables['node']->type}";

        // Bring it all together.
        $suggests = array_merge(
            $suggests,
            array($type),
            theme_get_suggestions($args, $type)
        );
    }
}

function hitsa_preprocess_hitsa_front_content(&$variables)
{
    if (module_exists('hitsa_articles')) { // HITSA Articles module
        // Add the "Important article" block
        $query = array('article_type' => 'important', 'range' => array(0, 1));
        $important_nid = hitsa_articles_query_content($query);
        if (!empty($important_nid['node'])) {
            $article_nid = reset($important_nid['node']);
            $important_article = node_load($article_nid->nid);
            $variables['important_article'] = theme('hitsa_important_article', array('node' => $important_article));
        }

        // Add news block
        $variables['news_block'] = views_embed_view('hitsa_news', 'news_block');

        // Add our stories block
        $query = array('article_type' => 'our_stories', 'range' => array(0, 2));
        $our_stories_nids = hitsa_articles_query_content($query);

        if (!empty($our_stories_nids['node'])) {
            $our_stories_nodes = node_load_multiple(array_keys($our_stories_nids['node']));
            $authors = array();
            foreach ($our_stories_nodes as $story_node) {
                $authors[$story_node->uid] = user_load($story_node->uid);
            }
            $variables['our_stories_block'] = theme('hitsa_our_stories_block', array('nodes' => $our_stories_nodes, 'authors' => $authors));
        }
    }
    if (module_exists('hitsa_events')) {
        // $block = module_invoke('hitsa_events', 'block_view', 'fornt_page_training');

        // $variables['hitsa_training_events'] = render($block['content']);
        // $block = module_invoke('hitsa_events','block_view','fornt_page_events');
        // $variables['hitsa_front_events'] = render($block['content']);
    }
    if (module_exists('hitsa_logos')) { // HITSA Logos module
        // Add awards block
        $variables['awards_block'] = views_embed_view('hitsa_logos', 'awards_block');
    }
}

function hitsa_preprocess_views_view(&$vars)
{
    if ($vars['view']->name === 'hitsa_search') { // Search page
        $vars['search_query'] = !empty($vars['view']->exposed_input['query']) ? $vars['view']->exposed_input['query'] : '';
        $vars['result_count'] = $vars['view']->total_rows > 0 ?
            format_plural($vars['view']->total_rows, '1 result found', '@count results found') : t('No results found');
    }
    //dpm($vars);
}

function hitsa_preprocess_views_view_unformatted(&$vars)
{
    if ($vars['view']->name === 'hitsa_search') {
    }
}

/* Main menu render functions */
function hitsa_menu_tree__hitsa_main_menu($variables)
{
    return '<ul class="header-nav_main">' . $variables['tree'] . '</ul>';
}

function hitsa_submenu_tree__hitsa_main_menu($variables)
{
    $output = "";

    // Add gallery to "About us" submenu
    if (module_exists('hitsa_gallery')) {
        $about_us_mlid = variable_get('hitsa_about_us_mlid');
        if (!empty($about_us_mlid) && $about_us_mlid == $variables['mlid']) {
            $gallery_teaser = hitsa_gallery_latest_gallery_preview();
            //dpm($gallery_teaser);
        }
    }

    $output .= '<div class="header-nav_dropdown"><div class="inline"><div class="row"><div class="col-' . (!empty($gallery_teaser) ? '9' : '12') . '">';
    $output .= '<h3>' . t($variables['parent']) . '</h3>';
    $output .= '<div class="row">';

    foreach ($variables['submenu'] as $submenu_column) {
        $output .= '<div class="col-3"><ul>';
        foreach ($submenu_column as $submenu_link) {
            $output .= render($submenu_link);
        }
        $output .= '</ul></div>';
    }

    $output .= '</div></div>';

    if (!empty($gallery_teaser)) {
        $output .= $gallery_teaser;
    }

    $output .= '</div></div></div>';
    return $output;
}

function hitsa_service_menu_tree__hitsa_main_menu($variables)
{
    $service_submenu = $variables['element'];
    $output = "";
    $output .= '<div class="header-nav_dropdown"><div class="inline"><div class="row"><div class="col-9">';
    $output .= '<div class="row">';
    foreach ($service_submenu['#below'] as $service_subtype) {
        if (!empty($service_subtype['#below'])) {
            $output .= '<div class="col-4">';
            $output .= '<h3>' . t($service_subtype['#title']) . '</h3>';
            $output .= '<ul>';
            if (!empty($service_subtype['#below'])) {
                foreach ($service_subtype['#below'] as $service) {
                    if (!empty($service['#original_link'])) {
                        $output .= render($service);
                    }
                }
            }
            $output .= '</ul></div>';
        }
    }
    $output .= '</div>';

    $output .= '</div></div></div></div>';

    return $output;
}

/* Mobile main menu render functions */
function hitsa_menu_tree__hitsa_main_menu_mobile($variables)
{
    $output = '';
    foreach ($variables['#tree'] as &$menu_link) {
        if (!isset($menu_link['#href'])) continue;
        $menu_link['#theme'] = 'menu_link__hitsa_main_menu_mobile';
        $output .= render($menu_link);
    }
    return '<ul>' . $output . '</ul>';
}

function hitsa_submenu_tree__hitsa_main_menu_mobile($variables)
{
    $output = "";
    $output .= '<ul>';

    foreach ($variables['submenu'] as $submenu_column) {
        foreach ($submenu_column as $submenu_link) {
            $output .= render($submenu_link);
        }

    }
    $output .= '</ul>';
    return $output;
}

function hitsa_service_menu_tree__hitsa_main_menu_mobile($variables)
{
    $service_submenu = $variables['element'];
    $output = "";
    $output .= '<ul>';
    foreach ($service_submenu['#below'] as $service_subtype) {
        if (!empty($service_subtype['#below'])) {
            $services_output = '';
            foreach ($service_subtype['#below'] as $service) {
                if (!empty($service['#original_link'])) {
                    $services_output .= render($service);
                }
            }
            $output .= '<li><a href="">' . t($service_subtype['#title']) . '</a><ul>' . $services_output . '</ul></li>';
        }
    }
    $output .= '</ul>';
    return $output;
}

function hitsa_menu_link__hitsa_main_menu_mobile($variables)
{
    global $language;

    $element = $variables['element'];

    $sub_menu = '';
    $element['#attributes']['class'] = array();
    $service_menu_mlid = variable_get('hitsa_services_mlid');
    $element['#title'] = t($element['#title']);
    if ($element['#original_link']['mlid'] === $service_menu_mlid) {
        $sub_menu = theme('service_menu_tree__hitsa_main_menu_mobile', array('element' => $element));
        $services_available = FALSE;
        foreach ($element['#below'] as $service_subtype) {
            if (!empty($service_subtype['#below'])) {
                $services_available = TRUE;
            }
        }
        if (!$services_available) {
            return ''; // No services available, hide menu.
        }
    } else if ($element['#below']) {
        $children_mids = array_fill_keys(element_children($element['#below']), TRUE);
        $children = array();
        foreach ($element['#below'] as $key => $el) {
            if (isset($children_mids[$key])) {
                $children[$key] = $el;
            }
        }
        $children_split = array_chunk($children, 5);

        $sub_menu = theme('submenu_tree__hitsa_main_menu_mobile',
            array(
                'submenu' => $children_split,
                'parent' => $element['#title'],
                'mlid' => $element['#original_link']['mlid'],
                'plid' => $element['#original_link']['plid']
            )
        );
    } else if ($element['#href'] === '<front>' && $element['#original_link']['depth'] === '1') {
        // Hide first level main menu elements without set link and children.
        return '';
    }
    $output = l($element['#title'], $element['#href'], $element['#localized_options']);
    return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

/* Sitemap */
function hitsa_menu_tree__hitsa_sitemap($variables)
{
    $menu_tree = '';
    $menu_tree_array = array();
    $service_menu_mlid = variable_get('hitsa_services_mlid');
    foreach ($variables['#tree'] as $mlid => $link) {
        if ($mlid == $service_menu_mlid) {
            foreach ($link['#below'] as $service_subtype) {
                if (!empty($service_subtype['#below'])) {
                    $link['#theme'] = array('menu_link__hitsa_sitemap__service');
                    $menu_tree_array[] = render($link);
                    break;
                }
            }
        } else if (!empty($link['#theme'])) {
            $link['#theme'] = array('menu_link__hitsa_sitemap');
            //$menu_tree .= render($link);
            $menu_tree_array[] = render($link);
        }
    }
    $per_column = ceil(count($menu_tree_array) / 3);
    $menu_tree_array_split = array_chunk($menu_tree_array, $per_column);

    foreach ($menu_tree_array_split as $delta => $menu_tree_column) {
        if ($delta === 0) array_unshift($menu_tree_column, '<h3 class="heading-link"><a href="' . url('<front>') . '">' . t('HOMEPAGE') . '</a></h3>');
        $menu_tree .= '<div class="col-4 sm-12"><div class="sitemap">' . implode($menu_tree_column) . '</div></div>';
    }
    return $menu_tree;
}

/*
* Services block
*/
function hitsa_menu_tree__hitsa_services_block($variables)
{
    $output = '';
    foreach ($variables['#tree'] as $service_subtype) {
        if (!empty($service_subtype['#below'])) {
            $output .= '<h5 class="size-large">' . $service_subtype['#title'] . '</h5>';
            $output .= '<ul class="bullet-links">';
            $service_subtype['#theme'] = 'menu_link__hitsa_services_block';
            $output .= render($service_subtype);
            $output .= '</ul>';
        }
    }
    return '<div data-tab="tab-1">' . $output . '</div>';
}

function hitsa_menu_link__hitsa_services_block($variables)
{
    $output = '';
    $service_subtype = $variables['element'];
    $qty = 0;
    foreach ($service_subtype['#below'] as $service) {
        if (!empty($service['#original_link'])) {
            $link = l($service['#title'], $service['#href'], $service['#localized_options']);
            $output .= '<li' . ((++$qty > 4) ? ' data-show="bullet-list-1"' : '') . '>' . $link . "</li>\n";
        }
    }
    if ($qty > 4) {
        $output .= '<li><div data-toggle="bullet-list-1" class="bullet-list-show_more"><span data-hide="bullet-list-1" class="after-arrow_down">';
        $output .= t('Show more') . ' (' . ($qty - 4) . ')' . '</span><span data-show="bullet-list-1" class="after-arrow_up">';
        $output .= t('Show less') . '</span></div></li>';
    }
    return $output;
}

function hitsa_menu_link__hitsa_sitemap(array $variables)
{
    $element = $variables['element'];
    $sub_menu = '';
    $output = '';

    if (!empty($element['#below']) && $element['#original_link']['plid'] === '0') {
        $sub_menu = drupal_render($element['#below']);
        $output = '<h3>' . t($element['#title']) . '</h3>';
    } else if ($element['#original_link']['plid'] !== '0') {
        $output = l($element['#title'], $element['#href'], $element['#localized_options']);
    }

    return $output . $sub_menu . "\n";
}

function hitsa_menu_link__hitsa_sitemap__service(array $variables)
{
    $element = $variables['element'];

    $output = '';
    $output = '<h3>' . t($element['#title']) . '</h3>';
    $output .= '<ul>';
    if (!empty($element['#below'])) {
        foreach ($element['#below'] as $service_subtype) {
            if (!empty($service_subtype['#below'])) {
                $output .= '<li>';
                $output .= '<span>' . $service_subtype['#title'] . '</span>';
                $output .= '<ul class="bullet-list_article">';
                foreach ($service_subtype['#below'] as $service) {
                    if (!empty($service['#original_link'])) {
                        $output .= render($service);
                    }
                }
                $output .= '</ul></li>';
            }
        }
    }

    $output .= '</ul>';
    return $output . "\n";
}

function hitsa_menu_link__hitsa_main_menu($variables)
{
    global $language;

    $element = $variables['element'];

    $sub_menu = '';
    $element['#attributes']['class'] = array();
    $service_menu_mlid = variable_get('hitsa_services_mlid');
    $element['#title'] = t($element['#title']);
    if ($element['#original_link']['mlid'] === $service_menu_mlid) {
        $sub_menu = theme('service_menu_tree__hitsa_main_menu', array('element' => $element));
        $services_available = FALSE;
        foreach ($element['#below'] as $service_subtype) {
            if (!empty($service_subtype['#below'])) {
                $services_available = TRUE;
            }
        }
        if (!$services_available) {
            return ''; // No services available, hide menu.
        }
    } else if ($element['#below']) {
        $children_mids = array_fill_keys(element_children($element['#below']), TRUE);
        $children = array();
        foreach ($element['#below'] as $key => $el) {
            if (isset($children_mids[$key])) {
                $children[$key] = $el;
            }
        }
        $children_qty = count($children);
        if ($children_qty <= 12) {
            $chunk = 3;
        } else if ($children_qty <= 16) {
            $chunk = 4;
        } else {
            $chunk = 5;
        }
        $children_split = array_chunk($children, $chunk);
        $sub_menu = theme('submenu_tree__hitsa_main_menu',
            array(
                'submenu' => $children_split,
                'parent' => $element['#title'],
                'mlid' => $element['#original_link']['mlid'],
                'plid' => $element['#original_link']['plid']
            )
        );
    } else if ($element['#href'] === '<front>' && $element['#original_link']['depth'] === '1') {
        // Hide first level main menu elements without set link and children.
        return '';
    }
    $output = l($element['#title'], $element['#href'], $element['#localized_options']);
    return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

/* Header menu render functions */
function hitsa_header_menu_tree__hitsa_header_menu($variables)
{
    return '<ul class="bullet-links">' . $variables['tree']['#children'] . '</ul>';
}

/* Quicklinks menu render functions */
function hitsa_quicklinks_menu_tree__hitsa_quicklinks_menu($variables)
{
    $fb_link = variable_get_value('hitsa_fb_link');

    $fb_link_item = '';
    if (!empty($fb_link)) {
        $fb_link_item = sprintf('<li><a href="%s" target="_blank" class="before-facebook-circle"></a></li>', check_url($fb_link));
    }

    return '<ul class="header-quicklinks">' . $variables['tree']['#children'] . $fb_link_item . '</ul>';
}

/* Quicklinks menu render functions */
function hitsa_quicklinks_menu_tree__hitsa_quicklinks_mobile_menu($variables)
{
    $fb_link = variable_get_value('hitsa_fb_link');
    $fb_link_item = '';
    if (!empty($fb_link)) {
        $fb_link_item = sprintf('<li><a href="%s" target="_blank" class="before-facebook-circle">Facebook</a></li>', check_url($fb_link));
    }

    return '<ul>' . $variables['tree']['#children'] . $fb_link_item . '</ul>';
}

/* Language switcher render functions */
function hitsa_links__locale_block($variables)
{
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
            
            if(!empty($link['attributes']['xml:lang'])) {
                $link['attributes']['lang'] = $link['attributes']['xml:lang'];
            }
            
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
            } elseif (!empty($link['title'])) {
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

        $output .= '<li><form method="get" action="' . url('search') . '">
                <div class="header-search"><input type="text" name="query" placeholder="' . t('Search') . '">
                <button></button></div></form></li>';

        $output .= '</ul>';
    }

    return $output;
}

function hitsa_links__mobile_locale_block($variables)
{
    $links = $variables['links'];
    $attributes = $variables['attributes'];
    $heading = $variables['heading'];
    global $language_url;
    $output = '';

    if (count($links) > 0) {

        $output .= '<div class="language">';

        $num_links = count($links);
        $i = 1;
        foreach ($links as $key => $link) {
            if (isset($link['href']) && ($link['href'] == $_GET['q'] || ($link['href'] == '<front>' && drupal_is_front_page()))
                && (empty($link['language']) || $link['language']->language == $language_url->language)) {
                $title = _hitsa_language_abbreviations($link['language']->language);
                $output .= '<div class="language-active">' . $title . '</div>';
            }
        }

        $output .= '<div class="language-more">';
        foreach ($links as $key => $link) {
            $class = array($key);
            
            if(!empty($link['attributes']['xml:lang'])) {
                $link['attributes']['lang'] = $link['attributes']['xml:lang'];
            }
            
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

            if (isset($link['href'])) {
                // Pass in $link as $options, they share the same keys.
                $output .= l($link['title'], $link['href'], $link);
            } elseif (!empty($link['title'])) {
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
        }

        $output .= '</div></div>';
    }

    return $output;
}

function _hitsa_language_abbreviations($lang)
{
    switch ($lang) {
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
function hitsa_menu_tree__hitsa_footer_menu($variables)
{
    $links = array();
    foreach ($variables['#tree'] as $key => $link) {
        if (substr($key, 0, 1) === '#') continue;
        $links[] = render($link);
    }
    $links_tree = implode(' | ', $links);
    return '<p>' . $links_tree . '</p>';
}

function hitsa_menu_link__hitsa_footer_menu($variables)
{
    $element = $variables['element'];
    $sub_menu = '';

    if ($element['#below']) {
        $sub_menu = drupal_render($element['#below']);
    }
    $output = l($element['#title'], $element['#href'], $element['#localized_options']);
    return $output . $sub_menu;
}

function hitsa_preprocess_menu_link(&$variables)
{
    $hook = $variables['theme_hook_original'];

    switch ($hook) {
        case 'menu_link__hitsa_header_menu':
            if (isset($variables['element']['#attributes']['class'])) unset($variables['element']['#attributes']['class']);
            break;
    }
}

/* Webform Theme Wrappers */
function hitsa_form($variables)
{
    $element = $variables['element'];
    if (isset($element['#action'])) {
        $element['#attributes']['action'] = drupal_strip_dangerous_protocols($element['#action']);
    }
    element_set_attributes($element, array('method', 'id'));
    if (empty($element['#attributes']['accept-charset'])) {
        $element['#attributes']['accept-charset'] = "UTF-8";
    }
    // Anonymous DIV to satisfy XHTML compliance.
    return '<form' . drupal_attributes($element['#attributes']) . '><div class="row">' . $element['#children'] . '</div></form>';
}

function hitsa_preprocess_webform_form(&$variables)
{

    $contact_us_webform_nid = variable_get('hitsa_contacts_contact_us_webform_nid');
    // "Contact Us" form
    if ($variables['nid'] === $contact_us_webform_nid) {

        if (!empty($variables['form']['actions']['submit'])) {
            $variables['form']['actions']['submit']['#attributes']['class'] = array('btn btn-filled sm-stretch');
        }
        if (!empty($variables['form']['submitted']['name'])) {
            $variables['form']['submitted']['name']['#wrapper_attributes']['class'][] = 'form-item_half';
        }
        if (!empty($variables['form']['submitted']['e_mail'])) {
            $variables['form']['submitted']['e_mail']['#wrapper_attributes']['class'][] = 'form-item_half';
        }
    }
}

function hitsa_webform_element($variables)
{
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

function hitsa_form_element_label($variables)
{
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
    } // Show label only to screen readers to avoid disruption in visual flows.
    elseif ($element['#title_display'] == 'invisible') {
        $attributes['class'] = 'element-invisible';
    }
    if (!empty($attributes['class'])) {
        $attributes['class'] .= ' form-item_title';
    } else {
        $attributes['class'] = 'form-item_title';
    }

    if (!empty($element['#id'])) {
        $attributes['for'] = $element['#id'];
    }
    if ($element['#type'] === 'checkbox') {
        return '<span class="label-title">' . $title . '</span>';
    } elseif ($element['#type'] === 'radio') {

        return '<span class="label-title">' . $title . '</span>';
    } else {
        if(!empty($attributes['for'])) {
            // Remove "for" attribute to pass HTML validation
            unset($attributes['for']);
        }
        // The leading whitespace helps visually separate fields from inline labels.
        return ' <div' . drupal_attributes($attributes) . '>' . $t('!title !required', array('!title' => $title, '!required' => $required)) . "</div>\n";
    }
}

function hitsa_form_element($variables)
{
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
    if ($element['#type'] === 'checkbox') {
        $attributes['class'][] = 'customCheckbox';
        $output = '<label><span' . drupal_attributes($attributes) . '>' . "\n";
    } elseif ($element['#type'] === 'radio') {
        $attributes['class'][] = 'customRadio';
        $output = '<label class="full-width"><span' . drupal_attributes($attributes) . '>' . "\n";
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
            if ($element['#type'] == 'radio') {
                $output .= '';
            } elseif ($element['#type'] !== 'checkbox') {
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

    if ($element['#type'] === 'checkbox') {
        $output .= "</span>" . theme('form_element_label', $variables) . "\n" . "</label>\n";
    } elseif ($element['#type'] === 'radio') {
        $output .= "</span>" . theme('form_element_label', $variables) . "\n" . "</label>\n";
    } else {
        $output .= "</div>\n";
    }
    return $output;
}

function hitsa_button($variables)
{
    $element = $variables['element'];
    $element['#attributes']['type'] = 'submit';

    element_set_attributes($element, array('id', 'name', 'value'));

    $element['#attributes']['class'][] = 'form-' . $element['#button_type'];
    if (!empty($element['#attributes']['disabled'])) {
        $element['#attributes']['class'][] = 'form-button-disabled';
    }

    if (isset($element['#buttontype']) && $element['#buttontype'] == 'button') {
        $value = $element['#value'];
        unset($element['#attributes']['value']);
        return '<button' . drupal_attributes($element['#attributes']) . '>' . $value . '</button>';
    } else {
        return '<input' . drupal_attributes($element['#attributes']) . ' />';
    }
}

function hitsa_container($variables)
{
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

function hitsa_textarea($variables)
{
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

function hitsa_webform_email($variables)
{
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

function hitsa_checkbox($variables)
{
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

function hitsa_pager($variables)
{
    $tags = $variables['tags'];
    $element = $variables['element'];
    $parameters = $variables['parameters'];
    $quantity = $variables['quantity'];
    global $pager_page_array, $pager_total;

    // Calculate various markers within this pager piece:
    // Middle is used to "center" pages around the current page.
    $pager_middle = ceil($quantity / 2);
    // current is the page we are currently paged to
    $pager_current = $pager_page_array[$element] + 1;

    // first is the first page listed by this pager piece (re quantity)
    $pager_first = $pager_current - $pager_middle + 1;
    // last is the last page listed by this pager piece (re quantity)
    $pager_last = $pager_current + $quantity - $pager_middle;
    // max is the maximum page number
    $pager_max = $pager_total[$element];
    // End of marker calculations.

    // Prepare for generation loop.
    $i = $pager_first;
    if ($pager_last > $pager_max) {
        // Adjust "center" if at end of query.
        $i = $i + ($pager_max - $pager_last);
        $pager_last = $pager_max;
    }
    if ($i <= 0) {
        // Adjust "center" if at start of query.
        $pager_last = $pager_last + (1 - $i);
        $i = 1;
    }
    // End of generation loop preparation.

    //$li_first = theme('pager_first', array('text' => (isset($tags[0]) ? $tags[0] : t('«')), 'element' => $element, 'parameters' => $parameters));
    $li_previous = ($pager_page_array[$element] > 0)
        ? '<a href="javascript:void(0);" data-page="prev" class="before-arrow_left"></a>' : '';
    $li_next = ($pager_page_array[$element] < ($pager_total[$element] - 1))
        ? '<a href="javascript:void(0);" data-page="next" class="before-arrow_right"></a>' : '';
    //$li_last = theme('pager_last', array('text' => (isset($tags[4]) ? $tags[4] : t('»')), 'element' => $element, 'parameters' => $parameters));

    if ($pager_total[$element] > 1) {
        /*
        if ($li_first) {
          $items[] = array(
            'class' => array('pager-first'),
            'data' => $li_first,
          );
        }*/
        if ($li_previous) {
            $items[] = array(
                'class' => array('pager-previous'),
                'data' => $li_previous,
            );
        }

        // When there is more than one page, create the pager list.
        if ($i != $pager_max) {
            if ($i > 1) {
                $items[] = array(
                    'class' => array('pager-ellipsis'),
                    'data' => '…',
                );
            }
            // Now generate the actual pager piece.
            for (; $i <= $pager_last && $i <= $pager_max; $i++) {
                if ($i < $pager_current) {
                    $items[] = array(
                        'class' => array(),
                        'data' => theme('pager_previous', array('text' => $i, 'element' => $element, 'interval' => ($pager_current - $i), 'parameters' => $parameters)),
                    );
                }
                if ($i == $pager_current) {
                    $items[] = array(
                        'class' => array('active'),
                        'data' => '<a href="javascript:void(0);" data-page="' . $i . '">' . $i . '</a>',
                    );
                }
                if ($i > $pager_current) {
                    $items[] = array(
                        'class' => array(),
                        'data' => theme('pager_next', array('text' => $i, 'element' => $element, 'interval' => ($i - $pager_current), 'parameters' => $parameters)),
                    );
                }
            }
            if ($i < $pager_max) {
                $items[] = array(
                    'class' => array(),
                    'data' => '…',
                );
            }
        }
        // End generation.
        if ($li_next) {
            $items[] = array(
                'class' => array(),
                'data' => $li_next,
            );
        }
        /*
        if ($li_last) {
          $items[] = array(
            'class' => array(),
            'data' => $li_last,
          );
        }
        */

        return theme('item_list__pager', array(
            'items' => $items,
            'attributes' => array('class' => array('pager')),
        ));
    }
}

function hitsa_item_list__pager($variables)
{
    $items = $variables['items'];
    $title = $variables['title'];
    $type = $variables['type'];
    $attributes = $variables['attributes'];

    // Only output the list container and title, if there are any list items.
    // Check to see whether the block title exists before adding a header.
    // Empty headers are not semantic and present accessibility challenges.
    $output = '';
    if (isset($title) && $title !== '') {
        $output .= '<h3>' . $title . '</h3>';
    }

    if (!empty($items)) {
        $output .= '<ul class="paginator" data-plugin="filterPaginator" data-relative="paginatorNumber">';
        $num_items = count($items);
        $i = 0;
        foreach ($items as $item) {
            $attributes = array();
            $children = array();
            $data = '';
            $i++;
            if (is_array($item)) {
                foreach ($item as $key => $value) {
                    if ($key == 'data') {
                        $data = $value;
                    } elseif ($key == 'children') {
                        $children = $value;
                    } else {
                        $attributes[$key] = $value;
                    }
                }
            } else {
                $data = $item;
            }

            if (count($children) > 0) {
                // Render nested list.
                $data .= theme_item_list(array('items' => $children, 'title' => NULL, 'type' => $type, 'attributes' => $attributes));
            }
            if ($i == 1) {
                $attributes['class'][] = 'first';
            }
            if ($i == $num_items) {
                $attributes['class'][] = 'last';
            }
            $output .= '<li' . drupal_attributes($attributes) . '>' . $data . "</li>\n";
        }
        $output .= "</ul>";
    }
    return $output;
}

function hitsa_pager_link($variables)
{
    $text = $variables['text'];
    $page_new = $variables['page_new'];
    $element = $variables['element'];
    $parameters = $variables['parameters'];
    $attributes = $variables['attributes'];

    $page = isset($_GET['page']) ? $_GET['page'] : '';
    if ($new_page = implode(',', pager_load_array($page_new[$element], $element, explode(',', $page)))) {
        $parameters['page'] = $new_page;
    }

    $query = array();
    if (count($parameters)) {
        $query = drupal_get_query_parameters($parameters, array());
    }
    if ($query_pager = pager_get_query_parameters()) {
        $query = array_merge($query, $query_pager);
    }

    // Set each pager link title
    if (!isset($attributes['title'])) {
        static $titles = NULL;
        if (!isset($titles)) {
            $titles = array(
                t('« first') => t('Go to first page'),
                t('‹ previous') => t('Go to previous page'),
                t('next ›') => t('Go to next page'),
                t('last »') => t('Go to last page'),
            );
        }
        if (isset($titles[$text])) {
            $attributes['title'] = $titles[$text];
        } elseif (is_numeric($text)) {
            $attributes['title'] = t('Go to page @number', array('@number' => $text));
        }
    }

    // @todo l() cannot be used here, since it adds an 'active' class based on the
    //   path only (which is always the current path for pager links). Apparently,
    //   none of the pager links is active at any time - but it should still be
    //   possible to use l() here.
    // @see http://drupal.org/node/1410574
    $attributes['href'] = url($_GET['q'], array('query' => $query));
    $page = $text - 1;
    return '<a href="javascript:void(0);" data-page="' . $page . '">' . check_plain($text) . '</a>';
}

function hitsa_gallery_grid($variables)
{

    $output = '<ul class="gallery-thumbs">';
    foreach ($variables['grid']['#items'] as $image) {
        $output .= '<li><a href="javascript:void(0);" ';
        $output .= 'style="background-image:url(' . image_style_url('hitsa_gallery_thumbnail', $image['uri']) . ')" ';
        $output .= 'data-image="' . image_style_url('hitsa_gallery_image_full', $image['uri']) . '" ';
        $output .= 'data-download="' . file_create_url($image['uri']) . '" ';
        $output .= 'data-id="' . $image['fid'] . '" ';


        $title = array();
        // Image metadata
        if (!empty($image['field_file_image_title_text'])) {
            $title[] = check_plain($image['field_file_image_title_text'][LANGUAGE_NONE][0]['value']);
        }
        if (!empty($image['field_image_author'])) {
            $title[] = check_plain($image['field_image_author'][LANGUAGE_NONE][0]['value']);
        }
        if (!empty($image['field_image_date'])) {
            $title[] = date("d.m.Y", $image['field_image_date'][LANGUAGE_NONE][0]['value']);
        }
        $title = implode(', ', $title);

        $output .= 'title="' . $title . '">';
        $output .= '<img src="' . '/' . drupal_get_path('theme', $GLOBALS['theme']) . '/static/assets/imgs/placeholder-1.gif" ';
        $output .= 'alt="' . (!empty($image['field_file_image_alt_text']) ? check_plain($image['field_file_image_alt_text'][LANGUAGE_NONE][0]['safe_value']) : '') . '">';
        $output .= '</a></li>';
    }
    $output .= '</ul>';
    return $output;
}

function hitsa_css_alter(&$css)
{
    $exclude = array(
        'modules/system/system.theme.css' => FALSE,
    );
    $css = array_diff_key($css, $exclude);
}

function hitsa_checkboxes($variables)
{
    $element = $variables['element'];
    $attributes = array();
    if (isset($element['#id'])) {
        $attributes['id'] = $element['#id'];
    }
    $attributes['class'][] = 'form-checkboxes';
    if (!empty($element['#attributes']['class'])) {
        $attributes['class'] = array_merge($attributes['class'], $element['#attributes']['class']);
    }
    if (isset($element['#attributes']['title'])) {
        $attributes['title'] = $element['#attributes']['title'];
    }
    return (!empty($element['#children']) ? $element['#children'] : '');
}

function hitsa_radio($variables)
{
    $element = $variables['element'];
    $element['#attributes']['type'] = 'radio';
    element_set_attributes($element, array('id', 'name', '#return_value' => 'value'));

    // Unchecked checkbox has #value of integer 0.
    if (!empty($element['#checked'])) {
        $element['#attributes']['checked'] = 'checked';
    }
    _form_set_class($element, array('form-checkbox'));

    return '<input' . drupal_attributes($element['#attributes']) . ' /><span class="check"></span>';
}

function hitsa_radios($variables)
{
    $element = $variables['element'];
    $attributes = array();
    $element['#theme_wrappers'] = array();
    if (isset($element['#id'])) {
        $attributes['id'] = $element['#id'];
    }
    $attributes['class'] = 'form-radios';
    if (!empty($element['#attributes']['class'])) {
        $attributes['class'] .= ' ' . implode(' ', $element['#attributes']['class']);
    }
    if (isset($element['#attributes']['title'])) {
        $attributes['title'] = $element['#attributes']['title'];
    }
    return (!empty($element['#children']) ? $element['#children'] : '');
}

function hitsa_status_messages($variables) {
  $display = $variables['display'];
  $output = '';

  $status_heading = array(
    'status' => ' notification-success',
    'error' => ' notification-danger',
    'warning' => '',
  );
  foreach (drupal_get_messages($display) as $type => $messages) {
    
    $output .= '<div class="row"><div class="col-12">';
    $output .= '<div class="notification' . $status_heading[$type] . '" data-plugin="notification">';
    $output .= '<div class="notification-sign"></div>';
    $output .= '<div class="notification-text">';
    if (count($messages) > 1) {
      
      foreach ($messages as $message) {
        $output .= '<p>' . $message . "</p>\n";
      }
    }
    else {
      $output .= '<p>' . reset($messages) . '</p>';
    }
    $output .= '</div>';
    $output .= '<div class="notification-close"><span class="notification-close-label">' . t('Close') . '</span><span class="before-close"></span></div>';
    $output .= "</div></div></div>";
  }
  return $output;
  }