<?php

namespace MJ\SupportTicket\Entity;

use XF\Entity\AbstractPrefixGroup;
use XF\Mvc\Entity\Structure;

/**
 * COLUMNS
 * @property int|null prefix_group_id
 * @property int display_order
 *
 * GETTERS
 * @property \XF\Phrase|string title
 *
 * RELATIONS
 * @property \XF\Entity\Phrase MasterTitle
 * @property \MJ\SupportTicket\Entity\TicketPrefix[] Prefixes
 */
class TicketPrefixGroup extends AbstractPrefixGroup
{
	protected function getClassIdentifier()
	{
		return 'MJ\SupportTicket:TicketPrefix';
	}

	protected static function getContentType()
	{
		return 'support_ticket';
	}

	public static function getStructure(Structure $structure)
	{
		self::setupDefaultStructure(
			$structure,
			'xf_mjst_ticket_prefix_group',
			'MJ\SupportTicket:TicketPrefixGroup',
			'MJ\SupportTicket:TicketPrefix'
		);

		return $structure;
	}
}
