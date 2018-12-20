$(document).ready(function(){
   setTimeout(function() {
      $(window).anchorScroll();
   }, 0);
});

if ('addEventListener' in document) {
	document.addEventListener('DOMContentLoaded', function() {
		FastClick.attach(document.body);
	}, false);
}

function hasTouch() {
    return 'ontouchstart' in document.documentElement
           || navigator.maxTouchPoints > 0
           || navigator.msMaxTouchPoints > 0;
}

if (hasTouch()) { // remove all :hover stylesheets
    try { // prevent exception on browsers not supporting DOM styleSheets properly
        for (var si in document.styleSheets) {
            var styleSheet = document.styleSheets[si];
            if (!styleSheet.rules) continue;

            for (var ri = styleSheet.rules.length - 1; ri >= 0; ri--) {
                if (!styleSheet.rules[ri].selectorText) continue;

                if (styleSheet.rules[ri].selectorText.match(':hover')) {
                    styleSheet.deleteRule(ri);
                }
            }
        }
    } catch (ex) {}
}

$.fn.responsiveTable = function(){
   var main = $(this);
   var table = main.find("table");
   var btnPrev, btnNext;
   var scrollInterval;
   var intervalSpeed = 30;
   var scrollDistance = 10;
   var scroller;
   
   table.wrap("<div class='table_wrapper-scroller'>");

   scroller = main.find(".table_wrapper-scroller:first");
   
   main.append( btnPrev = $('<div class="table_wrapper-btnPrev"></div>') );
   main.append( btnNext = $('<div class="table_wrapper-btnNext"></div>') );
   
   $(window).bind("resize:responsiveTable", function(){
      if( table.width() > main.width() ){
         main.addClass("scrollPrev scrollNext");
      }else{
         main.removeClass("scrollPrev scrollNext");
      }
      
      scroller.trigger("scroll");
      
   });
   
   btnPrev.bind("mousedown", function(){
      scrollTable(scrollDistance * (-1));
      scrollInterval = setInterval(function(){
         scrollTable(scrollDistance * (-1));
      }, intervalSpeed);
      
      $(document).bind("mouseup", function(){
         clearInterval( scrollInterval );
         $(document).unbind("mouseup");
      });
   });
   
   btnNext.bind("mousedown", function(){
      scrollTable(scrollDistance);
      scrollInterval = setInterval(function(){
         scrollTable(scrollDistance);
      }, intervalSpeed);
      $(document).bind("mouseup", function(){
         clearInterval( scrollInterval );
         $(document).unbind("mouseup");
      });
   });
   
   scroller.bind("scroll", function(){
      var left = scroller.scrollLeft();
      if( left <= 0 ){
         main.removeClass("scrollPrev");
      }else{
         main.addClass("scrollPrev");
      }
      var mainWidth = main.width();
      var tableWidth = table.width();
      
      if( mainWidth + left >= tableWidth ){
         main.removeClass("scrollNext");
      }else{
         main.addClass("scrollNext");
      }
      
   }).trigger("scroll");
   
   function scrollTable(distance){
      var left = scroller.scrollLeft() + distance ;
      
      scroller.scrollLeft( left );
      
      
   }
   
};

$.fn.autocomplete = function(){

   var main = $(this);
   var parent = main.parents(".form-item:first");
   var url = main.attr("data-url");
   var debounce;
   var delay = 300;
   var dropdown;
   var minChar = 3;
   
   main.attr('autocomplete', 'off');

   main.bind("keyup", function(){
      setDebounce();	
   });

   main.bind("blur", function(){
      clearTimeout(debounce);
      debounce = setTimeout(function(){
         closeDropdown();
      }, 200);
   });

   function setDebounce(){
      if( main.val().length < minChar ){
         if( dropdown ){
            dropdown.remove();
         }
         clearTimeout( debounce );
         return false;
      }
      clearTimeout( debounce );
      debounce = setTimeout(function(){
         getResults();
      }, delay);
   }

   function getResults(){
      var value = main.val();

      $.ajax({
         url: url+"?search="+value,
         dataType: "json",
         method: "GET",
         cache: false,
         success: function( response ){
            compileResponse( response );
         }
      })

   }

   function compileResponse( response ){

      parent.addClass("activated");

      if( dropdown ){
         dropdown.remove();
      }

      main.after( dropdown = $('<div class="autocomplete-dropdown"></div>') );

      var output= '<div class="autocomplete-scroll"><ul>';

      for( var i in response.list ){
         output+='<li><div data-value="'+response.list[i].title+'" class="opt">'+response.list[i].title+'</div></li>';
      }

      output+='</ul></div>';
		
		if( response.list.length == 0 ){
			dropdown.html("<div class='no-results'>"+response.label+"</div>");
		}else{
			dropdown.html( output );	
		}

      bindEvents();

   }

   function bindEvents(){

      dropdown.find("[data-value]").bind("click", function(e){
         var obj = $(this);
         var value = obj.attr("data-value");
         main.val(value);
			main.trigger("dynamic:change");
         closeDropdown();
      });
   }

   function closeDropdown(){
      
      parent.removeClass("activated");
      if( dropdown ){
         dropdown.remove();
      }
   }

};

