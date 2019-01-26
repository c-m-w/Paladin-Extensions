<?php

namespace XR\PM\XF\Pub\Controller;

use XF\Mvc\FormAction;

class Account extends XFCP_Account
{
	protected function preferencesSaveProcess(\XF\Entity\User $visitor)
	{
		$form = parent::preferencesSaveProcess($visitor);

		$receiveEmails = $this->filter('option.xr_pm_receive_update_email', 'bool');
		$form->setup(function(FormAction $form) use ($receiveEmails, $visitor)
		{
			$visitor->Option->xr_pm_receive_update_email = $receiveEmails;
		});

		return $form;
	}
}