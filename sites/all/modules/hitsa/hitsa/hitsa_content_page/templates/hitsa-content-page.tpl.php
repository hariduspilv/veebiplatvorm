<div class="block" id="all">
  <h1 class="block-title"><?php print drupal_get_title(); ?></h1>
      <?php if(!empty($academic_years)): ?>
      <form method="post" data-plugin="filters">
        <div class="row">
          <div class="col-12">
            
            <div class="btn-bar">
              <span class="btn-input">
                <input type="checkbox" name="category" value="all" checked="">
                <span class="btn btn-xs btn-alternate"><?php print t('All'); ?></span>
              </span><!--/btn-input-->
              <?php foreach($academic_years as $delta => $academic_year): ?>
              <span class="btn-input">
                <input type="checkbox" name="category" value="<?php print $academic_year->tid; ?>">
                <span class="btn btn-xs btn-alternate"><?php print $academic_year->name; ?></span>
              </span><!--/btn-input-->
              <?php endforeach; ?>
        </div><!--/btn-bar-->
        <input type="hidden" name="page" id="paginatorNumber">
        <?php if($bundle === 'article'): ?>
        <input type="hidden" name="article_type" value="<?php if(current_path() === 'our-stories') {print 'our_stories';} else print 'news'; ?>">
        <?php endif; ?>
      </div><!--/col-12-->
      
    </div><!--/row-->
    
    <div class="row-spacer-xs sm-hide"></div>
    <hr />
    <div class="row-spacer sm-hide"></div>
      
    <div class="row">
      <div class="col-12">
         <div class="form-item-row">
            
            <div class="form-item after-search form-item_rounded form-item-stretch">
               <div class="form-item_title"><?php print t('Search by title'); ?></div>
               <input type="text" name="title" placeholder="<?php print $search_placeholder; ?>" data-plugin="autocomplete" 
               data-url="<?php print url("api/$bundle-autocomplete" . ($bundle === 'article' ? "-$content_type" : "")); ?>" data-onSubmit="true" />
            </div><!--/form-item-->
            
            <div class="form-item form-item_rounded after-calendar form-item-stretch">
               <div class="form-item_title"><?php print t('Date'); ?></div>
               <input type="text" name="date" data-plugin="datepickerRange" data-onSubmit="true" placeholder="<?php print t('Pick date (period)'); ?>" />
            </div><!--/form-item-->
            
            <div class="row-spacer-xs sm-show"></div>
            
            <div class="form-item">
               <div class="form-item_title sm-hide">&nbsp;</div>
               <button class="btn btn-filled"><?php print t('Search'); ?></button>
            </div><!--/form-item-->
            
         </div><!--/form-item-row-->
      </div><!--/col-12-->
    </div><!--/row-->
    
  <div class="row-spacer sm-hide"></div>
  </form>
  
  <div class="row-spacer sm-hide"></div>
  <div class="row-spacer-xs sm-show"></div>
  <hr class="sm-show">
  <?php endif; ?>
  <?php if($bundle === 'article'): ?>
  <div data-posturl="<?php print url('api/articles'); ?>" data-plugin="filterContents">
  <?php elseif($bundle === 'gallery'): ?>
  <div data-posturl="<?php print url('api/gallery'); ?>" data-plugin="filterContents">
  <?php else: ?>
  <div>
  <?php endif; ?>
  <?php print $output; ?>
  </div>
</div><!--/block-->