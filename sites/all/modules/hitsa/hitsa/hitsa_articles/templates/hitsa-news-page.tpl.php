<div class="row">
  <div class="col-12">
            
    <div class="block">
      <h1 class="block-title"><?php print drupal_get_title(); ?></h1>
      
      <div class="row-spacer-xs"></div>
      
      <form method="post" action="">
        <div class="row">
          <div class="col-9">
             
            <div class="btn-bar">
              <span class="btn-input">
                <input type="radio" name="category" value="0" checked="">
                <span class="btn btn-xs btn-alternate"><?php print t('All'); ?></span>
              </span><!--/btn-input-->
              <?php foreach($academic_years as $delta => $academic_year): ?>
              <span class="btn-input"<?php if($delta > 2) print ' data-show="hiddenFilter | inlineBlock"'; ?>>
                <input type="radio" name="category" value="<?php print $academic_year->tid; ?>">
                <span class="btn btn-xs btn-alternate"><?php print $academic_year->name; ?></span>
              </span><!--/btn-input-->
              <?php endforeach; ?>

            </div><!--/btn-bar-->
             
          </div><!--/col-9-->
          
          <div class="col-3">
          <?php if(count($academic_years) > 3): ?>
             <a href="javascript:void(0);" class="cta-link pull-right before-plus" data-toggle="hiddenFilter" data-class="'active' : hiddenFilter"><?php print t('More choices'); ?></a>
          <?php endif; ?>
          </div><!--/col-3-->
        </div><!--/row-->
      </form>
      
      <div class="row-spacer"></div>
      <?php foreach($nodes as $tid => $academic_year): ?>
      <div class="row">
        <div class="col-12">
          <?php if(!empty($academic_year_keyed[$tid])): ?>
          <h3><?php print check_plain($academic_year_keyed[$tid]); ?></h3>
          <?php endif; ?>
        </div><!--/col-12-->
      </div><!--/row-->
      
      <div class="row-spacer-xs"></div>
      
      <div class="row row-vertical-xl">
        <?php foreach($academic_year as $academic_year_nodes): ?>
          <?php print $academic_year_nodes; ?>
        <?php endforeach; ?>
      </div><!--/row-->
      
      <?php if(next($nodes) !== FALSE): ?>
      <div class="row-spacer"></div>
      <div class="row-spacer"></div>
      <hr>
      <div class="row-spacer"></div>
      <?php endif; ?>
      
      <?php endforeach; ?>
      
      <div class="row">
        <div class="col-12">
          <ul class="paginator">
            <li><a href="" class="before-arrow_left"></a></li>
            <li><a href="">1</a></li>
            <li class="active"><a href="">2</a></li>
            <li><a href="">3</a></li>
            <li>...</li>
            <li><a href="">6</a></li>
            <li><a href="" class="before-arrow_right"></a></li>
          </ul><!--/paginator-->
        </div><!--/col-12-->
      </div><!--/row-->
               
    </div><!--/block-->
            
  </div><!--/col-12-->
</div>