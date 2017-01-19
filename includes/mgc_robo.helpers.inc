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