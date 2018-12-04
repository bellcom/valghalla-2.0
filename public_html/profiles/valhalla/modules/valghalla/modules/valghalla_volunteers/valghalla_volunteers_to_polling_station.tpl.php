<?php
/**
 * @file
 * valghalla_volunteers_to_polling_station.tpl.php
 */
?>

<table class="table">
  <tr>
    <th>
    </th>
    <?php foreach ($existing_roles as $existing_role_nid => $existing_role): ?>
      <th>
        <?php print $existing_role; ?>
      </th>
    <?php endforeach; ?>
  </tr>

  <?php foreach ($parties_status as $party_status): ?>
    <?php if ($party_status['status']['total_count']['total'] !== 0): ?>
      <tr class="<?php print $party_status['party_status_label']; ?>">
        <td>
          <?php print $party_status['party_name']; ?>
        </td>
        <?php foreach ($party_status['status']['role_count'] as $role_nid => $role_count): ?>
          <?php if (array_key_exists($role_nid, $existing_roles)): ?>
            <td>
              <?php print $role_count['total']; ?>
            </td>
          <?php endif; ?>
        <?php endforeach; ?>
      </tr>
    <?php endif; ?>
  <?php endforeach; ?>
</table>

<?php if ($party_posts_to_fill): ?>
  <div id="volunteer-station-list">
    <?php foreach ($party_posts_to_fill as $party_tid => $party_posts): ?>
      <div>
        <h2>
          <?php print $party_posts['party_name'] . ' ' . $parties_status[$party_tid]['party_status_label']; ?>
        </h2>
        <?php foreach($parties_status[$party_tid]['status']['role_count'] as $role_count): ?>
          <?php if ($role_count['total'] !== 0) : ?>
            <div>
              <?php print $role_count['role_name'] . ': ' .$role_count['assigned'] . '/' . $role_count['total'] ?>
            </div>
          <?php endif; ?>
        <?php endforeach; ?>

        edit link: <?php print $party_posts['edit_url']; ?>

        <?php foreach ($party_posts['posts'] as $i => $post): ?>
          <dl class="clearfix" id="volunteer-station-list-item-<?php print $i ?>">
            <dt class="label-<?php print $post['role_title'] ?>"><?php print $post['role_title'] ?></dt>
            <dd data-post="<?php print $post['role_nid'] . $post['party_tid'] . $i; ?>">
              <div class="row">
                <div class="post col-xs-6"
                  <?php if (!isset($post['existing_post'])): ?> style="display:none;" <?php endif; ?> >

                  <?php if (isset($post['existing_post'])): ?>
                    <div>NAME: <?php print $post['existing_post']['name']; ?></div>
                    <div>reply link: <?php print $post['existing_post']['reply_link']; ?></div>
                    <div>RSVP: <?php
                      //0 => t('unknown')
                      //1 => t('yes')
                      //2 => t('no')
                      //3 => t('never')
                      print $post['existing_post']['rsvp']; ?>
                    </div>
                    <div>RSVP comment: <?php print $post['existing_post']['rsvp_comment']; ?></div>
                  <?php endif; ?>
                </div>

                <div class="col-xs-6"
                  <?php if (isset($post['existing_post'])): ?> style="display:none;" <?php endif; ?> >
                  <input type="text" class="form-control"
                         placeholder="<?php print t('Vælg en deltager'); ?>"/>
                </div>
                <?php if (user_access('add volunteer to station')) : ?>
                  <a data-role_nid="<?php print $post['role_nid']; ?>"
                     data-party_tid="<?php print $post['party_tid']; ?>"
                     data-pollingstation_nid="<?php print $pollingstation_nid; ?>"
                    <?php if (isset($post['existing_post'])): ?> style="display:none;"  <?php endif; ?>
                     class="btn btn-default btn-xs js-add-volunteer"><span
                      class="glyphicon glyphicon-plus"></span></a>
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
                    class="btn btn-default btn-xs"><span
                      class="glyphicon glyphicon-user"></span><span
                      class="glyphicon glyphicon-plus"></span></a>
                  <?php if (isset($post['existing_post'])): ?>
                    <a
                      href="/node/<?php print $post['existing_post']['nid'] ?>/edit?destination=<?php print (implode('/',
                        arg())) ?>" class="btn btn-default btn-xs edit">rediger <span
                        class="glyphicon glyphicon-user"></span></a>
                    <a data-fcid="<?php print $post['existing_post']['fcid'] ?>"
                       class="remove btn btn-danger btn-xs js-remove-volunteer">fjern <span
                        class="glyphicon glyphicon-minus"></span></a>
                  <?php endif; ?>
                <?php endif; ?>

              </div>
            </dd>
          </dl>
        <?php endforeach; ?>
      </div>

    <?php endforeach; ?>
  </div>
<?php endif; ?>
