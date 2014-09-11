<?php
$tests = array(
  array(
    'yy' => 36,
    'md' => 0,
    'expected' => 19,
  ),
  array(
    'yy' => 57,
    'md' => 0,
    'expected' => 19,
  ),
  array(
    'yy' => 99,
    'md' => 0,
    'expected' => 19,
  ),

  array(
    'yy' => 36,
    'md' => 4,
    'expected' => 20,
  ),
  array(
    'yy' => 57,
    'md' => 4,
    'expected' => 19,
  ),
  array(
    'yy' => 99,
    'md' => 4,
    'expected' => 19,
  ),

  array(
    'yy' => 36,
    'md' => 5,
    'expected' => 20,
  ),
  array(
    'yy' => 57,
    'md' => 5,
    'expected' => 20,
  ),
  array(
    'yy' => 99,
    'md' => 5,
    'expected' => 19,
  ),

  array(
    'yy' => 36,
    'md' => 9,
    'expected' => 20,
  ),
  array(
    'yy' => 57,
    'md' => 9,
    'expected' => 19,
  ),
  array(
    'yy' => 99,
    'md' => 9,
    'expected' => 19,
  ),

  array(
    'yy' => 13,
    'md' => FALSE,
    'expected' => 19,
  ),
);

$error = FALSE;
foreach ($tests as $test) {
  $result = _valghalla_vol_validate_age_get_century($test['yy'], $test['md']);
  if($test['expected'] !== $result) {
    $error = TRUE;
    error_log('Test failed: yy: ' . $test['yy'] . ' md: ' . $test['md'] . ' Expected: ' . $test['expected'] );
  }
}

if (!$error) {
  error_log('Tests passed: ' . count($tests));
}
