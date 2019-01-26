<?php

namespace Siropu\ReferralContests\Pub\Controller;

use XF\Mvc\ParameterBag;

class Contest extends \XF\Pub\Controller\AbstractController
{
     protected function preDispatchController($action, ParameterBag $params)
     {
          if (!\XF::visitor()->hasPermission('siropuReferralContests', 'viewContests'))
          {
               throw $this->exception($this->noPermission());
          }
     }
     public function actionIndex(ParameterBag $params)
     {
          if ($params->contest_id)
          {
               $contest = $this->assertContestExists($params->contest_id);

               $viewParams = [
                    'contest'      => $contest,
                    'topReferrers' => $this->getContestRepo()->getContestTopReferrers($contest, 10)
               ];

               return $this->view('Siropu\ReferralContests:Contest\View', 'siropu_referral_contests_contest_view', $viewParams);
          }

          $contests = $this->getContestRepo()
               ->findContests()
               ->whereOr(['enabled', 1], ['winner_user_id', '<>', 0])
               ->fetch();

          $viewParams = [
               'contests' => $contests
          ];

          return $this->view('Siropu\ReferralContests:Contest', 'siropu_referral_contests_contest_list', $viewParams);
     }
     public function actionTopReferrers(ParameterBag $params)
     {
          $contest = $this->assertContestExists($params->contest_id);

          $viewParams = [
               'contest'      => $contest,
               'topReferrers' => $this->getContestRepo()->getContestTopReferrers($contest, 10)
          ];

          return $this->view('Siropu\ReferralContests:Contest\TopReferrers', 'siropu_referral_contests_contest_top_referrers', $viewParams);
     }
     public function actionPrizes(ParameterBag $params)
     {
          $contest = $this->assertContestExists($params->contest_id);

          $viewParams = [
               'contest' => $contest,
               'prizes'  => $contest->getPrizes()
          ];

          return $this->view('Siropu\ReferralContests:Contest\Prizes', 'siropu_referral_contests_contest_prizes', $viewParams);
     }
     public function actionFaq()
     {
          return $this->view('Siropu\ReferralContests:Faq', 'siropu_referral_contests_faq');
     }
     public function actionTools()
     {
          $finder = $this->getToolRepo()
               ->findToolsForList()
               ->where('enabled', 1);

          $viewParams = [
               'tools' => $finder->fetch()->groupBy('type'),
               'count' => $finder->total()
          ];

          return $this->view('Siropu\ReferralContests:Tools', 'siropu_referral_contests_referral_tools', $viewParams);
     }
     public function getContestRepo()
     {
          return $this->repository('Siropu\ReferralContests:Contest');
     }
     public function getToolRepo()
     {
          return $this->repository('Siropu\ReferralContests:Tool');
     }
     protected function assertContestExists($id, $with = null)
     {
          return $this->assertRecordExists('Siropu\ReferralContests:Contest', $id, $with, 'siropu_referral_contests_contest_not_found');
     }
}
