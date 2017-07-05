<?php
/**
 * @file
 * userform.rel.inc
 */

/**
 * Implements hook_rel_build_info().
 */
function userform_rel_build_info() {
  $export = array();

  $rel = new stdClass();
  $rel->api_version = 1;
  $rel->build_id = 'user_profile_form';
  $rel->label = 'user_profile_form';
  $rel->entity_type = 'user';
  $rel->bundle = 'user';
  $rel->view_mode = 'form';
  $rel->context = 'form';
  $rel->path = 'admin/config/people/accounts/fields';
  $rel->elements = array(
    'account' => array(
      'owner' => 'drupal',
      'label' => 'Account',
      'parent' => '',
      'group_info' => array(
        'format_type' => 'div',
        'format_settings' => array(
          'formatter' => 'open',
          'instance_settings' => array(
            'show_label' => FALSE,
          ),
        ),
        'label' => 'Div',
        'description' => 'This fieldgroup renders the inner content in a simple div with the title as legend.',
        'format_types' => array(
          0 => 'open',
          1 => 'collapsible',
          2 => 'collapsed',
        ),
        'instance_settings' => array(
          'description' => '',
          'show_label' => 1,
          'label_element' => 'h3',
          'effect' => 'none',
          'speed' => 'fast',
          'classes' => '',
          'required_fields' => 1,
          'id' => '',
        ),
        'default_formatter' => 'open',
      ),
      'weight' => -10,
      'element_type' => 'container',
    ),
    'name' => array(
      'owner' => 'rel',
      'label' => 'Brugernavn',
      'parent' => 'account',
      'group_info' => FALSE,
      'weight' => -10,
      'element_type' => 'textfield',
    ),
    'mail' => array(
      'owner' => 'rel',
      'label' => 'E-mail-adresse',
      'parent' => 'account',
      'group_info' => FALSE,
      'weight' => 0,
      'element_type' => 'textfield',
    ),
    'pass' => array(
      'owner' => 'rel',
      'label' => 'Pass',
      'parent' => 'account',
      'group_info' => FALSE,
      'weight' => 1,
      'element_type' => 'password_confirm',
    ),
    'current_pass' => array(
      'owner' => 'rel',
      'label' => 'Nuværende adgangskode',
      'parent' => 'account',
      'group_info' => FALSE,
      'weight' => -5,
      'element_type' => 'password',
    ),
    'status' => array(
      'owner' => 'rel',
      'label' => 'Status',
      'parent' => 'account',
      'group_info' => FALSE,
      'weight' => 2,
      'element_type' => 'radios',
    ),
    'roles' => array(
      'owner' => 'rel',
      'label' => 'Roller',
      'parent' => 'account',
      'group_info' => FALSE,
      'weight' => 3,
      'element_type' => 'checkboxes',
    ),
    'notify' => array(
      'owner' => 'rel',
      'label' => 'Påmind bruger om ny konto',
      'parent' => 'account',
      'group_info' => FALSE,
      'weight' => 4,
      'element_type' => 'checkbox',
    ),
    'signature_settings' => array(
      'owner' => 'rel',
      'label' => 'Indstillinger for signatur',
      'parent' => '',
      'group_info' => array(
        'format_type' => 'fieldset',
        'format_settings' => array(),
        'label' => 'Feltgruppe',
        'description' => 'This fieldgroup renders the inner content in a fieldset with the title as legend.',
        'format_types' => array(
          0 => 'open',
          1 => 'collapsible',
          2 => 'collapsed',
        ),
        'instance_settings' => array(
          'description' => '',
          'classes' => '',
          'required_fields' => 1,
        ),
        'default_formatter' => 'collapsible',
      ),
      'weight' => 1,
      'element_type' => 'fieldset',
    ),
    'signature' => array(
      'owner' => 'rel',
      'label' => 'Signatur',
      'parent' => 'signature_settings',
      'group_info' => FALSE,
      'weight' => 0,
      'element_type' => 'text_format',
    ),
    'picture' => array(
      'owner' => 'rel',
      'label' => 'Billede',
      'parent' => '',
      'group_info' => array(
        'format_type' => 'fieldset',
        'format_settings' => array(),
        'label' => 'Feltgruppe',
        'description' => 'This fieldgroup renders the inner content in a fieldset with the title as legend.',
        'format_types' => array(
          0 => 'open',
          1 => 'collapsible',
          2 => 'collapsed',
        ),
        'instance_settings' => array(
          'description' => '',
          'classes' => '',
          'required_fields' => 1,
        ),
        'default_formatter' => 'collapsible',
      ),
      'weight' => 1,
      'element_type' => 'fieldset',
    ),
    'picture_current' => array(
      'owner' => 'rel',
      'label' => 'Picture current',
      'parent' => 'picture',
      'group_info' => FALSE,
      'weight' => 0,
      'element_type' => '',
    ),
    'picture_delete' => array(
      'owner' => 'rel',
      'label' => 'Slet billede',
      'parent' => 'picture',
      'group_info' => FALSE,
      'weight' => 1,
      'element_type' => 'checkbox',
    ),
    'picture_upload' => array(
      'owner' => 'rel',
      'label' => 'Upload billede',
      'parent' => 'picture',
      'group_info' => FALSE,
      'weight' => 2,
      'element_type' => 'file',
    ),
    'field_full_name' => array(
      'owner' => 'drupal',
      'label' => 'Field full name',
      'parent' => '',
      'group_info' => FALSE,
      'weight' => '1',
      'element_type' => 'container',
    ),
    'field_party' => array(
      'owner' => 'drupal',
      'label' => 'Field party',
      'parent' => '',
      'group_info' => FALSE,
      'weight' => '6',
      'element_type' => 'container',
    ),
    'field_polling_station' => array(
      'owner' => 'drupal',
      'label' => 'Field polling station',
      'parent' => '',
      'group_info' => FALSE,
      'weight' => '7',
      'element_type' => 'container',
    ),
    'actions' => array(
      'owner' => 'rel',
      'label' => 'Actions',
      'parent' => '',
      'group_info' => array(
        'format_type' => 'div',
        'format_settings' => array(
          'formatter' => 'open',
          'instance_settings' => array(
            'show_label' => FALSE,
          ),
        ),
        'label' => 'Div',
        'description' => 'This fieldgroup renders the inner content in a simple div with the title as legend.',
        'format_types' => array(
          0 => 'open',
          1 => 'collapsible',
          2 => 'collapsed',
        ),
        'instance_settings' => array(
          'description' => '',
          'show_label' => 1,
          'label_element' => 'h3',
          'effect' => 'none',
          'speed' => 'fast',
          'classes' => '',
          'required_fields' => 1,
          'id' => '',
        ),
        'default_formatter' => 'open',
      ),
      'weight' => 100,
      'element_type' => 'actions',
    ),
    'submit' => array(
      'owner' => 'rel',
      'label' => 'Gem',
      'parent' => 'actions',
      'group_info' => FALSE,
      'weight' => 0,
      'element_type' => 'submit',
    ),
    'cancel' => array(
      'owner' => 'rel',
      'label' => 'Opsig konto',
      'parent' => 'actions',
      'group_info' => FALSE,
      'weight' => 1,
      'element_type' => 'submit',
    ),
    'ckeditor' => array(
      'owner' => 'drupal',
      'label' => 'Rich text editor settings',
      'parent' => '',
      'group_info' => array(
        'format_type' => 'fieldset',
        'format_settings' => array(
          'formatter' => 'collapsed',
        ),
        'label' => 'Feltgruppe',
        'description' => 'This fieldgroup renders the inner content in a fieldset with the title as legend.',
        'format_types' => array(
          0 => 'open',
          1 => 'collapsible',
          2 => 'collapsed',
        ),
        'instance_settings' => array(
          'description' => '',
          'classes' => '',
          'required_fields' => 1,
        ),
        'default_formatter' => 'collapsible',
      ),
      'weight' => 10,
      'element_type' => 'fieldset',
    ),
    'ckeditor_default' => array(
      'owner' => 'rel',
      'label' => 'Standardtilstand',
      'parent' => 'ckeditor',
      'group_info' => FALSE,
      'weight' => 0,
      'element_type' => 'radios',
    ),
    'ckeditor_show_toggle' => array(
      'owner' => 'rel',
      'label' => 'Show the disable/enable rich text editor toggle',
      'parent' => 'ckeditor',
      'group_info' => FALSE,
      'weight' => 1,
      'element_type' => 'radios',
    ),
    'ckeditor_width' => array(
      'owner' => 'rel',
      'label' => 'Editor width',
      'parent' => 'ckeditor',
      'group_info' => FALSE,
      'weight' => 2,
      'element_type' => 'textfield',
    ),
    'ckeditor_lang' => array(
      'owner' => 'rel',
      'label' => 'Sprog',
      'parent' => 'ckeditor',
      'group_info' => FALSE,
      'weight' => 3,
      'element_type' => 'select',
    ),
    'ckeditor_auto_lang' => array(
      'owner' => 'rel',
      'label' => 'Auto-detect language',
      'parent' => 'ckeditor',
      'group_info' => FALSE,
      'weight' => 4,
      'element_type' => 'radios',
    ),
    'contact' => array(
      'owner' => 'drupal',
      'label' => 'Personlig kontaktformular',
      'parent' => 'contact',
      'group_info' => FALSE,
      'weight' => 0,
      'element_type' => 'checkbox',
    ),
    'locale' => array(
      'owner' => 'drupal',
      'label' => 'Sprogindstillinger',
      'parent' => '',
      'group_info' => array(
        'format_type' => 'fieldset',
        'format_settings' => array(),
        'label' => 'Feltgruppe',
        'description' => 'This fieldgroup renders the inner content in a fieldset with the title as legend.',
        'format_types' => array(
          0 => 'open',
          1 => 'collapsible',
          2 => 'collapsed',
        ),
        'instance_settings' => array(
          'description' => '',
          'classes' => '',
          'required_fields' => 1,
        ),
        'default_formatter' => 'collapsible',
      ),
      'weight' => 1,
      'element_type' => 'fieldset',
    ),
    'language' => array(
      'owner' => 'rel',
      'label' => 'Sprog',
      'parent' => 'locale',
      'group_info' => FALSE,
      'weight' => 0,
      'element_type' => 'radios',
    ),
    'mimemail' => array(
      'owner' => 'drupal',
      'label' => 'Indstillinger for e-mail',
      'parent' => '',
      'group_info' => array(
        'format_type' => 'fieldset',
        'format_settings' => array(),
        'label' => 'Feltgruppe',
        'description' => 'This fieldgroup renders the inner content in a fieldset with the title as legend.',
        'format_types' => array(
          0 => 'open',
          1 => 'collapsible',
          2 => 'collapsed',
        ),
        'instance_settings' => array(
          'description' => '',
          'classes' => '',
          'required_fields' => 1,
        ),
        'default_formatter' => 'collapsible',
      ),
      'weight' => 5,
      'element_type' => 'fieldset',
    ),
    'mimemail_textonly' => array(
      'owner' => 'rel',
      'label' => 'Kun e-mail i ren tekst',
      'parent' => 'mimemail',
      'group_info' => FALSE,
      'weight' => 0,
      'element_type' => 'checkbox',
    ),
  );
  $rel->duplicate = array();
  $export['user_profile_form'] = $rel;

  return $export;
}
