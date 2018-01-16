
<?php

?>
            <div class="block block-narrow <?php ($type=='desktop')?print 'sm-hide':print 'sm-show'?>" data-plugin="tabs">
               <h2 class="block-title"><?php print($period['name'])?></h2>
               
               <div class="row pull-up">
                  <div class="col-12">
                     <a href="javascript:void(0);" data-target="tab-1" class="link-tab"><?php print t('Hours')?></a><a href="javascript:void(0);" data-target="tab-2" class="link-tab"><?php print t('Breaks')?></a>
                  </div><!--/col-12-->
               </div><!--/row-->
               <div class="row-spacer-xs"></div>
               <div data-tab="tab-1">

               <?php print $hours?>
                  
                  <div class="row-spacer"></div>
                  
                  <a href="<?php print url('calendar')?>" class="btn btn-filled btn-stretch"><?php print t('Curriculum calendar')?></a>
                  
               </div><!--/data-tab-1-->
               <div data-tab="tab-2">
                  <?php print $breaks?>
                  
                  <div class="row-spacer"></div>
                  
                  <a href="<?php print url('calendar')?>" class="btn btn-filled btn-stretch"><?php print t('Curriculum calendar')?></a>
                  
               </div><!--/data-tab-->
               
            </div><!--/block-->