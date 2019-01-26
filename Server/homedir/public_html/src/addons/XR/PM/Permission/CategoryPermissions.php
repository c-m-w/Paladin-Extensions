<?php

namespace XR\PM\Permission;

use XF\Mvc\Entity\Entity;
use XF\Permission\TreeContentPermissions;

class CategoryPermissions extends TreeContentPermissions
{
	public function getContentType()
	{
		return 'xr_pm_category';
	}

	public function getAnalysisTypeTitle()
	{
		return \XF::phrase('xr_pm_product_category_permissions');
	}

	public function getContentTitle(Entity $entity)
	{
		return $entity->title;
	}

	public function isValidPermission(\XF\Entity\Permission $permission)
	{
		return ($permission->permission_group_id == 'xr_pm');
	}

	public function getContentTree()
	{
		/** @var \XR\PM\Repository\Category $categoryRepo */
		$categoryRepo = $this->builder->em()->getRepository('XR\PM:Category');
		return $categoryRepo->createCategoryTree($categoryRepo->findCategoryList()->fetch());
	}

	protected function getFinalPerms($contentId, array $calculated, array &$childPerms)
	{
		if (!isset($calculated['xr_pm']))
		{
			$calculated['xr_pm'] = [];
		}

		$final = $this->builder->finalizePermissionValues($calculated['xr_pm']);

		if (empty($final['view']))
		{
			$childPerms['xr_pm']['view'] = 'deny';
		}

		return $final;
	}

	protected function getFinalAnalysisPerms($contentId, array $calculated, array &$childPerms)
	{
		$final = $this->builder->finalizePermissionValues($calculated);

		if (empty($final['xr_pm']['view']))
		{
			$childPerms['xr_pm']['view'] = 'deny';
		}

		return $final;
	}
}