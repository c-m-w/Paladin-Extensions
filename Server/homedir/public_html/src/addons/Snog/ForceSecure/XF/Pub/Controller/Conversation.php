<?php

namespace Snog\ForceSecure\XF\Pub\Controller;

use XF\Mvc\ParameterBag;

class Conversation extends XFCP_Conversation
{
	public function actionAdd()
	{
		if ($this->isPost())
		{
			$message = $this->plugin('XF:Editor')->fromInput('message');
			if (stristr($message, '[img]http://')) return $this->error(\XF::phrase('snog_forcesecure_insecure'));
		}

		return parent::actionAdd();
	}

	public function actionAddReply(ParameterBag $params)
	{
		$this->assertPostOnly();

		$message = $this->plugin('XF:Editor')->fromInput('message');
		if (stristr($message, '[img]http://')) return $this->error(\XF::phrase('snog_forcesecure_insecure'));

		return parent::actionAddReply($params);
	}

	public function actionMessagesEdit(ParameterBag $params)
	{
		if ($this->isPost())
		{
			$message = $this->plugin('XF:Editor')->fromInput('message');
			if (stristr($message, '[img]http://')) return $this->error(\XF::phrase('snog_forcesecure_insecure'));
		}

		return parent::actionMessagesEdit($params);
	}
}