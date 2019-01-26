<?php

namespace Siropu\Shoutbox\Widget;

class Shoutbox extends \XF\Widget\AbstractWidget
{
	use \Siropu\Shoutbox\Shoutbox;

	protected $defaultOptions = [
		'height'        => 0,
          'sidebarStyle'  => false,
          'hideTimestamp' => false
	];

	public function render()
	{
          $visitor = \XF::visitor();

		if ($visitor->hasPermission('siropuShoutbox', 'view') && $visitor->hasRequiredAge())
		{
			return $this->renderer('siropu_shoutbox', [
				'shoutbox' => $this->getShoutboxParams(['height' => $this->options['height']]),
				'title'    => $this->getTitle() ?: \XF::phrase('siropu_shoutbox')
			]);
		}
	}
}
