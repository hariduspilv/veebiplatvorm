$.fn.gallery = function(){
   
   var main = $(this);
   var thumbCont = main.find(".gallery-thumbs:first");
   var paginator = main.find("#paginator:first");
   var gallery = main.find("#gallery:first");
   var thumbnails = thumbCont.find("li");
   var thumbsPerView = 15;
   var pages = Math.ceil( thumbnails.size() / thumbsPerView );
   var currentPage = 0;
   var visiblePageNumbers = 3;
   var startSlide = 0;
   var totalImages = thumbnails.size();
	var downloadObj = $("#download-link:first");
	
   var mThumbObj = main.find(".mobile-thumbnails:first");
	var mThumbHolder = mThumbObj.find(".mobile-thumbnails-holder");
	var mThumbScroller = mThumbObj.find(".mobile-thumbnails-scroller");
	mThumbScroller.html("<ul>"+thumbCont.html()+"</ul>");
	var mThumbnails = mThumbScroller.find("li");
	
   var slideTemplate = gallery.find(".swiper-wrapper:first").html();

	$(window).bind("keydown", function(e){
		var code = e.which || e.keyCode;
		
		if( mySwiper ){
			if( code == 37 ){
				mySwiper.slidePrev();
			}else if( code == 39 ){
				mySwiper.slideNext();
			}
		}
	});
	
   function generateSlides(){
      var slidesHTML = '';
      
      thumbnails.each(function(e, val){
         var obj = $(this);
         var anchor = obj.find("a:first");

         var image = anchor.attr("data-image");
         var title = anchor.attr("title");
         
         var tmp = slideTemplate;
         tmp = tmp.replace("?image?", image);
         tmp = tmp.replace("?title?", title);
         tmp = tmp.replace("?totalImages?", totalImages);
         tmp = tmp.replace("?currentImage?", e+1);
         
         slidesHTML+= tmp;
      });
      
      gallery.find(".swiper-wrapper:first").html( slidesHTML );
   }
   
   function fillEmptySlots(){
      var emptySlots = (pages * thumbsPerView) - thumbnails.size();

      var emptySlotsHTML = '';
      for( var i = 0; i < emptySlots; i++ ){
         emptySlotsHTML+= '<li><span>'+thumbnails.eq(0).find("a").html()+'</span></li>';
      }
      thumbCont.append(emptySlotsHTML);
      thumbnails = thumbCont.find("li");
   }
   
   function generatePaginator(){
      var paginatorHTML = '';

      if( pages == 1 ){ return false; }
      
      thumbnails.hide().slice(currentPage* thumbsPerView, (currentPage+1)*thumbsPerView ).show();
      
      paginatorHTML+= '<li><a href="#prev" class="before-arrow_left"></a></li>';
      
      var paginatorStart = currentPage;
      
      if( currentPage > 0 ){ paginatorStart--; }
      
      if( paginatorStart + (visiblePageNumbers+1) > pages ){
         paginatorStart = pages - (visiblePageNumbers+1);
      }
         
      var paginatorEnd = paginatorStart+visiblePageNumbers;
      if( paginatorEnd > pages ){ paginatorEnd = pages; }
      
      
      for( var i = paginatorStart; i < paginatorEnd; i++){
         if( i < 0 ){ continue; }
         if( i == currentPage ){
            paginatorHTML+= '<li class="active"><a href="#page-'+i+'">'+(i+1)+'</a></li>';  
         }else{
            paginatorHTML+= '<li><a href="#page-'+i+'">'+(i+1)+'</a></li>';  
         }
      }
      
      if( paginatorStart + visiblePageNumbers < pages-1 ){
         paginatorHTML+= '<li>...</li>';
      }
      
      if( currentPage+1 == pages ){
         paginatorHTML+= '<li class="active"><a href="#page-'+(pages-1)+'">'+(pages)+'</a></li>';
      }else{
         paginatorHTML+= '<li><a href="#page-'+(pages-1)+'">'+(pages)+'</a></li>';  
      }
      
      paginatorHTML+= '<li><a href="#next" class="before-arrow_right"></a></li>';
      
      paginator.html( paginatorHTML );
      
      bindPaginator();
      
   };
   
   function bindThumbnails(){
      
      var anchors = thumbnails.find("a");

      anchors.removeAttr("title").bind("click", function(e){
         e.preventDefault();
         var obj = $(this);
			var parent = obj.parent();
			var activeIndex = thumbnails.index( parent );
			
			if( mySwiper ){
				mySwiper.slideTo(activeIndex, 0);  
			}else{
				startSlide = activeIndex;
			}

			/*
         history.replaceState(undefined, undefined, "#image="+obj.attr("data-id"));
         $(window).trigger("hashchange");
			*/
			
      });
		
		mThumbnails.each(function(){
			var obj = $(this);
			var anchor = obj.find("a:first");
			
			anchor.bind("click", function(e){
				e.preventDefault();
				var activeIndex = mThumbnails.index( obj );

				if( mySwiper ){
					mySwiper.slideTo(activeIndex, 0);  
				}else{
					startSlide = activeIndex;
				}
			});
		});
   }
   
   function bindPaginator(){
      paginator.find("a[href*='#page-']").bind("click", function(e){
         e.preventDefault();
         var nr = $(this).attr("href").split("#page-")[1];
         nr = parseInt( nr );
         currentPage = nr;
         
         generatePaginator();
         
      });
      
      paginator.find("a[href='#prev']").bind("click", function(e){
         e.preventDefault();
         currentPage--;
         if(currentPage < 0 ){ currentPage = 0; return false;}
         generatePaginator();
      });
      
      paginator.find("a[href='#next']").bind("click", function(e){
         e.preventDefault();
         currentPage++;
         if(currentPage > pages - 1 ){ currentPage = pages - 1; return false;}
         generatePaginator();
      });
   };
   
   function bindHistory(){
		
		return false;
		
      $(window).on("hashchange", function(){
         var hash = getParameters(window.location.hash);
         if( hash.image ){
            var activeImage = thumbnails.find("a[data-id='"+hash.image+"']:first").parents("li:first");
            var activeIndex = thumbnails.index( activeImage );
            
            if( mySwiper ){
               mySwiper.slideTo(activeIndex, 0);  
            }else{
               startSlide = activeIndex;
            }
         }
      }).trigger("hashchange");
   }
   
   function setActiveThumbnail(){
      var activeIndex = mySwiper.activeIndex;
      
      thumbnails.filter(".active").removeClass("active");
      
      thumbnails.eq( activeIndex ).addClass("active");
      
      //history.replaceState(undefined, undefined, "#image="+thumbnails.eq( activeIndex ).find("a:first").attr("data-id"));
      
      var activeThumbPage = Math.floor(activeIndex / thumbsPerView);
      
      if( activeThumbPage !== currentPage ){
         currentPage = activeThumbPage;
         generatePaginator();
      }
		
		mThumbnails.removeClass("active").eq(activeIndex).addClass("active");
		
		var thumbLeft = mThumbnails.eq(activeIndex).position().left - mThumbHolder.position().left;
		var scrollLeft = mThumbHolder.scrollLeft();
		
		thumbLeft+= scrollLeft - (mThumbHolder.width()/2) + 50;
		
		mThumbHolder.animate({scrollLeft: thumbLeft}, {duration:250, queue:false});
		
		downloadObj.attr("href", thumbnails.eq( activeIndex ).find("a:first").attr("data-download") );
   };
   
   function loadGalleryImage(){
      
      var index = mySwiper.activeIndex;
      
      var activeSlide = gallery.find(".swiper-slide").eq(index);
      activeSlide.find(".gallery-image:first").attr("style", "background-image:url("+activeSlide.attr('data-image')+")");
		
		if( activeSlide.attr("data-imagePushed") !== "1"){
			activeSlide.find(".gallery-image:first").prepend('<img src="'+activeSlide.attr("data-image")+'" class="print_img"/>');
			
			activeSlide.attr("data-imagePushed", "1");
		}
      
      if( index > 0 ){
         var previousSlide = activeSlide.prev(".swiper-slide");
         previousSlide.find(".gallery-image:first").attr("style", "background-image:url("+previousSlide.attr('data-image')+")");
      }
      
      var nextSlide = activeSlide.next(".swiper-slide");
      if( nextSlide.size() > 0 ){
         nextSlide.find(".gallery-image:first").attr("style", "background-image:url("+nextSlide.attr('data-image')+")");
      }
      
      
   }
   
   bindHistory();
   
   generateSlides();
   
   var mySwiper = new Swiper(gallery.find(".swiper-container"), {
      slidesPerView: 1,
      prevButton: gallery.find(".swiper-button-prev:first"),
      nextButton: gallery.find(".swiper-button-next:first"),
      onSlideChangeEnd: function(swiper){
         loadGalleryImage();
         setActiveThumbnail();
      }
   });
   
	gallery.find(".swiper-container").find(".swiper-slide").bind("click", function(){
		if( $(window).width() <= 375 && $(window).width() > $(window).height() ){
			$(this).parents(".overlay:first").trigger("click");
		}	
	});
	
   mySwiper.slideTo(startSlide, 0);
   
   fillEmptySlots();
   
   generatePaginator();
   
   loadGalleryImage();
   
   bindThumbnails();
	setActiveThumbnail();
}