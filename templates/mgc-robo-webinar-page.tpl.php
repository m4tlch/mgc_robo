<?php

/*
 * Код партнера:9acd77b617baa86c23c46c323a54e3e9
   Ключ партнера: d997a29401b7b938bbbae1af53e3bc57
*/

$content = (object) array(
  "limit"  => 2,
  "offset" => 0,
);
$encoded = json_encode($content);
$base    = base64_encode($encoded);

$params     = array(
  "partner" => "9acd77b617baa86c23c46c323a54e3e9",
  "key"     => "d997a29401b7b938bbbae1af53e3bc57",
  "action"  => "users-list",
  "content" => $base,
);
$postFields = http_build_query($params);


$server = "https://pruffmelab.com/engine/api/";
$curl   = curl_init($server);
curl_setopt($curl, CURLOPT_USERAGENT, "Mozilla/4.0");
curl_setopt($curl, CURLOPT_RETURNTRANSFER, TRUE);
curl_setopt($curl, CURLOPT_HEADER, 0);
curl_setopt($curl, CURLOPT_POST, TRUE);
/** @noinspection CurlSslServerSpoofingInspection */
curl_setopt($curl, CURLOPT_SSL_VERIFYPEER, FALSE);
curl_setopt($curl, CURLOPT_POSTFIELDS, $postFields);
curl_setopt($curl, CURLOPT_TIMEOUT, 30);
$result = curl_exec($curl);

$json = json_decode($result);

$stop = 'Stop';