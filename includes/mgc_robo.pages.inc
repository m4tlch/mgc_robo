<?php
function mgc_robo_theme() {
  $path = drupal_get_path('module', 'mgc_robo') . '/templates';

  return array(
    'mgc_robo_page' => array(
      'path'      => $path,
      'template'  => 'mgc-robo-page',
      'variables' => array(
        'image_path' => '',
      ),
    ),
  );
}

function mgc_robo_access($op) {
  switch ($op) {

    case 'view robo':
      return user_is_logged_in();
      break;
  }

  return FALSE;
}

function mgc_robo_page() {
  drupal_add_css(drupal_get_path('module', 'mgc_robo') . '/css/mgc-robo.css');
  drupal_add_js(drupal_get_path('module', 'mgc_robo') . '/js/mgc-robo.js');
  return theme('mgc_robo_page', array(
    'image_path' => drupal_get_path('module', 'mgc_robo') . '/images/',
  ));
}
