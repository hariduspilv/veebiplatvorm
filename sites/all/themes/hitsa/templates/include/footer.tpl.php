<div class="inline">
  <div class="row">
    <div class="col-4 sm-12">
      <?php if(!empty($footer_general_contact)): ?>
      <h3><?php print t('General contact'); ?></h3>
        <?php print $footer_general_contact; ?>
      <?php endif; ?>
    </div><!--/col-4-->
    <div class="col-8 sm-12">
      <?php if(!empty($footer_important_contact)): ?>
      <h3><?php print t('Important contacts'); ?></h3>
        <?php print $footer_important_contact; ?>
      <?php endif; ?>
    </div><!--/col-4-->
  </div><!--/row-->
</div><!--/inline-->

<div class="map">
  <iframe src="https://www.google.com/maps/embed?pb=!1m18!1m12!1m3!1d2120.677165355292!2d27.011086316401293!3d57.89163583248798!2m3!1f0!2f0!3f0!3m2!1i1024!2i768!4f13.1!3m3!1m2!1s0x46eae4e87664624f%3A0x862356c0f15c8fc!2sV%C3%B5rumaa+Kutsehariduskeskus!5e0!3m2!1set!2see!4v1505983870537" style="border:0" allowfullscreen></iframe>
</div><!--/map-->
   
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