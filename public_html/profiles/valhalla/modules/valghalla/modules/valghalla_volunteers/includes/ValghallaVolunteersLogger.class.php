<?php

namespace ValghallaVolunteers;

use Monolog\Formatter\LineFormatter;
use Monolog\Logger;

/**
 * ValghallaVolunteersLogger class definition.
 */
class ValghallaVolunteersLogger {

  /**
   * Wrapper for logging info message.
   *
   * @param string $message
   *   The message.
   */
  public static function info($message) {
    ValghallaVolunteersLogger::writeLogMessage(Logger::INFO, $message);
  }

  /**
   * Wrapper for logging warning message.
   *
   * @param string $message
   *   The message.
   */
  public static function warning($message) {
    ValghallaVolunteersLogger::writeLogMessage(Logger::WARNING, $message);
  }

  /**
   * Wrapper for error warning message.
   *
   * @param string $message
   *   The message.
   */
  public static function error($message) {
    ValghallaVolunteersLogger::writeLogMessage(Logger::ERROR, $message);
  }

  /**
   * Calls actual logging command.
   *
   * @param int $level
   *   Level of logging.
   * @param string $message
   *   The messages.
   */
  private static function writeLogMessage($level, $message) {
    $logger = monolog('valghalla_volunteers_channel');
    $handler = $logger->popHandler();

    if ($handler) {
      // The default output format is
      // "[%datetime%] %channel%.%level_name%: %message% %context% %extra%\n".
      $output = "[%datetime%] %level_name%: %message% %extra%\n";

      $formatter = new LineFormatter($output);
      $handler->setFormatter($formatter);
      $logger->pushHandler($handler);
      $logger->pushProcessor(function ($entry) {
        global $user;
        $entry['extra']['uid'] = $user->uid;
        $entry['extra']['uri'] = $_SERVER['REQUEST_URI'];
        $entry['extra']['ip'] = ip_address();
        return $entry;
      });
    }

    $logger->log($level, $message, array());
  }

}
