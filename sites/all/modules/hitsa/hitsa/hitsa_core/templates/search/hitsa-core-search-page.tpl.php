<div class="block" id="all">

  <h2 class="block-title"><span class="sm-hide"><?php print t('Searching for'); ?> <i>"<?php print check_plain($search_query); ?>"</i>
    (<?php print t('!count results found', array('!count' => $result_count)); ?>)</span>
    <span class="sm-show"><?php print t('Searching'); ?> "<?php print check_plain($search_query); ?>" (<?php print t('!count results', array('!count' => $result_count)); ?>)</span>
  </h2>

  <?php if(!empty($bundle_filter)): ?>
  <div class="row">
     <div class="col-12">
        <h3><?php print t('Filter categories'); ?></h3>
     </div><!--/col-12-->
  </div><!--/row-->

  <form method="post" data-plugin="filters">
    <input type="hidden" name="query" data-onsubmit="true" value="<?php print check_plain($search_query); ?>">

    <div class="row">
      <div class="col-12">

					<div class="btn-bar">
            <span class="btn-input">
               <input type="checkbox" name="category" value="all" checked="">
               <span class="btn btn-xs btn-alternate"><?php print t('All'); ?></span>
            </span><!--/btn-input-->

            <?php foreach($bundle_filter as $bundle => $name): ?>
            <span class="btn-input">
               <input type="checkbox" name="category" value="<?php print check_plain($bundle); ?>">
               <span class="btn btn-xs btn-alternate"><?php print check_plain($name); ?></span>
            </span><!--/btn-input-->
            <?php endforeach; ?>

          </div><!--/btn-bar-->

        </div><!--/col-12-->
    </div><!--/row-->

    <div class="row-spacer-xs sm-hide"></div>
    <hr>
    <div class="row-spacer sm-hide"></div>

    <div class="row">
       <div class="col-12">
          <div class="form-item-row">

             <div class="form-item after-search form-item_rounded form-item-stretch">
                <div class="form-item_title"><?php print t('Search by title'); ?></div>
                <input type="text" name="query" placeholder="<?php print t('Start typing'); ?>" data-url="api/autocomplete.json" data-onSubmit="true" autocomplete="off">
             </div><!--/form-item-->

             <div class="form-item form-item_rounded after-calendar form-item-stretch">
                <div class="form-item_title"><?php print t('Date'); ?></div>
                <input type="text" name="date" data-plugin="datepickerRange" data-onSubmit="true" placeholder="<?php print t('Choose date (range)'); ?>">
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
  <?php endif; ?>

	<div data-posturl="<?php print url('api/search'); ?>" data-plugin="filterContents">
    <?php print $result_output; ?>
	</div>
</div>
