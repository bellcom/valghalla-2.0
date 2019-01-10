<?php

/**
 * @file
 * Valghalla_external_server_signup.utils.inc.
 */

/**
 * Fetches and loads entry from GET params.
 *
 * @param string $name
 *   The name of a get param.
 * @param string $type
 *   The type of entry to load - node or taxonomy_term.
 *
 * @return mixed
 *   Loaded entry.
 */
function _valghalla_external_server_signup_fetch_entity_from_url($name, $type) {
  if (isset($_GET[$name])) {
    $uuid = $_GET[$name];
    $entities = entity_uuid_load($type, array($uuid));
    if (!empty($entities) && is_array($entities)) {
      $entity = reset($entities);
      return $entity;
    }
  }
}

/**
 * Gets the tokens array according to the form mode.
 *
 * @param string $mode
 *   Mode of the form: party, party_role, party_role_polling_station.
 *
 * @return array
 *   List of tokens, where key is the token itself and value is the token
 *   description.
 */
function _valghalla_external_server_signup_text_get_replacement_tokens($mode) {
  switch ($mode) {
    case 'party':
      return array(
        '@election_name' => 'name of the election',
        '@election_time' => 'time of the election',
        '@party_name' => 'name of the party',
      );

    case 'party_role':
      return array(
        '@election_name' => 'name of the election',
        '@election_time' => 'time of the election',
        '@party_name' => 'name of the party',
        '@role_name' => 'chosen role',
        '@role_meeting_date' => 'time when the person must come',
      );

    case 'party_polling_station':
      return array(
        '@election_name' => 'name of the election',
        '@election_time' => 'time of the election',
        '@party_name' => 'name of the party',
        '@polling_station_name' => 'name of the polling station',
      );

    case 'party_role_polling_station':
      return array(
        '@election_name' => 'name of the election',
        '@election_time' => 'time of the election',
        '@party_name' => 'name of the party',
        '@role_name' => 'chosen role',
        '@role_meeting_date' => 'time when the person must come',
        '@polling_station_name' => 'name of the polling station',
      );
  }
}

/**
 * Returns the list of roles that are available for selection.
 *
 * @param int $election_nid
 *   The election node NID.
 * @param int $party_tid
 *   The party node TID.
 * @param int $polling_station_nid
 *   Node ID of polling station,
 *   if null the all available polling stations are returned.
 *
 * @return array
 *   The array of roles mapped by role->nid.
 */
function _valghalla_external_server_signup_get_available_roles($election_nid, $party_tid, $polling_station_nid = NULL) {
  $available_roles = array();

  if ($polling_station_nid) {
    $polling_stations = array($polling_station_nid);
  }
  else {
    $polling_stations = array_keys(odin_get_polling_stations($election_nid));
  }

  $all_roles = odin_get_roles();
  $volunteers_count = odin_get_volunteers_count($election_nid, $polling_stations, $all_roles, $party_tid);

  foreach ($volunteers_count['role_count'] as $role_nid => $role_count) {
    if ($role_count['assigned'] > $role_count['total']) {
      $available_roles[$role_nid] = $all_roles[$role_nid];
    }
  }

  return $available_roles;
}

/**
 * Returns the list of available polling stations.
 *
 * Delegates the work to odin_get_signup_available_polling_stations().
 *
 * @param int $election_nid
 *   Node ID of election.
 * @param int $party_tid
 *   Term ID of party.
 * @param int $role_nid
 *   Node ID of role, if null the all available polling stations are returned.
 *
 * @return array
 *   List of polling stations.
 *
 * @see odin_get_signup_available_polling_stations()
 */
function _valghalla_external_server_signup_get_available_polling_stations($election_nid, $party_tid, $role_nid = NULL) {
  $available_polling_stations = array();
  if ($role_nid) {
    $available_polling_stations = odin_get_signup_available_polling_stations($election_nid, 1, $role_nid, $party_tid);
  }
  else {
    foreach (odin_get_roles() as $role_nid => $role) {
      $foundPollingStations = odin_get_signup_available_polling_stations($election_nid, 1, $role_nid, $party_tid);
      foreach ($foundPollingStations as $constituency => $psList) {
        foreach ($psList as $ps_key => $ps_name) {
          $available_polling_stations[$constituency][$ps_key] = $ps_name;
        }
      }
    }
  }

  return $available_polling_stations;
}

/**
 * HTML snippet for presenting polling station address.
 *
 * @param mixed $polling_station
 *   Polling station node.
 *
 * @return string
 *   HTML snippet.
 */
function _valghalla_external_server_signup_get_polling_station_detail_html($polling_station) {
  $name = $polling_station->title;
  $road = $polling_station->field_address_road['da'][0]['value'];
  $road_no = $polling_station->field_address_road_no['da'][0]['value'];
  $zip = $polling_station->field_address_zipcode['da'][0]['value'];
  $city = $polling_station->field_address_city['da'][0]['value'];

  $html = <<<"EOD"
<p>$name</p>
<p>$road $road_no</p>
<p>$zip $city</p>
EOD;

  return $html;
}

/**
 * HTML snippet for presenting role details.
 *
 * @param mixed $role
 *   Role node.
 *
 * @return string
 *   HTML snippet.
 */
function _valghalla_external_server_signup_get_role_detail_html($role) {
  $meeting_time = $role->field_meetingtime['und'][0]['value'];
  $html = <<<"EOD"
  Rolle mødetidspunkt <b>$meeting_time</b>
EOD;

  return $html;
}
