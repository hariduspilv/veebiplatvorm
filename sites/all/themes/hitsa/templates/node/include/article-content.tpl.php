<div class="block">
  <?php if(!empty($article_type) && !empty($article_types_list[$article_type[0]['value']])): ?>
  <h1 class="block-title"><?php print check_plain($article_types_list[$article_type[0]['value']]); ?></h1>
  <?php else: ?>
    <h1 class="block-title"><?php print $title; ?></h1>
  <?php endif; ?>
  
  <div class="row-spacer-xs"></div>
  <div class="row">
    <div class="col-8">
      <article class="padding-right">
        <?php if($node->type === 'article'): ?>
        <h1><?php print $title; ?></h1>
        <?php endif; ?>
        
        <?php if(!empty($body)): ?>
        <?php if(!empty($body[0]['safe_summary'])): ?>
        <div class="intro">
           <?php print $body[0]['safe_summary']; ?>
        </div><!--/intro-->
        <?php endif; ?>
        
        <?php if(!empty($body[0]['safe_value'])): ?>
          <?php print nl2br($body[0]['safe_value']); ?>
        <?php endif; ?>
        <?php endif; ?>
        
        <?php if(!empty($elements['cp_contact_information'])): ?>
          <?php print render($elements['cp_contact_information']); ?>
        <?php endif; ?>
      </article>
    </div><!--/col-8-->
    <div class="col-4">
      <div class="btn-bar align-right">
        <a href="" class="btn-circle before-share"></a>
        <a href="javascript:window.print();" class="btn-circle before-print"></a>
      </div><!--/button-row-->
      <div class="row-spacer-xl"></div>
      
      <?php foreach($cp_gallery as $image): // Gallery ?>
      <figure>
        <img src="<?php print image_style_url('hitsa_core_thumbnail', $image['uri']); ?>" alt="<?php print check_plain($image['alt']); ?>">
        <figcaption><?php print check_plain($image['alt']); ?></figcaption>
      </figure>
      <?php endforeach; ?>
    </div><!--/col-4-->
  </div><!--/row-->
</div><!--/block-->