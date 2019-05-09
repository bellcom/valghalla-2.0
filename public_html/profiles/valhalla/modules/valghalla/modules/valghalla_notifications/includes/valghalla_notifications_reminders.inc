<?php

/**
 * @file
 * Valghalla notifications rsvp reminder.
 */

/**
 * Valghalla RSVP Reminder.
 *
 * This notifies volunteers with no rsvp status 14 an 7 days before an election.
 *
 * @param int $last_run_ts
 *   Run unix timestamp of last cron run.
 */
function valghalla_notifications_rsvp_reminder($last_run_ts) {
  // Only run once a day.
  if (date('Ymd') <= date('Ymd', $last_run_ts)) {
    return;
  }

  // Find active election.
  $nids = db_select('field_data_field_election_status', 'es')
    ->fields('es', array('entity_id'))
    ->condition('es.bundle', 'election')
    ->condition('es.field_election_status_value', 1)
    ->execute()
    ->fetchAll(PDO::FETCH_COLUMN);

  if (empty($nids)) {
    watchdog('valghalla_notification', 'RSVP reminder: Der blev ikke fundet noget aktict valg - aktiver dit valg. ', array(), WATCHDOG_NOTICE);
    return;
  }

  foreach ($nids as $nid) {
    $election = node_load($nid);
    $election_date = field_get_items('node', $election, 'field_date');
    list($election_date, $time) = preg_split("|T|", $election_date[0]['value']);
    $today_date = strtotime(date('Y-m-d'));
    $election_date1 = strtotime($election_date);
    $days_to_election = floor(($election_date1 - $today_date) / 86400);

    // Check dates.
    $notification_days_arr = variable_get('valghalla_notifications_rsvp_reminder_days');
    $notification_days = explode(',', variable_get('valghalla_notifications_rsvp_reminder_days'));
    $notification_days = array_map('trim', $notification_days);
    if (!in_array($days_to_election, $notification_days)) {
      watchdog('valghalla_notification', 'RSVP reminder blev ikke kørt idet idag ikke er nogen rykker dag. Valg: %election_date Dage til valget: %todays Rykkerdage: %godays', array(
        '%todays' => $days_to_election,
        '%godays' => $notification_days_arr,
        '%election_date' => $election_date,
      ), WATCHDOG_NOTICE
      );
      continue;
    }

    $volunteer_query = new EntityFieldQuery();
    $volunteer_query->entityCondition('entity_type', 'field_collection_item')
      ->entityCondition('bundle', 'field_electioninfo')
      ->propertyCondition('archived', 0)
      ->fieldCondition('field_election', 'target_id', $election->nid);

    $volunteer_result = $volunteer_query->execute();

    if (!empty($volunteer_result)) {
      foreach (reset($volunteer_result) as $value) {
        if ($volunteer_fc = entity_load_single('field_collection_item', $value->item_id)) {
          // Check if the user deserves a reminder.
          if ($field = field_get_items('field_collection_item', $volunteer_fc, 'field_rsvp')) {
            if ($field[0]['value'] == 0) {
              $tokens = _valghalla_helper_get_token_values($volunteer_fc);
              valghalla_notifications_notify_volunteer($nid, $tokens['!position_nid'], $volunteer_fc, 'reminder');
            }
          }
        }
      }
    }
  }
}

/**
 * Valghalla toGo Reminder.
 *
 * This notifies volunteers with toGo reminder in specific amount
 * of days before an election.
 *
 * @param int $last_run_ts
 *   Run unix timestamp of last cron run.
 */
function valghalla_notifications_togo_reminder($last_run_ts) {
  // Only run once a day.
  if (date('Ymd') <= date('Ymd', $last_run_ts)) {
    return;
  }

  // Find active election.
  $nids = db_select('field_data_field_election_status', 'es')
    ->fields('es', array('entity_id'))
    ->condition('es.bundle', 'election')
    ->condition('es.field_election_status_value', 1)
    ->execute()
    ->fetchAll(PDO::FETCH_COLUMN);

  if (empty($nids)) {
    watchdog('valghalla_notification', 'ToGO påmindelse: Der blev ikke fundet noget aktict valg - aktiver dit valg. ', array(), WATCHDOG_NOTICE);
    return;
  }

  foreach ($nids as $nid) {
    $election = node_load($nid);
    $election_date = field_get_items('node', $election, 'field_date');
    list($election_date, $time) = preg_split("|T|", $election_date[0]['value']);
    $today_date = strtotime(date('Y-m-d'));
    $election_date1 = strtotime($election_date);
    $days_to_election = floor(($election_date1 - $today_date) / 86400);

    // Check dates.
    $togo_notification_days = variable_get('valghalla_notifications_reminder_togo_days');
    if (intval($togo_notification_days) != $days_to_election) {
      watchdog('valghalla_notification', 'ToGO påmindelse blev ikke kørt idet idag ikke er nogen rykker dag. Valg: %election_date Dage til valget: %todays Rykkerdage: %godays', array(
        '%todays' => $days_to_election,
        '%godays' => $togo_notification_days,
        '%election_date' => $election_date,
      ), WATCHDOG_NOTICE
      );
      continue;
    }

    $volunteer_query = new EntityFieldQuery();
    $volunteer_query->entityCondition('entity_type', 'field_collection_item')
      ->entityCondition('bundle', 'field_electioninfo')
      ->propertyCondition('archived', 0)
      ->fieldCondition('field_election', 'target_id', $election->nid);

    $volunteer_result = $volunteer_query->execute();

    if (!empty($volunteer_result)) {
      foreach (reset($volunteer_result) as $value) {
        if ($volunteer_fc = entity_load_single('field_collection_item', $value->item_id)) {
          if ($field = field_get_items('field_collection_item', $volunteer_fc, 'field_rsvp')) {
            // Send notification only for volunteers with field_rsvp="Ja" value.
            if ($field[0]['value'] == 1) {
              $tokens = _valghalla_helper_get_token_values($volunteer_fc);
              valghalla_notifications_notify_volunteer($nid, $tokens['!position_nid'], $volunteer_fc, 'reminder_togo');
            }
          }
        }
      }
    }
  }
}
