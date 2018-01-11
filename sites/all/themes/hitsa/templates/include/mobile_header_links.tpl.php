<div class="block sm-show">
   <h3 class="block-title"><?php print t('Quick links')?></h3>
  

<?php 
    foreach ($links as $link_key => $link) {
        # code?>
        <a href="<?php print(url($link['link_path']))?>" class="btn btn-stretch"><?php print t($link['link_title'])?></a>
        <?php
    }
?>
</div><!--/block-->