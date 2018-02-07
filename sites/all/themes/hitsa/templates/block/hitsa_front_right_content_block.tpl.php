<div class="block block-narrow">
   <h2 class="block-title"><?php print $block_title?></h2>

   <div class="accordion accordion-xs" data-plugin="accordion">
      <?php foreach($services as $service):?>
        <?php print $service['html']?>
      <?php endforeach;?>
   </div><!--/accordion-->

</div><!--/block-->
