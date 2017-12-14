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
  <?php if ($attachment_before): ?>
  <div class="row">
    <?php print $attachment_before; ?>
  </div>
  <?php endif; ?>
  
  <div class="row-spacer sm-hide"></div>
  
  <?php if($view->current_display === 'news_block'): ?>
    <?php if ($rows): ?>
    <div class="row sm-hide">
      <?php print $rows; ?>
    </div>
    <?php endif; ?>
  <?php else: ?>
    <?php if ($rows): ?>
      <?php print $rows; ?>
    <?php endif; ?>
  <?php endif; ?>
  
  <div class="row-spacer"></div>
  
  <?php if($view->current_display === 'news_block'): ?>
  <div class="row">
    <div class="col-12">
       <a href="<?php print url('news'); ?>" class="btn sm-stretch"><?php print t('All news'); ?></a>
    </div><!--/col-12-->
  </div><!--/row-->
<?php endif; ?>