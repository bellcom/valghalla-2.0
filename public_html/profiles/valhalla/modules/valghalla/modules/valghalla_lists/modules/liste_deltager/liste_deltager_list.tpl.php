<?php
/**
 * @file
 * liste_deltager_list.tpl.php
 */
?>
<div class="pull-right"><?php print format_date(time(), 'short'); ?></div>
<br />
<center>
  <h4><?php print $header['election'] ?></h4>
  <h4><?php print $header['date']; ?></h4>
</center>
<br /><br />

<h5>
<?php print $header['polling_station'];?>; <?php print $header['adress'];?>
<?php if (isset($header['schoolcode'])) : ?>
 - Skolekode <?php print $header['schoolcode'];?>
<?php endif; ?>
</h5>
<h5>
<?php print $header['contact_info']; ?>
</h5>
<?php print $table; ?>
