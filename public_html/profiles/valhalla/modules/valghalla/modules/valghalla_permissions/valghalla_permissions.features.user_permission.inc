<?php
/**
 * @file
 * valghalla_permissions.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function valghalla_permissions_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access content'.
  $permissions['access content'] = array(
    'name' => 'access content',
    'roles' => array(
      'Brevstemme administrator' => 'Brevstemme administrator',
      'Partisekretær' => 'Partisekretær',
      'admin' => 'admin',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'access content overview'.
  $permissions['access content overview'] = array(
    'name' => 'access content overview',
    'roles' => array(
      'Brevstemme administrator' => 'Brevstemme administrator',
      'Valgsekretær' => 'Valgsekretær',
      'admin' => 'admin',
    ),
    'module' => 'node',
  );

  // Exported permission: 'access entire user profile form'.
  $permissions['access entire user profile form'] = array(
    'name' => 'access entire user profile form',
    'roles' => array(
      'admin' => 'admin',
    ),
    'module' => 'valghalla_volunteers',
  );

  // Exported permission: 'access user profiles'.
  $permissions['access user profiles'] = array(
    'name' => 'access user profiles',
    'roles' => array(
      'admin' => 'admin',
    ),
    'module' => 'user',
  );

  // Exported permission: 'add volunteer to station'.
  $permissions['add volunteer to station'] = array(
    'name' => 'add volunteer to station',
    'roles' => array(
      'Brevstemme administrator' => 'Brevstemme administrator',
      'Partisekretær' => 'Partisekretær',
      'Valgsekretær' => 'Valgsekretær',
      'admin' => 'admin',
    ),
    'module' => 'valghalla_volunteers',
  );

  // Exported permission: 'add volunteers'.
  $permissions['add volunteers'] = array(
    'name' => 'add volunteers',
    'roles' => array(
      'Brevstemme administrator' => 'Brevstemme administrator',
      'Partisekretær' => 'Partisekretær',
      'Valgsekretær' => 'Valgsekretær',
      'admin' => 'admin',
    ),
    'module' => 'valghalla_volunteers',
  );

  // Exported permission: 'administer content types'.
  $permissions['administer content types'] = array(
    'name' => 'administer content types',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'administer nodes'.
  $permissions['administer nodes'] = array(
    'name' => 'administer nodes',
    'roles' => array(
      'admin' => 'admin',
    ),
    'module' => 'node',
  );

  // Exported permission: 'administer permissions'.
  $permissions['administer permissions'] = array(
    'name' => 'administer permissions',
    'roles' => array(
      'admin' => 'admin',
    ),
    'module' => 'user',
  );

  // Exported permission: 'administer sub secretaries'.
  $permissions['administer sub secretaries'] = array(
    'name' => 'administer sub secretaries',
    'roles' => array(
      'admin' => 'admin',
    ),
    'module' => 'valghalla_volunteers',
  );

  // Exported permission: 'administer users'.
  $permissions['administer users'] = array(
    'name' => 'administer users',
    'roles' => array(
      'admin' => 'admin',
    ),
    'module' => 'user',
  );

  // Exported permission: 'administer valghalla'.
  $permissions['administer valghalla'] = array(
    'name' => 'administer valghalla',
    'roles' => array(
      'admin' => 'admin',
    ),
    'module' => 'valghalla_volunteers',
  );

  // Exported permission: 'assign Brevstemme administrator role'.
  $permissions['assign Brevstemme administrator role'] = array(
    'name' => 'assign Brevstemme administrator role',
    'roles' => array(),
    'module' => 'role_delegation',
  );

  // Exported permission: 'assign Partisekretær role'.
  $permissions['assign Partisekretær role'] = array(
    'name' => 'assign Partisekretær role',
    'roles' => array(
      'Partisekretær' => 'Partisekretær',
      'Valgsekretær' => 'Valgsekretær',
    ),
    'module' => 'role_delegation',
  );

  // Exported permission: 'assign Valgsekretær role'.
  $permissions['assign Valgsekretær role'] = array(
    'name' => 'assign Valgsekretær role',
    'roles' => array(),
    'module' => 'role_delegation',
  );

  // Exported permission: 'assign admin role'.
  $permissions['assign admin role'] = array(
    'name' => 'assign admin role',
    'roles' => array(),
    'module' => 'role_delegation',
  );

  // Exported permission: 'assign all roles'.
  $permissions['assign all roles'] = array(
    'name' => 'assign all roles',
    'roles' => array(),
    'module' => 'role_delegation',
  );

  // Exported permission: 'bypass node access'.
  $permissions['bypass node access'] = array(
    'name' => 'bypass node access',
    'roles' => array(
      'admin' => 'admin',
    ),
    'module' => 'node',
  );

  // Exported permission: 'cancel account'.
  $permissions['cancel account'] = array(
    'name' => 'cancel account',
    'roles' => array(),
    'module' => 'user',
  );

  // Exported permission: 'change own username'.
  $permissions['change own username'] = array(
    'name' => 'change own username',
    'roles' => array(
      'admin' => 'admin',
    ),
    'module' => 'user',
  );

  // Exported permission: 'change volunteers rsvp'.
  $permissions['change volunteers rsvp'] = array(
    'name' => 'change volunteers rsvp',
    'roles' => array(
      'Brevstemme administrator' => 'Brevstemme administrator',
      'Partisekretær' => 'Partisekretær',
      'Valgsekretær' => 'Valgsekretær',
      'admin' => 'admin',
    ),
    'module' => 'valghalla_volunteers',
  );

  // Exported permission: 'create constituency content'.
  $permissions['create constituency content'] = array(
    'name' => 'create constituency content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'create election content'.
  $permissions['create election content'] = array(
    'name' => 'create election content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'create email content'.
  $permissions['create email content'] = array(
    'name' => 'create email content',
    'roles' => array(
      'Valgsekretær' => 'Valgsekretær',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create panel content'.
  $permissions['create panel content'] = array(
    'name' => 'create panel content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'create polling_station content'.
  $permissions['create polling_station content'] = array(
    'name' => 'create polling_station content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'create roles content'.
  $permissions['create roles content'] = array(
    'name' => 'create roles content',
    'roles' => array(
      'Valgsekretær' => 'Valgsekretær',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create volunteers content'.
  $permissions['create volunteers content'] = array(
    'name' => 'create volunteers content',
    'roles' => array(
      'Brevstemme administrator' => 'Brevstemme administrator',
      'Partisekretær' => 'Partisekretær',
      'Valgsekretær' => 'Valgsekretær',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any constituency content'.
  $permissions['delete any constituency content'] = array(
    'name' => 'delete any constituency content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete any election content'.
  $permissions['delete any election content'] = array(
    'name' => 'delete any election content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete any email content'.
  $permissions['delete any email content'] = array(
    'name' => 'delete any email content',
    'roles' => array(
      'Valgsekretær' => 'Valgsekretær',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any panel content'.
  $permissions['delete any panel content'] = array(
    'name' => 'delete any panel content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete any polling_station content'.
  $permissions['delete any polling_station content'] = array(
    'name' => 'delete any polling_station content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete any roles content'.
  $permissions['delete any roles content'] = array(
    'name' => 'delete any roles content',
    'roles' => array(
      'Valgsekretær' => 'Valgsekretær',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any volunteers content'.
  $permissions['delete any volunteers content'] = array(
    'name' => 'delete any volunteers content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete own constituency content'.
  $permissions['delete own constituency content'] = array(
    'name' => 'delete own constituency content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete own election content'.
  $permissions['delete own election content'] = array(
    'name' => 'delete own election content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete own email content'.
  $permissions['delete own email content'] = array(
    'name' => 'delete own email content',
    'roles' => array(
      'Valgsekretær' => 'Valgsekretær',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own panel content'.
  $permissions['delete own panel content'] = array(
    'name' => 'delete own panel content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete own polling_station content'.
  $permissions['delete own polling_station content'] = array(
    'name' => 'delete own polling_station content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete own roles content'.
  $permissions['delete own roles content'] = array(
    'name' => 'delete own roles content',
    'roles' => array(
      'Valgsekretær' => 'Valgsekretær',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own volunteers content'.
  $permissions['delete own volunteers content'] = array(
    'name' => 'delete own volunteers content',
    'roles' => array(
      'Brevstemme administrator' => 'Brevstemme administrator',
      'Partisekretær' => 'Partisekretær',
      'Valgsekretær' => 'Valgsekretær',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete revisions'.
  $permissions['delete revisions'] = array(
    'name' => 'delete revisions',
    'roles' => array(
      'admin' => 'admin',
    ),
    'module' => 'node',
  );

  // Exported permission: 'diff view changes'.
  $permissions['diff view changes'] = array(
    'name' => 'diff view changes',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'diff',
  );

  // Exported permission: 'edit any constituency content'.
  $permissions['edit any constituency content'] = array(
    'name' => 'edit any constituency content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit any election content'.
  $permissions['edit any election content'] = array(
    'name' => 'edit any election content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit any email content'.
  $permissions['edit any email content'] = array(
    'name' => 'edit any email content',
    'roles' => array(
      'Valgsekretær' => 'Valgsekretær',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any panel content'.
  $permissions['edit any panel content'] = array(
    'name' => 'edit any panel content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit any polling_station content'.
  $permissions['edit any polling_station content'] = array(
    'name' => 'edit any polling_station content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit any roles content'.
  $permissions['edit any roles content'] = array(
    'name' => 'edit any roles content',
    'roles' => array(
      'Valgsekretær' => 'Valgsekretær',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any volunteers content'.
  $permissions['edit any volunteers content'] = array(
    'name' => 'edit any volunteers content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit own constituency content'.
  $permissions['edit own constituency content'] = array(
    'name' => 'edit own constituency content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit own election content'.
  $permissions['edit own election content'] = array(
    'name' => 'edit own election content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit own email content'.
  $permissions['edit own email content'] = array(
    'name' => 'edit own email content',
    'roles' => array(
      'Valgsekretær' => 'Valgsekretær',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own panel content'.
  $permissions['edit own panel content'] = array(
    'name' => 'edit own panel content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit own polling_station content'.
  $permissions['edit own polling_station content'] = array(
    'name' => 'edit own polling_station content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit own roles content'.
  $permissions['edit own roles content'] = array(
    'name' => 'edit own roles content',
    'roles' => array(
      'Valgsekretær' => 'Valgsekretær',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own volunteers content'.
  $permissions['edit own volunteers content'] = array(
    'name' => 'edit own volunteers content',
    'roles' => array(
      'Brevstemme administrator' => 'Brevstemme administrator',
      'Partisekretær' => 'Partisekretær',
      'Valgsekretær' => 'Valgsekretær',
    ),
    'module' => 'node',
  );

  // Exported permission: 'import volunteers'.
  $permissions['import volunteers'] = array(
    'name' => 'import volunteers',
    'roles' => array(
      'admin' => 'admin',
    ),
    'module' => 'valghalla_volunteers_import',
  );

  // Exported permission: 'revert revisions'.
  $permissions['revert revisions'] = array(
    'name' => 'revert revisions',
    'roles' => array(
      'admin' => 'admin',
    ),
    'module' => 'node',
  );

  // Exported permission: 'see all psn numbers'.
  $permissions['see all psn numbers'] = array(
    'name' => 'see all psn numbers',
    'roles' => array(
      'Brevstemme administrator' => 'Brevstemme administrator',
      'Valgsekretær' => 'Valgsekretær',
      'admin' => 'admin',
    ),
    'module' => 'valghalla_volunteers',
  );

  // Exported permission: 'select account cancellation method'.
  $permissions['select account cancellation method'] = array(
    'name' => 'select account cancellation method',
    'roles' => array(),
    'module' => 'user',
  );

  // Exported permission: 'use text format filtered_html'.
  $permissions['use text format filtered_html'] = array(
    'name' => 'use text format filtered_html',
    'roles' => array(
      'Brevstemme administrator' => 'Brevstemme administrator',
      'Partisekretær' => 'Partisekretær',
      'Valgsekretær' => 'Valgsekretær',
      'admin' => 'admin',
    ),
    'module' => 'filter',
  );

  // Exported permission: 'use text format full_html'.
  $permissions['use text format full_html'] = array(
    'name' => 'use text format full_html',
    'roles' => array(
      'Brevstemme administrator' => 'Brevstemme administrator',
      'Valgsekretær' => 'Valgsekretær',
      'admin' => 'admin',
    ),
    'module' => 'filter',
  );

  // Exported permission: 'valghalla change party'.
  $permissions['valghalla change party'] = array(
    'name' => 'valghalla change party',
    'roles' => array(
      'Brevstemme administrator' => 'Brevstemme administrator',
      'Valgsekretær' => 'Valgsekretær',
      'admin' => 'admin',
    ),
    'module' => 'valghalla',
  );

  // Exported permission: 'valghalla export volunteers list'.
  $permissions['valghalla export volunteers list'] = array(
    'name' => 'valghalla export volunteers list',
    'roles' => array(
      'Brevstemme administrator' => 'Brevstemme administrator',
      'Valgsekretær' => 'Valgsekretær',
      'admin' => 'admin',
    ),
    'module' => 'valghalla_lists',
  );

  // Exported permission: 'valghalla see all parties'.
  $permissions['valghalla see all parties'] = array(
    'name' => 'valghalla see all parties',
    'roles' => array(
      'Brevstemme administrator' => 'Brevstemme administrator',
      'Valgsekretær' => 'Valgsekretær',
      'admin' => 'admin',
    ),
    'module' => 'valghalla',
  );

  // Exported permission: 'valghalla view external signup list'.
  $permissions['valghalla view external signup list'] = array(
    'name' => 'valghalla view external signup list',
    'roles' => array(
      'Valgsekretær' => 'Valgsekretær',
      'admin' => 'admin',
    ),
    'module' => 'valghalla_signup_list',
  );

  // Exported permission: 'valghalla view kvittering list'.
  $permissions['valghalla view kvittering list'] = array(
    'name' => 'valghalla view kvittering list',
    'roles' => array(
      'Valgsekretær' => 'Valgsekretær',
      'admin' => 'admin',
    ),
    'module' => 'valghalla_lists',
  );

  // Exported permission: 'valghalla view messages list'.
  $permissions['valghalla view messages list'] = array(
    'name' => 'valghalla view messages list',
    'roles' => array(
      'Brevstemme administrator' => 'Brevstemme administrator',
      'Valgsekretær' => 'Valgsekretær',
      'admin' => 'admin',
    ),
    'module' => 'valghalla_lists',
  );

  // Exported permission: 'valghalla view no-email list'.
  $permissions['valghalla view no-email list'] = array(
    'name' => 'valghalla view no-email list',
    'roles' => array(
      'Valgsekretær' => 'Valgsekretær',
      'admin' => 'admin',
    ),
    'module' => 'valghalla_lists',
  );

  // Exported permission: 'valghalla view no-reply list'.
  $permissions['valghalla view no-reply list'] = array(
    'name' => 'valghalla view no-reply list',
    'roles' => array(
      'Brevstemme administrator' => 'Brevstemme administrator',
      'Valgsekretær' => 'Valgsekretær',
      'admin' => 'admin',
    ),
    'module' => 'valghalla_lists',
  );

  // Exported permission: 'valghalla view parties-volunteers list'.
  $permissions['valghalla view parties-volunteers list'] = array(
    'name' => 'valghalla view parties-volunteers list',
    'roles' => array(
      'Brevstemme administrator' => 'Brevstemme administrator',
      'Partisekretær' => 'Partisekretær',
      'Valgsekretær' => 'Valgsekretær',
      'admin' => 'admin',
    ),
    'module' => 'valghalla_lists',
  );

  // Exported permission: 'valghalla view party-overview list'.
  $permissions['valghalla view party-overview list'] = array(
    'name' => 'valghalla view party-overview list',
    'roles' => array(
      'Brevstemme administrator' => 'Brevstemme administrator',
      'Partisekretær' => 'Partisekretær',
      'Valgsekretær' => 'Valgsekretær',
      'admin' => 'admin',
    ),
    'module' => 'valghalla_lists',
  );

  // Exported permission: 'valghalla view pollingstation list'.
  $permissions['valghalla view pollingstation list'] = array(
    'name' => 'valghalla view pollingstation list',
    'roles' => array(
      'Valgsekretær' => 'Valgsekretær',
      'admin' => 'admin',
    ),
    'module' => 'valghalla_lists',
  );

  // Exported permission: 'valghalla-list view all parties'.
  $permissions['valghalla-list view all parties'] = array(
    'name' => 'valghalla-list view all parties',
    'roles' => array(
      'Brevstemme administrator' => 'Brevstemme administrator',
      'Valgsekretær' => 'Valgsekretær',
      'admin' => 'admin',
    ),
    'module' => 'valghalla_lists',
  );

  // Exported permission: 'view own unpublished content'.
  $permissions['view own unpublished content'] = array(
    'name' => 'view own unpublished content',
    'roles' => array(
      'Brevstemme administrator' => 'Brevstemme administrator',
      'Partisekretær' => 'Partisekretær',
      'Valgsekretær' => 'Valgsekretær',
      'admin' => 'admin',
    ),
    'module' => 'node',
  );

  // Exported permission: 'view polling station'.
  $permissions['view polling station'] = array(
    'name' => 'view polling station',
    'roles' => array(
      'Brevstemme administrator' => 'Brevstemme administrator',
      'Partisekretær' => 'Partisekretær',
      'Valgsekretær' => 'Valgsekretær',
      'admin' => 'admin',
    ),
    'module' => 'valghalla_volunteers',
  );

  // Exported permission: 'view revisions'.
  $permissions['view revisions'] = array(
    'name' => 'view revisions',
    'roles' => array(
      'admin' => 'admin',
    ),
    'module' => 'node',
  );

  // Exported permission: 'view volunteers'.
  $permissions['view volunteers'] = array(
    'name' => 'view volunteers',
    'roles' => array(
      'Brevstemme administrator' => 'Brevstemme administrator',
      'Partisekretær' => 'Partisekretær',
      'Valgsekretær' => 'Valgsekretær',
      'admin' => 'admin',
    ),
    'module' => 'valghalla_volunteers',
  );

  // Exported permission: 'volunteers rsvp'.
  $permissions['volunteers rsvp'] = array(
    'name' => 'volunteers rsvp',
    'roles' => array(
      'Brevstemme administrator' => 'Brevstemme administrator',
      'Partisekretær' => 'Partisekretær',
      'Valgsekretær' => 'Valgsekretær',
      'admin' => 'admin',
    ),
    'module' => 'valghalla_volunteers',
  );

  return $permissions;
}
