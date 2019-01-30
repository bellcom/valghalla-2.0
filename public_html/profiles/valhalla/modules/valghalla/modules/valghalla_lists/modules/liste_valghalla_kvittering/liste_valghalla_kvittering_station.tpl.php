<div class="valgsteder-kvittering-list">
<?php if($polling_station): ?>
  <h3><?php
    $polling_station_nid = array_keys($polling_station);
    print "<a href='/volunteers/station/".$polling_station_nid[0] . "'>" . t('Kvittering for Di&aelig;t - ') . $polling_station[$polling_station_nid[0]]."</a>"; ?></h3>
  <?php if($volunteer_lists): ?>
  <table class="table table-striped">
    <thead>
        <tr>
          <th><?php print t('Rolle'); ?></th>
          <th><?php print t('Parti'); ?></th>
          <th><?php print t('Navn'); ?></th>
          <th><?php print t('KM'); ?></th>
          <th><?php print t('Timer'); ?></th>
          <th><?php print t('Di&aelig;t'); ?></th>
          <th>
          </th>
        </tr>
      </thead>
    <tbody class='table-striped'>
  <?php foreach($volunteer_lists as $volunteer): ?>
      <tr><td><?php print $volunteer['role']; ?></td>
          <td><?php print $volunteer['party']; ?></td>
          <td><a href="/node/<?php print $volunteer['nid']; ?>"><?php print $volunteer['name']; ?></a></td>
          <td><?php print $volunteer['km']; ?></td>
          <td><?php print $volunteer['hours']; ?></td>
          <td><?php print $volunteer['diaet']; ?></td>
          <td><a href='/field-collection/field-electioninfo/<?php print $volunteer['fc_id']; ?>/edit?destination=/valghalla_lists/kvittering/<?php print $polling_station_nid[0]; ?>'><?php print t('Redig&#233;r'); ?></a></td>
      </tr>
  <?php endforeach; ?>
    </tbody>
  </table>
  <?php endif;?>
<?php elseif (!$volunteer_lists && !$polling_station) : ?>
  <div><?php print t('Der er ikke valgt noget valg'); ?></div>
<?php endif;?>
</div>