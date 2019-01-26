<?php

namespace MJ\SupportTicket\Entity;

use XF\Mvc\Entity\Entity;
use XF\Mvc\Entity\Structure;

/**
 * COLUMNS
 * @property int ticket_id
 * @property string field_id
 * @property string field_value
 */
class TicketFieldValue extends Entity
{
	public static function getStructure(Structure $structure)
	{
		$structure->table = 'xf_mjst_ticket_field_value';
		$structure->shortName = 'MJ\SupportTicket:TicketFieldValue';
		$structure->primaryKey = ['support_ticket_id', 'field_id'];
		$structure->columns = [
			'support_ticket_id' => ['type' => self::UINT, 'required' => true],
			'field_id'          => ['type' => self::STR, 'maxLength' => 25,
				'match'         => 'alphanumeric'
			],
			'field_value'       => ['type' => self::STR, 'default' => '']
		];
		$structure->getters = [];
		$structure->relations = [];

		return $structure;
	}
}
