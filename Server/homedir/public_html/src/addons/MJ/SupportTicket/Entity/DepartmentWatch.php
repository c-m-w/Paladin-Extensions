<?php

namespace MJ\SupportTicket\Entity;

use XF\Mvc\Entity\Entity;
use XF\Mvc\Entity\Structure;

/**
 * COLUMNS
 * @property int user_id
 * @property int department_id
 * @property string notify_on
 * @property bool send_alert
 * @property bool send_email
 * @property bool include_children
 *
 * RELATIONS
 * @property \MJ\SupportTicket\Entity\Department Department
 * @property \XF\Entity\User User
 */
class DepartmentWatch extends Entity
{
	public static function getStructure(Structure $structure)
	{
		$structure->table = 'xf_mjst_department_watch';
		$structure->shortName = 'MJ\SupportTicket:DepartmentWatch';
		$structure->primaryKey = ['user_id', 'department_id'];
		$structure->columns = [
			'user_id'           => ['type' => self::UINT, 'required' => true],
			'department_id'       => ['type' => self::UINT, 'required' => true],
			'notify_on'         => ['type' => self::STR, 'default' => '',
				'allowedValues' => ['', 'ticket', 'message']
			],
			'send_alert'        => ['type' => self::BOOL, 'default' => false],
			'send_email'        => ['type' => self::BOOL, 'default' => false],
			'include_children'  => ['type' => self::BOOL, 'default' => false]
		];
		$structure->getters = [];
		$structure->relations = [
			'Department' => [
				'entity' => 'MJ\SupportTicket:Department',
				'type' => self::TO_ONE,
				'conditions' => 'department_id',
				'primary' => true
			],
			'User' => [
				'entity' => 'XF:User',
				'type' => self::TO_ONE,
				'conditions' => 'user_id',
				'primary' => true
			],
		];

		return $structure;
	}
}
