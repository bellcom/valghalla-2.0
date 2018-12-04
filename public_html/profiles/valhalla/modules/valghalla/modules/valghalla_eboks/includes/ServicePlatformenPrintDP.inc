<?php

/**
 * @file
 * The wrapper class to work with Serviceplatformen Print service.
 */

use Mpdf\Mpdf;

/**
 * Class that holds the service requests for Digital Post.
 */
class ServiceplatformenPrintDP extends ServiceplatformenPrint {
  /**
   * ServiceplatformenPrint constructor.
   */
  public function __construct() {
    parent::__construct();

    $this->request['BrevSPBody'] = array(
      'Kanalvalg' => 'D',
      'Prioritet' => 'D',
    );
  }
}
