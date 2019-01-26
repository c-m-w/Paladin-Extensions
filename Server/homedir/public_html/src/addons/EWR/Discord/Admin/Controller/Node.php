<?php

namespace EWR\Discord\Admin\Controller;

use XF\Mvc\ParameterBag;

class Node extends XFCP_Node
{
	public function actionDiscord(ParameterBag $params)
	{
		$node = $this->assertNodeExists($params['node_id']);
		
		if ($node->node_type_id != 'Forum')
		{
			return $this->redirect($this->buildLink('nodes/edit', $node));
		}
		
		$discordRepo = $this->repository('EWR\Discord:Discord');
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
			'node' => $node,
			'channels' => $choices,
		];
		return $this->view('XF:Forum\Discord', 'EWRdiscord_forum', $viewParams);
	}
	
	public function actionDiscordSave(ParameterBag $params)
	{
		$this->assertPostOnly();
		
		$node = $this->assertNodeExists($params['node_id']);
		$discord = $this->filter('discord', 'array');
		
		if (empty($discord['threads']['channel']) &&
			empty($discord['threads']['message']))
		{
			unset($discord['threads']);
		}
		if (empty($discord['posts']['channel']) &&
			empty($discord['posts']['message']))
		{
			unset($discord['posts']);
		}
		
		$node->discord_options = $discord;
		$node->save();
		
		return $this->redirect($this->buildLink('nodes') . $this->buildLinkHash($node->node_id));
	}
}