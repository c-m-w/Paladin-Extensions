<?php

namespace MJ\SupportTicket\Finder;

use XF\Mvc\Entity\Finder;

class Ticket extends Finder
{
	public function watchedOnly($userId = null)
	{
		if ($userId === null)
		{
			$userId = \XF::visitor()->user_id;
		}
		if (!$userId)
		{
			// no user, just ignore
			return $this;
		}

		$this->whereOr(
			['Watch|' . $userId . '.user_id', '!=', null],
			['Department.Watch|' . $userId . '.user_id', '!=', null]
		);

		return $this;
	}

	public function forFullView($includeDepartment = true)
	{
		$visitor = \XF::visitor();

		$this->with(['User']);

		if ($visitor->user_id)
		{
			$this->with('Watch|' . $visitor->user_id);
		}

		if ($includeDepartment)
		{
			$this->with(['Department']);

			if ($visitor->user_id)
			{
				$this->with('Department.Watch|' . $visitor->user_id);
			}
		}

		return $this;
	}

	public function useDefaultOrder()
	{
		$defaultSort = $this->app()->options()->mjstDefaultSortOrder;
		$defaultOrder = !empty($defaultSort['order']) ? $defaultSort['order'] : 'last_update';
		$defaultDir = !empty($defaultSort['direction']) ? $defaultSort['direction'] : 'desc';

		$this->setDefaultOrder($defaultOrder, $defaultDir);

		return $this;
	}
}
