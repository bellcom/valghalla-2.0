var valhalla_blocks = {
  loadOverview : function(delta){
    jQuery.get("/valhalla_blocks/ajax/view/"+delta, function(data){
      jQuery('#valhalla_block-'+delta).html(data);
      jQuery('#valhalla_block-'+delta).removeClass('spinner-loading');
    });
  }
};
