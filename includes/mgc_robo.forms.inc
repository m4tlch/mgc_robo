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
    'User'         => t('Установить тариф'),
    'Email'        => t('e-mail'),
    'CoursesQty'   => t('Кол-во курсов'),
    'Tariff'       => t('Тариф'),
    'PaidDate'     => t('Дата оплаты'),
    'LeftPaidTime' => t('Истекает оплата'),
  );

  $rows     = array();
  $teachers = mgc_cached_teachers_data();
  if ($teachers) {
    if (isset($form_state['values']['mail']) && $form_state['values']['mail'] !== '') {
      foreach ($teachers as $key => $teacher) {
        if ($teacher->mail === $form_state['values']['mail']) {
          if (mgc_user_has_curator_role($teacher)) {
            $role = ' (куратор)';
          }
          else {
            $role = '';
          }
          $courses_qty                  = mgc_get_node_count('course', $teacher->uid);
          $courses_qty                  = $courses_qty ? : '0';
          $tariff                       = mgc_get_tariff($teacher, $courses_qty);
          $rows['key-' . $teacher->uid] = array(
            'User'         => '<a href="/set-tariff/' . $teacher->uid . '" target = "_blank">' . $teacher->name . $role . '</a>',
            'Email'        => $teacher->mail,
            'CoursesQty'   => $courses_qty,
            'Tariff'       => $tariff,
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
        $courses_qty                  = mgc_get_node_count('course', $teacher->uid);
        $courses_qty                  = $courses_qty ? : '0';
        $tariff                       = mgc_get_tariff($teacher, $courses_qty);
        $rows['key-' . $teacher->uid] = array(
          'User'         => '<a href="/set-tariff/' . $teacher->uid . '" target = "_blank">' . $teacher->name . $role . '</a>',
          'Email'        => $teacher->mail,
          'CoursesQty'   => $courses_qty,
          'Tariff'       => $tariff,
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

function mgc_robo_set_tariff_form($form, $form_state, $teacher) {
  $courses_qty = mgc_get_node_count('course', $teacher->uid);
  $courses_qty = $courses_qty ? : '0';
  $tariff      = mgc_get_tariff($teacher, $courses_qty);
  $tariff_type = mgc_get_tariff_type($teacher);
  if (!$tariff_type) {
    $tariff_type = 'free';
  }
  $form['name']                   = array(
    '#type'        => 'fieldset',
    '#title'       => $teacher->name . " ($teacher->mail)",
    '#collapsible' => TRUE,
    '#collapsed'   => FALSE,
  );
  $options                        = array(
    'free' => t('Бесплатный доступ'),
    'paid' => t('Платный доступ'),
  );
  $form['name']['tariff_type']    = array(
    '#type'          => 'radios',
    '#title'         => t('Тип доступа'),
    '#options'       => $options,
    '#description'   => t('Если выбрать платный доступ, то пользователь будет поставлен на тариф по-умолчанию, либо на переопределенный ниже.'),
    '#default_value' => $tariff_type,
  );
  $form['name']['course_qty']     = array(
    '#type'          => 'textfield',
    '#title'         => t('Кол-во курсов'),
    '#disabled'      => TRUE,
    '#default_value' => $courses_qty,
    '#size'          => 20,
    '#maxlength'     => 20,
  );
  $form['name']['current_tariff'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Текущий тариф'),
    '#disabled'      => TRUE,
    '#default_value' => $tariff,
    '#size'          => 20,
    '#maxlength'     => 20,
  );
  $form['name']['default_tariff'] = array(
    '#type'  => 'hidden',
    '#value' => $tariff,
  );
  $form['name']['new_tariff']     = array(
    '#type'          => 'textfield',
    '#title'         => t('Переопределить тариф'),
    '#default_value' => '',
    '#attributes'    => array(
      'placeholder' => 'Введите число',
    ),
    '#size'          => 20,
    '#maxlength'     => 20,
  );
  $form['submit']                 = array(
    '#type'  => 'submit',
    '#value' => 'Сохранить',
  );
  return $form;
}

function mgc_robo_set_tariff_form_validate($form, &$form_state) {
  if ($form_state['input']['new_tariff'] !== '' && !is_numeric($form_state['input']['new_tariff'])) {
    form_set_error('new_tariff', 'Введите число');
  }
}

function mgc_robo_set_tariff_form_submit($form, &$form_state) {
  $user   = $form_state['build_info']['args'][0];
  $tariff = $form_state['input']['new_tariff'] !== '' ? $form_state['input']['new_tariff'] : $form_state['input']['default_tariff'];
  db_merge('mgc_tariff_override')->key(array('user_id' => $user->uid))->fields(array(
    'tariff'      => $tariff,
    'tariff_type' => $form_state['input']['tariff_type'],
    'created'     => REQUEST_TIME,
  ))->execute();
  drupal_set_message('Form submitted');
}


function mgc_ajax_callback($form, &$form_state) {
  $form_state['rebuild'] = TRUE;
  return $form;
}

function mgc_robokassa_merchantform($form, &$form_state) {

  global $user;
  // generate signature

  $inv_id              = $form_state['build_info']['args'][0];
  $desc                = $form_state['build_info']['args'][1];
  $out_summ            = $form_state['build_info']['args'][2];
  $shp_item            = $form_state['build_info']['args'][3];
  $crc                 = mgc_get_order_signature($out_summ, $inv_id, $shp_item);
  $form['#action']     = 'https://merchant.roboxchange.com/Index.aspx?isTest=' . variable_get('robo_payment_is_test');
  $form['MrchLogin']   = array(
    '#type'  => 'hidden',
    '#value' => variable_get('robo_payment_merchant_login'),
  );
  $form['#attributes'] = array(
    'class' => array(
      'robokassa-payment-form',
    ),
  );
  $form['Desc']        = array(
    '#type'  => 'hidden',
    '#value' => $desc,
  );
  $form['Shp_item']    = array(
    '#type'  => 'hidden',
    '#value' => $shp_item,
  );
  $form['InvId']       = array(
    '#type'  => 'hidden',
    '#value' => $inv_id,
  );

  $form['OutSum'] = array(
    '#type'  => 'hidden',
    '#value' => $out_summ,
  );

  $form['SignatureValue'] = array(
    '#type'  => 'hidden',
    '#value' => $crc,
  );

  $form['IncCurrLabel'] = array(
    '#type'  => 'hidden',
    '#value' => variable_get('robo_payment_currency'),
  );

  $form['Culture'] = array(
    '#type'  => 'hidden',
    '#value' => variable_get('robo_payment_language'),
  );

  $form['Months_Qty'] = array(
    '#type'  => 'hidden',
    '#value' => 1,
  );

  $form['submit'] = array(
    '#type'       => 'submit',
    '#value'      => t('Оплатить'),
    '#attributes' => array(
      'class' => array(
        'pay-link',
      ),
    ),
    '#ajax'       => array(
      'callback' => 'mgc_create_robo_enrollment_ajax',
      'event'    => 'click',
    ),
  );

  return $form;
}

function mgc_create_robo_enrollment_ajax($form, $form_state) {
  global $user;

  $user_id   = $user->uid;
  $status    = 'pending';
  $amount    = $form_state['input']['OutSum'];
  $month_qty = $form_state['input']['Months_Qty'];
  $paid_days = $month_qty * (int) variable_get('tariff_days_qty');
  $enrolled  = time();
  $created   = $enrolled;
  if ($form_state['values']['Shp_item'] == MGC_WEBINAR_TARIFF_SHP_ITEM) {
    $shp_type = 'webinar';
  }
  else {
    $shp_type = 'course';
  }

  mgc_set_new_enrollment($user_id, $status, $amount, $enrolled, $created, $form_state['values']['InvId'], $paid_days,
    $form_state['values']['Shp_item'], $shp_type);

  ctools_include('ajax');
  ctools_add_js('ajax-responder');
  $path    = 'https://merchant.roboxchange.com/Index.aspx?isTest=' . variable_get('robo_payment_is_test');
  $query   = array(
    'Culture'        => $form_state['values']['Culture'],
    'Desc'           => $form_state['values']['Desc'],
    'Shp_item'       => $form_state['values']['Shp_item'],
    'InvId'          => $form_state['values']['InvId'],
    'MrchLogin'      => $form_state['values']['MrchLogin'],
    'OutSum'         => $amount,
    'SignatureValue' => $form_state['input']['SignatureValue'],
  );
  $options = array(
    'query' => $query,
  );

  $commands[] = ctools_ajax_command_redirect($path, 0, $options);
  print ajax_render($commands);
  drupal_exit();
}

function mgc_feedback_form($form, &$form_state) {
  $form['#id']         = 'feedback_modal';
  $form['#attributes'] = array(
    'class' => array(
      'form-group feedback-modal-form',
    ),
  );
  $form['close']       = array(
    '#markup' => '<div class="close-modal">Закрыть</div>',
  );
  $form['message']     = array(
    '#title'      => 'Опишите необходимые для вас функции и мы с Вами свяжемся',
    '#type'       => 'textarea',
    '#rows'       => 10,
    '#cols'       => 60,
    '#resizable'  => TRUE, // form-control
    '#attributes' => array(
      'class'       => array(
        'form-control',
      ),
      'placeholder' => 'Ваше сообщение',
    ),
  );
  $form['submit']      = array(
    '#type'       => 'submit',
    '#value'      => t('Отправить'),
    '#attributes' => array(
      'class' => array(
        'btn btn-primary btn-large btn-block',
      ),
    ),
    '#ajax'       => array(
      'callback' => 'mgc_send_feedback_ajax',
      'event'    => 'click',
    ),
  );
  return $form;

}

function mgc_send_feedback_ajax($form, &$form_state) {
  global $user;
  $mail_body    = $form_state['input']['message'];
  $mail_subject = 'Учитель ' . $user->name . ' хочет индивидуальный тариф на реврайте';
  global $language;
  if ($mail_body !== '') {
    drupal_mail('system', __FUNCTION__, MGC_FEEDBACK_MAIL, $language, array(
      'context' => array(
        'subject' => $mail_subject,
        'message' => 'E-mail учителя: ' . $user->mail . '<br>Текст сообщения: <br> ===========================<br>' . $mail_body,
      ),
    ));
    $commands[] = ajax_command_invoke('.feedback-modal-form', 'hide');
    $commands[] = ajax_command_remove('#task-saved-popup, #ditoolsi-overlay');

    return array(
      '#type'     => 'ajax',
      '#commands' => $commands,
    );
  }
  else {
    $commands[] = ajax_command_invoke('.feedback-modal-form textarea', 'addClass', array('modal-error'));
    $commands[] = ajax_command_invoke('.feedback-modal-form textarea', 'attr',
      array('placeholder', 'Сообщение пустым быть не может!'));
    return array(
      '#type'     => 'ajax',
      '#commands' => $commands,
    );
  }
}

