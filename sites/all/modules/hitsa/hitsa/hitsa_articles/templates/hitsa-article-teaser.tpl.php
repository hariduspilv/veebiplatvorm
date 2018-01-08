<div class="col-4 sm-12">
  <a href="<?php print url('node/' . $node->nid); ?>" class="object"<?php if($node->type === 'gallery') print ' data-plugin="modal"'; ?>>
    <span class="object-inner">
      <?php 
      if($node->type === 'article') {
        $image = $node->subpage_images;
      } else if($node->type === 'gallery') {
        $image = $node->gallery_images;
      }
      if(!empty($image[LANGUAGE_NONE][0])): ?>
      <span class="object-image" style="background-image:url(<?php print image_style_url('hitsa_core_thumbnail', $image[LANGUAGE_NONE][0]['uri']); ?>);">
        <img alt="" src="<?php print '/' . drupal_get_path('theme', $GLOBALS['theme']) . '/static/assets/imgs/placeholder-56.gif'; ?>">
      </span>
      <?php else: ?>
      <span class="object-image">
				<span class="object-placeholder">
					<span><img src="<?php print $placeholder_image_url; ?>" /></span>
				</span><!--/object-placeholder-->
				<img alt="" src="<?php print '/' . drupal_get_path('theme', $GLOBALS['theme']) . '/static/assets/imgs/placeholder-56.gif'; ?>" />
			</span><!--/object-image-->
      <?php endif; ?>
      <span class="object-content">
        <span class="object-title"><?php print check_plain($node->title); ?></span>
        <span class="object-footer">
          <span class="before-calendar"><?php print format_date($node->created, 'hitsa_date_month'); ?></span>
          <?php if(!empty($author->name)): ?>
          <span class="before-user"><?php print $author->name; ?></span>
          <?php endif; ?>
        </span><!--/object-footer-->
      </span><!--/object-content-->
    </span><!--/object-inner-->
  </a><!--/object-->
</div><!--/col-4-->