<?php if(isset($openAll)):?>
<?php if(empty($values['error'])):?>
<div class="accordion" data-plugin="accordion" data-allClosed="TRUE">
  <?php else:?>
  <div class="accordion" data-plugin="accordion">
    <?php endif?>
    <?php else:?>

    <div class="accordion" data-plugin="accordion">
      <?php endif?>
      <?php if (!empty($values) &&!isset($values['error'])) : ?>
      <?php foreach ($values as $id => $accordion_content) : ?>
      <?php if(isset($openAll)):?>
      <div class="accordion-entry accordion-active">
        <?php else:?>
        <div class="accordion-entry">
          <?php endif?>
          <?php if(!empty($accordion_content['Name'])):?>
          <div class="accordion-title">
            <?php print $accordion_content['Name']?>
          </div>
          <?php endif?>
          <div class="accordion-content">
            <?php if(!empty($accordion_content['persons'])):?>
            <?php foreach ($accordion_content['persons'] as $name):?>
            <div class="object object-horizontal">
              <div class="object-inner">
                <div class="object-content">
                  <div class="object-content_col">
                    <p><b>
                        <?php print $name['name']?></b></p>
                  </div>
                  <!--/object-content_col-->
                  <?php if(!empty($name['extra_information'])):?>
                  <div class="object-content_col">
                    <p>
                      <?php print $name['extra_information']?>
                    </p>
                  </div>
                  <?php endif?>
                  <!--/object-content_col-->
                </div>
                <!--/object-content-->
              </div>
              <!--/object-inner-->
            </div>
            <!-- <div class="row-spacer sm-hide"></div> -->
            <?php if(empty($name['end'])):?>
            <hr>
            <?php endif?>
            <?php endforeach?>
            <?php endif?>

            <!--/object-->



          </div>
          <!--/accordion-entry-->
        </div>
        <!--/accordion-content-->

        <!--/accordion-entry-->
        <?php endforeach ?>
        <?php endif ?>
        <?php if(isset($values['error'])):?>
        <div class="accordion-entry">
          <div class="accordion-title">
            <?php print t('Not found')?>
          </div>
          <div class="accordion-content">

            <div class="object object-horizontal">
              <div class="object-inner">
                <div class="object-content">
                  <div class="object-content_col">
                    <p>
                      <?php print $values['error']?>
                    </p>

                  </div>
                  <!--/object-content_col-->

                </div>
                <!--/object-content-->
              </div>
              <!--/object-inner-->
            </div>
            <!--/object-inner-->
          </div>
          <!--/object-inner-->
        </div>
        <!--/object-inner-->
        <?php endif?>
      </div>
      <!--/row-->
