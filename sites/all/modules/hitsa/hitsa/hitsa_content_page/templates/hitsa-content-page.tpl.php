<div class="row">
  <div class="col-12">
            
    <div class="block" id="all">
      <h1 class="block-title"><?php print drupal_get_title(); ?></h1>
      
      <form method="post" data-plugin="filters">
        <div class="row">
          <div class="col-12">
             
            <div class="btn-bar">
              <span class="btn-input">
                <input type="checkbox" name="category" value="all" checked="">
                <span class="btn btn-xs btn-alternate"><?php print t('All'); ?></span>
              </span><!--/btn-input-->
              <?php foreach($academic_years as $delta => $academic_year): ?>
              <span class="btn-input"<?php if($delta > 2) print ' data-show="hiddenFilter | inlineBlock"'; ?>>
                <input type="checkbox" name="category" value="<?php print $academic_year->tid; ?>">
                <span class="btn btn-xs btn-alternate"><?php print $academic_year->name; ?></span>
              </span><!--/btn-input-->
              <?php endforeach; ?>

            </div><!--/btn-bar-->
            <input type="hidden" name="page" id="paginatorNumber">
            <?php if($bundle === 'article'): ?>
            <input type="hidden" name="article_type" value="<?php if(current_path() === 'our-stories') {print 'our-stories';} else print 'news'; ?>">
            <?php endif; ?>
          </div><!--/col-9-->
          
          <div class="col-3">
          <?php if(count($academic_years) > 3): ?>
             <a href="javascript:void(0);" class="cta-link pull-right before-plus" data-toggle="hiddenFilter" data-class="'active' : hiddenFilter"><?php print t('More choices'); ?></a>
          <?php endif; ?>
          </div><!--/col-3-->
        </div><!--/row-->
      </form>
      
      <div class="row-spacer sm-hide"></div>
      <div class="row-spacer-xs sm-show"></div>
      <hr class="sm-show">
      <?php if($bundle === 'article'): ?>
      <div data-posturl="<?php print url('api/articles'); ?>" data-plugin="filterContents">
      <?php elseif($bundle === 'gallery'): ?>
      <div data-posturl="<?php print url('api/gallery'); ?>" data-plugin="filterContents">
      <?php endif; ?>
        <?php print $output; ?>
    </div><!--/block-->
  </div><!--/col-12-->
</div>