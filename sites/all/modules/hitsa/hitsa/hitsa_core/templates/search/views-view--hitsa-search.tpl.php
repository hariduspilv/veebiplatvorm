<?php

/**
 * @file
 * Main view template.
 *
 * Variables available:
 * - $classes_array: An array of classes determined in
 *   template_preprocess_views_view(). Default classes are:
 *     .view
 *     .view-[css_name]
 *     .view-id-[view_name]
 *     .view-display-id-[display_name]
 *     .view-dom-id-[dom_id]
 * - $classes: A string version of $classes_array for use in the class attribute
 * - $css_name: A css-safe version of the view name.
 * - $css_class: The user-specified classes names, if any
 * - $header: The view header
 * - $footer: The view footer
 * - $rows: The results of the view query, if any
 * - $empty: The empty text to display if the view is empty
 * - $pager: The pager next/prev links to display, if any
 * - $exposed: Exposed widget form/info to display
 * - $feed_icon: Feed icon to display, if any
 * - $more: A link to view more, if any
 *
 * @ingroup views_templates
 */
?>
<div class="block <?php print $classes; ?>">
  
  <?php if(!empty($search_query)): ?>
  <h2 class="block-title"><?php print t('Searching for'); ?> <i>"<?php print check_plain($search_query); ?>"</i> (<?php print $result_count; ?>)</h2>
  <?php endif; ?>
  
  <div class="row">
    <div class="col-12">
       <h3><?php print t('Filter categories'); ?></h3>
    </div><!--/col-12-->
  </div>
  
  <form method="post" action="otsing.html" data-plugin="filters">
    <div class="row">
      <div class="col-12">
				<div class="btn-bar">
          <span class="btn-input">
             <input type="checkbox" name="category" value="all" checked="">
             <span class="btn btn-xs btn-alternate">Kõik</span>
          </span><!--/btn-input-->
          
          <span class="btn-input">
             <input type="checkbox" name="category" value="kontaktid">
             <span class="btn btn-xs btn-alternate">Kontaktid</span>
          </span><!--/btn-input-->
          
          <span class="btn-input">
             <input type="checkbox" name="category" value="uudised">
             <span class="btn btn-xs btn-alternate">Uudised</span>
          </span><!--/btn-input-->
					 
					 <span class="btn-input">
             <input type="checkbox" name="category" value="sundmused">
             <span class="btn btn-xs btn-alternate">Sündmused</span>
          </span><!--/btn-input-->
        </div><!--/btn-bar-->
                     
      </div><!--/col-12-->
    </div><!--/row-->
    <div class="row-spacer-xs sm-hide"></div>
    <hr>
    <div class="row-spacer sm-hide"></div>
    <div class="row">
      <div class="col-12">
        <div class="form-item-row">
           
          <div class="form-item after-search form-item_rounded form-item-stretch">
             <div class="form-item_title">Otsi pealkirja järgi</div>
             <input type="text" name="title" placeholder="Alusta trükkimist" data-plugin="autocomplete" data-url="api/autocomplete.json" data-onsubmit="true">
          </div><!--/form-item-->
          <div class="form-item form-item_rounded after-calendar form-item-stretch">
             <div class="form-item_title">Kuupäev</div>
             <input type="text" name="date" data-plugin="datepickerRange" data-onsubmit="true" placeholder="Vali kuupäev">
          </div><!--/form-item-->
          <div class="row-spacer-xs sm-show"></div>
          <div class="form-item">
             <div class="form-item_title sm-hide">&nbsp;</div>
             <button class="btn btn-filled">Otsi</button>
          </div><!--/form-item-->
           
        </div><!--/form-item-row-->
      </div><!--/col-12-->
    </div><!--/row-->
    <div class="row-spacer sm-hide"></div>
  </form>
  
  <?php print render($title_prefix); ?>
  <?php if ($title): ?>
    <?php print $title; ?>
  <?php endif; ?>
  <?php print render($title_suffix); ?>
  <?php if ($header): ?>
    <div class="view-header">
      <?php print $header; ?>
    </div>
  <?php endif; ?>

  <?php if ($attachment_before): ?>
    <div class="attachment attachment-before">
      <?php print $attachment_before; ?>
    </div>
  <?php endif; ?>
  
  <?php if ($rows): ?>
    <div class="view-content">
      <?php print $rows; ?>
    </div>
  <?php elseif ($empty): ?>
    <div class="view-empty">
      <?php print $empty; ?>
    </div>
  <?php endif; ?>

  <?php if ($pager): ?>
    <?php print $pager; ?>
  <?php endif; ?>

  <?php if ($attachment_after): ?>
    <div class="attachment attachment-after">
      <?php print $attachment_after; ?>
    </div>
  <?php endif; ?>

  <?php if ($more): ?>
    <?php print $more; ?>
  <?php endif; ?>

  <?php if ($footer): ?>
    <div class="view-footer">
      <?php print $footer; ?>
    </div>
  <?php endif; ?>

  <?php if ($feed_icon): ?>
    <div class="feed-icon">
      <?php print $feed_icon; ?>
    </div>
  <?php endif; ?>

</div><?php /* class view */ ?>
<script>
  jQuery('hr.spacing-xl').last().remove();
</script>