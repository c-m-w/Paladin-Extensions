<?php

namespace Siropu\ReferralContests\Entity;

use XF\Mvc\Entity\Entity;
use XF\Mvc\Entity\Structure;

class Tool extends Entity
{
     public static function getStructure(Structure $structure)
	{
          $structure->table      = 'xf_siropu_referral_contests_referral_tool';
          $structure->shortName  = 'ReferralContests:Tool';
          $structure->primaryKey = 'tool_id';

          $structure->columns = [
               'tool_id'     => ['type' => self::UINT, 'autoIncrement' => true],
               'type'        => ['type' => self::STR, 'default' => 'banner'],
               'name'        => ['type' => self::STR, 'required' => 'please_enter_valid_name'],
               'content'     => ['type' => self::STR, 'default' => ''],
               'size'        => ['type' => self::STR, 'default' => ''],
               'target_url'  => ['type' => self::STR, 'match' => 'url_empty', 'default' => ''],
               'click_count' => ['type' => self::UINT, 'default' => 0],
               'enabled'     => ['type' => self::UINT, 'default' => 1]
          ];

          $structure->getters = [
               'type_phrase'        => true,
               'absolute_file_path' => true
          ];

          return $structure;
     }
     public function isBanner()
     {
          return $this->type == 'banner';
     }
     public function isText()
     {
          return $this->type == 'text';
     }
     public function getTypePhrase()
     {
          return \XF::phrase('siropu_referral_contests_type.' . $this->type);
     }
     public function getAbsoluteFilePath()
     {
          return $this->app()->applyExternalDataUrl('siropu/rc/' . $this->content, true);
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
          if ($this->isBanner())
          {
               \XF\Util\File::deleteFromAbstractedPath('data://siropu/rc/' . $this->content);
          }
	}
}
