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