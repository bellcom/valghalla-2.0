<?php
/**
 * @file
 * The wrapper class to work with Serviceplatformen Print service.
 */

/**
 * Class that holds the service requests.
 */
class ServicePlatformenPrint {

  /**
   * SOAPClient object.
   *
   * @var object
   */
  protected $client;

  /**
   * SOAP Request array.
   *
   * @var array
   */
  protected $request;

  /**
   * ServiceplatformenPrint constructor.
   */
  public function __construct() {
    global $user;

    $wsdl_address = variable_get('valghalla_eboks_wsdl');
    $service_location = variable_get('valghalla_eboks_location');
    $certfile_passphrase = variable_get('valghalla_eboks_certfile_passphrase');
    $certfile = variable_get('valghalla_eboks_certfile');

    $this->client = new SoapClient($wsdl_address, array(
      'location' => $service_location,
      'local_cert' => $certfile,
      'passphrase' => $certfile_passphrase,
      'trace' => TRUE,
    ));

    $serviceagreementuuid = variable_get('valghalla_eboks_serviceagreementuuid');
    $usersystemuuid = variable_get('valghalla_eboks_usersystemuuid');
    $useruuid = variable_get('valghalla_eboks_useruuid');
    $serviceuuid = variable_get('valghalla_eboks_serviceuuid');
    $accountinginfo = variable_get('valghalla_eboks_accountinginfo');

    $this->request = array(
      'InvocationContext' => array(
        'ServiceAgreementUUID' => $serviceagreementuuid,
        'UserSystemUUID' => $usersystemuuid,
        'UserUUID' => $useruuid,
        'ServiceUUID' => $serviceuuid,
        'AccountingInfo' => $accountinginfo,
        'OnBehalfOfUser' => $user->name,
      ),
    );
  }

  /**
   * Get Request data.
   */
  public function getRequest() {
    return $this->request;
  }

  /**
   * Send message method call.
   */
  public function sendMessage() {
    ini_set('soap.wsdl_cache_enabled', 0);
    ini_set('soap.wsdl_cache_ttl', 0);
    try {
      $response = $this->client->afsendBrev($this->request);
      $response['status'] = TRUE;
    }
    catch (Exception $e) {
      $response = array(
        'status' => FALSE,
        'text' => $e->faultstring,
        'code' => $e->faultcode,
      );
    }
    if (variable_get('valghalla_eboks_debug', FALSE)) {
      $path = file_directory_temp() . '/service-print-soap';
      if (!file_exists($path)) {
        mkdir($path, 0777, TRUE);
      }
      $path .= '/request-' . time() . '-' . uniqid() . '.xml';
      file_unmanaged_save_data($this->client->__getLastRequest(), $path, FILE_EXISTS_REPLACE);
      watchdog('ServicePlatformenPrint', 'XML-request filesaved to %path', array('%path' => $path));
    }
    $response['response'] = $this->client->__getLastResponse();
    return $response;

  }

  /**
   * Render entire message to send.
   *
   * @param array $params
   *   Array with message sources.
   *
   * @return string
   *   Formatted message.
   */
  public function renderMessage(array $params) {
    $message = format_string($params['body'], $params['tokens']);
    return check_markup($message, isset($params['format']) ? $params['format'] : NULL);
  }

}
