<?php if(!empty($locations)): ?>
  <?php
  $i = 0;
  foreach($locations as $location): ?>
  <div class="block block-narrow <?php if($type === 'primary') {print 'sm-show';} else if($i === 0) print 'sm-hide'; ?>">
    <?php if((node_access("update", $location, $user) === TRUE)): ?>
      <ul class="tabs primary" style="margin-bottom: 30px;">
        <li><a href="<?php print url('node/' . $location->nid . '/edit'); ?>"><?php print t('Edit'); ?></a></li>
        <li><a href="<?php print url('node/' . $location->nid . '/translate'); ?>"><?php print t('Translate'); ?></a></li>
      </ul>
    <?php endif; ?>
    <h2 class="block-title sm-borderless"><?php print check_plain($location->title); ?></h2>

    <div class="accordion accordion-xs" data-plugin="accordion">

      <div class="accordion-entry">
        <div class="accordion-title"><?php print t('General information'); ?></div>
        <div class="accordion-content">

          <ul class="list-details">
            <?php if(!empty($location->location_address)): ?>
            <li>
              <div class="before-home"></div>
              <div class="list-details_text">
                <p><?php print check_plain($location->location_address[LANGUAGE_NONE][0]['safe_value']); ?> </p>
              </div><!--/list-details_text-->
            </li>
            <?php endif; ?>
            <?php if(!empty($location->phone_nr)): ?>
            <?php foreach ($location->phone_nr[LANGUAGE_NONE] as $phone_number):?>
            <li>
            <div class="before-phone"></div>
            <div class="list-details_text">
              <p><?php print check_plain($phone_number['safe_value']); ?></p>
            </div><!--/list-details_text-->
            </li>
            <?php endforeach; ?>
            <?php endif; ?>
            <?php if(!empty($location->e_mail)): ?>
            <li>
              <div class="before-envelope"></div>
              <div class="list-details_text">
                <p>
                <a href="javascript:void(0);" class="email-tooltip tooltipstered" data-tooltip-content="#email-<?php print $i?>"><?php print t('E-mail')?> </a>

                </p>
                <div class="d-none">
                                  <div id="email-<?php print $i?>" class="tooltip-content">
                                    <?php print hitsa_core_email_obfuscator_link($location->e_mail,'mailto')?>
                                  </div><!--tooltip-content-->
                                 </div><!--/d-none-->
              </div><!--/list-details_text-->
            </li>
            <?php endif; ?>
            <?php if(!empty($location->location_visiting_hours)): ?>
            <li>
              <div class="before-unlock"></div>
              <div class="list-details_text">
                <p><?php print check_plain($location->location_visiting_hours[LANGUAGE_NONE][0]['safe_value']); ?></p>
              </div><!--/list-details_text-->
            </li>
            <?php endif; ?>
          </ul><!--/list-details-->

        </div><!--/accordion-content-->
      </div><!--/accordion-entry-->
      <?php if(!empty($location->full_map)): ?>
      <div class="accordion-entry">
        <div class="accordion-title"><?php print t('Map'); ?></div>
        <div class="accordion-content" style="height:300px; width:100%">
          <?php print $location->full_map?>

        </div><!--/accordion-content-->
      </div><!--/accordion-entry-->
      <?php endif; ?>

      <?php if(!empty($location->location_parking) || !empty($location->location_parking_attachment)): ?>
      <div class="accordion-entry">
        <div class="accordion-title"><?php print t('Parking'); ?></div>
        <div class="accordion-content">
          <?php if(!empty($location->location_parking)): ?>
          <p><?php print nl2br(check_plain($location->location_parking[LANGUAGE_NONE][0]['safe_value'])); ?></p>
          <?php endif; ?>
          <?php if(!empty($location->location_parking_attachment)): ?>
          <ul class="list-details">
            <li>
              <div class="list-details_text">
                <p>
                  <a href="<?php print file_create_url($location->location_parking_attachment[LANGUAGE_NONE][0]['uri']); ?>" target="_blank">
                  <?php if(!empty($location->location_parking_attachment[LANGUAGE_NONE][0]['description'])): ?>
                    <?php print $location->location_parking_attachment[LANGUAGE_NONE][0]['description']; ?>
                  <?php else: ?>
                    <?php print t('Attachment'); ?>
                  <?php endif; ?>
                  </a>

                </p>
              </div>
            </li>
          </ul>
          <?php endif; ?>
        </div><!--/accordion-content-->
      </div><!--/accordion-entry-->
      <?php endif; ?>

      <?php if(!empty($location->location_transport)): ?>
      <div class="accordion-entry">
        <div class="accordion-title"><?php print t('Transportation'); ?></div>
        <div class="accordion-content">
          <p><?php print nl2br(check_plain($location->location_transport[LANGUAGE_NONE][0]['safe_value'])); ?></p>
        </div><!--/accordion-content-->
      </div><!--/accordion-entry-->
      <?php endif; ?>
      <?php if(!empty($location->field_extra_info)):?>
      <div class="accordion-entry">
        <?php if(!empty($location->field_extra_info_title)):?>
          <div class="accordion-title"><?php print $location->field_extra_info_title[LANGUAGE_NONE][0]['safe_value'] ?></div>
        <?php else:?>
        <div class="accordion-title"><?php print t('Extra information'); ?></div>
        <?php endif?>
        <div class="accordion-content">
          <?php print $location->field_extra_info[LANGUAGE_NONE][0]['safe_value']?>
        </div>
      </div>
      <?php endif;?>
    </div><!--/accordion-->

  </div><!--/block-->
  <?php
  $i++;
  endforeach; ?>
<?php endif; ?>
