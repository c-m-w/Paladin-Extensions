<?php

namespace Siropu\ReferralContests\Entity;

use XF\Mvc\Entity\Entity;
use XF\Mvc\Entity\Structure;

class Unconfirmed extends Entity
{
     public static function getStructure(Structure $structure)
	{
          $structure->table      = 'xf_siropu_referral_contests_unconfirmed';
          $structure->shortName  = 'ReferralContests:Unconfirmed';
          $structure->primaryKey = 'user_id';

          $structure->columns = [
               'user_id'         => ['type' => self::UINT, 'required' => true],
               'referrer_id'     => ['type' => self::UINT, 'required' => true],
               'invitation_code' => ['type' => self::STR, 'maxLength' => 40, 'default' => '']
          ];

          $structure->relations = [
               'User' => [
                    'entity'     => 'XF:User',
                    'type'       => self::TO_ONE,
                    'conditions' => 'user_id',
                    'primary'    => true
               ],
               'Referrer' => [
				'entity'     => 'XF:User',
				'type'       => self::TO_ONE,
				'conditions' => [['user_id', '=', '$referrer_id']]
			],
               'Invitation' => [
                    'entity'     => 'Siropu\ReferralContests:Invitation',
				'type'       => self::TO_ONE,
				'conditions' => 'invitation_code'
               ]
          ];

          $structure->defaultWith = ['User', 'Referrer', 'Invitation'];

          return $structure;
     }
}
