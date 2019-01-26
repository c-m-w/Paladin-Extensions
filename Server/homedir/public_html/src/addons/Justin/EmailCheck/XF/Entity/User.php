<?php

namespace Justin\EmailCheck\XF\Entity;

class User extends XFCP_User
{
	protected function verifyEmail(&$email)
	{
		$emailValid = parent::verifyEmail($email);
		if (!$emailValid)
		{
			return $emailValid;
		}

		if ($this->getOption('admin_edit') && $email === '')
		{
			return true;
		}
		
		$emailcheck = $this->app()->options()->j_validtorpizza;
		if ($emailcheck)
		{
			$client = \XF::app()->http()->client();
			try
			{
				// Attempt to connect to Valdator.pizza api
				$response = $client->get("https://www.validator.pizza/email/$email")->json();
				if($response !== null){
					if($response['disposable'] == 'true'){
						$this->error(\XF::phrase('please_enter_valid_email'), 'email');
						return false;
					}
				}
			}
			catch(\GuzzleHttp\Exception\RequestException $e)
			{
				// this is an exception with the underlying request, so let it go through
				\XF::logException($e, false, 'Valdator.pizza connection error: ');
			}
		}
		
		$ipqualitycheck = $this->app()->options()->j_enableipquality['enabled'];
		if($ipqualitycheck){
			$key = $this->app()->options()->j_enableipquality['apikey'];
			$strictness = 1;
			$client = \XF::app()->http()->client();
			try
			{
				// Attempt to connect to ipqualityscore api
				$result = $client->get("http://ipqualityscore.com/api/json/email/$key/$email/?strictness=$strictness")->json();
				if($result !== null){
					if (!$result['valid']) {
						$this->error(\XF::phrase('please_enter_valid_email'), 'email');
							return false;
						} elseif($result['disposable'] == "true") {
							$this->error(\XF::phrase('please_enter_valid_email'), 'email');
							return false;
						}
					}
				}
			catch(\GuzzleHttp\Exception\RequestException $e)
			{
				// this is an exception with the underlying request, so let it go through
				\XF::logException($e, false, 'ipqualityscore connection error: ');
			}
		}
		return $emailValid;
	}

}