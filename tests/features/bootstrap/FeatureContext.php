
<?php

use Behat\Behat\Tester\Exception\PendingException;
use Drupal\DrupalExtension\Context\RawDrupalContext;
use Behat\Behat\Context\SnippetAcceptingContext;
use Behat\Gherkin\Node\PyStringNode;
use Behat\Gherkin\Node\TableNode;

/**
 * Defines application features from the specific context.
 */
class FeatureContext extends RawDrupalContext implements SnippetAcceptingContext {

  /**
   * Initializes context.
   *
   * Every scenario gets its own context instance.
   * You can also pass arbitrary arguments to the
   * context constructor through behat.yml.
   */
  public function __construct() {
  }

  /**
    * @AfterStep
    */
  public function takeScreenshotAfterFailedStep($scope)
  {
    if (99 === $scope->getTestResult()->getResultCode()) {
        $this->takeScreenshot();
    }
  }

  private function takeScreenshot()
  {
    $driver      = $this->getSession()->getDriver();
    if (!$driver instanceof Behat\Mink\Driver\Selenium2Driver) {
      return;
    }
    $page               = $this->getSession()->getPage()->getContent();
    $screenshot         = $driver->getScreenshot();
    $screenshotFileName = date('d-m-y_h-i-s') . '_' . uniqid() . '.png';
    $pageFileName       = date('d-m-y_h-i-s') . '_' . uniqid() . '.html';
    $filePath           = '/var/www/tmp/';
    file_put_contents($filePath.$screenshotFileName, $screenshot);
    file_put_contents($filePath.$pageFileName, $page);
    print 'Screenshot at: ' . $filePath.$screenshotFileName."\n";
    print 'HTML dump at: ' . $filePath.$pageFileName."\n";
  }

  /**
    * @Given I am on a large viewport
    */
  public function iAmOnALargeViewport()
  {
    $driver      = $this->getSession()->getDriver();
    if (!$driver instanceof Behat\Mink\Driver\Selenium2Driver) {
      return;
    }
    $this->getSession()->resizeWindow(1440, 900, 'current');
  }

  /**
    * @Given I am logged in with new user :username
    */
  public function iAmLoggedInWithNewUser($username)
  {
    //This will generate a random password, you could set your own here
    $password = user_password(8);

    //set up the user fields
    $fields = array(
      'name' => $username . user_password(),
      'mail' => $username . '@email.com',
      'pass' => $password,
      'status' => 1,
      'init' => 'email address',
      'roles' => array(
        DRUPAL_AUTHENTICATED_RID => 'authenticated user',
      ),
    );

    //the first parameter is left blank so a new user is created
    $account = user_save('', $fields);

    // Now for the actual login.
    $this->getSession()->visit('/user');

    $this->getSession()->getPage()->fillField('edit-name', $username);
    $this->getSession()->getPage()->fillField('edit-pass', $password);

    $this->getSession()->getPage()->pressButton('edit-submit');
  }
  /**
    * @Given I fill in wysiwyg on field :arg1 with :arg2
    */
  public function iFillInWysiwygOnFieldWith($instanceId, $text)
  {
    $instance = $this->getWysiwygInstance($instanceId);
    $this->getSession()->executeScript("$instance.setData(\"$text\");");
  }

  /**
   * Get the instance variable to use in Javascript.
   *
   * @param string
   *   The instanceId used by the WYSIWYG module to identify the instance.
   *
   * @throws Exeception
   *   Throws an exception if the editor doesn't exist.
   *
   * @return string
   *   A Javascript expression representing the WYSIWYG instance.
   */
  protected function getWysiwygInstance($instanceId) {
    $instance = "CKEDITOR.instances['$instanceId']";

    if (!$this->getSession()->evaluateScript("return !!$instance")) {
      throw new \Exception(sprintf('The editor "%s" was not found on the page %s', $instanceId, $this->getSession()->getCurrentUrl()));
    }

    return $instance;
  }

  /**
   * Wait until the id="updateprogress" element is gone,
   * or timeout after 3 minutes (180,000 ms).
   *
   * @Given I wait for the batch job to finish
   */
  public function iWaitForTheBatchJobToFinish()
  {
    $this->getSession()->wait(180000, 'jQuery("#updateprogress").length === 0');
  }

  /**
   * Check drupal system variables.
   *
   * @Given the following variables are set:
   */
  public function theFollowingVariablesAreSet(TableNode $variablesTable)
  {
    foreach ($variablesTable as $variableHash) {
      $variable = variable_get($variableHash['variable']);
      if (is_array($variable)) {
        $variable = json_encode($variable);
      }
      if ($variable === NULL || $variable != $variableHash['value']) {
        throw new \Exception(sprintf('The variable "%s" was not set to "%s" as specified', $variableHash['variable'], $variableHash['value']));
      }
    }
  }

