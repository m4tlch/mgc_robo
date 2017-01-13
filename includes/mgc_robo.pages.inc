<?php

function mgc_stats_teachers_page() {
  drupal_add_css(drupal_get_path('module', 'mgc_robo') . '/css/mgc-robo.css');
  drupal_add_js(drupal_get_path('module', 'mgc_robo') . '/js/mgc-robo.js');
  return theme('mgc_stats_teachers_page_theme', array(
    'image_path' => drupal_get_path('module', 'mgc_robo') . '/images/',
  ));
}

function mgc_robo_teachers_page() {
  drupal_add_css(drupal_get_path('module', 'mgc_robo') . '/css/mgc-robo.css');
  drupal_add_js(drupal_get_path('module', 'mgc_robo') . '/js/mgc-robo.js');
  return theme('mgc_robo_teachers_page', array(
    'image_path' => drupal_get_path('module', 'mgc_robo') . '/images/',
  ));
}
