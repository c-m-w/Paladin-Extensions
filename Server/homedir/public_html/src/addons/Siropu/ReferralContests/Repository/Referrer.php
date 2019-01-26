<?php

namespace Siropu\ReferralContests\Repository;

use XF\Mvc\Entity\Finder;
use XF\Mvc\Entity\Repository;

class Referrer extends Repository
{
     public function getTopReferrers($limit = 10)
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
                    COUNT(*) AS siropu_referral_count
               FROM xf_user AS u1
               LEFT JOIN xf_user AS u2 ON u2.user_id = u1.siropu_referrer_id
               WHERE u1.siropu_referrer_id <> 0
               AND u1.register_date >= ?
               AND u1.is_banned = 0
               AND u2.is_banned = 0
               GROUP BY u1.siropu_referrer_id
               ORDER BY siropu_referral_count DESC
               LIMIT ?
		', [strtotime('first day of this month 00:00'), $limit]);
     }
     public function getTopReferrersFromCache()
     {
          $simpleCache = $this->app()->simpleCache();
          return $simpleCache['Siropu/ReferralContests']['topReferrers'];
     }
     public function updateTopReferrersCache($widgetKey, array $referrers = [])
     {
          $simpleCache = $this->app()->simpleCache();
          $simpleCache['Siropu/ReferralContests']['topReferrers'] = [$widgetKey => $referrers];
     }
     public function deleteTopReferrersCache()
     {
          $simpleCache = $this->app()->simpleCache();
          $simpleCache['Siropu/ReferralContests']['topReferrers'] = '';
     }
}
