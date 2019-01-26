<?php

namespace MJ\SupportTicket\Entity;

use XF\Mvc\Entity\Entity;
use XF\Mvc\Entity\Structure;

class TicketEscalationLog extends Entity
{
	public static function getStructure(Structure $structure)
	{
		$structure->table = 'xf_mjst_ticket_escalation_log';
		$structure->shortName = 'MJ\SupportTicket:TicketEscalationLog';
		$structure->columns = [
			'escalation_log_id' => ['type' => self::UINT, 'required' => true],
			'escalation_id'     => ['type' => self::UINT, 'required' => true],
			'support_ticket_id' => ['type' => self::UINT, 'required' => true],
			'log_date'          => ['type' => self::UINT, 'default' => \XF::$time]
		];
		$structure->relations = [
			'Escalation' => [
				'entity'     => 'MJ\SupportTicket:TicketEscalation',
				'type'       => self::TO_ONE,
				'conditions' => 'escalation_id',
				'primary'    => true
			],
			'Ticket' => [
				'entity'     => 'MJ\SupportTicket:TicketEscalation',
				'type'       => self::TO_ONE,
				'conditions' => 'support_ticket_id',
				'primary'    => true
			],
		];
		$structure->getters = [];

		return $structure;
	}
}