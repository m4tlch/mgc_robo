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

function mgc_update_trial_access($user, $status = 'active', $override = 'no changes') {
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