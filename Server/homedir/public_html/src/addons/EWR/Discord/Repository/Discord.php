<?php

namespace EWR\Discord\Repository;

use XF\Mvc\Entity\AbstractCollection;
use XF\Mvc\Entity\Repository;

class Discord extends Repository
{
	public function assertSetup()
	{
		$provider = $this->getProvider();
			
		if (empty($provider->options['client_id']) ||
			empty($provider->options['client_secret']) ||
			empty($provider->options['bot_token']))
		{
			return false;
		}
		
		return $provider;
	}
	
	public function getGuild($endpoint = '')
	{
		$provider = $this->assertSetup();
		$server = $this->getServer();
		
		if (!$provider || !$server)
		{
			return false;
		}
		
		try
		{
			$client = \XF::app()->http()->client();
			$response = $client->get('https://discordapp.com/api/guilds/'.$server.$endpoint, [
				'headers' => [
					'Authorization' => 'Bot '.$provider->options['bot_token'],
					'User-Agent' => 'DiscordBot (8wayrunBot, v2)',
				],
				'query' => [
					'limit' => 1000,
				],
			]);
			$json = $response->json();
		}
		catch (\Exception $e)
		{
			if (!empty($e->getResponse()) && $e->getResponse()->getStatusCode() == 404)
			{
				return false;
			}
			
			throw new \XF\PrintableException(\XF::phrase('error_occurred_while_connecting_with_x',
				['provider' => 'Discord']));
		}
		
		return $json;
	}
	
	public function patchMember($user, $discord, $remove = false)
	{
		$provider = $this->assertSetup();
		$server = $this->getServer();
		$options = $this->options();
		$data = [];
		
		if (!$provider || !$server)
		{
			return false;
		}
		
		if ($options->EWRdiscord_sync_nicks)
		{
			$data['nick'] = $user->username;
		}

		if ($options->EWRdiscord_sync_roles)
		{
			$member = $this->getGuild('/members/'.$discord->provider_key);
			$data['roles'] = [];
			
			foreach ($options->EWRdiscord_roles AS $key => $role)
			{
				if (($role && !$remove && $user->isMemberOf($role)) ||
					(!$role && !empty($member['roles']) && in_array($key, $member['roles'])))
				{
					$data['roles'][] = $key;
				}
			}
			
			if (!empty($member['roles']))
			{
				foreach ($member['roles'] AS $role)
				{
					if (!array_key_exists($role, $options->EWRdiscord_roles))
					{
						$data['roles'][] = $role;
					}
				}
			}
		}
		
		if (!empty($data))
		{
			try
			{
				$client = \XF::app()->http()->client();
				$response = $client->patch('https://discordapp.com/api/guilds/'.$server.'/members/'.$discord->provider_key, [
					'headers' => [
						'Authorization' => 'Bot '.$provider->options['bot_token'],
						'User-Agent' => 'DiscordBot (8wayrunBot, v2)',
						'Content-Type' => 'application/json'
					],
					'body' => json_encode($data),
				]);
			}
			catch (\Exception $e) {}
		}
	}
	
	public function patchMemberBan($user, $discord, $ban = true)
	{
		$provider = $this->assertSetup();
		$server = $this->getServer();
		
		if (!$provider || !$server)
		{
			return false;
		}
		
		try
		{
			$client = \XF::app()->http()->client();
			$payload = ['headers' => [
				'Authorization' => 'Bot '.$provider->options['bot_token'],
				'User-Agent' => 'DiscordBot (8wayrunBot, v2)',
			]];
			
			if ($ban)
			{
				$response = $client->put('https://discordapp.com/api/guilds/'.$server.'/bans/'.$discord->provider_key, $payload);
			}
			else
			{
				$response = $client->delete('https://discordapp.com/api/guilds/'.$server.'/bans/'.$discord->provider_key, $payload);
			}
		}
		catch (\Exception $e) {}
	}
	
	public function createDMChannel($recipient)
	{
		$provider = $this->assertSetup();
		$server = $this->getServer();
		
		if (!$provider || !$server)
		{
			return false;
		}
		
		try
		{
			$client = \XF::app()->http()->client();
			$response = $client->post('https://discordapp.com/api/users/@me/channels', [
				'headers' => [
					'Authorization' => 'Bot '.$provider->options['bot_token'],
					'User-Agent' => 'DiscordBot (8wayrunBot, v2)',
					'Content-Type' => 'application/json'
				],
				'body' => json_encode([
					'recipient_id' => $recipient
				]),
			]);
			
			return $response->json()['id'];
		}
		catch (\Exception $e) {}
	}
	
	public function postToChannel($channel, $data, $endpoint = 'channels/')
	{
		$provider = $this->assertSetup();
		$server = $this->getServer();
		
		if (!$provider || !$server)
		{
			return false;
		}
		
		try
		{
			$client = \XF::app()->http()->client();
			$response = $client->post('https://discordapp.com/api/'.$endpoint.$channel.'/messages', [
				'headers' => [
					'Authorization' => 'Bot '.$provider->options['bot_token'],
					'User-Agent' => 'DiscordBot (8wayrunBot, v2)',
					'Content-Type' => 'application/json'
				],
				'body' => json_encode($data),
			]);
		}
		catch (\Exception $e) {}
	}
	
	public function syncDiscord()
	{
		$discord = $this->finder('XF:UserConnectedAccount')
			->with('User')
			->where('provider', 'discord')
			->where('sync_date', '<', \XF::$time-86400)
			->order('sync_date', 'ASC')
			->fetchOne();
			
		if ($discord)
		{
			$this->patchMember($discord->User, $discord);
			$discord->set('sync_date', \XF::$time);
			$discord->save();
		}
		
		try
		{
			$client = \XF::app()->http()->client();
			$response = $client->get('https://discordapp.com/api/guilds/'.$this->getServer().'/widget.json');
			$json = $response->json();
			
			$cache = [
				'server' => $json['id'],
				'invite' => $json['instant_invite'],
				'online' => count($json['members']),
			];
			
			\XF::app()->simpleCache()->setValue('EWR/Discord', 'discord', $cache);
		}
		catch (\Exception $e) {}
	}
	
	public function getProvider()
	{
		return $this->repository('XF:ConnectedAccount')->findProvidersForList()
			->where('provider_id', 'discord')
			->fetchOne();
	}
	
	public function getServer()
	{
		return $this->options()->EWRdiscord_server;
	}
}