<div class="row">
    <div class="col-md-12"><h1>Информация о вашей оплате</h1>
        <div class="well">
            <dl class="dl-vertical">
                <dt> Количество ваших курсов на платформе:</dt>
                <dd><?php global $user;

                  $courses_qty = mgc_get_node_count('course', $user->uid);
                  print  $courses_qty;
                  ?>
                </dd>
            </dl>
            <dl class="dl-vertical">
                <dt> Ваш тариф</dt>
                <dd><?php
                  print mgc_get_tariff($user, $courses_qty);
                  ?></dd>
            </dl>
            <dl class="dl-vertical">
                <dt> Осталось оплаченного времени</dt>
                <dd>
                  <?php
                  if (mgc_get_trial_access_status($user) === 'active') {
                    print 'У вас тестовый период';
                  }
                  else {
                    $time_left = mgc_get_teacher_paid_time_left($user, 'course');
                    if ($time_left && $time_left['left_seconds'] > 0) {
                      print  mgc_time_diff($time_left);
                    }
                    else {
                      print '0';
                    }
                  }

                  ?></dd>
            </dl>
        </div>
        <hr>
    </div>
</div>
<div class="row">
    <div class="col-md-12"><a href="/robo/payment"
                              class="btn btn-primary btn-success btn-lg">Перейти
            к оплате </a></div>
</div>
<br><br>
<div class="row">
    <div class="panel panel-default">
        <div class="panel-heading">История оплат</div>
      <?php

      ?>
        <table class="table">
            <thead>
            <tr>
                <th>#</th>
                <th>Заказ №</th>
                <th>Тип заказа</th>
                <th>Статус заказа</th>
                <th>Дней оплачено</th>
                <th>Сумма оплаты</th>
                <th>Дата оплаты</th>
            </tr>
            </thead>
            <tbody>
            <?php
            $rows = mgc_get_paid_enrollments($user->uid);
            $stop = 'Stop';
            if ($rows) {
              foreach ($rows as $key => $row) {
                $shp_type       = ($row->shp_type === 'webinar') ? 'За вебинар' : 'За курсы';
                $payment_status = ($row->payment_status === 'active') ? 'Активный' : 'Закончился';
                print '<tr>';
                print '<th scope="row">' . $key . '</th>';
                print ' <td>' . $row->inv_id . '</td>';
                print ' <td>' . $shp_type . '</td>';
                print ' <td>' . $payment_status . '</td>';
                print ' <td>' . $row->paid_days . '</td>';
                print ' <td>' . number_format($row->amount, 2, '.', '') . '</td>';
                print ' <td>' . date('M j, Y H:i', $row->enrolled) . '</td>';
                print '</tr>';
              }
            }
            ?>
            </tbody>
        </table>
    </div>
</div>
