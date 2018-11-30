<?php

class ExternalWebservice {
  private $endpoint;
  private $authToken;

  function __construct() {
    $this->endpoint = variable_get('valghalla_external_server_endpoint');
  }

  /**
   * Calling webservice endpoint: /valghalla_resource_export
   */
  function fetchContent($page = 0) {
    $getParams = http_build_query(
      array(
        'page' => $page,
      )
    );
    $requestUrl = $this->endpoint . '/valghalla_resource_export.json?' . $getParams;
    $result = $this->requestWrapper($requestUrl);
    return $result;
  }

  /**
   * Calling webservice endpoint : POST /valghalla_resource_export
   * @return object
   */
  function pushNodeSerialized($data) {
    $requestUrl = $this->endpoint . '/valghalla_resource_export.json';

    $options = array();
    $options['method'] = 'POST';
    $options['data'] = json_encode(array(
      'node_export_data' => $data
    ));

    $result = $this->requestWrapper($requestUrl, $options);
    return $result;
  }

  /**
   * Calling webservice endpoint : POST /taxonomy_term
   *
   * Also checks if the term with the same uuid is already present in the system, then it will be updated.
   * If not - new term will be created.
   *
   * @return object
   */
  function pushTerm($term) {
    // Check if the term exists on external server.
    $remoteTerm = $this->getTermByUuid($term->uuid);
    if ($remoteTerm) {
      // There is the same term on remote server, update it.
      $term->tid = $remoteTerm->tid;
    } else {
      // No term on remote server with the same uuid, create a new one.
      unset($term->tid);
    }

   $json = valghalla_internal_server_term_to_json($term);

    $requestUrl = $this->endpoint . '/taxonomy_term.json';

    $options = array();
    $options['method'] = 'POST';
    $options['data'] = $json;
    $result = $this->requestWrapper($requestUrl, $options);

    if (!empty($result) && is_array($result)) {
      return array_pop($result);
    }
  }

  /**
   * Calling webservice endpoint : GET /taxonomy_term
   * @return object
   */
  function getTermByUuid($uuid) {
    $params = http_build_query(array(
      'parameters' => array(
        'uuid' => $uuid
      )
    ));

    $requestUrl = $this->endpoint . '/taxonomy_term.json?' . $params;
    $result = $this->requestWrapper($requestUrl);

    if (!empty($result) && is_array($result)) {
      return array_pop($result);
    }
  }

  /**
   * Calling webservice endpoint : GET /valghalla_resource_export/uuid
   * @return object
   */
  function exportByUuid($uuid) {
    $requestUrl = $this->endpoint . '/valghalla_resource_export/' . $uuid . '.json';
    $result = $this->requestWrapper($requestUrl);

    if (!empty($result) && is_array($result)) {
      return array_pop($result);
    }
  }

  /**
   * Calling webservice endpoint : DELETE /valghalla_resource_export/uuid
   * @return object
   */
  function removeFromQueueByUuid($uuid) {
    $requestUrl = $this->endpoint . '/valghalla_resource_export/' . $uuid . '.json';

    $result = $this->requestWrapper($requestUrl, array('method' => 'DELETE'));

    if (!empty($result) && is_array($result)) {
      return array_pop($result);
    }
  }

  private function requestWrapper($requestUrl, $options = array()) {
    if (!$this->authToken) {
      $user = variable_get('valghalla_external_server_user');
      $password = variable_get('valghalla_external_server_password');
      $this->authToken = 'Basic ' . base64_encode($user . ':' . $password);
    }

    $options['headers'] = array();
    $options['headers']['Authorization'] = $this->authToken;
    $options['headers']['Content-Type'] = 'application/json';

    $result = drupal_http_request($requestUrl, $options);
    if ($result->code == 200) {
      return json_decode($result->data);
    }
  }
}

///**
// * Calling webservice endpoint : GET /webform_node_export
// *
// * @param $page
// *
// * @return mixed
// */
//function os2forms_webform_sharing_get_webform_node_export($page = 0) {
//  $getParams = http_build_query(
//    array(
//      'page' => $page,
//      'options' => array(
//        'orderby' => array(
//          'changed' => 'DESC'
//        )
//      )
//    )
//  );
//  $repoUrl = variable_get('os2forms_webform_sharing_repo_endpoint') . '/webform_node_export.json?'. $getParams;
//
//  $options['headers']['Authorization'] = os2forms_webform_sharing_basic_auth();
//
//  $result = drupal_http_request($repoUrl, $options);
//  if ($result->code == 200) {
//    return json_decode($result->data);
//  }
//}
//


///**
// * Calling webservice endpoint : POST /webform_node_export
// * @return object
// */
//function os2forms_webform_sharing_post_webform_node_export($data) {
//  $repoUrl = variable_get('os2forms_webform_sharing_repo_endpoint') . '/webform_node_export.json';
//
//  $options['headers']['Authorization'] = os2forms_webform_sharing_basic_auth();
//  $options['headers']['Content-Type'] = 'application/json';
//  $options['method'] = 'POST';
//  $options['data'] = json_encode(array(
//    'node_export_data' => $data
//  ));
//
//  $result = drupal_http_request($repoUrl, $options);
//  if ($result->code == 200) {
//    return json_decode($result->data);
//  }
//}
//