var mapStyles = [ { "featureType": "water", "elementType": "geometry", "stylers": [ { "color": "#e9e9e9" }, { "lightness": 17 } ] }, { "featureType": "landscape", "elementType": "geometry", "stylers": [ { "color": "#f5f5f5" }, { "lightness": 20 } ] }, { "featureType": "road.highway", "elementType": "geometry.fill", "stylers": [ { "color": "#ffffff" }, { "lightness": 17 } ] }, { "featureType": "road.highway", "elementType": "geometry.stroke", "stylers": [ { "color": "#ffffff" }, { "lightness": 29 }, { "weight": 0.2 } ] }, { "featureType": "road.arterial", "elementType": "geometry", "stylers": [ { "color": "#ffffff" }, { "lightness": 18 } ] }, { "featureType": "road.local", "elementType": "geometry", "stylers": [ { "color": "#ffffff" }, { "lightness": 16 } ] }, { "featureType": "poi", "elementType": "geometry", "stylers": [ { "color": "#f5f5f5" }, { "lightness": 21 } ] }, { "featureType": "poi.park", "elementType": "geometry", "stylers": [ { "color": "#dedede" }, { "lightness": 21 } ] }, { "elementType": "labels.text.stroke", "stylers": [ { "visibility": "on" }, { "color": "#ffffff" }, { "lightness": 16 } ] }, { "elementType": "labels.text.fill", "stylers": [ { "saturation": 36 }, { "color": "#333333" }, { "lightness": 40 } ] }, { "elementType": "labels.icon", "stylers": [ { "visibility": "off" } ] }, { "featureType": "transit", "elementType": "geometry", "stylers": [ { "color": "#f2f2f2" }, { "lightness": 19 } ] }, { "featureType": "administrative", "elementType": "geometry.fill", "stylers": [ { "color": "#fefefe" }, { "lightness": 20 } ] }, { "featureType": "administrative", "elementType": "geometry.stroke", "stylers": [ { "color": "#fefefe" }, { "lightness": 17 }, { "weight": 1.2 } ] }];

$.fn.googleMaps = function(){
   var main = $(this);
	var zoom = main.attr("data-zoom") || 17;
	var mapObj, marker;

   var icon = {
      url: main.attr("data-icon"),
      scaledSize: new google.maps.Size(28, 40)
   };
   
   var latlng = {
      lat: parseFloat( main.attr("data-coords").split(",")[0] ),
      lng: parseFloat( main.attr("data-coords").split(",")[1] )
   };
	
	function initialize(){
		mapObj = new google.maps.Map(main[0], {
			scrollwheel: false,
			center: latlng,
			zoom: parseInt(zoom),
			mapTypeControl: false,
			styles: mapStyles
		});

		marker = new google.maps.Marker({
			position: latlng,
			icon: icon
		});

		marker.setMap(mapObj);
		
	};
   
   
	$(window).bind("resize:googleMaps", function(){
		if( mapObj ){
			mapObj.setCenter(latlng);
		}
	});
	
	main.bind("dynamic:resize", function(){
		setTimeout(function(){
			initialize();
		}, 100);
	});
	
	initialize();
	
};