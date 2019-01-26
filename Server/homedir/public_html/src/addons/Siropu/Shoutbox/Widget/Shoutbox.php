<?php

namespace Siropu\Shoutbox\Widget;

class Shoutbox extends \XF\Widget\AbstractWidget
{
	use \Siropu\Shoutbox\Shoutbox;

	public function render()
	{
		if (\XF::visitor()->canViewSiropuShoutbox())
		{
			return $this->renderer('siropu_shoutbox', ['shoutbox' => $this->getShoutboxParams()]);
		}
	}
}
