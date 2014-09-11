jQuery(document).ready(function($){
  $('.js-show-volunteer-mail').click(function(event){
    var id = $(this).attr('id');
    var message = $('.js-volunteer-mail-text').html();
    jQuery.get("/valghalla_mail/ajax/view/"+id, function(data){
      $('.js-volunteer-mail').html(data);
    });
  });
});
