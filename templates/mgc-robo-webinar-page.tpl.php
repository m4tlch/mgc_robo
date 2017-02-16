<?php

/*$user_params = array(
  'id'         => -1,
  'login'      => 'test2@test.com',
  'short_name' => 'mgc_test2',
  'name'       => 'Aloiz2',
  'surname'    => 'Komershaft2',
  'password'   => '1',
  'admin'      => '0',
  'maximum'    => '2',
  'tariff'     => MGC_PRUFFMELAB_TARIFF_WITH_VIDEO,
);

$stop = _pruffmelab_api_users_edit($user_params);*/

//$stop = _pruffmelab_api_webinars_edit(-1, 116141, 'mgc_test_webinar2', 'WEBINAR ALLLLLO2');
//$stop = _pruffmelab_api_webinars_delete('5b430177299a74b6d82c25cf53ea8b7a');
//$stop = _pruffmelab_api_webinars_set_moderators('c57d0c1eeb24bdf273acc8b96e40f35f', array('123831'));
//$stop = _pruffmelab_api_medias_list(MGC_PRUFFMELAB_LIMIT, 0, -1, 'c57d0c1eeb24bdf273acc8b96e40f35f');
$stop = 'Stop';
?>
<h4><?= l(t('Проверить работу вебинара'), '/webinars/test',
    array('attributes' => array('target' => '_blank', 'class' => array('link-to-test')))); ?></h4>
<div class="container">
    <div class="row">

        <div class="col-md-12">
            <div class="webinar-container"></div>
        </div>
    </div>
</div>
<script>
    var $ = jQuery.noConflict();
</script>
<script src="https://pruffmelab.com/engine/api/js/library.js"></script>
<script src="https://pruffmelab.com/webinar/loader.js"></script>
<script>

    var api = pruffmeLab({
        partner: "<?=MGC_PRUFFMELAB_PARTNER_CODE?>",// Указываем код партнера
        webinar: "c57d0c1eeb24bdf273acc8b96e40f35f",// Указываем уникальный Hash вебинара созданного методом webinars-edit
        flash_source: location.protocol + "//" + location.host + "/webinar/Pruffme.swf"//Установка ссылки на собственный Flash проигрыватель
    });

    function exampleLoginAsUser() {
        var user_session = "<?php
          $result = _pruffmelab_api_users_login(116141);
          print $result->session;
          ?>";// Получили через users-login
        alert("User session " + user_session);
        //Устанавливаем пользовательскую сессию
        api.setSession(user_session, function (result) {
                //Сессия сохранилась в cookies

                //Теперь привязываем пользователя к браузеру
                api.loginWebinar('c57d0c1eeb24bdf273acc8b96e40f35f', function (result) {
                        //Сохранилась сессия участника вебинара

                        //Теперь можно загружать саму вебинарную комнату
                        loadWebinarRoomScripts('.webinar-container');

                    },
                    function (error) {
                        alert("ERROR loginWebinar:" + JSON.stringify(error, null, 4));
                    });
            },
            function (error) {
                alert("ERROR setSession: " + JSON.stringify(error, null, 4));
            });
    }
</script>
