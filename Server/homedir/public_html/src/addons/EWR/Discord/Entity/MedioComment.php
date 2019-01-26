<?php

namespace EWR\Discord\Entity;

use XF\Mvc\Entity\Structure;

class MedioComment extends XFCP_MedioComment
{
	protected function _postSave()
	{
		if ($this->comment_state == 'visible' &&
			($this->isInsert() || $this->isChanged('comment_state')))
		{
			if (!empty(\XF::options()->EWRdiscord_channels['ewrmediocomments']))
			{
				$channel = \XF::options()->EWRdiscord_channels['ewrmediocomments'];
				$length = \XF::options()->EWRdiscord_payload;
				
				$data = [
					'content' => \XF::phrase('EWRdiscord_x_commented_on_media_y', [
							'user' => $this->username,
							'title' => str_replace('@', '@𝅳', $this->Media->media_title),
							'url' => \XF::app()->router()->buildLink('canonical:ewr-medio/posts', $this)
						])->render(),
					'embed' => [
						'description' => str_replace('@', '@𝅳',
							htmlspecialchars_decode(\XF::app()->stringFormatter()->snippetString($this->comment_message,
								$length, ['stripBbCode' => true]))),
					],
				];
				
				$this->repository('EWR\Discord:Discord')->postToChannel($channel, $data);
			}
		}
		
		return parent::_postSave();
	}
}