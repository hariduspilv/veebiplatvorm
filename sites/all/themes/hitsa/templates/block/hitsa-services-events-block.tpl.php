<?php if(!empty($services) || !empty($events)): ?>
<div class="block block-narrow" data-plugin="tabs">
  <h2 class="block-title"><?php print t('Services'); ?></h2>
  
  <div class="row pull-up">
     <div class="col-12">
        <?php if(!empty($services)): ?>
        <a href="javascript:void(0);" data-target="tab-1" class="link-tab"><?php print t('Services'); ?></a>
        <?php endif; ?>
        <?php if(!empty($events)): ?>
        <a href="javascript:void(0);" data-target="tab-2" class="link-tab"><?php print t('Trainings'); ?></a>
        <?php endif; ?>
     </div><!--/col-12-->
  </div><!--/row-->
  <div class="row-spacer-xs"></div>
  <?php if(!empty($services)): ?>
  <?php print $services; ?>
  <div data-tab="tab-1">
    <h5 class="size-large">Avalikud teenused</h5>
    
    <ul class="bullet-links">
       <li><a href="">Ruumide rent</a></li>
       <li><a href="">Juuksur</a></li>
       <li><a href="">Kohvik</a></li>
       <li><a href="">Catering</a></li>
       
       <li data-show="bullet-list-1"><a href="">Ruumide rent</a></li>
       <li data-show="bullet-list-1"><a href="">Juuksur</a></li>
       <li data-show="bullet-list-1"><a href="">Kohvik</a></li>
       <li data-show="bullet-list-1"><a href="">Catering</a></li>
       
       <li>
          <div data-toggle="bullet-list-1" class="bullet-list-show_more"><span data-hide="bullet-list-1" class="after-arrow_down">Näita rohkem (4)</span><span data-show="bullet-list-1" class="after-arrow_up">Näita vähem</span></div>
       </li>
       
    </ul>
    
    <h5 class="size-large">Teenused ettevõtjale</h5>
    <ul class="bullet-links">
       <li><a href="">Konsultatsioon</a></li>
       <li><a href="">Arendusteenus</a></li>
       <li><a href="">Uuringuteenus</a></li>
       <li><a href="">Laboriteenus</a></li>
    </ul>
  </div><!--/data-tab-1-->
  <?php endif; ?>
  <?php if(!empty($events)): ?>
    <?php print $events; ?>
  <?php endif; ?>
</div>
<?php endif; ?>