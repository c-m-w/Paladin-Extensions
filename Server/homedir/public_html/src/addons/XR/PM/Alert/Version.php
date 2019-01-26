<?php

namespace XR\PM\Alert;

use XF\Alert\AbstractHandler;
use XF\Mvc\Entity\Entity;

class Version extends AbstractHandler
{
	public function canViewContent(Entity $entity, &$error = null)
	{
		return $entity->Product->canView();
	}

	public function getEntityWith()
	{
		return ['Product'];
	}
}