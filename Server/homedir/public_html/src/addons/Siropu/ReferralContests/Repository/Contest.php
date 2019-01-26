<?php

namespace Siropu\ReferralContests\Repository;

use XF\Mvc\Entity\Finder;
use XF\Mvc\Entity\Repository;

class Contest extends Repository
{
     public function findContests()
     {
          return $this->finder('Siropu\ReferralContests:Contest');
     }
     public function findContestsForPublicDisplay()
     {
          return $this->findContests()
               ->isEnabled()
               ->whereOr([['end_date', 0], ['end_date', '>=', \XF::$time]]);
     }
     public function getContestTotalReferrals($contest)
     {
          return $this->finder('XF:User')
               ->where('siropu_referrer_id', '<>', 0)
               ->where('register_date', '>=', $contest->start_date)
               ->where('register_date', '<=', $contest->end_date ?: \XF::$time);
     }
     public function getContestTopReferrers($contest, $limit = 3)
     {
		return $this->db()->fetchAll('
			SELECT
				u2.user_id,
				u2.username,
				u2.display_style_group_id,
				u2.avatar_date,
				u2.gravatar,
				u2.like_count,
				u2.message_count,
				u2.trophy_points,
				COUNT(*) AS referral_count
			FROM xf_user AS u1
			LEFT JOIN xf_user AS u2 ON u2.user_id = u1.siropu_referrer_id
			WHERE u1.siropu_referrer_id > 0
			AND u1.register_date >= ?
			AND u1.register_date <= ?
			AND u1.message_count >= ?
			AND u1.is_banned = 0
			AND u2.is_banned = 0
			GROUP BY u1.siropu_referrer_id
			ORDER BY referral_count DESC, u2.user_id ASC
			LIMIT ?
		', [$contest->start_date, $contest->end_date ?: \XF::$time, $contest->minimum_posts, $limit]);
     }
}
