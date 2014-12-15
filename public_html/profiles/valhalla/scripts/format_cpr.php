<?php

$query = new EntityFieldQuery();
$query->entityCondition('entity_type', 'node')
  ->entityCondition('bundle', 'volunteers');
$result = $query->execute();

if (isset($result['node'])) {
  foreach ($result['node'] as $nid => $info) {
    $volunteer = node_load($nid);

    $language = field_language('node', $volunteer, 'field_cpr_number');

    $cpr = &$volunteer->field_cpr_number[$language][0]['value'];
    if (!strstr($cpr, '-')) {
      $format_cpr = substr($cpr, 0, 6);
      $format_cpr .= '-';
      $format_cpr .= substr($cpr, 6, 4);

      $cpr = $format_cpr;

      error_log(__FILE__ . ' : ' . __LINE__ . ': ' .  print_r($volunteer->field_cpr_number, 1));
      node_save($volunteer);
    }
  }

}
