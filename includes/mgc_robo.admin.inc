<?php

function mgc_robo_config_admin_form($form, &$form_state) {

  $form['settings'] = array(
    '#type'        => 'fieldset',
    '#title'       => t('Настройки магазина'),
    '#collapsible' => TRUE,
    '#collapsed'   => FALSE,
  );

  $form['settings']['robo_payment_merchant_login'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Идентификатор магазина'),
    '#default_value' => variable_get('robo_payment_merchant_login'),
    '#required'      => TRUE,
  );

  $form['settings']['robo_payment_password_1'] = array(
    //'#type'          => 'password',
    '#type'          => 'textfield',
    '#title'         => t('Пароль #1'),
    '#default_value' => variable_get('robo_payment_password_1'),
    '#required'      => TRUE,
  );

  $form['settings']['robo_payment_password_2'] = array(
    //'#type'          => 'password',
    '#type'          => 'textfield',
    '#title'         => t('Пароль #2'),
    '#default_value' => variable_get('robo_payment_password_2'),
    '#required'      => TRUE,
  );

  $form['settings']['robo_payment_is_test'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Тестовые платежи(введите 0 или 1)'),
    '#default_value' => variable_get('robo_payment_is_test'),
    '#required'      => TRUE,
  );

  $form['settings']['robo_payment_test_password_1'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Тестовый пароль #1'),
    '#default_value' => variable_get('robo_payment_test_password_1'),
    '#required'      => TRUE,
  );

  $form['settings']['robo_payment_test_password_2'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Тестовый пароль #2'),
    '#default_value' => variable_get('robo_payment_test_password_2'),
    '#required'      => TRUE,
  );

  //  $form['settings']['ditoolsi_payment_url'] = array(
  //    '#type'          => 'textfield',
  //    '#title'         => t('Robokassa URL магазина'),
  //    '#default_value' => variable_get('robo_payment_url', 'http://test.robokassa.ru/Index.aspx'),
  //    '#required'      => TRUE,
  //  );

  $form['settings']['robo_payment_currency'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Валюта'),
    '#default_value' => variable_get('robo_payment_currency'),
    '#required'      => TRUE,
  );

  $form['settings']['robo_payment_language'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Язык'),
    '#default_value' => variable_get('robo_payment_language'),
    '#required'      => TRUE,
  );

  $form['settings']['robo_payment_currency_suffix'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Префикс валюты'),
    '#default_value' => variable_get('robo_payment_currency_suffix', t('rub.')),
    '#required'      => TRUE,
  );

  /*  $result_url = url('robo/payment/result', array(
      'absolute' => TRUE,
    ));

    $form['settings']['robo_payment_result_url'] = array(
      '#type'          => 'textfield',
      '#title'         => t('Result URL'),
      '#default_value' => variable_get('robo_payment_result_url', $result_url),
      '#required'      => TRUE,
    );*/


  $form['tariff_tier1']           = array(
    '#type'  => 'textfield',
    '#title' => t('Тариф для 1,2 курса'),
    '#value' => variable_get('tariff_tier1', 2990),

  );
  $form['tariff_tier2']           = array(
    '#type'  => 'textfield',
    '#title' => t('Тариф для более 2-х курсов'),
    '#value' => variable_get('tariff_tier2', 7490),

  );
  $form['tariff_alpha']           = array(
    '#type'  => 'textfield',
    '#title' => t('Тариф для Альфа вебинара'),
    '#value' => variable_get('tariff_alpha', 1000),

  );
  $form['tariff_beta']            = array(
    '#type'  => 'textfield',
    '#title' => t('Тариф для Бета вебинара'),
    '#value' => variable_get('tariff_beta', 2000),

  );
  $form['tariff_gamma']           = array(
    '#type'  => 'textfield',
    '#title' => t('Тариф для Гамма вебинара'),
    '#value' => variable_get('tariff_gamma_alpha', 4000),

  );
  $form['tariff_gamma_plus']      = array(
    '#type'  => 'textfield',
    '#title' => t('Тариф для Гамма+ вебинара'),
    '#value' => variable_get('tariff_gamma_plus', 6000),

  );
  $form['tariff_gamma_plus_plus'] = array(
    '#type'  => 'textfield',
    '#title' => t('Тариф для Гамма++ вебинара'),
    '#value' => variable_get('tariff_gamma_plus_plus', 8000),

  );
  $form['tariff_days_qty']        = array(
    '#type'  => 'textfield',
    '#title' => t('Количество дней в месяце'),
    '#value' => variable_get('tariff_days_qty', 30),

  );


  $form['actions']['save'] = array(
    '#type'  => 'submit',
    '#value' => t('Сохранить'),
  );


  return $form;
}

