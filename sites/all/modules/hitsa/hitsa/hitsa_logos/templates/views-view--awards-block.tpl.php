<?php

/**
 * @file
 * Main view template.
 *
 * Variables available:
 * - $classes_array: An array of classes determined in
 *   template_preprocess_views_view(). Default classes are:
 *     .view
 *     .view-[css_name]
 *     .view-id-[view_name]
 *     .view-display-id-[display_name]
 *     .view-dom-id-[dom_id]
 * - $classes: A string version of $classes_array for use in the class attribute
 * - $css_name: A css-safe version of the view name.
 * - $css_class: The user-specified classes names, if any
 * - $header: The view header
 * - $footer: The view footer
 * - $rows: The results of the view query, if any
 * - $empty: The empty text to display if the view is empty
 * - $pager: The pager next/prev links to display, if any
 * - $exposed: Exposed widget form/info to display
 * - $feed_icon: Feed icon to display, if any
 * - $more: A link to view more, if any
 *
 * @ingroup views_templates
 */
?>
<div class="block block-narrow sm-hide">
  <?php if($title = variable_get_value('front_confirmation_title', array('default' => t('Awards')))): ?>
  <h2 class="block-title"><?php print $title; ?></h2>
  <?php else:?>
    <h2 class="block-title"><?php print t('Awards'); ?></h2>
  <?php endif;?>
  <?php if ($rows): ?>
  <div class="row pull-up">
    <?php print $rows; ?>
  </div>
  <?php endif; ?>
</div>
