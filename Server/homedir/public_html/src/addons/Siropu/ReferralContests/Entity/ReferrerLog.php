<?php

namespace Siropu\ReferralContests\Entity;

use XF\Mvc\Entity\Entity;
use XF\Mvc\Entity\Structure;

class ReferrerLog extends Entity
{
     public static function getStructure(Structure $structure)
	{
          $structure->table      = 'xf_siropu_referral_contests_referrer_log';
          $structure->shortName  = 'ReferralContests:ReferrerLog';
          $structure->primaryKey = 'log_id';

          $structure->columns = [
               'log_id'  => ['type' => self::UINT, 'autoIncrement' => true],
               'user_id' => ['type' => self::UINT, 'default' => \XF::visitor()->user_id],
               'url'     => ['type' => self::STR, 'default' => ''],
               'date'    => ['type' => self::UINT, 'default' => \XF::$time],
          ];

          $structure->getters = [];

          $structure->relations = [
               'User' => [
                    'entity'     => 'XF:User',
                    'type'       => self::TO_ONE,
                    'conditions' => 'user_id'
               ]
          ];

          return $structure;
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
