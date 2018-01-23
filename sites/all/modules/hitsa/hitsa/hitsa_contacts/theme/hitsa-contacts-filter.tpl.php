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
      
    </div><!--/col-12-->
    
  </div><!--/row-->
  
  <div class="row-spacer-xs sm-hide"></div>
  <hr />
  <div class="row-spacer sm-hide"></div>
           
  <div class="row">
    <div class="col-8">
      <div class="form-item-row">
        <div class="form-item after-search form-item_rounded form-item-stretch">
          <div class="form-item_title"><?php print t('Search for person'); ?></div>
          <input type="text" name="person" placeholder="<?php print t('Search for person'); ?>" data-plugin="autocomplete" data-url="<?php print url('api/contact-autocomplete/' . $contact_nid); ?>" data-onsubmit="true" autocomplete="off"/>
        </div><!--/form-item-->
        
        <div class="form-item form-item_rounded form-item-stretch">
          <div class="form-item_title"><?php print t('Job position'); ?></div>
          <select name="profession" data-plugin="SumoSelect">
             <option value=""><?php print t('Select category'); ?></option>
             <?php foreach($job_positions as $j): ?>
               <option value="<?php print $j->tid; ?>"><?php print check_plain($j->name); ?></option>
             <?php endforeach; ?>
          </select>
        </div><!--/form-item-->
        <div class="form-item">
          <div class="form-item_title sm-hide">&nbsp;</div>
          <button class="btn btn-filled"><?php print t('Search'); ?></button>
        </div><!--/form-item-->
                    
      </div><!--/form-item-row-->
    </div><!--/col-12-->
  </div><!--/row-->
  <?php if(!empty($contact_nid)): ?>
    <input type="hidden" name="nid" value="<?php print $contact_nid; ?>">
  <?php endif; ?>
</form>