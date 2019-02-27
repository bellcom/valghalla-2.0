<?php

/**
 * @file
 * Overrides page template.
 */
?>
<!-- Begin - wrapper -->
<div class="layout__wrapper">

  <!-- Begin - sidr source provider -->
  <aside class="sidr-source-provider">

    <!-- Begin - navigation -->
    <nav class="slinky-menu" role="navigation">
      <?php print render($menu_slinky__main_menu); ?>
    </nav>
    <!-- End - navigation -->

  </aside>
  <!-- End - sidr source provider -->

  <!-- Begin - header static -->
  <header class="flexy-header flexy-header--static">
    <div class="flexy-header__row flexy-header__row--first hidden-xs">
      <div class="container-fluid">
        <div class="flexy-row">
          <div class="flexy-spacer"></div>

          <!-- Begin - navigation -->
          <nav class="flexy-header__secondary-navigation"
               role="navigation">
            <?php print render($flexy_list__secondary); ?>
          </nav>
          <!-- End - navigation -->

          <?php if (isset($election_party_switcher)): ?>
            <!-- Begin - election switcher -->
            <div class="flexy-header__election-switcher">
              <?php print render($election_party_switcher['content']); ?>
            </div>
            <!-- End - election switcher -->
          <?php endif; ?>

        </div>
      </div>
    </div>
    <div class="flexy-header__row flexy-header__row--second">
      <div class="container-fluid">
        <div class="flexy-row">

          <!-- Begin - logo -->
          <a href="<?php print $front_page; ?>" class="flexy-header__logo">
            <img src="<?php print $logo; ?>"
                 alt="<?php print t('@site_name logo', array('@site_name' => $site_name)); ?>"/>
          </a>
          <!-- End - logo -->

          <div class="flexy-spacer"></div>

          <!-- Begin - navigation -->
          <nav class="flexy-header__navigation__wrapper hidden-xs hidden-sm"
               role="navigation">

            <ul class="flexy-navigation">
              <?php if(isset($valghalla_participants['navigation'])): ?>
                <li class="flexy-navigation__item flexy-navigation__item--dropdown">
                  <?php print $valghalla_participants['navigation']; ?>
                </li>
              <?php endif; ?>

              <?php if(isset($valghalla_lists['navigation'])): ?>
                <li class="flexy-navigation__item flexy-navigation__item--dropdown flexy-navigation__item__dropdown--wide">
                  <?php print $valghalla_lists['navigation']; ?>
                </li>
              <?php endif; ?>

              <?php if(isset($valghalla_administration['navigation'])): ?>
                <li class="flexy-navigation__item flexy-navigation__item--dropdown">
                  <?php print $valghalla_administration['navigation']; ?>
                </li>
              <?php endif; ?>

              <?php if(isset($admin_valghalla['navigation'])): ?>
                <li class="flexy-navigation__item flexy-navigation__item--dropdown">
                  <?php print $admin_valghalla['navigation']; ?>
                </li>
              <?php endif; ?>

            </ul>
          </nav>
          <!-- End - navigation -->

          <!-- Begin - responsive toggle -->
          <button
            class="flexy-header__sidebar-toggle sidr-toggle--right visible-xs visible-sm">
            <span class="icon fa fa-bars"></span>
          </button>
          <!-- End - responsive toggle -->

        </div>
      </div>
    </div>
  </header>
  <!-- End - header static -->

  <!-- Begin - header sticky -->
  <header class="flexy-header flexy-header--sticky">
    <div class="flexy-header__row">
      <div class="container-fluid">
        <div class="flexy-row">

          <!-- Begin - logo -->
          <a href="<?php print $front_page; ?>" class="flexy-header__logo">
            <img src="<?php print $logo; ?>"
                 alt="<?php print t('@site_name logo', array('@site_name' => $site_name)); ?>"/>
          </a>
          <!-- End - logo -->

          <div class="flexy-spacer"></div>

          <!-- Begin - navigation -->
          <nav class="flexy-header__navigation__wrapper hidden-xs hidden-sm"
               role="navigation">

            <ul class="flexy-navigation">
              <?php if(isset($valghalla_participants['navigation'])): ?>
                <li class="flexy-navigation__item flexy-navigation__item--dropdown">
                  <?php print $valghalla_participants['navigation']; ?>
                </li>
              <?php endif; ?>

              <?php if(isset($valghalla_lists['navigation'])): ?>
                <li class="flexy-navigation__item flexy-navigation__item--dropdown flexy-navigation__item__dropdown--wide">
                  <?php print $valghalla_lists['navigation']; ?>
                </li>
              <?php endif; ?>

              <?php if(isset($valghalla_administration['navigation'])): ?>
                <li class="flexy-navigation__item flexy-navigation__item--dropdown">
                  <?php print $valghalla_administration['navigation']; ?>
                </li>
              <?php endif; ?>

              <?php if(isset($admin_valghalla['navigation'])): ?>
                <li class="flexy-navigation__item flexy-navigation__item--dropdown">
                  <?php print $admin_valghalla['navigation']; ?>
                </li>
              <?php endif; ?>

              <li class="flexy-navigation__item flexy-navigation__item--dropdown">
                <a href="#"><?php print t('Valghalla Manual'); ?></a>
                <ul class="flexy-navigation__item__dropdown-menu">
                  <li class="flexy-navigation__item__dropdown-menu__item"><a href="http://valghalla.dk/valghalla-manual" target="_blank"><?php print t('Valghalla Manual'); ?></a></li>
                  <li class="flexy-navigation__item__dropdown-menu__item"><a href="http://valghalla.dk/sites/default/files/valhalla-vejledning-til-valgsekretren.pdf" target="_blank"><?php print t('Vejledning til valgsekretær'); ?></a></li>
                  <li class="flexy-navigation__item__dropdown-menu__item"><a href="http://valghalla.dk/sites/default/files/kom-godt-i-gang-med-valhalla-partier.pdf" target="_blank"><?php print t('Kom godt i gang'); ?></a></li>
                </ul>
              </li>

            </ul>
          </nav>
          <!-- End - navigation -->

          <!-- Begin - responsive toggle -->
          <button
            class="flexy-header__sidebar-toggle sidr-toggle--right visible-xs visible-sm">
            <span class="icon fa fa-bars"></span>
          </button>
          <!-- End - responsive toggle -->

        </div>
      </div>
    </div>
  </header>
  <!-- End - header sticky -->

  <!-- Begin - content -->
  <main class="layout__content" role="main">
    <a id="main-content"></a>

    <section class="sectioned sectioned--page-header sectioned--small-inner-spacing">
      <div class="sectioned__inner">
        <div class="container-fluid">
          <div class="row">
            <div class="col-xs-12 col-md-6">

              <?php if (!empty($title)): ?>
                <h1><?php print $title; ?></h1>
              <?php endif; ?>

            </div>
            <div class="col-xs-12 col-md-6">
              <div class="hidden-xs text-right text-sm-left breadcrumb__wrapper">
                <?php print $breadcrumb; ?>
              </div>
            </div>
          </div>
        </div>
      </div>
    </section>

    <section class="sectioned">
      <div class="sectioned__inner">
        <div class="container-fluid">

          <?php if (!empty($page['help'])): ?>
            <?php print render($page['help']); ?>
          <?php endif; ?>

          <?php if (!empty($action_links)): ?>
            <ul class="action-links"><?php print render($action_links); ?></ul>
          <?php endif; ?>

          <?php if (!empty($messages)): ?>
            <!-- Begin - messages -->
            <?php print $messages; ?>
            <!-- End - messages -->
          <?php endif; ?>

          <?php if (!empty($tabs_primary)): ?>
            <!-- Begin - tabs primary -->
            <?php print render($tabs_primary); ?>
            <!-- End - tabs primary -->
          <?php endif; ?>

          <?php if (!empty($tabs_secondary)): ?>
            <!-- Begin - tabs secondary -->
            <?php print render($tabs_secondary); ?>
            <!-- End - tabs secondary -->
          <?php endif; ?>

          <?php if (!empty($page['sidebar__right'])): ?>
            <div class="row">
              <section class="col-sm-8">
                <?php print render($page['content']); ?>
              </section>

              <aside class="hidden-xs col-sm-4" role="complementary">
                <?php print render($page['sidebar__right']); ?>
              </aside>
            </div>

          <?php else: ?>
            <?php print render($page['content']); ?>
          <?php endif; ?>

        </div>
      </div>
    </section>
  </main>
  <!-- End - content -->

  <!-- Begin - footer -->
  <footer class="layout__footer">
    <div class="container-fluid">
      <div class="layout__footer__inner">
        <div class="text-center">
          &copy; <?php echo date('Y'); ?> <?php print t('OS2valghalla'); ?>
        </div>
      </div>
    </div>
  </footer>
  <!-- End - footer -->

</div>
<!-- End - wrapper -->
