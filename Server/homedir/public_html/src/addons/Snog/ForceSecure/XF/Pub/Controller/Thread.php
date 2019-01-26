<?php

namespace Snog\ForceSecure\XF\Pub\Controller;

use XF\Mvc\ParameterBag;

class Thread extends XFCP_Thread
{
	public function actionAddReply(ParameterBag $params)
	{
		$this->assertPostOnly();
		$message = $this->plugin('XF:Editor')->fromInput('message');
		if (stristr($message, '[img]http://')) return $this->error(\XF::phrase('snog_forcesecure_insecure'));
		return parent::actionAddReply($params);
	}
}