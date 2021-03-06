<?php
function mgc_get_teachers() {
  $teachers = mgc_get_users_by_role('преподаватель');
  $curators = mgc_get_users_by_role('куратор');
  $users    = array_merge($teachers, $curators);
  return $users;
}

function mgc_get_last_activation($teacher_id) {
  $query      = db_select('mgc_pupil_activation', 'm')
    ->fields('m', array('created'))
    ->condition('teacher_id', $teacher_id, '=')
    ->orderBy('created', 'DESC')
    ->range(0, 1)
    ->execute();
  $activation = $query->fetchAssoc();

  return $activation;
}

function mgc_get_last_updated_node($type, $uid) {
  $query = db_select('node', 'n')
    ->fields('n', array('nid', 'title', 'changed'))
    ->condition('type', $type, '=')
    ->condition('uid', $uid, '=')
    ->orderBy('changed', 'DESC')
    ->range(0, 1)
    ->execute();
  $node  = $query->fetchAssoc();

  return $node;
}

function mgc_get_last_progress($teacher_id) {
  $query    = db_select('mgc_task_progress_update', 'm')
    ->fields('m', array('created'))
    ->condition('teacher_id', $teacher_id, '=')
    ->orderBy('created', 'DESC')
    ->range(0, 1)
    ->execute();
  $progress = $query->fetchAssoc();

  return $progress;
}

function mgc_get_nodes_by_type($type, $uid) {
  return node_load_multiple(array(), array('type' => $type, 'uid' => $uid));
}

function mgc_get_node_count($type, $uid) {
  $query = db_select('node', 'n')
    ->fields('n', array('nid', 'title'))
    ->condition('type', $type, '=')
    ->condition('uid', $uid, '=')
    ->countQuery();


  return $query->execute()->fetchField();
}

function mgc_get_tariff($teacher, $courses_qty) {

  if ($tariff = mgc_get_override_tariff($teacher)) {
    return $tariff;
  }
  else {
    if ($courses_qty < 3) {
      $tariff = variable_get('tariff_tier1', 0);
    }
    else {
      $tariff = variable_get('tariff_tier2', 0);
    }
  }

  return $tariff;
}

function mgc_get_override_tariff($teacher) {
  $query = db_select('mgc_tariff_override', 'm')
    ->fields('m', array('tariff'))
    ->condition('user_id', $teacher->uid, '=');
  return $query->execute()->fetchField();
}

function mgc_get_users_by_role($role_name) {
  $role  = user_role_load_by_name($role_name);
  $uids  = db_select('users_roles', 'ur')
    ->fields('ur', array('uid'))
    ->condition('ur.rid', $role->rid, '=')
    ->execute()
    ->fetchCol();
  $users = user_load_multiple($uids);
  return $users;
}

function mgc_get_user_search_autocomplete($teacher_mail) {
  $matches  = array();
  $teachers = mgc_get_teachers();

  if (!empty($teachers)) {
    foreach ($teachers as $teacher) {
      if (mb_stristr($teacher->mail, $teacher_mail)) {
        $matches[check_plain($teacher->mail)] = check_plain($teacher->mail);
      }
    }
  }
  drupal_json_output($matches);
  drupal_exit();
}

/**
 * @param string $out_summ сумма заказа
 * @param string $inv_id описание заказа
 * @param string $shp_item тип товара
 * @return string формирование подписи
 *
 * MGC_ROBOKASSA_MRCH_LOGIN и MGC_ROBOKASSA_MRCH_PASS1 - регистрационная информация (логин, пароль #1)
 *
 */
function mgc_get_order_signature($out_summ, $inv_id, $shp_item) {
  if (variable_get('robo_payment_is_test') === '1') {
    $mrh_pass1 = variable_get('robo_payment_test_password_1');
  }
  else {
    $mrh_pass1 = variable_get('robo_payment_password_1');
  }
  $signature = md5(variable_get('robo_payment_merchant_login') . ":$out_summ:$inv_id:" . $mrh_pass1 . ":Shp_item=$shp_item");
  return $signature;
}

/**
 * @param integer $inv_id number of order
 * @param string $inv_desc order description
 * @param string $out_summ sum of order
 * @param string $shp_item code of goods
 * @return string
 */
function mgc_get_robokassa_payment_button($inv_id, $inv_desc, $out_summ, $shp_item) {
  $mrh_login = variable_get('robo_payment_merchant_login');
  // generate signature
  $crc     = mgc_get_order_signature($out_summ, $inv_id, $shp_item);
  $in_curr = variable_get('robo_payment_currency');
  $culture = variable_get('robo_payment_language');
  // payment form
  print "<div class='pay-link-wrapper'><form  class='robokassa-payment-form' 
action='https://merchant.roboxchange.com/Index.aspx?isTest=" . variable_get('robo_payment_is_test') . "' 
 method=POST>" . "<input type=hidden 
name=MrchLogin value=$mrh_login>" . "<input type=hidden name=OutSum value=$out_summ>" . "<input type=hidden 
name=InvId value=$inv_id>" . "<input type=hidden name=Desc value='$inv_desc'>" . "<input type=hidden 
name=SignatureValue value=$crc>" . "<input type=hidden name=Shp_item value='$shp_item'>" . "<input 
type=hidden name=IncCurrLabel value=$in_curr>" . "<input type=hidden name=Culture value=$culture>" . "<input type=submit class='pay-link' value='Оплатить'>" . "</form></div>";
}

