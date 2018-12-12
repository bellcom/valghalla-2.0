<?php

/**
 * helper function, this one wraps a name in rsvp settings
 *
 * @global stdClass $language
 * @param stdClass $node
 * @return string
 */
function _valghalla_helper_wrap_name($node, $container = 'p', $fcid = null) {
  global $language;

  $rsvp_map = array(
    0 => t('Har endnu ikke bekræftet'),
    1 => t('Har bekræftet sin deltagelse'),
    2 => t('Har meldt afbud til dette valg'),
    3 => t('Ønsker at blive slettet'),
  );
  $rsvp_class_map = array(
    0 => t('unknown'),
    1 => t('yes'),
    2 => t('no'),
    3 => t('never'),
  );

  $party = '';
  if ($party_field = field_get_items('node', $node, 'field_party')) {
    $party = taxonomy_term_load($party_field[0]['tid']);
  }

  $rsvp_markup = "";

  $fc = entity_load_single('field_collection_item', $fcid);
  if (is_object($fc)) {
    $rsvp_message = field_get_items('field_collection_item', $fc, 'field_rsvp_comment');
    $rsvp = field_get_items('field_collection_item', $fc, 'field_rsvp');
  }

  if ($rsvp_message) {
    if (!empty($rsvp_message[0]['value'])) {
      $rsvp_markup = '<button class="btn btn-default btn-xs">';
      $rsvp_markup .=   '<span class="rsvp-message-icon fa fa-envelope-o" data-toggle="popover" data-placement="top" data-title="' . t('Deltagerens svar') . '" data-content="' . $rsvp_message[0]['value'] . '"></span>';
      $rsvp_markup .= '</button>';
    }
  }

  $rsvp = empty($rsvp[0]['value']) ? 0 : $rsvp[0]['value'];

  $reply_link = '';

  if (user_access('add volunteer to station') && ($rsvp == 0 || variable_get('valghalla_volunteers_always_show_rsvp_link', FALSE))) {
    $field_token = field_get_items('field_collection_item', $fc, 'field_token');
    $reply_link = '<a class="btn btn-default btn-xs" data-toggle="tooltip" data-placement="top" title="Svar for denne tilforordnede" class="reply edit" href="/volunteers/rsvp/'  . $field_token[0]['value'] . '"><span class="glyphicon glyphicon-comment"></span></a>';
  }

  $valid = '';
  if ($external_signup_field = field_get_items('node', $node, 'field_external_signup')
      && !($cpr_valid_date_field = field_get_items('node', $node, 'field_cpr_valid_date'))) {
    $valid = 'notvalidated';
  }

  $display = '(' . $party->name . ') ' . $node->title . ' (' . $rsvp_map[$rsvp] . ')' . $rsvp_markup . $reply_link;
  return '<' . $container . ' class="volunteer ' . $valid . ' ' . $rsvp_class_map[$rsvp] . '">' . $display . '</' . $container . '>';
}

/**
 * Validate the login token.
 *
 * If valid, the session variable valghalla_volunteer will contain the related
 * node.
 */
function _valghalla_volunteers_validate_key($token) {
  $volunteer_query = new EntityFieldQuery();
  $volunteer_query->entityCondition('entity_type', 'field_collection_item')
    ->entityCondition('bundle', 'field_electioninfo')
    ->propertyCondition('archived', 0)
    ->fieldCondition('field_token', 'value', $token);
  $result = $volunteer_query->execute();

  $fcid = key(array_shift($result));

  $fc = entity_load_single('field_collection_item', $fcid);

  return $fc;
}

/**
 * Get email from its token.
 */
function _valghalla_helper_get_email_by_token($token) {
  global $language;
  static $emails = array();

  if (isset($emails[$token])) {
    return $emails[$token];
  }

  $entity_id = db_select('field_data_field_token', 't')
      ->fields('t', array('entity_id'))
      ->condition('entity_type', 'node', '=')
      ->condition('bundle', 'email', '=')
      ->condition('field_token_value', $token, '=')
      ->execute()
      ->fetchField();

  $emails[$token] = FALSE;
  if ($entity_id) {
    $email = node_load($entity_id);
    $emails[$token] = new stdClass();
    $emails[$token]->subject = $email->title;
    $emails[$token]->body_plain = $email->body[$language->language][0]['value'];
    $emails[$token]->body_html = $email->body[$language->language][0]['safe_value'];
  }

  return $emails[$token];
}

/**
 * retrive volunteer node by cpr number
 *
 * @param string $cpr
 * @return mixed stdClass on success otherwise false
 */
