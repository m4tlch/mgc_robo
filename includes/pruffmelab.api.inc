<?php

function _pruffmelab_request($action, $request_params) {

  $content = (object) $request_params;
  $encoded = json_encode($content);
  $base    = base64_encode($encoded);

  $params     = array(
    'partner' => MGC_PRUFFMELAB_PARTNER_CODE,
    'key'     => MGC_PRUFFMELAB_PARTNER_KEY,
    'action'  => $action,
    'content' => $base,
  );
  $postFields = http_build_query($params);


  $server = MGC_PRUFFMELAB_SERVER;
  $curl   = curl_init($server);
  curl_setopt($curl, CURLOPT_USERAGENT, MGC_PRUFFMELAB_USER_AGENT);
  curl_setopt($curl, CURLOPT_RETURNTRANSFER, TRUE);
  curl_setopt($curl, CURLOPT_HEADER, 0);
  curl_setopt($curl, CURLOPT_POST, TRUE);
  /** @noinspection CurlSslServerSpoofingInspection */
  curl_setopt($curl, CURLOPT_SSL_VERIFYPEER, FALSE);
  curl_setopt($curl, CURLOPT_POSTFIELDS, $postFields);
  curl_setopt($curl, CURLOPT_TIMEOUT, 30);
  $result = curl_exec($curl);

  return json_decode($result);
}

/** Данная команда возвращает информацию о партнере
 * @return mixed
 */
function _pruffmelab_api_info() {
  $action         = 'info';
  $request_params = array();

  return _pruffmelab_request($action, $request_params);
}

/**
 * Данная команда возвращает список зарегистрированных в системе пользователей. Каждый пользователь может быть владельцем вебинара или модератором
 * @param int $limit количество выводимых пользователей
 * @param int $offset смещение
 * @return mixed
 */
function _pruffmelab_api_user_list($limit = MGC_PRUFFMELAB_LIMIT, $offset = 0) {
  $action         = 'users-list';
  $request_params = array(
    'limit'  => $limit,
    'offset' => $offset,
  );

  return _pruffmelab_request($action, $request_params);
}

/** Данная команда возвращает информацию об отдельном пользователе
 * @param int $id Идентификатор пользователя
 * @return mixed
 */
function _pruffmelab_api_user_info($id) {
  $action         = 'user-info';
  $request_params = array(
    'id' => $id,
  );

  return _pruffmelab_request($action, $request_params);
}

/** Данная команда удаляет пользователя из системы
 * @param int $id Идентификатор пользователя
 * @return mixed
 */
function _pruffmelab_api_user_delete($id) {
  $action         = 'user-delete';
  $request_params = array(
    'id' => $id,
  );

  return _pruffmelab_request($action, $request_params);
}

/** Функция для создания нового или редактирования старого пользователя
 * @param int $id
 * @param $params
 * @return mixed
 * {
 * "user": {
 * "id": -1,                       // Для создания нового пользователя передаем -1. Для редактирования id пользователя
 * "login": "test@test.com",        // Должен быть уникальным
 * "short_name": "uniq_test_name", // Должен быть уникальным
 * "name": "Name",
 * "surname": "Surname",
 * "password": "test",//пароль для логина пользователя
 * "admin": 0,                     // Является ли пользователь администратором(глобальным администратором системы)
 * "maximum": 10,                  // Максимальное кол-во участников в вебинаре пользователей
 * "tariff":1                      // 0 - без видеозаписи. 1 с видеозаписью
 * }
 * }
 */
function _pruffmelab_api_users_edit($params) {
  $action         = 'users-edit';
  $request_params = array(
    'user' => array(
      'id'         => $params['id'],
      'login'      => $params['login'],
      'short_name' => $params['short_name'],
      'name'       => $params['name'],
      'surname'    => $params['surname'],
      'password'   => $params['password'],
      'admin'      => $params['admin'],
      'maximum'    => $params['maximum'],
      'tariff'     => $params['tariff'],
    ),
  );

  return _pruffmelab_request($action, $request_params);
}

/**  Возвращает сессию для существующего пользователя, чтобы он мог работать в системе
 * @param int $user
 * @return mixed
 */
function _pruffmelab_api_users_login($user) {
  $action         = 'users-login';
  $request_params = array(
    'user' => $user,
  );

  return _pruffmelab_request($action, $request_params);
}

/** Возвращает список вебинаров в системе
 * @param int $limit
 * @param int $offset
 * @param int $id
 * @param int $ordering
 * @return mixed
 */
