<?php

namespace XR\PM\Job;

use XF\Job\AbstractRebuildJob;

class Category extends AbstractRebuildJob
{
	protected function getNextIds($start, $batch)
	{
		$db = $this->app->db();

		return $db->fetchAllColumn($db->limit(
			"
				SELECT category_id
				FROM xf_xr_pm_category
				WHERE category_id > ?
				ORDER BY category_id
			", $batch
		), $start);
	}

	protected function rebuildById($id)
	{
		/** @var \XR\PM\Entity\Category $category */
		$category = $this->app->em()->find('XR\PM:Category', $id);
		if ($category)
		{
			$category->rebuildCounters();
			$category->save();
		}
	}

	protected function getStatusType()
	{
		return 'Product categories';
	}
}