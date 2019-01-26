<?php

namespace Siropu\ReferralContests\Entity;

use XF\Mvc\Entity\Entity;
use XF\Mvc\Entity\Structure;

class Invitation extends Entity
{
     public static function getStructure(Structure $structure)
	{
          $structure->table      = 'xf_siropu_referral_contests_invitation';
          $structure->shortName  = 'ReferralContests:Invitation';
          $structure->primaryKey = 'invitation_code';

          $structure->columns = [
               'invitation_code'    => ['type' => self::STR, 'maxLength' => 40, 'required' => true],
               'user_id'            => ['type' => self::UINT, 'default' => \XF::visitor()->user_id],
               'recipient'          => ['type' => self::STR, 'default' => ''],
               'message'            => ['type' => self::STR, 'default' => ''],
               'registered_user_id' => ['type' => self::UINT, 'default' => 0],
               'invitation_date'    => ['type' => self::UINT, 'default' => \XF::$time],
               'expiration_date'    => ['type' => self::UINT, 'default' => 0]
          ];

          $structure->getters = [
               'invitation_url' => false
          ];

          $structure->relations = [
               'User' => [
                    'entity'     => 'XF:User',
                    'type'       => self::TO_ONE,
                    'conditions' => 'user_id'
               ],
               'Registered' => [
                    'entity'     => 'XF:User',
                    'type'       => self::TO_ONE,
                    'conditions' => [['user_id', '=', '$registered_user_id']]
               ]
          ];

          return $structure;
     }
     public function getInvitationUrl()
     {
          $urlParameter = \XF::options()->siropuReferralContestsInvitationUrlParameter;
          return $this->app()->router('public')->buildLink('canonical:index', '', [$urlParameter => $this->invitation_code]);
     }
     public function isValid()
     {
            $expirationTime = \XF::options()->siropuReferralContestsInvitationExpirationTime;

            if ($this->registered_user_id != 0)
            {
                  return false;
            }

            if ($this->expiration_date)
            {
                  return $this->expiration_date > \XF::$time;
            }
            else if ($expirationTime)
            {
                  return $this->invitation_date > \XF::$time - $expirationTime * 86400;
            }

            return true;
     }
      public function generateCode($salt = '')
      {
          $this->invitation_code = sha1(uniqid($salt) . mt_rand());
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
