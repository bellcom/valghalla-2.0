Feature: Module: valghalla_volunteer_validator

Background:
  Given I am on a large viewport
  Given Valghalla testdata is available

@api @javascript
  Scenario: When name is fetched from the CPR service, the field must be disabled.
    Given I am logged in as a user with the "administrator" role
    # Variable value means do not fetch name from CPR service
    Given The variable "valghalla_volunteer_validator_get_name" is set to "0"
    And I go to "/valghalla/deltagere/alle"
    And I click "redigér"
    Then the "Navn *" field should not be disabled

    # Variable value means fetch name from CPR service
    Given The variable "valghalla_volunteer_validator_get_name" is set to "1"
    And I go to "/valghalla/deltagere/alle"
    And I click "redigér"
    Then the "Navn *" field should be disabled

@api @javascript
  # This test is dependant of https://cpr.dk/migrering-af-cpr-systemet/test/testpersoner-i-testmiljoeet/
  Scenario: Attendee name is fetched from CPR Service.
    Given I am logged in as a user with the "administrator" role
    Given there are no attendees with CPR "070761-4285"
    # Variable value means do not fetch name from CPR service
    Given The variable "valghalla_volunteer_validator_enable" is set to "1"
    Given The variable "valghalla_volunteer_validator_get_address" is set to "1"
    Given The variable "valghalla_volunteer_validator_get_name" is set to "1"
    And I go to "/valghalla/deltagere/tilfoej"
    Then the "Navn *" field should be disabled
    And I fill in "CPR Nummer *" with "070761-4285"
    And I fill in "Telefon *" with "12345678"
    And I fill in "Email *" with "testdeltager@bellcom.dk"
    And I press "Gem"
    Then I should see "Deltagere Jens Mortensen oprettet."
    And I go to "/valghalla/deltagere/alle"
    And I fill in "Navn" with "Jens Mortensen"
    And I press "Udfør"
    Then I should see "Jens Mortensen"
    And I should see "070761-4285"
