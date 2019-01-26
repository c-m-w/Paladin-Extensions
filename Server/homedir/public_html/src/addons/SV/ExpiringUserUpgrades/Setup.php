<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\ExpiringUserUpgrades;

use SV\Utils\InstallerHelper;
use XF\AddOn\AbstractSetup;
use XF\AddOn\StepRunnerInstallTrait;
use XF\AddOn\StepRunnerUninstallTrait;
use XF\AddOn\StepRunnerUpgradeTrait;
use XF\Db\Schema\Alter;

/**
 * Add-on installation, upgrade, and uninstall routines.
 */
class Setup extends AbstractSetup
{
    // from https://github.com/Xon/XenForo2-Utils cloned to src/addons/SV/Utils
    use InstallerHelper;
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
    }

    public function installStep2()
    {
        $sm = $this->schemaManager();

        foreach ($this->getAlterTables() as $tableName => $callback)
        {
            $sm->alterTable($tableName, $callback);
        }
    }

    public function installStep3()
    {
        $this->applyRegistrationDefaults([
            'sv_exup_email_on_expiring_expired_upgrade' => 1,
            'sv_exup_email_on_upgrade_purchase' => 1,
            'sv_exup_email_on_upgrade_reversal' => 1
        ]);
    }

    public function upgrade2000000Step1()
    {
        $this->installStep1();
    }

    public function upgrade2000000Step2()
    {
        $this->installStep2();
    }

    public function upgrade2000000Step3()
    {
        $db = $this->db();

        $upgrades = $db->fetchAllKeyed(
            '
                SELECT *
                FROM xf_user_upgrade
            ', 'user_upgrade_id'
        );

        if (!empty($upgrades))
        {
            foreach ($upgrades AS $upgrade)
            {
                $records = $this->app()->finder('XF:UserUpgradeActive')
                                ->where('user_upgrade_id', '=', $upgrade['user_upgrade_id'])
                                ->fetch();

                // must update records one by one rather than in batches as other add-ons may have added their own info to the extra array of certain records
                foreach ($records AS $record)
                {
                    /** @var \XF\Entity\UserUpgradeActive $record */
                    $extra = $record->extra;

                    $extra['extra_group_ids'] = $upgrade['extra_group_ids'];
                    $extra['recurring'] = $upgrade['recurring'];

                    // VB import does not seem to save these extra values so must do so now
                    if (!isset($extra['cost_amount']))
                    {
                        $extra['cost_amount'] = $upgrade['cost_amount'];
                    }
                    if (!isset($extra['cost_currency']))
                    {
                        $extra['cost_currency'] = $upgrade['cost_currency'];
                    }
                    if (!isset($extra['length_amount']))
                    {
                        $extra['length_amount'] = $upgrade['length_amount'];
                    }
                    if (!isset($extra['length_unit']))
                    {
                        $extra['length_unit'] = $upgrade['length_unit'];
                    }

                    // save the current user groups so we can later know if the upgrade details have changed.
                    // we use this in order to know whether to display the 'Extend Upgrade' button.
                    $record->fastUpdate('extra', $extra);
                }
            }
        }
    }

    public function upgrade2000001Step1()
    {
        // migrate alerts
        $this->db()->query('update xf_user_alert set action = ? where action = ? and content_type = ?',
            ['payment_reversal_upgrade', 'payment_reversal', 'exup']);
        $this->db()->query('update xf_user_alert set action = ? where action = ? and content_type = ?',
            ['payment_reversal_extend_upgrade', 'upgrade_payment_reversal', 'exup']);
    }

    public function upgrade2000002Step1()
    {
        $this->db()->query(
            'update xf_user_upgrade_active 
          set notified_date = 0 
          where notified_date > 0 && end_date <= (UNIX_TIMESTAMP() + (86400 * 7))'
        );
    }

    public function upgrade2000300Step1()
    {
        $this->installStep3();
    }

    /**
     * Reverts database schema changes - dropping tables
     */
    public function uninstallStep1()
    {
        $sm = $this->schemaManager();

        foreach ($this->getTables() as $tableName => $callback)
        {
            $sm->dropTable($tableName);
        }
    }

    /**
     * Reverts database schema changes - table alters
     */
    public function uninstallStep2()
    {
        $sm = $this->schemaManager();

        foreach ($this->getRemoveAlterTables() as $tableName => $callback)
        {
            $sm->alterTable($tableName, $callback);
        }
    }

    public function uninstallStep3()
    {
        $db = $this->db();
        $db->query("DELETE FROM xf_user_alert WHERE content_type = 'exup'");
    }

    /**
     * @return array
     */
    protected function getTables()
    {
        $tables = [];

        return $tables;
    }

    /**
     * @return array
     */
    protected function getAlterTables()
    {
        $tables = [];

        $tables['xf_user_upgrade_active'] = function (Alter $table) {
            $table->addKey(['user_upgrade_id'], 'user_upgrade_id');
            $this->addOrChangeColumn($table, 'notified_date', 'int')->setDefault(0);
        };

        $tables['xf_user_upgrade'] = function (Alter $table) {
            $this->addOrChangeColumn($table, 'exup_days', 'int')->setDefault(7);
        };

        $tables['xf_user_option'] = function (Alter $table) {
            $this->addOrChangeColumn($table, 'sv_exup_email_on_expiring_expired_upgrade', 'tinyint', 3)->setDefault(1);
            $this->addOrChangeColumn($table, 'sv_exup_email_on_upgrade_purchase', 'tinyint', 3)->setDefault(1);
            $this->addOrChangeColumn($table, 'sv_exup_email_on_upgrade_reversal', 'tinyint', 3)->setDefault(1);
        };

        return $tables;
    }

    /**
     * @return array
     */
    protected function getRemoveAlterTables()
    {
        $tables = [];

        $tables['xf_user_upgrade_active'] = function (Alter $table) {
            $table->dropColumns(['notified_date']);
            $table->dropIndexes(['user_upgrade_id']);
        };

        $tables['xf_user_upgrade'] = function (Alter $table) {
            $table->dropColumns(['exup_days']);
        };

        $tables['xf_user_option'] = function (Alter $table) {
            $table->dropColumns([
                'sv_exup_email_on_expiring_expired_upgrade',
                'sv_exup_email_on_upgrade_purchase',
                'sv_exup_email_on_upgrade_reversal'
            ]);
        };

        return $tables;
    }
}