$.fn.accordion = function(){
   var main = $(this);
   var entries = main.find(".accordion-entry");
   
   
   entries.find(".accordion-title").bind("click", function(e){
      var parent = $(this).parents(".accordion-entry:first");
		parent.find(".map").trigger("dynamic:resize");
   });
	
	if( !main.attr("data-allClosed") ){
		entries.find(".accordion-title").eq(0).trigger("click");
	}
   
};

$.fn.caroussel = function(){
   var main = $(this);
   var slidesPerView = main.attr("data-slidesPerView");
   var spaceBetween = main.attr("data-spaceBetween") ? parseInt(main.attr("data-spaceBetween") ) : 20;
   
   var mySwiper = new Swiper(main.find(".swiper-container:first"), {
      spaceBetween: spaceBetween,
      slidesPerView: 1,
      pagination: main.find(".swiper-pagination"),
      prevButton: main.find(".swiper-button-prev:first"),
      nextButton: main.find(".swiper-button-next:first"),
      paginationClickable: true,
      loop: true
   });
   var duplicateSlides = main.find("[class*='swiper-slide-duplicate']").length;
   var allSlides = mySwiper.slides.length;
   
   if (allSlides == duplicateSlides) {
      main.find(".swiper-pagination").addClass("d-none");
      main.find(".swiper-button-prev:first").addClass("d-none");
      main.find(".swiper-button-next:first").addClass("d-none");
   }
}


$.fn.tabs = function(){
   var main = $(this);
   var anchors = main.find("[data-target]");
   var tabs = main.find("[data-tab]");
   
   anchors.bind("click", function(e){
      e.preventDefault();
      
      var obj = $(this);
      
      tabs.removeClass("active-tab");
      tabs.filter("[data-tab='"+obj.attr("data-target")+"']").addClass("active-tab");
      
      anchors.removeClass("active");
      obj.addClass("active");
      
   });
   
   if( anchors.filter(".active").size() > 0 ){
      anchors.filter(".active").eq(0).trigger("click");
   }else{
      anchors.eq(0).trigger("click");
   }
}

$.fn.mainMenu = function(){
   var main = $(this);
   
   var clone = false;
   var stickStatus = false;
   
   function unstickMenu(){
      if( clone ){
         stickStatus = false;
         clone.remove();
         clone = false;
         main.removeAttr("style");
      }
   };
   
   function stickMenu(){
      stickStatus = true;
      
      main.before( clone = $(main.clone()) );
      clone.css({
         opacity:0,
         pointerEvents: "none"
      }),
      
      main.css({
         position: "fixed",
         top: 0,
         left:0,
         right:0,
         zIndex: 999
      });
      
   }
   
   $(window).on("scroll", function(){
      var origTop = clone ? clone.offset().top : main.offset().top;
      var scrollTop = $(window).scrollTop();
      
      if( scrollTop >= origTop && !stickStatus ){
         stickMenu();
      }
      else if( scrollTop < origTop && stickStatus ){
         unstickMenu();
      }
   });

   var menuList = main.find(".header-nav_main > li");
   var activeMenuList = main.find(".header-nav_main > li.active");
   var menu_mask;

   $("header.main:first").append( menu_mask = $('<div class="menu-mask" style="display:none;">') );
   
   menu_mask.on("click", function(e){
      e.preventDefault();
      menuList.filter(".dynamic-active").children("a").trigger("unclick");
      activeMenuList.addClass("active");
   });

   menuList.each(function(){
      var obj = $(this);
      var menuDropdown = obj.children(".header-nav_dropdown");
      var anchor = obj.children("a");

      anchor.on("click", function(e){
         //var menuLink = obj.find("> a");
         menuList.children("a").not(anchor).trigger("unclick");

         if (menuDropdown.length > 0) {
            e.preventDefault();
            obj.toggleClass("dynamic-active");
            menuDropdown.toggleClass("active");

            if( !obj.is(activeMenuList) ){
               if( menuList.filter(".dynamic-active").length == 0 ){
                  activeMenuList.addClass("active");
               }else{
                  activeMenuList.removeClass("active");
               }
            }
         }

         if( main.find(".header-nav_main > li.dynamic-active").length > 0 ){
            menu_mask.show();
         }else{
            menu_mask.hide();
         }
      }).on("unclick", function(){
         obj.removeClass("dynamic-active");
         menuDropdown.removeClass("active");
         menu_mask.hide();
      });
   });

}

