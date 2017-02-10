<?php

function mgc_set_trial_access($user) {
  $id = db_insert('mgc_payment_order')->fields(array(
    'uid'     => $user->uid,
    'status'  => 'active',
    'created' => time(),
  ))->execute();
  return $id;
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
  $shp_type
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