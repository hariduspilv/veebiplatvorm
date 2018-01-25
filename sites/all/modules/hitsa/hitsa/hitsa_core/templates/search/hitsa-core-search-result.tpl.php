
<?php 
$array_keys = array_keys($result_items);
$last = array_pop($array_keys);
foreach($result_items as $bundle => $items): ?>
<div class="row">
	<div class="col-12">
		<h3 id="<?php print $bundle; ?>"><?php print $bundles[$bundle]; ?> (<?php print count($items); ?>)</h3>
	</div><!--/col-12-->
</div>
<div class="row-spacer-xs"></div>
  <div class="row">
    <?php dpm($bundle); ?>
  <?php 
  $array_item_keys = array_keys($items);
  $last_item = array_pop($array_item_keys);
  foreach($items as $delta => $item): ?>
    <?php if($bundle === 'contact') print '<div class="col-12">'; ?>
    <?php print $item; ?>
    <?php if($bundle === 'contact'): ?>
    </div>
      <?php if($delta !== $last_item): ?>
      <div class="row-spacer-xs sm-hide"></div>
      <hr class="spacing-xs sm-show">
      <?php endif; ?>
    <?php endif; ?>
  <?php endforeach; ?>
  </div>
  <?php if($bundle !== $last): ?>
  <hr class="spacing-xl">
  <?php endif; ?>
<?php endforeach; ?>