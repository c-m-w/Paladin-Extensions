<?php

namespace xenMade\LAU\Entity;

use XF\Mvc\Entity\Entity;
use XF\Mvc\Entity\Structure;

class LauLog extends Entity
{
	public static function getStructure(Structure $structure)
	{
		$structure->table = 'xf_xenmade_lau_log';
		$structure->shortName = 'LAU:LauLog';
		$structure->primaryKey = 'log_id';

		$structure->columns = [
			'log_id' => ['type' => self::UINT, 'autoIncrement' => true, 'nullable' => true],

            'from_user_id' => ['type' => self::UINT, 'default' => 0],
            'from_username' => ['type' => self::STR, 'maxLength' => 50,
                'required' => 'please_enter_valid_name'
            ],

            'to_user_id' => ['type' => self::UINT, 'default' => 0],
            'to_username' => ['type' => self::STR, 'maxLength' => 50,
                'required' => 'please_enter_valid_name'
            ],

            'dateline' => ['type' => self::UINT, 'default' => \XF::$time],

            'reason' => ['type' => self::STR, 'default' => ''],

            'ip_address' => ['type' => self::BINARY, 'maxLength' => 16],
		];

		$structure->getters = [];

		$structure->relations = [
            'FromUser' => [
                'entity'     => 'XF:User',
                'type'       => self::TO_ONE,
                'conditions' => [['user_id', '=', '$from_user_id']],
                'primary'    => true
            ],

            'ToUser' => [
                'entity'     => 'XF:User',
                'type'       => self::TO_ONE,
                'conditions' => [['user_id', '=', '$to_user_id']],
                'primary'    => true
            ]
        ];

        $structure->defaultWith = [
            'FromUser', 'ToUser'
        ];

		$structure->options = [];

		return $structure;
	}
}