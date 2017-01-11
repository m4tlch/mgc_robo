<?php
function mgc_robo_form($form, $form_state) {

  $header = array(
    'User'             => t('Учитель'),
    'CoursesUpdate'    => t('Обновление курса'),
    'PupilsActivation' => t('Активация ученика'),
    'TaskChecked'      => t('Проверка задания'),
  );

  $rows     = array();
  $teachers = mgc_get_teachers();
  //$records      = mgc_get_records();
  $qty_per_day  = 0;
  $current_date = date('Y-m');
  $email_array  = array();
  $user_email   = '';
  if ($teachers) {
    foreach ($teachers as $key => $teacher) {
      $last_updated_course = mgc_get_last_updated_node('course', $teacher->uid);
      if ($last_updated_course) {
        $course_update = $last_updated_course['title'] . ' ' . date('Y-m-h', $last_updated_course['changed']);
      }
      else {
        $course_update = 'Нет курса';
      }
      $stop                         = 'Stop';
      $rows['key-' . $teacher->uid] = array(
        'User'             => $teacher->name,
        'CoursesUpdate'    => $course_update,
        'PupilsActivation' => $current_date,
        'TaskChecked'      => $current_date,
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