<?php if(!empty($important_article)) print $important_article; // Tähtis uudis ?>
<div class="row">
  <div class="col-9">

    <?php if(!empty($news_block)) print $news_block; // Uudised ?>
    <?php if(!empty($hitsa_front_events)) print $hitsa_front_events; // Uudised ?>



    <div class="block">
               <h2 class="block-title">Galerii</h2>

               <div class="row">
                  <div class="col-12">
                     <a href="" class="object">
                        <span class="object-inner">
                           <span class="object-image" style="background-image:url(<?php print '/' . drupal_get_path('theme', $GLOBALS['theme']) . '/static/assets/tmp/object-1.jpg'; ?>);"><img alt="" src="<?php print '/' . drupal_get_path('theme', $GLOBALS['theme']) . '/static/assets/imgs/placeholder-56.gif'; ?>"></span>
                           <span class="object-content">
                              <span class="object-title">Kevadnädal 2017</span>
                              <span class="object-footer">
                                 <span class="before-shopping">20. juuni 2017</span>
                              </span><!--/object-footer-->
                           </span><!--/object-content-->
                        </span><!--/object-inner-->
                     </a><!--/object-->
                  </div><!--/col-12-->
               </div><!--/row-->

               <div class="row-spacer"></div>

               <div class="row">
                  <div class="col-6">
                     <a href="" class="object">
                        <span class="object-inner">
                           <span class="object-image" style="background-image:url(<?php print '/' . drupal_get_path('theme', $GLOBALS['theme']) . '/static/assets/tmp/object-1.jpg'; ?>);"><img alt="" src="<?php print '/' . drupal_get_path('theme', $GLOBALS['theme']) . '/static/assets/imgs/placeholder-56.gif'; ?>"></span>
                           <span class="object-content">
                              <span class="object-title">Eesti Vabariigi 99-aastapäeva aktus</span>
                              <span class="object-footer">
                                 <span class="before-shopping">20. juuni 2017</span>
                              </span><!--/object-footer-->
                           </span><!--/object-content-->
                        </span><!--/object-inner-->
                     </a><!--/object-->
                  </div><!--/col-6-->
                  <div class="col-6">
                     <a href="" class="object">
                        <span class="object-inner">
                           <span class="object-image" style="background-image:url(<?php print '/' . drupal_get_path('theme', $GLOBALS['theme']) . '/static/assets/tmp/object-1.jpg'; ?>);"><img alt="" src="<?php print '/' . drupal_get_path('theme', $GLOBALS['theme']) . '/static/assets/imgs/placeholder-56.gif'; ?>"></span>
                           <span class="object-content">
                              <span class="object-title">Jõulunädal 2016</span>
                              <span class="object-footer">
                                 <span class="before-shopping">20. juuni 2017</span>
                              </span><!--/object-footer-->
                           </span><!--/object-content-->
                        </span><!--/object-inner-->
                     </a><!--/object-->
                  </div><!--/col-6-->
               </div><!--/row-->

               <div class="row">
                  <div class="col-12">
                     <a href="" class="btn">Kõik galeriid</a>
                  </div><!--/col-12-->
               </div><!--/row-->

            </div><!--/block-->
  </div><!--/col-9-->

  <div class="col-3">
    <div class="block block-narrow">
               <h2 class="block-title">Teenused</h2>

               <div class="row pull-up">
                  <div class="col-12">
                     <a href="javascript:void(0);" data-target="tab-1" class="link-tab">Teenused</a><a href="javascript:void(0);" data-target="tab-2" class="link-tab active">Koolitused</a>
                  </div><!--/col-12-->
               </div><!--/row-->
               <div class="row-spacer-xs"></div>
               <div data-tab="tab-1">
                  Teenused sisu.
               </div><!--/data-tab-1-->
               <div data-tab="tab-2" class="active-tab">
                  <div class="row">




                     <div class="col-12 col-margin">
                        <a href="<?php print url('training_calendar')?>" class="btn btn-filled btn-stretch"><?php print t('Training calendar')?></a>
                     </div><!--/col-12-->

                  </div><!--/row-->
               </div><!--/data-tab-->

            </div><!--/block-->

    <?php if(!empty($our_stories_block)) print $our_stories_block; // Meie lood ?>

    <?php if(!empty($awards_block)) print $awards_block; // Tunnustused ?>

  </div><!--/col-3-->
</div>
