<?php

namespace MJ\SupportTicket\Repository;

use XF\Repository\AbstractField;

class TicketField extends AbstractField
{
	protected function getRegistryKey()
	{
		return 'mjstTicketFields';
	}

	protected function getClassIdentifier()
	{
		return 'MJ\SupportTicket:TicketField';
	}

	public function getDisplayGroups()
	{
		return [
			'before'         => \XF::phrase('before_message'),
			'after'          => \XF::phrase('after_message'),
			'ticket_info'    => \XF::phrase('mjst_ticket_info'),
			'submitter_info' => \XF::phrase('mjst_submitter_info')
		];
	}
}
