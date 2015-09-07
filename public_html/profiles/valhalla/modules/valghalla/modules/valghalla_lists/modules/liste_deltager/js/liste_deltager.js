(function ($) {
  Drupal.behaviors.liste_deltager = {
    attach: function (context, settings) {

      $('.js-select-all').on('click', function(event) {
        var allIsSelected = true;
        var $parent = $(this).parent();
        var $inputs = $parent.find('input');
        var $options = $parent.find('option');

        $inputs.each(function(index, value) {
          var $input = $(this);

          if ( ! $input.is(':checked')) {
            allIsSelected = false;
          }
        });

        $options.each(function(index, value) {
          var $option = $(this);

          if ( ! $option.is(':selected')) {
            allIsSelected = false;
          }
        });

        // All is checked, so uncheck all
        if (allIsSelected) {
          $inputs.prop('checked', false);
          $options.removeAttr('selected');
        }
        // All or some needs to be checked - check all
        else {
          $inputs.prop('checked', true);
          $options.attr('selected', 'selected');
        }

        event.preventDefault();
      });
      //$('.js-select-all').click(function(e){
      //  $(this).parent().find('input').prop('checked', true);
      //  $(this).parent().find('option').attr('selected', 'selected');
      //  e.preventDefault();
      //});
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
