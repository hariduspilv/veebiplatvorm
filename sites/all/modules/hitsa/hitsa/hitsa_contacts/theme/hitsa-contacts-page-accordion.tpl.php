<script>/*global Drupal */ Drupal.behaviors.spamspan.attach();</script>
<?php if(!empty($contact_departments)): // General contact search output ?>
<div class="accordion" data-plugin="accordion">
  <?php foreach($contact_departments as $contact_department):
    if(empty($nodes[$contact_department->tid])) continue;
    $current_nodes = $nodes[$contact_department->tid];
  ?>
  <div class="accordion-entry">
    <div class="accordion-title"><?php print sprintf('%s (%d)', check_plain($contact_department->name), count($current_nodes)); ?></div>
    <div class="accordion-content">
      <?php foreach($current_nodes as $node): ?>
        <?php print render($node); ?>
      <?php if(next($current_nodes) !== FALSE): ?>
      <hr class="spacing-xl" />
      <?php endif; ?>
      <?php endforeach; ?>
    </div><!--/accordion-content-->
  </div><!--/accordion-entry-->
  <?php endforeach; ?>
</div><!--/accordion-->
<?php else: // Consultation times search output ?>
  <?php if(!empty($nodes)): ?>
    <?php
    $i = 0;
    while(!empty($nodes[$i])): ?>
    <div class="col-12">
    <?php print render($nodes[$i]); ?>
    </div>
    <?php if(!empty($nodes[$i+1])): ?>
    <hr class="spacing-xl">
    <?php endif; ?>
    <?php $i++; endwhile; ?>
  <?php endif; ?>
<?php endif; ?>