function _valghalla_helper_get_volunteer_by_cpr($cpr) {
  $entity_id = db_select('field_data_field_cpr_number', 't')
      ->fields('t', array('entity_id'))
      ->condition('entity_type', 'node', '=')
      ->condition('bundle', 'volunteers', '=')
      ->condition('field_cpr_number_value', $cpr, '=')
      ->execute()
      ->fetchField();

  if ($entity_id) {
    return node_load($entity_id);
  }

  return FALSE;
}

/**
 * Thomas Thune Hansen <tth@bellcom.dk>
 *
 * Helper function to check if the post if unused on the chosen polling
 * station
 *
 * @param
 *  polling station nid
 *  role nid
 *  party tid
 * @return
 *  bool
 */
function _valghalla_helper_validate_polling_post($polling_station_id, $role_id, $party_id){
  $polling_station = node_load($polling_station_id);
  $posts_array = valghalla_volunteers_to_polling_station_roles($polling_station, $party_id, FALSE);

  $role_array = _valghalla_helper_get_role_array();

  // If existing in the posts_array is empty, then all posts are vacant
  if(!is_array($posts_array['existing'])){
    $free_posts = $posts_array['posts_to_fill'];
  }
  else {
    // Get the remaining free posts
    $free_posts = array_diff_assoc($posts_array['posts_to_fill'], $posts_array['existing']);
  }
  // Check if one of the free posts has the correct role id.
  foreach($free_posts as $post){
    if($role_array[strtolower($post['role_title'])] == $role_id){
      return TRUE;
    }
  }
  return FALSE;
}

function _valghalla_helper_get_role_array(){
  // tth: Get all roles, query all content from bundle 'roles'
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'roles');
  $results = $query->execute();
  $nodes = node_load_multiple(array_keys($results['node']));

  // tth: Create an array for lookup
  $role_array = array();
  foreach($nodes as $key => $value){
    $role_array[strtolower($value->title)] = $key;
  }

  return $role_array;
}

/**
 * returns a keyed array of roles
 */
function _valghalla_helper_get_roles() {
  trigger_error('Function ' . __FUNCTION__ . ' is deprecated, use odin_get_roles instead', E_USER_DEPRECATED);
  return odin_get_roles();
}

function _valghalla_helper_get_parties() {
  trigger_error('Function ' . __FUNCTION__ . ' is deprecated, use odin_get_parties instead', E_USER_DEPRECATED);
  return odin_get_parties();
}

/**
 * Get posts to fill on polling station for party.
 *
 */
function _valghalla_helper_get_posts_to_fill($polling_station, $party_tid){
  $posts_to_fill = array();

  $roles = odin_get_roles();

  // Loop over roles and fetch count for each role on polling station.
  foreach ($roles as $role_nid => $role_title){
    $role_count = _valghalla_helper_get_roles_count(array($polling_station->nid), $role_nid, $party_tid);
    // Due to the structure that is expected in the recieving end. We need to to this.
    while ($role_count) {
      $posts_to_fill[] = array('role_title' => $role_title, 'role_nid' => $role_nid);
      $role_count--;
    }
  }

  return $posts_to_fill;
}

/**
 * Get a count of roles on polling station for party.
 *
 */
function _valghalla_helper_get_roles_count($polling_station_nids, $role_nid, $party_tid = NULL){
  $election_nid = ($_SESSION['election_nid']) ? $_SESSION['election_nid'] : variable_get('valghalla_signup_election_nid', FALSE);

  if ($election_nid) {
    $query = db_select('field_data_field_role_n' . $role_nid, 'vr');
    $query->innerJoin('field_data_field_ppsp_party', 'vp', 'vp.entity_id=vr.entity_id');
    $query->innerJoin('field_data_field_ppsp_polling_station', 'vps', 'vps.entity_id=vr.entity_id');
    $query->innerJoin('field_data_field_volunteers_pr_pol_st_party', 'vpp', 'vpp.field_volunteers_pr_pol_st_party_value=vr.entity_id');
    $query->addExpression('SUM(vr.field_role_n' . $role_nid . '_number_vo)');
    if ($party_tid) {
      $query->condition('vp.field_ppsp_party_tid', $party_tid);
    }
    $query->condition('vps.field_ppsp_polling_station_nid', $polling_station_nids, 'IN');
    $query->condition('vpp.entity_id', $election_nid);
    $res = $query->execute()->fetchColumn();

    return $res;
  }

  return 0;
}

/**
 * returns a keyed array of polling stations
 */
function _valghalla_helper_get_polling_stations() {

  $data = array();
  foreach (entity_load('node', FALSE, array('type' => 'polling_station')) as $item) {
    $data[$item->nid] = $item->title;
  }

  asort($data, SORT_REGULAR);
  return $data;
}

function _valghalla_helper_get_active_election() {

  $nid = db_select('field_data_field_election_status', 's')
      ->fields('s', array('entity_id'))
      ->condition('field_election_status_value', 1)
      ->execute()
      ->fetchColumn();
  if ($nid) {
    return node_load($nid);
  }

  return FALSE;
}

