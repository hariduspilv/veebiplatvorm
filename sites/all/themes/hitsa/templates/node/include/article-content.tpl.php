<div class="block">
  <?php if(!empty($article_type) && !empty($article_types_list[$article_type[0]['value']])): 
  $heading_title = check_plain($article_types_list[$article_type[0]['value']]);
  ?>
  <h2 class="block-title"><?php print $heading_title; ?></h2>
  <?php elseif($node->type === 'content_page' && $node->cp_type[LANGUAGE_NONE][0]['value'] === 'cp_service'): 
  $heading_title = t('Services');
  ?>
  <h1 class="block-title"><?php print $heading_title; ?></h1>
  <?php else: 
  $heading_title = $title;
  ?>
    <h1 class="block-title"><?php print $heading_title; ?></h1>
  <?php endif; ?>

  <div class="row-spacer-xs"></div>
  <div class="row">
    <?php if(!empty($content['cp_type']) && $content['cp_type']['#items'][0]['value'] === 'cp_contacts'): ?>
      <?php if(!empty($content['cp_contacts'])): ?>
        <?php 
        $i = 0;
        while(!empty($content['cp_contacts']['#items'][$i])): ?>
        <div class="col-12">
        <?php print render($content['cp_contacts'][$i]); ?>
        </div>
        <?php if(!empty($content['cp_contacts'][$i+1])): ?>
        <hr class="spacing-xl">
        <?php endif; ?>
        <?php $i++; endwhile; ?>
      <?php endif; ?>
    <?php else: ?>
    <div class="col-8 sm-12">
      <article class="padding-right">
        <div class="btn-bar align-right sm-show sm-pull_right">
          <a href="" class="btn-circle before-share"></a>
          <a href="javascript:window.print();" class="sm-hide btn-circle before-print"></a>
        </div>
        <?php if($node->type === 'article'): ?>
        <h1><?php print $title; ?>
          <span class="editor-info">
				  	<span class="before-calendar"><?php print format_date($node->created, 'hitsa_date_month'); ?></span>
				  	<?php if(!empty($author_name)): ?>
				  	<span class="before-user"><?php print check_plain($author_name); ?></span>
				  	<?php endif; ?>
				  </span>
				</h1>
				<?php else: ?>
				<h1><?php print $title; ?></h1>
        <?php endif; ?>
        
        <?php if(!empty($body)): ?>
        <?php if(!empty($body[0]['safe_summary'])): ?>
        <div class="intro">
           <?php print $body[0]['safe_summary']; ?>
        </div><!--/intro-->
        <?php endif; ?>
        
        <?php if(!empty($body[0]['safe_value'])): ?>
          <?php print $body[0]['safe_value']; ?>
        <?php endif; ?>
        <?php endif; ?>

        <?php if(!empty($cinfo_contact_person)): ?>
          <p>
            <b><?php print check_plain($cinfo_contact_person[0]['safe_value']); ?></b>
          </p>
        <?php endif; ?>
        <ul class="list-details">
          <?php if(!empty($cinfo_homepage_url)): ?>
          <li>
             <div class="before-home"></div>
             <div class="list-details_text">
                <p>
                  <a href="<?php print check_url($cinfo_homepage_url[0]['url']); ?>" target="_blank">
                  <?php print preg_replace('/^https?:\/\//', '', check_url($cinfo_homepage_url[0]['url'])); ?>
                  </a>
                </p>
             </div><!--/list-details_text-->
          </li>
          <?php endif; ?>
          <?php if(!empty($cinfo_e_mail)): ?>
          <li>
             <div class="before-envelope"></div>
             <div class="list-details_text">
                <p>
                  <?php print spamspan(check_plain($cinfo_e_mail[0]['email'])); ?>
                </p>
             </div><!--/list-details_text-->
          </li>
          <?php endif; ?>
          <?php if(!empty($cinfo_phone_nr)): ?>
          <li>
             <div class="before-phone"></div>
             <div class="list-details_text">
                <p><?php print check_plain($cinfo_phone_nr[0]['safe_value']); ?></p>
             </div><!--/list-details_text-->
          </li>
          <?php endif; ?>
          <?php if(!empty($cinfo_address)): ?>
          <li>
             <div class="before-location"></div>
             <div class="list-details_text">
                <p><?php print check_plain($cinfo_address[0]['safe_value']); ?></p>
             </div><!--/list-details_text-->
          </li>
          <?php endif; ?>
        </ul>
        
        <?php if($node->type === 'article'): ?>
          <div class="row-spacer-xs"></div>
          <span class="article-date">
            <i><?php print t('Last changed') . ': ' . date('d.m.Y', $node->changed); ?></i>
          </span>
        <?php endif; ?>
      </article>
    </div><!--/col-8-->
    <div class="col-4 sm-12 no-print">
    
      <div class="row-spacer-xl"></div>

      <?php if(!empty($subpage_images) || (!empty($cp_image) && $subpage_images = $cp_image)): $image = $subpage_images[0]; // Gallery ?>
        <figure>
          <a href="<?php print image_style_url('hitsa_article_modal_view', $image['uri']); ?>"
          data-plugin="modal" data-heading="<?php print $heading_title; ?>" data-closebutton="<?php print t('Close'); ?>">
            <img src="<?php print image_style_url('hitsa_core_thumbnail', $image['uri']); ?>" 
            alt="<?php if(!empty($image['field_file_image_alt_text'])) print check_plain($image['field_file_image_alt_text'][LANGUAGE_NONE][0]['value']); ?>">
          </a>
          <figcaption><?php if(!empty($image['field_file_image_title_text'])) print check_plain($image['field_file_image_title_text'][LANGUAGE_NONE][0]['value']); ?></figcaption>
        </figure>
      <?php endif; ?>
      <?php if(!empty($article_video)): ?>
      <figure>
        <a href="<?php print file_create_url($article_video[0]['uri']); ?>" 
        title="<?php print check_plain($article_video[0]['filename']); ?>" 
        data-plugin="modal" data-closebutton="<?php print t('Close'); ?>">
          <?php if(!empty($video_thumbnail)): ?>
          <img src="<?php print $video_thumbnail; ?>" 
          alt="<?php print check_plain($article_video[0]['filename']); ?>">
          <?php else: ?>
          <img src="<?php print image_style_url('hitsa_core_thumbnail', $image['uri']); ?>" 
          alt="<?php if(!empty($image['field_file_image_alt_text'])) print check_plain($image['field_file_image_alt_text'][LANGUAGE_NONE][0]['value']); ?>">
          <?php endif; ?>
        </a>
        <figcaption><?php print check_plain($article_video[0]['filename']); ?></figcaption>
      </figure>
      <?php elseif(!empty($subpage_images[1])): $image = $subpage_images[1]; ?>
      <figure>
        <a href="<?php print image_style_url('hitsa_article_modal_view', $image['uri']); ?>" 
        data-plugin="modal" data-heading="<?php print $heading_title; ?>" data-closebutton="<?php print t('Close'); ?>">
          <img src="<?php print image_style_url('hitsa_core_thumbnail', $image['uri']); ?>" 
          alt="<?php if(!empty($image['field_file_image_alt_text'])) print check_plain($image['field_file_image_alt_text'][LANGUAGE_NONE][0]['value']); ?>">
        </a>
        <figcaption><?php if(!empty($image['field_file_image_title_text'])) print check_plain($image['field_file_image_title_text'][LANGUAGE_NONE][0]['value']); ?></figcaption>
      </figure>
      <?php endif; ?>
    </div><!--/col-4-->
    <?php endif; ?>
  </div><!--/row-->
  
</div><!--/block-->