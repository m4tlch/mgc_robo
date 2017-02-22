<?php

function mgc_set_trial_access($user) {
  $id = db_insert('mgc_trial_access')->fields(array(
    'uid'      => $user->uid,
    'status'   => 'active',
    'created'  => time(),
    'updated'  => time(),
    'override' => 'no changes',
  ))->execute();
  return $id;
}

function mgc_update_trial_access(
  $user,
  $status = 'active',
  $override = 'no changes'
) {
  $time    = mgc_get_trial_access_time($user);
  $created = $time['created'];
  /** @noinspection SummerTimeUnsafeTimeManipulationInspection */
  $diff = $created + MGC_TRIAL_TIME_DAYS * 86400 - time();
  if ($diff <= 0 && $override === 'no changes') {
    $status = 'blocked';
  }
  if ($override === 'no changes') {
    db_update('mgc_trial_access')->fields(array(
      'status'  => $status,
      'updated' => time(),
    ))->condition('uid', $user->uid)->execute();
  }
  else {
    db_update('mgc_trial_access')->fields(array(
      'status'   => $status,
      'updated'  => time(),
      'override' => $override,
    ))->condition('uid', $user->uid)->execute();
  }

  $stop = 'Stop';
}

function mgc_set_new_enrollment(
  $user_id,
  $status,
  $amount,
  $enrolled,
  $created,
  $inv_id,
  $paid_days,
  $shp_item,
  $shp_type,
  $webinar_type
) {
  $id = db_insert('mgc_payment_order')->fields(array(
    'uid'            => $user_id,
    'status'         => $status,
    'amount'         => $amount,
    'enrolled'       => $enrolled,
    'created'        => $created,
    'inv_id'         => $inv_id,
    'paid_days'      => $paid_days,
    'shp_item'       => $shp_item,
    'shp_type'       => $shp_type,
    'webinar_type'   => $webinar_type,
    'payment_status' => 'active',
  ))->execute();
  return $id;
}

function mgc_update_enrollment($inv_id, $status = 'paid') {
  db_update('mgc_payment_order')->fields(array(
    'status'   => $status,
    'enrolled' => time(),
  ))->condition('inv_id', $inv_id)->execute();
}

function mgc_update_enrollment_status($inv_id, $payment_status) {
  db_update('mgc_payment_order')->fields(array(
    'payment_status' => $payment_status,
  ))->condition('inv_id', $inv_id)->execute();
}

function mgc_create_pruffmelab_webinar($inv_id) {

  $order = db_select('mgc_payment_order', 'n')
    ->fields('n', array('uid', 'webinar_type'))
    ->condition('inv_id', $inv_id, '=')
    ->execute()
    ->fetchAssoc();
  $stop  = 'Stop';
  if ($order) {
    $user         = user_load($order['uid']);
    $webinar_type = $order['webinar_type'];

    switch ($webinar_type) {
      case 'tariff_free':
        $user_maximum       = 10;
        $webinar_with_video = 0;
        break;
      case 'tariff_alpha':
        $user_maximum       = 50;
        $webinar_with_video = 0;
        break;
      case 'tariff_beta':
        $user_maximum       = 300;
        $webinar_with_video = 1;
        break;
      case 'tariff_gamma_alpha':
        $user_maximum       = 500;
        $webinar_with_video = 1;
        break;
      case 'tariff_gamma_plus':
        $user_maximum       = 700;
        $webinar_with_video = 1;
        break;
      case 'tariff_gamma_plus_plus':
        $user_maximum       = 1000;
        $webinar_with_video = 1;
        break;
      default:
        $user_maximum       = 10;
        $webinar_with_video = 0;
        break;
    }
    $result = mgc_create_pruffmelab_user($user, $user_maximum,
      $webinar_with_video, FALSE);
    /*Если есть уже на платформе, повторяем запрос, но уже с айдишником*/
    if (isset($result->error->additional)) {
      $result = mgc_create_pruffmelab_user($user, $user_maximum,
        $webinar_with_video, $result->error->additional);
    }
    if ($result->result->user->id) {

      $pruffmelab_id      = $result->result->user->id;
      $webinar_short_name = 'rewrite_webinar_' . $pruffmelab_id;
      $webinar_name       = 'Rewrite webinar for user ' . $pruffmelab_id;
      $webinars_list      = _pruffmelab_api_webinars_list(MGC_PRUFFMELAB_LIMIT,
        0, $pruffmelab_id, MGC_PRUFFMELAB_WEBINAR_SORTING_BY_ACTIVITY);
      if (empty($webinars_list->result)) {
        _pruffmelab_api_webinars_edit(-1, $pruffmelab_id, $webinar_short_name,
          $webinar_name);
      }
    }
  }
}

function mgc_create_pruffmelab_user(
  $user,
  $user_maximum,
  $webinar_with_video,
  $pruffmelab_id
) {

  $user_params = array(
    'id'         => $pruffmelab_id ? : -1,
    'login'      => $user->mail,
    'short_name' => 'rewrite' . $user->uid,
    'name'       => $user->name ? : 'noname' . $user->uid,
    'surname'    => 'nosurname' . $user->uid,
    //TODO   user_pass()
    'password'   => '1',
    'admin'      => '0',
    'maximum'    => $user_maximum,
    'tariff'     => $webinar_with_video,
  );
  return _pruffmelab_api_users_edit($user_params);
}


