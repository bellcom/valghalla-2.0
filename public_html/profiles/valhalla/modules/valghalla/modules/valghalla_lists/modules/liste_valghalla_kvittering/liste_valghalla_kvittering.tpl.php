<div class="valgsteder-kvittering-list">
<?php if($lists): ?>
  <?php foreach($lists as $nid => $constituency): ?>
  <h3><?php print t('Valgkreds: ') . "<a href='/node/$nid'>".$constituency['c_title']."</a>"; ?></h3>
  <ul>
    <?php foreach($constituency['nodes'] as $key => $number): ?>
      <li>
        <?php print "<a href='/valghalla_lists/kvittering/$key'>".$number['title']."</a>"; ?>
      </li>
    <?php endforeach; ?>
  </ul>
  <?php endforeach; ?>
  <?php elseif (!$user_restrict_stations): ?>
  <div></div>
  <?php else: ?>
  <div>
  <?php print t('Der er ikke valgt noget valg'); ?>
  </div>
<?php endif;?>
</div>

