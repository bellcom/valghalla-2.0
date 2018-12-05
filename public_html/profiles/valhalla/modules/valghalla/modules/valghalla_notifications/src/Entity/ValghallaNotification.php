<?php
/**
 * @file
 * Provides Valghalla notification enitity class.
 */

/**
 * Valghalla notification Entity class.
 */
class ValghallaNotification extends Entity {

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
   * The status of the task.
   *
   * @var string
   */
  public $status;

  /**
   * The status details.
   *
   * @var string
   */
  public $status_info;

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
    parent::__construct($values, 'entity_valghalla_notification');
  }

  /**
   * {@inheritdoc}
   */
  protected function defaultLabel() {
    return "Notification {$this->id}";
  }

}
