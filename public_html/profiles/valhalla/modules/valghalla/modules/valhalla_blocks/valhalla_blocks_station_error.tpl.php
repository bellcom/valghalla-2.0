<div id="valhalla-station-error-list" style="border:  4px solid red">
<?php if (!empty($extra)): ?>
  <div class="valhalla-station-error-list-wrapper">
    <table>
        <tr>
            <thead>
            <th>
                <?php print t('Fejl i valgsted'); ?>
            </th>
            </thead>
        </tr>
        <tbody>
        <?php foreach($extra as $i): ?>
            <tr>
                <td>
                    <a href="/volunteers/station/<?php print $i['station_id']; ?>"><?php print $i['polling_station_name']; ?></a>
                </td>
            </tr>
        <?php endforeach; ?>
      </tbody>
    </table>
  </div>
<?php endif;?>
</div>

