<div class="block">

  <?php foreach($nodes as $delta => $node_array): ?>

  <?php if(!empty($titles[$delta])): ?>
  <div class="row">
    <div class="col-12">
       <h3><?php print check_plain($titles[$delta]); ?></h3>
    </div><!--/col-12-->
  </div>
  <?php endif; ?>

  <div class="row-spacer-xs"></div>

  <div class="row row-vertical-xl">
    <?php foreach($node_array as $node): ?>
      <?php print $node; ?>
    <?php endforeach; ?>
  </div><!--/row-->

  <?php if(next($nodes) !== FALSE): ?>
  <div class="row-spacer"></div>
  <div class="row-spacer"></div>
  <hr>
  <div class="row-spacer"></div>
  <?php endif; ?>

  <?php endforeach; ?>
</div>
