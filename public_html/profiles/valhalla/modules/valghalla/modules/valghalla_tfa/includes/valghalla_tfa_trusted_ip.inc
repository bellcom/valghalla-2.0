<?php

/**
 * @file classes for Valghalla TFA
 */

/**
 * Class TfaTrustedBrowser
 */
class TfaTrustedIp extends TfaBasePlugin implements TfaLoginPluginInterface {

  /**
   * @return bool
   */
  public function loginAllowed() {
    $trusted_ips = explode(',', variable_get('valghalla_tfa_trusted_ip'));
    $remote_ip = $_SERVER['REMOTE_ADDR'];

    //is trusted IP?
    if (in_array($remote_ip, $trusted_ips)) {
      return TRUE;
    }
    return FALSE;
  }

}