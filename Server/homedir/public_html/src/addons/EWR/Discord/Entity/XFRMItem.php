<?php

namespace EWR\Discord\Entity;

use XF\Mvc\Entity\Structure;

class XFRMItem extends XFCP_XFRMItem
{
	protected function _postSave()
	{
		$parent = parent::_postSave();
		
		if ($this->resource_state == 'visible' &&
			($this->isInsert() || $this->isChanged('resource_state')))
		{
			if (!empty(\XF::options()->EWRdiscord_channels['xfrm']))
			{
				$channel = \XF::options()->EWRdiscord_channels['xfrm'];
				
				$url = \XF::app()->router('public')->buildLink('canonical:resources', $this);
				$icon = $this->User ? $this->User->getAvatarUrl('s', null, true) : '';
				$length = \XF::options()->EWRdiscord_payload;
			
				$content = \XF::phrase('EWRdiscord_x_posted_new_resource_y', [
					'user' => $this->username,
					'title' => str_replace('@', '@𝅳', $this->title),
					'url' => $url
				])->render('raw');
				
				$data = [
					'content' => $content,
					'embed' => [
						'description' => str_replace('@', '@𝅳',
							htmlspecialchars_decode(\XF::app()->stringFormatter()->snippetString($this->tag_line, $length,
								['stripBbCode' => true]))),
						'url' => $url,
						'thumbnail' => [
							'url' => $this->getIconUrl(null, true),
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