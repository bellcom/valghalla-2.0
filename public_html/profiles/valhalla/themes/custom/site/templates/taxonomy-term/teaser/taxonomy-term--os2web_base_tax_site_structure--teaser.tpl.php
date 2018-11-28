<?php if ($view_mode == 'teaser'): ?>
  <!-- Begin - teaser -->
  <div id="taxonomy-term-<?php print $term->tid; ?>" class="<?php print $classes; ?>">

    <?php if (isset($content['field_os2web_base_field_logo'])): ?>

      <!-- Begin - logo -->
      <div class="entity-teaser__logo">
        <?php print render($content['field_os2web_base_field_logo']); ?>
      </div>
      <!-- End - logo -->

    <?php endif; ?>

    <!-- Begin - heading -->
    <div class="entity-teaser__heading">
      <h2 class="entity-teaser__heading__title heading-h5">
        <a href="<?php print $term_url; ?>"><?php print $term_name; ?></a>
      </h2>
    </div>
    <!-- End - heading -->

    <div class="entity-teaser__body">

      <!-- Begin - links -->
      <div class="entity-teaser__links">
        <?php if (isset($content['field_os2web_base_field_related'])): ?>
          <?php print render($content['field_os2web_base_field_related']); ?>
        <?php endif; ?>
      </div>
      <!-- End - links -->

    </div>
  </div>
  <!-- End - teaser -->

<?php endif; ?>
