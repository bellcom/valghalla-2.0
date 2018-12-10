<?php
/**
 * @file
 * valghalla_volunteers_to_polling_station.tpl.php
 */
?>

<?php if ($party_posts_to_fill): ?>
  <?php foreach ($party_posts_to_fill as $party_tid => $party_posts): ?>
    <div class="boxy boxy--<?=$parties_status[$party_tid]['party_status_label']; ?>" id="party_<?=strtolower($party_posts['party_name']); ?>">

      <!-- Begin - heading -->
      <div class="boxy__heading">
        <div class="flexy-row">
          <h2 class="boxy__heading__title"><?php print $party_posts['party_name']; ?></h2>

          <?php foreach($parties_status[$party_tid]['status']['role_count'] as $role_count): ?>
            <?php if ($role_count['assigned'] !== 0) : ?>
              <div class="boxy__heading__meta-data">
                <?php print $role_count['role_name'] . ': ' . $role_count['total'] . '/' . $role_count['assigned']?>
              </div>
            <?php endif; ?>
          <?php endforeach; ?>

          <div class="flexy-spacer"></div>

          <?php if ($party_posts['party_subscribe_url']): ?>
            <button type="button"
                    class="btn btn-default btn-xs"
                    data-toggle="tooltip"
                    data-placement="top"
                    title="<?= t('Link til ekstern tilmelding'); ?>"
                    data-external-url="<?php print $party_posts['party_subscribe_url'] ?>"
            >
              <span class="glyphicon glyphicon-link"></span>
            </button>
          <?php endif; ?>

          <a href="<?php print $party_posts['edit_url']; ?>" class="btn btn-default btn-xs" data-toggle="tooltip" data-placement="top" title="<?=t('Redigér'); ?>">
            <span class="glyphicon glyphicon-edit"></span>
          </a>

        </div>
      </div>
      <!-- End - heading -->

      <!-- Begin - body -->
      <div class="boxy__body">

        <?php if (count($party_posts['posts']) > 0): ?>
          <?php foreach ($party_posts['posts'] as $i => $post): ?>
            <div
              class="entity-list <?php print (isset($post['existing_post'])) ? 'entity-list--volunteer' : 'entity-list--volunteer-form'; ?>"
              id="volunteer-station-list-item-<?php print $i ?>"
              data-post="<?php print $post['role_nid'] . $post['party_tid'] . $i; ?>"
            >

              <!-- Begin - data -->
                <div class="entity-list__data">
                  <div class="entity-list__data__item entity-list__data__item--status">
                    <?php
                    //0 => t('unknown') - yellow
                    //1 => t('yes') - green
                    //2 => t('no') - danger
                    //3 => t('never') - danger
                    ?>
                    <?php if ($post['existing_post']['rsvp'] == '0'): ?>
                      <span
                        data-toggle="tooltip"
                        data-placement="top"
                        title="<?= t('Har endnu ikke svaret'); ?>"
                        class="status-circle status-circle--warning"
                      ></span>
                    <?php endif; ?>

                    <?php if ($post['existing_post']['rsvp'] == '1'): ?>
                      <span
                        data-toggle="tooltip"
                        data-placement="top"
                        title="<?= t('Har svaret ja'); ?>"
                        class="status-circle status-circle--success"
                      ></span>
                    <?php endif; ?>

                    <?php if ($post['existing_post']['rsvp'] == '2'): ?>
                      <span
                        data-toggle="tooltip"
                        data-placement="top"
                        title="<?= t('Har svaret nej'); ?>"
                        class="status-circle status-circle--danger"
                      ></span>
                    <?php endif; ?>

                    <?php if ($post['existing_post']['rsvp'] == '3'): ?>
                      <span
                        data-toggle="tooltip"
                        data-placement="top"
                        title="<?= t('Vil ikke kontaktes igen'); ?>"
                        class="status-circle status-circle--danger"
                      ></span>
                    <?php endif; ?>
                  </div>

                  <div class="entity-list__data__item entity-list__data__item--role">
                    <strong><?php print $post['role_title'] ?></strong>
                  </div>

                  <?php if (isset($post['existing_post'])): ?>
                    <div class="entity-list__data__item entity-list__data__item--name">
                      <?php print $post['existing_post']['name']; ?>
                    </div>
                  <?php endif; ?>

                </div>
              <!-- End - data -->

              <!-- Begin - form -->
              <?php if (! isset($post['existing_post'])): ?>
              <div class="entity-list__form">
                <input type="text" class="form-control input-sm" placeholder="<?=t('Vælg en deltager'); ?>"/>
              </div>
              <?php endif; ?>
              <!-- End - form -->

              <!-- Begin - controls -->
              <div class="entity-list__controls">

                <!-- Begin - response -->
                <?php if ($post['existing_post']['rsvp_comment']): ?>
                  <span
                    data-toggle="tooltip"
                    data-placement="left"
                    title="<?= t('Kommentar'); ?>"
                  >
                    <button
                      class="btn btn-default btn-xs"
                      data-toggle="popover"
                      data-placement="top"
                      data-content="<?php print $post['existing_post']['rsvp_comment']; ?>"
                      title="<?= t('Kommentar'); ?>"
                    >
                      <span class="glyphicon glyphicon-comment"></span>
                    </button>
                  </span>
                <?php endif; ?>
                <!-- End - response -->

                <!-- Begin - external seat link -->
                <?php if ($post['post_subscribe_url']): ?>
                  <button
                    type="button"
                    class="btn btn-default btn-xs"
                    data-toggle="tooltip"
                    data-placement="top"
                    title="<?= t('Link til ekstern tilmelding'); ?>"
                    data-external-url="<?=$post['post_subscribe_url']; ?>"
                  >
                    <span class="glyphicon glyphicon-link"></span>
                  </button>
                <?php endif; ?>
                <!-- End - external seat link -->

                <?php if (user_access('add volunteer to station')) : ?>

                  <!-- Begin - add existing -->
                  <a data-role_nid="<?php print $post['role_nid']; ?>"
                     data-party_tid="<?php print $post['party_tid']; ?>"
                     data-pollingstation_nid="<?php print $pollingstation_nid; ?>"
                     data-toggle="tooltip"
                     data-placement="top"
                     title="<?= t('Tilføj eksisterende deltager'); ?>"
                    <?php if (isset($post['existing_post'])): ?> style="display:none;"  <?php endif; ?>
                     class="btn btn-default btn-xs js-add-volunteer"
                  >
                    <span class="glyphicon glyphicon-plus"></span>
                  </a>
                  <!-- End - add existing -->

                  <!-- Begin - add new -->
                  <?php
                  $add_url = url('valghalla/deltagere/tilfoej',
                    [
                      'query' => [
                        'role_nid'           => $post['role_nid'],
                        'party_tid'          => $post['party_tid'],
                        'pollingstation_nid' => $pollingstation_nid,
                        'destination'        => current_path(),
                      ],
                    ]);
                  ?>
                  <a
                    href="<?php print $add_url; ?>" <?php if (isset($post['existing_post'])): ?> style="display:none;"  <?php endif; ?>
                    class="btn btn-default btn-xs"
                    data-toggle="tooltip"
                    data-placement="top"
                    title="<?= t('Opret en ny deltager'); ?>"
                  >
                    <span class="glyphicon glyphicon-user"></span>
                    <span class="glyphicon glyphicon-plus"></span>
                  </a>
                  <!-- End - add new -->

                  <?php if (isset($post['existing_post'])): ?>

                    <!-- Begin - reply -->
                    <?php if ($post['existing_post']['reply_link']): ?>
                      <a
                        href="<?=$post['existing_post']['reply_link']; ?>"
                        class="btn btn-default btn-xs"
                        data-toggle="tooltip"
                        data-placement="top"
                        title="<?= t('Besvar for denne deltager'); ?>"
                      >
                        <span class="glyphicon glyphicon-edit"></span>
                      </a>
                    <?php endif; ?>
                    <!-- End - reply -->

                    <!-- Begin - edit -->
                    <a href="/node/<?php print $post['existing_post']['nid'] ?>/edit?destination=<?php print (implode('/', arg())) ?>"
                       class="btn btn-default btn-xs edit"
                       data-toggle="tooltip"
                       data-placement="top"
                       title="<?= t('Redigér deltager'); ?>"
                    >
                      <span class="glyphicon glyphicon-user"></span>
                    </a>
                    <!-- End - edit -->

                    <!-- Begin - remove -->
                    <a data-fcid="<?php print $post['existing_post']['fcid'] ?>"
                       data-toggle="tooltip"
                       data-placement="top"
                       title="<?= t('Fjern deltager'); ?>"
                       class="remove btn btn-danger btn-xs js-remove-volunteer"
                    >
                      <span class="glyphicon glyphicon-minus"></span>
                    </a>
                    <!-- End - remove -->

                  <?php endif; ?>

                <?php endif; ?>

              </div>
              <!-- End - controls -->

            </div>
          <?php endforeach; ?>
        <?php else: ?>
          <?=t('Dette parti har ingen tildelte pladser.'); ?>
        <?php endif; ?>

      </div>
      <!-- End - body -->

    </div>

  <?php endforeach; ?>
