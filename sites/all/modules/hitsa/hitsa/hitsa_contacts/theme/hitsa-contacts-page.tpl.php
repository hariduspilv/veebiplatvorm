<div class="block">
               
      <h2 class="block-title"><?php print t('Contact'); ?></h2>
      
      <div class="row">
         <div class="col-12">
            <h3><?php print t('Filter'); ?></h3>
         </div><!--/col-12-->
      </div><!--/row-->
      
      <form method="post" action="<?php print url('contact'); ?>" data-plugin="filters">
      <div class="row">
        <div class="col-12">
           
          <div class="btn-bar">
            
             <span class="btn-input">
                <input type="checkbox" name="category" value="all" checked />
                <span class="btn btn-xs btn-alternate"><?php print t('All'); ?></span>
             </span><!--/btn-input-->
             
             <?php foreach($contact_departments as $delta => $department): ?>
             <span class="btn-input"<?php /*if($delta > 2) print ' data-show="hiddenFilter | inlineBlock"';*/ ?>>
                <input type="checkbox" name="category" value="<?php print $department->tid; ?>" />
                <span class="btn btn-xs btn-alternate"><?php print check_plain($department->name); ?></span>
             </span><!--/btn-input-->
             <?php endforeach; ?>
          </div><!--/btn-bar-->
          
        </div><!--/col-9-->
        
        <div class="col-3">

        </div><!--/col-3-->
        
      </div><!--/row-->
      
      <div class="row-spacer-xs"></div>
      <hr />
      <div class="row-spacer"></div>
               
      <div class="row">
        <div class="col-12">
          <div class="form-item-row">
            <div class="form-item after-search form-item_rounded">
              <div class="form-item_title"><?php print t('Search for person'); ?></div>
              <input type="text" name="person" placeholder="<?php print t('Search for person'); ?>" data-plugin="autocomplete" data-url="<?php print url('api/contact-autocomplete'); ?>" data-onsubmit="true" autocomplete="off"/>
            </div><!--/form-item-->

            <div class="form-item form-item_rounded">
              <div class="form-item_title"><?php print t('Job position'); ?></div>
              <select name="profession" data-plugin="SumoSelect">
                 <option value=""><?php print t('Select category'); ?></option>
                 <?php foreach($job_positions as $j): ?>
                   <option value="<?php print $j->tid; ?>"><?php print check_plain($j->name); ?></option>
                 <?php endforeach; ?>
              </select>
            </div><!--/form-item-->

            <div class="form-item">
              <div class="form-item_title">&nbsp;</div>
              <button class="btn btn-filled"><?php print t('Search'); ?></button>
            </div><!--/form-item-->
                        
          </div><!--/form-item-row-->
        </div><!--/col-12-->
      </div><!--/row-->
               
      </form>
               
      <div class="row">
        <div class="col-12" data-posturl="<?php print url('api/contact'); ?>" data-plugin="filterContents">
          <?php print $contact_accordion; ?>
        </div><!--/col-12-->
      </div><!--/row-->
    </div><!--/block-->
      
<?php if(!empty($contact_form)): ?>     
<div class="block">
  
  <h2 class="block-title"><?php print t('Contact us'); ?></h2>
  <?php print render($contact_form); ?>
</div><!--/block-->
<?php endif; ?>