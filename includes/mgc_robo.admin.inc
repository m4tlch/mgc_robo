<?php

function mgc_robo_config_admin_form($form, &$form_state) {

  $form['tariff_tier1']    = array(
    '#type'  => 'textfield',
    '#title' => t('Тариф для 1,2 курса'),
    '#value' => variable_get('tariff_tier1', 2990),

  );
  $form['tariff_tier2']    = array(
    '#type'  => 'textfield',
    '#title' => t('Тариф для более 2-х курсов'),
    '#value' => variable_get('tariff_tier2', 7490),

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
}

function mgc_robo_config_admin_form_submit($form, &$form_state) {

  variable_set('tariff_tier1', $form_state['input']['tariff_tier1']);
  variable_set('tariff_tier2', $form_state['input']['tariff_tier2']);
  drupal_set_message('Тарфиы обновлены');
}


