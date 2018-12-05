<h2>
<!--  --><?php //print $form['#election']; ?>
</h2>

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
  unset($form['comment']);
  print drupal_render_children($form);
?>

<hr/>

<p>
  <?php
  print $form['#bottom_text'];
  ?>
</p>

<?php print drupal_render($comment_field); ?>

<?php ?>

