<?php

$dir = __DIR__;
require ($dir . '/src/XF.php');

XF::start($dir);
$app = XF::setupApp('XF\Pub\App');
$session = $app->session();

$response = $app->response();
$request = $app->request();

$redirect = $app->router('admin')->buildLink('ewr-discord/code', '', [
	'code' => !empty($_GET['code']) ? $_GET['code'] : '',
	'guild' => !empty($_GET['guild_id']) ? $_GET['guild_id'] : '',
]);

$response->redirect($redirect, 302);
$response->send($request);