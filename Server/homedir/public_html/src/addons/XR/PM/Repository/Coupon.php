<?php

namespace XR\PM\Repository;

use XF\Mvc\Entity\ArrayCollection;
use XF\Mvc\Entity\Finder;
use XF\Mvc\Entity\Repository;
use XF\Mvc\Reply\AbstractReply;

class Coupon extends Repository
{
	/**
	 * @return Finder
	 */
	public function findCouponsForList()
	{
		$finder = $this->finder('XR\PM:Coupon')
			->setDefaultOrder('coupon_id', 'DESC');

		return $finder;
	}

	/**
	 * @param array $validCouponTypes
	 * @return Finder
	 */
	public function findUsableCoupons(array $validCouponTypes = [])
	{
		$finder = $this->findCouponsForList()
			->where('active', 1);

		if ($validCouponTypes)
		{
			$finder->where('coupon_type', $validCouponTypes);
		}

		return $finder;
	}

	public function filterUsable(ArrayCollection $coupons)
	{
		return $coupons->filter(function(\XR\PM\Entity\Coupon $coupon)
		{
			return $coupon->canUse();
		});
	}
}