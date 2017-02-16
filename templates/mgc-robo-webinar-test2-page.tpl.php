<div class="container">
    <div class="row">
        <div class="col-md-12">
            <div class="webinar-container" style="position:absolute;top:20px;left:2%;right:2%;"></div>
        </div>
    </div>
</div>
<script>
    var $ = jQuery.noConflict();
</script>
<script src="https://pruffmelab.com/engine/api/js/library.js"></script>
<script src="https://pruffmelab.com/webinar/loader.js"></script>
<script>

    // Указываем, что это режим для проведения теста
    var global_pruffmelab_checking_mode = true;

    var api;    //Объявляем api
    function onTest()   //В нужном месте вызываем инициализатор
    {
        alert('Скрипт теста вебинара из документации загружен');
        var api = pruffmeLab({
            partner: "<?=MGC_PRUFFMELAB_PARTNER_CODE?>",// Указываем код партнера
            webinar: "c57d0c1eeb24bdf273acc8b96e40f35f",// Указываем уникальный Hash вебинара созданного методом webinars-edit
            flash_source: location.protocol + "//" + location.host + "/webinar/Pruffme.swf" //Установка ссылки на собственный Flash проигрыватель
        });
        api.loginWebinarViewerName(     //Вход в вебинар под тестовым слушателем
            global_pruffmelab_webinar_hash,
            "Тестовый Участник",
            function (result) {
                loadWebinarRoomScripts('.example-cnt');// в каком контейнере рисуем блок
            },
            function (error) {
                alert("Error loginWebinarViewerName:");
            }
        );
    }


</script>
