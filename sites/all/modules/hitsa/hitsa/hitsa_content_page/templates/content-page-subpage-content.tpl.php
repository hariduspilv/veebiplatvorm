<article id="subpage">
  <h3><?php $title = field_get_items('paragraphs_item', $subpage, 'subpage_title'); print check_plain($title[0]['safe_value']); ?>
    <span class="btn-bar align-right pull-right">
       <a href="" class="btn-circle before-share" data-plugin="share"></a>
       <a href="javascript:window.print();" class="btn-circle before-print"></a>
    </span><!--/button-row-->
  </h3>

  <?php if(!empty($subpage->subpage_body)): ?>
    <?php if(!empty($subpage->subpage_body[LANGUAGE_NONE][0]['safe_summary'])): ?>
    <div class="intro">
       <?php print nl2br($subpage->subpage_body[LANGUAGE_NONE][0]['safe_summary']); ?>
    </div><!--/intro-->
    <?php endif; ?>
    
    <?php if(!empty($subpage->subpage_body[LANGUAGE_NONE][0]['safe_value'])): ?>
      <?php print nl2br($subpage->subpage_body[LANGUAGE_NONE][0]['safe_value']); ?>
    <?php endif; ?>
  <?php endif; ?>
  
  <?php if(!empty($subpage->subpage_images)): ?>
    <div class="row">
    <?php foreach($subpage->subpage_images[LANGUAGE_NONE] as $image): ?>
      <div class="col-6 sm-12">
        <figure>
          <img src="<?php print image_style_url('hitsa_core_thumbnail', $image['uri']); ?>" alt="<?php print $image['alt']; ?>">
          <figcaption><?php print $image['title']; ?></figcaption>
        </figure>
      </div>
    <?php endforeach; ?>
    </div>
  <?php endif; ?>
  
  <?php if(!empty($subpage->cinfo_contact_person)): ?>
    <p>
      <b><?php print check_plain($subpage->cinfo_contact_person[LANGUAGE_NONE][0]['safe_value']); ?></b>
    </p>
  <?php endif; ?>
  <ul class="list-details">
    <?php if(!empty($subpage->cinfo_homepage_url)): ?>
    <li>
       <div class="before-home"></div>
       <div class="list-details_text">
          <p>
            <a href="<?php print check_url($subpage->cinfo_homepage_url[LANGUAGE_NONE][0]['url']); ?>" target="_blank">
            <?php print check_url($subpage->cinfo_homepage_url[LANGUAGE_NONE][0]['url']); ?>
            </a>
          </p>
       </div><!--/list-details_text-->
    </li>
    <?php endif; ?>
    <?php if(!empty($subpage->cinfo_e_mail)): ?>
    <li>
       <div class="before-envelope"></div>
       <div class="list-details_text">
          <p>
            <a href="mailto:<?php print check_plain($subpage->cinfo_e_mail[LANGUAGE_NONE][0]['email']); ?>">
              <?php print check_plain($subpage->cinfo_e_mail[LANGUAGE_NONE][0]['email']); ?>
            </a>
          </p>
       </div><!--/list-details_text-->
    </li>
    <?php endif; ?>
    <?php if(!empty($subpage->cinfo_phone_nr)): ?>
    <li>
       <div class="before-phone"></div>
       <div class="list-details_text">
          <p><?php print check_plain($subpage->cinfo_phone_nr[LANGUAGE_NONE][0]['safe_value']); ?></p>
       </div><!--/list-details_text-->
    </li>
    <?php endif; ?>
    <?php if(!empty($subpage->cinfo_address)): ?>
    <li>
       <div class="before-location"></div>
       <div class="list-details_text">
          <p><?php print check_plain($subpage->cinfo_address[LANGUAGE_NONE][0]['safe_value']); ?></p>
       </div><!--/list-details_text-->
    </li>
    <?php endif; ?>
  </ul>
</article>