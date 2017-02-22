<div class="mgc-robo-payment-form-wrapper">
    <div class="mgc-form-title-wrapper">
        <div class="mgc-form-title tariffs-title">Ваш тарифный план</div>
    </div>
    <div class="mgc-form-description-wrapper">
        <div class="mgc-form-description tariffs-description">При единовременной
            оплате платформы за 3 месяца скидка 10%, за 6 месяцев- 15%, за 12
            месяцев- 20%
        </div>
    </div>
  <?php
  $tariff_tier1           = variable_get('tariff_tier1', 2990);
  $tariff_tier1_formatted = number_format((float) $tariff_tier1, 2, '.', '');
  $tariff_tier2           = variable_get('tariff_tier2', 7490);
  $tariff_tier2_formatted = number_format((float) $tariff_tier2, 2, '.', '');
  $id1                    = mgc_get_new_order_id($user->uid);
  $id2                    = mgc_get_new_order_id($user->uid);
  $id3                    = mgc_get_new_order_id($user->uid);
  global $user;
  ?>
    <div class="mgc-form-wrapper tariffs-slick-slider bxslider tariffs-form-wrapper">
        <!--Тариф 1-->
        <div class="tariff-block tariff-slider-item tariff-1" data-shp-item="1"
             data-inv-id="<?= $id1 ?>"
             data-tariff="<?= $tariff_tier1_formatted ?>">
            <div class="tariff-block-title"> Standart</div>
            <div class="tariff-price-wrapper"><span
                        class="price-number">
                    <?= $tariff_tier1 ?>
                </span> <span
                        class="price-currency"> руб. </span></div>
            <div class="courses-qty-wrapper"> Курс на аккаунте: <span>1</span>
            </div>
            <div class="qty-to-pay-wrapper">
                <div class="qty-to-pay-description"> Количество оплачиваемых
                </div>
                <div class="input-group"><span class="input-group-btn"> <button
                                type="button" class="btn btn-default btn-number"
                                disabled="disabled" data-type="minus"
                                data-field="quant[1]"> <span
                                    class="glyphicon glyphicon-minus"></span> </button> </span>
                    <input type="text" name="quant[1]"
                           class="form-control input-number" value="1" min="1"
                           max="999"> <span class="input-group-btn"> <button
                                type="button" class="btn btn-default btn-number"
                                data-type="plus" data-field="quant[1]"> <span
                                    class="glyphicon glyphicon-plus"></span> </button> </span>
                </div>
            </div>
          <?php
          $form = drupal_get_form('mgc_robokassa_merchantform', $id1, 'Тариф ', $tariff_tier1_formatted, '1');
          print '<div class="pay-link-wrapper">' . render($form) . '</div>'; ?>
        </div>
        <div class="tariff-block tariff-2" data-shp-item="2" data-inv-id="<?= $id2 ?>"
             data-tariff="<?= $tariff_tier2_formatted ?>">
            <div class="tariff-block-title"> Business</div>
            <div class="tariff-price-wrapper"><span
                        class="price-number"> <?= $tariff_tier2 ?></span> <span
                        class="price-currency"> руб. </span></div>
            <div class="courses-qty-wrapper"> Курс на аккаунте: <span>2-5</span>
            </div>
            <div class="qty-to-pay-wrapper">
                <div class="qty-to-pay-description"> Количество оплачиваемых
                </div>
                <div class="input-group"><span class="input-group-btn"> <button
                                type="button" class="btn btn-default btn-number"
                                disabled="disabled" data-type="minus"
                                data-field="quant[1]"> <span
                                    class="glyphicon glyphicon-minus"></span> </button> </span>
                    <input type="text" name="quant[1]"
                           class="form-control input-number" value="1" min="1"
                           max="999"> <span class="input-group-btn"> <button
                                type="button" class="btn btn-default btn-number"
                                data-type="plus" data-field="quant[1]"> <span
                                    class="glyphicon glyphicon-plus"></span> </button> </span>
                </div>
            </div>
          <?php
          $form = drupal_get_form('mgc_robokassa_merchantform', $id2, 'Тариф ', $tariff_tier2_formatted, '2');
          print '<div class="pay-link-wrapper">' . render($form) . '</div>';
          // mgc_get_robokassa_payment_button($id2, 'Тариф ', $tariff_tier2_formatted, '2'); ?>
        </div>
        <div class="tariff-block tariff-3">
            <div class="tariff-block-title"> Индивидуальный тариф</div>
            <div class="tariff-desc-wrapper">
                <div class="desc-main">
                    -Интеграция с CRM системой <br>
                    -E-mail маркетинг <br>
                    -Продажа Ваших курсов <br>
                    -Партнерская программа <br>
                    -Автовебинары <br>
                    - и др. возможности, которые Вам необходимы. <br>
                </div>
                <div class="disclaimer"> Для обсуждения <br> индивидуального
                    тарифа
                    <br>
                    свяжитесь с вашим менеджером
                </div>
            </div>
          <?php
          $form = drupal_get_form('mgc_feedback_form');

          print '<div class="pay-link-wrapper"><button class="pay-link open-feedback-modal btn btn-default form-submit" 
