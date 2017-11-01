<div class="block no-padding">
  <div class="row">
    <?php if(count($titles) > 1): ?>
    <div class="col-3 d-flex">
      <ul class="side-menu">
        <?php foreach($subpages as $subpage_array): ?>
        <?php foreach($subpage_array as $subpage): ?>
        <li <?php if($active_subpage['subpage']->item_id === $subpage->item_id) print 'class="active"'; ?>>
          <a href="<?php print url(current_path(), array('query' => array('subpage' => $subpage->item_id))); ?>">
            <?php $title = field_get_items('paragraphs_item', $subpage, 'subpage_title'); print check_plain($title[0]['safe_value']); ?>
          </a>
        </li>
        <?php endforeach; ?>
        <?php endforeach; ?>
      </ul>
    </div><!--/col-3-->
    <?php endif; ?>
    <div class="col-<?php if(count($titles) > 1) {print '9';} else print '12';?>">
      <?php print theme('content_page_subpage_content', array('subpage' => $active_subpage['subpage'])); ?>
    </div><!--/col-9-->
  </div><!--/row-->
</div>