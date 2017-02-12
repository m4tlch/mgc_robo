<?php
function mgc_cached_teachers_data($reset = FALSE) {
  global $language;
  $langcode = $language->language;

  $data = &drupal_static(__FUNCTION__, NULL, $reset);

  if (!isset($data) || $reset) {
    if (!$reset && ($cache = cache_get("teachers_table:$langcode")) && !empty($cache->data) && REQUEST_TIME < $cache->expire) {
      $data = $cache->data;
    }
    else {
      $data = mgc_get_teachers();
      cache_set("teachers_table:$langcode", $data, 'cache',
        REQUEST_TIME + MGC_TEACHERS_CACHE_EXPIRE); //stores in cache table and expires after 1 hour
    }
  }
  return $data;
}

function mgc_print_form($form_name, $var1 = NULL, $var2 = NULL, $var3 = NULL) {
  $form = drupal_get_form($form_name, $var1, $var2, $var3);
  $form = drupal_render($form);
  print $form;
}

function mgc_print_timer() {
  $time_start = microtime(TRUE);
  $time_end   = microtime(TRUE);
  $time       = $time_end - $time_start;
  echo "Process Time: {$time}";
}

function mgc_time_diff($enroll_time) {
  //TODO пересчет тарифа в днях

  $seconds = $enroll_time['enrolled'] + $enroll_time['paid_days'] * 24 * 60 * 60 - time();
  if ($seconds < 0) {
    return '0';
  }
  $days    = floor($seconds / 86400);
  $seconds %= 86400;

  $hours   = floor($seconds / 3600);
  $seconds %= 3600;

  $minutes = floor($seconds / 60);
  $seconds %= 60;


  return "$days дней $hours часов";
  //echo "$days дней $hours часов $minutes minutes and $seconds seconds";
}

function mgc_mail($mail, $mail_subject, $mail_body) {
  global $language;
  drupal_mail('system', __FUNCTION__, $mail, $language, array(
    'context' => array(
      'subject' => $mail_subject,
      'message' => $mail_body,
    ),
  ));
}