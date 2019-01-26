<?php

namespace Siropu\ReferralContests\Option;

class RewardTypes extends \XF\Option\AbstractOption
{
	public static function renderOption(\XF\Entity\Option $option, array $htmlParams)
	{
		$rewardTypes = \XF::repository('Siropu\ReferralContests:RewardType')
			->findRewardTypesForList()
			->fetch()
			->pluckNamed('name', 'reward_type_id');

		return self::getTemplate('admin:siropu_referral_contests_option_template_rewardTypes', $option, $htmlParams, [
			'rewardTypes' => $rewardTypes
		]);
	}
	public static function verifyOption(array &$value)
	{


		return true;
	}
}