/**
 * helper function for checking voulenteers count
 *
 * @global stdClass $user
 * @global stdClass $language
 * @return boolean
 */
function _valghalla_helper_volunteers_count() {
  global $user, $language;

  $user_party_id = empty($user->field_party[LANGUAGE_NONE][0]['tid']) ? FALSE : $user->field_party[LANGUAGE_NONE][0]['tid'];

  $where = '';
  if ($user_party_id) {
    $where = ' WHERE p.field_party_tid = ' . (int) $user_party_id;
  }

  $result = db_query('SELECT COUNT(*) AS num FROM {field_data_field_party} AS p' . $where);
  foreach ($result as $record) {
    return (bool) $record->num;
  }
}

/**
 * Retrieve values for tokens.
 *
 * @author Thomas Thune Hansen <tth@bellcom.dk>
 */
function _valghalla_helper_get_token_values($entity) {
  // Get host entity.
  $host_entity = $entity->hostEntity();
  // Load needed fields and nodes.
  if ($field = field_get_items('field_collection_item', $entity, 'field_election')) {
    $election_node = node_load($field[0]['target_id']);
  }

  if ($field = field_get_items('field_collection_item', $entity, 'field_vlnt_station')) {
    $polling_station_node = node_load($field[0]['target_id']);
  }

  if ($field = field_get_items('field_collection_item', $entity, 'field_post_role')) {
    $post_node = node_load($field[0]['target_id']);
  }

  // Empty variables.
  $volunteer_nid = '';
  $name = '';
  $email = '';
  $phone = '';
  $link = '';
  $date_now = '';
  $days = '';
  $election = '';
  $election_date = '';
  $polling_station = '';
  $polling_station_address = '';
  $position = '';
  $position_nid = '';
  $position_description = '';
  $time = '';
  $responsible = '';

  // Date info.
  //
  $date_now = date(variable_get('valghalla_datetime_format', 'd-m-Y H:i:s'));

  // Host entity (volunteer) info.
  //
  if (is_object($host_entity)) {
    $volunteer_nid = $host_entity->nid;

    $name = $host_entity->title;

    if ($email_field = field_get_items('node', $host_entity, 'field_email')) {
      $email = $email_field[0]['email'];
    }

    if ($phone_field = field_get_items('node', $host_entity, 'field_phone')) {
      $phone = $phone_field[0]['value'];
    }
  }

  // RSVP link.
  //
  if ($field = field_get_items('field_collection_item', $entity, 'field_token')) {
    $link_base_url = NULL;
    if (module_exists('valghalla_internal_server') && variable_get('valghalla_internal_server_enable')) {
      $link_base_url = valghalla_internal_server_get_external_server_url();
    }
    else {
      global $base_url;
      $link_base_url = $base_url;
    }

    $url = $link_base_url . '/volunteers/rsvp/' . $field[0]['value'];
    $link = '<a href="' . $url . '">' . $url . '</a>';
  }

  // Election info.
  //
  if (is_object($election_node)) {
    $election = $election_node->title;

    if ($field = field_get_items('node', $election_node, 'field_date')) {
      $election_date = date(variable_get('valghalla_date_format', 'd-m-Y'), strtotime($field[0]['value']));
    }

    $time_left = strtotime($field[0]['value']) - time();
    $days = (int) ($time_left / 86400);
  }

  // Polling station info.
  //
  if (is_object($polling_station_node)) {
    $polling_station = $polling_station_node->title;

    $polling_station_address = valghalla_polling_station_get_adress($polling_station_node);

    if ($field = field_get_items('node', $polling_station_node, 'field_contact')) {
      $responsible = $field[0]['value'];
    }
  }

  // Post info.
  //
  if (is_object($post_node)) {
    $position = $post_node->title;
    $position_nid = $post_node->nid;

    if ($field = field_get_items('node', $post_node, 'field_meetingtime')) {
      $time = $field[0]['value'];
    }

    if ($field = field_get_items('node', $post_node, 'field_description')) {
      $position_description = $field[0]['value'];
    }
  }

  return array(
    'nid' => $volunteer_nid,
    'position_nid' => $position_nid,
    '!name' => $name,
    '!email' => $email,
    '!phone' => $phone,
    '!link' => $link,
    '!url' => $url,
    '!date_now' => $date_now,
    '!days' => $days,
    '!election' => $election,
    '!election_date' => $election_date,
    '!polling_station' => $polling_station,
    '!polling_station_address' => $polling_station_address,
    '!polling_station_contact' => $responsible,
    '!position' => $position,
    '!position_nid' => $position_nid,
    '!position_description' => $position_description,
    '!time' => $time,
  );
}