function mgc_get_signature() {
  if (isset($_POST['inv_id'], $_POST['out_summ'], $_POST['shp_item'])) {
    $out_summ  = $_POST['out_summ'] . '.00';
    $inv_id    = $_POST['inv_id'];
    $shp_item  = $_POST['shp_item'];
    $signature = mgc_get_order_signature($out_summ, $inv_id, $shp_item);
    return array(
      'signature' => $signature,
      'status'    => 'success',
    );
  }
  else {
    return array(
      'status' => 'fail',
    );
  }

}

function mgc_get_new_order_id($user_id, $status = 'pending') {
  $id = db_insert('mgc_robo_orders')->fields(array(
    'user_id' => $user_id,
    'status'  => $status,
  ))->execute();
  return $id;
}

function mgc_get_paid_enrollments($user_id) {
  $query = db_select('mgc_payment_order', 'm')
    ->fields('m', array('enrolled', 'amount', 'inv_id', 'paid_days', 'shp_type', 'payment_status'))
    ->condition('uid', $user_id, '=')//->orderBy('enrolled', 'DESC')
    ->condition('status', 'paid', '=')//->orderBy('enrolled', 'DESC')
    //->condition('payment_status', 'active', '=')//->orderBy('enrolled', 'DESC')
    ->execute();

  return $query->fetchAll();
}

function mgc_get_active_enroll($user_id, $shp_type) {
  $query = db_select('mgc_payment_order', 'm')
    ->fields('m', array('enrolled', 'paid_days', 'inv_id'))
    ->condition('uid', $user_id, '=')
    ->condition('shp_type', $shp_type, '=')
    ->orderBy('enrolled', 'DESC')
    ->range(0, 1)
    ->execute();

  return $query->fetchAssoc();
}

function mgc_get_tariff_type($teacher) {
  $query = db_select('mgc_tariff_override', 'm')
    ->fields('m', array('tariff_type'))
    ->condition('user_id', $teacher->uid, '=');
  return $query->execute()->fetchField();
}

function mgc_get_access($user) {

  $free_access    = mgc_teacher_has_free_access($user);
  $trial_access   = mgc_teacher_has_trial_access($user);
  $paid_time_left = mgc_get_teacher_paid_time_left($user, 'course');

  return $free_access || $paid_time_left || $trial_access;
}

function mgc_teacher_has_free_access($user) {
  $result = mgc_get_tariff_type($user);
  if ($result === 'free') {
    return TRUE;
  }
  else {
    return FALSE;
  }
}

function mgc_teacher_has_trial_access($user) {
  $result = mgc_get_trial_access_status($user);
  $stop   = 'Stop';
  if (!$result || $result === 'active') {
    return TRUE;
  }
  else {
    return FALSE;
  }
}

function mgc_get_teacher_paid_time_left($user, $shp_type) {
  $time = mgc_get_active_enroll($user->uid, $shp_type);
  $stop = 'Stop';
  if ($time) {
    /** @noinspection SummerTimeUnsafeTimeManipulationInspection */
    $diff_seconds = $time['enrolled'] + $time['paid_days'] * 24 * 60 * 60 - time();
    if ($diff_seconds > 0) {
      mgc_update_enrollment_status($time['inv_id'], 'active');
      return array(
        'left_seconds' => $diff_seconds,
        'enrolled'     => $time['enrolled'],
        'paid_days'    => $time['paid_days'],
      );
    }
    mgc_update_enrollment_status($time['inv_id'], 'expired');
    return FALSE;
  }
}

function mgc_get_trial_access_status($user) {
  mgc_update_trial_access($user);
  $query = db_select('mgc_trial_access', 'mta')->fields('mta', array('status'))->condition('uid', $user->uid, '=');
  return $query->execute()->fetchField();
}

function mgc_get_trial_override_status($user) {
  mgc_update_trial_access($user);
  $query = db_select('mgc_trial_access', 'mta')->fields('mta', array('override'))->condition('uid', $user->uid, '=');
  return $query->execute()->fetchField();
}

function mgc_get_trial_access_time($user) {
  $query = db_select('mgc_trial_access', 'mta')
    ->fields('mta', array('status', 'created', 'updated'))
    ->condition('uid', $user->uid, '=');
  return $query->execute()->fetchAssoc();
}
