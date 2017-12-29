(function ($) {
  Drupal.behaviors.hitsaMobileIdStatus = {
    attach: function (context, settings) {
      $('body', context).once('iDStatusListener', function() {
        var checkStatus = setInterval(checkCurrStatus, 2000);
      });
      
      function checkCurrStatus() {
        if(typeof settings.hitsaMobileIdStatus !== "undefined") { // Check auth status
          $.get('login/status', function(data) {
            if(data.status === 'USER_AUTHENTICATED') {
              window.location.replace(window.location.origin);
            }
            if(data.status === 'none') {
              settings.hitsaMobileIdStatus = undefined;
            }
            
          });
        }
      }
    }
  };
})(jQuery);