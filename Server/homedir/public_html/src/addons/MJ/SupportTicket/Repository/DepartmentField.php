<?php

namespace MJ\SupportTicket\Repository;

use XF\Mvc\Entity\Finder;
use XF\Mvc\Entity\Repository;
use XF\Repository\AbstractFieldMap;

class DepartmentField extends AbstractFieldMap
{
	protected function getMapEntityIdentifier()
	{
		return 'MJ\SupportTicket:DepartmentField';
	}

	protected function getAssociationsForField(\XF\Entity\AbstractField $field)
	{
		return $field->getRelation('DepartmentFields');
	}

	protected function updateAssociationCache(array $cache)
	{
		$departmentIds = array_keys($cache);
		$departments = $this->em->findByIds('MJ\SupportTicket:Department', $departmentIds);

		foreach ($departments as $department)
		{
			/** @var \MJ\SupportTicket\Entity\Department $department */
			$department->field_cache = $cache[$department->department_id];
			$department->saveIfChanged();
		}
	}
}
