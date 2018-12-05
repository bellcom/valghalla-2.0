<p>
  <?php
  print $form['#upper_text'];
  ?>
</p>

<div style="border: 1px solid black">
  <p>...</p>

  <p>NemID block</p>

  <p>...</p>
</div>

<?php
$comment_field = $form['comment'];
$submit = $form['submit'];
$term_agreement = $form['terms_agreement'];
unset($form['comment']);
unset($form['submit']);
unset($form['terms_agreement']);

print drupal_render_children($form);
?>

<hr/>

<p>
  <?php
  print $form['#bottom_text'];
  ?>
</p>

<?php print drupal_render($comment_field); ?>
<?php print drupal_render($term_agreement); ?>
<?php print drupal_render($submit); ?>

<?php ?>
