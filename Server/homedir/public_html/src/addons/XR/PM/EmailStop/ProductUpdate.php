<?php

namespace XR\PM\EmailStop;

use XF\EmailStop\AbstractHandler;

class ProductUpdate extends AbstractHandler
{
	public function getStopOneText(\XF\Entity\User $user, $contentId)
	{
	}

	public function getStopAllText(\XF\Entity\User $user)
	{
		return \XF::phrase('xr_pm_you_sure_youd_like_to_unsubscribe_from_all_product_updates');
	}

	public function stopOne(\XF\Entity\User $user, $contentId)
	{
	}

	public function stopAll(\XF\Entity\User $user)
	{
		$user->Option->fastUpdate('xr_pm_receive_update_email', false);
	}
}