(function ($) {

    $(window).load(function () {
        var input = $('#edit-field-valghalla-mail-attachments-und-0-upload');
        input.addClass('hidden');

        $('#edit-field-valghalla-mail-attachments-und-0-upload-button').addClass('hidden');
        $(":file").filestyle({buttonText: "Vælg fil"});

        $(":file").filestyle({placeholder: "Ingen fil"});

    });

})(jQuery);

(function ($) {
    Drupal.behaviors.insertButton = {
        attach: function (context, settings) {
            var endpoint = '/valghalla/report';
            var $wrapper = $('.front .breadcrumb__wrapper');
            var $breadcrumb = $('.breadcrumb');

            // If we don't have a wrapper, stop what we are doing!
            if ($wrapper.length === 0) return;

            // Don't proceed if a breadcrumb is present. This will break styling.
            if ($breadcrumb.length > 0) return;

            // Generate PDF download link.
            var $button = $('<a/>')
                            .attr('href', endpoint)
                            .attr('target', '_blank')
                            .addClass('btn btn-secondary')
                            .html(Drupal.t('Generér PDF rapport'));

            // Inserts a button into the wrapper.
            $wrapper.html($button);
        }
    };
})(jQuery);
