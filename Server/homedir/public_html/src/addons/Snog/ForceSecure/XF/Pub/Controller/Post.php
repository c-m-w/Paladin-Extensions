<?php

namespace Snog\ForceSecure\XF\Pub\Controller;

use XF\Mvc\ParameterBag;

class Post extends XFCP_Post
{
	public function actionEdit(ParameterBag $params)
	{
		if ($this->isPost())
		{
			$message = $this->plugin('XF:Editor')->fromInput('message');
			if (stristr($message, '[img]http://')) return $this->error(\XF::phrase('snog_forcesecure_insecure'));
		}

		return parent::actionEdit($params);
	}
}