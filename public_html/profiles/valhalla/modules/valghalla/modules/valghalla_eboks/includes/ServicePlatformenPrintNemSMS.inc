<?php
/**
 * @file
 * The wrapper class to work with Serviceplatformen Print service.
 */

module_load_include('inc', 'valghalla_eboks', 'includes/ServicePlatformenPrint');

/**
 * Class that holds the service requests for Digital Post.
 */
class ServicePlatformenPrintNemSMS extends ServicePlatformenPrint {

  /**
   * MaterialeID variable.
   *
   * Also used as MeddelelsesIndholdstypeIdentifikator or SysID.
   */
  private $materialeId;

  /**
   * ServiceplatformenPrintDP constructor.
   */
  public function __construct() {
    parent::__construct();

    $this->materialeId = variable_get('valghalla_eboks_materiale_id_nemsms');
  }

  /**
   * Set receiver callback.
   */
  public function setTo($to) {
    $this->request['BrevSPBody']['ForsendelseI']['ForsendelseModtager'] = array(
      'AfsendelseModtager' => array('CPRnummerIdentifikator' => $to),
    );
  }

  /**
   * Prepare request data.
   *
   * @param string $message
   *   SMS string.
   * @param array $params
   *   Request array.
   */
  public function prepareRequest($message, array $params) {
    $message_data = base64_encode($message);
    $this->request['BrevSPBody'] = array(
      'Kanalvalg' => 'S',
      'Prioritet' => 'D',
      'DigitalPostParametre' => array(
        'MeddelelseIndholdstypeIdentifikator' => $this->materialeId,
      ),
      'ForsendelseI' => array(
        'AfsendelseIdentifikator' => $this->getId($params),
        'FilformatNavn' => 'TXT',
        'MeddelelseIndholdData' => $message_data,
        'DokumentParametre' => array(),
      ),
    );
  }

}
