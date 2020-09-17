<?php

/**
 * @file
 * Handles the Valghalla notifications entity.
 */

module_load_include('inc', 'valghalla_notifications', 'includes/EntityValghallaNotificationControllerInterface');
module_load_include('inc', 'valghalla_notifications', 'includes/EntityValghallaNotificationController');

/**
 * Fetch a valghalla_notification object.
 *
 * This function ends up being a shim between the menu system and
 * entity_valghalla_notification_load_multiple().
 *
 * @param int $id
 *   Integer specifying the valghalla_notification entity id.
 * @param bool $reset
 *   A boolean indicating that the internal cache should be reset.
 *
 * @return mixed
 *   A fully-loaded entity object or FALSE if it cannot be loaded.
 *
 * @see entity_valghalla_notification_load_multiple()
 */
function entity_valghalla_notification_load($id = NULL, $reset = FALSE) {
  $ids = (isset($id) ? array($id) : array());
  $valghalla_notification = entity_valghalla_notification_load_multiple($ids, array(), $reset);
  return $valghalla_notification ? reset($valghalla_notification) : FALSE;
}

/**
 * Loads multiple valghalla_notification entities.
 *
 * We only need to pass this request along to entity_load(), which
 * will in turn call the load() method of our entity controller class.
 */
function entity_valghalla_notification_load_multiple($ids = FALSE, $conditions = array(), $reset = FALSE) {
  return entity_load('entity_valghalla_notification', $ids, $conditions, $reset);
}

/**
 * Implements the uri callback.
 */
function entity_valghalla_notification_uri($valghalla_notification) {
  return array(
    'path' => 'valghalla/administration/notifications/' . $valghalla_notification->id,
  );
}

/**
 * Defines Valghalla Notification Entity menu items.
 */
function entity_valghalla_menu(&$items) {
  $items['valghalla/administration/notifications-list'] = array(
    'title' => 'Kommunikationslog',
    'page callback' => 'entity_valghalla_notification_list_entities',
    'access arguments' => array('view any valghalla notification entity'),
    'type' => MENU_NORMAL_ITEM,

  );

  // The page to view our entities - needs to follow what
  // is defined in entity_valghalla_notification_uri and will use
  // to retrieve the necessary entity info.
  $items['valghalla/administration/notifications-list/%entity_valghalla_notification'] = array(
    'title callback' => 'entity_valghalla_notification_title',
    'title arguments' => array(3),
    'page callback' => 'entity_valghalla_notification_view',
    'page arguments' => array(3),
    'access callback' => 'entity_valghalla_notification_check_notification_view_access',
    'access arguments' => array(3),
  );

  // 'View' tab for an individual entity page.
  $items['valghalla/administration/notifications-list/%entity_valghalla_notification/view'] = array(
    'title' => 'View',
    'type' => MENU_DEFAULT_LOCAL_TASK,
    'weight' => -10,
  );

  // 'Remove' tab for an individual entity page.
  $items['valghalla/administration/notifications-list/%entity_valghalla_notification/remove'] = array(
    'title' => 'Remove',
    'page callback' => 'drupal_get_form',
    'page arguments' => array(
      'entity_valghalla_notification_confirm_delete',
      3,
    ),
    'access callback' => 'entity_valghalla_notification_check_notification_delete_access',
    'access arguments' => array(3),
    'type' => MENU_LOCAL_TASK,
  );

  $items['node/%/notifications'] = array(
    'title callback' => 'entity_valghalla_notification_notification_tab_title',
    'page callback' => 'entity_valghalla_notification_list_entities',
    'page arguments' => array(1),
    'access callback' => 'entity_valghalla_notification_check_volunteer_notifications_access',
    'access arguments' => array(1),
    'type' => MENU_LOCAL_TASK,
    'weight' => 1,
  );

  return $items;
}

/**
 * Basic information for the page.
 */
function entity_valghalla_notification_info_page() {
  if (user_access('administer valghalla notification entities')) {
    $content['table'] = entity_valghalla_notification_list_entities();
  }

  return $content;
}

