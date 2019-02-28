<?php

/**
 * @file
 * Valghalla_external_server_nemlogin.inc.
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
  $idp = variable_get('valghalla_external_server_nemlogin_idp', 'https://nemlogin.bellcom.dk/simplesaml');

  $url = url($idp . VALGHALLA_EXTERNAL_SERVER_NEMLOGIN_URL_LOGIN, array(
    'query' => array(
      'mnemo' => 'bellcom.dk',
      'forward' => $GLOBALS['base_url'] . base_path() . 'nemlogin/login-callback?destination=' . urlencode($destination),
    ),
  ));
  return $url;
}

/**
 * One time fetch function for the CPR from the session.
 *
 * This function is used to store CPR value between redirects.
 * Is none found, null is returned.
 *
 * After function execution CPR is deleted from the session.
 *
 * @return string
 *   The CPR stored in the session.
 */
function valghalla_external_server_nemlogin_fetch_cpr() {
  if (isset($_SESSION['valghalla_external_server_nemlogin_cpr'])) {
    $cpr = $_SESSION['valghalla_external_server_nemlogin_cpr'];
    unset($_SESSION['valghalla_external_server_nemlogin_cpr']);
    return $cpr;
  }

  return NULL;
}
