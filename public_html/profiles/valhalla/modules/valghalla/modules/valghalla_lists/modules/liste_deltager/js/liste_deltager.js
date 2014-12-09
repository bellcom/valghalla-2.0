(function ($) {
  Drupal.behaviors.liste_deltager = {
    attach: function (context, settings) {
      if ($('.table').length === 0) {
        $('#liste-deltager-form input[type="checkbox"]').prop('checked', 1);
      }
      else {
        $('table').tablesorter({
          theme: 'bootstrap',
          headerTemplate: '{content} {icon}',
          widgets : [ 'zebra', 'columns', 'uitheme' ]
        });
      }
    }
  };
})(jQuery);
