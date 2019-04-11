<?php

/**
 * @file
 * Provides ValghallaVolunteerValidationRecort enitity class.
 */

/**
 * ValghallaVolunteerValidationRecord Entity class.
 */
class ValghallaVolunteerValidationRecord extends Entity {

  /**
   * The internal numeric id of the notification.
   *
   * @var int
   */
  public $id;

  /**
   * The task type.
   *
   * @var string
   */
  public $type;

  /**
   * The Unix timestamp when the task was created.
   *
   * @var int
   */
  public $created;

  /**
   * {@inheritdoc}
   */
  protected $defaultLabel = TRUE;

  /**
   * {@inheritdoc}
   */
  public function __construct($values = array()) {
    parent::__construct($values, 'valghalla_volunteer_validation_record');
  }

  /**
   * {@inheritdoc}
   */
  protected function defaultLabel() {
    return "Notification {$this->id}";
  }

}
