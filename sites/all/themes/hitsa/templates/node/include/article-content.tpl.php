<div class="block<?php if(!empty($hide_main_block)) print ' sm-hide'; ?>">
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

  <?php if(!empty($contact_filter)): ?>
  <?php print $contact_filter; ?>
  <?php endif; ?>

  <div class="row-spacer-xs sm-hide"></div>

  <div class="row"
    <?php if(!empty($contact_filter)) {print ' data-posturl="' . url('api/contact') . '" data-plugin="filterContents"';} ?>>

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
    <div class="col-12">
      <article class="clearSpace">
        <?php if(!empty($field_school_selections) && $field_school_selections[0]['value']=='catering'):?>
        <div class="article-heading">
          <h1><?php print $title?></h1>
          <?php if(!empty($content['field_catering_file'])):?>
          <?php foreach($field_catering_file as $catering_file):?>
          <a target="_blank" class="link-circle"
            href="<?php print $catering_file['url']?>">
            <span class="before-document"></span>
            <?php print $catering_file['name']?>
          </a>

          <?php endforeach?>
          <?php endif?>
        </div>
        <!--/article-heading-->
        <div class="row-spacer"></div>
        <?php endif;?>

        <?php if(empty($field_school_selections)): ?>
        <div class="btn-bar align-right sm-show sm-pull_right">
          <a href="javascript:void(0);" class="btn-circle before-share"
            data-plugin="share"></a>
          <a href="javascript:window.print();"
            class="sm-hide btn-circle before-print"></a>
        </div>
        <?php elseif($field_school_selections[0]['value']!='catering'):?>
        <div class="btn-bar align-right sm-show sm-pull_right">
          <a href="javascript:void(0);" class="btn-circle before-share"
            data-plugin="share"></a>
          <a href="javascript:window.print();"
            class="sm-hide btn-circle before-print"></a>
        </div>
        <?php endif?>
        <?php if(empty($field_school_selections)): ?>
        <h1 class="col-7 sm-12"><?php print $title; ?>
          <?php elseif($field_school_selections[0]['value']!='catering'):?>
          <h1 class="col-7 sm-12"><?php print $title; ?>
            <?php endif?>
            <?php if($node->type === 'article'): ?>

            <span class="editor-info">
              <span
                class="before-calendar"><?php print format_date($node->created, 'hitsa_date_month'); ?></span>
              <?php if(!empty($author_name)): ?>
              <span
                class="before-user"><?php print check_plain($author_name); ?></span>
              <?php endif; ?>
            </span>
            <?php endif; ?>
          </h1>

          <div class="row">
            <?php    if($node->type === 'content_page' && $node->cp_type[LANGUAGE_NONE][0]['value'] === 'cp_simple_without_images'):?>
            <div class="col-12 sm-12">
              <?php else:?>
              <div class="col-7 sm-12">
                <?php endif?>



                <?php if(!empty($body)): ?>
                <?php if(!empty($body[0]['safe_summary'])): ?>
                <div class="intro">
                  <?php print $body[0]['safe_summary']; ?>
                </div>
                <!--/intro-->
                <?php endif; ?>
                <div class="sm-hide">
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
                      <?php print $end?>
                    </div>
                    <!--/hidden-container-->
                  </div>
                  <!--/showMore-->
                  <?php endif;?>
                  <?php endif?>
                  <?php endif?>
                  <?php endif; ?>
                </div>
                <?php if(!empty($cinfo_company)): ?>
                <p>
                  <b><?php print check_plain($cinfo_company[0]['safe_value']); ?></b>
                </p>
                <?php endif; ?>

                <?php if(!empty($cinfo_homepage_url) || !empty($cinfo_e_mail)
            || !empty($cinfo_phone_nr) || !empty($cinfo_address)
            || !empty($cinfo_contact_person) || !empty($cinfo_contact_person_profession)
            ): ?>
                <ul class="list-details">
                  <?php if(!empty($cinfo_contact_person)): ?>
                  <li>
                    <div class="before-user"></div>
                    <div class="list-details_text">
                      <p>
                        <?php print check_plain($cinfo_contact_person[0]['safe_value']); ?>
                      </p>
                    </div>
                    <!--/list-details_text-->
                  </li>
                  <?php endif; ?>
                  <?php if(!empty($cinfo_contact_person_profession)): ?>
                  <li>
                    <div class="before-briefcase"></div>
                    <div class="list-details_text">
                      <p>
                        <?php print check_plain($cinfo_contact_person_profession[0]['safe_value']); ?>
                      </p>
                    </div>
                    <!--/list-details_text-->
                  </li>
                  <?php endif; ?>
                  <?php if(!empty($cinfo_homepage_url)): ?>
                  <li>
                    <div class="before-home"></div>
                    <div class="list-details_text">
                      <p>
                        <a href="<?php print check_url($cinfo_homepage_url[0]['url']); ?>"
                          target="_blank">
                          <?php print preg_replace('/^https?:\/\//', '', check_url($cinfo_homepage_url[0]['url'])); ?>
                        </a>
                      </p>
                    </div>
                    <!--/list-details_text-->
                  </li>
                  <?php endif; ?>
                  <?php if(!empty($cinfo_e_mail)): ?>
                  <li>
                    <div class="before-envelope"></div>
                    <div class="list-details_text">
                      <p>
                        <?php print spamspan(check_plain($cinfo_e_mail[0]['email'])); ?>
                      </p>
                    </div>
                    <!--/list-details_text-->
                  </li>
                  <?php endif; ?>
                  <?php if(!empty($cinfo_phone_nr)): ?>
                  <li>
                    <div class="before-phone"></div>
                    <div class="list-details_text">
                      <p>
                        <?php print check_plain($cinfo_phone_nr[0]['safe_value']); ?>
                      </p>
                    </div>
                    <!--/list-details_text-->
                  </li>
                  <?php endif; ?>
                  <?php if(!empty($cinfo_address)): ?>
                  <li>
                    <div class="before-location"></div>
                    <div class="list-details_text">
                      <p>
                        <?php print check_plain($cinfo_address[0]['safe_value']); ?>
                      </p>
                    </div>
                    <!--/list-details_text-->
                  </li>
                  <?php endif; ?>
                </ul>
                <?php endif; ?>
                <?php if(!empty($contacts_block)):?>
                <?php print $contacts_block?>
                <?php endif?>
                <div class="row-spacer-xs"></div>
                <span class="article-date sm-hide">
                  <i><?php print t('Last changed') . ': ' . date('d.m.Y', $node->changed); ?></i>
                </span>

              </div>
              <?php    if($node->type === 'content_page' && $node->cp_type[LANGUAGE_NONE][0]['value'] === 'cp_simple_without_images'):?>
              <?php else:?>
              <div class="col-4 sm-12 col-offset-1 sm-offset-0">
                <?php endif?>

                 <?php if(empty($field_school_selections)): ?>
         <div class="btn-bar align-right sm-hide">
                  <a href="javascript:void(0);" class="btn-circle before-share"
                    data-plugin="share"></a>
                  <a href="javascript:window.print();"
                    class="sm-hide btn-circle before-print"></a>
                </div>
        <?php elseif($field_school_selections[0]['value']!='catering'):?>
         <div class="btn-bar align-right sm-hide">
                  <a href="javascript:void(0);" class="btn-circle before-share"
                    data-plugin="share"></a>
                  <a href="javascript:window.print();"
                    class="sm-hide btn-circle before-print"></a>
                </div>
        <?php endif?>


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

                <span class="article-date sm-show">
                  <i><?php print t('Last changed') . ': ' . date('d.m.Y', $node->changed); ?></i>
                </span>

              </div>
              <!--/col-4-->

            </div>

      </article>


    </div>
    <!--/col-12-->
    <?php endif; ?>
  </div>
  <!--/row-->

</div>
<!--/block-->
<?php if(!empty($bottom_block)):?>
<?php print $bottom_block?>
<?php endif?>
