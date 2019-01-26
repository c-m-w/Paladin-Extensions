<?php

namespace MJ\SupportTicket\Entity;

use XF\Entity\AbstractFieldMap;
use XF\Mvc\Entity\Structure;

/**
 * COLUMNS
 * @property int department_id
 * @property int field_id
 *
 * RELATIONS
 * @property \MJ\SupportTicket\Entity\TicketField Field
 * @property \MJ\SupportTicket\Entity\Department Department
 */
class DepartmentField extends AbstractFieldMap
{
	public static function getContainerKey()
	{
		return 'department_id';
	}

	public static function getStructure(Structure $structure)
	{
		self::setupDefaultStructure(
			$structure,
			'xf_mjst_department_field',
			'MJ\SupportTicket:DepartmentField',
			'MJ\SupportTicket:TicketField'
		);

		$structure->relations['Department'] = [
			'entity' => 'MJ\SupportTicket:Department',
			'type' => self::TO_ONE,
			'conditions' => 'department_id',
			'primary' => true
		];

		return $structure;
	}
}
