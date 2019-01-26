<?php

namespace EWR\Discord\Entity;

use XF\Mvc\Entity\Structure;

class UserConnectedAccount extends XFCP_UserConnectedAccount
{
	protected function _preSave()
	{
		if ($this->isInsert() && $this->provider == 'discord')
		{
			if (\XF::options()->EWRdiscord_sync_nicks || \XF::options()->EWRdiscord_sync_roles)
			{
				$this->repository('EWR\Discord:Discord')->patchMember($this->User, $this);
				$this->sync_date = \XF::$time;
			}
		}
		
		return parent::_preSave();
	}
	
	protected function _preDelete()
	{
		if ($this->provider == 'discord')
		{
			if (\XF::options()->EWRdiscord_sync_nicks || \XF::options()->EWRdiscord_sync_roles)
			{
				$this->repository('EWR\Discord:Discord')->patchMember($this->User, $this, true);
			}
		}
		
		return parent::_preDelete();
	}
	
	public static function getStructure(Structure $structure)
	{
		$parent = parent::getStructure($structure);
		
		$structure->columns['sync_date'] = ['type' => self::UINT, 'required' => false, 'default' => 0];
		
		return $parent;
	}
}