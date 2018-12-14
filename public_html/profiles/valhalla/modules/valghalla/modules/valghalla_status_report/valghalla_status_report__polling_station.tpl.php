<?php if ($party_posts_to_fill): ?>
  <?php foreach ($party_posts_to_fill as $party_tid => $party_posts): ?>

    <!-- Begin - heading -->
    <h3><?php print $party_posts['party_name']; ?></h3>

    <?php if ($party_posts['party_subscribe_url']): ?>
      <a href="<?php print $party_posts['party_subscribe_url'] ?>">
        <?=t('Eksternt link'); ?>
      </a>
    <?php endif; ?>
    <!-- End - heading -->

    <!-- Begin - body -->
    <table>
      <thead>
      <tr>
        <th><?=t('Status'); ?></th>
        <th><?=t('Rolle'); ?></th>
        <th><?=t('Navn'); ?></th>
        <th></th>
      </tr>
      </thead>

      <?php if (count($party_posts['posts']) > 0): ?>
        <tbody>
          <?php foreach ($party_posts['posts'] as $i => $post): ?>
            <tr>

              <!-- Begin - status -->
              <?php
              //0 => t('unknown') - yellow
              //1 => t('yes') - green
              //2 => t('no') - danger
              //3 => t('never') - danger
              ?>
              <?php if ($post['existing_post']['rsvp'] == '0'): ?>
                <td class="warning"> </td>
              <?php elseif ($post['existing_post']['rsvp'] == '1'): ?>
                <td class="success"> </td>
              <?php elseif ($post['existing_post']['rsvp'] == '2'): ?>
                <td class="danger"> </td>
              <?php elseif ($post['existing_post']['rsvp'] == '3'): ?>
                <td class="danger"> </td>
              <?php else: ?>
                <td> </td>
              <?php endif; ?>
              <!-- End - status -->

              <!-- Begin - role -->
              <td>
                &nbsp;

                <strong><?php print $post['role_title'] ?></strong>
              </td>
              <!-- End - role -->

              <!-- Begin - name -->
              <td>
                &nbsp;&nbsp;

                <?php if (! isset($post['existing_post'])): ?>
                  <i><?=t('Denne plads er tom.'); ?></i>
                <?php else: ?>
                  <?php print $post['existing_post']['name']; ?>
                <?php endif; ?>
              </td>
              <!-- End - name -->

              <!-- Begin - controls -->
              <td>
                &nbsp;
                &nbsp;
                <!-- Begin - external seat link -->
                <?php if (isset($post['post_subscribe_url'])): ?>
                  <a href="<?=$post['post_subscribe_url']; ?>">
                    <?= t('Ekstern tilmelding'); ?>
                  </a>
                <?php endif; ?>
                <!-- End - external seat link -->

              </td>
              <!-- End - controls -->

            </tr>
          <?php endforeach; ?>
        </tbody>
      <?php else: ?>
        <tbody>
        <tr>
          <td colspan="4">
            <?=t('Dette parti har ingen tildelte pladser.'); ?>
          </td>
        </tr>
        </tbody>
      <?php endif; ?>

    </table>
    <!-- End - body -->

  <?php endforeach; ?>
<?php endif; ?>
