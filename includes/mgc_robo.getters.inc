<?php
function mgc_get_teachers() {
  $teachers = mgc_get_users_by_role('преподаватель');
  $curators = mgc_get_users_by_role('куратор');
  $users    = array_merge($teachers, $curators);
  return $users;
}

function mgc_get_records() {
  $query = db_select('mgc_autochecks_info', 'm')->fields('m', array(
    'user_id',
    'email',
    'course_id',
    'lesson_title',
    'lesson_number',
    'date',
  ))// ->groupBy('date')
  ->orderBy('date', 'DESC')//Most recent first.
  ->extend('PagerDefault')->limit(30)->execute();
  return $query;
}

function mgc_get_last_activation($teacher_id) {
  $query      = db_select("mgc_pupil_activation", "m")
    ->fields("m", array("created"))
    ->condition("teacher_id", $teacher_id, "=")
    ->orderBy("created", "DESC")
    ->range(0, 1)
    ->execute();
  $activation = $query->fetchAssoc();

  return $activation;
}

function mgc_get_last_updated_node($type, $uid) {
  $query = db_select("node", "n")
    ->fields("n", array("nid", "title", "changed"))
    ->condition("type", $type, "=")
    ->condition("uid", $uid, "=")
    ->orderBy("changed", "DESC")
    ->range(0, 1)
    ->execute();
  $node  = $query->fetchAssoc();

  return $node;
}

function mgc_get_last_progress($teacher_id) {
  $query    = db_select("mgc_task_progress_update", "m")
    ->fields("m", array("created"))
    ->condition("teacher_id", $teacher_id, "=")
    ->orderBy("created", "DESC")
    ->range(0, 1)
    ->execute();
  $progress = $query->fetchAssoc();

  return $progress;
}

function mgc_get_nodes_by_type($type, $uid) {
  return node_load_multiple(array(), array('type' => $type, 'uid' => $uid));

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

function mgc_get_teachers_table_rows($teacher) {
  $last_updated_course = mgc_get_last_updated_node('course', $teacher->uid);
  if ($last_updated_course) {
    $course_update = date('Y-m-d H:i:s', $last_updated_course['changed']);
  }
  else {
    $course_update = '-';
  }

  $last_updated_lesson = mgc_get_last_updated_node('lesson', $teacher->uid);
  if ($last_updated_lesson) {
    $lesson_update = date('Y-m-d H:i:s', $last_updated_lesson['changed']);
  }
  else {
    $lesson_update = '-';
  }

  $pupil_activation = mgc_get_last_activation($teacher->uid);
  if ($pupil_activation) {
    $activation_update = date('Y-m-d H:i:s', $pupil_activation['created']);
  }
  else {
    $activation_update = '-';
  }

  $progress = mgc_get_last_progress($teacher->uid);
  if ($progress) {
    $progress_update = date('Y-m-d H:i:s', $progress['created']);
  }
  else {
    $progress_update = '-';
  }

  if (mgc_user_has_curator_role($teacher)) {
    $role = ' (куратор)';
  }
  else {
    $role = '';
  }
  $rows['key-' . $teacher->uid] = array(
    'User'             => $teacher->name . $role,
    'CoursesUpdate'    => $course_update,
    'LessonsUpdate'    => $lesson_update,
    'PupilsActivation' => $activation_update,
    'TaskChecked'      => $progress_update,
  );

  return $rows;
}