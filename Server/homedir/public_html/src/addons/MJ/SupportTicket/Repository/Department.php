<?php

namespace MJ\SupportTicket\Repository;

use XF\Mvc\Entity\Finder;
use XF\Mvc\Entity\AbstractCollection;
use XF\Mvc\Entity\Repository;

class Department extends Repository
{
	public function getDepartmentList()
	{
		$departments = $this->findDepartmentList()->fetch();

		return $this->filterViewable($departments);
	}

	/**
	 * @return Finder
	 */
	public function findDepartmentList($with = null)
	{
		$finder = $this->finder('MJ\SupportTicket:Department');
		if ($with)
		{
			$finder->with($with);
		}
		$finder->order('display_order');

		return $finder;
	}

	public function getFullDepartmentList($with = null)
	{
		/** @var \XF\Finder\Department $finder */
		$finder = $this->finder('MJ\SupportTicket:Department')->order('display_order');

		if ($with)
		{
			$finder->with($with);
		}

		return $finder->fetch();
	}

	public function getViewableDepartments($with = null)
	{
		if ($with === null)
		{
			$with = [];
		}
		else
		{
			$with = (array)$with;
		}

		$with = [
			'Permissions|' . \XF::visitor()->permission_combination_id
		];

		$departments = $this->findDepartmentList($with)->fetch();
		return $this->filterViewable($departments);
	}

	public function getOpenableDepartments($with = null)
	{
		$departments = $this->getViewableDepartments($with);
		return $this->filterOpenable($departments);
	}

	public function getViewableAnyDepartments($with = null)
	{
		$departments = $this->getViewableDepartments($with);
		return $this->filterViewableAny($departments);
	}

	public function filterViewableAny(AbstractCollection $departments)
	{
		if (!$departments->count())
		{
			return $departments;
		}

		\XF::visitor()->cacheSupportDepartmentPermissions();
		return $departments->filter(function($entity)
		{
			// TODO: ideally type hint the viewable interface
			return $entity->canViewAnyTicket();
		});
	}

	public function filterOpenable(AbstractCollection $departments)
	{
		if (!$departments->count())
		{
			return $departments;
		}

		\XF::visitor()->cacheSupportDepartmentPermissions();
		return $departments->filter(function($entity)
		{
			// TODO: ideally type hint the viewable interface
			return $entity->canOpenTicket();
		});
	}

	public function filterViewable(AbstractCollection $departments)
	{
		if (!$departments->count())
		{
			return $departments;
		}

		\XF::visitor()->cacheSupportDepartmentPermissions();
		return $departments->filterViewable();
	}
}
