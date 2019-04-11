<?php

/**
 * @file
 * Provides ValghallaVolunteerValidationRecord enitity controller class.
 */

/**
 * The ValghallaVolunteerValidationRecord entity controller class.
 */
class ValghallaVolunteerValidationRecordController extends EntityAPIController {

  /**
   * {@inheritdoc}
   */
  public function create(array $values = array()) {
    $values += array(
      'created' => REQUEST_TIME,
      'bundle_type' => 'default_bundle',
    );

    $entity = parent::create($values);
    return $entity;
  }

  /**
   * {@inheritdoc}
   */
  public function save($entity, DatabaseTransaction $transaction = NULL) {
    $entity->changed = REQUEST_TIME;
    return parent::save($entity, $transaction);
  }

}
