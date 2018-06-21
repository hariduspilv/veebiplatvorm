<header class="mobile" data-plugin="mobileMenu">
  
  <div class="main-links">
     <a href="javascript:void(0);" class="before-menu" data-trigger="menu"><?php print t('Menu'); ?></a>
     <div class="pull-right">
        <a href="javascript:void(0);" class="before-link" data-trigger="links"></a>
        <a href="javascript:void(0);" class="before-search" data-trigger="search"></a>
     </div><!--/pull-right-->
  </div><!--/main-links-->
  
  <div data-target="search" class="mobile-search">
     <form method="get" action="<?php print url('search'); ?>">
        <div class="form-item">
           <input name="query" type="text" placeholder="<?php print t('Search'); ?>..."/>
           <button type="submit"></button>
        </div><!--/form-item-->
     </form>
  </div><!--/search-->
  
  <div class="mobile-menu">
     <div class="panel-header">
        <?php if(!empty($language_switcher_mobile)): ?>
          <?php print $language_switcher_mobile; ?>
        <?php endif; ?>
        <div class="closeBtn"></div>
     </div><!--/panel-header-->
     
     <?php if(!empty($main_menu_mobile)): ?>
       <?php print render($main_menu_mobile); ?>
     <?php endif; ?>
     
  </div><!--/mobile-menu-->
  
  <div class="mobile-quick-links">
     <div class="panel-header">
        <div class="panel-title before-link"><?php print t('External links'); ?></div>
        <div class="closeBtn"></div>
     </div><!--/panel-header-->
     
     <?php print render($quicklinks_menu); ?>
     
  </div><!--/mobile-quick-links-->
      
</header><!--/mobile-->
   
<?php if(!empty($site_logo)): ?>
<div class="mobile-logo">
   <a href="<?php print url('<front>'); ?>" class="header-logo"><img alt="" src="<?php print $site_logo; ?>" /></a>
</div><!--/mobile-logo-->
<?php endif; ?>