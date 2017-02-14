<div class="container">
    <div class="row">
        <div class="col-md-12">
            <div class="webinar-container" style="position:absolute;top:20px;left:2%;right:2%;"></div>
        </div>
    </div>
</div>
<script src="https://pruffmelab.com/engine/api/js/library.js"></script>
<script src="https://pruffmelab.com/webinar/loader.js"></script>
<script>

    var global_pruffmelab_partner = "e0792832920a0d8eba41db02cd1d22f7";
    var global_pruffmelab_webinar_hash = "e806f9f611a15d8bd53e9dbb63462e0a";
    var global_pruffmelab_checking_mode = true;

    var api;
    function onTestLoad() {
        alert('Скрипт теста вебинара с сайта загружен');
        api = pruffmeLab({
            partner: global_pruffmelab_partner
        });
        examplePreLoginAsViewer();
    }

    function examplePreLoginAsViewer() {
        //Объявим, что делать если пользователь не имеет сессии
        window.onPruffmeLabNoParticipant = function () {
            alert("Не получен код участника");
        };

        //Задаем свою сессию для пользователя
        api.loginWebinarViewerName(
            global_pruffmelab_webinar_hash,
            "Тестовый Участник",
            function (result) {
                //Сохранилась сессия участника вебинара
                //Теперь можно загружать саму вебинарную комнату
                loadWebinarRoomScripts('.webinar-container');
            },
            function (error) {
                alert("Error loginWebinarViewerName:" + JSON.stringify(error, null, 4));
            });
    }


</script>