/**
 * Info about replacement tokens.
 *
 * @author Thomas Thune Hansen <tth@bellcom.dk>
 */
function _valghalla_helper_get_volunteer_info_params($node) {
  return "<p><strong>Erstatningstokens til brug i emne- og indholdsfeltet:</strong></p>
          <ul>
          <li><em>!name</em>" . t(' vil blive erstattet af modtagerens navn') . "</li>
          <li><em>!email</em>" . t(' vil blive erstattet af modtagerens email adresse') . "</li>
          <li><em>!phone</em>" . t(' vil blive erstattet af modtagerens telefonnr') . "</li>
          <li><em>!date_now</em>" . t(' vil blive erstattet af tidspunktet for mailens udsendelse') . "</li>
          <li><em>!days</em>" . t(' vil blive erstattet af antallet af dage der er til valget (f.eks. 3)') . "</li>
          <li><em>!election</em>" . t(' vil blive erstattet af valgets titel') . "</li>
          <li><em>!election_date</em>" . t(' vil blive erstattet af valgets dato') . "</li>
          <li><em>!polling_station</em>" . t(' vil blive erstattet af valgstedets navn') . "</li>
          <li><em>!polling_station_address</em>" . t(' vil blive erstattet af valgstedets adresse') . "</li>
          <li><em>!position</em>" . t(' vil blive erstattet af rollens titel') . "</li>
          <li><em>!position_description</em>" . t(' vil blive erstattet af rollens beskrivelse') . "</li>
          <li><em>!time</em>" . t(' vil blive erstattet af rollens mødetidspunkt') . "</li>
          <li><em>!link</em>" . t(' vil blive erstattet med link til RSVP side (brug denne hvis der sendes HTML mails.') . "</li>
          <li><em>!url</em>" . t(" vil blive erstattet med url'en til RSVP side (brug denne hvis der sendes plain text mails.") . "</li>
          <li><em>!polling_station_contact</em>" . t(' vil blive erstattet med kontaktpersonen på valgstedet') . "</li>
          </ul>
          <p><em>Bemærk!</em>" . t(' i nogle tilfælde vil nogle tokens ikke være tilgængelige.') . "</p>";
}

/**
 * _valghalla_helper_get_age_from_cpr
 * Returns the correct age from CPR number taking century into account
 *
 * @param string $cpr
 *
 * @return int
 * @author Henrik Farre <hf@bellcom.dk>
 */
function _valghalla_helper_get_age_from_cpr($cpr)
{
  // Based on http://kronsell.net/cpralder.htm
  // Also see http://da.wikipedia.org/wiki/CPR-nummer#Under_eller_over_100_.C3.A5r
  $year_prefix = 19;
  $year        = substr($cpr, 4, 2);

  switch (substr($cpr, 7, 1))
  {
    case 0:
    case 1:
    case 2:
    case 3:
      $year_prefix = 19;
      break;
    case 4:
    case 9:
      if ($year <= 36) {
        $year_prefix = 20;
      }
      break;
    case 5:
    case 6:
    case 7:
    case 8:
      if ($year <= 36) {
        $year_prefix = 20;
      }
      if ($year >= 58) {
        $year_prefix = 18;
      }
      break;
  }

  $day   = substr($cpr, 0, 2);
  $month = substr($cpr, 2, 2);
  $year  = $year_prefix . $year;

  $date     = DateTime::createFromFormat('d-m-Y', $day . '-' . $month . '-' . $year);
  $now      = new DateTime();
  $interval = $now->diff($date);

  return $interval->y;
}


/**
 * Returns the list of existing tokens (as an array).
 */
function _valghalla_helper_get_existing_tokens() {
  $query = db_select('field_data_field_token', 'ft')
    ->distinct()
    ->fields('ft', array('field_token_value'))
    ->execute()
    ->fetchAll();

  $tokens_list = array();

  foreach ($query as $q => $v) {
    $tokens_list[] = $v->field_token_value;
  }

  return $tokens_list;
}


/**
 * Creates a new unique token.
 */
function _valghalla_helper_new_unique_token() {
  $existing_tokens = _valghalla_helper_get_existing_tokens();
  $unique_str = '';

  while (true) {
    $unique_str = _valghalla_helper_get_random_string(10);
    if (!in_array($unique_str, $existing_tokens)) {
      break;
    }
  }

  return $unique_str;
}


/*
 * Generates a random string with a certain lenght.
 */
function _valghalla_helper_get_random_string($len) {
  $result = '';
  $chars = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ';
  $chars .= 'abcdefghijklmnopqrstuvwxyz';
  $chars .= '0123456789';

  for ($i = 0; $i < $len; $i++) {
    $rand_num = (rand(0, strlen($chars) - 1));
    $result .= $chars[$rand_num];
  }

  return $result;
}

