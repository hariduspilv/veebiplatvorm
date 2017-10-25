<?php

/**
 * @file
 * Default theme implementation to display a region.
 *
 * Available variables:
 * - $content: The content for this region, typically blocks.
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the following:
 *   - region: The current template type, i.e., "theming hook".
 *   - region-[name]: The name of the region with underscores replaced with
 *     dashes. For example, the page_top region would have a region-page-top class.
 * - $region: The name of the region variable as defined in the theme's .info file.
 *
 * Helper variables:
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $is_admin: Flags true when the current user is an administrator.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 *
 * @see template_preprocess()
 * @see template_preprocess_region()
 * @see template_process()
 *
 * @ingroup themeable
 */
?>
<?php

/**
 * @file
 * Default theme implementation to display a region.
 *
 * Available variables:
 * - $content: The content for this region, typically blocks.
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the following:
 *   - region: The current template type, i.e., "theming hook".
 *   - region-[name]: The name of the region with underscores replaced with
 *     dashes. For example, the page_top region would have a region-page-top class.
 * - $region: The name of the region variable as defined in the theme's .info file.
 *
 * Helper variables:
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $is_admin: Flags true when the current user is an administrator.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 *
 * @see template_preprocess()
 * @see template_preprocess_region()
 * @see template_process()
 *
 * @ingroup themeable
 */
?>
<?php if(!empty($school_image)):?>
<?php print $school_image?>
<?php endif;?>
<div class="inline">
      <div class="row">
         <div class="col-12">
            
            <div class="swiper-holder" data-plugin="caroussel" data-slidesPerView="4">
               <div class="swiper-container">
                  <div class="swiper-wrapper">

                     <div class="swiper-slide">
                        <div class="row">
                           <div class="col-3">
                              <a href="" class="block">
                                 <span class="caroussel_profession">
                                    <span class="caroussel_profession-icon before-catering"></span>
                                    <span class="caroussel_profession-title">Toitlustus</span>
                                    <span class="btn">Vaata erialasid</span>
                                 </span><!--/caroussel_profession-->
                              </a><!--/block-->
                           </div><!--/col-3-->
                           <div class="col-3">
                              <a href="" class="block">
                                 <span class="caroussel_profession">
                                    <span class="caroussel_profession-icon before-tourism"></span>
                                    <span class="caroussel_profession-title">Turism ja majutus</span>
                                    <span class="btn">Vaata erialasid</span>
                                 </span><!--/caroussel_profession-->
                              </a><!--/block-->
                           </div><!--/col-3-->
                           <div class="col-3">
                              <a href="" class="block">
                                 <span class="caroussel_profession">
                                    <span class="caroussel_profession-icon before-shopping"></span>
                                    <span class="caroussel_profession-title">Kaubandus</span>
                                    <span class="btn">Vaata erialasid</span>
                                 </span><!--/caroussel_profession-->
                              </a><!--/block-->
                           </div><!--/col-3-->
                           <div class="col-3">
                              <a href="" class="block">
                                 <span class="caroussel_profession">
                                    <span class="caroussel_profession-icon before-business"></span>
                                    <span class="caroussel_profession-title">Äri</span>
                                    <span class="btn">Vaata erialasid</span>
                                 </span><!--/caroussel_profession-->
                              </a><!--/block-->
                           </div><!--/col-3-->
                        </div><!--/row-->
                        
                     </div><!--/swiper-slide-->
                     
                     <div class="swiper-slide">
                        <div class="row">
                           <div class="col-3">
                              <a href="" class="block">
                                 <span class="caroussel_profession">
                                    <span class="caroussel_profession-icon before-catering"></span>
                                    <span class="caroussel_profession-title">Toitlustus</span>
                                    <span class="btn">Vaata erialasid</span>
                                 </span><!--/caroussel_profession-->
                              </a><!--/block-->
                           </div><!--/col-3-->
                           <div class="col-3">
                              <a href="" class="block">
                                 <span class="caroussel_profession">
                                    <span class="caroussel_profession-icon before-tourism"></span>
                                    <span class="caroussel_profession-title">Turism ja majutus</span>
                                    <span class="btn">Vaata erialasid</span>
                                 </span><!--/caroussel_profession-->
                              </a><!--/block-->
                           </div><!--/col-3-->
                           <div class="col-3">
                              <a href="" class="block">
                                 <span class="caroussel_profession">
                                    <span class="caroussel_profession-icon before-shopping"></span>
                                    <span class="caroussel_profession-title">Kaubandus</span>
                                    <span class="btn">Vaata erialasid</span>
                                 </span><!--/caroussel_profession-->
                              </a><!--/block-->
                           </div><!--/col-3-->
                           <div class="col-3">
                              <a href="" class="block">
                                 <span class="caroussel_profession">
                                    <span class="caroussel_profession-icon before-business"></span>
                                    <span class="caroussel_profession-title">Äri</span>
                                    <span class="btn">Vaata erialasid</span>
                                 </span><!--/caroussel_profession-->
                              </a><!--/block-->
                           </div><!--/col-3-->
                        </div><!--/row-->
                        
                     </div><!--/swiper-slide-->
                     
                     <div class="swiper-slide">
                        <div class="row">
                           <div class="col-3">
                              <a href="" class="block">
                                 <span class="caroussel_profession">
                                    <span class="caroussel_profession-icon before-catering"></span>
                                    <span class="caroussel_profession-title">Toitlustus</span>
                                    <span class="btn">Vaata erialasid</span>
                                 </span><!--/caroussel_profession-->
                              </a><!--/block-->
                           </div><!--/col-3-->
                           <div class="col-3">
                              <a href="" class="block">
                                 <span class="caroussel_profession">
                                    <span class="caroussel_profession-icon before-tourism"></span>
                                    <span class="caroussel_profession-title">Turism ja majutus</span>
                                    <span class="btn">Vaata erialasid</span>
                                 </span><!--/caroussel_profession-->
                              </a><!--/block-->
                           </div><!--/col-3-->
                           
                        </div><!--/row-->
                        
                     </div><!--/swiper-slide-->
                     
                  </div><!--/swiper-wrapper-->
               </div><!--/swiper-container-->
               
               <div class="swiper-pagination"></div>
               <div class="swiper-button-prev"></div>
               <div class="swiper-button-next"></div>
               
            </div><!--/swiper-holder-->
            
         </div><!--/col-12-->
      </div><!--/row-->

   </div><!--/inline-->
<?php if ($content): ?>
  
    <?php print $content; ?>
  
<?php endif; ?>
