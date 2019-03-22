<?php
/**
 * available variables is
 *  $rsvp: the state of the rsvp, if empty this is undesided.
 *  $rsvp_status: the state of the rsvp, contains descriptive text
 *  $name: name of the volunteer
 *  $phone: the volunteers phone number
 *  $email: the volunteers email address
 *  $form: the rsvp form
 *  $is_internet_explorer: true/false - browser is IE11 and below.
 */
?>

<?php if ($is_internet_explorer): ?>
  <div class="alert alert-warning" role="alert">
    <strong><?php print t('Vent! Vi kan se at du benytter Internet Explorer.'); ?></strong>
    <br>
    <?php print t('Ved tilgang til denne side fra E-boks, oplever flere Internet Explorer brugere at formularen ikke virker.<br><br>Prøv at åbne denne side i en ny fane eller benyt en anden browser såsom Google Chrome eller Firefox.'); ?>
  </div>
<?php endif; ?>

<?php if (isset($name)): ?>
  <h2><?php print t('Hej %name', array('%name' => $name)) ?></h2>
<?php endif; ?>
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
      <strong><?php print t('Funktion:'); ?></strong><br />
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
      <strong>Dato:</strong><br />
    </td>
    <td class="col-sm-9 col-md-9">
      <?php print $params['!election_date']; ?><br />
    </td>
  </tr>

  <tr>
    <td class="col-sm-3 col-md-3">
      <strong><?php print t('Tidspunkter:'); ?></strong><br />
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
      <strong><?php print t('Valgsted:'); ?></strong>
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
    </td>
  </tr>
</table>
<?php print $post_script ?>
