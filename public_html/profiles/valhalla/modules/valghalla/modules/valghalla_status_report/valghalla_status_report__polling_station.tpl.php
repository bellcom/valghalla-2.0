<?php if ($party_posts_to_fill): ?>
  <?php foreach ($party_posts_to_fill as $party_tid => $party_posts): ?>
    <?php if (count($party_posts['posts']) > 0): ?>

      <!-- Begin - heading -->
      <h3><?php print t('Parti') . ' ' . $party_posts['party_name']; ?>:</h3>
      <!-- End - heading -->

      <!-- Begin - body -->
      <table>
        <thead>
        <tr>
          <th><?=t('Status'); ?></th>
          <th><?=t('Rolle'); ?></th>
          <th><?=t('Navn'); ?></th>
        </tr>
        </thead>

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
                  <i><span class="text-muted"><?php print t('Denne plads er tom.'); ?></span></i>
                <?php else: ?>
                  <?php print $post['existing_post']['name']; ?>
                <?php endif; ?>
              </td>
              <!-- End - name -->

            </tr>
          <?php endforeach; ?>
        </tbody>
      </table>
      <!-- End - body -->

    <?php endif; ?>
  <?php endforeach; ?>
<?php endif; ?>
