<?php

namespace Siropu\ReferralContests\Admin\Controller;

use XF\Mvc\ParameterBag;
use XF\Mvc\FormAction;

class Contest extends AbstractController
{
     public function actionIndex(ParameterBag $params)
     {
          $finder = $this->getContestRepo()
               ->findContests();

          $viewParams = [
               'contests' => $finder->fetch(),
               'total'    => $finder->total()
          ];

          return $this->view('Siropu\ReferralContests:Contest', 'siropu_referral_contests_contest_list', $viewParams);
     }
     public function actionAdd(ParameterBag $params)
     {
          $contest = $this->em()->create('Siropu\ReferralContests:Contest');
          return $this->contestAddEdit($contest);
     }
     public function actionEdit(ParameterBag $params)
     {
          $contest = $this->assertContestExists($params->contest_id);
          return $this->contestAddEdit($contest);
     }
     public function actionSave(ParameterBag $params)
     {
          $this->assertPostOnly();

		if ($params->contest_id)
		{
			$contest = $this->assertContestExists($params->contest_id);
		}
		else
		{
			$contest = $this->em()->create('Siropu\ReferralContests:Contest');
		}

		$this->contestSaveProcess($contest)->run();

		return $this->redirect($this->buildLink('referral-contests'));
     }
     public function actionToggle()
     {
          $plugin = $this->plugin('XF:Toggle');
		return $plugin->actionToggle('Siropu\ReferralContests:Contest', 'enabled');
     }
     public function actionStatistics(ParameterBag $params)
     {
          $viewParams = [
               'contest' => $this->assertContestExists($params->contest_id)
          ];

          return $this->view('Siropu\ReferralContests:Contest\Stats', 'siropu_referral_contests_contest_statistics', $viewParams);
     }
     public function actionDelete(ParameterBag $params)
     {
          $contest = $this->assertContestExists($params->contest_id);

          if ($this->isPost())
          {
               $contest->delete();
               return $this->redirect($this->buildLink('referral-contests'));
          }

          $viewParams = [
               'contest' => $contest
          ];

          return $this->view('Siropu\ReferralContests:Contest\Delete', 'siropu_referral_contests_contest_delete', $viewParams);
     }
     protected function contestAddEdit(\Siropu\ReferralContests\Entity\Contest $contest)
	{
          $rewardTypes = $this->getRewardTypeRepo()
			->findRewardTypesForList()
			->fetch()
			->pluckNamed('name', 'reward_type_id');

          $viewParams = [
               'contest'     => $contest,
               'rewardTypes' => $rewardTypes,
               'nextCounter' => count($contest->prizes) + 1
          ];

          return $this->view('Siropu\ReferralContests:Contest\Edit', 'siropu_referral_contests_contest_edit', $viewParams);
     }
     protected function contestSaveProcess(\Siropu\ReferralContests\Entity\Contest $contest)
	{
          $input = $this->filter([
               'name'          => 'str',
               'description'   => 'str',
               'minimum_posts' => 'uint',
               'prizes'        => 'array',
               'end_date'      => 'datetime',
               'enabled'       => 'bool'
          ]);

          $form = $this->formAction();
          $form->basicEntitySave($contest, $input);

          $template = $contest->getMasterTemplate();

          $form->validate(function(FormAction $form) use ($contest, $template, $input)
          {
               if (!$template->set('template', $input['description']))
               {
                    $form->logErrors($template->getErrors());
               }
          });

          $form->apply(function() use ($template)
		{
			$template->saveIfChanged();
		});

		return $form;
     }
     public function getContestRepo()
     {
          return $this->repository('Siropu\ReferralContests:Contest');
     }
     public function getRewardTypeRepo()
     {
          return $this->repository('Siropu\ReferralContests:RewardType');
     }
     protected function assertContestExists($id, $with = null)
     {
          return $this->assertRecordExists('Siropu\ReferralContests:Contest', $id, $with, 'siropu_referral_contests_contest_not_found');
     }
}