  /**
   * Just wait a bit, 1 second, for animations, and such to end.
   *
   * @Then I wait a bit
   */
  public function iWaitABit()
  {
    $this->getSession()->wait(1000);
  }

    /**
     * @Given I click all :arg1
     */
    public function iClickAll($arg1)
    {
      $links = $this->getSession()->getPage()->findAll('css', $arg1);
      foreach ($links as $link) {
         $link->click();
      }
    }

  /**
   * Checks, that form element with specified label is visible on page.
   *
   * @Then /^(?:|I )should see an? "(?P<label>[^"]*)" form element$/
   */
  public function assertFormElementOnPage($label) {
    $element = $this->getSession()->getPage();
    $nodes = $element->findAll('css', '.form-item label');
    foreach ($nodes as $node) {
      if ($node->getText() === $label) {
        if ($node->isVisible()) {
          return;
        }
        else {
          throw new \Exception("Form item with label \"$label\" not visible.");
        }
      }
    }
    throw new \Behat\Mink\Exception\ElementNotFoundException($this->getSession(), 'form item', 'label', $label);
  }

  /**
   * Checks, that form element with specified label is visible on page.
   *
   * @Then /^(?:|I )should not see an? "(?P<label>[^"]*)" form element$/
   */
  public function assertFormElementNotOnPage($label) {
    $element = $this->getSession()->getPage();
    $nodes = $element->findAll('css', '.form-item label');
    foreach ($nodes as $node) {
      if ($node->getText() === $label) {
        if ($node->isVisible()) {
          throw new \Exception("Form item with label \"$label\" is visible.");
        }
        else {
          return;
        }
      }
    }
  }

    /**
     * @Given The variable :arg1 is set to :arg2
     */
    public function theVariableIsSetTo($arg1, $arg2)
    {
      variable_set($arg1, $arg2);
    }

    /**
     * @Then the :label field should not be disabled
     */
    public function theFieldShouldNotBeDisabled($label)
    {
      $element = $this->getSession()->getPage();
      $nodes = $element->findAll('css', '.form-item label');
      foreach ($nodes as $node) {
        if ($node->getText() === $label) {
          $formItemMarkup = $node->getParent()->getHtml();
          if (strstr($formItemMarkup, 'disabled="disabled"')) {
            throw new \Exception("Form item with label \"$label\" is disabled.");
          }
          else {
            return;
          }
        }
      }
      throw new \Behat\Mink\Exception\ElementNotFoundException($this->getSession(), 'form item', 'label', $label);
    }

    /**
     * @Then the :label field should be disabled
     */
    public function theFieldShouldBeDisabled($label)
    {
      $element = $this->getSession()->getPage();
      $nodes = $element->findAll('css', '.form-item label');
      foreach ($nodes as $node) {
        if ($node->getText() === $label) {
          $formItemMarkup = $node->getParent()->getHtml();
          if (strstr($formItemMarkup, 'disabled="disabled"')) {
            return;
          }
          else {
            throw new \Exception("Form item with label \"$label\" is not disabled.");
          }
        }
      }
      throw new \Behat\Mink\Exception\ElementNotFoundException($this->getSession(), 'form item', 'label', $label);
    }

    /**
     * @Given there are no attendees with CPR :arg1
     */
    public function thereAreNoAttendeesWithCpr($cpr)
    {
      $query = new EntityFieldQuery();
      $query->entityCondition('entity_type', 'node')
         ->fieldCondition('field_cpr_number', 'value', $cpr);
      $result = $query->execute();

      if (isset($result['node'])) {
        node_delete(key($result['node']));
      }
    }

    /**
     * @Given I go to attendee page for :attendeeName
     */
    public function iGoToAttendeePageFor($attendeeName)
    {
      $query = new EntityFieldQuery();
      $query->entityCondition('entity_type', 'node')
          ->propertyCondition('title', $attendeeName);
      $result = $query->execute();

      if (isset($result['node'])) {
        $this->getSession()->visit($this->getMinkParameter('base_url') . '/node/' . key($result['node']));
      }
      else {
        throw new \Exception("Attendee with name  \"$attendeeName\" is not found.");
      }
    }

