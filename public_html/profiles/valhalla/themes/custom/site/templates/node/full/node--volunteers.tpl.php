<?php

/**
 * @file
 * Overrides node template for volunteers node type.
 */
?>
<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <span class="pull-right"><?php print t('Gemt:'); ?> <?php print valhalla_bs_last_editor($node) . ' ' . format_date($node->changed); ?></span>

  <br />
  <br />
  <table class="table">
    <tr>
      <td><?php print t('Adresse:'); ?></td>
      <td><?php print _theme_generate_address($node);?></td>
    </tr>
    <tr>
      <td><?php print t('Telefon:'); ?></td>
      <td><?php print _theme_generate_phone($node);?></td>
    </tr>
    <tr>
      <td><?php print t('Email:'); ?></td>
      <td><?php print _theme_generate_mail($node);?></td>
    </tr>
    <tr>
      <td><?php print t('Cpr:'); ?>Cpr:</td>
      <td><?php print _theme_generate_cpr($node);?></td>
    </tr>
    <tr>
      <td></td>
      <td><?php print _theme_generate_no_mail($node);?></td>
    </tr>
  </table>
  <br /><br />

  <?php print _theme_generate_election_info($node); ?>
</div>
