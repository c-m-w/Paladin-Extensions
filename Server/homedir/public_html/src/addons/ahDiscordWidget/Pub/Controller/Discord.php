<?php

namespace ahDiscordWidget\Pub\Controller;

class Discord extends \XF\Pub\Controller\AbstractController
{
	public function actionIndex()
	{
  	$viewParams = [];
    return $this->view('ahDiscordWidget:View', 'ah_discord_index', $viewParams);
	}
}