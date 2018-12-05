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
 *
 * @return array
 *   The array of roles mapped by role->nid.
 */
function _valghalla_external_server_signup_get_available_roles($election_nid, $party_tid) {
  $available_roles = array();

  $election_polling_stations = odin_get_polling_stations($election_nid);
  $all_roles = odin_get_roles();
  $volunteers_count = odin_get_volunteers_count($election_nid, array_keys($election_polling_stations), $all_roles, $party_tid);

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
 * Delegates the work to valghalla_signup_get_avaiable_polling_stations().
 *
 * @param int $election_nid
 *   Node ID of election.
 * @param int $role_nid
 *   Node ID of role.
 *
 * @return array
 *   List of polling stations.
 *
 * @see valghalla_signup_get_avaiable_polling_stations()
 */
function _valghalla_external_server_signup_get_available_polling_stations($election_nid, $role_nid) {
  // Delegating work to valghalla_signup module,
  // not to repeat the same logic again.
  return valghalla_signup_get_avaiable_polling_stations($election_nid, 1, $role_nid);
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
