<div class="block no-padding">
  <div class="row">
    <div class="col-3 d-flex">
      <ul class="side-menu">
        <?php foreach($nodes as $node_array): ?>
        <?php foreach($node_array as $node): ?>
        <li <?php if($active_node['node']->nid === $node->nid) print 'class="active"'; ?>>
          <a href="<?php print url(current_path(), array('query' => array('subpage' => $node->nid))); ?>">
            <?php print check_plain($node->title); ?>
          </a>
        </li>
        <?php endforeach; ?>
        <?php endforeach; ?>
      </ul>
    </div><!--/col-3-->
    <div class="col-9">
      <?php print theme('content_page_subpage_content', array('node' => $active_node['node'])); ?>
    </div><!--/col-9-->
  </div><!--/row-->
</div>