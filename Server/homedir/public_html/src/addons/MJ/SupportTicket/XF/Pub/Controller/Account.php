<?php

namespace MJ\SupportTicket\XF\Pub\Controller;

use XF\Entity\User;

class Account extends XFCP_Account
{
	protected function preferencesSaveProcess(User $visitor)
	{
		$form = parent::preferencesSaveProcess($visitor);
		$input = $this->filter([
			'option' => [
				'disable_email_on_support_ticket' => 'bool',
				'email_on_support_ticket'         => 'bool'
			],
		]);
		$disableEmail = $this->options()->mjstDisableEmail;

		if($disableEmail){
			$userOptions = $visitor->getRelationOrDefault('Option');
			$form->setupEntityInput($userOptions, [
				'disable_email_on_support_ticket' => !$input['option']['disable_email_on_support_ticket'],
			]);
		}else{
			$userOptions = $visitor->getRelationOrDefault('Option');
			$form->setupEntityInput($userOptions, [
				'email_on_support_ticket' => $input['option']['email_on_support_ticket'],
			]);
		}
		return $form;
	}
}
