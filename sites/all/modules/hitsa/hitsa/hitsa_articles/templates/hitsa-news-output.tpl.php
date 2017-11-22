<?php dpm($nodes); ?>
<?php foreach($nodes as $tid => $academic_year): ?>
  <div class="row">
        <div class="col-12">
          
          <?php if(!empty($academic_year_keyed[$tid])): ?>
          <h3><?php print check_plain($academic_year_keyed[$tid]); ?></h3>
          <?php endif; ?>
        </div><!--/col-12-->
      </div><!--/row-->
          
  <div class="row-spacer-xs"></div>
  
  <div class="row row-vertical-xl">
    <?php foreach($academic_year as $academic_year_nodes): ?>
      <?php print $academic_year_nodes; ?>
    <?php endforeach; ?>
  </div><!--/row-->
  
  <?php if(next($nodes) !== FALSE): ?>
  <div class="row-spacer"></div>
  <div class="row-spacer"></div>
  <hr>
  <div class="row-spacer"></div>
  <?php endif; ?>

<?php endforeach; ?>

<div class="row">
	<div class="col-12">
	  <?php if(!empty($pager)): ?>
	    <?php print $pager; ?>
	  <?php endif; ?>
	</div><!--/col-12-->
</div>