function _pruffmelab_api_webinars_list(
  $limit = MGC_PRUFFMELAB_LIMIT,
  $offset = 0,
  $id = -1,
  $ordering = MGC_PRUFFMELAB_WEBINAR_SORTING_BY_ACTIVITY
) {
  $action         = 'webinars-list';
  $request_params = array(
    'limit'    => $limit,
    'offset'   => $offset,
    'userId'   => $id,
    'ordering' => $ordering,
  );

  return _pruffmelab_request($action, $request_params);
}

/**Создание или редактирование вебинара. В ответ приходит полное его описание
 * @param int $id Указываем -1 для создания или идентификатор для редактирования
 * @param int $creatorId Идентификатор создателя вебинара
 * @param string $webinar_login Уникальный код вебинара
 * @param string $webinar_label_name Название вебинара
 * @return mixed
 */
function _pruffmelab_api_webinars_edit(
  $id,
  $creatorId,
  $webinar_login,
  $webinar_label_name
) {
  $action         = 'webinars-edit';
  $request_params = array(
    'webinar' => array(
      'id'        => $id,
      'creatorId' => $creatorId,
      'login'     => $webinar_login,
      'name'      => $webinar_label_name,
    ),
  );

  return _pruffmelab_request($action, $request_params);
}

/** Получение подробной информации о вебинаре
 * @param string $hash передаем Уникальный Хэш вебинара
 * @return mixed
 */
function _pruffmelab_api_webinars_info($hash) {
  $action         = 'webinars-info';
  $request_params = array(
    'hash' => $hash,
  );

  return _pruffmelab_request($action, $request_params);
}

/**Удаление вебинара
 * @param string $webinar
 * @return mixed
 */
function _pruffmelab_api_webinars_delete($webinar) {
  $action         = 'webinars-delete';
  $request_params = array(
    'webinar' => $webinar,
  );

  return _pruffmelab_request($action, $request_params);
}

/**Добавление и удаление модераторов. Список текущих модератором можно посмотреть в webinars-info
 * @param string $webinar передаем Уникальный Хэш вебинара
 * @param array $moderators Список идентификаторов участников. Если удалить всех, то передаем пустой массив
 * @return mixed
 */
function _pruffmelab_api_webinars_set_moderators($webinar, array $moderators) {
  $action         = 'webinars-set-moderators';
  $request_params = array(
    'webinar'    => $webinar,
    'moderators' => $moderators,
  );

  return _pruffmelab_request($action, $request_params);
}

/** Возвращает список записей вебинаров
 * @param int $limit Максимальное кол-во записей
 * @param int $offset
 * @param string $user_id Пользователь для которого возвращаем вебинары. Если указать -1 - вернутся для всех пользователей
 * @param string $webinar Hash вебинара для которого необходимо получить список записей
 * @return mixed
 */
function _pruffmelab_api_medias_list(
  $limit = MGC_PRUFFMELAB_LIMIT,
  $offset = 0,
  $user_id,
  $webinar
) {
  $action         = 'medias-list';
  $request_params = array(
    'limit'   => $limit,
    'offset'  => $offset,
    'userId'  => $user_id,
    'webinar' => $webinar,
  );

  return _pruffmelab_request($action, $request_params);
}

/**
 * Возвращает информацию об использованном времени в вебинарах(для одного вебинара)
 * (Информацию можно получить в течение месяца после проведения вебинара)
 * @param string $date_from // Начало периода
 * @param string $date_to // Конец периода
 * @param string $webinar
 * @return mixed
 */
function _pruffmelab_api_statistics_detailed_one(
  $date_from,
  $date_to,
  $webinar
) {
  $action         = 'statistics-detailed-one';
  $request_params = array(
    'date_from' => $date_from,
    'date_to'   => $date_to,
    'webinar'   => $webinar,
  );

  return _pruffmelab_request($action, $request_params);
}

/** Возвращает информацию об использованном времени в вебинарах
 * (Информацию можно получить в течение месяца после проведения вебинара)
 * @param string $date_from
 * @param string $date_to
 * @return mixed
 */
function _pruffmelab_api_statistics_detailed_all(
  $date_from,
  $date_to
) {
  $action         = 'statistics-detailed-all';
  $request_params = array(
    'date_from' => $date_from,
    'date_to'   => $date_to,
  );

  return _pruffmelab_request($action, $request_params);
}

/** Возвращает информацию о всех участниках вебинара
 * @param string $date_from Начало периода (не обязательное)
 * @param string $date_to Конец периода  (не обязательное)
 * @param string $webinar Хэш вебинара
 * @return mixed
 */
function _pruffmelab_api_webinar_participants(
  $date_from,
  $date_to,
  $webinar
) {
  $action         = 'webinar-participants';
  $request_params = array(
    'date_from' => $date_from,
    'date_to'   => $date_to,
    'webinar'   => $webinar,
  );

  return _pruffmelab_request($action, $request_params);
}
