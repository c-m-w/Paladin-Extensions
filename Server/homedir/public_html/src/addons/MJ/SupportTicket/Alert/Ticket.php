<?php

namespace MJ\SupportTicket\Alert;

use XF\Mvc\Entity\Entity;

class Ticket extends \XF\Alert\AbstractHandler
{
	public function getEntityWith()
	{
		$visitor = \XF::visitor();

		return ['Department', 'Department.Permissions|' . $visitor->permission_combination_id];
	}

	public function getTemplateName($action)
	{
		return 'public:mjst_alert_' . $this->contentType . '_' . $action;
	}

	public function getOptOutDisplayOrder()
	{
		return 30104;
	}
}
