<?php

namespace MJ\SupportTicket\Repository;

use XF\Repository\AbstractPrefix;

class TicketPrefix extends AbstractPrefix
{
	protected function getRegistryKey()
	{
		return 'mjstPrefixes';
	}

	protected function getClassIdentifier()
	{
		return 'MJ\SupportTicket:TicketPrefix';
	}
}
