<div class="block">
  <?php if(!empty($article_type) && !empty($article_types_list[$article_type[0]['value']])): 
  $heading_title = check_plain($article_types_list[$article_type[0]['value']]);
  ?>
  <h1 class="block-title"><?php print $heading_title; ?></h1>
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
        <?php print render($content['cp_contacts']); ?>
      <?php endif; ?>
    <?php else: ?>
    <div class="col-8 sm-12">
      <article class="padding-right">
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

        <?php if(!empty($elements['cp_contact_information'])): ?>
          <?php print render($elements['cp_contact_information']); ?>
        <?php endif; ?>
        
        <?php if($node->type === 'article'): ?>
          <div class="row-spacer-xs"></div>
          <span class="article-date">
            <i><?php print t('Last changed') . ': ' . date('d.m.Y', $node->changed); ?></i>
          </span>
        <?php endif; ?>
      </article>
    </div><!--/col-8-->
    <div class="col-4 sm-12 no-print">
      <?php if($node->type === 'article' || $node->type === 'content_page'): ?>
      <div class="btn-bar align-right">
        <a href="javascript:void(0);" class="btn-circle before-share" data-plugin="share"></a>
        <a href="javascript:window.print();" class="btn-circle before-print"></a>
      </div><!--/button-row-->
      <?php endif; ?>
    
      <div class="row-spacer-xl"></div>

      <?php if(!empty($subpage_images) || !empty($subpage_images = $cp_image)): $image = $subpage_images[0]; // Gallery ?>
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