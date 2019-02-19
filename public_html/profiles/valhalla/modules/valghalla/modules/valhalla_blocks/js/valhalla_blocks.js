(function ($) {
  Drupal.behaviors.loadOverview = {
    attach: function (context, settings) {
      var deltas = ['party_status', 'party_constituency_status'];

      for (var int in deltas) {
        var value = deltas[int];

        lazyLoadContent(value, settings);
      }
    }
  };
})(jQuery);

function _removeButton() {
  var $wrapper = jQuery('.front .breadcrumb__wrapper');
  var $button = $wrapper.find('.js-generate-pdf-report');

  $button.remove();
}

function _addButton() {
  var endpoint = '/valghalla/report';
  var $wrapper = jQuery('.front .breadcrumb__wrapper');
  var $breadcrumb = jQuery('.breadcrumb');

  // If we don't have a wrapper, stop what we are doing!
  if ($wrapper.length === 0) {
    return;
  }

  // Don't proceed if a breadcrumb is present. This will break styling.
  if ($breadcrumb.length > 0) {
    return;
  }

  // Generate PDF download link.
  var $button = jQuery('<a/>')
      .attr('href', endpoint)
      .attr('target', '_blank')
      .addClass('btn btn-secondary js-generate-pdf-report')
      .html('Generér PDF rapport');

  // Inserts a button into the wrapper.
  $wrapper.html($button);
}

function lazyLoadContent(delta, settings) {

  // Remove button.
  _removeButton();

  jQuery.get("/valhalla_blocks/ajax/view/" + delta, function (data) {
    jQuery('#valhalla_block-' + delta + ' .progress').css({visibility: 'hidden'});
    jQuery('#valhalla_block-' + delta + ' .content').html(data);

    // If nothing is returned, don't re-add the button.
    if (data === 'Der er ikke valgt noget valg' || data === 'Der er ingen valgsteder på dette valg') {
      return;
    }

    // Add button.
    if (settings.electionActive) {
      _addButton();
    }
  });
}
