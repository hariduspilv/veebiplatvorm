<?php if(!empty($catering)):?>
<div class="row">
               <div class="col-6 sm-12">
                   <?php print($events)?>
               </div>
               <div class="col-6 sm-12">
                   <?php print($catering)?>
               </div>
</div>
<?php else:?>
<?php print $events?>
<?php endif?>