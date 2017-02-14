<?php

/*$user_params = array(
  'id'         => -1,
  'login'      => 'test@test.com',
  'short_name' => 'mgc_test',
  'name'       => 'Aloiz',
  'surname'    => 'Komershaft',
  'password'   => '1',
  'admin'      => '0',
  'maximum'    => '2',
  'tariff'     => MGC_PRUFFMELAB_TARIFF_WITH_VIDEO,
);

$stop = _pruffmelab_api_users_edit($user_params);   */

//$stop = _pruffmelab_api_webinars_edit(-1, 116141, 'mgc_test_webinar2', 'WEBINAR ALLLLLO2');
//$stop = _pruffmelab_api_webinars_delete('5b430177299a74b6d82c25cf53ea8b7a');
//$stop = _pruffmelab_api_webinars_set_moderators('c57d0c1eeb24bdf273acc8b96e40f35f', array('123831'));
$stop = _pruffmelab_api_medias_list(MGC_PRUFFMELAB_LIMIT, 0, -1, 'c57d0c1eeb24bdf273acc8b96e40f35f');
$stop = 'Stop';