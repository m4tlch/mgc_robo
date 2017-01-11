<?php
function mgc_robo_form($form, $form_state) {

  $header = array(
    'User'             => t('Учитель'),
    'CoursesUpdate'    => t('Обновление курса'),
    'LessonsUpdate'    => t('Обновление урока'),
    'PupilsActivation' => t('Активация ученика'),
    'TaskChecked'      => t('Проверка задания'),
  );

  $rows         = array();
  $teachers     = mgc_get_teachers();
  $current_date = date('Y-m');

  if ($teachers) {
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
        'CoursesUpdate'    => $course_update,
        'LessonsUpdate'    => $lesson_update,
        'PupilsActivation' => $activation_update,
        'TaskChecked'      => $progress_update,
      );
    }
  }
  /*  if ($records) {
      foreach ($records as $key => $record) {
        $stop = 'Stop';
        if ($current_date == '') {
          $current_date = $record->date;
        }
        if ($current_date == $record->date) {
          $qty_per_day++;
          if (!in_array($record->email, $email_array)) {
            $email_array[] = $record->email;
          }

        }
        else {
          $current_date  = $record->date;
          $qty_per_day   = 1;
          $email_array   = array();
          $email_array[] = $record->email;
        }
        $pupils = '';
        if (count($email_array) > 1) {
          foreach ($email_array as $email) {
            $pupils .= '<span>' . $email . ' </span>';
          }
        }
        else {
          $pupils .= '<span>' . $email_array[0] . ' </span>';
        }

        $rows['key-' . $record->date] = array(
          'Date'   => $current_date,
          'Pupils' => '<span class="show-pupils-array" data-pupils-count="' . count($email_array) . '">' . count($email_array) . '</span><div class="pupils-array">' . $pupils . '</div>',
          'Checks' => $qty_per_day,
        );

      }
    }*/
  $stop          = 'Stop';
  $form['table'] = array(
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