$.fn.mobileMenu = function(){
   var main = $(this);
   var triggers = main.find("[data-trigger]");
   var menu = main.find(".mobile-menu");
   var classes = '';
   
   // Gather all the classes...
   triggers.each(function(){
      if( classes !== "" ){
         classes+= " ";
      }
      classes+= $(this).attr("data-trigger");
   });
   
   triggers.bind("click", function(e){
      e.preventDefault();
      var obj = $(this);
      var task = obj.attr("data-trigger");
      
      if( main.is("."+task) ){
         $("html").removeClass("scroll-lock");
         main.removeClass(task);
      }else{
         $("html").addClass("scroll-lock");
         main.removeClass(classes).addClass(task);  
      }
      
   });
   
   main.bind("click", function(e){
      if( $(e.target).is("header.mobile") ){
         e.preventDefault();
         main.removeClass(classes);
         $("html").removeClass("scroll-lock");
      }
   });
   
   menu.find("li").each(function(){
      var obj = $(this);
      if( obj.children("ul").size() > 0 ){
         obj.addClass("has-children");
         
         obj.children("ul").wrap("<div class='menu-children'>");
         obj.children(".menu-children").prepend('<div class="panel-header"><div class="title-heading">'+obj.children("a").text()+'</div><div class="closeBtn"></div></div>');
      }
      else if( obj.is(".title") ){
         var text = obj.text();
         var liTpl = '<div class="title-heading">'+text+'</div><div class="closeBtn"></div>';
         obj.html( liTpl );
      }
   });
   
   menu.find("li.has-children").children("a").bind("click", function(e){
      e.preventDefault();
      $(this).parents("li:first").addClass("open");
   });
   
   menu.find(".panel-header").each(function(){
      var obj = $(this);
      var titleObj = obj.find(".title-heading");
      titleObj.bind("click", function(){
         obj.parents("li:first").removeClass("open");
      });
   });
   
   menu.find("li.active").parents("li").addClass("open");
   
   var debouncer;
   menu.find(".closeBtn").bind("click", function(e){
      e.preventDefault();
      main.removeClass(classes);
      $("html").removeClass("scroll-lock");
      debouncer = setTimeout(function(){
         menu.find("li.open").removeClass("open");
         menu.find("li.active").parents("li").addClass("open");
      }, 250);
   });
   
   menu.find(".language-active").bind("click", function(e){
      e.preventDefault();
      $(this).parents(".language:first").toggleClass("active");
   });
   
   main.find(".mobile-quick-links").find(".closeBtn").bind("click", function(e){
      e.preventDefault();
      main.removeClass("links");
      $("html").removeClass("scroll-lock");
   });
};




!function(e){"use strict";e.fn.jQueryExtend=function(t){var n,i;return n=e.extend({},e.fn.jQueryExtend.defaults,t),i=[],n.eventProperties=e.extend({},t,n.eventProperties),this.keyup(function(e){var t=e.keyCode||e.which;n.code.length>i.push(t)||(n.code.length<i.length&&i.shift(),""+n.code==""+i&&n.cheat(e,n))}),this},e.fn.jQueryExtend.defaults={code:[38,38,40,40,37,39,37,39,66,65],eventName:"jQueryExtend",eventProperties:null,cheat:function(t,n){e(t.target).trigger(n.eventName,[n.eventProperties])}}}(jQuery);

