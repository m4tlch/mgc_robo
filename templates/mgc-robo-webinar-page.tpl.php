<div class="container">
    <div class="row">
        <div class="col-md-12">

        </div>
    </div>
</div>
<div class="rewrite-webinar-container"></div>
<script>
    var $ = jQuery.noConflict();
</script>
<script src="https://pruffmelab.com/engine/api/js/library.js"></script>
<script src="https://pruffmelab.com/webinar/loader.js"></script>
<script>

    var api = pruffmeLab({
        partner: "<?=MGC_PRUFFMELAB_PARTNER_CODE?>",
        webinar: "d0990a31b8905ab65b249709653a9389",// Указываем уникальный Hash вебинара созданного методом webinars-edit
        flash_source: location.protocol + "//" + location.host + "/webinar/Pruffme.swf"
    });

    function LoginAsUser() {
        var user_session = "<?php
          $result = _pruffmelab_api_users_login(126693);
          print $result->session;
          ?>";// Получили через users-login
        //alert("User session " + user_session);
        //Устанавливаем пользовательскую сессию
        api.setSession(user_session, function (result) {
                //Сессия сохранилась в cookies

                //Теперь привязываем пользователя к браузеру
                api.loginWebinar(global_pruffmelab_webinar_hash, function (result) {
                        //Сохранилась сессия участника вебинара

                        //Теперь можно загружать саму вебинарную комнату
                        loadWebinarRoomScripts('.rewrite-webinar-container');

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