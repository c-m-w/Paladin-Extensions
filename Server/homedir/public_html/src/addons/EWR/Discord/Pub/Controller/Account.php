<?php

namespace EWR\Discord\Pub\Controller;

use XF\Mvc\ParameterBag;

class Account extends XFCP_Account
{
	protected function preferencesSaveProcess(\XF\Entity\User $visitor)
	{
		$reply = parent::preferencesSaveProcess($visitor);
		
		$options = $this->filter([
			'discord_options' => [
				'crate' => 'bool',
				'count' => 'bool',
				'toast' => 'bool',
				'alert' => 'bool',
			],
		]);
		
		foreach ($options['discord_options'] AS &$option)
		{
			$option = !$option;
		}
		
		$userOptions = $visitor->getRelationOrDefault('Option');
		$userOptions->discord_options = $options['discord_options'];
		$userOptions->save();
		
		return $reply;
	}
}