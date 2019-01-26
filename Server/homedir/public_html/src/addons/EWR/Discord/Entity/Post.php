<?php

namespace EWR\Discord\Entity;

use XF\Mvc\Entity\Structure;

class Post extends XFCP_Post
{
	protected function _postSave()
	{
		$parent = parent::_postSave();
		
		if (!$this->position && $this->Thread->discussion_state == 'visible' && $this->isInsert())
		{
			$this->postThreadToDiscord($this->Thread, $this);
		}
		
		if ($this->position && $this->message_state == 'visible' &&
			($this->isInsert() || $this->isChanged('message_state')))
		{
			$discord = $this->Thread->Forum->Node->discord_options;
			
			if (!empty(\XF::options()->EWRdiscord_channels['posts']) || !empty($discord['posts']['channel']))
			{
				$url = \XF::app()->router('public')->buildLink('canonical:posts', $this);
				$length = !empty($discord['posts']['payload']) ? $discord['posts']['payload'] : \XF::options()->EWRdiscord_payload;
				
				if (!empty($discord['posts']['channel']))
				{
					if ($discord['posts']['channel'] > 0)
					{
						$channel = $discord['posts']['channel'];
					}
					else
					{
						return parent::_postSave();
					}
				}
				else
				{
					$channel = \XF::options()->EWRdiscord_channels['posts'];
				}
					
				if (!empty($discord['posts']['message']))
				{
					$content = str_ireplace(
						['{user}', '{title}', '{url}'],
						[$this->username, $this->Thread->title, $url],
						$discord['posts']['message']
					);
				}
				else
				{
					$content = \XF::phrase('EWRdiscord_x_replied_to_thread_y', [
						'user' => $this->username,
						'title' => str_replace('@', '@𝅳', $this->Thread->title),
						'url' => $url
					])->render('raw');
				}
				
				$data = [
					'content' => $content,
					'embed' => [
						'description' => str_replace('@', '@𝅳',
							htmlspecialchars_decode(\XF::app()->stringFormatter()->snippetString($this->message,
								$length, ['stripBbCode' => true]))),
					],
				];
				
				$this->repository('EWR\Discord:Discord')->postToChannel($channel, $data);
			}
		}
		
		return $parent;
	}
	
	public function postThreadToDiscord($thread)
	{
		$discord = $thread->Forum->Node->discord_options;
			
		if (!empty(\XF::options()->EWRdiscord_channels['threads']) || !empty($discord['threads']['channel']))
		{
			$url = \XF::app()->router('public')->buildLink('canonical:threads', $thread);
			$icon = $thread->User ? $thread->User->getAvatarUrl('s', null, true) : '';
			$length = !empty($discord['threads']['payload']) ? $discord['threads']['payload'] : \XF::options()->EWRdiscord_payload;
			
			if (!empty($discord['threads']['channel']))
			{
				if ($discord['threads']['channel'] > 0)
				{
					$channel = $discord['threads']['channel'];
				}
				else
				{
					return parent::_postSave();
				}
			}
			else
			{
				$channel = \XF::options()->EWRdiscord_channels['threads'];
			}
				
			if (!empty($discord['threads']['message']))
			{
				$content = str_ireplace(
					['{user}', '{title}', '{url}'],
					[$thread->username, str_replace('@', '@𝅳', $thread->title), $url],
					$discord['threads']['message']
				);
			}
			else
			{
				$content = \XF::phrase('EWRdiscord_x_posted_new_thread_y', [
					'user' => $thread->username,
					'title' => str_replace('@', '@𝅳', $thread->title),
					'url' => $url
				])->render('raw');
			}
			
			$data = [
				'content' => $content,
				'embed' => [
					'title' => $thread->title,
					'description' => str_replace('@', '@𝅳',
						htmlspecialchars_decode(\XF::app()->stringFormatter()->snippetString($this->message, $length,
							['stripBbCode' => true]))),
					'url' => $url,
					'thumbnail' => [
						'url' => $icon,
					],
					'author' => [
						'name' => $thread->username,
						'url' => $thread->User ? \XF::app()->router('public')->buildLink('canonical:members', $thread->User) : '',
						'icon_url' => $icon,
					],
				],
			];
			
			$this->repository('EWR\Discord:Discord')->postToChannel($channel, $data);
		}
	}
}