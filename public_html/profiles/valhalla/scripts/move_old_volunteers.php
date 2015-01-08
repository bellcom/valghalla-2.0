<?php
$election_nid = 2380;

$taxonomy = taxonomy_vocabulary_machine_name_load('partier');
$roles_array = _valhalla_helper_get_role_array();
foreach (node_load_multiple(array(), array('type' => 'polling_station')) as $polling_station){
  foreach (taxonomy_get_tree($taxonomy->vid) as $term) {
    $posts_array = get_posts_array($polling_station, $term->tid);

    if($posts_array['existing']) {
      foreach ($posts_array['existing'] as $volunteer_nid => $post) {
        $role_nid = $roles_array[$posts_array['posts_to_fill'][$volunteer_nid]['title']];
        $volunteer_nid = $volunteer_nid;
        $polling_station_nid = $polling_station->nid;

        valghalla_volunteers_add_volunteer_to_post($volunteer_nid, $polling_station_nid, $role_nid, $term->tid, $election_nid);
      }
    }
  }
}

function get_posts_array($polling_station, $user_party_id) {
 global $user, $language;

  $station_id = $polling_station->nid;
  $field_digital_election_list=field_get_items('node', $polling_station, 'field_digital_election_list');
  $posts_to_fill = array();
  $existing = array();
  $volunteers_2 = array();
  $extra_array = array();

  $res = db_select('node', 'n')
    ->fields('n', array('nid', 'title'))
    ->condition('n.type', 'roles')
    ->execute();

  while($rec=$res->fetchAssoc()){
    $nids[$rec['nid']]= $rec['title'];
  }

  if ($volunteers_pr_party=field_get_items('node',$polling_station, 'field_volunteers_pr_party_1')) {
    foreach ($volunteers_pr_party as $item) {
      $field_collection_item=entity_load('field_collection_item', array($item['value']));
      $party_id=field_get_items('field_collection_item',$field_collection_item[$item['value']],'field_party_list');

      if($party_id[0]["party_list"]==$user_party_id) {
        foreach($nids as $nid=>$title){
          $field_name='field_role_n'.$nid;
          $field=field_get_items('field_collection_item',$field_collection_item[$item['value']],$field_name);

          if($field&&(int)$field[0]['number_vo']>0){
            $posts_to_fill = array_merge($posts_to_fill, array_fill(0,$field[0]['number_vo'], strtolower ($title)));
          }
        }
      }
    }
  }

  // tth: Get all roles, query all content from bundle 'roles'
  $role_array = _valhalla_helper_get_role_array();

  // tth: Loop through the roles used on the pollingstation, and load the volunteers
  // $station_role_id is the "uniqe" id for the current role from the current party on the
  // current station. This is set during the add volunteer to station routine
  $post_id = rand(1,20) . rand(1,20);
  foreach($posts_to_fill as $key => $value){
    $station_role_id = $user_party_id . $role_array[$value] . $station_id;

    $volunteer_query = new EntityFieldQuery();
    $volunteer_query->fieldCondition('field_polling_station_post', 'value', $station_role_id, 'like')
      ->entityCondition('bundle', 'volunteers')
      ->entityCondition('entity_type', 'node')
      ->propertyCondition('status', 1);

    $reset_query = $volunteer_query->execute();
    $volunteers[$value] = reset($reset_query);

    // yani: this array contains all the existed volunteers, used to compare with $existing later.
    $volunteers_2[$value] = $volunteers[$value];
  }

  // tth: Populate "existing"-array with volunteer data
  foreach($posts_to_fill as $key => $value){
    unset($posts_to_fill[$key]);
    $id = NULL;

    $station_role_id = $user_party_id . $role_array[$value] . $station_id;
    // tth: Check if there is a volunteer with the role
    if(!empty($volunteers[$value])){
      $reset_array = array_shift($volunteers[$value]);
      $id = reset($reset_array);
    }
    if($id){
      $existing[$id] = array(
          'data' => _valhalla_helper_wrap_name(node_load($id)),
          'nid' => $id
        );
    }
    else {
      // tth: The id is used when the js inserts the volunteer info on the page
      // previously the id was just a running number, which caused the volunteer
      // info to be places in numerous fields on the list, although the volunteer
      // was only added to one post.
      // The problem only existed when watching multiple parties on the polling
      // station. Fix: insert a number that is not repeated.
      $id = "p" . $user_party_id . $post_id;
      $post_id++;
      $value = $value;
    }

    $posts_to_fill[$id] = array('title' => $value, 'party_id' => $user_party_id);

    $id = NULL;
  }

  // yani: make a array of whole volunteers.
  if (!empty($volunteers_2)) {
    foreach ($volunteers_2 as $role_name => $people) {
      if(!empty($people)) {
        foreach ($people as $key => $object) {
          $id = $object->nid;
          $extra_array[$id] = array(
            'data' => _valhalla_helper_wrap_name(node_load($id), 'p',1),
            'nid' => $id,
            'title' => $role_name,
          );
        }
    } }
  }

  // Yani: compare $volunteers and $existing to find out if the number of the place and the number of existed volunteers are the same.
  $extra = array();
  if (count($extra_array) > count($existing)) {
    $extra= array_diff_assoc($extra_array, $existing);
  }

  return array(
          'posts_to_fill' => $posts_to_fill,
          'party_id' => $user_party_id,
          'station_id' => $station_id,
          'existing' => isset($existing) ? $existing : "",
          'extra' => isset($extra) ? $extra : "",
       );
}

function _valhalla_helper_get_role_array(){
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

function _valhalla_helper_wrap_name($node, $container = 'p',$extra = null) {
  global $language;

  $rsvp_map = array(
      0 => t('Har endnu ikke bekræftet'),
      1 => t('Har bekræftet sin deltagelse'),
      2 => t('Har meldt afbud til dette valg'),
      3 => t('Ønsker at blive slettet'),
  );
  $rsvp_class_map = array(
      0 => 'unknown',
      1 => 'yes',
      2 => 'no',
      3 => 'never',
  );

  $party = taxonomy_term_load($node->field_party[$language->language][0]['tid']);

  $rsvp_markup = "";

  $rsvp_message = field_get_items('node', $node, 'field_rsvp_comment');

  if($rsvp_message){
    if(!empty($rsvp_message[0]['value'])){
      $rsvp_markup = '<span class="rsvp-message-icon"></span><span style="display:none;" class="rsvp-message">' . $rsvp_message[0]['value'] . '</span>';
    }
  }
}
