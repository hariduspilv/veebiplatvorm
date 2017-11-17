<div class="col-4">
  <a href="<?php print url('node/' . $node->nid); ?>" class="object">
    <span class="object-inner">
      <?php if(!empty($node->subpage_images[LANGUAGE_NONE][0])): ?>
      <span class="object-image" style="background-image:url(<?php print image_style_url('hitsa_core_thumbnail', $node->subpage_images[LANGUAGE_NONE][0]['uri']); ?>);">
        <img alt="" src="<?php print '/' . drupal_get_path('theme', $GLOBALS['theme']) . '/static/assets/imgs/placeholder-56.gif'; ?>">
      </span>
      <?php endif; ?>
      <span class="object-content">
        <span class="object-title"><?php print check_plain($node->title); ?></span>
        <span class="object-footer">
          <span class="before-shopping"><?php print format_date($node->created, 'hitsa_date_month'); ?></span>
          <?php if(!empty($author->name)): ?>
          <span class="before-shopping"><?php print $author->name; ?></span>
          <?php endif; ?>
        </span><!--/object-footer-->
      </span><!--/object-content-->
    </span><!--/object-inner-->
  </a><!--/object-->
</div><!--/col-4-->