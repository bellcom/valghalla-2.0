<?php

/**
 * @file
 * The wrapper class to work with Serviceplatformen Print service.
 */

/**
 * Class that holds the service requests.
 */
class ServiceplatformenPrint {

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
   * Set Request data.
   *
   * @param array $request
   *   Request array.
   */
  public function setRequest(array $request) {
    $this->request = $request;
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
      $response = $this->client->PrintAfsendBrevRequest($this->request);
      $response['status'] = TRUE;
      return $response;
    }
    catch (Exception $e) {
      $response = explode(':', $e->faultstring);
      return array(
        'status' => FALSE,
        'text' => empty($response[1]) ? $response[1] : $e->faultstring,
      );
    }
  }
}
