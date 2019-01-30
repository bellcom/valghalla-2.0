<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
$sql = 'select * from field_collection_item left join field_data_field_electioninfo on item_id=field_electioninfo_value where field_name=:name and entity_id IS NULL';
$result = db_query($sql, array(':name' => "field_electioninfo"));
  foreach ($result as $row) {
    entity_delete('field_collection_item', $row->item_id );
   echo 'deleted: '.$row->item_id . PHP_EOL;
  }