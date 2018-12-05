var volunteer_info = volunteer_info || {};
var volunteer_tmp_element;
var valghalla_volunteers = valghalla_volunteers || [];

(function ($) {
  Drupal.behaviors.valghalla_volunteers = {
    attach: function (context, settings) {
      // Fetch info about post
      $('dd input').on('focus', function(){
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
        $('.modal').modal();
      });

      // Remove volunteer from post
      $('.js-remove-volunteer').on('click', function(){
        var fcid = $(this).attr('data-fcid');
        $parent = $(this).parent();
        $el = $parent.find('.volunteer');

        $parent.find('.edit').remove();
        $parent.find('.js-remove-volunteer').hide();

        $el.text('...');

        $.post('/ajax/volunteers/station/remove', {'fcid': fcid}, function(data){
          if(data.success){
            $parent.find('div').show();
            $parent.find('div.post').hide();
            $parent.find('.js-add-volunteer').show();
            Drupal.behaviors.valghalla_volunteers.populateTable();
          }
        });
      });

      // Select volunteer from modal
      $('.js-select-volunteer').on('click', function(event){
        $('.modal').modal('hide');
        $el = $('[data-post="'+volunteer_info.post_id+'"]');

        $el.find('.js-add-volunteer').hide();
        $el.find('.post').html('<p class="volunteer">...</p>');
        $el.find('div').hide();
        $el.find('div.post').show();

        volunteer_info.volunteer_nid = $(this).attr('data-volunteer_nid');

        $.post('/ajax/volunteers/station/add', volunteer_info, function(data){
          $el.find('div.post').html(data.html);
          $el.append('<a href="/node/'+volunteer_info.volunteer_nid+'/edit?destination=volunteers/station/'+volunteer_info.pollingstation_nid+'" class="btn btn-default btn-xs edit"><span class="glyphicon glyphicon-user"></span></a>');

          $el.append('<a data-fcid="'+data.fcid+'" class="remove btn btn-default btn-xs js-remove-volunteer"><span class="glyphicon glyphicon-minus"></span></a>');

          setTimeout(function(){
            Drupal.behaviors.valghalla_volunteers.populateTable();
          }, 500);
        });
      });

      Drupal.behaviors.valghalla_volunteers.populateTable();
      // <------------------- Add to polling station modal
    },
    autocompleteSelect: function( item ){
      $el = item.volunteer_item;
      $el.find('.js-add-volunteer').hide();

      volunteer_info.volunteer_nid = item.volunteer_nid;

      $el.find('div.post').html('<p class="volunteer">...</p>');
      $el.find('div').hide();
      $el.find('div.post').show();

      $.post('/ajax/volunteers/station/add', volunteer_info, function(data){
        $el.find('div.post').html(data.html);
        $el.find('div.post').show();
        $el.append('<a href="/node/'+volunteer_info.volunteer_nid+'/edit?destination=volunteers/station/'+volunteer_info.pollingstation_nid+'" class="btn btn-default btn-xs edit"><span class="glyphicon glyphicon-user"></span></a>');

        $el.append('<a data-fcid="'+data.fcid+'" class="remove btn btn-default btn-xs js-remove-volunteer"><span class="glyphicon glyphicon-minus"></span></a>');
        setTimeout(function(){
          Drupal.behaviors.valghalla_volunteers.populateTable();
        }, 500);
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
})(jQuery);
