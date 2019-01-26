<?php

namespace EWR\Discord\Entity;

use XF\Mvc\Entity\Structure;

class Thread extends XFCP_Thread
{
	protected function _postSave()
	{
		if ($this->isChanged('discussion_state') && $this->discussion_state == 'visible' && !$this->isInsert())
		{
			$this->FirstPost->postThreadToDiscord($this);
		}
		
		return parent::_postSave();
	}
}