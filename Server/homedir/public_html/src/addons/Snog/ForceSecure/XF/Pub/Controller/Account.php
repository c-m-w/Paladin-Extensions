<?php

namespace Snog\ForceSecure\XF\Pub\Controller;

class Account extends XFCP_Account
{
	public function actionAccountDetails()
	{
		if ($this->isPost())
		{
			$input['profile']['about'] = $this->plugin('XF:Editor')->fromInput('about');
			if (stristr($input['profile']['about'], '[img]http://')) return $this->error(\XF::phrase('snog_forcesecure_about'));
		}

		return parent::actionAccountDetails();
	}

	public function actionSignature()
	{
		if ($this->isPost())
		{
			$signature = $this->plugin('XF:Editor')->fromInput('signature');
			if (stristr($signature, '[img]http://')) return $this->error(\XF::phrase('snog_forcesecure_signature'));
		}

		return parent::actionSignature();
	}
}