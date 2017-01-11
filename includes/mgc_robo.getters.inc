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

function mgc_get_last_updated_node($type, $uid) {
  $query = db_select("node", "n")// select from the node table
  ->fields("n", array("nid", "title", "changed"))// fields nid, title
  ->condition("type", $type, "=")// where the node type = page
  ->condition("uid", $uid, "=")// where the node type = page
  ->orderBy("changed", "DESC")// order by the newest
  ->range(0, 1)// select only 10 records
  ->execute(); // execute the query
  $node  = $query->fetchAssoc();

  return $node;
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