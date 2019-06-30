<div class="block">
  <?php if(!empty($article_type) && !empty($article_types_list[$article_type[0]['value']])):
    $heading_title = check_plain($article_types_list[$article_type[0]['value']]);
    ?>
    <h2 class="block-title"><?php print $heading_title; ?></h2>
    <?php elseif($node->type === 'content_page' && $node->cp_type[LANGUAGE_NONE][0]['value'] === 'cp_service'):
    $heading_title = t('Services');
    ?>
    <h2 class="block-title"><?php print $heading_title; ?></h2>

    <?php else:
      $active_menu_trail = menu_get_active_trail(); // Set active menu trail
      if(count($active_menu_trail) === 3) {
        $heading_title = t($active_menu_trail[1]['link_title']);
      }
    ?>
    <h2 class="block-title"><?php print $heading_title; ?></h2>
    <?php endif; ?>

  <div class="row-spacer-xs"></div>
  <div class="row">
    <div class="col-8 sm-12">
      <article>
        <div class="article-heading">
          <?php if(!empty($title)):?>
            <h1><?php print $title?></h1>
          <?php endif?>
          <?php if(!empty($content['field_catering_file'])):?>
            <?php foreach($field_catering_file as $catering_file):?>
              <a target="_blank" class="link-circle"
                href="<?php print $catering_file['url']?>">
                <span class="before-document"></span>
                <?php print $catering_file['name']?>
              </a>
            <?php endforeach?>
          <?php endif?>
          <!--/link-circle-->
        </div>
        <!--/article-heading-->
        <div class="row-spacer"></div>
                <?php if(!empty($body[0]['safe_summary'])): ?>
                <div class="intro">
                  <?php print $body[0]['safe_summary']; ?>
                </div>
                <!--/intro-->
                <?php endif; ?>
                <div class="sm-hide">
                <div class="row-spacer"></div>
                  <?php if(!empty($body[0]['safe_value'])): ?>
                  <?php print $body[0]['safe_value']; ?>
                  <?php endif; ?>
                </div>
                <div class="sm-show">
                  <?php if(!empty($body[0]['safe_summary'])): ?>
                  <div class="hidden-content" data-plugin="showMore">
                    <div class="text-center">
                      <a href="" class="link"
                        data-anchor><?php print t('Read more')?><span
                          class="before-arrow_down"></span></a>
                    </div>
                    <!--/text-center-->
                    <div class="hidden-container" data-container>
                      
                      <?php print $body[0]['safe_value']?>
                    </div>
                    <!--/hidden-container-->
                  </div>
                  <!--/showMore-->
                  <?php else:?>
                  <?php if(!isset($end)):?>
                  <?php if(!empty($start)):?>
                  <?php print $start?>
                  <?php endif;?>
                  <?php else:?>
                  <?php if(!empty($start)):?>
                  <?php print $start?>
                  <?php endif;?>
                  <?php if(!empty($end)):?>
                  <div class="hidden-content" data-plugin="showMore">
                    <div class="text-center">
                      <a href="" class="link"
                        data-anchor><?php print t('Read more')?><span
                          class="before-arrow_down"></span></a>
                    </div>
                    <!--/text-center-->
                    <div class="hidden-container" data-container>
                            
                      <div class="row-spacer"></div>
                      <?php print $end?>
                    </div>
                    <!--/hidden-container-->
                  </div>
                  <!--/showMore-->
                  <?php endif;?>
                  <?php endif?>
                  <?php endif?>
      </article>
    </div>
    <!--/col-8-->
    <div class="col-4 sm-12 no-print sm-hide">
      <div class="row-spacer-xl no-print sm-hide"></div>
                <?php if(!empty($subpage_images) || (!empty($cp_image) && $subpage_images = $cp_image)): $image = $subpage_images[0]; // Gallery ?>
                <figure>
                  <a href="<?php print image_style_url('hitsa_article_modal_view', $image['uri']); ?>"
                    data-download="<?php print file_create_url($image['uri']); ?>"
                    data-plugin="modal"
                    data-modal="image-<?php print $image['fid']; ?>"
                    data-heading="<?php print $heading_title; ?>"
                    data-closebutton="<?php print t('Close'); ?>"
                    <?php (!empty($image['field_file_image_title_text']))? print ' data-title="' . check_plain($image['field_file_image_title_text'][LANGUAGE_NONE][0]['value']) . '"': print 'data-title=""' ?>>
                    <img
                      src="<?php print image_style_url('hitsa_core_thumbnail', $image['uri']); ?>"
                      alt="<?php if(!empty($image['field_file_image_alt_text'])) print check_plain($image['field_file_image_alt_text'][LANGUAGE_NONE][0]['value']); ?>">
                  </a>
                  <figcaption>
                    <?php if(!empty($image['field_file_image_title_text'])) print check_plain($image['field_file_image_title_text'][LANGUAGE_NONE][0]['value']); ?>
                  </figcaption>
                </figure>
                <?php endif; ?>
                <?php if(!empty($article_video)): ?>
                <figure>
                  <a href="<?php print file_create_url($article_video[0]['uri']); ?>"
                    data-title="<?php print check_plain($article_video[0]['filename']); ?>"
                    data-plugin="modal"
                    data-modal="video-<?php print $article_video[0]['fid']; ?>"
                    data-closebutton="<?php print t('Close'); ?>"
                    data-heading="<?php print check_plain($article_video[0]['filename']); ?>"
                    <?php if(!empty($image['field_file_image_title_text'])) print ' data-title="' . check_plain($article_video[0]['filename']) . '"'; ?>>
                    <?php if(!empty($video_thumbnail)): ?>
                    <img src="<?php print $video_thumbnail; ?>"
                      alt="<?php print check_plain($article_video[0]['filename']); ?>">
                    <?php else: ?>
                    <img
                      src="<?php print image_style_url('hitsa_core_thumbnail', $image['uri']); ?>"
                      alt="<?php if(!empty($image['field_file_image_alt_text'])) print check_plain($image['field_file_image_alt_text'][LANGUAGE_NONE][0]['value']); ?>">
                    <?php endif; ?>
                  </a>
                  <figcaption>
                    <?php print check_plain($article_video[0]['filename']); ?>
                  </figcaption>
                </figure>
                <?php elseif(!empty($subpage_images[1])): $image = $subpage_images[1]; ?>
                <figure>
                  <a href="<?php print image_style_url('hitsa_article_modal_view', $image['uri']); ?>"
                    data-download="<?php print file_create_url($image['uri']); ?>"
                    data-plugin="modal"
                    data-modal="image-<?php print $image['fid']; ?>"
                    data-heading="<?php print $heading_title; ?>"
                    data-closebutton="<?php print t('Close'); ?>"
                    <?php if(!empty($image['field_file_image_title_text'])) print ' data-title="' . check_plain($image['field_file_image_title_text'][LANGUAGE_NONE][0]['value']) . '"'; ?>>
                    <img
                      src="<?php print image_style_url('hitsa_core_thumbnail', $image['uri']); ?>"
                      alt="<?php if(!empty($image['field_file_image_alt_text'])) print check_plain($image['field_file_image_alt_text'][LANGUAGE_NONE][0]['value']); ?>">
                  </a>
                  <figcaption>
                    <?php if(!empty($image['field_file_image_title_text'])) print check_plain($image['field_file_image_title_text'][LANGUAGE_NONE][0]['value']); ?>
                  </figcaption>
                </figure>
                <?php endif; ?>

    </div>
    <!--/col-4-->
  </div>
  <!--/row-->

</div>
<?php if(!empty($bottom_block)):?>
<?php print $bottom_block?>
<?php endif?>
