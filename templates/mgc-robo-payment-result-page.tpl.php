<div class="row">
    <div class="col-md-12">
      <?php
      $mrh_pass2 = variable_get('robo_payment_test_password_2');

      //установка текущего времени
      //current date
      $tm   = getdate(time() + 9 * 3600);
      $date = "$tm[year]-$tm[mon]-$tm[mday] $tm[hours]:$tm[minutes]:$tm[seconds]";

      // чтение параметров
      // read parameters
      $out_summ = $_REQUEST["OutSum"];
      $inv_id   = $_REQUEST["InvId"];
      $shp_item = $_REQUEST["Shp_item"];
      $crc      = $_REQUEST["SignatureValue"];

      $crc = strtoupper($crc);

      $my_crc = strtoupper(md5("$out_summ:$inv_id:$mrh_pass2:Shp_item=$shp_item"));

      // проверка корректности подписи
      // check signature
      if ($my_crc != $crc) {
        echo "bad sign\n";
        mgc_update_enrollment($inv_id, 'fail');
        //mgc_mail('paul.nike@yandex.ru', '$mail_subject', $inv_id);
        exit();
      }

      // признак успешно проведенной операции
      // success
      echo "OK$inv_id\n";
      mgc_update_enrollment($inv_id);
      mgc_create_pruffmelab_webinar($inv_id);
      //mgc_mail('paul.nike@yandex.ru', '$mail_subject2', $inv_id);
      ?>
    </div>
</div>