<?php

namespace MJ\SupportTicket\Entity;

use XF\Entity\AbstractField;
use XF\Mvc\Entity\Structure;

/**
 * COLUMNS
 * @property string field_id
 * @property int display_order
 * @property string field_type
 * @property array field_choices
 * @property string match_type
 * @property array match_params
 * @property int max_length
 * @property bool required
 * @property string display_template
 * @property string display_group
 *
 * GETTERS
 * @property \XF\Phrase title
 * @property \XF\Phrase description
 *
 * RELATIONS
 * @property \XF\Entity\Phrase MasterTitle
 * @property \XF\Entity\Phrase MasterDescription
 * @property \MJ\SupportTicket\Entity\DepartmentField[] DepartmentFields
 */
class TicketField extends AbstractField
{
	protected function getClassIdentifier()
	{
		return 'MJ\SupportTicket:TicketField';
	}

	protected static function getPhrasePrefix()
	{
		return 'mjst_ticket_field';
	}

	protected function _postDelete()
	{
		/** @var \MJ\SupportTicket\Repository\DepartmentField $repo */
		$repo = $this->repository('MJ\SupportTicket:DepartmentField');
		$repo->removeFieldAssociations($this);

		$this->db()->delete('xf_mjst_ticket_field_value', 'field_id = ?', $this->field_id);

		parent::_postDelete();
	}

	public static function getStructure(Structure $structure)
	{
		self::setupDefaultStructure(
			$structure,
			'xf_mjst_ticket_field',
			'MJ\SupportTicket:TicketField',
			[
				'groups' => ['before', 'after', 'ticket_info', 'submitter_info'],
			]
		);
		$structure->columns += [
			'choice_callback_class' => ['type' => self::STR, 'maxLength' => 100, 'default' => ''],
			'choice_callback_method' => ['type' => self::STR, 'maxLength' => 75, 'default' => ''],
		];
		$structure->relations['DepartmentFields'] = [
			'entity' => 'MJ\SupportTicket:DepartmentField',
				'type' => self::TO_MANY,
				'conditions' => 'field_id'
		];

		return $structure;
	}
}
