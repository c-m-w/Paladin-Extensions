<?php

namespace MJ\SupportTicket\Entity;

use XF\Mvc\Entity\Entity;
use XF\Mvc\Entity\Structure;

/**
 * COLUMNS
 * @property int user_id
 * @property int support_ticket_id
 * @property bool email_subscribe
 *
 * RELATIONS
 * @property \MJ\SupportTicket\Entity\Ticket Ticket
 * @property \XF\Entity\User User
 */
class TicketWatch extends Entity
{
	public static function getStructure(Structure $structure)
	{
		$structure->table = 'xf_mjst_ticket_watch';
		$structure->shortName = 'MJ\SupportTicket:TicketWatch';
		$structure->primaryKey = ['user_id', 'support_ticket_id'];
		$structure->columns = [
			'user_id'           => ['type' => self::UINT, 'required' => true],
			'support_ticket_id' => ['type' => self::UINT, 'required' => true],
			'email_subscribe'   => ['type' => self::BOOL, 'default' => false]
		];
		$structure->getters = [];
		$structure->relations = [
			'Ticket' => [
				'entity' => 'MJ\SupportTicket:Ticket',
				'type' => self::TO_ONE,
				'conditions' => 'support_ticket_id',
				'primary' => true
			],
			'User' => [
				'entity' => 'XF:User',
				'type' => self::TO_ONE,
				'conditions' => 'user_id',
				'primary' => true
			],
		];

		return $structure;
	}
}
