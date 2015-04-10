Feature: Login
  Users should be able to login
@user @api @javascript
  Scenario: User login
    Given I am logged in as a user with the "administrator" role
    And I go to "/user"
    Then I should see "Historik"

@user @javascript
  Scenario: Anonymous users are not allowed to see the frontpage
    Given I go to "/"
    Then I should see "Brugerkonto"
