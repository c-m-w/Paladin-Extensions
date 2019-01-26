<?php

namespace XR\PM\XF\Repository;

class Payment extends XFCP_Payment
{
	public function getPaymentProfileTitlePairs()
	{
		return $this->findPaymentProfilesForList()->fetch()->pluckNamed('title', 'payment_profile_id');
	}

	public function getPaymentProfileOptionsData($includeEmpty = true)
	{
		$choices = [];
		if ($includeEmpty)
		{
			$choices = [
				0 => ['value' => 0, 'label' => \XF::phrase('(choose_payment_method)')]
			];
		}

		$choices += $this->getPaymentProfileTitlePairs();

		return $choices;
	}
}