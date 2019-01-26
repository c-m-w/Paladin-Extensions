<?php

namespace EWR\Discord\Entity;

use XF\Mvc\Entity\Structure;

class ProfilePost extends XFCP_ProfilePost
{
	protected function _postSave()
	{
		if ($this->message_state == 'visible' &&
			($this->isInsert() || $this->isChanged('message_state')))
		{
			if (!empty(\XF::options()->EWRdiscord_channels['profile']) && $this->user_id == $this->profile_user_id)
			{
				$channel = \XF::options()->EWRdiscord_channels['profile'];
				
				$data = [
					'content' => \XF::phrase('EWRdiscord_x_updated_status_y', [
							'user' => $this->username,
							'title' => str_replace('@', '@𝅳', $this->message),
							'url' => \XF::app()->router()->buildLink('canonical:profile-posts', $this)
						])->render(),
				];
				
				$this->repository('EWR\Discord:Discord')->postToChannel($channel, $data);
			}
		}
		
		return parent::_postSave();
	}
}