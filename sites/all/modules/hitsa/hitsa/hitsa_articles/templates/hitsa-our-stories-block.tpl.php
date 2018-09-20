<div class="block block-narrow">
  <?php if($our_stories_title = variable_get_value('front_our_stories_title', array('default' => t('Our stories')))): ?>
  <h2 class="block-title"><?php print $our_stories_title; ?></h2>
  <?php endif; ?>
  <div class="row pull-up">
    
    <?php foreach($nodes as $node): ?>
    <div class="col-12">
      <?php if((node_access("update", $node, $user) === TRUE)): ?>
      <ul class="tabs primary">
        <li><a href="<?php print url('node/' . $node->nid . '/edit'); ?>"><?php print t('Edit'); ?></a></li>
        <li><a href="<?php print url('node/' . $node->nid . '/translate'); ?>"><?php print t('Translate'); ?></a></li>
      </ul>
      <?php endif; ?>
      <a href="<?php print url('node/' . $node->nid); ?>" class="object object-small">
        <span class="object-inner">
          <?php if(!empty($node->subpage_images[LANGUAGE_NONE][0])): ?>
          <span class="object-image" style="background-image:url(<?php print image_style_url('hitsa_core_thumbnail', $node->subpage_images[LANGUAGE_NONE][0]['uri']); ?>);">
            <img alt="" src="<?php print '/' . drupal_get_path('theme', $GLOBALS['theme']) . '/static/assets/imgs/placeholder-56.gif'; ?>">
          </span>
          <?php endif; ?>
          <span class="object-content">
            <span class="object-title"><?php print check_plain($node->title); ?></span>
            <span class="object-footer">
              <?php if(!empty($authors[$node->uid]->name)): ?>
              <span class="before-user"><?php print $authors[$node->uid]->name; ?></span>
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