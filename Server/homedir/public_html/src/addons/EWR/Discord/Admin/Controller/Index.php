<?php

namespace EWR\Discord\Admin\Controller;

use XF\Mvc\ParameterBag;

class Index extends \XF\Admin\Controller\AbstractController
{
	protected function preDispatchController($action, ParameterBag $params)
	{
		$this->assertAdminPermission('option');
	}
	
	public function actionCode(ParameterBag $params)
	{
		$guild = $this->filter('guild', 'str');
		
		if ($guild)
		{
			$this->repository('XF:Option')->updateOption('EWRdiscord_server', $guild);
		}
		
		return $this->redirect($this->buildLink('options/groups/EWRdiscord/'));
	}
}