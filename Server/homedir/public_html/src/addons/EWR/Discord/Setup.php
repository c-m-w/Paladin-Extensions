<?php

namespace EWR\Discord;

use XF\Db\Schema\Alter;
use XF\Db\Schema\Create;

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
		$this->schemaManager()->alterTable('xf_node', function(Alter $table)
		{
            $table->addColumn('discord_options', 'blob')->nullable();
		});
		
		$this->schemaManager()->alterTable('xf_user_connected_account', function(Alter $table)
		{
            $table->addColumn('sync_date', 'int', 10);
		});
	}
	
	public function installStep2()
	{
		$this->db()->insert('xf_connected_account_provider', [
			'provider_id' => 'discord',
			'provider_class' => 'EWR\Discord:Provider\Discord',
			'display_order' => 100,
			'options' => ''
		], true);
	}
	
	public function installStep3()
	{
		$this->schemaManager()->alterTable('xf_user_option', function(Alter $table)
		{
            $table->addColumn('discord_options', 'blob')->nullable();
		});
	}
	
	public function uninstallStep1()
	{
		$this->schemaManager()->alterTable('xf_node', function(Alter $table)
		{
			$table->dropColumns('discord_options');
		});
		
		$this->schemaManager()->alterTable('xf_user_connected_account', function(Alter $table)
		{
			$table->dropColumns('sync_date');
		});
		
		$this->schemaManager()->alterTable('xf_user_option', function(Alter $table)
		{
			$table->dropColumns('discord_options');
		});
	}
	
	public function uninstallStep2()
	{
		$this->db()->delete('xf_connected_account_provider', 'provider_class = ?', 'EWR\Discord:Provider\Discord');
	}
	
	public function upgrade2000Step1()
	{
		$this->installStep1();
		$this->installStep2();
	}
	
	public function upgrade2012Step1()
	{
		$this->installStep3();
	}
}