<?php
//krumo($images);

?>
<div class="row detail-pictures" data-plugin="detailPictures">
  <?php if(!empty($images)):?>
  <?php foreach($images as $key => $image):?>
    <?php if($key ==0):?>
      <div class="col-12">
        <figure>
          <a href="<?php print $image['full_url']?>" data-fancybox="fancybox" data-caption="<?php print $image['title']?>">
            <img src="<?php print $image['full_url']?>" alt="<?php print $image['alt_text']?>">
          </a>
          <?php else:?>
      <div class="col-6">
        <figure class="little">
          <a href="<?php print $image['full_url']?>" data-fancybox="fancybox" data-caption="<?php print $image['title']?>" style="background-image: url(<?php print $image['thumbnail']?>);"></a>
    <?php endif?>
        </figure>
        </div>
  <?php  endforeach;?>
  <?php endif?>
</div><!--/row-->
