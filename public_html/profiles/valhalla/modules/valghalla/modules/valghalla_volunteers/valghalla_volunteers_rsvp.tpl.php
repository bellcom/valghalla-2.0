<?php
/**
 * available variables is
 *  $rsvp: the state of the rsvp, if empty this is undesided.
 *  $rsvp_status: the state of the rsvp, contains descriptive text
 *  $name: name of the volunteer
 *  $phone: the volunteers phone number
 *  $email: the volunteers email adderss
 *  $form: the rsvp form
 */
?>

<h2><?php print t('Hej %name', array('%name' => $name)) ?></h2>

<div>
  <p><?php print t('Her kan du tilkendegive om du ønsker at udfylde den post vi har tiltænkt dig i det kommende valg.') ?></p>
</div>
<?php if($rsvp): ?>
<p> Vi har registreret følgende svar: <strong> <?php print $rsvp_status; ?></strong>.</p>
<?php endif; ?>
<table>
  <tr>
    <td>
      <b>Funktion:</b><br />
      <?php print $params['!position']; ?><br />
      <b>Dato:</b><br />
      <?php print $params['!election_date']; ?><br />
    </td>
    <td>
      <b>Valgsted:</b><br />
      <?php print $params['!polling_station']; ?><br />
      <?php print nl2br($params['!polling_station_address']); ?><br />
      <?php print $polling_station['address2']; ?>
    </td>
  </tr>
</table>
<?php print $post_script ?>
