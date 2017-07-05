<?php
/**
 * @file
 * userform.ds.inc
 */

/**
 * Implements hook_ds_layout_settings_info().
 */
function userform_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'user|user|form';
  $ds_layout->entity_type = 'user';
  $ds_layout->bundle = 'user';
  $ds_layout->view_mode = 'form';
  $ds_layout->layout = 'ds_2col_stacked_fluid';
  $ds_layout->settings = array(
    'regions' => array(
      'footer' => array(
        0 => 'notify',
        1 => 'submit',
        7 => 'cancel',
        23 => 'account',
        24 => 'actions',
      ),
      'hidden' => array(
        2 => 'ckeditor_default',
        3 => 'language',
        4 => 'mimemail_textonly',
        6 => 'signature',
        8 => 'ckeditor_show_toggle',
        10 => 'picture_delete',
        11 => 'ckeditor_width',
        13 => 'picture_current',
        14 => 'ckeditor_lang',
        15 => 'picture_upload',
        18 => 'ckeditor_auto_lang',
        25 => 'picture',
        26 => 'signature_settings',
        27 => 'locale',
        28 => 'contact',
        29 => 'timezone',
        30 => 'mimemail',
        31 => 'ckeditor',
        32 => '_add_existing_field',
      ),
      'left' => array(
        5 => 'name',
        9 => 'field_full_name',
        12 => 'current_pass',
        16 => 'mail',
        17 => 'pass',
      ),
      'right' => array(
        19 => 'status',
        20 => 'roles',
        21 => 'field_party',
        22 => 'field_polling_station',
      ),
    ),
    'fields' => array(
      'notify' => 'footer',
      'submit' => 'footer',
      'ckeditor_default' => 'hidden',
      'language' => 'hidden',
      'mimemail_textonly' => 'hidden',
      'name' => 'left',
      'signature' => 'hidden',
      'cancel' => 'footer',
      'ckeditor_show_toggle' => 'hidden',
      'field_full_name' => 'left',
      'picture_delete' => 'hidden',
      'ckeditor_width' => 'hidden',
      'current_pass' => 'left',
      'picture_current' => 'hidden',
      'ckeditor_lang' => 'hidden',
      'picture_upload' => 'hidden',
      'mail' => 'left',
      'pass' => 'left',
      'ckeditor_auto_lang' => 'hidden',
      'status' => 'right',
      'roles' => 'right',
      'field_party' => 'right',
      'field_polling_station' => 'right',
      'account' => 'footer',
      'actions' => 'footer',
      'picture' => 'hidden',
      'signature_settings' => 'hidden',
      'locale' => 'hidden',
      'contact' => 'hidden',
      'timezone' => 'hidden',
      'mimemail' => 'hidden',
      'ckeditor' => 'hidden',
      '_add_existing_field' => 'hidden',
    ),
    'classes' => array(
      'layout_class' => array(
        '' => '',
      ),
      'right' => array(
        'well' => 'well',
      ),
    ),
    'wrappers' => array(
      'header' => 'div',
      'left' => 'div',
      'right' => 'div',
      'footer' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
    'layout_disable_css' => 0,
  );
  $export['user|user|form'] = $ds_layout;

  return $export;
}
