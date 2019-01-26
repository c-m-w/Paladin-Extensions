<?php

namespace Siropu\Shoutbox\Pub\View;

use XF\Mvc\View;

class Shoutbox extends View
{
	public function renderJson()
	{
		return [
			'html' => $this->renderer->getHtmlOutputStructure($this->renderTemplate($this->getTemplateName(), $this->getParams())),
			'time' => \XF::$time
		];
     }
}
