<?php
/**
 * @file
 * valghalla_volunteers_seat_matrix_roles_table.tpl.php
 */
?>
<div class="sticky">
  <div class="table-responsive">
    <table class="table table--overview-of-parties">
      <tr>
        <th></th>

        <?php foreach ($existing_roles as $existing_role_nid => $existing_role): ?>
          <th><?php print $existing_role; ?></th>
        <?php endforeach; ?>
      </tr>

      <?php foreach ($parties_status as $party_status): ?>
        <?php if ($party_status['status']['total_count']['assigned'] !== 0): ?>
          <tr class="<?php print $party_status['party_status_label']; ?>">
            <td>
              <a href="#" data-scroll-to="#party_<?=strtolower($party_status['party_name']); ?>">
                <strong><?php print $party_status['party_name']; ?></strong>
              </a>
            </td>

            <?php foreach ($existing_roles as $existing_role_nid => $existing_role): ?>
              <td>
                <?php if ($party_status['status']['role_count'][$existing_role_nid]['assigned'] !== 0): ?>
                  <?php print $party_status['status']['role_count'][$existing_role_nid]['total'] . '/' . $party_status['status']['role_count'][$existing_role_nid]['assigned'] ?>
                <?php else: ?>
                  -
                <?php endif; ?>
              </td>
            <?php endforeach; ?>

          </tr>
        <?php endif; ?>
      <?php endforeach; ?>
    </table>
  </div>
</div>
