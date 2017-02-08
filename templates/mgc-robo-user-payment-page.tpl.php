<div class="row">
    <div class="col-md-12"><h1>Информация об вашей оплате</h1>
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
                <dd><?php
                  $enroll_date = mgc_get_active_enroll($user->uid, 'course');
                  if ($enroll_date) {
                    print  mgc_time_diff($enroll_date);
                  }
                  else {
                    print '0';
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
                <th>Дней оплачено</th>
                <th>Сумма оплаты</th>
                <th>Дата оплаты</th>
            </tr>
            </thead>
            <tbody>
            <?php
            $rows = mgc_get_paid_enrollments($user->uid);
            if ($rows) {
              foreach ($rows as $key => $row) {
                $shp_type = ($row->shp_type === 'webinar') ? 'За вебинар' : 'За курсы';
                print '<tr>';
                print '<th scope="row">' . $key . '</th>';
                print ' <td>' . $row->inv_id . '</td>';
                print ' <td>' . $shp_type . '</td>';
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