id="open-modal-feedback" 
name="op" value="Оплатить">Оплатить</button></div>';
          print render($form);

          ?>
        </div>
    </div>
    <div class="mgc-form-title-wrapper">
        <div class="mgc-form-title webinars-title">Дополнительные услуги:</div>
    </div>
    <div class="mgc-form-description-wrapper">
        <div class="mgc-form-description webinars-description">Вебинарная
            комната.
        </div>
    </div>
    <div class="webinar-block">
        <div class="webinar-block-wrapper">
            <div class="webinar-main-column-wrapper">
                <div class="webinar-column column-0">
                    <div class="column-title"></div>
                    <div class="column-count"> Количество участников вебинаров
                    </div>
                    <div class="column-option-1"> Видиозапись вебинаров</div>
                    <div class="column-option-2"> Загрузка и хранение
                        видеофайлов
                    </div>
                    <div class="column-price"> Стоимость</div>
                    <div class="column-checkbox"></div>
                </div>
                <div class="webinar-column column-1">
                    <div class="webinar-column-wrapper">
                        <div class="column-title"> Старт</div>
                        <div class="column-count"> 10</div>
                        <div class="column-option-1"> -</div>
                        <div class="column-option-2"> *</div>
                        <div class="column-price"> Бесплатно</div>
                    </div>
                    <div class="column-checkbox"><input type="checkbox"
                                                        name="option1checkBox"
                                                        id="option1checkBox" data-webinar-type="tariff_free"
                                                        value="0"> <label
                                for="option1checkBox"></label></div>
                </div>
                <div class="webinar-column column-2">
                    <div class="webinar-column-wrapper">
                        <div class="column-title"> Альфа</div>
                        <div class="column-count"> 50</div>
                        <div class="column-option-1"> +</div>
                        <div class="column-option-2"> *</div>
                        <div class="column-price"> <?= variable_get('tariff_alpha', 1000) ?> Р<span> в месяц</span>
                        </div>
                    </div>
                    <div class="column-checkbox"><input type="checkbox"
                                                        name="option2checkBox"
                                                        id="option2checkBox" data-webinar-type="tariff_alpha"
                                                        value="<?= variable_get('tariff_alpha', 1000) ?>"> <label
                                for="option2checkBox"></label></div>
                </div>
                <div class="webinar-column column-3">
                    <div class="webinar-column-wrapper">
                        <div class="column-title"> Бета</div>
                        <div class="column-count"> 300</div>
                        <div class="column-option-1"> +</div>
                        <div class="column-option-2"> +</div>
                        <div class="column-price"> <?= variable_get('tariff_beta', 2000) ?> Р<span> в месяц</span>
                        </div>
                    </div>
                    <div class="column-checkbox"><input type="checkbox"
                                                        name="option3checkBox"
                                                        id="option3checkBox" data-webinar-type="tariff_beta"
                                                        value="<?= variable_get('tariff_beta', 2000) ?>"> <label
                                for="option3checkBox"></label></div>
                </div>
                <div class="webinar-column column-4">
                    <div class="webinar-column-wrapper">
                        <div class="column-title"> Гамма</div>
                        <div class="column-count"> 500</div>
                        <div class="column-option-1"> +</div>
                        <div class="column-option-2"> +</div>
                        <div class="column-price"> <?= variable_get('tariff_gamma_alpha', 4000) ?>
                            Р<span> в месяц</span>
                        </div>
                    </div>
                    <div class="column-checkbox"><input type="checkbox"
                                                        name="option4checkBox"
                                                        id="option4checkBox" data-webinar-type="tariff_gamma_alpha"
                                                        value="<?= variable_get('tariff_gamma_alpha', 4000) ?>"> <label
                                for="option4checkBox"></label></div>
                </div>
                <div class="webinar-column column-5">
                    <div class="webinar-column-wrapper">
                        <div class="column-title"> Гамма+</div>
                        <div class="column-count"> 700</div>
                        <div class="column-option-1"> +</div>
                        <div class="column-option-2"> +</div>
                        <div class="column-price"> <?= variable_get('tariff_gamma_plus', 6000) ?> Р<span> в месяц</span>
                        </div>
                    </div>
                    <div class="column-checkbox"><input type="checkbox"
                                                        name="option5checkBox"
                                                        id="option5checkBox" data-webinar-type="tariff_gamma_plus"
                                                        value="<?= variable_get('tariff_gamma_plus', 6000) ?>"> <label
                                for="option5checkBox"></label></div>
                </div>
                <div class="webinar-column column-6">
                    <div class="webinar-column-wrapper">
                        <div class="column-title"> Гамма++</div>
                        <div class="column-count"> 1000</div>
                        <div class="column-option-1"> +</div>
                        <div class="column-option-2"> +</div>
                        <div class="column-price"> <?= variable_get('tariff_gamma_plus_plus', 8000) ?>
                            Р<span> в месяц</span>
                        </div>
                    </div>
                    <div class="column-checkbox column-6"><input
                                type="checkbox" name="option6checkBox"
                                id="option6checkBox" data-webinar-type="tariff_gamma_plus_plus"
                                value="<?= variable_get('tariff_gamma_plus_plus', 8000) ?>"> <label
                                for="option6checkBox"></label></div>
                </div>
            </div>
            <div class="webinar-payment-wrapper" data-shp-item="3" data-inv-id="<?= $id3 ?>" data-tariff="webinar">
                <div class="webinar-payment-label"> Количество оплачиваемых
                </div>
                <div class="qty-to-pay-wrapper">
                    <div class="input-group"><span class="input-group-btn"> <button
                                    type="button"
                                    class="btn btn-default btn-number webinar-minus-btn"
                                    disabled="disabled" data-type="minus"
                                    data-field="quant[1]"> <span
                                        class="glyphicon glyphicon-minus"></span> </button> </span>
                        <input type="text" name="quant[1]"
                               class="form-control input-number webinar-qty"
                               value="1"
                               min="1" max="999"> <span class="input-group-btn"><button
                                    type="button"
                                    class="btn btn-default btn-number webinar-plus-btn"
                                    data-type="plus" data-field="quant[1]">
                  <span class="glyphicon glyphicon-plus"></span>
              </button>
          </span>
                    </div>
                </div>
                <div class="total-amount">
                    <div class="total-amount-wrapper"><span
                                class="desc">Итого: </span><span
                                class="price-number">0</span> <span
                                class="price-currency"> руб. </span>
                    </div>
                </div>
              <?php
              $form = drupal_get_form('mgc_robokassa_merchantform', $id3, 'Вебинар ', '0.00', '3');
              print '<div class="pay-link-wrapper">' . render($form) . '</div>';
              //mgc_get_robokassa_payment_button($id3, "Вебинар", '0.00', '3'); ?>
            </div>
        </div>
    </div>
</div>
<link rel="stylesheet" type="text/css"
      href="//cdn.jsdelivr.net/jquery.slick/1.6.0/slick.css"/>
<script type="text/javascript"
        src="//cdn.jsdelivr.net/jquery.slick/1.6.0/slick.min.js"></script>
<?php
//drupal_add_css(drupal_get_path('theme',
//    'ditoolsi') . '/css/jquery.bxslider.css', 'file');
//drupal_add_js(drupal_get_path('theme',
//    'ditoolsi') . '/js/jquery.bxslider.min.js', 'file');
//drupal_add_js(drupal_get_path('theme', 'ditoolsi') . '/js/alertify.min.js', 'file');
?>


