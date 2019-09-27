<div class="highlight-bg-1">
   <div class="inline">
      <div class="row">
        <div class="col-6">
          <?php print render($quicklinks_menu); ?>
        </div><!--/col-6-->
        <div class="col-6 flex-right">
          <?php if(!empty($language_switcher)): ?>
            <?php print $language_switcher; ?>
          <?php else: ?>
          <ul class="header-quicklinks">
            <li>
              <form method="get" action="<?php print url('search'); ?>">
                <div class="header-search">
                  <input type="text" name="query" placeholder="<?php print t('Search'); ?>">
                  <button></button>
                </div>
              </form>
            </li>
          </ul>
          <?php endif; ?>
        </div><!--/col-6-->
      </div><!--/row-->
   </div><!--/inline-->
</div><!--/highlight-bg-->

<div class="inline">
   <div class="row">
     <?php if(!isset($header_menu_1)):?>
      <div class="col-6">
        <?php if(!empty($site_logo)): ?>
        <a href="<?php print url('<front>'); ?>" class="header-logo"><img style="max-width: 140%" alt="" src="<?php print $site_logo; ?>" /></a>
        <?php endif; ?>
      </div><!--/col-9-->
      <div class="col-6">
        <div class="bullet-links-wrapper">
        <?php print render($header_menu); ?>
        </div>
      </div><!--/col-3-->
        <?php else:?>
          <div class="col-6">

            <?php if(!empty($site_logo)): ?>
            <a href="<?php print url('<front>'); ?>" class="header-logo"><img style="max-width: 140%" alt="" src="<?php print $site_logo; ?>" /></a>
            <?php endif; ?>
          </div><!--/col-9-->
          <div class="col-6">
            <div class="bullet-links-wrapper">
              <?php print render($header_menu_0); ?>
              <?php print render($header_menu_1); ?>
            </div>
          </div>
        <?php endif?>
   </div><!--/row-->
</div><!--/inline-->

<div class="header-nav" data-plugin="mainMenu">
   <div class="inline">
      <div class="row">
         <div class="col-12">
            <?php print render($main_menu); ?>
         </div><!--/col-12-->
      </div><!--/row-->
   </div><!--/inline-->
</div><!--/header-nav-->
