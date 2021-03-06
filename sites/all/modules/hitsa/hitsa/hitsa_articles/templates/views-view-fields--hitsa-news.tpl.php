<?php

/**
 * @file
 * Default simple view template to all the fields as a row.
 *
 * - $view: The view in use.
 * - $fields: an array of $field objects. Each one contains:
 *   - $field->content: The output of the field.
 *   - $field->raw: The raw data for the field, if it exists. This is NOT output safe.
 *   - $field->class: The safe class id to use.
 *   - $field->handler: The Views field handler object controlling this field. Do not use
 *     var_export to dump this object, as it can't handle the recursion.
 *   - $field->inline: Whether or not the field should be inline.
 *   - $field->inline_html: either div or span based on the above flag.
 *   - $field->wrapper_prefix: A complete wrapper containing the inline_html to use.
 *   - $field->wrapper_suffix: The closing tag for the wrapper.
 *   - $field->separator: an optional separator that may appear before a field.
 *   - $field->label: The wrap label text to use.
 *   - $field->label_html: The full HTML of the label to use including
 *     configured element type.
 * - $row: The raw result object from the query, with all data it fetched.
 *
 * @ingroup views_templates
 */
?>
<div class="col-6 sm-12">
  <?php if(!empty($row->_field_data)):?>
  <?php if((node_access("update", $row->_field_data['nid']['entity'], $user) === TRUE)): ?>
      <ul class="tabs primary">
        <li><a href="<?php print url('node/' . $row->nid . '/edit'); ?>"><?php print t('Edit'); ?></a></li>
        <li><a href="<?php print url('node/' . $row->nid . '/translate'); ?>"><?php print t('Translate'); ?></a></li>
      </ul>
    <?php endif; ?>
    <?php endif; ?>
  <a href="<?php print $fields['path']->content; ?>" class="object<?php if($view->current_display === 'news_block') {print ' object-horizontal';} ?>">
    <span class="object-inner">
      <?php if(!empty($fields['subpage_images']->content)): ?>
      <span class="object-image" style="background-image:url(<?php print $fields['subpage_images']->content; ?>);">
        <img alt="" src="<?php print '/' . drupal_get_path('theme', $GLOBALS['theme']) . '/static/assets/imgs/placeholder-56.gif'; ?>" />
      </span>
      <?php else: ?>
      <span class="object-image">
				<span class="object-placeholder">
					<img src="<?php print $placeholder_image_url; ?>" />
				</span><!--/object-placeholder-->
				<img alt="" src="<?php print '/' . drupal_get_path('theme', $GLOBALS['theme']) . '/static/assets/imgs/placeholder-56.gif'; ?>" />
			</span><!--/object-image-->
      <?php endif; ?>
      <span class="object-content">
        <span class="object-title"><?php print $fields['title']->content; ?></span>
        <span class="object-footer">
          <span class="before-calendar"><?php print $fields['created']->content; ?></span>
          <?php $author_name = !empty($fields['field_author_custom']->content) ?
              $fields['field_author_custom']->content : $fields['name']->content;
          if(!empty($author_name)):?>
          <span class="before-user"><?php print $author_name; ?></span>
          <?php endif; ?>
        </span><!--/object-footer-->
      </span><!--/object-content-->
    </span>
  </a><!--/object-->
</div><!--/col-6-->
