<?php if(!empty($services) || !empty($events)): ?>
<div class="block block-narrow" data-plugin="tabs">
    <?php if(!empty($block_title)):?>
  <h2 class="block-title"><?php print $block_title; ?></h2>
  <?php endif?>
  <div class="row pull-up">
     <div class="col-12">
        <?php if(!empty($services)): ?>
        <a href="javascript:void(0);" data-target="tab-1" class="link-tab"><?php print t('Services'); ?></a>
        <?php endif; ?>
        <?php if(!empty($events)): ?>
        <a href="javascript:void(0);" data-target="tab-2" class="link-tab"><?php print t('Trainings'); ?></a>
        <?php endif; ?>
     </div><!--/col-12-->
  </div><!--/row-->
  <div class="row-spacer-xs"></div>
  <?php if(!empty($services)): ?>
  <?php print $services; ?>
  <?php endif; ?>
  <?php if(!empty($events)): ?>
    <?php print $events; ?>
  <?php endif; ?>
</div>
<?php endif; ?>

