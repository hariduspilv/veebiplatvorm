<?php

/**
 * @file
 * Default theme implementation to display a node.
 *
 * Available variables:
 * - $title: the (sanitized) title of the node.
 * - $content: An array of node items. Use render($content) to print them all,
 *   or print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $user_picture: The node author's picture from user-picture.tpl.php.
 * - $date: Formatted creation date. Preprocess functions can reformat it by
 *   calling format_date() with the desired parameters on the $created variable.
 * - $name: Themed username of node author output from theme_username().
 * - $node_url: Direct URL of the current node.
 * - $display_submitted: Whether submission information should be displayed.
 * - $submitted: Submission information created from $name and $date during
 *   template_preprocess_node().
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the
 *   following:
 *   - node: The current template type; for example, "theming hook".
 *   - node-[type]: The current node type. For example, if the node is a
 *     "Blog entry" it would result in "node-blog". Note that the machine
 *     name will often be in a short form of the human readable label.
 *   - node-teaser: Nodes in teaser form.
 *   - node-preview: Nodes in preview mode.
 *   The following are controlled through the node publishing options.
 *   - node-promoted: Nodes promoted to the front page.
 *   - node-sticky: Nodes ordered above other non-sticky nodes in teaser
 *     listings.
 *   - node-unpublished: Unpublished nodes visible only to administrators.
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 *
 * Other variables:
 * - $node: Full node object. Contains data that may not be safe.
 * - $type: Node type; for example, story, page, blog, etc.
 * - $comment_count: Number of comments attached to the node.
 * - $uid: User ID of the node author.
 * - $created: Time the node was published formatted in Unix timestamp.
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $zebra: Outputs either "even" or "odd". Useful for zebra striping in
 *   teaser listings.
 * - $id: Position of the node. Increments each time it's output.
 *
 * Node status variables:
 * - $view_mode: View mode; for example, "full", "teaser".
 * - $teaser: Flag for the teaser state (shortcut for $view_mode == 'teaser').
 * - $page: Flag for the full page state.
 * - $promote: Flag for front page promotion state.
 * - $sticky: Flags for sticky post setting.
 * - $status: Flag for published status.
 * - $comment: State of comment settings for the node.
 * - $readmore: Flags true if the teaser content of the node cannot hold the
 *   main body content.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 *
 * Field variables: for each field instance attached to the node a corresponding
 * variable is defined; for example, $node->body becomes $body. When needing to
 * access a field's raw values, developers/themers are strongly encouraged to
 * use these variables. Otherwise they will have to explicitly specify the
 * desired field language; for example, $node->body['en'], thus overriding any
 * language negotiation rule that was previously applied.
 *
 * @see template_preprocess()
 * @see template_preprocess_node()
 * @see template_process()
 *
 * @ingroup themeable
 */
?>
<div class="object object-horizontal">
  <span class="object-inner">
    <?php if(!empty($node->contact_image)): // Contact Image ?>
    <span class="object-image object-image-circle" style="background-image:url(<?php print image_style_url('hitsa_contacts_page_image', $node->contact_image[LANGUAGE_NONE][0]['uri']); ?>);">
      <img alt="" src="<?php print '/' . drupal_get_path('theme', $GLOBALS['theme']) . '/static/assets/imgs/placeholder-56.gif'; ?>" />
    </span>
    <?php endif; ?>
    <span class="object-content">
      <div class="object-content_col">
        <p>
          <b><?php print check_plain($node->title); // Name ?> <?php if(!empty($node->contact_cv)): // Contact CV ?><a target="_blank" href="<?php print $node->contact_cv[LANGUAGE_NONE][0]['url']; ?>">(CV)</a><?php endif; ?></b>
        </p>
        <p>
          <?php if($job_position_field = field_get_items('node', $node, 'job_position')): // Job position ?>
            <?php $job_position = field_view_value('node', $node, 'job_position', $job_position_field[0]); print render($job_position); ?><br />
          <?php endif; ?>
          <?php if($phone_nr = field_get_items('node', $node, 'phone_nr')): // Phone Nr ?>
            <?php print check_plain($node->phone_nr[LANGUAGE_NONE][0]['safe_value']); ?><br />
          <?php endif; ?>
          <?php if(!empty($node->e_mail[LANGUAGE_NONE][0]['email'])): // E-mail ?>
          <a href="mailto:<?php print check_plain($node->e_mail[LANGUAGE_NONE][0]['email']); ?>"><?php print check_plain($node->e_mail[LANGUAGE_NONE][0]['email']); ?></a>
          <?php endif; ?>
        </p>
      </div><!--/object-content_col-->
      <div class="object-content_col">
        <p><b><?php print t('Reception times'); ?>:</b></p>
        <?php if($reception_times = field_get_items('node', $node, 'reception_times')): // Reception times ?>
        <p><?php print nl2br(check_plain($reception_times[0]['safe_value'])); ?></p>
        <?php endif; ?>
      </div><!--/object-content_col-->
    </span><!--/object-content-->
  </span><!--/object-inner-->
</div><!--/object-->