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
<p> <?php print t('Vi har registreret følgende svar: '); ?> <strong> <?php print $rsvp_status; ?></strong>.</p>
<?php endif; ?>
<br />
<table>
  <tr>
    <td class="col-sm-3 col-md-3">
      <b><?php print t('Funktion:'); ?></b><br />
    </td>
    <td class="col-sm-9 col-md-9">
      <?php if (!empty($params['!position_description'])) : ?>
        <?php print $params['!position_description']; ?>
      <?php else: ?>
        <?php print $params['!position']; ?>
      <?php endif; ?>
    </td>
  </tr>
  <tr>
    <td class="col-sm-3 col-md-3">
      <b>Dato:</b><br />
    </td>
    <td class="col-sm-9 col-md-9">
      <?php print $params['!election_date']; ?><br />
    </td>
  </tr>

  <tr>
    <td class="col-sm-3 col-md-3">
      <b><?php print t('Tidspunkter:'); ?></b><br />
    </td>
    <td class="col-sm-9 col-md-9">
      <?php print $params['!time']; ?><br />
    </td>
  </tr>
  <tr>
    <br />
  </tr>
  <tr>
    <td class="col-sm-3 col-md-3">
      <b><?php print t('Valgsted:'); ?></b>
    </td>
    <td class="col-sm-9 col-md-9">
      <?php print $params['!polling_station']; ?><br />
    </td>
  </tr>
  <tr>
    <td class="col-sm-3 col-md-3">
    </td>
    <td class="col-sm-9 col-md-9">
      <?php print nl2br($params['!polling_station_address']); ?><br />
      <?php print $polling_station['address2']; ?>
    </td>
  </tr>
</table>
<?php print $post_script ?>
