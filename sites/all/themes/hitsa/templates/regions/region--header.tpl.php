<?php

/**
 * @file
 * Default theme implementation to display a region.
 *
 * Available variables:
 * - $content: The content for this region, typically blocks.
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the following:
 *   - region: The current template type, i.e., "theming hook".
 *   - region-[name]: The name of the region with underscores replaced with
 *     dashes. For example, the page_top region would have a region-page-top class.
 * - $region: The name of the region variable as defined in the theme's .info file.
 *
 * Helper variables:
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $is_admin: Flags true when the current user is an administrator.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 *
 * @see template_preprocess()
 * @see template_preprocess_region()
 * @see template_process()
 *
 * @ingroup themeable
 */
?>

<div class="highlight-bg-1">
   <div class="inline">
      <div class="row">
        <div class="col-8">
          <?php print render($quicklinks_menu); ?>
        </div><!--/col-6-->
        <div class="col-4 flex-right">
          <?php if(!empty($language_switcher)): ?>
            <?php print $language_switcher; ?>
          <?php endif; ?>
        </div><!--/col-6-->
      </div><!--/row-->
   </div><!--/inline-->
</div><!--/highlight-bg-->

<div class="inline">
   <div class="row">
      <div class="col-9">
        <?php if(!empty($site_logo)): ?>
        <a href="<?php print url('<front>'); ?>" class="header-logo"><img alt="" src="<?php print $site_logo; ?>" /></a>
        <?php endif; ?>
      </div><!--/col-9-->
      <div class="col-3">
        <?php print render($header_menu); ?>
      </div><!--/col-3-->
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
<?php if ($content): ?>
  
    <?php print $content; ?>
  
<?php endif; ?>
