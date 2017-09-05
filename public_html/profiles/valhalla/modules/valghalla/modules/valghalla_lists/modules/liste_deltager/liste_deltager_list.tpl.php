<?php
/**
 * @file
 * liste_deltager_list.tpl.php
 */
?>
<div class="pull-right"><?php print format_date(time(), 'short'); ?></div>
<br />
<center>
  <h4><?php print $header['election']; ?></h4>
  <h4><?php print $header['date']; ?></h4>
</center>
<br /><br />

<?php foreach($table as $polling_station => $markup): ?>
  <h5>
    <?php if (isset($header[$polling_station]['polling_station'])): ?>
      <?php print $header[$polling_station]['polling_station'];?>; <?php print $header[$polling_station]['adress'];?>
    <?php endif; ?>
    <?php if (isset($header[$polling_station]['schoolcode'])) : ?>
      <?php print t('- Skolekode '); ?> <?php print $header[$polling_station]['schoolcode'];?>
    <?php endif; ?>
  </h5>
  <h5>
  <?php print $header[$polling_station]['contact_info']; ?>
  </h5>
  <?php print $table[$polling_station]; ?>
  <div style="page-break-after: always;"></div>
<?php endforeach; ?>
