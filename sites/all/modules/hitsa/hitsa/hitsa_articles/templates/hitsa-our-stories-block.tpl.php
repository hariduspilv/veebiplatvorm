<div class="block block-narrow">
  <h2 class="block-title"><?php print t('Our stories'); ?></h2>
  <div class="row pull-up">
    <?php foreach($nodes as $node): ?>
    <div class="col-12">
      <a href="<?php print url('node/' . $node->nid); ?>" class="object object-small">
        <span class="object-inner">
          <?php if(!empty($node->cp_gallery[LANGUAGE_NONE][0])): ?>
          <span class="object-image" style="background-image:url(<?php print image_style_url('hitsa_core_thumbnail', $node->cp_gallery[LANGUAGE_NONE][0]['uri']); ?>);">
            <img alt="" src="<?php print '/' . drupal_get_path('theme', $GLOBALS['theme']) . '/static/assets/imgs/placeholder-56.gif'; ?>">
          </span>
          <?php endif; ?>
          <span class="object-content">
            <span class="object-title"><?php print check_plain($node->title); ?></span>
            <span class="object-footer">
              <?php if(!empty($authors[$node->uid]->name)): ?>
              <span class="before-shopping"><?php print $authors[$node->uid]->name; ?></span>
              <?php endif; ?>
            </span><!--/object-footer-->
          </span><!--/object-content-->
        </span><!--/object-inner-->
      </a><!--/object-->
    </div><!--/col-12-->
    <?php endforeach; ?>
    <div class="col-12 col-margin">
      <a href="<?php print url('our-stories'); ?>" class="btn btn-stretch"><?php print t('All stories'); ?></a>
    </div><!--/col-12-->
  </div><!--/row-->
</div>