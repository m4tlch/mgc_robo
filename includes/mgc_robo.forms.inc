<?php
function mgc_stats_teachers_form($form, $form_state) {

  $header = array(
    'User'             => t('Учитель'),
    'Email'            => t('e-mail'),
    'CoursesUpdate'    => t('Обновление курса'),
    'LessonsUpdate'    => t('Обновление урока'),
    'PupilsActivation' => t('Активация ученика'),
    'TaskChecked'      => t('Проверка задания'),
  );

  $rows     = array();
  $teachers = mgc_cached_teachers_data();

  if ($teachers) {
    if (isset($form_state['values']['mail']) && $form_state['values']['mail'] !== '') {
      foreach ($teachers as $key => $teacher) {
        if ($teacher->mail == $form_state['values']['mail']) {
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
            'Email'            => $teacher->mail,
            'CoursesUpdate'    => $course_update,
            'LessonsUpdate'    => $lesson_update,
            'PupilsActivation' => $activation_update,
            'TaskChecked'      => $progress_update,
          );
        }
      }
    }
    else {
      foreach ($teachers as $key => $teacher) {
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
          'Email'            => $teacher->mail,
          'CoursesUpdate'    => $course_update,
          'LessonsUpdate'    => $lesson_update,
          'PupilsActivation' => $activation_update,
          'TaskChecked'      => $progress_update,
        );
      }
    }

  }
  $form['user_mail']['user_mail_title'] = array(
    '#type'  => 'item',
    '#title' => t('Search on e-mail:'),
  );

  $form['user_mail']['mail'] = array(
    '#type'              => 'textfield',
    '#title'             => t('User e-mail'),
    '#size'              => 60,
    '#maxlength'         => 128,
    '#prefix'            => "<div class='process-ditools-labels'>",
    '#suffix'            => "</div>",
    '#autocomplete_path' => 'stats/teachers/autocomplete',
    '#ajax'              => array(
      'event'    => 'blur',
      'wrapper'  => 'teachers-table',
      'callback' => 'mgc_ajax_callback',
    ),
  );
  $stop                      = 'Stop';
  $form['#id']               = 'teachers-table';
  $form['table']             = array(
    '#type'       => 'tableselect',
    '#header'     => $header,
    '#options'    => $rows,
    '#empty'      => t('Нет данных.'),
    '#js_select'  => FALSE,
    //'#multiple'   => TRUE,
    '#attributes' => array(
      'class' => array('tablesorter responsive table-teachers-stats'),
      'id'    => array('sortTableTeachers'),
    ),
  );


  $form['table']['#attached']['js'] = array(

    drupal_get_path('theme', 'ditoolsi') . '/js/tablesort/jquery.tablesorter.min.js',
    drupal_get_path('theme', 'ditoolsi') . '/js/common/table-common.js',
  );

  $form['table']['#attached']['css'] = array(
    drupal_get_path('theme', 'ditoolsi') . '/css/table-style.css',
  );
  return $form;
}

function mgc_robo_teachers_form($form, $form_state) {

  $header = array(
    'User'         => t('Учитель'),
    'Email'        => t('e-mail'),
    'TariffPaid'   => t('Оплаченный тариф'),
    'PaidDate'     => t('Дата оплаты'),
    'LeftPaidTime' => t('Истекает оплата'),
  );

  $rows     = array();
  $teachers = mgc_cached_teachers_data();

  if ($teachers) {
    if (isset($form_state['values']['mail']) && $form_state['values']['mail'] !== '') {
      foreach ($teachers as $key => $teacher) {
        if ($teacher->mail == $form_state['values']['mail']) {
          if (mgc_user_has_curator_role($teacher)) {
            $role = ' (куратор)';
          }
          else {
            $role = '';
          }
          $rows['key-' . $teacher->uid] = array(
            'User'         => $teacher->name . $role,
            'Email'        => $teacher->mail,
            'TariffPaid'   => t('Оплаченный тариф'),
            'PaidDate'     => t('Дата оплаты'),
            'LeftPaidTime' => t('Истекает оплата'),
          );
        }
      }
    }
    else {
      foreach ($teachers as $key => $teacher) {

        if (mgc_user_has_curator_role($teacher)) {
          $role = ' (куратор)';
        }
        else {
          $role = '';
        }
        $rows['key-' . $teacher->uid] = array(
          'User'         => $teacher->name . $role,
          'Email'        => $teacher->mail,
          'TariffPaid'   => t('Оплаченный тариф'),
          'PaidDate'     => t('Дата оплаты'),
          'LeftPaidTime' => t('Истекает оплата'),
        );
      }
    }

  }
  $form['user_mail']['user_mail_title'] = array(
    '#type'  => 'item',
    '#title' => t('Search on e-mail:'),
  );

  $form['user_mail']['mail'] = array(
    '#type'              => 'textfield',
    '#title'             => t('User e-mail'),
    '#size'              => 60,
    '#maxlength'         => 128,
    '#prefix'            => "<div class='process-ditools-labels'>",
    '#suffix'            => "</div>",
    '#autocomplete_path' => 'stats/teachers/autocomplete',
    '#ajax'              => array(
      'event'    => 'blur',
      'wrapper'  => 'robo-teachers-table',
      'callback' => 'mgc_ajax_callback',
    ),
  );
  $stop                      = 'Stop';
  $form['#id']               = 'robo-teachers-table';
  $form['table']             = array(
    '#type'       => 'tableselect',
    '#header'     => $header,
    '#options'    => $rows,
    '#empty'      => t('Нет данных.'),
    '#js_select'  => FALSE,
    //'#multiple'   => TRUE,
    '#attributes' => array(
      'class' => array('tablesorter responsive table-robo-teachers'),
      'id'    => array('sortTableRoboTeachers'),
    ),
  );


  $form['table']['#attached']['js'] = array(

    drupal_get_path('theme', 'ditoolsi') . '/js/tablesort/jquery.tablesorter.min.js',
    drupal_get_path('theme', 'ditoolsi') . '/js/common/table-common.js',
  );

  $form['table']['#attached']['css'] = array(
    drupal_get_path('theme', 'ditoolsi') . '/css/table-style.css',
  );
  return $form;
}

function mgc_ajax_callback($form, &$form_state) {
  $form_state['rebuild'] = TRUE;
  return $form;
}

