<?php

/**
 * @file
 * Valghalla_external_server_nemlogin.inc
 */

/**
 * Generates a NemID login link.
 *
 * @param string $destination
 *   The destination callback url.
 *
 * @return string
 *   Generated string.
 */
function valghalla_external_server_nemlogin_login_link($destination) {
  $idp = variable_get('valghalla_external_server_nemlogin_idp', 'https://test-nemlogin.bellcom.dk/simplesaml');

  $url = url($idp . VALGHALLA_EXTERNAL_SERVER_NEMLOGIN_URL_LOGIN, array(
    'query' => array(
      'mnemo' => 'bellcom.dk',
      'forward' => $GLOBALS['base_url'] . base_path() . 'nemlogin/login-callback?destination=' . urlencode($destination)
    )
  ));
  return $url;
}

/**
 * Fetches the CPR from the session.
 *
 * Is none found, null is returned.
 *
 * @return string
 *   The CPR stored in the session.
 */
function valghalla_external_server_nemlogin_fetch_cpr() {
  if (isset($_SESSION['valghalla_external_server_nemlogin_cpr'])) {
    return $_SESSION['valghalla_external_server_nemlogin_cpr'];
  }

  return NULL;
}

/**
 * Deletes the CPR from the session, destroys session on external IDP.
 */
function valghalla_external_server_nemlogin_logout() {
  unset($_SESSION['valghalla_external_server_nemlogin_cpr']);

  // TODO: make a proper logout.
  //$idp = variable_get('valghalla_external_server_nemlogin_idp', 'https://test-nemlogin.bellcom.dk/simplesaml');
  //drupal_http_request($idp . VALGHALLA_EXTERNAL_SERVER_NEMLOGIN_URL_LOGOUT);
}
