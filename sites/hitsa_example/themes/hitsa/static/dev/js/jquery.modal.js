$.fn.modal = function(){
	var main = $(this);
	var href = main.attr("href");
	var html, overlay;
	var xhr = false;
	var visible = false;
   var type = "html";
	var title = main.attr("title") || main.attr("data-title");
	var heading = main.attr("data-heading") || "";
	
	main.bind("click", function(e){
		e.preventDefault();
		
		if( main.attr("data-modal") ){
			var id = $(this).attr("data-modal");
			
			var hash = getParameters(window.location.hash);
			
			hash.modal = id;
			
			var newHash = compileHash(hash);
			history.replaceState(undefined, undefined, newHash);
			$(window).trigger("hashchange");	
		}else{
			getType();
			openOverlay();
			getData();
		}
		
	});
	
	function checkHash(){
		var hash = getParameters(window.location.hash);

		if( hash.modal == main.attr("data-modal") && !visible){
			getType();
			openOverlay();
			getData();
		}else if( hash.modal !== main.attr("data-modal") && visible ){
			closeOverlay();
		}
	}
	
	function compileHash(hash){
		var newHash = '#';

		for( var i in hash ){
			if( newHash !== "#"){newHash+='&';}
			newHash+= i+"="+hash[i];

		}
		
		return newHash;
	}
	
	if( main.attr("data-modal") ){
		$(window).bind("hashchange", function(){
			checkHash();
		});
		
		if( window.location.hash ){
			checkHash();
		}
	}
	
	$(window).unbind("overlay:close").bind("overlay:close", function(){
	   closeOverlay();
	});
	
	main.bind("close", function(){
	   closeOverlay();
	});
	
	if( main.attr("data-init") ){
		main.trigger("click");
	}
	
	function getType(){
		if( href.match(".jpg") || href.match(".jpeg") || href.match(".png") ){
			type = "image";
		}
		else if( href.match("youtube.") ){
			type = "youtube";
		}else{
			type = "html";
		}
	};
	
	function getData(newHref){
		
		var tmpHref = newHref ? newHref : href;
		
		if( type == "image" ){
			var tmp = new Image();
			tmp.onload = function(){
				appendContent();
			};
			tmp.src = href;
		}
		else if( type == "youtube" ){
			appendContent();
		}
		else{
			xhr = $.ajax({
				dataType: "html",
				url: tmpHref,
				cache: false,
				success: function(response){
					html = $(response).find("[data-modal]")[0].outerHTML;
					appendContent();
				}
			});
		}
		
	}
	
	function openOverlay(parameters){
		
      if( visible ){ return false; }
      visible = true;
      
		var output = 	'<div class="overlay" data-close="true">';
			output+= 	'</div><!--/overlay-->';
		
		$("body").append(overlay = $(output) );
		$("html").addClass("overflow-hidden");
		
      if( parameters ){
         if( parameters["search"] ){
            overlay.attr("data-search", parameters["search"] );
         }
      }
      
		overlay.fadeIn(250, function(){
				
		});
		
		
		overlay.bind("click", function(e){
			if( $(e.target).is("[data-close]") ){
				e.preventDefault();
				closeOverlay();
			}
		});
		
	}
	
	function appendContent(){
		visible = true;
		if( !visible ){
			setTimeout(function(){
				appendContent();
			}, 100);
			return false;
		}
		
		var addonClass = '';
		
		if( html && $(html).is(".sm-opaque") ){
			addonClass = "overlay-gallery";
		};
		
		if( main.attr("data-modalClass") ){
			addonClass = main.attr("data-modalClass");
		}
		
		if( type == "image" ){
			addonClass = "size-m";
		}else if( type == "youtube" ){
			addonClass = "overlay-video";
		}
		
		var output = '';
		output+=			'<div class="overlay-inline '+addonClass+'">';
		
		if( type == "image" ){
			output+=	'<div class="block">';

				output+= '<div class="block-title">'+heading+'&nbsp;<a href="javascript:void(0);" data-close="true" class="btn btn-transparent pull-right after-close">'+main.attr("data-closeButton")+'</a></div>';
				output+= '<div class="btn-bar align-right"> <a href="javscript:void(0);" class="btn-circle before-share" data-plugin="share"></a> <a href="javascript:window.print();" class="sm-hide btn-circle before-print"></a> <a href="'+href+'" id="download-link" target="_blank" class="btn-circle before-download"></a></div><div class="row-spacer">&nbsp;</div>';
				output+= '<figure><img src="'+href+'" /><figcaption>'+title+'</figcaption></figure>';
			output+= '</div><!--/block-->';
		}
		else if( type == "youtube" ){
			var youtubeHash = getParameters( "?"+href.split("?")[1] )['v'];
			output+=	'<div class="block">';
				output+= '<div class="block-title">'+heading+'&nbsp;<a href="javascript:void(0);" data-close="true" class="btn btn-transparent pull-right after-close">'+main.attr("data-closeButton")+'</a></div>';
				output+= '<div class="btn-bar align-right"> <a href="javscript:void(0);" class="btn-circle before-share" data-plugin="share"></a></div><div class="row-spacer">&nbsp;</div>';
				output+= '<div class="video-container"><iframe width="100%" height="600" src="https://www.youtube.com/embed/'+youtubeHash+'?autoplay=1" frameborder="0" allowfullscreen></iframe></div>';
			output+= '</div><!--/block-->';
		}
		else{
			output+=			html;	
		}
		output+=			'</div>';
		
		overlay.html( output );
		
		setTimeout(function(){
			overlay.addClass("overlay-enter content-loaded");	
		}, 10);
		
		bindEvents();
		
	}
	
	function closeOverlay(){
		
		if( xhr ){
			xhr.abort();
			xhr = false;	
		}
		
		overlay.removeClass("overlay-enter");
		
		visible = false;
		html = "";
		
		setTimeout(function(){
			overlay.fadeOut(250, function(){
				$("html").removeClass("overflow-hidden");
				overlay.remove();
			});
		}, 250);
		
		var hash = getParameters(window.location.hash);
		
		if( hash.modal ){
			
			if( hash.modal == main.attr("data-modal") ){
				delete hash.modal;
				delete hash.anchor;

				var newHash = compileHash(hash);

				history.replaceState(undefined, undefined, newHash);	
			}
			
		}
		
		
	}
	
	function bindEvents(){
		
		overlay.find("[target='overlay']").bind("click", function(e){
			e.preventDefault();
			overlay.removeClass("content-loaded");
			getData( $(this).attr("href") );
		});
		
		$(window).bind("keydown.modal", function(e){
			var key = 'which' in e ? e.which : e.keyCode;
			
			if( key == 27 ){
				closeOverlay();
				$(window).unbind("keydown.modal");
			}
		});
		
		

		$wpm.bindObjects(overlay);
      
	}
	
}