<?php endif; ?>

<!-- Begin - external link -->
<div class="modal modal-clipboard fade" tabindex="-1" role="dialog" id="modal-clipboard">
  <div class="modal-dialog" role="document">
    <div class="modal-content">
      <div class="modal-header">
        <button type="button" class="close" data-dismiss="modal" aria-label="<?=t('Luk vindue'); ?>">
          <span aria-hidden="true">&times;</span>
        </button>

        <h4 class="modal-title"><?=t('Link til ekstern tilmelding');?></h4>
      </div>

      <div class="modal-body">

        <!-- Begin - input -->
        <div class="input-group">

          <!-- Begin - copy -->
          <span class="input-group-btn">
            <button class="btn btn-default"
                    data-toggle="tooltip"
                    data-placement="top"
                    title="<?=t('Kopiér link til udklipsholderen'); ?>"
                    type="button"
                    data-clipboard-target="#clipboard_target"
            >
              <span class="glyphicon glyphicon-paste"></span>
            </button>
          </span>
          <!-- End - copy -->

          <!-- Begin - input -->
          <input type="text" class="form-control modal-clipboard__input" id="clipboard_target" />
          <!-- End - input -->

          <!-- Begin - open -->
          <span class="input-group-btn">
            <a href="#"
               class="btn btn-default modal-clipboard__external-link"
               data-toggle="tooltip"
               data-placement="top"
               title="<?= t('Åben link i nyt vindue'); ?>"
               target="_blank"
            >
              <span class="glyphicon glyphicon-link"></span>
            </a>
          </span>
          <!-- End - open -->

        </div>
        <!-- End - input -->

      </div>

      <div class="modal-footer">
        <button type="button" class="btn btn-default" data-dismiss="modal"><?=t('Luk vindue'); ?></button>
      </div>
    </div>
  </div>
</div>
<!-- End - external link -->
