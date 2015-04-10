Feature: Volunteers

Background:
  Given I am on a large viewport
  Given Valghalla testdata is available

@api @javascript
  Scenario: Checkbox for "Fritagelse for Digital post" is on the volunteer form
    Given I am logged in as a user with the "administrator" role
    And I go to "/valghalla/deltagere/alle"
    And I click "redigér"
    Then I should see a "Fritagelse for Digital Post" form element

@api @javascript
  Scenario: If the attendee has "Fritagelse for Digital post" this should be shown on the node view page
    Given I am logged in as a user with the "administrator" role
    And I go to attendee page for "Test Deltager No-Mail"
    Then I should see "Deltageren er fritaget for digital post"

@api @test
  Scenario: When an attendee has "Fritagelse for Digital post" checked, valghalla_mail should not send
    him/her mails.

   Given attendee "Test Deltager No-Mail" has Fritagelse for Digital post checked
   Then valghalla_mail_volunteer_no_mail() should return "TRUE" for that user

@api @test
  Scenario: When an attendee has "Fritagelse for Digital post" unchecked, valghalla_mail should send
    him/her mails.

   Given attendee "Test Deltager" has Fritagelse for Digital post unchecked
   Then valghalla_mail_volunteer_no_mail() should return "FALSE" for that user