/**
 * Checks access to volunteer notifications.
 */
function entity_valghalla_notification_check_volunteer_notifications_access($nid) {
  $node = node_load($nid);

  // Taking care of notification with no volunteer.
  if (!$node) {
    if (user_access('view any valghalla notification entity') && user_access('valghalla see all parties')) {
      return TRUE;
    }
  }

  if (($node->type == 'volunteers')
    && user_access('view any valghalla notification entity')) {
    // User can see notification for all volunteers.
    if (user_access('valghalla see all parties')) {
      return TRUE;
    }
    else {
      // Check if the volunteer party is the same as the current user party.
      global $user;
      $current_user = user_load($user->uid);
      $current_user_party_id = empty($current_user->field_party[LANGUAGE_NONE][0]['tid']) ? FALSE : $current_user->field_party[LANGUAGE_NONE][0]['tid'];

      $field_party = field_get_items('node', $node, 'field_party');
      if (!empty($field_party)) {
        $volunteer_party_id = $field_party[0]['tid'];

        if (intval($volunteer_party_id) == intval($current_user_party_id)) {
          return TRUE;
        }
      }
    }
  }
  return FALSE;
}

/**
 * Checks access to view notification.
 */
function entity_valghalla_notification_check_notification_view_access($notification) {
  return entity_valghalla_notification_check_volunteer_notifications_access($notification->vol_id);
}

/**
 * Checks access to delete notification.
 */
function entity_valghalla_notification_check_notification_delete_access($notification) {
  if (entity_valghalla_notification_check_volunteer_notifications_access($notification->vol_id)) {
    if (user_access('administer valghalla notification entities')) {
      return TRUE;
    }
  }
  return FALSE;
}

/**
 * Generates notification tab title with notification counter.
 */
function entity_valghalla_notification_notification_tab_title() {
  $query = new EntityFieldQuery();
  $notification_ids = $query->entityCondition('entity_type', 'entity_valghalla_notification')
    ->propertyOrderBy('created', 'DESC')
    ->propertyCondition('vol_id', arg(1))
    ->execute();
  $count = empty($notification_ids) ? 0 : count(reset($notification_ids));
  return t('Kommunikationslog (@count)', array('@count' => $count));
}

/**
 * Returns a render array with all entity_valghalla_notification entities.
 */
