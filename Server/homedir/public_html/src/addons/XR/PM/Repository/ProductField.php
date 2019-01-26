<?php

namespace XR\PM\Repository;

use XF\Repository\AbstractField;

class ProductField extends AbstractField
{
	protected function getRegistryKey()
	{
		return 'xrpmProductFields';
	}

	protected function getClassIdentifier()
	{
		return 'XR\PM:ProductField';
	}

	public function getDisplayGroups()
	{
		return [
			'tab_content' => \XF::phrase('xr_pm_tab_content'),
			'tab_link' => \XF::phrase('xr_pm_tab_link'),
			'above_details' => \XF::phrase('xr_pm_above_details'),
			'below_details' => \XF::phrase('xr_pm_below_details')
		];
	}
}