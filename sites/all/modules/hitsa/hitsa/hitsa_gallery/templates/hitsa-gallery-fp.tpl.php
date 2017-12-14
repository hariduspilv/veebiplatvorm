<div class="block sm-hide">
  <h2 class="block-title sm-borderless"><?php print t('Gallery'); ?></h2>
  
  <div class="row">
    <?php if(!empty($nodes[0])): 
    $node = $nodes[0];
    ?>
     <div class="col-12">
        <a href="<?php print url('node/' . $node['#node']->nid); ?>" class="object">
           <span class="object-inner">
              <span class="object-image" style="background-image:url(<?php print image_style_url('hitsa_gallery_image_full', $node['gallery_images'][0]['#item']['uri']); ?>);"><img alt="" src="<?php print '/' . drupal_get_path('theme', $GLOBALS['theme']) . '/static/assets/imgs/placeholder-56.gif'; ?>"></span>
              <span class="object-content">
                 <span class="object-title"><?php print $node['#node']->title; ?></span>
                 <span class="object-footer">
                    <span class="before-calendar"><?php print date('d. F Y', $node['#node']->created); ?></span>
                 </span><!--/object-footer-->
              </span><!--/object-content-->
           </span><!--/object-inner-->
        </a><!--/object-->
     </div><!--/col-12-->
     <?php endif; ?>
  </div><!--/row-->
  
  <div class="row-spacer"></div>
  
  <div class="row">
    <?php foreach($nodes as $delta => $node): 
    if($delta == 0) continue;
    ?>
    <div class="col-6 sm-12">
        <a href="<?php print url('node/' . $node['#node']->nid); ?>" class="object">
           <span class="object-inner">
              <span class="object-image" style="background-image:url(<?php print image_style_url('hitsa_gallery_menu_teaser', $node['gallery_images'][0]['#item']['uri']); ?>);"><img alt="" src="<?php print '/' . drupal_get_path('theme', $GLOBALS['theme']) . '/static/assets/imgs/placeholder-56.gif'; ?>"></span>
              <span class="object-content">
                 <span class="object-title"><?php print $node['#node']->title; ?></span>
                 <span class="object-footer">
                    <span class="before-calendar"><?php print date('d. F Y', $node['#node']->created); ?></span>
                 </span><!--/object-footer-->
              </span><!--/object-content-->
           </span><!--/object-inner-->
        </a><!--/object-->
     </div><!--/col-6-->
    <?php endforeach; ?>
  </div><!--/row-->
  
  <div class="row">
     <div class="col-12">
        <a href="<?php print url('gallery'); ?>" class="btn sm-stretch"><?php print t('All galleries'); ?></a>
     </div><!--/col-12-->
  </div><!--/row-->
</div>