<?php

namespace MJ\SupportTicket\Entity;

use XF\Entity\AbstractPrefixMap;
use XF\Mvc\Entity\Entity;
use XF\Mvc\Entity\Structure;

/**
 * COLUMNS
 * @property int department_id
 * @property int prefix_id
 *
 * RELATIONS
 * @property \MJ\SupportTicket\Entity\TicketPrefix Prefix
 * @property \MJ\SupportTicket\Entity\Department Department
 */
class DepartmentPrefix extends AbstractPrefixMap
{
	public static function getContainerKey()
	{
		return 'department_id';
	}

	public static function getStructure(Structure $structure)
	{
		self::setupDefaultStructure($structure, 'xf_mjst_department_prefix', 'MJ\SupportTicket:DepartmentPrefix', 'MJ\SupportTicket:TicketPrefix');

		$structure->relations['Department'] = [
			'entity' => 'MJ\SupportTicket:Department',
			'type' => self::TO_ONE,
			'conditions' => 'department_id',
			'primary' => true
		];

		return $structure;
	}
}
