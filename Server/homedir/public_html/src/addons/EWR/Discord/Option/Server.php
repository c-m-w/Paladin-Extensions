<?php

namespace EWR\Discord\Option;

class Server extends \XF\Option\AbstractOption
{
	public static function renderOption(\XF\Entity\Option $option, array $htmlParams)
	{
		$provider = \XF::repository('EWR\Discord:Discord')->assertSetup();
		$redirect = \XF::app()->options()->boardUrl;
		
		if ($provider)
		{
			$redirect = 'https://discordapp.com/oauth2/authorize'.
				'?client_id='.$provider->options['client_id'].
				'&response_type=code&scope=bot&permissions=8'.
				'&redirect_uri='.urlencode($redirect.'/connected_discord.php');
		}

		return self::getTemplate('admin:option_template_EWRdiscord_server', $option, $htmlParams, [
			'provider' => $provider,
			'redirect' => $redirect,
		]);
	}
}