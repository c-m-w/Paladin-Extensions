<?php

namespace xenMade\AED\Option;

use \XF\Option\AbstractOption;

class Alert extends AbstractOption
{
	public static function renderOption(\XF\Entity\Option $option, array $htmlParams)
	{
		/** @var \XF\Repository\Node $nodeRepo */
		$nodeRepo = \XF::repository('XF:Node');
		$nodeTree = $nodeRepo->createNodeTree($nodeRepo->getFullNodeList());

		return self::getTemplate('admin:aed_option_template_alert', $option, $htmlParams, [
			'nodeTree' => $nodeTree
		]);
	}
}