function entity_valghalla_notification_list_entities($vol_nid = FALSE) {
  $content = array();

  // Load all of our entities.
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'entity_valghalla_notification')
    ->propertyOrderBy('created', 'DESC')
    ->pager(20);

  // Limiting volunteers to current user party, if only user does not have a
  // certain permission = 'valghalla see all parties'.
  if (!user_access('valghalla see all parties')) {
    global $user;
    $current_user = user_load($user->uid);
    $current_user_party_id = empty($current_user->field_party[LANGUAGE_NONE][0]['tid']) ? FALSE : $current_user->field_party[LANGUAGE_NONE][0]['tid'];
    if ($current_user_party_id) {
      $party_volunteers_subquery = db_select('field_data_field_party', 'fp');
      $party_volunteers_subquery->fields('fp', array('entity_id'));
      $party_volunteers_subquery->condition('bundle', 'volunteers');
      $party_volunteers_subquery->condition('field_party_tid', $current_user_party_id);

      $query->propertyCondition('vol_id', $party_volunteers_subquery, 'IN');
    }
  }

  $headers[] = t('ID');
  $headers[] = t('Gateway');
  $headers[] = t('Type');
  if ($vol_nid) {
    $query->propertyCondition('vol_id', $vol_nid);
  }
  else {
    $headers[] = t('Deltager');
  }
  $headers[] = t('Modtager');
  $headers[] = t('Besked');
  $headers[] = t('Tidspunkt');
  $headers[] = t('Status');
  $headers[] = t('Operations');
  $result = $query->execute();
  $ids = reset($result);
  if (!empty($ids)) {
    $entities = entity_valghalla_notification_load_multiple(array_keys($ids));

    // Does user have delete permissions?
    $can_delete_notifications = user_access('administer valghalla notification entities');
    foreach ($entities as $entity) {
      $message = strip_tags(str_replace('<br/>', '  ', $entity->message));
      $row = $row_data = array();
      $row_data['id'] = l($entity->id, 'valghalla/administration/notifications-list/' . $entity->id);
      $row_data['gateway'] = check_plain($entity->gateway);
      $row_data['type'] = check_plain($entity->type);
      if (!$vol_nid) {
        $row_data['volunteer'] = entity_valghalla_notification_volunteer_view($entity->vol_id);
      }
      $row_data['to'] = check_plain($entity->recipient);
      $row_data['message'] = substr($message, 0, 50);
      $row_data['created'] = format_date($entity->created, 'short');
      $row_data['status'] = check_plain($entity->status);

      $operation_links = array(
        array(
          'title' => t('View'),
          'href' => 'valghalla/administration/notifications-list/' . $entity->id,
        ),
      );

      // Adding remove link.
      if ($can_delete_notifications) {
        $operation_links[] = array(
          'title' => t('Remove'),
          'href' => 'valghalla/administration/notifications-list/' . $entity->id . '/remove',
        );
      }

      $row_data['operations'] = theme('links__ctools_dropbutton', array(
        'links' => $operation_links,
      ));

      $row['data'] = $row_data;
      if (strtolower($entity->status) == 'failed') {
        $row['class'] = 'failed danger';
      }
      $rows[] = $row;
    }
    // Put our entities into a themed table. See theme_table() for details.
    $content['entity_table'] = array(
      '#theme' => 'table',
      '#rows' => $rows,
      '#header' => $headers,
    );
  }
  else {
    // There were no entities. Tell the user.
    $content[] = array(
      '#type' => 'item',
      '#markup' => t('Ingen resultater.'),
    );
  }
  $content['pager'] = array('#theme' => 'pager');
  return $content;
}

/**
 * Callback for a page title when this entity is displayed.
 */
function entity_valghalla_notification_title($entity) {
  return t('Kommunikationslog (id=@id)', array('@id' => $entity->id));
}

/**
 * Menu callback to display an entity.
 *
 * As we load the entity for display, we're responsible for invoking a number
 * of hooks in their proper order.
 *
 * @see hook_entity_prepare_view()
 * @see hook_entity_view()
 * @see hook_entity_view_alter()
 */
function entity_valghalla_notification_view($entity, $view_mode = 'default') {
  // Our entity type, for convenience.
  $entity_type = 'entity_valghalla_notification';
  // Start setting up the content.
  $entity->content = array(
    '#view_mode' => $view_mode,
  );
  // Build fields content - this is where the Field API really comes in to play.
  // The task has very little code here because it all gets taken care of by
  // field module.
  // field_attach_prepare_view() lets the fields load any data they need
  // before viewing.
  field_attach_prepare_view($entity_type, array($entity->id => $entity),
    $view_mode);
  // We call entity_prepare_view() so it can invoke hook_entity_prepare_view()
  // for us.
  entity_prepare_view($entity_type, array($entity->id => $entity));
  // Now field_attach_view() generates the content for the fields.
  $entity->content += field_attach_view($entity_type, $entity, $view_mode);

  $entity->content['created'] = array(
    '#type' => 'item',
    '#title' => t('Afsendelses dato'),
    '#markup' => format_date($entity->created),
  );
  $entity->content['type'] = array(
    '#type' => 'item',
    '#title' => t('Notifikation type'),
    '#markup' => $entity->type,
  );
  $entity->content['recipient'] = array(
    '#type' => 'item',
    '#title' => t('Modtager'),
    '#markup' => $entity->recipient,
  );
  $entity->content['message'] = array(
    '#type' => 'item',
    '#title' => t('Besked'),
    '#markup' => $entity->message,
  );
  $entity->content['gateway'] = array(
    '#type' => 'item',
    '#title' => t('Gateway'),
    '#markup' => $entity->gateway,
  );
  $entity->content['volunteer'] = array(
    '#type' => 'item',
    '#title' => t('Deltager'),
    '#markup' => entity_valghalla_notification_volunteer_view($entity->vol_id),
  );
  $entity->content['status'] = array(
    '#type' => 'item',
    '#title' => t('Status'),
    '#markup' => $entity->status,
  );
  if (!empty($entity->status_info)) {
    $entity->content['status_info'] = array(
      '#type' => 'item',
      '#title' => t('Status details'),
      '#markup' => htmlspecialchars($entity->status_info),
    );
  }

  // Now to invoke some hooks. We need the language code for
  // hook_entity_view(), so let's get that.
  global $language;
  $langcode = $language->language;

  // And now invoke hook_entity_view().
  module_invoke_all('entity_view', $entity, $entity_type, $view_mode,
    $langcode);
  // Now invoke hook_entity_view_alter().
  drupal_alter(array('valghalla_notification_view', 'entity_view'),
    $entity->content, $entity_type);

  // And finally return the content.
  return $entity->content;
}

