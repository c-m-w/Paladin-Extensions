<?php

namespace xenMade\LAU;

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
        $this->schemaManager()->createTable('xf_xenmade_lau_log', function(\XF\Db\Schema\Create $table)
        {
            $table->addColumn('log_id', 'int')->autoIncrement();
            $table->addColumn('from_user_id', 'int')->setDefault(0);
            $table->addColumn('from_username', 'varchar', 50);
            $table->addColumn('to_user_id', 'int')->setDefault(0);
            $table->addColumn('to_username', 'varchar', 50);
            $table->addColumn('dateline', 'int')->setDefault(0);
            $table->addColumn('reason', 'varchar', 255);
            $table->addColumn('ip_address', 'varbinary', 16)->setDefault('');

            $table->addPrimaryKey('log_id');
            $table->addKey('from_user_id');
            $table->addKey('to_user_id');
        });
    }

    public function upgrade20001Step1()
    {
        $this->installStep1();
    }

    public function uninstallStep1(array $stepParams = [])
    {
        $sm = $this->schemaManager();

        $this->schemaManager()->dropTable('xf_xenmade_lau_log');
    }
}