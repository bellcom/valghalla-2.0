(function ($) {
  Drupal.behaviors.liste_deltager = {
    attach: function (context, settings) {
      $('.js-select-all').click(function(e){
        $(this).parent().find('input').prop('checked', true);
        $(this).parent().find('option').attr('selected','selected');
        e.preventDefault();
      });
      if ($('.table').length === 0) {
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
