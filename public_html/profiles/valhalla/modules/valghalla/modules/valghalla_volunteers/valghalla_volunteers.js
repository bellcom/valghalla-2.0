var volunteer_info = volunteer_info || {};
var volunteer_tmp_element;
var valghalla_volunteers = valghalla_volunteers || [];

(function ($) {
  Drupal.behaviors.valghalla_volunteers = {
    attach: function (context, settings) {
      // Fetch info about post
      $('.entity-list--volunteer-form input').on('focus', function(){
        var $parent = $(this).parent().parent();
        var $el = $parent.find('.js-add-volunteer');
        volunteer_info.post_id = $parent.attr('data-post');
        volunteer_info.pollingstation_nid = $el.attr('data-pollingstation_nid');
        volunteer_info.role_nid = $el.attr('data-role_nid');
        volunteer_info.party_tid = $el.attr('data-party_tid');
        volunteer_tmp_element = $parent;

        $(this).autocomplete({
          minLength: 0,
          source: valghalla_volunteers,
          focus: function( event, ui ) {
            return false;
          },
          select: function( event, ui ) {
            ui.item.volunteer_item = volunteer_tmp_element;
            Drupal.behaviors.valghalla_volunteers.autocompleteSelect(ui.item);
            return false;
          }
        })
        .data( "ui-autocomplete" )._renderItem = function(ul, item){
          return $( "<li>" )
            .append("<a data-volunteer_nid='"+ item.volunteer_nid +"'>" + item.label + "<br>" + item.desc + "</a>")
            .appendTo( ul );
        };
      });

      // Add to polling station modal: ---------------------->
      $('.js-add-volunteer').on('click', function(){
        var $parent = $(this).parent();
        var $el = $(this);

        volunteer_info.post_id = $parent.attr('data-post');
        volunteer_info.pollingstation_nid = $el.attr('data-pollingstation_nid');
        volunteer_info.role_nid = $el.attr('data-role_nid');
        volunteer_info.party_tid = $el.attr('data-party_tid');
        $('.js-add-volunteer-modal').modal();
      });

      // Remove volunteer from post
      $('.js-remove-volunteer').on('click', function(){
        var fcid = $(this).attr('data-fcid');
        $parent = $(this).parent();

        // Show a modal.
        swal({
              title: Drupal.t('Er du sikker?'),
              text: Drupal.t('Dette vil fjerne deltageren fra pladsen. Denne handling kan ikke fortrydes.'),
              type: 'warning',
              showCancelButton: true,
              confirmButtonClass: 'btn-danger',
              cancelButtonText: Drupal.t('Annullér'),
              confirmButtonText: Drupal.t('Ja, fjern deltageren'),
              closeOnConfirm: false
            },
            function () {
              $.post('/ajax/volunteers/station/remove', {'fcid': fcid}, function (data) {

                // Show a modal.
                swal({
                  title: Drupal.t('Deltageren blev fjernet fra pladsen!'),
                  text: Drupal.t('Siden genindlæses...'),
                  type: 'success',
                  showCancelButton: false,
                  showConfirmButton: false,
                });

                // Refresh after 2.5 sec.
                setTimeout(function () {
                  location.reload();
                }, 2500);
              });
            });



        // $el = $parent.find('.volunteer');

        // $parent.find('.edit').remove();
        // $parent.find('.js-remove-volunteer').hide();

        // $el.text('...');

        // $.post('/ajax/volunteers/station/remove', {'fcid': fcid}, function(data){
        //   if(data.success){
        //
        //     // Show a modal.
        //     swal({
        //       title: Drupal.t('Siden genindlæses...'),
        //       type: 'success',
        //       showCancelButton: false,
        //       showConfirmButton: false,
        //     });
        //
        //     // Refresh after 2.5 sec.
        //     setTimeout(function() {
        //       location.reload();
        //     }, 100);
        //
        //
        //
        //     $parent.find('div').show();
        //     $parent.find('div.post').hide();
        //     $parent.find('.js-add-volunteer').show();
        //     Drupal.behaviors.valghalla_volunteers.populateTable();
        //   }
        // });
      });

      // Select volunteer from modal
      $('.modal').on('click', '.js-select-volunteer', function(event) {
        volunteer_info.volunteer_nid = $(this).attr('data-volunteer_nid');

        // $el = $('[data-post="'+volunteer_info.post_id+'"]');

        // $el.find('.js-add-volunteer').hide();
        // $el.find('.post').html('<p class="volunteer">...</p>');
        // $el.find('div').hide();
        // $el.find('div.post').show();


        $.post('/ajax/volunteers/station/add', volunteer_info, function(data){
          // $el.find('div.post').html(data.html);
          // $el.append('<a href="/node/'+volunteer_info.volunteer_nid+'/edit?destination=volunteers/station/'+volunteer_info.pollingstation_nid+'" class="btn btn-default btn-xs edit"><span class="glyphicon glyphicon-user"></span></a>');

          // $el.append('<a data-fcid="'+data.fcid+'" class="remove btn btn-default btn-xs js-remove-volunteer"><span class="glyphicon glyphicon-minus"></span></a>');

          // setTimeout(function(){
          //   Drupal.behaviors.valghalla_volunteers.populateTable();
          // }, 500);

          // Hide modal.
          $('.modal').modal('hide');

          // When modal is hidden.
          $('.modal').on('hidden.bs.modal', function () {

            // Show a modal.
            swal({
              title: Drupal.t('Deltageren blev tilføjet til pladsen!'),
              text: Drupal.t('Siden genindlæses...'),
              type: 'success',
              showCancelButton: false,
              showConfirmButton: false,
            });

            // Refresh after 2.5 sec.
            setTimeout(function() {
              location.reload();
            }, 2500);
          })
        });
      });

      Drupal.behaviors.valghalla_volunteers.populateTable();
      // <------------------- Add to polling station modal
    },
    autocompleteSelect: function( item ){
      // $form = item.volunteer_item;
      // $parent = $form.parent();
      // $data = $parent.find('.entity-list__data');
      // $controls = $parent.find('.entity-list__controls');
      volunteer_info.volunteer_nid = item.volunteer_nid;

      // Hide.
      // $controls.find('.js-add-volunteer').hide();

      // Add volunteer.
      $.post('/ajax/volunteers/station/add', volunteer_info, function(data) {

        // Show a modal.
        swal({
          title: Drupal.t('Deltageren blev tilføjet til pladsen!'),
          text: Drupal.t('Siden genindlæses...'),
          type: 'success',
          showCancelButton: false,
          showConfirmButton: false,
        });

        // Refresh after 2.5 sec.
        setTimeout(function() {
          location.reload();
        }, 2500);

        // var $editButton = '<a href="/node/'+volunteer_info.volunteer_nid+'/edit?destination=volunteers/station/'+volunteer_info.pollingstation_nid+'" class="btn btn-default btn-xs edit"><span class="glyphicon glyphicon-user"></span></a>';
        // var $removeButton = '<a data-fcid="'+data.fcid+'" class="remove btn btn-default btn-xs js-remove-volunteer"><span class="glyphicon glyphicon-minus"></span></a>';
        //
        // // Switch between form display and volunteer display.
        // $parent
        //     .removeClass('entity-list--volunteer-form')
        //     .addClass('entity-list--volunteer');
        //
        // // Hide form.
        // $form.addClass('hidden');
        //
        // // Hide all controls.
        // $controls.find('.btn').addClass('hidden');
        //
        // // Show data.
        // $data.html(data.html);
        // $data.removeClass('hidden');
        //
        // // Add buttons.
        // $controls.append($editButton);
        // $controls.append($removeButton);
        //
        // setTimeout(function(){
        //   Drupal.behaviors.valghalla_volunteers.populateTable();
        // }, 500);
      });
    },
    populateTable: function(){
      $.get('/ajax/volunteers/station/getvolunteers', function(data){

        valghalla_volunteers = [];
        for (var key in data){

          valghalla_volunteers.push({
            label: "(" + data[key].volunteer_party + ") " + data[key].volunteer_name,
            value: "(" + data[key].volunteer_party + ")" + data[key].volunteer_name,
            volunteer_nid: data[key].volunteer_nid,
            desc: ""
          });
        }

        $(document).trigger('volunteersLoaded');
      });
    },
    unsetVolunteer: function(nid){
      var data = Drupal.settings.valghalla_volunteers.volunteers;
      for (var key in data){
        if(data[key].volunteer_nid === nid){
          Drupal.settings.valghalla_volunteers.volunteers.splice(key, 1);
        }
      }
    }
  };
  Drupal.behaviors.valghallaMoveEditPollingStationButton = {
    attach: function (context, settings) {
      var $button = $('.edit-polling-station');
      var $wrapper = $('.page-volunteers-station .breadcrumb__wrapper');
      var $breadcrumb = $('.breadcrumb');

      // If we don't have a wrapper, stop what we are doing!
      if ($wrapper.length === 0) return;

      // Don't proceed if a breadcrumb is present. This will break styling.
      if ($breadcrumb.length > 0) return;

      // Inserts a button into the wrapper.
      $wrapper.html($button.removeClass('hidden'));
    },
  };
})(jQuery);
