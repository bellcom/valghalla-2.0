Feature: Mails - Administrator role
  Users should be able to send mails using Valghalla

Background:
  Given I am on a large viewport
  Given Valghalla testdata is available
  # These variables tell mailsystem and mimemail modules to send
  # filtered_html mails.
  Given the following variables are set:
    | variable        | value                               |
    | mimemail_engine | mimemail                            |
    | mimemail_format | filtered_html                       |
    | mail_system     | {"default-system":"MimeMailSystem"} |


@mail @api @javascript
  Scenario: Admin user can see mail menu item
    Given I am logged in as a user with the "administrator" role
    And I go to "/"
    And I click "Administration"
    Then I should see "Send mails til deltagere"

@mail @api @javascript
  Scenario: Admin user can access send mail page
    Given I am logged in as a user with the "administrator" role
    And I go to "/valghalla/administration/sendmail"
    Then I should see "Opret E-mail"
    And I should see "Vælg en mailskabelon her:"
    And I should see "Navn på E-mail skabelon *"

@mail @api @javascript
  Scenario: It must be possible to send formatted mails.
    Given I am logged in as a user with the "administrator" role
    And I go to "/valghalla/administration/sendmail"
    # This is the body field, with a ckeditor instance
    Then I should see an "div#cke_edit-body-und-0-value" element
    And I should not see "Tekstformat"

@mail @api @javascript
  Scenario: It must be possible to preview a mail before it is sent.
    Given I am logged in as a user with the "administrator" role
    And I go to "/valghalla/administration/sendmail"
    And I fill in "Navn på E-mail skabelon *" with "Test"
    And I fill in "Emne" with "Test Emne"
    # Indhold field has id "edit-body-und-0-value"
    And I fill in wysiwyg on field "edit-body-und-0-value" with "Hej !name <br><a href='link'>Test mail link</a>"
    And I press "Næste"
    # Next step in mail sending form
    Then I should see "E-mail test oprettet."
    And I select "Testvalg" from "Valg"
    And I select "Ubesvaret" from "RSVP Status"
    And I select "TI" from "Frivillig type"
    And I select "A" from "Parti"
    And I select "Test Valgsted" from "Valgsted"
    And I press "Næste"
    # The preview page
    Then I should see "Test Deltager (valghalla@bellcom.dk)"
    And I click "Test Deltager (valghalla@bellcom.dk)"
    And I wait for AJAX to finish
    Then I should see "Hej Test Deltager"
    And I should see the link "Test mail link"
    And I press "Send"
    # Final step
    And I wait for the batch job to finish
    Then I should see "E-mails er blevet sendt"
