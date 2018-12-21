<?php

/**
 * @file
 * External signup form template.
 */

$comment_field = $form['comment'];
$submit = $form['submit'];
$term_agreement = $form['terms_agreement'];

unset($form['comment']);
unset($form['submit']);
unset($form['terms_agreement']);
?>

<div class="narrow-wrapper">

  <!-- Begin - message -->
  <?php if (isset($form['#party_message'])): ?>
    <div class="alert alert-info">
      <?php print $form['#party_message']; ?>
    </div>
  <?php endif; ?>
  <!-- End - message -->

  <!-- Begin - upper text -->
  <div class="partial">
    <div class="partial__body">
      <?php print $form['#upper_text']; ?>
    </div>
  </div>
  <!-- End - upper text -->

  <!-- Begin - nemid login -->
  <div>
    <p>NemID block</p>
  </div>
  <!-- End - nemid login -->

  <!-- Begin - form -->
  <div class="partial">
    <div class="partial__body">
      <?php print drupal_render_children($form); ?>
    </div>
  </div>
  <!-- End - form -->

  <!-- Begin - bottom text -->
  <div class="partial">
    <div class="partial__body">
      <?php print $form['#bottom_text']; ?>
    </div>
  </div>
  <!-- End - bottom text -->

  <!-- Begin - comment -->
  <?php print drupal_render($comment_field); ?>
  <!-- End - comment -->

  <!-- Begin - agreement -->
  <?php print drupal_render($term_agreement); ?>
  <!-- End - agreement -->

  <!-- Begin - submit -->
  <?php print drupal_render($submit); ?>
  <!-- End - submit -->

</div>
