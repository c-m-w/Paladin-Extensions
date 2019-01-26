<?php

namespace NF\GiftUpgrades;

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
        $sm = $this->schemaManager();

        foreach ($this->getTables() as $tableName => $callback)
        {
            $sm->createTable($tableName, $callback);
            $sm->alterTable($tableName, $callback);
        }

        foreach ($this->getAlterTables() as $tableName => $callback)
        {
            $sm->alterTable($tableName, $callback);
        }
    }

    public function upgrade2000070Step1()
    {
        $this->installStep1();
    }

    public function uninstallStep1()
    {
        $sm = $this->schemaManager();

        foreach ($this->getTables() as $tableName => $callback)
        {
            $sm->dropTable($tableName);
        }
    }

    public function uninstallStep2()
    {
        $sm = $this->schemaManager();

        foreach ($this->getRemoveAlterTables() as $tableName => $callback)
        {
            $sm->alterTable($tableName, $callback);
        }
    }

    /**
     * @return array
     */
    protected function getTables()
    {
        $tables = [];

        $tables['xf_nf_gifted_content'] = function ($table) {
            /** @var Create|Alter $table */
            $this->addOrChangeColumn($table, 'gift_id', 'int')->autoIncrement();
            $this->addOrChangeColumn($table, 'user_upgrade_record_id', 'int');
            $this->addOrChangeColumn($table, 'content_type', 'varbinary', 25);
            $this->addOrChangeColumn($table, 'content_id', 'int');
            $this->addOrChangeColumn($table, 'gift_user_id', 'int');
            $this->addOrChangeColumn($table, 'is_anonymous', 'tinyint')->setDefault(0);
            $this->addOrChangeColumn($table, 'gift_date', 'int');
            $this->addOrChangeColumn($table, 'content_user_id', 'int');
            $table->addKey(['content_type', 'content_id'], 'content_type_content_id');
            $table->addKey(['gift_date'], 'gift_date');
        };

        $tables['xf_nixfifty_gift_upgrade_statistics'] = function ($table) {
            /** @var Create|Alter $table */
            $this->addOrChangeColumn($table, 'stat_id', 'int')->autoIncrement();
            $this->addOrChangeColumn($table, 'gift_upgrade_id', 'int');
            $this->addOrChangeColumn($table, 'stat_date', 'int');
        };

        return $tables;
    }

    /**
     * @return array
     */
    protected function getAlterTables()
    {
        $tables = [];

        $tables['xf_user_upgrade'] = function (Alter $table) {
            $this->addOrChangeColumn($table, 'can_gift', 'tinyint', 3)->setDefault(1);
        };

        $tables['xf_user_upgrade_active'] = function (Alter $table) {
            $this->addOrChangeColumn($table, 'is_gift', 'tinyint', 3)->setDefault(0);
            $this->addOrChangeColumn($table, 'pay_user_id', 'int')->setDefault(0);
        };

        $tables['xf_user_upgrade_expired'] = function (Alter $table) {
            $this->addOrChangeColumn($table, 'is_gift', 'tinyint', 3)->setDefault(0);
            $this->addOrChangeColumn($table, 'pay_user_id', 'int')->setDefault(0);
        };

        return $tables;
    }

    /**
     * @return array
     */
    protected function getRemoveAlterTables()
    {
        $tables = [];

        $tables['xf_user_upgrade'] = function (Alter $table) {
            $table->dropColumns(['can_gift']);
        };

        $tables['xf_user_upgrade_active'] = function (Alter $table) {
            $table->dropColumns(['is_gift', 'pay_user_id']);
        };

        $tables['xf_user_upgrade_expired'] = function (Alter $table) {
            $table->dropColumns(['is_gift', 'pay_user_id']);
        };

        return $tables;
    }

    /**
     * @param Create|Alter $table
     * @param string       $name
     * @param string|null  $type
     * @param string|null  $length
     * @return \XF\Db\Schema\Column
     */
    protected function addOrChangeColumn($table, $name, $type = null, $length = null)
    {
        if ($table instanceof Create)
        {
            $table->checkExists(true);

            return $table->addColumn($name, $type, $length);
        }
        else if ($table instanceof Alter)
        {
            if ($table->getColumnDefinition($name))
            {
                return $table->changeColumn($name, $type, $length);
            }

            return $table->addColumn($name, $type, $length);
        }
        else
        {
            throw new \LogicException("Unknown schema DDL type ". get_class($table));

        }
    }
}