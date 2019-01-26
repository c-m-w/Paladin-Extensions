<?php

namespace Siropu\Shoutbox\Entity;

use XF\Mvc\Entity\Entity;
use XF\Mvc\Entity\Structure;

class Shout extends Entity
{
     public static function getStructure(Structure $structure)
	{
          $structure->table      = 'xf_siropu_shoutbox_shout';
          $structure->shortName  = 'Shoutbox:Shout';
          $structure->primaryKey = 'shout_id';

          $structure->columns = [
               'shout_id'      => ['type' => self::UINT, 'autoIncrement' => true],
               'shout_user_id' => ['type' => self::UINT, 'default' => \XF::visitor()->user_id],
               'shout_message' => ['type' => self::STR, 'required' => 'siropu_shoutbox_cannot_submit_empty_shout'],
               'shout_date'    => ['type' => self::UINT, 'default' => \XF::$time],
          ];

          $structure->getters   = [];
		$structure->relations = [
               'User' => [
				'entity'     => 'XF:User',
				'type'       => self::TO_ONE,
				'conditions' => [['user_id', '=', '$shout_user_id']]
			],
          ];

          $structure->defaultWith = ['User'];

          return $structure;
     }
     public function canEdit()
     {
          $visitor = \XF::visitor();

          if ($visitor->hasPermission('siropuShoutbox', 'editAny')
          )
          {
               return true;
          }

          if ($visitor->hasPermission('siropuShoutbox', 'editOwn') && $this->shout_user_id == $visitor->user_id)
          {
               return true;
          }
     }
     public function canDelete()
     {
          $visitor = \XF::visitor();

          if ($visitor->hasPermission('siropuShoutbox', 'deleteAny')
          )
          {
               return true;
          }

          if ($visitor->hasPermission('siropuShoutbox', 'deleteOwn') && $this->shout_user_id == $visitor->user_id)
          {
               return true;
          }
     }
     protected function _preSave()
	{

	}
     protected function _postSave()
	{
          $threadId = \XF::options()->siropuShoutboxThreadId;
          $threadMinMessageLength = \XF::options()->siropuShoutboxThreadMessageMinLength;

          if ($threadId
               && ($threadMinMessageLength == 0
                    || strlen($this->app()->stringFormatter()->stripBbCode($this->shout_message)) >= $threadMinMessageLength))
          {
               $thread = $this->em()->find('XF:Thread', $threadId);

               if ($thread)
               {
                    $replier = $this->app()->service('XF:Thread\Replier', $thread);
                    $replier->setMessage($this->shout_message);
                    $replier->setIsAutomated();
                    $replier->save();
               }
          }
	}
	protected function _preDelete()
	{

	}
	protected function _postDelete()
	{

	}
}
