<a href="<?php print url('node/' . $node->nid); ?>" class="object object-max_width">
  <span class="object-inner">
     <span class="object-content">
        <span class="object-title"><?php print $node->title; ?></span>
        <?php if($node->type === 'article'): ?>
        <span class="object-footer">
           <span class="before-calendar"><?php print format_date($node->created, 'hitsa_date_month'); ?></span>
           <?php if($node->uid !== '0' && $author = user_load($node->uid)): ?>
           <span class="before-user"><?php print $author->name; ?></span>
           <?php endif; ?>
        </span><!--/object-footer-->
        <?php endif; ?>
        <?php if(!empty($excerpt)): ?>
        <span class="object-description"><?php print $excerpt; ?></span><!--/object-description-->
        <?php endif; ?>
     </span><!--/object-content-->
  </span><!--/object-inner-->
</a>