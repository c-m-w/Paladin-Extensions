<?php

namespace EWR\Discord\Entity;

use XF\Mvc\Entity\Structure;

class User extends XFCP_User
{
	protected function _postSave()
	{
		if (($this->isChanged('username') || $this->isChanged('user_group_id') ||
			$this->isChanged('secondary_group_ids')) && $this->Discord)
		{
			if (\XF::options()->EWRdiscord_sync_nicks || \XF::options()->EWRdiscord_sync_roles)
			{
				$this->repository('EWR\Discord:Discord')->patchMember($this, $this->Discord);
				$this->Discord->set('sync_date', \XF::$time, ['forceSet' => true]);
				$this->Discord->save();
			}
		}
		
		if ($this->isChanged('is_banned') && $this->Discord)
		{
			if (\XF::options()->EWRdiscord_sync_bans)
			{
				$this->repository('EWR\Discord:Discord')->patchMemberBan($this, $this->Discord, $this->is_banned);
			}
		}
		
		return parent::_postSave();
	}
	
	protected function _preDelete()
	{
		if ($this->Discord)
		{
			if (\XF::options()->EWRdiscord_sync_nicks || \XF::options()->EWRdiscord_sync_roles)
			{
				$this->repository('EWR\Discord:Discord')->patchMember($this, $this->Discord, true);
			}
		}
		
		return parent::_preDelete();
	}
	
	public static function getStructure(Structure $structure)
	{
		$parent = parent::getStructure($structure);
		
		$structure->relations['Discord'] = [
			'entity' => 'XF:UserConnectedAccount',
			'type' => self::TO_ONE,
			'conditions' => [
				['user_id', '=', '$user_id'],
				['provider', '=', 'discord']
			],
			'key' => 'provider',
		];
		
		return $parent;
	}
}