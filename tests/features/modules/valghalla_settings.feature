Feature: Module: valghalla_settings 

Background:
  Given I am on a large viewport
  Given Valghalla testdata is available

@api @javascript
  Scenario: Address fields must only be visible for "Partisekretær" according to the settings
    Given I am logged in as a user with the "Partisekretær" role
    # Variable value means show for all users
    Given The variable "valhalla_settings_hide_address_fields" is set to "0"
    And I go to "/valghalla/deltagere/alle"
    And I click "redigér"
    Then I should see a "Adresse" form element
    Then I should see a "Hus nr." form element
    Then I should see a "Sal" form element
    Then I should see a "Dør / side" form element
    Then I should see a "Postnr." form element
    Then I should see a "By" form element
    Then I should see a "CO Navn" form element

    # Variable value means hide for all users
    Given The variable "valhalla_settings_hide_address_fields" is set to "1"
    And I go to "/valghalla/deltagere/alle"
    And I click "redigér"
    Then I should not see a "Adresse" form element
    Then I should not see a "Hus nr." form element
    Then I should not see a "Sal" form element
    Then I should not see a "Dør / side" form element
    Then I should not see a "Postnr." form element
    Then I should not see a "By" form element
    Then I should not see a "CO Navn" form element

    # Variable value means show only for admin users
    Given The variable "valhalla_settings_hide_address_fields" is set to "2"
    And I go to "/valghalla/deltagere/alle"
    And I click "redigér"
    Then I should not see a "Adresse" form element
    Then I should not see a "Hus nr." form element
    Then I should not see a "Sal" form element
    Then I should not see a "Dør / side" form element
    Then I should not see a "Postnr." form element
    Then I should not see a "By" form element
    Then I should not see a "CO Navn" form element

@api @javascript
  Scenario: Address fields must only be visible for "administrator" according to the settings
    Given I am logged in as a user with the "administrator" role
    # Variable value means show for all users
    Given The variable "valhalla_settings_hide_address_fields" is set to "0"
    And I go to "/valghalla/deltagere/alle"
    And I click "redigér"
    Then I should see a "Adresse" form element
    Then I should see a "Hus nr." form element
    Then I should see a "Sal" form element
    Then I should see a "Dør / side" form element
    Then I should see a "Postnr." form element
    Then I should see a "By" form element
    Then I should see a "CO Navn" form element

    # Variable value means hide for all users
    Given The variable "valhalla_settings_hide_address_fields" is set to "1"
    And I go to "/valghalla/deltagere/alle"
    And I click "redigér"
    Then I should not see a "Adresse" form element
    Then I should not see a "Hus nr." form element
    Then I should not see a "Sal" form element
    Then I should not see a "Dør / side" form element
    Then I should not see a "Postnr." form element
    Then I should not see a "By" form element
    Then I should not see a "CO Navn" form element

    # Variable value means show only for admin users
    Given The variable "valhalla_settings_hide_address_fields" is set to "2"
    And I go to "/valghalla/deltagere/alle"
    And I click "redigér"
    Then I should see a "Adresse" form element
    Then I should see a "Hus nr." form element
    Then I should see a "Sal" form element
    Then I should see a "Dør / side" form element
    Then I should see a "Postnr." form element
    Then I should see a "By" form element
    Then I should see a "CO Navn" form element
