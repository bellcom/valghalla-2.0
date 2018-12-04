<?php
/**
 * @file
 * The wrapper class to work with Serviceplatformen Print service.
 */

use Drupal\Valghalla\Pdf;
use Mpdf\Output\Destination;

module_load_include('inc', 'valghalla_eboks', 'includes/ServicePlatformenPrint');

/**
 * Class that holds the service requests for Digital Post.
 */
class ServicePlatformenPrintDP extends ServicePlatformenPrint {

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

    $this->materialeId = variable_get('valghalla_eboks_materiale_id_dp');
  }

  /**
   * ServiceplatformenPrintDP constructor.
   */
  public function setTo($to) {
    $this->request['BrevSPBody']['ForsendelseI']['ForsendelseModtager'] = array(
      'AfsendelseModtager' => array('CPRnummerIdentifikator' => $to),
    );
  }

  /**
   * Prepare request data.
   *
   * @param array $params
   *   Request array.
   */
  public function prepareRequest(array $params) {
    $message = $this->renderMessage($params);
    $pdf = new Pdf();
    $pdf->WriteHTML($message);
    $pdf_output = $pdf->Output(FALSE, Destination::STRING_RETURN);
    $message_data = base64_encode($pdf_output);
    $title_text = format_string($params['subject'], $params['tokens']);

    $this->request['BrevSPBody'] = array(
      'Kanalvalg' => 'D',
      'Prioritet' => 'D',
      'DigitalPostParametre' => array(
        'MeddelelseIndholdstypeIdentifikator' => $this->materialId,
      ),
      'ForsendelseI' => array(
        'AfsendelseIdentifikator' => $this->getId($params),
        'FilformatNavn' => 'PDF',
        'MeddelelseIndholdData' => $message_data,
        'DokumentParametre' => array(
          'TitelTekst' => $title_text,
        ),
      ),
    );
  }

  /**
   * Generate unique ID for message.
   *
   * @param array $params
   *   Message parameters.
   *
   * @return string
   *   Message id.
   */
  private function getId(array $params) {
    $message_id = strtotime('now');
    // @TODO Implement message id.
    return $this->materialeId . 'BBR' . sprintf('%021d', $message_id);
  }

}
