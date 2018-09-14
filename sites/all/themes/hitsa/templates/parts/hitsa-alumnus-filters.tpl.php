<h2 class="block-title"><?php print t('Alumnus')?></h2>
               
               <div class="row sm-hide">
                  <div class="col-12">
                     <h3><?php print t('Filter')?></h3>
                  </div><!--/col-12-->
               </div><!--/row-->
               
               <form method="post" action="kontakt.html" data-plugin="filters">
               
               <div class="row">
                  <div class="col-12">
                     <div class="form-item-row">
                        
                        <div class="form-item after-search form-item_rounded form-item-stretch">
                           <div class="form-item_title"><?php print t('Name search')?></div>
                           <input type="text" name="name" placeholder="<?php print t('Name search')?>" data-plugin="autocomplete" data-url="/api/alumnus_autocomplete" data-onSubmit="true" />
                        </div><!--/form-item-->

                        <div class="row-spacer-xs sm-show"></div>
                        <div class="form-item">
                           <div class="form-item_title sm-hide">&nbsp;</div>
                           <button class="btn btn-filled">Otsi</button>
                        </div><!--/form-item-->
                        
                     </div><!--/form-item-row-->
                  </div><!--/col-12-->
               </div><!--/row-->
               
               </form>