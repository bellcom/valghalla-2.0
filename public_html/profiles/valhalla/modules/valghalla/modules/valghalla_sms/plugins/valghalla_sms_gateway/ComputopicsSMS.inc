<?php

/**
 * @file
 * Ctools plugin for Valghalla notification Computopics SMS gateway .
 */

$plugin = [
  'title' => t('Computopics SMS gateway'),
  // Send plugin callback.
  'callback' => 'computopic_sms_send',
];

/**
 * Computopics SMS send callback.
 */
function computopic_sms_send($to, $message, $context) {
  global $base_url;
  $service_url = 'https://smssys.dk/';
  $user = variable_get('valghalla_sms_computopic_user', FALSE);
  $pass = variable_get('valghalla_sms_computopic_pass', FALSE);
  $notification = entity_valghalla_notification_load($context['notification_id']);

  $callback_url = $base_url . '/valghalla-sms-computopic/' . $notification->created;
  $landekode = 45;

  try {
    // Curl call to service.
    $params = array(
      'user' => $user,
      'pass' => $pass,
      'message' => $message,
      'landekode' => $landekode,
      'number' => $to,
      'callbackurl' => $callback_url,
      'charset' => 'UTF-8',
    );
    if ($context['notification_id']) {
      $params['messageid'] = $context['notification_id'];
    }
    $options = array(
      CURLOPT_URL => $service_url . '?' . http_build_query($params),
      CURLOPT_RETURNTRANSFER => TRUE,
      CURLOPT_SSL_VERIFYPEER => FALSE,
    );

    $ch = curl_init();
    curl_setopt_array($ch, $options);
    $content = curl_exec($ch);
    $result = curl_getinfo($ch);
    curl_close($ch);

    $response = new SimpleXMLElement($content);
    $status_code = (string) $response->status->statusline->code;
    if (intval($status_code) == 0) {
      $result['status'] = 'Sent';
    }
    elseif (intval($status_code) > 0 && intval($status_code) < 2000) {
      $result['status'] = FALSE;
    }
    else {
      $result['status'] = $status_code;
    }
    $message = response_status_mesage($status_code);
    $result['response'] = $message ?: $content;
  }
  catch (Exception $e) {
    return array(
      'status' => FALSE,
      'response' => $e->__toString(),
    );
  }
  return $result;
}

/**
 * Get response status message.
 *
 * @param int $status_code
 *   Response ctatue code.
 *
 * @return mixed
 *   Status message or FALSE.
 */
function response_status_mesage($status_code) {
  $statuses = array(
    0 => 'Besked håndteret successfuldt.',
    1001 => 'Ugyldigt brugernavn og/eller kode.',
    1002 => 'Ugyldigt telefonnummer.',
    1003 => 'Et senderalias er ikke tilladt sammen med en pris.',
    1004 => 'Beskeden er for lang.',
    1005 => 'Beskeden kunne ikke håndteres.',
    1006 => 'Ugyldig landekode.',
    1007 => 'Ingen udbyder specificeret, kontakt Computopic.',
    1008 => 'Senderalias er for langt.',
    1009 => 'Specificerede senderalias er ikke tilladt.',
    1010 => 'Ingen senderalias tilladt for brugeren.',
    1011 => 'Ingen pris tilladt for brugeren.',
    1012 => 'Ugyldig pris specificeret.',
    1013 => 'Ugyldig timing timestamp.',
    1014 => 'Timing timestamp er allerede overskredet.',
    1015 => 'Timing timestamp ikke tilladt sammen med by-pass queue.',
    1016 => 'By-pass queue ikke tilladt for brugeren.',
    1017 => 'Intet svar fra udbyder(e).',
    1018 => 'Uspecificeret fejl.',
    1019 => 'Ugyldig shortcode.',
    1020 => 'Pris defineret uden shortcode.',
    1021 => 'Ikke alle obligatoriske variabler sat.',
    1022 => 'Usupporterede variabler forsøgt sat.',
    1023 => 'Ugyldig callbackurl specificeret.',
    1024 => 'Kunne ikke finde valgte gate.',
    1025 => 'Pris/donation ikke tilladt for shortcode/land.',
    1026 => 'Bulk afsendelse ikke tilladt for land.',
    1027 => 'Besked kunne ikke leveres.',
    1028 => 'Afvist af underleverandør.',
    1029 => 'Underleverandør midlertidigt utilgængelig.',
    1030 => 'Ingen abonnent på nummeret.',
    1031 => 'Ugyldigt besked-ID.',
    1032 => 'Callbackurl kan ikke sættes uden messageid.',
    1033 => 'Ugyldig WAP URL.',
    1034 => 'Donation ikke tilladt.',
    1035 => 'Donation specificeret uden pris.',
    1036 => 'WAP besked er for lang. Max 220 tegn.',
    1037 => 'SMS pris ikke fastsat. Kontakt Computopic.',
    1038 => 'Kald fra ikke-godkendt server.',
    1039 => 'WAP URL ikke tilladt med binær data.',
    1040 => 'Ugyldig port.',
    1041 => 'Besked skal være hex-værdier når port er sat.',
    1042 => 'Buffered, f.eks. fordi telefonen er slukket.',
    1043 => 'Ugyldig port.',
    1044 => 'Besked skal være binær.',
    1045 => 'Binære beskeder er ikke tilgængelige.',
    1046 => 'Gatewayen er midlertidigt utilgængelig.',
    1047 => 'Ugyldig besked-kategory.',
    1048 => 'Ugyldigt charset.',
    1049 => 'SMS-kvote opbrugt.',
    1050 => 'Fejl hos modtager..',
    2001 => 'I kø.',
    2002 => 'Sendt, afventer delivery notification.',
    2003 => 'Oprettet i systemet.',
    2004 => 'Sat ud af kø.',
    2005 => 'Slettet.',
  );
  if (isset($statuses[$status_code])) {
    return $statuses[$status_code];
  }

  return FALSE;
}

/**
 * Computopic service callback.
 */
function valghalla_sms_computopic($created) {
  $params = drupal_get_query_parameters();
  if (empty($params['msg_id'])) {
    return drupal_not_found();
  }
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'entity_valghalla_notification')
    ->propertyCondition('id', $params['msg_id'])
    ->propertyCondition('created', $created);
  $result = $query->execute();
  if (empty($result)) {
    return drupal_not_found();
  }

  $notification = entity_valghalla_notification_load($params['msg_id']);

  $status_code = $params['status'];
  if (intval($status_code) == 0) {
    $notification->status = 'Succeed';
  }
  elseif (intval($status_code) > 0 && intval($status_code) < 2000) {
    $notification->status = 'Failed';
  }
  else {
    $notification->status = check_plain($status_code);
  }
  $notification->status_info = check_plain($params['status_description']);
  $notification->save();
}
