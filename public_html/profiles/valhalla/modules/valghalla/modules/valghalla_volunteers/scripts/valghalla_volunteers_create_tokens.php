<?php

/*
 * Script that searches "volunteers" from the database and provides them with token strings.
 * Ment to be called with "drush scr <path-to-file>"
 */


function  _valghalla_volunteers_get_nodes() {
	$query = db_select('node', 'n')
		->fields('n', array('nid'))
		->condition('type', 'volunteers')
		->execute()
		->fetchAll();

	$result = array();

	foreach ($query as $q => $v) {
		$result[] = $v->nid;
	}

	return $result;
}


function  _valghalla_volunteers_edit_node_data($nid) {
	$node = node_load($nid);
	$items = field_get_items('node', $node, 'field_electioninfo');

	foreach ($items as $item) {
		$fc = field_collection_field_get_entity($item);
		 _valghalla_volunteers_edit_collection_field($fc);
	}
}


function  _valghalla_volunteers_edit_collection_field($field_item) {
	if (empty($field_item->field_token)) {
		$new_token = _valghalla_helper_new_unique_token();

		$field_item->field_token['und'][0]['value'] = $new_token;
		$field_item->field_token['und'][0]['format'] = '';
		$field_item->field_token['und'][0]['safe_value'] = $new_token;

		$field_item->save(TRUE);
	}
}


$nids =  _valghalla_volunteers_get_nodes();
foreach ($nids as $n) {
	 _valghalla_volunteers_edit_node_data($n);
}

echo 'Done!' . "\n" ;


