<?php
/**
 * @file
 * Valghalla notification preview message template.
 */
?>
<?php if ($subject) : ?>
<div class = 'valghalla-notification-subject'>
  <?php print t('Emne :') . $subject;?>
</div>
<?php endif; ?>
<?php if ($body) : ?>
<div class= 'valghalla-notification-body'>
  <?php print $body; ?>
</div>
<?php endif; ?>
