<?php
/**
 * @file valghalla_mail_rsvp_reminder.inc
 *
 * @copyright 2012 OS2 - Offentligt Digitaliseringsfællesskab.
 * See README.md at https://github.com/os2web/valghalla_mail
 */

/**
 * Valghalla RSVP Reminder
 *
 * this notifies volunteers with no rsvp status 14 an 7 days before an election
 *
 * @param int $last_run_ts unix timestamp of last cron run
 * @return void
 */
function valghalla_mail_rsvp_reminder($last_run_ts) {
  // only run once a day
  if (date('Ymd') <= date('Ymd', $last_run_ts)) {
    $check_data = date('d-m-Y', $last_run_ts);
    watchdog('Valghalla', 'Cron for Valghalla mails blev ikke kørt da den allerede er kørt i dag: %last_run', array('%last_run' => $check_data), WATCHDOG_NOTICE);
    return;
  }

  // find active election
  $nids = db_select('field_data_field_election_status', 'es')
      ->fields('es', array('entity_id'))
      ->condition('es.bundle', 'election')
      ->condition('es.field_election_status_value', 1)
      ->execute()
      ->fetchAll(PDO::FETCH_COLUMN);

  if (empty($nids)) {
    watchdog('Valghalla', 'Der blev ikke fundet noget aktict valg - aktiver dit valg. ', WATCHDOG_NOTICE);
    return;
  }

  foreach($nids as $nid){
    $election = node_load($nid);
    $election_date = field_get_items('node', $election, 'field_date');
    list($election_date, $time) = preg_split("|T|", $election_date[0]['value']);
    $today_date = strtotime(date('Y-m-d'));
    $election_date1 = strtotime($election_date);
    $days_to_election = floor(($election_date1 - $today_date) / 86400);

    // check dates
    $notification_days_arr = variable_get('valghalla_rsvp_reminder_days');
    $notification_days = explode(',', variable_get('valghalla_rsvp_reminder_days'));
    if (!in_array($days_to_election, $notification_days)) {
      watchdog('Valghalla', 'Mail job blev ikke kørt idet idag ikke er nogen rykker dag. Valg: %election_date Dage til valget: %todays Rykkerdage: %godays', array('%todays' => $days_to_election, '%godays' => $notification_days_arr, '%election_date' => $election_date), WATCHDOG_NOTICE);
      return;
    }

    // helpers
    $election->days_to_election = $days_to_election;
    $election_date = field_get_items('node', $election, 'field_date');
    $election->election_date = date('j/m Y', strtotime($election_date[0]['value']));

    $volunteer_query = new EntityFieldQuery();
    $volunteer_query->entityCondition('entity_type', 'field_collection_item')
                    ->entityCondition('bundle', 'field_electioninfo')
                    ->fieldCondition('field_election', 'target_id', $election->nid);

    $volunteer_result = $volunteer_query->execute();

    if(!empty($volunteer_result)){
      foreach(reset($volunteer_result) as $value){
        if($volunteer_fc = entity_load_single('field_collection_item', $value->item_id)){
          // tth: Check if the user deserves a reminder
          if($field = field_get_items('field_collection_item', $volunteer_fc, 'field_rsvp')){
            if($field[0]['value'] == 0){
              valghalla_mail_rsvp_reminder_send($election, $volunteer_fc);
            }
          }
        }
      }
    }
  }
}

/**
 * this function prepares the email and triggers the mail_send() hook
 *
 * @global stdClass $language
 * @param stdClass $election
 * @param stdClass $volunteer
 */
function valghalla_mail_rsvp_reminder_send($election, $volunteer_fc) {
  global $language;
  module_load_include('inc', 'valhalla_volunteers', 'valhalla_volunteers');
  $volunteer_node = $volunteer_fc->hostEntity();
  $email = field_get_items('node', $volunteer_node, 'field_email');

  $to = $email[0]['email'];
  $from = variable_get('site_mail', 'admin@example.com');
  $tokens = _valghalla_helper_get_token_values($volunteer_fc);

  // Fetch the mail for the volunteers role
  if($mail = valghalla_mail_get_mail($election->nid, $tokens['!position_nid'], 'reminder')){
    $params = array_merge(array('tokens' => $tokens), $mail);
  }

  $send = TRUE;
  $result = drupal_mail('valghalla_mail', 'mail', $to, $language, $params, $from, $send);
}
