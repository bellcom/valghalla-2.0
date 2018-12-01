<?php

namespace ValghallaInternalServer;

use Monolog\Formatter\LineFormatter;
use Monolog\Logger;

class ValghallaLogger {
  public static function info($message) {
    ValghallaLogger::writeLogMessage(Logger::INFO, $message);
  }

  public static function warning($message) {
    ValghallaLogger::writeLogMessage(Logger::WARNING, $message);
  }

  public static function error($message) {
    ValghallaLogger::writeLogMessage(Logger::ERROR, $message);
  }

  private static function writeLogMessage($level, $message) {
    $logger = monolog('valghalla_internal_server_channel');
    $handler = $logger->popHandler();

    if ($handler) {
      // the default output format is "[%datetime%] %channel%.%level_name%: %message% %context% %extra%\n"
      $output = "[%datetime%] %level_name%: %message%\n";

      $formatter = new LineFormatter($output);
      $handler->setFormatter($formatter);
      $logger->pushHandler($handler);
    }

    $logger->log($level, $message, array());
  }
}