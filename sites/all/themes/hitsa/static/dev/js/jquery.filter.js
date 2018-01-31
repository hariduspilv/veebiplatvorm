$.fn.filters = function(){
	
	var main = $(this);
	var formItems = main.find("input, select");
	var onSubmit = {};
	
	main.bind("submit", function(e){
		e.preventDefault();
		buildURL(true);
	});
	
	formItems.not("[data-onSubmit]").bind("change dynamic:change", function(e){
		var obj = $(this);
		var name = obj.attr("name");
		var relatives = formItems.filter("[name='"+name+"']");
		var all = relatives.filter("[value='all']");
		
		if( name !== "page" ){
			formItems.filter("[name='page']").val("");
		}
		
		if( obj.is(all) && obj.is(":checked") ){
			relatives.not(all).prop("checked", false);
		}
		else if( obj.not(all) && obj.is(":checked") ){
			all.prop("checked", false);
		}
		buildURL();
	});
	
	function buildURL(buildAll){
		
		var array = {};
		
		formItems.filter("[type='checkbox']:checked,[type='radio']:checked").each(function(){
			var obj = $(this);
			var name = obj.attr("name");
			var value = obj.attr("value");
			var onSubmitStatus = obj.attr("data-onSubmit");
			
			if( onSubmitStatus ){
				if( buildAll ){
					onSubmit[name] = value;
				}
				return;
			}
			
			if( !array[name] ){ array[name] = []; }
			array[name].push( value );
		});
		
		var url = '';
		
		for( var i in array ){
			var tmp = array[i].join(",");
			if( url !== "" ){ url+="&"; }
			url+= i+"="+tmp;
		};
		
		formItems.filter("input[type='text'], input[type='hidden'], select").each(function(){
			var obj = $(this);
			var name = obj.attr("name");
			var value = obj.val();
			var onSubmitStatus = obj.attr("data-onSubmit");
			
			if( value !== "" && !onSubmitStatus){
				if( url !== "" ){ url+= "&"; }
				url+= name+"="+value;
			}else{
				if( buildAll ){ 
					onSubmit[name] = value;
				}
			}
		});
		
		for( var i in onSubmit ){
			if( onSubmit[i] !== "" ){
				if( url !== "" ){ url+="&";}
				url+= i+"="+onSubmit[i];
			}	
		}
		
		url = "?"+url;
		
		history.replaceState(undefined, undefined, url);
		$(window).trigger("querychange");
		
	}
	
	function initializeFormItems(){
		var query = window.location.search;
		
		if( query == "?" || query == "" ){ return false; }
		
		query = getParameters( query );
		
		for( var i in query ){
			var inputs = formItems.filter("[name='"+i+"']");

			inputs.filter("[type='checkbox'],[type='radio']").prop("checked", false);
			var name = i;
			
			var params = query[i].split(",");
			
			for( var ii in params ){
				var current = params[ii];
				var element = inputs.filter("[name='"+name+"']");
				
				if( element.is("select,input[type='text'],input[type='hidden']") ){
					if( element.is("[data-onSubmit]") ){
						onSubmit[name] = current;	
					}
					element.val(current);
				}else{
					element = element.filter("[value='"+current+"']");
					element.prop("checked", true);
				}
				
			}
			
		}
		
	}
	
	initializeFormItems();
	
};


$.fn.filterContents = function(){
	var main = $(this);
	var postURL = main.attr("data-postURL");
	
	function postData(){
		$.ajax({
			url: postURL,
			data: window.location.search.replace("?", ""),
			dataType: "html",
			success: function(response){
				main.html(response);
				$wpm.bindObjects( main );
			}
		})
	}
	
	$(window).bind("querychange", function(){
		postData();
	});
}

$.fn.filterPaginator = function(){
	var main = $(this);
	var anchors = main.find("[data-page]");
	var relative = $("#"+ main.attr("data-relative") );
	var minValue = parseInt(anchors.filter("[data-rel='first']:first").attr("data-page"));

	var maxValue = parseInt(anchors.filter("[data-rel='last']:first").attr("data-page"));
	
	anchors.bind("click", function(e){
		e.preventDefault();
		var obj = $(this);
		var page = obj.attr("data-page");
		
		if( page == "prev" || page == "next" ){
			var inputValue = parseInt(relative.val());
			if( isNaN(inputValue) ){ inputValue = 0; }
			
			inputValue = page == "prev" ? inputValue-1 : inputValue+1;
			
			if( inputValue < minValue ){ inputValue = minValue; }
			if( inputValue > maxValue ){ inputValue = maxValue; }
			
			relative.val(inputValue).trigger("change");
		}else{
			page = parseInt( page );
			relative.val(page).trigger("change");
		}
		
	});
}