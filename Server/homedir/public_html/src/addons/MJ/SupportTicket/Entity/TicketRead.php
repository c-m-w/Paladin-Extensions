<?php

namespace MJ\SupportTicket\Entity;

use XF\Mvc\Entity\Entity;
use XF\Mvc\Entity\Structure;

/**
 * COLUMNS
 * @property int|null support_ticket_read_id
 * @property int user_id
 * @property int ticket_id
 * @property int support_ticket_read_date
 *
 * RELATIONS
 * @property \XF\Entity\User User
 * @property \MJ\SupportTicket\Entity\Ticket Ticket
 */
class TicketRead extends Entity
{
	public static function getStructure(Structure $structure)
	{
		$structure->table = 'xf_mjst_ticket_read';
		$structure->shortName = 'MJ\SupportTicket:TicketRead';
		$structure->primaryKey = 'support_ticket_read_id';
		$structure->columns = [
			'support_ticket_read_id'   => ['type' => self::UINT, 'autoIncrement' => true, 'nullable' => true],
			'user_id'                  => ['type' => self::UINT, 'required' => true],
			'support_ticket_id'        => ['type' => self::UINT, 'required' => true],
			'support_ticket_read_date' => ['type' => self::UINT, 'required' => true]
		];
		$structure->getters = [];
		$structure->relations = [
			'User' => [
				'entity' => 'XF:User',
				'type' => self::TO_ONE,
				'conditions' => 'user_id',
				'primary' => true
			],
			'Ticket' => [
				'entity' => 'MJ\SupportTicket:Ticket',
				'type' => self::TO_ONE,
				'conditions' => 'support_ticket_id',
				'primary' => true
			],
		];

		return $structure;
	}
}
