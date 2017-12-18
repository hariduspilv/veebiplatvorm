<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>
<?php if (!empty($title)): ?>
<div class="row">
  <div class="col-12">
     <h3><?php print $title; ?><?php print sprintf(' (%d)', count($rows)); ?></h3>
  </div><!--/col-12-->
</div>
<?php endif; ?>

<div class="row">
<?php 
  end($rows); 
  $last = key($rows);
?>
<?php foreach ($rows as $id => $row): ?>
  <div<?php if ($classes_array[$id]) { print ' class="col-12 ' . $classes_array[$id] .'"';  } ?>>
    <?php print $row; ?>
  </div>
  <?php if($id === $last): ?>
    <hr class="spacing-xl">
  <?php endif; ?>
<?php endforeach; ?>
</div>

