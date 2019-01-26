<?php

namespace Siropu\ReferralContests\Pub\Controller;

use XF\Mvc\ParameterBag;

class Referral extends \XF\Pub\Controller\AbstractController
{
     public function actionUsers(ParameterBag $params)
     {
          $user = $this->assertRecordExists('XF:User', $params->user_id);

          $type    = $this->filter('type', 'str');
          $page    = $params->page;
		$perPage = 20;

          $finder = $this->finder('XF:User')
               ->where('siropu_referrer_id', $user->user_id)
               ->order('register_date', 'desc');

          if ($type == 'currentMonth')
          {
               $finder->where('register_date', '>=', strtotime('first day of this month 00:00'));
          }

		$total = $finder->total();

          $this->assertValidPage($page, $perPage, $total, 'referrals/users', $user);
		$this->assertCanonicalUrl($this->buildLink('referrals/users', $user, ['page' => $page]));

          $referrals = $finder->limitByPage($page, $perPage)->fetch();

          $viewParams = [
               'user'      => $user,
               'referrals' => $referrals,
               'total'     => $total,
               'page'      => $page,
               'perPage'   => $perPage
          ];

          return $this->view('Siropu\ReferralContests:Referral', 'siropu_referral_contests_referral_list', $viewParams);
     }
}
