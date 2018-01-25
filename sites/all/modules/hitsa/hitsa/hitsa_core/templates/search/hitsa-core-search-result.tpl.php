
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
  <?php foreach($items as $item): ?>
    <?php print $item; ?>
  <?php endforeach; ?>
  </div>
  <?php if($bundle !== $last): ?>
  <hr class="spacing-xl">
  <?php endif; ?>
<?php endforeach; ?>