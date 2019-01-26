<?php

namespace EWR\Discord\Entity;

use XF\Mvc\Entity\Structure;

class UserOption extends XFCP_UserOption
{
	public static function getStructure(Structure $structure)
	{
		$parent = parent::getStructure($structure);
		
		$structure->columns['discord_options'] = ['type' => self::JSON_ARRAY, 'required' => false, 'default' => []];
		
		return $parent;
	}
}