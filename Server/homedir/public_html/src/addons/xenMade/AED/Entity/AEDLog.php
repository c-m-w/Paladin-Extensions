<?php

namespace  xenMade\AED\Entity;

use XF\Mvc\Entity\Entity;
use XF\Mvc\Entity\Structure;

class AEDLog extends Entity
{
    public static function getStructure(Structure $structure)
    {
        $structure->table      = 'xf_xenmade_aed_log';
        $structure->shortName  = 'xenMade\AED:AED';
        $structure->primaryKey = 'aed_id';

        $structure->columns = [
            'aed_id' => ['type' => self::UINT, 'autoIncrement' => true],
            'from_user_id'  => ['type' => self::UINT, 'default' => 0],
            'to_user_id'  => ['type' => self::UINT, 'default' => 0],
            'user_fingerprint'  => ['type' => self::STR, 'default' => ''],
            'ip_address' => ['type' => self::BINARY, 'maxLength' => 16],
            'login_date'  => ['type' => self::UINT, 'default' => \XF::$time],
        ];

        $structure->getters   = [];

        $structure->relations = [
            'ToUser' => [
                'entity' => 'XF:User',
                'type' => self::TO_ONE,
                'conditions' => [['user_id', '=', '$to_user_id']],
                'primary' => true
            ],
            'FromUser' => [
                'entity' => 'XF:User',
                'type' => self::TO_ONE,
                'conditions' => [['user_id', '=', '$from_user_id']],
                'primary' => true
            ]
        ];

        $structure->defaultWith = [
            'ToUser', 'FromUser'
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
