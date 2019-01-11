document.addEventListener('DOMContentLoaded', function(){
	// do something
	selection =  document.getElementById("edit-cp-type-und");

	extra_picture = document.getElementById("edit-cp-image");
	//More Details https://developer.mozilla.org/en-US/docs/Web/API/MutationObserver
	// select the target node
	// create an observer instance
	var observer = new MutationObserver(function(mutations) {

		adding_button = document.getElementsByClassName("form-item-cp-image-und-1");
		adding_button[0].style.display="none";

	});
	if(selection.value == 'cp_specialities'){
		extra_picture = document.getElementById("edit-cp-image");
		adding_button = document.getElementsByClassName("form-item-cp-image-und-1");
		if(typeof adding_button[0]!=='undefined'){
			adding_button[0].style.display="none";
		}

		// configuration of the observer:
		var config = { attributes: true, childList: true, characterData: true };
		// pass in the target node, as well as the observer options
		observer.observe(extra_picture, config);
	}
	selection.addEventListener("change" , function(){

		if(selection.value == 'cp_specialities'){
			extra_picture = document.getElementById("edit-cp-image");
			adding_button = document.getElementsByClassName("form-item-cp-image-und-1");
			if(typeof adding_button[0]!=='undefined'){
				adding_button[0].style.display="none";
			}

			var config = { attributes: true, childList: true, characterData: true };

			observer.observe(extra_picture, config);
		}
		else{

			extra_picture = document.getElementById("edit-cp-image");
			adding_button = document.getElementsByClassName("form-item-cp-image-und-1");

			if(typeof adding_button[0]!=='undefined'){
				adding_button[0].style.display="block";
			}

		}
	});

});
