<?php

class KkLogin {
  private $nemloginUrl = 'https://nemlogin-test.kk.dk';

  public function getSubDomain() {
    //return 'domain.kk.dk'; //replace this value for your domain;
    return $_SERVER['SERVER_NAME'];
  }

  public function getCookieDomain() {
    return "." . $this->getSubDomain();
  }

  public function haveCookie() {
    return $this->getCookie() != NULL;
  }

  public function getCookie() {
    return $_COOKIE["nemloginkk"];
  }

  public function updateCookie($samlid) {
    setcookie('nemloginkk', $samlid, time() + 3600 * 24, '/', $this->getCookieDomain(), true);
  }

  public function isLoggedIn() {
    return file_get_contents($this->nemloginUrl . '/nemlogin/loggedInService/' . $this->getCookie()) == "true";
  }

//  public function login() {
//    $b64Url = base64_encode("https://domain.kk.dk/somePath/handleloginpost.php");
//    header('Location: ' . $this->nemloginUrl . '/nemlogin/login?callbackurl=' . $b64Url);
//  }

  public function getLoginUrl() {
    $b64Url = base64_encode($_SERVER['REQUEST_SCHEME'] . "://" . $_SERVER['HTTP_HOST'] . "/nemlogin/handlepost");
    return $this->nemloginUrl . '/nemlogin/login?callbackurl=' . $b64Url;
  }

//  public function logout() {
//    setcookie("nemloginkk", "", time() - 3600, "/", "." . $this->getSubDomain());
//    $b64Url = base64_encode("https://domain.kk.dk/somepage.php");
//    header('Location: ' . $this->nemloginUrl . '/nemlogin/logout?callbacklogout=' . $b64Url);
//  }

  function getLoggedInStatus() {
    $response = file_get_contents($this->nemloginUrl  . '/nemlogin/loggedInUserService/' . $this->getCookie());
    $response = json_decode($response);

    return $response;
    //access array..
  }
} 