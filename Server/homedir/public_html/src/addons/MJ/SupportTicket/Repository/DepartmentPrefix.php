<?php

namespace MJ\SupportTicket\Repository;

use XF\Mvc\Entity\Finder;
use XF\Mvc\Entity\Repository;
use XF\Repository\AbstractPrefixMap;

class DepartmentPrefix extends AbstractPrefixMap
{
	protected function getMapEntityIdentifier()
	{
		return 'MJ\SupportTicket:DepartmentPrefix';
	}

	protected function getAssociationsForPrefix(\XF\Entity\AbstractPrefix $prefix)
	{
		return $prefix->getRelation('DepartmentPrefixes');
	}

	protected function updateAssociationCache(array $cache)
	{
		$ids = array_keys($cache);
		$departments = $this->em->findByIds('MJ\SupportTicket:Department', $ids);

		foreach ($departments as $department)
		{
			/** @var \MJ\SupportTicket\Entity\Department $department */
			$department->prefix_cache = $cache[$department->department_id];
			$department->saveIfChanged();
		}
	}
}
