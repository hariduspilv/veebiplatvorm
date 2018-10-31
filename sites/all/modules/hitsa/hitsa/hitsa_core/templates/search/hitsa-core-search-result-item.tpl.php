<?php if($result_item['entity']->type === 'contact'): 
  $contact_view = node_view($result_item['entity']);
?>
<?php print render($contact_view); ?>
<?php elseif($result_item['entity']->type === 'event' || $result_item['entity']->type === 'training'): ?>
<div class="col-12">
  <?php 
  global $language;
  //$result_item['entity']->event_tags[$language->language] = $result_item['entity']->event_tags[LANGUAGE_NONE];
  $node_rendered = hitsa_events_event_html($result_item['entity'], $result_item['entity']->field_event_type[LANGUAGE_NONE][0]['value'], $result_item['entity']->event_date[LANGUAGE_NONE][0]['value'], TRUE);
  print $node_rendered['html']; ?>
</div>
<?php else: ?>
<div class="col-12">
	<a href="<?php print url('node/' . $result_item['entity']->nid); ?>" class="object object-max_width">
		<span class="object-inner">
			<span class="object-content">
				<span class="object-title"><?php print $result_item['entity']->title; ?></span>
				<span class="object-footer">
					<span class="before-calendar"><?php print format_date($result_item['entity']->created, 'hitsa_date_month'); ?></span>
					<?php 
					$author_name = !empty($result_item['entity']->field_author_custom) ? 
						$result_item['entity']->field_author_custom[LANGUAGE_NONE][0]['safe_value'] : NULL;
						
					if(!empty($author_name)): ?>
					<span class="before-user"><?php print $author_name; ?></span>
					<?php endif; ?>
				</span><!--/object-footer-->
				<span class="object-description">
					<?php if(!empty($result_item['excerpt'])) print $result_item['excerpt']; ?>
				</span><!--/object-description-->
			</span><!--/object-content-->
		</span><!--/object-inner-->
	</a><!--/object-->
</div>
<?php endif; ?>