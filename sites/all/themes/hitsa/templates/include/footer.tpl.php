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
    </div><!--/col-4-->
  </div><!--/row-->
</div><!--/inline-->

<?php if(!empty($hitsa_school_place_id)): ?>
<div class="map">
  <iframe src="https://www.google.com/maps/embed/v1/place?key=AIzaSyBQW5d3aaKFwt_7LaKW683Q8VAcJjv7SbU&q=<?php print urlencode($hitsa_school_place_id); ?>" style="border:0" allowfullscreen></iframe>
</div><!--/map-->
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