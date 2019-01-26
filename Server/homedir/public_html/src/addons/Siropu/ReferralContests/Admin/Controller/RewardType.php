<?php

namespace Siropu\ReferralContests\Admin\Controller;

use XF\Mvc\ParameterBag;
use XF\Mvc\FormAction;

class RewardType extends AbstractController
{
     public function actionIndex(ParameterBag $params)
     {
          $finder = $this->getRewardTypeRepo()->findRewardTypesForList();

          $viewParams = [
               'rewardTypes' => $finder->fetch(),
               'total'       => $finder->total()
          ];

          return $this->view('Siropu\ReferralContests:RewardType', 'siropu_referral_contests_reward_type_list', $viewParams);
     }
     public function actionAdd(ParameterBag $params)
     {
          $rewardType = $this->em()->create('Siropu\ReferralContests:RewardType');
          $rewardType->type = $this->filter('type', 'str');

          if ($rewardType->isDbTechCredits() && !$this->em()->find('XF:AddOn', 'DBTech/Credits'))
          {
               return $this->error(\XF::phrase('siropu_referral_contests_dbtech_credits_not_installed'));
          }

          return $this->rewardTypeAddEdit($rewardType);
     }
     public function actionEdit(ParameterBag $params)
     {
          $rewardType = $this->assertRewardTypeExists($params->reward_type_id);
          return $this->rewardTypeAddEdit($rewardType);
     }
     public function actionSave(ParameterBag $params)
     {
          $this->assertPostOnly();

		if ($params->reward_type_id)
		{
			$rewardType = $this->assertRewardTypeExists($params->reward_type_id);
		}
		else
		{
			$rewardType = $this->em()->create('Siropu\ReferralContests:RewardType');
               $rewardType->type = $this->filter('type', 'str');
		}

		$this->rewardTypeSaveProcess($rewardType)->run();

		return $this->redirect($this->buildLink('referral-contests/reward-types'));
     }
     public function actionDelete(ParameterBag $params)
     {
          $rewardType = $this->assertRewardTypeExists($params->reward_type_id);

          if ($this->isPost())
          {
               $rewardType->delete();
               return $this->redirect($this->buildLink('referral-contests/reward-types'));
          }

          $viewParams = [
               'rewardType' => $rewardType
          ];

          return $this->view('Siropu\ReferralContests:RewardType\Delete', 'siropu_referral_contests_reward_type_delete', $viewParams);
     }
     public function getRewardTypeRepo()
     {
          return $this->repository('Siropu\ReferralContests:RewardType');
     }
     protected function rewardTypeAddEdit(\Siropu\ReferralContests\Entity\RewardType $rewardType)
	{
          $viewParams = [
               'rewardType' => $rewardType,
               'currencies' => []
          ];

          if ($rewardType->isDbTechCredits())
          {
               $addon = $this->em()->find('XF:AddOn', 'DBTech/Credits');

               if ($addon->version_id >= 905010031)
               {
                    $currencies = \XF::repository('DBTech\Credits:Currency')->findCurrenciesForList(true);

                    foreach ($currencies as $currency)
                    {
                         $viewParams['currencies'][$currency->currency_id] = $currency->title;
                    }
               }
               else
               {
                    $currencies = \DBTech\Credits\Application\App::em()->findCached('DBTech\Credits:Currency');

                    foreach ($currencies as $currencyId => $currency)
                    {
                         $viewParams['currencies'][$currencyId] = $currency->getTitle();
                    }
               }
          }

          return $this->view('Siropu\ReferralContests:RewardType\Edit', 'siropu_referral_contests_reward_type_edit', $viewParams);
     }
     protected function rewardTypeSaveProcess(\Siropu\ReferralContests\Entity\RewardType $rewardType)
	{
          $input = $this->filter([
               'name'     => 'str',
               'currency' => 'str'
          ]);

          $form = $this->formAction();
          $form->basicEntitySave($rewardType, $input);

          $form->validate(function(FormAction $form) use ($rewardType)
          {
               if (!$rewardType->type)
               {
                    $form->logError(\XF::phrase('siropu_referral_contests_reward_type_not_found'));
               }
          });

		return $form;
     }
     protected function assertRewardTypeExists($id, $with = null)
     {
          return $this->assertRecordExists('Siropu\ReferralContests:RewardType', $id, $with, 'siropu_referral_contests_reward_type_not_found');
     }
}
