<?php if($view_mode === 'full'): ?>
<div class="row">
  <div class="col-12">

    <div class="block sm-opaque" data-plugin="gallery" data-modal="true">

      <h1 class="block-title"><?php print $title; ?>
      <?php if($modal): ?>
      <a href="javascript:void(0);" data-close="true" class="btn btn-transparent pull-right after-close"><?php print t('Close'); ?></a>
      <?php endif; ?>
      </h1>

			<div class="gallery-wrapper">
				<div class="row">
					<div class="col-12">
						<div class="btn-bar align-right">
							<a href="javscript:void(0);" class="btn-circle before-share" data-plugin="share"></a>
							<a href="javascript:window.print();" class="btn-circle before-print sm-hide"></a>
							<a href="" id="download-link" target="_blank" class="btn-circle before-download" download></a>
						</div>
					</div><!--/col-12-->
				</div><!--/row-->

				<div class="row sm-grow">
					<div class="col-3 sm-hide">
						<?php if(!empty($content['gallery_images'])): ?>
						  <?php print render($content['gallery_images']); ?>
						<?php endif; ?>

						<div class="row-spacer"></div>
						<ul class="paginator paginator-left" id="paginator">
						</ul><!--/paginator-->

					</div><!--/col-3-->

					<div class="col-9 sm-12">
						<div class="swiper-holder swiper-gallery" id="gallery">
							<div class="swiper-container">
								<div class="swiper-wrapper">
									<div class="swiper-slide" data-image="?image?">
                    <a class="gallery-image" href="?href?" data-fancybox="gallery" data-caption="?caption?">
										<div class="gallery-image">

                      <span class="before-picture"></span>
											<img alt="" src="<?php print '/' . drupal_get_path('theme', $GLOBALS['theme']) . '/static/assets/imgs/placeholder-gallery.gif'; ?>">
										</div><!--/gallery-image-->
                    </a><!--/gallery-image-->
										<div class="gallery-description">
											<div class="gallery-title">?title?</div>
											<div class="gallery-page">?currentImage?/?totalImages?</div>
										</div><!--/gallery-description-->
									</div><!--/swiper-slide-->
								</div><!--/swiper-wrapper-->
							</div><!--/swiper-container-->
							<div class="swiper-button-prev"></div>
							<div class="swiper-button-next"></div>
						</div><!--/swiper-holder-->
					</div><!--/col-9-->

				</div><!--/row-->
			</div><!--/gallery-wrapper-->
			<div class="row sm-show mobile-thumbnails">
				<div class="col-12">
					<div class="mobile-thumbnails-holder">
						<div class="mobile-thumbnails-scroller">

						</div><!--/mobile-thumbnails-scroller-->
					</div><!--/mobile-thumbnails-holder-->
				</div><!--/col-12-->
			</div><!--/row-->
    </div>
  </div><!--/col-12-->
</div>
<?php elseif($view_mode === 'search_result'): ?>
  <?php include 'include/search-result.tpl.php'; ?>
<?php elseif($view_mode === 'menu_teaser'): ?>
<div class="col-3">
  <h4><?php print htmlspecialchars_decode(check_plain($title)); ?></h4>
  <?php if(!empty($content['gallery_images'])): ?>
  <a href="<?php print $node_url; ?>"><img alt="<?php if(!empty($content['gallery_images'][0]['field_file_image_alt_text'][LANGUAGE_NONE][0]['value']))
  {print check_plain($content['gallery_images'][0]['field_file_image_alt_text'][LANGUAGE_NONE][0]['value']);} ?>"
  src="<?php print image_style_url('hitsa_gallery_menu_teaser', $content['gallery_images']['#items'][0]['uri']); ?>"></a>
  <?php endif; ?>
  <a href="<?php print $node_url; ?>" class="btn"><?php print t('Check gallery'); ?></a>
</div>
<?php else: ?>
<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>

  <?php print render($title_prefix); ?>
  <?php if (!$page): ?>
    <h2<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
  <?php endif; ?>
  <?php print render($title_suffix); ?>

  <?php if ($display_submitted): ?>
    <div class="submitted">
      <?php print $submitted; ?>
    </div>
  <?php endif; ?>

  <div class="content"<?php print $content_attributes; ?>>
    <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['comments']);
      hide($content['links']);
      print render($content);
    ?>
  </div>

  <?php print render($content['links']); ?>

  <?php print render($content['comments']); ?>

</div>
<?php endif; ?>
