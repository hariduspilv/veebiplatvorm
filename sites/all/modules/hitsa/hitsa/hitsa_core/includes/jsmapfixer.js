document.addEventListener("DOMContentLoaded", function(event) {
    // Select the node that will be observed for mutations
    var targetNode = document.getElementById('mapFrame_footer');

// Options for the observer (which mutations to observe)
    var config = { attributes: true, childList: true, subtree: true };

// Callback function to execute when mutations are observed
    var callback = function(mutationsList, observer) {
        for(var mutation of mutationsList) {
            // console.dir(mutation);
            if(mutation.type=="childList"){
                // console.dir(mutation);
                if(mutation.target.id=="mapFrame_footer"){
                  var new_target = mutation.target;
                      if(new_target.children!==null){
                          if(new_target.children[0]!==null){
                           var new_children = new_target.children[0];
                           if(new_children.children[0]!==null){
                               if(new_children.children[0].id=="mapFrame_footer_map"){
                                    new_children.children[0].classList.remove("dogis_map_default_map_open");
                                    new_children.children[0].classList.add("dogis_map_default_map_closed");
                               }
                           }
                           if(new_children.children[1]!==null){
                               if(new_children.children[1].id=="mapFrame_footer_map_panel"){
                                    new_children.children[1].classList.remove("dogis_map_default_panel_open");
                                    new_children.children[1].classList.add("dogis_map_default_panel_closed");
                               }
                           }
                           if(new_children.children[2]!==null){
                               if(new_children.children[2].id=="mapFrame_footer_map_panel_btn"){
                                    new_children.children[2].classList.remove("dogis_map_default_panel_btn_open");
                                    new_children.children[2].classList.add("dogis_map_default_panel_btn_closed");
                               }
                           }
                           observer.disconnect();
                          }
                      }

                }
            }
        }
    };

// Create an observer instance linked to the callback function
    var observer = new MutationObserver(callback);

// Start observing the target node for configured mutations
    observer.observe(targetNode, config);
//     var maps = document.querySelectorAll(".dg-mapframe");
//     if(maps!==null){
//         maps.forEach(function (item, index) {
//             var callback_loop = function(mutationsList, observer_loop) {
//                 for(var mutation of mutationsList) {
//                     if(mutation.type=="childList") {
//                         var new_target = mutation.target;
//                         if (new_target.children !== null) {
//                             if (new_target.children[0] !== null) {
//                                 if (new_target.children[0] !== null) {
//                                     var new_children = new_target.children[0];
//                                     if (new_children !== null) {
//                                         if (new_children.children !== null) {
//                                             if (new_children.children[0] !== null) {
//                                                 if (new_children.children[0].style !== null) {
//                                                     new_children.children[0].classList.remove("dogis_map_default_map_open");
//                                                     new_children.children[0].classList.add("dogis_map_default_map_closed");
//                                                 }
//                                             }
//                                             if (new_children.children[1] !== null) {
//                                                 if (new_children.children[1].style !== null) {
//                                                     new_children.children[1].classList.remove("dogis_map_default_panel_open");
//                                                     new_children.children[1].classList.add("dogis_map_default_panel_closed");
//                                                     // new_children.children[1].style.display = "none";
//                                                 }
//                                             }
//                                             if (new_children.children[2] !== null) {
//                                                 if (new_children.children[2].style !== null) {
//                                                     new_children.children[2].classList.remove("dogis_map_default_panel_btn_open");
//                                                     new_children.children[2].classList.add("dogis_map_default_panel_btn_closed");
//                                                     // new_children.children[2].style.display = "none";
//                                                 }
//
//                                             }
//                                         }
//                                     }
//                                 }
//                                 // observer.disconnect();
//                             }
//                         }
//                     }
//
//                 }
//             }
//
//             var observer_loop = new MutationObserver(callback_loop);
//
// // Start observing the target node for configured mutations
//             observer_loop.observe(item, config);
//         });
//     }

});