<div class="row">
  <div class="col-12">
     <div class="block bg-highlight">
        <div class="row">
           <div class="col-9 vertical-center">
              <h2><?php print check_plain($node->title); ?></h2>
           </div><!--/col-9-->
           <div class="col-3">
              <a href="<?php print url('node/' . $node->nid); ?>" class="btn btn-inverted pull-right"><?php print t('Read more'); ?></a>
           </div><!--/col-3-->
        </div><!--/row-->
     </div><!--/block-->
  </div><!--/col-12-->
</div>