<?php

namespace Siropu\ReferralContests\Entity;

use XF\Mvc\Entity\Entity;
use XF\Mvc\Entity\Structure;

class Contest extends Entity
{
     public static function getStructure(Structure $structure)
	{
          $structure->table      = 'xf_siropu_referral_contests_contest';
          $structure->shortName  = 'ReferralContests:Contest';
          $structure->primaryKey = 'contest_id';

          $structure->columns = [
               'contest_id'     => ['type' => self::UINT, 'autoIncrement' => true],
               'name'           => ['type' => self::STR, 'required' => 'please_enter_valid_name'],
               'description'    => ['type' => self::STR, 'required' => 'siropu_referral_contests_please_enter_valid_description'],
               'minimum_posts'  => ['type' => self::UINT, 'default' => 0],
               'end_date'       => ['type' => self::UINT, 'default' => 0],
               'prizes'         => ['type' => self::SERIALIZED_ARRAY, 'default' => []],
               'referral_count' => ['type' => self::UINT, 'default' => 0],
               'winner_user_id' => ['type' => self::UINT, 'default' => 0],
               'start_date'     => ['type' => self::UINT, 'default' => \XF::$time],
               'enabled'        => ['type' => self::UINT, 'default' => 1]
          ];

          $structure->getters = [
               'total_referrals' => true,
               'valid_referrals' => true,
               'top_referrers'   => true,
               'winner'          => true
          ];

          $structure->relations = [
               'User' => [
                    'entity'     => 'XF:User',
                    'type'       => self::TO_ONE,
                    'conditions' => [['user_id', '=', '$winner_user_id']],
               ],
               'MasterTemplate' => [
				'entity' => 'XF:Template',
				'type' => self::TO_ONE,
				'conditions' => [
					['style_id', '=', 0],
					['type', '=', 'public'],
					['title', '=', '_siropu_referral_contests.', '$contest_id']
				]
			]
          ];

          $structure->defaultWith = ['MasterTemplate'];

          return $structure;
     }
     public function isValid()
     {
          return ($this->end_date == 0 || $this->end_date > \XF::$time);
     }
     public function getTotalReferrals()
     {
          return $this->getContestRepo()->getContestTotalReferrals($this)->total();
     }
     public function getValidReferrals()
     {
          if ($this->minimum_posts)
          {
               return $this->getContestRepo()->getContestTotalReferrals($this)
                    ->where('message_count', '>=', $this->minimum_posts)
                    ->total();
          }
          else
          {
               return $this->total_referrals;
          }
     }
     public function getTopReferrers()
     {
          return $this->getContestRepo()->getContestTopReferrers($this, count($this->prizes) ?: 3);
     }
     public function getWinner()
     {
          return current($this->top_referrers);
     }
     public function getPrizes()
     {
          $prizes = [];

          foreach ($this->prizes as $prize)
          {
               $rewardType = $this->em()->find('Siropu\ReferralContests:RewardType', $prize['reward_type_id']);

               if ($rewardType)
               {
                    $prizes[] = [
                         'amount' => $prize['reward_amount'],
                         'type'   => $rewardType
                    ];
               }
          }

          return $prizes;
     }
     protected function verifyPrizes(&$prizes)
     {
          foreach ($prizes as $key => $prize)
          {
               if (empty($prize['reward_amount']) || empty($prize['reward_type_id']))
               {
                    unset($prizes[$key]);
               }
          }

          return true;
     }
     public function getTemplateName()
	{
		return '_siropu_referral_contests.' . $this->contest_id;
	}
     public function getMasterTemplate()
	{
		$template = $this->MasterTemplate;

		if (!$template)
		{
			$template = $this->_em->create('XF:Template');
			$template->title = $this->_getDeferredValue(function() { return $this->getTemplateName(); }, 'save');
			$template->type = 'public';
			$template->style_id = 0;
		}

		return $template;
	}
     public function renderDescription()
     {
          if ($this->MasterTemplate)
          {
               return $this->app()->templater()->renderTemplate('public:' . $this->getTemplateName());
          }
          else
          {
               return $this->description;
          }
     }
     protected function _preSave()
	{

	}
     protected function _postSave()
	{

	}
	protected function _preDelete()
	{

	}
	protected function _postDelete()
	{
          if ($this->MasterTemplate)
		{
			$this->MasterTemplate->delete();
		}
	}
     public function getContestRepo()
     {
          return $this->repository('Siropu\ReferralContests:Contest');
     }
}
