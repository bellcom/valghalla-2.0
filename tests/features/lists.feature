Feature: Lists - Administrator role
  Users should be able to see various attendee lists

Background:
  Given I am on a large viewport

@lists @api @javascript
  Scenario: Admin user can see "Deltagerlister" menu item
    Given I am logged in as a user with the "administrator" role
    And I go to "/"
    And I click "Lister"
    Then I should see "Deltagerlister"

@lists @api @javascript
  Scenario: Admin user can access "Deltagerlister"
    Given I am logged in as a user with the "administrator" role
    And I go to "/valghalla_lists/deltagere"
    And I select "Testvalg" from "edit-election"
    And I press "Vælg"
    Then I should see "Gem filtre"
    And I should see "Filtre" in the "#edit-filters" element

@lists @api @javascript
  Scenario: Admin user can save new "Deltagerlister" filter selection
    Given I am logged in as a user with the "administrator" role
    And I go to "/valghalla_lists/deltagere"
    And I select "Testvalg" from "edit-election"
    And I press "Vælg"
    And I fill in "Navn på filter" with "test-filter"
    And I click all ".js-select-all"
    And I press "Gem"
    Then I should see "test-filter" in the "#edit-filters" element
    
@lists @api @javascript
  Scenario: When selecting a saved filter, the list should be loaded
    Given I am logged in as a user with the "administrator" role
    And I go to "/valghalla_lists/deltagere"
    And I select "Testvalg" from "edit-election"
    And I press "Vælg"
    And I click "test-filter"
    Then I should see a "table" element
