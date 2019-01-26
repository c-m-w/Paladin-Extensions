<?php

namespace EWR\Discord\Entity;

use XF\Mvc\Entity\Structure;

class XFMGComment extends XFCP_XFMGComment
{
	protected function _postSave()
	{
		$parent = parent::_postSave();
		
		if ($this->comment_state == 'visible' &&
			($this->isInsert() || $this->isChanged('comment_state')))
		{
			if (!empty(\XF::options()->EWRdiscord_channels['xfmgcomments']))
			{
				$channel = \XF::options()->EWRdiscord_channels['xfmgcomments'];
				$length = \XF::options()->EWRdiscord_payload;
				
				$data = [
					'content' => \XF::phrase('EWRdiscord_x_commented_on_media_y', [
							'user' => $this->username,
							'title' => str_replace('@', '@𝅳', $this->Media->title),
							'url' => \XF::app()->router('public')->buildLink('canonical:media', $this->Media)
						])->render('raw'),
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
}