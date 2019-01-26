<?php

namespace EWR\Discord\Entity;

use XF\Mvc\Entity\Structure;

class XFMGItem extends XFCP_XFMGItem
{
	protected function _postSave()
	{
		$parent = parent::_postSave();
		
		if ($this->media_state == 'visible' &&
			($this->isInsert() || $this->isChanged('media_state')))
		{
			if (!empty(\XF::options()->EWRdiscord_channels['xfmg']))
			{
				$channel = \XF::options()->EWRdiscord_channels['xfmg'];
				
				$url = \XF::app()->router('public')->buildLink('canonical:media', $this);
				$icon = $this->User ? $this->User->getAvatarUrl('s', null, true) : '';
				$length = \XF::options()->EWRdiscord_payload;
			
				$content = \XF::phrase('EWRdiscord_x_posted_new_media_y', [
					'user' => $this->username,
					'title' => str_replace('@', '@𝅳', $this->title),
					'url' => $url
				])->render('raw');
				
				$image = $this->getCurrentThumbnailUrl(true);
				
				$data = [
					'content' => $content,
					'embed' => [
						'description' => str_replace('@', '@𝅳',
							htmlspecialchars_decode(\XF::app()->stringFormatter()->snippetString($this->description, $length,
								['stripBbCode' => true]))),
						'url' => $url,
						'image' => [
							'url' => $image,
						],
						'thumbnail' => [
							'url' => $icon,
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