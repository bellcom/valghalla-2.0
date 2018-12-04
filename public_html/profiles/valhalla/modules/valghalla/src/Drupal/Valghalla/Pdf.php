<?php
/**
 * @file
 * The wrapper class for PDF generation.
 */

namespace Drupal\Valghalla;

use Mpdf\Mpdf;

/**
 * Class that holds the service requests.
 */
class Pdf extends Mpdf {

  /**
   * ValghallaPdf constructor.
   */
  public function __construct(array $config = []) {
    parent::__construct($config);
    $stylesheet = DRUPAL_ROOT . '/' . drupal_get_path('module', 'valghalla') . '/css/pdf.css';
    if (file_exists($stylesheet)) {
      $this->WriteHTML(file_get_contents($stylesheet), 1);
    }
  }
}