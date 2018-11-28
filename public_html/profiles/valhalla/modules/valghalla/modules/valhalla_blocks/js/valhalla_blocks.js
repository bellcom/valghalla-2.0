(function ($) {
    Drupal.behaviors.loadOverview = {
        attach: function (context, settings) {
            var deltas = ['party_status', 'party_constituency_status'];

            for (var int in deltas) {
                var value = deltas[int];

                lazyLoadContent(value);
            }
        }
    };
})(jQuery);

function lazyLoadContent(delta) {
    jQuery.get("/valhalla_blocks/ajax/view/" + delta, function (data) {
        jQuery('#valhalla_block-' + delta + ' .progress').css({visibility: 'hidden'});
        jQuery('#valhalla_block-' + delta + ' .content').html(data);
    });
}
