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

function mgc_print_form($form_name) {
  $form = drupal_get_form($form_name);
  $form = drupal_render($form);
  print $form;
}