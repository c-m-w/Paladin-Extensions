<?php

namespace Andy\History\Entity;

use XF\Mvc\Entity\Entity;
use XF\Mvc\Entity\Structure;

class History extends Entity
{
	public static function getStructure(Structure $structure)
	{
		$structure->table = 'xf_andy_history';
		$structure->shortName = 'Andy\History:History';
		$structure->primaryKey = 'history_id';
		$structure->columns = [
			'history_id' => ['type' => self::UINT, 'autoIncrement' => true, 'nullable' => true],
			'user_id' => ['type' => self::UINT, 'required' => true],
			'thread_id' => ['type' => self::UINT, 'required' => true],
			'thread_read_date' => ['type' => self::UINT, 'required' => true],
		];
		$structure->getters = [];
		$structure->relations = [
			'Thread' => [
				'entity' => 'XF:Thread',
				'type' => self::TO_ONE,
				'conditions' => 'thread_id',
				'primary' => true
			]
		];

		return $structure;
	}	
}