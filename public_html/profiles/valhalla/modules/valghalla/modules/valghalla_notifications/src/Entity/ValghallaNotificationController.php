<?php
/**
 * @file
 * Provides Valghalla notification enitity controller class.
 */

/**
 * The Valghalla notification entity controller class.
 */
class ValghallaNotificationController extends EntityAPIController {

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
