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
            <li>
            <div class="before-phone"></div>
            <div class="list-details_text">
              <p><?php print check_plain($location->phone_nr[LANGUAGE_NONE][0]['safe_value']); ?></p>
            </div><!--/list-details_text-->
            </li>
            <?php endif; ?>
            <?php if(!empty($location->e_mail)): ?>
            <li>
              <div class="before-envelope"></div>
              <div class="list-details_text">
                <p>
                  <?php print spamspan(check_plain($location->e_mail[LANGUAGE_NONE][0]['email'])); ?>
                </p>
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
      <?php if(!empty($location->location_coordinates)): ?>
      <div class="accordion-entry">
        <div class="accordion-title"><?php print t('Map'); ?></div>
        <div class="accordion-content">
        <?php if(!empty($location->address_link)):?>
        <a target="_blank" href="<?php print $location->address_link ?>" class="map-wrapper">
        <?php else:?>
        <a href="http://maps.google.com" class="map-wrapper">
        <?php endif;?>
          
						<div class="map" data-plugin="googleMaps" data-coords="<?php 
						print sprintf('%s,%s', $location->location_coordinates[LANGUAGE_NONE][0]['lat'], 
						$location->location_coordinates[LANGUAGE_NONE][0]['lng']); ?>" 
						data-icon="<?php print '/' . drupal_get_path('theme', $GLOBALS['theme']) . '/static/assets/imgs/mapIcon.png'; ?>" data-zoom="15"></div>
						<img alt="" src="<?php print '/' . drupal_get_path('theme', $GLOBALS['theme']) . '/static/assets/imgs/placeholder-56.gif'; ?>">
					</a>
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
        
    </div><!--/accordion-->
               
  </div><!--/block-->
  <?php 
  $i++;
  endforeach; ?>
<?php endif; ?>