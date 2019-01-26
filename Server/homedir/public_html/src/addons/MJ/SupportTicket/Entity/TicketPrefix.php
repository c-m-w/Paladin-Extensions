<?php

namespace MJ\SupportTicket\Entity;

use XF\Entity\AbstractPrefix;
use XF\Mvc\Entity\Structure;

/**
 * COLUMNS
 * @property int|null prefix_id
 * @property int prefix_group_id
 * @property int display_order
 * @property int materialized_order
 * @property string css_class
 * @property array allowed_user_group_ids
 *
 * GETTERS
 * @property \XF\Phrase|string title
 * @property array department_ids
 *
 * RELATIONS
 * @property \XF\Entity\Phrase MasterTitle
 * @property \MJ\SupportTicket\Entity\TicketPrefixGroup PrefixGroup
 * @property \MJ\SupportTicket\Entity\DepartmentPrefix[] DepartmentPrefixes
 */
class TicketPrefix extends AbstractPrefix
{
	protected function getClassIdentifier()
	{
		return 'MJ\SupportTicket:TicketPrefix';
	}

	protected static function getContentType()
	{
		return 'support_ticket';
	}

	/**
	 * @return array
	 */
	public function getDepartmentIds()
	{
		if (!$this->prefix_id)
		{
			return [];
		}

		return $this->db()->fetchAllColumn("
			SELECT department_id
			FROM xf_mjst_department_prefix
			WHERE prefix_id = ?
		", $this->prefix_id);
	}

	protected function _postDelete()
	{
		parent::_postDelete();

		$this->repository('MJ\SupportTicket:DepartmentPrefix')->removePrefixAssociations($this);
	}

	public static function getStructure(Structure $structure)
	{
		self::setupDefaultStructure($structure, 'xf_mjst_ticket_prefix', 'MJ\SupportTicket:TicketPrefix');

		$structure->getters['department_ids'] = true;

		$structure->relations['DepartmentPrefixes'] = [
			'entity' => 'MJ\SupportTicket:DepartmentPrefix',
			'type' => self::TO_MANY,
			'conditions' => 'prefix_id'
		];

		return $structure;
	}
}
