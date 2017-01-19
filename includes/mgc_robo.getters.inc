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