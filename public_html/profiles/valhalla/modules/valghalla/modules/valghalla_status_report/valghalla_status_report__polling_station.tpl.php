<?php if ($party_posts_to_fill): ?>
  <?php foreach ($party_posts_to_fill as $party_tid => $party_posts): ?>
    <?php if (count($party_posts['posts']) > 0): ?>

      <!-- Begin - heading -->
      <h3><?php print t('Parti') . ' ' . $party_posts['party_name']; ?> <?php if($election_is_active): ?>(<a href="<?php print $party_posts['party_subscribe_url']; ?>">link</a>)<?php endif; ?></h3>
      <!-- End - heading -->

      <!-- Begin - body -->
      <table>
        <thead>
        <tr>
          <?php if($election_is_active): ?>
            <th><?php print t('Status'); ?></th>
          <?php endif; ?>
          <th><?php print t('Rolle'); ?></th>
          <th><?php print t('Navn'); ?></th>
        </tr>
        </thead>

        <tbody>
          <?php foreach ($party_posts['posts'] as $i => $post): ?>
            <tr>

              <!-- Begin - status -->
              <?php
              // 0 => t('unknown') - yellow.
              // 1 => t('yes') - green.
              // 2 => t('no') - danger.
              // 3 => t('never') - danger.
              ?>
              <?php if($election_is_active): ?>
                <?php if ($post['existing_post']['rsvp'] == '0'): ?>
                  <td class="warning"> </td>
                <?php elseif ($post['existing_post']['rsvp'] == '1'): ?>
                  <td class="success"> </td>
                <?php elseif ($post['existing_post']['rsvp'] == '2'): ?>
                  <td class="danger"> </td>
                <?php elseif ($post['existing_post']['rsvp'] == '3'): ?>
                  <td class="danger"> </td>
                <?php elseif (!isset($post['existing_post'])): ?>
                  <td><a href="<?php print $post['post_subscribe_url']; ?>">Link</a> </td>
                <?php else: ?>
                  <td> </td>
                <?php endif; ?>
              <?php endif; ?>
              <!-- End - status -->

              <!-- Begin - role -->
              <td>
                &nbsp;
                <?php print $post['role_description'] ?>
              </td>
              <!-- End - role -->

              <!-- Begin - name -->
              <td>
                &nbsp;&nbsp;
                <?php if (!isset($post['existing_post'])): ?>
                  <i><span class="text-muted"><?php print t('Denne plads er tom.'); ?></span></i>
                <?php else: ?>
                  <?php if ($post['existing_post']['rsvp'] == '2' || $post['existing_post']['rsvp'] == '3'): ?>
                    <strike><?php print $post['existing_post']['name']; ?></strike>
                  <?php else: ?>
                    <?php print $post['existing_post']['name']; ?>
                  <?php endif; ?>
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
