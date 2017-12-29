<div class="inline">
      
  <div class="row">
    <div class="col-12">
        
      <div class="block">
         
         <h1 class="block-title"><?php print t('Log in'); ?></h1>
         <div class="row">
          <div class="col-6 sm-12 col-border-after sm-hide">
            <div class="login-block">
               <h1><?php print t('Log in using ID card'); ?></h1>
               
               <?php print render($id_form); ?>
               
            </div><!--/login-block-->
          </div><!--/col-6-->
          <div class="col-6 sm-12">
             <div class="login-block">
                <h1><?php print t('Log in using mobile ID'); ?></h1>
                
                <?php print render($mobile_id_form); ?>
                
             </div><!--/login-block-->
          </div><!--/col-6-->
         </div><!--/row-->
         
      </div><!--/block-->
        
    </div><!--/col-12-->
  </div><!--/row-->
      
</div>