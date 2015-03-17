<?php
/**
 * @file
 * This file holds page callbacks for valghalla_pages.
 */

/**
 * Page callback for admin overview page.
 */
function valghalla_pages_admin_valghalla() {
  $out = '
    <a class="btn btn-success" href="/node/add/election?destination=valghalla/administration/valg">' . t('+ Tilføj valg') . '</a>
    <div><h3>' . t('Liste over valg') . '</h3></div>';

  // Fetch all elecitons.
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
        ->entityCondition('bundle', 'election')
        ->propertyCondition('status', 1)
        ->fieldOrderBy('field_date', 'value', 'DESC');
  $result = $query->execute();

  $elections = node_load_multiple(array_keys($result['node']));

  foreach ($elections as $election) {
    $title = $election->title;

    $date = '';
    if ($date_field = field_get_items('node', $election, 'field_date')) {
      $date = date('d-m-y', strtotime($date_field[0]['value']));
    }

    $status = 'ikke aktiv';
    if ($status_field = field_get_items('node', $election, 'field_election_status')) {
      if ($status_field[0]['value'] == 1) {
        $status = 'aktiv';
      }
    }

    $mails = '';
    if ($mails_send_field = field_get_items('node', $election, 'field_election_mails_send')) {
      if ($mails_send_field[0]['value'] == 1) {
        $mails = 'sendt';
      }
    }

    $type = '';
    if ($election_type_field = field_get_items('node', $election, 'field_election_type')) {
      $type_array = array();
      foreach ($election_type_field as $delta) {
        $type_term = taxonomy_term_load($delta['tid']);
        $type_array[] = $type_term->name;
      }
      $type = implode(', ', $type_array);
    }
    $actions = array();
    $actions[] = '<a href="/node/' . $election->nid . '/edit?destination=' . current_path() . '">rediger</a>';

    if ($status !== 'aktiv') {
      $actions[] = l('aktiver', 'valghalla/election/start/' . $election->nid);
    }
    else {
      $actions[] = l('deaktiver', 'valghalla/election/stop/' . $election->nid);

      if ($mails !== 'sendt') {
        $actions[] = l('send invitationer', 'valghalla/administration/sendinvitation/' . $election->nid);
      }
    }

    $actions[] = '<a href="/valghalla/administration/valg/mails/' . $election->nid . '">E-mail skabeloner</a>';

    $action_links = implode(' | ', $actions);

    $rows[] = array($title, $date, $status, $mails, $type, $action_links);
  }

  $header = array(
    'Titel',
    'Dato',
    'Status',
    'Invitationer sendt',
    'Type',
    'Valgmuligheder',
  );

  $elections_table = theme_table(array(
    'header' => $header,
    'rows' => $rows,
    'attributes' => array('class' => 'table'),
  ));

  // Fetch all old elecitons.
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
        ->entityCondition('bundle', 'election')
        ->propertyCondition('status', 0)
        ->fieldOrderBy('field_date', 'value', 'DESC');
  $result = $query->execute();

  $elections = node_load_multiple(array_keys($result['node']));
  $rows = array();

  foreach ($elections as $election) {
    $title = $election->title;

    $actions = array();
    $actions[] = '<a href="/node/' . $election->nid . '/edit?destination=' . current_path() . '">rediger</a>';

    $action_links = implode(' | ', $actions);
    $rows[] = array($title, $action_links);
  }

  $header = array('Titel', 'Valgmuligheder');

  $old_elections_table = '<h3>Arkiverede valg</h3>';
  $old_elections_table .= theme_table(array(
    'header' => $header,
    'rows' => $rows,
    'attributes' => array('class' => 'table'),
  ));

  $extra = '
    <div>
    </div>
    ';
  return $out . $elections_table . $old_elections_table . $extra;
}
