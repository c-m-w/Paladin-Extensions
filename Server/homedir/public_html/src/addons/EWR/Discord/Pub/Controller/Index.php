<?php

namespace EWR\Discord\Pub\Controller;

use XF\Mvc\ParameterBag;

class Index extends \XF\Pub\Controller\AbstractController
{
	protected function preDispatchController($action, ParameterBag $params)
	{
		if (!\XF::visitor()->hasPermission('EWRdiscord', 'viewDiscord'))
		{
			throw $this->exception($this->noPermission());
		}
	}
	
	public function actionIndex(ParameterBag $params)
	{
		$cache = \XF::app()->simpleCache()->getValue('EWR/Discord', 'discord');
		
		$viewParams = [
			'cache' => $cache,
		];
		return $this->view('EWR\Discord:Index', 'EWRdiscord_index', $viewParams);
	}
	
	public function actionBotPost(ParameterBag $params)
	{
		if (!\XF::visitor()->hasPermission('EWRdiscord', 'botPost'))
		{
			return $this->noPermission();
		}
		
		$discordRepo = $this->repository('EWR\Discord:Discord');
		
		if ($this->isPost())
		{
			$channel = $this->filter('channel', 'str');
			$data = $this->filter('data', 'array');
			
			$discordRepo->postToChannel($channel, $data);
			
			return $this->redirect($this->buildLink('ewr-discord'));
		}
		
		$channels = $discordRepo->getGuild('/channels');
		$choices = [];
		
		if (!empty($channels) && isset($channels[0]['position']))
		{
			usort($channels, function($a, $b) { return($a['position'] > $b['position']); });
			
			foreach ($channels AS $channel)
			{
				if (!$channel['type'])
				{
					$choices[$channel['id']] = $channel;
				}
			}
		}
		
		$viewParams = [
			'channels' => $choices,
		];
		
		return $this->view('EWR\Discord:BotPost', 'EWRdiscord_botpost', $viewParams);
	}

	public static function getActivityDetails(array $activities)
	{
		return \XF::phrase('EWRdiscord_viewing_discord_information');
	}
}