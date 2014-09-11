/*
 * @copyright bellcom open source aps
 * @author ulrik nielsen <un@bellcom.dk>
 */

jQuery(function(){
  jQuery('.page-admin-valghalla .confirm-rsvp-reset').click(function(event) {
    event.preventDefault();
    if (confirm("Er du sikker ? Alle data vil blive slettet.")) {
      document.location.href = this.href;
      return true;
    }
  });
});
