<?php

namespace XR\PM\Alert;

use XF\Alert\AbstractHandler;
use XF\Mvc\Entity\Entity;

class Purchase extends AbstractHandler
{
	public function canViewContent(Entity $entity, &$error = null)
	{
		return $entity->canView();
	}

	public function getEntityWith()
	{
		return ['Product', 'User'];
	}
}