  <figure class="sm-hide">

    <a href="<?php print($modal_image)?>" data-download="<?php print $full_url?>" data-plugin="modal" data-modal="image-7" data-heading="<?php print($title)?>" data-closebutton="<?php print(t('Close'))?>">

        <img src="<?php print ($thumbnail)?>" alt="<?php print $alt_title?>">
    </a>
    <figcaption>
      <?php if(!empty($title)):?>
       <?php print($title)?>
      <?php endif;?>
    </figcaption>
</figure>