function mgc_robo_config_admin_form_validate($form, &$form_state) {

  if (!is_numeric($form_state['input']['tariff_tier1'])) {
    form_set_error('tariff_tier1', 'Введите число');
  }
  if (!is_numeric($form_state['input']['tariff_tier2'])) {
    form_set_error('tariff_tier2', 'Введите число');
  }
  if (!is_numeric($form_state['input']['tariff_alpha'])) {
    form_set_error('tariff_alpha', 'Введите число');
  }
  if (!is_numeric($form_state['input']['tariff_beta'])) {
    form_set_error('tariff_beta', 'Введите число');
  }
  if (!is_numeric($form_state['input']['tariff_gamma'])) {
    form_set_error('tariff_gamma', 'Введите число');
  }
  if (!is_numeric($form_state['input']['tariff_gamma_plus'])) {
    form_set_error('tariff_gamma_plus', 'Введите число');
  }
  if (!is_numeric($form_state['input']['tariff_gamma_plus_plus'])) {
    form_set_error('tariff_gamma_plus_plus', 'Введите число');
  }
  if (!is_numeric($form_state['input']['robo_payment_is_test'])) {
    form_set_error('robo_payment_is_test', 'Введите число');
  }
  if (!is_numeric($form_state['input']['tariff_days_qty'])) {
    form_set_error('tariff_days_qty', 'Введите число');
  }
}

function mgc_robo_config_admin_form_submit($form, &$form_state) {

  variable_set('tariff_tier1', $form_state['input']['tariff_tier1']);
  variable_set('tariff_tier2', $form_state['input']['tariff_tier2']);
  variable_set('tariff_alpha', $form_state['input']['tariff_alpha']);
  variable_set('tariff_beta', $form_state['input']['tariff_beta']);
  variable_set('tariff_gamma', $form_state['input']['tariff_gamma']);
  variable_set('tariff_gamma_plus', $form_state['input']['tariff_gamma_plus']);
  variable_set('tariff_gamma_plus_plus', $form_state['input']['tariff_gamma_plus_plus']);
  variable_set('robo_payment_merchant_login', $form_state['input']['robo_payment_merchant_login']);
  variable_set('robo_payment_is_test', $form_state['input']['robo_payment_is_test']);
  variable_set('robo_payment_password_1', $form_state['input']['robo_payment_password_1']);
  variable_set('robo_payment_password_2', $form_state['input']['robo_payment_password_2']);
  variable_set('robo_payment_test_password_1', $form_state['input']['robo_payment_test_password_1']);
  variable_set('robo_payment_test_password_2', $form_state['input']['robo_payment_test_password_2']);
  variable_set('robo_payment_currency', $form_state['input']['robo_payment_currency']);
  variable_set('robo_payment_language', $form_state['input']['robo_payment_language']);
  variable_set('robo_payment_currency_suffix', $form_state['input']['robo_payment_currency_suffix']);
  variable_set('tariff_days_qty', $form_state['input']['tariff_days_qty']);

  drupal_set_message('настройки обновлены');
}

/*Pruffmelab*/

function mgc_pruffmelab_config_admin_form($form, &$form_state) {

  $form['settings'] = array(
    '#type'        => 'fieldset',
    '#title'       => t('Настройки pruffmelab'),
    '#collapsible' => TRUE,
    '#collapsed'   => FALSE,
  );

  $form['settings']['pruffmelab_partner_code'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Код партнера'),
    '#default_value' => variable_get('pruffmelab_partner_code', '9acd77b617baa86c23c46c323a54e3e9'),
    '#required'      => TRUE,
  );

  $form['settings']['pruffmelab_partner_key'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Ключ партнера'),
    '#default_value' => variable_get('pruffmelab_partner_key', 'd997a29401b7b938bbbae1af53e3bc57'),
    '#required'      => TRUE,
  );

  $form['settings']['pruffmelab_server'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Сервер'),
    '#default_value' => variable_get('pruffmelab_server', 'https://pruffmelab.com/engine/api/'),
    '#required'      => TRUE,
  );

  $form['settings']['pruffmelab_user_agent'] = array(
    '#type'          => 'textfield',
    '#title'         => t('user agent для curl'),
    '#default_value' => variable_get('pruffmelab_user_agent', 'Mozilla/4.0'),
    '#required'      => TRUE,
  );

  $form['settings']['pruffmelab_limit'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Лимит выдачи запроса'),
    '#default_value' => variable_get('pruffmelab_limit', 500),
    '#required'      => TRUE,
  );

  $form['actions']['save'] = array(
    '#type'  => 'submit',
    '#value' => t('Сохранить'),
  );


  return $form;
}

function mgc_pruffmelab_config_admin_form_validate($form, &$form_state) {

}

function mgc_pruffmelab_config_admin_form_submit($form, &$form_state) {

  variable_set('pruffmelab_partner_code', $form_state['input']['pruffmelab_partner_code']);
  variable_set('pruffmelab_partner_key', $form_state['input']['pruffmelab_partner_key']);
  variable_set('pruffmelab_server', $form_state['input']['pruffmelab_server']);
  variable_set('pruffmelab_user_agent', $form_state['input']['pruffmelab_user_agent']);
  variable_set('pruffmelab_limit', $form_state['input']['pruffmelab_limit']);

  drupal_set_message('настройки обновлены');
}

