<?php

namespace Justin\EmailCheck\XF\Pub\Controller;

class Register extends XFCP_Register
{
	public function actionIndex()
	{
		$actionIndex = parent::actionIndex();
		$j_enableregistrationproxycheck = $this->app()->options()->j_enableregistrationproxycheck['enabled'];
		if($j_enableregistrationproxycheck){
			$key = $this->app()->options()->j_enableregistrationproxycheck['apikey'];
			$strictness = 1;
			$ip = (isset($_SERVER["HTTP_CF_CONNECTING_IP"]) ? $_SERVER["HTTP_CF_CONNECTING_IP"] : $_SERVER["REMOTE_ADDR"]);
			$user_agent = $_SERVER['HTTP_USER_AGENT']; // User Browser (optional) - provides better forensics for our algorithm to enhance fraud scores.
			//$language = $_SERVER['HTTP_ACCEPT_LANGUAGE']; // User System Language (optional) - provides better forensics for our algorithm to enhance fraud scores.

			$client = \XF::app()->http()->client();
			try
			{
				// Attempt to connect to ipqualityscore api
				$result = $client->get("http://ipqualityscore.com/api/json/ip/$key/$ip/?user_agent=$user_agent&strictness=$strictness&fast=1")->json();
				if($result !== null){
					if (isset($result['fraud_score']) && $result['fraud_score'] >= 75) {
							return 	$this->error(\XF::phrase('j_ipquality_registration_check_error', ['ipaddress' => $ip]));
						} elseif($result['proxy'] == "true") {
							return $this->error(\XF::phraseDeferred('j_ipquality_registration_check_error', ['ipaddress' => $ip]));
						}
					}
				}
			catch(\GuzzleHttp\Exception\RequestException $e)
			{
				// this is an exception with the underlying request, so let it go through
				\XF::logException($e, false, 'ipqualityscore connection error: ');
			}
		}
		
		return $actionIndex;
	}
}