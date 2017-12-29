<?php print render($form['name']); ?>

<?php if(!empty($form['challenge_id'])): ?>
<div id="challenge-id" class="form-item" style="margin: -20px 0 10px 0">
  <div class="form-item_title"><?php print render($form['challenge_id']); ?></div>
	<div class="form-item_disclaimer"><?php print t('Check to make sure that your phone shows the same number.'); ?></div>
</div>
<?php endif; ?>

<?php print render($form['log_in']); ?>

<?php print drupal_render_children($form); ?>