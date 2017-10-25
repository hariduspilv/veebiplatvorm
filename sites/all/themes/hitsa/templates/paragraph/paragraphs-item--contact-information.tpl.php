<?php

/**
 * @file
 * Default theme implementation for a single paragraph item.
 *
 * Available variables:
 * - $content: An array of content items. Use render($content) to print them
 *   all, or print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. By default the following classes are available, where
 *   the parts enclosed by {} are replaced by the appropriate values:
 *   - entity
 *   - entity-paragraphs-item
 *   - paragraphs-item-{bundle}
 *
 * Other variables:
 * - $classes_array: Array of html class attribute values. It is flattened into
 *   a string within the variable $classes.
 *
 * @see template_preprocess()
 * @see template_preprocess_entity()
 * @see template_process()
 */
?>
<?php if(!empty($content['cinfo_contact_person'])): ?>
<p>
  <b><?php print check_plain($content['cinfo_contact_person'][0]['#markup']); ?></b>
</p>
<?php endif; ?>
<ul class="list-details">
  <?php if(!empty($content['cinfo_homepage_url'])): ?>
  <li>
     <div class="before-home"></div>
     <div class="list-details_text">
        <p>
          <a href="<?php print check_url($content['cinfo_homepage_url']['#items'][0]['display_url']); ?>" target="_blank">
            <?php print check_url($content['cinfo_homepage_url']['#items'][0]['display_url']); ?>
          </a>
        </p>
     </div><!--/list-details_text-->
  </li>
  <?php endif; ?>
  <?php if(!empty($content['cinfo_e_mail'])): ?>
  <li>
     <div class="before-envelope"></div>
     <div class="list-details_text">
        <p>
          <a href="mailto:<?php print check_plain($content['cinfo_e_mail'][0]['#markup']); ?>">
            <?php print check_plain($content['cinfo_e_mail'][0]['#markup']); ?>
          </a>
        </p>
     </div><!--/list-details_text-->
  </li>
  <?php endif; ?>
  <?php if(!empty($content['cinfo_phone_nr'])): ?>
  <li>
     <div class="before-phone"></div>
     <div class="list-details_text">
        <p><?php print check_plain($content['cinfo_phone_nr'][0]['#markup']); ?></p>
     </div><!--/list-details_text-->
  </li>
  <?php endif; ?>
  <?php if(!empty($content['cinfo_address'])): ?>
  <li>
     <div class="before-location"></div>
     <div class="list-details_text">
        <p><?php print check_plain($content['cinfo_address'][0]['#markup']); ?></p>
     </div><!--/list-details_text-->
  </li>
  <?php endif; ?>
</ul>