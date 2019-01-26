<?php

namespace EWR\Discord\Entity;

use XF\Mvc\Entity\Structure;

class XFRMUpdate extends XFCP_XFRMUpdate
{
	protected function _postSave()
	{
		$parent = parent::_postSave();
		
		if ($this->message_state == 'visible' &&
			($this->isInsert() || $this->isChanged('message_state')))
		{
			if (!empty(\XF::options()->EWRdiscord_channels['xfrmupdate']))
			{
				$channel = \XF::options()->EWRdiscord_channels['xfrmupdate'];
				
				$url = \XF::app()->router('public')->buildLink('canonical:resources', $this->Resource);
				$icon = $this->Resource->User ? $this->Resource->User->getAvatarUrl('s', null, true) : '';
				$length = \XF::options()->EWRdiscord_payload;
			
				$content = \XF::phrase('EWRdiscord_x_updated_resource_y', [
					'user' => $this->Resource->username,
					'title' => str_replace('@', '@𝅳', $this->Resource->title),
					'url' => $url
				])->render('raw');
				
				$data = [
					'content' => $content,
					'embed' => [
						'description' => str_replace('@', '@𝅳',
							htmlspecialchars_decode(\XF::app()->stringFormatter()->snippetString($this->message, $length,
								['stripBbCode' => true]))),
						'url' => $url,
						'thumbnail' => [
							'url' => $this->Resource->getIconUrl(null, true),
						],
						'author' => [
							'name' => $this->title,
							'url' => $url,
							'icon_url' => $icon,
						],
					],
				];
				
				$this->repository('EWR\Discord:Discord')->postToChannel($channel, $data);
			}
		}
		
		return $parent;
	}
}