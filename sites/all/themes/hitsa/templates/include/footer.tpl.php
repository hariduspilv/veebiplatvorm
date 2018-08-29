<div class="inline">
  <div class="row">
    <?php if(!empty($partners)): ?>
      <?php print $partners; ?>
    <?php endif; ?>
    <div class="col-4 sm-12">
      <?php if(!empty($footer_general_contact)): ?>
      <h3><?php print t('General contact'); ?></h3>
        <p><?php print $footer_general_contact; ?></p>
      <?php endif; ?>
    </div><!--/col-4-->
    <div class="col-<?php if(!empty($partners) && !empty($footer_general_contact)) {print 4;}else{print 8;}; ?> sm-12">
      <?php if(!empty($important_contacts)): ?>
      <h3><?php print t('Important contacts'); ?></h3>
      <table>
        <tbody>
        <?php print $important_contacts; ?>
        </tbody>
      </table>
      <?php endif; ?>
      <?php if(!empty($footer_text_area)):?>
      <?php if(!empty($footer_text_area_title)):?>
      <h3><?php print $footer_text_area_title ?></h3>
      <?php endif?>
      <?php print $footer_text_area?>
      <?php endif;?>
    </div><!--/col-4-->
  </div><!--/row-->
</div><!--/inline-->

<?php if(!empty($hitsa_school_place_coords) && !empty($google_api_key)): ?>
  <a href="<?php if(!empty($hitsa_school_place_address)) print $hitsa_school_place_address; ?>" target="_blank" class="map" data-plugin="googleMaps" data-coords="<?php print check_plain($hitsa_school_place_coords); ?>" data-icon="<?php print '/' . drupal_get_path('theme', $GLOBALS['theme']) . '/static/assets/imgs/mapIcon.png'; ?>">
</a><!--/map-->
<?php endif; ?>
   
<div class="inline">
  <div class="row">
    <div class="col-12 text-center">
      <?php if(!empty($footer_menu)): ?>
      <?php print render($footer_menu); ?>
      <?php endif; ?>
      <?php if(!empty($copyright_notice)): ?>
      <p><?php print check_plain($copyright_notice); ?></p>
      <?php endif; ?>
    </div><!--/col-12-->
  </div><!--/row-->
   
</div><!--/inline-->