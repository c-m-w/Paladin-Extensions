<?php

namespace Siropu\ReferralContests\Entity;

use XF\Mvc\Entity\Entity;
use XF\Mvc\Entity\Structure;

class RewardType extends Entity
{
     public static function getStructure(Structure $structure)
	{
          $structure->table      = 'xf_siropu_referral_contests_reward_type';
          $structure->shortName  = 'ReferralContests:RewardType';
          $structure->primaryKey = 'reward_type_id';

          $structure->columns = [
               'reward_type_id' => ['type' => self::UINT, 'autoIncrement' => true],
               'name'           => ['type' => self::STR, 'required' => 'please_enter_valid_name'],
               'type'           => ['type' => self::STR, 'default' => 'trophy_points'],
               'currency'       => ['type' => self::STR, 'default' => '']
          ];

          $structure->getters = [
               'type_phrase' => true
          ];

          return $structure;
     }
     public function getTypePhrase()
     {
          return \XF::phrase('siropu_referral_contests_reward_type.' . $this->type);
     }
     public function isTrophyPoints()
     {
          return $this->type == 'trophy_points';
     }
     public function isDbTechCredits()
     {
          return $this->type == 'dbtech_credits';
     }
     public function applyDbTechCredits($user, $amount, $phrase = 'siropu_referral_contests_reward_for_referring_new_member')
     {
          $addon   = $this->em()->find('XF:AddOn', 'DBTech/Credits');
          $message = (string) \XF::phrase($phrase);

          if ($addon->version_id >= 905010031)
          {
               $eventTriggerRepo = \XF::repository('DBTech\Credits:EventTrigger');
               $adjustHandler = $eventTriggerRepo->getHandler('adjust');
               $adjustHandler->apply($user->user_id, [
                    'currency_id' 	  => $this->currency,
                    'multiplier' 	  => $amount,
                    'message'        => $message,
                    'source_user_id' => \XF::visitor()->user_id,
               ], $user);
          }
          else
          {
               $adjust = \DBTech\Credits\Application\App::em()->findOne('DBTech\Credits:EventTrigger', 'adjust');
               $adjustEvent = $adjust->getClass();
               $adjustEvent->apply($referrerId, $this->currency, $amount, $message, \XF::visitor()->user_id);
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

	}
}
