<?php

/**
 * @file
 * Include SimpleSAML_Auth_Simple help functions.
 */

/**
 * Attempts to fetch field from the SimpleAuth attributes.
 *
 * Function that attempts to fetch field from the SimpleAuth attributes with
 * specific name, suffix with NumberIdentifier.
 * E.g. if field name is "CPR", method will attempt
 * to fetch dk:gov:saml:attribute:CprNumberIdentifier.
 *
 * If field value is fetch it is returned, otherwise NULL is returned.
 *
 * @param mixed $as
 *   SimpleAuth valid object.
 * @param string $field_name
 *   Name of the field.
 *
 * @return string
 *   Field value.
 */
function attempt_fetch_number_identifier($as, $field_name = 'cpr') {
  // Make first char uppercase and suffixing with NumberIdentifier.
  $field_name = ucfirst(strtolower($field_name));
  $field_name .= 'NumberIdentifier';

  $attrs = $as->getAttributes();
  $field_value = NULL;

  if (is_array($attrs) && isset($attrs["dk:gov:saml:attribute:$field_name"])) {
    if (is_array($attrs["dk:gov:saml:attribute:$field_name"]) && isset($attrs["dk:gov:saml:attribute:$field_name"][0])) {
      $field_value = $attrs["dk:gov:saml:attribute:$field_name"][0];
    }
  }

  return $field_value;
}

/**
 * NemidAuth interface.
 */
interface NemloginAuthInterface {

  /**
   * Check plugin status.
   *
   * @return bool
   *   Boolean value about plugin status.
   */
  public function isOk();

  /**
   * Check authorization status.
   *
   * @return bool
   *   Boolean value about authorization status.
   */
  public function isAuthenticated();

  /**
   * Main login method.
   */
  public function login();

  /**
   * Main logout method.
   */
  public function logout();

  /**
   * Fetch authorization value by key.
   *
   * @param string $key
   *   Key for fetching value.
   *
   * @return string
   *   Authorization value.
   */
  public function fetchValue($key);

  /**
   * Defines plugin settings form elements.
   *
   * @return array
   *   Settings form array.
   */
  public function settingsForm();

  /**
   * Defines plugin settings validate handler.
   *
   * @param array $form
   *   Form array.
   * @param array $form_state
   *   Form state array.
   */
  public function settingsFormValidate(array &$form, array &$form_state);

  /**
   * Defines plugin settings submit handler.
   *
   * @param array $form
   *   Form array.
   * @param array $form_state
   *   Form state array.
   */
  public function settingsFormSubmit(array &$form, array &$form_state);

}

/**
 * NemidAuth interface.
 */
abstract class NemloginAuth implements NemloginAuthInterface {

  /**
   * Authorization values array.
   *
   * @var array
   */
  protected $values;

  /**
   * {@inheritdoc}
   */
  public function fetchValue($key) {
    return isset($this->values[$key]) ? $this->values[$key] : NULL;
  }

  /**
   * {@inheritdoc}
   */
  public function settingsForm() {
  }

  /**
   * {@inheritdoc}
   */
  public function settingsFormValidate(array &$form, array &$form_state) {
  }

  /**
   * {@inheritdoc}
   */
  public function settingsFormSubmit(array &$form, array &$form_state) {
  }

  /**
   * Build return link based on data from current request.
   *
   * @return string
   *   Return link URL.
   */
  protected function getReturnUrl() {
    global $base_url, $base_path;
    $destination = drupal_get_destination();
    if ($destination['destination'] == ltrim(request_uri(), '/')) {
      $destination['destination'] = '';
    }
    return $base_url . $base_path . $destination['destination'];
  }

}
