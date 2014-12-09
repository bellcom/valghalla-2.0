console.log('hest');


(function ($) {
  Drupal.behaviors.exampleModule = {
    attach: function (context, settings) {

      var url = 'http://geo.oiorest.dk/postnumre.json';
      $.ajax({
        url: url,
        dataType: "jsonp",
        success: function (data) {
          var postnumre = [];
          $.each(data, function (i, post) {
            postnumre[i] = {
              value: post.nr,
              desc: post.navn
            };
          });

          $("[id$=-zipcode]").each(function() {
            $el = $(this);

            $el.autocomplete({
              source: postnumre,
              minLength: 1,
              select: function(event, ui) {
                var el_id = event.target.id.split('-')[2];
                $('[id$='+el_id+'-city]').val(ui.item.desc);
              },
              change: function(event,ui) {
                  if (ui.item === null) {
                    $el.val('');
                  }
              }
            }).data('ui-autocomplete')._renderItem = function( ul, item ) {
              console.log('hest');
                  return $( "<li>" )
                  .append( "<a>" + item.label + "<br>" + item.desc + "</a>" )
                  .appendTo( ul );
            };
          });
        }
      });

      $("[id$=-road]").focus(function () {
        var postnr = $(this).parent().parent().parent().parent().find('[id$=zipcode]').val();

        var $road = $(this);

      if (postnr.length !== 0) {
        var parametre = {};

        parametre.frapostnr = postnr;
        parametre.tilpostnr = postnr;

        var url = 'http://geo.oiorest.dk/vejnavne.json';
        $.ajax({
          url: url,
          dataType: "jsonp",
          data: parametre,

          success: function (vejnavne) {
            var data = [];
            $.each(vejnavne, function (i, vejnavn) {
              data[i] = vejnavn.navn;
            });
            $road.autocomplete({
              source: data,
              minLength: 1,
              change: function(event,ui) {
                if (ui.item === null) {
                  $road.val('');
                }
              }
            });
          }
        });
      }

      });

      $("[id$=-road-no]").focus(function () {
        var postnr = $(this).parent().parent().parent().parent().find('[id$=zipcode]').val();
        var road = $(this).parent().parent().parent().parent().find('[id$=-road]').val().trim();

        var $road_no = $(this);

        if (postnr.length !== 0) {
          var parametre = {};

          parametre.vejnavn = road;
          parametre.postnr = postnr;

          var url = 'http://geo.oiorest.dk/adresser.json';
          $.ajax({
            url: url,
            dataType: "jsonp",
            data: parametre,
            success: function (adresser) {
              var data = [];
              $.each(adresser, function (i, adresse) {
                data[i] = adresse.husnr;
              });
              $road_no.autocomplete({
                source: data,
                minLength: 1,
                change: function(event,ui) {
                  if (ui.item === null) {
                    $road_no.val('');
                  }
                }
              });
            }
          });
        }

      });

    }
  };
})(jQuery);
