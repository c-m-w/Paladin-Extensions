<?php

namespace XR\PM\Entity;

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
 */
class ProductField extends AbstractField
{
	protected function getClassIdentifier()
	{
		return 'XR\PM:ProductField';
	}

	protected static function getPhrasePrefix()
	{
		return 'xr_pm_product_field';
	}

	public static function getStructure(Structure $structure)
	{
		self::setupDefaultStructure(
			$structure,
			'xf_xr_pm_product_field',
			'XR\PM:̀ProductField',
			[
				'groups' => ['tab_content', 'tab_link', 'above_details', 'below_details']
			]
		);

		return $structure;
	}
}