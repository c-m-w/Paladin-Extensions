<?php

namespace Siropu\Shoutbox\Pub\View;

use XF\Mvc\View;

class Shoutbox extends View
{
     public function renderHtml()
	{
          $this->response->removeHeader('X-Frame-Options');
     }
	public function renderJson()
	{
		return [
			'html' => $this->renderer->getHtmlOutputStructure($this->renderTemplate($this->getTemplateName(), $this->getParams())),
			'time' => \XF::$time
		];
     }
}
