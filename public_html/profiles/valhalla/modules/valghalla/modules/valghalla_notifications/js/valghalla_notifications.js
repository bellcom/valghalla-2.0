(function ($) {
  "use strict";

  Drupal.behaviors.valghallaNotification = {
    attach: function (context, settings) {
      var $form = $('.valghalla-notifications-send').once();
      if (!$form.length) {
        return;
      }

      $form.find('select[name="template"]').change(function() {
        var $_this = $(this);
        if ($_this.val()) {
          location.href = '/valghalla/administration/sendto/' + $_this.val();
        }
      });

      $form.find('.js-show-volunteer-message').click(function(event){
        var id = $(this).attr('id');
        jQuery.get("/valghalla_notifications/ajax/view/"+id, function(data){
          $('.js-volunteer-preview-message').html(data);
        });
        return false;
      });
    }
  }
})(jQuery);