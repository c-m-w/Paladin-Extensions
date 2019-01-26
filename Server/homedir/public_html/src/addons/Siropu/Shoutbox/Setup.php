<?php

namespace Siropu\Shoutbox;

use XF\AddOn\AbstractSetup;
use XF\AddOn\StepRunnerInstallTrait;
use XF\AddOn\StepRunnerUninstallTrait;
use XF\AddOn\StepRunnerUpgradeTrait;

class Setup extends AbstractSetup
{
	use StepRunnerInstallTrait;
	use StepRunnerUpgradeTrait;
	use StepRunnerUninstallTrait;

	public function installStep1()
	{
		$this->schemaManager()->createTable('xf_siropu_shoutbox_shout', function(\XF\Db\Schema\Create $table)
		{
			$table->addColumn('shout_id', 'int')->autoIncrement();
			$table->addColumn('shout_user_id', 'int');
			$table->addColumn('shout_message', 'text');
			$table->addColumn('shout_date', 'int');
			$table->addKey('shout_user_id');
			$table->addKey('shout_date');
		});
	}
	public function installStep2()
	{
		$this->createWidget('siropu_shoutbox', 'siropu_shoutbox', [
			'positions' => [
				'forum_list_above_nodes' => 10
			]
		]);
	}
	public function upgrade(array $stepParams = [])
	{
		// TODO: Implement upgrade() method.
	}

	public function uninstall(array $stepParams = [])
	{
		$this->schemaManager()->dropTable('xf_siropu_shoutbox_shout');

		$this->app->response()->setCookie('siropuShoutboxNoSound', false);
		$this->app->response()->setCookie('siropuShoutboxReverse', false);
		$this->app->response()->setCookie('siropuShoutboxCollapsed', false);
	}
}
