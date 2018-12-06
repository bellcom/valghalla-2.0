<?php
/**
 * @file
 * valghalla_volunteers_seat_matrix_roles_table.tpl.php
 */
?>

<div class="row">
  <div class="col-xs-12 col-md-7">
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

  </div>
</div>
