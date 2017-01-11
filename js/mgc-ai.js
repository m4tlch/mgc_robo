(function ($) {

    "use strict";

   
    Drupal.behaviors.guideJS = {
        attach: function (context, setting) {

            $('.selector').once('guideJS', function () {
                $(this).click(function () {
                 
                })
            });

        }
    };
    $(document).ready(function () {
       
    });

})(jQuery);
