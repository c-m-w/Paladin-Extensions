<?php

namespace Siropu\ReferralContests\Cron;

class Contest
{
	public static function getContestWinner()
	{
		$contests = self::getContestRepo()
			->findContests()
			->where('end_date', '<>', 0)
			->where('end_date', '<=', \XF::$time)
			->isEnabled()
			->fetch();

		foreach ($contests as $contest)
		{
			$topReferrers = $contest->top_referrers;

			if ($topReferrers)
			{
				foreach ($contest->prizes as $counter => $prize)
				{
					$rewardType = \XF::em()->find('Siropu\ReferralContests:RewardType', $prize['reward_type_id']);

					if ($rewardType && isset($topReferrers[$counter]))
					{
						$referrer   = $topReferrers[$counter];
                              $userEntity = \XF::em()->find('XF:User', $referrer['user_id']);

						if ($rewardType->isTrophyPoints())
						{
							$userEntity->trophy_points += $prize['reward_amount'];
							$userEntity->save();
						}
						else if ($rewardType->isDbTechCredits())
						{
							$rewardType->applyDbTechCredits(
								$userEntity,
								$prize['reward_amount'],
								'siropu_referral_contests_reward_for_contest_placing'
							);
						}
					}
				}

				$contest->referral_count = $contest->total_referrals;
				$contest->winner_user_id = $contest->winner['user_id'];

				\XF::repository('XF:UserAlert')->alert(
				    $contest->User,
				    $contest->User->user_id,
				    $contest->User->username,
				    'siropu_referral_contests',
				    $contest->contest_id,
				    'winner'
			    );
			}

			$contest->enabled = 0;
			$contest->save();
		}
	}
	/**
      * @return \Siropu\ReferralContests\Repository\Contest
      */
     private static function getContestRepo()
     {
          return \XF::app()->repository('Siropu\ReferralContests:Contest');
     }
}
