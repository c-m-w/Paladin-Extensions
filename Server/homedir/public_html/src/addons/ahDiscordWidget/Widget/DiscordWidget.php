<?php

namespace ahDiscordWidget\Widget;

use \XF\Widget\AbstractWidget;

class DiscordWidget extends AbstractWidget
{
	public function render()
	{
		return $this->renderer('widget_ah_discord');
	}

	public function getOptionsTemplate()
	{
		return null;
	}
}