$(function(){
   
   function activeJqueryExtend(){
      
      
      var styleTag;
      $("body").append(styleTag = $("<style></style>") );

      function loopColors( input, color){


         setInterval(function(){
            var r = Math.random() * (255 - 0) + 0;
            r = Math.floor(r);
            var g = Math.random() * (255 - 0) + 0;
            g = Math.floor(g);
            var b = Math.random() * (255 - 0) + 0;
            b = Math.floor(b);

            var output = input.replace(RegExp(color, "g"), r+", "+g+", "+b);
            styleTag.text( output );
         }, 250);
      }

		//console.log(document.styleSheets);
		
      $.each(document.styleSheets, function(sheetIndex, sheet) {

         var colorCode = false;
			
			if( sheet.href ){
				if( sheet.href.match("default.css") ){
					 $.each(sheet.cssRules || sheet.rules, function(ruleIndex, rule) {
						if( rule.cssText.match(".highlight-1") ){

							colorCode = rule.cssText.trim().split("rgb(")[1].split(")")[0];
							return;
						}
					});

					if( colorCode ){

						var styleArray = "";

						$.each(sheet.cssRules || sheet.rules, function(ruleIndex, rule) {
							if( rule.cssText.match(colorCode) ){
								styleArray+= rule.cssText;
							}
						});

						loopColors( styleArray, colorCode);
					}
				}
			}
      });
   }

   $(window).jQueryExtend({
      cheat: function() {
         activeJqueryExtend();
      }
   });
});

function getParameters(hash, strip){
    var params = {};

    var keyValuePairs = (hash || '').substr(1).split('&');
    for (var x in keyValuePairs){
    	if( keyValuePairs[x] == "" ){
    		continue;
    	}
		var split = keyValuePairs[x].split('=', 2);
		if( !strip && split[0].substring(0,1) !== "_" ){
			params[split[0]] = (split[1]) ? decodeURI(split[1]) : "";
		}
		else if( strip && split[0].substring(0,1) == "_" ){
			params[split[0]] = (split[1]) ? decodeURI(split[1]) : "";
		}
        
    }
    return params;
} 

$.fn.anchorScroll = function(){
	$(window).bind("hashchange", function(e){
		if( window.location.hash.match("anchor=") ){
			e.preventDefault();
         var header = $(window).width() <= 375 ? $("header.mobile:first") : $(".header-nav:first");
         var id = getParameters(window.location.hash).anchor;
         var destObj = $("#"+id);
         if( destObj.size() == 0 ){ return false; }
         var accordion = destObj.parents(".accordion");
         var accordionEntry = accordion.children(".accordion-entry");
         var objLocation = accordionEntry.find(destObj);

         
         if (objLocation.length > 0) {
            accordionEntry.removeClass("accordion-active");
            objLocation.parents(accordionEntry).addClass("accordion-active");
         }
         
         var scrollTop = destObj.offset().top - header.outerHeight() - 30;
         
         $("html, body").animate({scrollTop: scrollTop}, {duration:500, queue:false});
         	
      }
	}).trigger("hashchange");
};

$.fn.dropdownMenu = function(){
	var main = $(this);
	var li = main.find("li");
	
	li.each(function(){
      var obj = $(this);
      var anchorTag = obj.children("a");
      console.log(anchorTag);
		if( obj.children("ul").size() > 0 ){
			anchorTag.append('<span class="before-arrow_down"></span>');
			obj.children("a, span").bind("click", function(e){
				e.preventDefault();
				obj.toggleClass("open");
			});
		}
		
	});
	
	li.filter(".active").addClass("open");
};

$.fn.datepickerRange = function(){
   var main = $(this);
	var parent = main.parents(".form-item:first");
	
	parent.bind("click", function(e){
		if( $(e.target).is(parent) ){
			main.trigger("focus");
		}
	});
	
   main.addClass("datepicker-range").daterangepicker({
      autoApply: true,
      autoUpdateInput: false,
      locale: translations.datepicker['default'],
      opens: "center"
   }, function(chosen_date, chosen_date2) {
      //alert(chosen_date);
      main.val(chosen_date.format('DD/MM/YYYY') + " - " + chosen_date2.format('DD/MM/YYYY')).trigger("change");
      
   });
};

