<?php

namespace EWR\Discord\Entity;

use XF\Mvc\Entity\Structure;

class Node extends XFCP_Node
{
	public static function getStructure(Structure $structure)
	{
		$parent = parent::getStructure($structure);
		
		$structure->columns['discord_options'] = ['type' => self::SERIALIZED_ARRAY, 'required' => false, 'default' => []];
		
		return $parent;
	}
}