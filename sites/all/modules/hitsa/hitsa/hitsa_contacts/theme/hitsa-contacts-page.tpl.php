<div class="row">
  <div class="col-<?php if(!empty($locations)) {print 9;} else {print 12;} ?>">
            
    <div class="block">
               
      <h2 class="block-title"><?php print t('Contact'); ?></h2>
      
      <div class="row">
         <div class="col-12">
            <h3><?php print t('Filter'); ?></h3>
         </div><!--/col-12-->
      </div><!--/row-->
      
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
          
        </div><!--/col-9-->
        
        <div class="col-3">

        </div><!--/col-3-->
        
      </div><!--/row-->
      
      <div class="row-spacer-xs"></div>
      <hr />
      <div class="row-spacer"></div>
               
      <div class="row">
        <div class="col-12">
          <div class="form-item-row">
            <div class="form-item after-search form-item_rounded">
              <div class="form-item_title"><?php print t('Search for person'); ?></div>
              <input type="text" name="person" placeholder="<?php print t('Search for person'); ?>" data-plugin="autocomplete" data-url="<?php print url('api/contact-autocomplete'); ?>" data-onsubmit="true" autocomplete="off"/>
            </div><!--/form-item-->

            <div class="form-item form-item_rounded">
              <div class="form-item_title"><?php print t('Job position'); ?></div>
              <select name="profession" data-plugin="SumoSelect">
                 <option value=""><?php print t('Select category'); ?></option>
                 <?php foreach($job_positions as $j): ?>
                   <option value="<?php print $j->tid; ?>"><?php print check_plain($j->name); ?></option>
                 <?php endforeach; ?>
              </select>
            </div><!--/form-item-->

            <div class="form-item">
              <div class="form-item_title">&nbsp;</div>
              <button class="btn btn-filled"><?php print t('Search'); ?></button>
            </div><!--/form-item-->
                        
          </div><!--/form-item-row-->
        </div><!--/col-12-->
      </div><!--/row-->
               
      </form>
               
      <div class="row">
        <div class="col-12" data-posturl="<?php print url('api/contact'); ?>" data-plugin="filterContents">
          <?php print $contact_accordion; ?>
        </div><!--/col-12-->
      </div><!--/row-->
    </div><!--/block-->
      
    <?php if(!empty($contact_form)): ?>     
    <div class="block">
      
      <h2 class="block-title"><?php print t('Contact us'); ?></h2>
      <?php print render($contact_form); ?>
    </div><!--/block-->
    <?php endif; ?>
            
  </div><!--/col-9-->
  <?php if(!empty($locations)): ?>
  <div class="col-3">
    <?php foreach($locations as $location): ?>
    <div class="block block-narrow">
      <h2 class="block-title"><?php print check_plain($location->title); ?></h2>

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
                    <a href="mailto:<?php print check_plain($location->e_mail[LANGUAGE_NONE][0]['email']); ?>"><?php print check_plain($location->e_mail[LANGUAGE_NONE][0]['email']); ?></a>
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
            <div class="map-wrapper">
							<div class="map" data-plugin="googleMaps" data-coords="<?php 
							print sprintf('%s,%s', $location->location_coordinates[LANGUAGE_NONE][0]['lat'], 
							$location->location_coordinates[LANGUAGE_NONE][0]['lng']); ?>" 
							data-icon="<?php print '/' . drupal_get_path('theme', $GLOBALS['theme']) . '/static/assets/imgs/mapIcon.png'; ?>" data-zoom="15"></div>
							<img src="<?php print '/' . drupal_get_path('theme', $GLOBALS['theme']) . '/static/assets/imgs/placeholder-56.gif'; ?>">
						</div>
          </div><!--/accordion-content-->
        </div><!--/accordion-entry-->
        <?php endif; ?>
        
        <?php if(!empty($location->location_parking)): ?>
        <div class="accordion-entry">
          <div class="accordion-title"><?php print t('Parking'); ?></div>
          <div class="accordion-content">
             <?php print nl2br(check_plain($location->location_parking[LANGUAGE_NONE][0]['safe_value'])); ?>
          </div><!--/accordion-content-->
        </div><!--/accordion-entry-->
        <?php endif; ?>
        
        <?php if(!empty($location->location_transport)): ?>
        <div class="accordion-entry">
          <div class="accordion-title"><?php print t('Transportation'); ?></div>
          <div class="accordion-content">
            <?php print nl2br(check_plain($location->location_transport[LANGUAGE_NONE][0]['safe_value'])); ?>
          </div><!--/accordion-content-->
        </div><!--/accordion-entry-->
        <?php endif; ?>
        
      </div><!--/accordion-->
               
    </div><!--/block-->
    <?php endforeach; ?>
    
            
  </div><!--/col-3-->
  <?php endif; ?>
</div><!--/row-->