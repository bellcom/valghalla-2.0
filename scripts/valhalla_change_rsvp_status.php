<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

$volunters =  db_query('SELECT f.field_electioninfo_value from {field_data_field_electioninfo} f left join {field_data_field_rsvp} r on f.field_electioninfo_value=r.entity_id where field_rsvp_value is null')->fetchAll();

foreach ($volunters as $field_election){

$fc = array_shift(entity_load('field_collection_item', array($field_election->field_electioninfo_value)));
$fc->field_rsvp[LANGUAGE_NONE][0]['value'] = 0;
$fc->save();

}