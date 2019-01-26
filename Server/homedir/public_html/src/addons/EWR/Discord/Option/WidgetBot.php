<?php

namespace EWR\Discord\Option;

class WidgetBot extends \XF\Option\AbstractOption
{
	public static function renderOption(\XF\Entity\Option $option, array $htmlParams)
	{
		$discordRepo = \XF::repository('EWR\Discord:Discord');
		$provider = $discordRepo->assertSetup();
		
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

		return self::getTemplate('admin:option_template_EWRdiscord_widgetbot', $option, $htmlParams, [
			'provider' => $provider,
			'channels' => $choices,
		]);
	}
}