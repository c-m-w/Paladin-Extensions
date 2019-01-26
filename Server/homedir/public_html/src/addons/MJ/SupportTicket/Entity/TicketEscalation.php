<?php

namespace MJ\SupportTicket\Entity;

use XF\Mvc\Entity\Entity;
use XF\Mvc\Entity\Structure;

class TicketEscalation extends Entity
{
	public static function getStructure(Structure $structure)
	{
		$structure->table = 'xf_mjst_ticket_escalation';
		$structure->shortName = 'MJ\SupportTicket:TicketEscalation';
		$structure->primaryKey = 'ticket_escalation_id';
		$structure->columns = [
			'ticket_escalation_id' => ['type' => self::UINT, 'nullable' => true, 'autoIncrement' => true],
			'title'                => ['type' => self::STR, 'required' => true],
			'department_ids'       => ['type' => self::LIST_COMMA, 'default' => [],
				'list' => ['type' => 'posint', 'unique' => true, 'sort' => SORT_NUMERIC]
			],
			'ticket_status_ids'    => ['type' => self::LIST_COMMA, 'default' => [],
				'list' => ['type' => 'posint', 'unique' => true, 'sort' => SORT_NUMERIC]
			],
			'priorities'           => ['type' => self::LIST_COMMA, 'default' => [],
				'list' => ['type' => 'posint', 'unique' => true, 'sort' => SORT_NUMERIC]
			],
			'time_elapsed'         => ['type' => self::UINT, 'default' => 0],
			'new_department_id'    => ['type' => self::UINT, 'default' => 0],
			'new_priority'         => ['type' => self::UINT, 'default' => 0],
			'new_ticket_status_id' => ['type' => self::UINT, 'default' => 0],
			'reply_message'        => ['type' => self::STR, 'default' => ''],
			'reply_user_id'        => ['type' => self::UINT, 'default' => 0]
		];
		$structure->relations = [
			'User' => [
				'entity' => 'XF:User',
				'type' => self::TO_ONE,
				'conditions' => [
					['user_id', '=', '$reply_user_id']
				],
				'primary' => true
			],
		];
		$structure->getters = [];

		return $structure;
	}
}