/**
 * Implements hook_field_extra_fields().
 *
 * This exposes the "extra fields" (usually properties that can be configured
 * as if they were fields) of the entity as pseudo-fields
 * so that they get handled by the Entity and Field core functionality.
 * Node titles get treated in a similar manner.
 */
function valghalla_notification_field_extra_fields() {
  $form_elements = array(
    'type' => array('label' => t('Type')),
    'vol_id' => array('label' => t('Deltager id')),
    'to' => array('label' => t('Modtager')),
    'message' => array('label' => t('Besked')),
    'gateway' => array('label' => t('Gateway')),
    'status' => array('label' => t('Status')),
    'status_info' => array('label' => t('Status info')),
  );
  $display_elements = array(
    'type' => array('label' => t('Type')),
    'vol_id' => array('label' => t('Deltager id')),
    'to' => array('label' => t('Modtager')),
    'message' => array('label' => t('Besked')),
    'gateway' => array('label' => t('Gateway')),
    'status' => array('label' => t('Status')),
    'status_info' => array('label' => t('Status info')),
    'created' => array('label' => t('Afsendelses dato')),
  );

  // Since we have only one bundle type, we'll just provide the extra_fields
  // for it here.
  $extra_fields['entity_valghalla_notification']['default_bundle']['form'] = $form_elements;
  $extra_fields['entity_valghalla_notification']['default_bundle']['display'] = $display_elements;

  return $extra_fields;
}

/**
 * Form builder for the valghalla_notification delete confirmation form.
 */
function entity_valghalla_notification_confirm_delete($form, &$form_state, $notification) {
  $form['notification_id'] = array('#type' => 'value', '#value' => $notification->id);
  $form_state['storage']['notification'] = $notification;
  return confirm_form($form,
    t('Delete notification'),
    'admin/structure/entity_valghalla_notification/manage',
    t('Are you sure you want to delete the notification %id?',
    array('%id' => $notification->id)));
}

/**
 * Submit handler to delete a valghalla_notification after confirmation.
 */
function entity_valghalla_notification_confirm_delete_submit($form, &$form_state) {
  $form_state['storage']['notification']->delete();
  drupal_set_message(t('Deleted notification %id.', array('%id' => $form_state['values']['notification_id'])));
  $form_state['redirect'] = 'valghalla/administration/notifications/list';
}

/**
 * View function for volunteer id value.
 */
function entity_valghalla_notification_volunteer_view($vol_id) {
  switch ($vol_id) {
    case '-1':
      $output = 'copy';
      break;

    default:
      $volunteer = node_load($vol_id);
      $output = empty($volunteer) ? 'N/A' : l($volunteer->title, 'node/' . $volunteer->nid, array(
        'attributes' => array('target' => '_blank'),
      ));
  }
  return $output;
}
