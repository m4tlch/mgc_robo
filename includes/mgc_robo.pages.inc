<?php
require_once __DIR__ . '/pruffmelab.api.inc';
function mgc_stats_teachers_page() {
  return theme('mgc_stats_teachers_page_theme',
    array(// 'image_path' => drupal_get_path('module', 'mgc_robo') . '/images/',
    ));
}

function mgc_robo_teachers_page() {
  return theme('mgc_robo_teachers_page', array());
}

function mgc_robo_payment_page() {
  drupal_set_title('');
  return theme('mgc_robo_payment_page', array());
}

function mgc_robo_payment_fail_page() {
  return theme('mgc_robo_payment_fail_page', array());
}

function mgc_robo_payment_result_page() {
  return theme('mgc_robo_payment_result_page', array());
}

function mgc_robo_payment_success_page() {
  return theme('mgc_robo_payment_success_page', array());
}

function mgc_robo_user_payment_page() {
  drupal_set_title('');
  return theme('mgc_robo_user_payment_page', array());
}

function mgc_robo_set_tariff_page($teacher) {
  drupal_set_title('Тариф для ' . $teacher->name);
  return theme('mgc_robo_set_tariff_page', array(
    'teacher' => $teacher,
  ));
}

function mgc_robo_webinar_page() {
  return theme('mgc_robo_webinar_page', array());
}