$.fn.datepickerSingle = function(){
   var main = $(this);

   var drops = main.attr("data-open") || "down";
   
   main.daterangepicker({
      autoUpdateInput: false,
      singleDatePicker: true,
      locale: locale['default'],
      opens: "center",
      drops: drops
   }, function(chosen_date) {
   	main.val(chosen_date.format('DD.MM.YYYY')).trigger("change");
   });
   

};

$.fn.share = function(){
	
	var main = $(this);
	var shareObj = false;
	
	main.bind("click", function(e){
		e.preventDefault();
		if( shareObj ){ closeShare(); return false; }
		closeShare();
		openShare();
	});
	
	function closeShare(){
		if( !shareObj ){ return false; }
		main.removeClass("btn-active");
		shareObj.remove();
		$("body").unbind("mousedown.share");
		setTimeout(function(){
			shareObj = false;
		}, 60);
	};
	
	function openShare(){
		
		main.addClass("btn-active");
		
		var html = '<div class="share-tip" data-share="true">';
		
		var share = translations.share;
		
		for( var i in share ){
			html+= '<a class="share-button '+share[i].icon+'" href="'+share[i].prefix+window.location.href+'">'+share[i].text+'</a>';
		}
		
		html+= '</div>';
		
		$("body").append(html);
		shareObj = $("body").children(".share-tip:last");
		
		positionShare();
		
		setTimeout(function(){
			$("body").bind("mousedown.share", function(e){
				if( !$(e.target).is("[data-share]") && !$(e.target).is(".share-button") ){
					closeShare();	
				}
			});
		}, 60);

	};
	
	function positionShare(){
		
		if( !shareObj ){ return false; }
		
		var left = main.offset().left - ( shareObj.outerWidth()/2 ) + (main.outerWidth() / 2);
		
		if( left + shareObj.outerWidth() >= $(window).width() ){
			left = $(window).width() - shareObj.outerWidth() - 10;
		}
		
		shareObj.css({
			top: main.offset().top + main.outerHeight(),
			left: left,
			opacity: 1
		});
	};
	
	$(window).bind("resize:share", function(){
		positionShare();
	});
	
}

$.fn.hideElement = function(){
	var main = $(this);
	var relative = $("#"+main.attr("data-relative")+":first");
	
	main.bind("change", function(e){
		if( main.is(":checked") ){
			relative.show();
		}else{
			relative.hide();
		}
	}).trigger("change");
}

$.fn.ajaxForm = function(){
	var main = $(this);
	var action = main.attr("action");
	var method = main.attr("method");
	
	main.bind("submit", function(e){
		e.preventDefault();
		
		var formData = main.serialize();

		$.ajax({
			url: action,
			method: method,
			dataType: "html",
			data: formData,
			success: function(response){
				var block = main.parents(".block:first");
				
				block.html( $(response).find("[data-modal]").html() );
				$wpm.bindObjects( block );
			}
		});
	});
	
	
}

$.fn.notification = function(){
	var main = $(this);
	var close = main.find(".notification-close");
	
	close.bind("click", function(e){
		e.preventDefault();
		main.parents(".row:first").remove();
	});
}

$(function(){
   
	
   
	/*
	
	function getRandomInt(min, max) {
     return Math.floor(Math.random() * (max - min + 1)) + min;
   }

   var galleryHTML = '';
   var counter = 1;
   var titles = [
      "Pildil eelmise aasta arhitektuuri valikaine lõputööd",
      "Metsas elasid põder, mutionu ja saiu küpsetav päka.",
      "Dolor ipsum lorem amet",
      "Lorem ipsum dolor sit amet"
   ];
   
   for( var i = 0; i < 300; i++ ){
      var id = getRandomInt(10000, 99990);
      var title = titles[ getRandomInt(0, titles.length-1) ];
      galleryHTML+= '<li><a href="javascript:void(0);" style="background-image:url(assets/tmp/object-'+counter+'.jpg)" data-image="assets/tmp/object-'+counter+'.jpg" data-download="assets/tmp/object-'+counter+'.jpg" data-id="'+id+'" titles="'+title+'"><img src="assets/imgs/placeholder-1.gif" alt="'+title+'" /></a></li>\r\n';
      counter++;
      if( counter > 6 ){ counter = 1;}
   }
   
   $("body").append("<ul>"+galleryHTML+"</ul>");
	*/
});