<article id="subpage">
  <h3><?php print check_plain($node->title); ?>
    <span class="btn-bar align-right pull-right">
       <a href="" class="btn-circle before-share"></a>
       <a href="javascript:window.print();" class="btn-circle before-print"></a>
    </span><!--/button-row-->
  </h3>

  <?php if(!empty($node->body)): ?>
    <?php if(!empty($node->body[LANGUAGE_NONE][0]['safe_summary'])): ?>
    <div class="intro">
       <?php print nl2br($node->body[LANGUAGE_NONE][0]['safe_summary']); ?>
    </div><!--/intro-->
    <?php endif; ?>
    
    <?php if(!empty($node->body[LANGUAGE_NONE][0]['safe_value'])): ?>
      <?php print nl2br($node->body[LANGUAGE_NONE][0]['safe_value']); ?>
    <?php endif; ?>
  <?php endif; ?>
</article>