  /**
   * @Given Valghalla testdata is available
   */
  public function valghallaTestdataIsAvailable()
  {
    // @Todo
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
        ->propertyCondition('title', 'Test Deltager No-Mail');

    $result = $query->execute();
    if (isset($result['node'])) {
      node_delete(key($result['node']));
    }

    $node = (object) array(
      'vid' => NULL,
      'uid' => '1',
      'title' => 'Test Deltager No-Mail',
      'log' => '',
      'status' => '1',
      'comment' => '0',
      'promote' => '1',
      'sticky' => '0',
      'nid' => NULL,
      'type' => 'volunteers',
      'language' => 'da',
      'created' => '1428566112',
      'changed' => '1428568628',
      'tnid' => '0',
      'translate' => '0',
      'revision_timestamp' => '1428568628',
      'revision_uid' => '1',
      'field_address_bnummer' => array(),
      'field_address_city' => array(),
      'field_address_coname' => array(),
      'field_address_door' => array(),
      'field_address_floor' => array(),
      'field_address_road' => array(),
      'field_address_road_no' => array(),
      'field_address_zipcode' => array(),
      'field_cpr_number' => array(
        'da' => array(
          array(
            'value' => '123456-1213',
            'format' => NULL,
            'safe_value' => '123456-1213',
          ),
        ),
      ),
      'field_cpr_valid_date' => array(),
      'field_diaet' => array(
        'da' => array(
          array(
            'value' => '750',
          ),
        ),
      ),
      'field_email' => array(
        'da' => array(
          array(
            'email' => 'valghalla@bellcom.dk',
          ),
        ),
      ),
      'field_label' => array(),
      'field_party' => array(
        'da' => array(
          array(
            'tid' => '3',
          ),
        ),
      ),
      'field_phone' => array(
        'da' => array(
          array(
            'value' => '0',
            'format' => NULL,
            'safe_value' => '0',
          ),
        ),
      ),
      'field_phone2' => array(),
      'field_polling_station' => array(),
      'field_polling_station_post' => array(),
      'field_rolle_id' => array(),
      'field_meeting_time' => array(),
      'field_ending_time' => array(),
      'field_cpr_status' => array(),
      'field_external_signup' => array(
        'und' => array(
          array(
            'value' => '0',
          ),
        ),
      ),
      'field_valid_state' => array(
        'und' => array(
          array(
            'value' => 'invalid',
          ),
        ),
      ),
      'field_volunteer_valid_date' => array(
        'und' => array(
          array(
            'value' => '2015-04-09 08:00:00',
            'timezone' => 'Europe/Copenhagen',
            'timezone_db' => 'UTC',
            'date_type' => 'datetime',
          ),
        ),
      ),
      'field_no_mail' => array(
        'und' => array(
          array(
            'value' => 1
          ),
        ),
      ),
      'name' => 'admin',
      'picture' => '0',
      'data' => 'a:7:{s:7:"contact";i:1;s:16:"ckeditor_default";s:1:"t";s:20:"ckeditor_show_toggle";s:1:"t";s:14:"ckeditor_width";s:4:"100%";s:13:"ckeditor_lang";s:2:"en";s:18:"ckeditor_auto_lang";s:1:"t";s:17:"mimemail_textonly";i:0;}',
    );
    node_save($node);

    $volunteer_no_mail_nid = $node->nid;

    return TRUE;
  }

    /**
     * @Given attendee :arg1 has Fritagelse for Digital post checked
     */
    public function attendeeHasFritagelseForDigitalPostChecked($arg1)
    {

      $query = new EntityFieldQuery();
      $query->entityCondition('entity_type', 'node')
          ->propertyCondition('title', $arg1);

      $result = $query->execute();
      if (isset($result['node'])) {
        $node = node_load(key($result['node']));

        if ($field = field_get_items('node', $node, 'field_no_mail')) {
          if ($field[0]['value'] == 0) {
            throw new \Exception("Attendee with name  \"$arg1\" does not have Fritagelse for Digital Post checked.");
          }
          else {
           $this->attendeeNid = $node->nid;
            return;
          }
        }
      }
      throw new \Exception("Attendee with name  \"$arg1\" does not exist.");
    }

    /**
     * @Then valghalla_mail_volunteer_no_mail() should return :arg1 for that user
     */
    public function valghallaMailVolunteerNoMailShouldReturnForThatUser($arg1)
    {
      $value = ($arg1 == "TRUE");

      if ($node = node_load($this->attendeeNid)) {
        $noMail = (bool)valghalla_mail_volunteer_no_mail($node);
        if ($noMail !== $value) {
          throw new \Exception("valghalla_mail_volunteer_no_mail() returned other than expected \"$arg1\"");
        }
        return;
      }
      throw new \Exception("Attendee with nid \"$this->attendeeNid\" does not exits.");
    }

    /**
     * @Given attendee :arg1 has Fritagelse for Digital post unchecked
     */
    public function attendeeHasFritagelseForDigitalPostUnchecked($arg1)
    {
      $query = new EntityFieldQuery();
      $query->entityCondition('entity_type', 'node')
          ->propertyCondition('title', $arg1);

      $result = $query->execute();
      if (isset($result['node'])) {
        $node = node_load(key($result['node']));

        if ($field = field_get_items('node', $node, 'field_no_mail')) {
          if ($field[0]['value'] == 1) {
            throw new \Exception("Attendee with name  \"$arg1\" does not have Fritagelse for Digital Post unchecked.");
          }
        }
        else {
          $this->attendeeNid = $node->nid;
          return;
        }
      }
      throw new \Exception("Attendee with name  \"$arg1\" does not exist.");
    }
}
