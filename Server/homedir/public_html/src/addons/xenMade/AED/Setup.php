<?php

namespace xenMade\AED;

use XF\AddOn\AbstractSetup;
use XF\AddOn\StepRunnerInstallTrait;
use XF\AddOn\StepRunnerUninstallTrait;
use XF\AddOn\StepRunnerUpgradeTrait;
use XF\Db\Schema\Alter;
use XF\Db\Schema\Create;

class Setup extends AbstractSetup
{
	use StepRunnerInstallTrait;
	use StepRunnerUpgradeTrait;
	use StepRunnerUninstallTrait;

    public function installStep1()
    {
        $this->schemaManager()->createTable('xf_xenmade_aed_log', function(\XF\Db\Schema\Create $table)
        {
            $table->addColumn('aed_id', 'int')->autoIncrement();
            $table->addColumn('from_user_id', 'int');
            $table->addColumn('to_user_id', 'int');
            $table->addColumn('user_fingerprint', 'varbinary', 32);
            $table->addColumn('ip_address', 'varbinary', 16);
            $table->addColumn('login_date', 'int');

            $table->addPrimaryKey('aed_id');

            $table->addKey('to_user_id');
            $table->addKey('from_user_id');
            $table->addKey('login_date');
            $table->addKey('user_fingerprint');
            $table->addKey('ip_address');
        });
    }

    public function upgrade20007Step1()
    {
        $sm = $this->schemaManager();

        $sm->alterTable('xf_user', function(Alter $table)
        {
            $table->dropColumns('bfp');
        });
    }

    public function upgrade20010Step1()
    {
        $sm = $this->schemaManager();

        if(!$sm->tableExists('xf_xenmade_aed_log'))
        {
            $this->schemaManager()->createTable('xf_xenmade_aed_log', function(\XF\Db\Schema\Create $table)
            {
                $table->addColumn('aed_id', 'int')->autoIncrement();
                $table->addColumn('from_user_id', 'int');
                $table->addColumn('to_user_id', 'int');
                $table->addColumn('user_fingerprint', 'varbinary', 32);
                $table->addColumn('ip_address', 'varbinary', 16);
                $table->addColumn('login_date', 'int');

                $table->addPrimaryKey('aed_id');

                $table->addKey('to_user_id');
                $table->addKey('from_user_id');
                $table->addKey('login_date');
                $table->addKey('user_fingerprint');
                $table->addKey('ip_address');
            });
        }
    }

    public function uninstallStep1(array $stepParams = [])
    {
        $this->schemaManager()->dropTable('xf_xenmade_aed_log');
    }
}