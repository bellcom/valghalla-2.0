<?php

namespace ValghallaInternalServer;

use Monolog\Formatter\LineFormatter;
use Monolog\Logger;

/**
 * ValghallaLogger class definition.
 */
class ValghallaLogger {

  /**
   * Wrapper for logging info message.
   *
   * @param string $message
   *   The message.
   */
  public static function info($message) {
    ValghallaLogger::writeLogMessage(Logger::INFO, $message);
  }

  /**
   * Wrapper for logging warning message.
   *
   * @param string $message
   *   The message.
   */
  public static function warning($message) {
    ValghallaLogger::writeLogMessage(Logger::WARNING, $message);
  }

  /**
   * Wrapper for error warning message.
   *
   * @param string $message
   *   The message.
   */
  public static function error($message) {
    ValghallaLogger::writeLogMessage(Logger::ERROR, $message);
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
    $logger = monolog('valghalla_internal_server_channel');
    $handler = $logger->popHandler();

    if ($handler) {
      // The default output format is
      // "[%datetime%] %channel%.%level_name%: %message% %context% %extra%\n".
      $output = "[%datetime%] %level_name%: %message%\n";

      $formatter = new LineFormatter($output);
      $handler->setFormatter($formatter);
      $logger->pushHandler($handler);
    }

    $logger->log($level, $message, array());
  }

}
