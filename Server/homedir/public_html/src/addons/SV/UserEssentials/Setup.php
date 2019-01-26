<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials;

use SV\Utils\InstallerSoftRequire;
use XF\AddOn\AbstractSetup;
use XF\AddOn\StepRunnerInstallTrait;
use XF\AddOn\StepRunnerUninstallTrait;
use XF\AddOn\StepRunnerUpgradeTrait;
use XF\Db\Schema\Alter;
use XF\Db\Schema\Create;
use XF\Entity\User;
use XF\PrintableException;

/**
 * Handles installation, upgrades, and uninstallation of the add-on.
 */
class Setup extends AbstractSetup
{
    // from https://github.com/Xon/XenForo2-Utils cloned to src/addons/SV/Utils
    use \SV\Utils\InstallerHelper;
    use StepRunnerInstallTrait;
    use StepRunnerUninstallTrait;
    use StepRunnerUpgradeTrait;

    /**
     * Creates add-on tables.
     */
    public function installStep1()
    {
        $sm = $this->schemaManager();

        foreach ($this->getTables() as $tableName => $callback)
        {
            $sm->createTable($tableName, $callback);
            $sm->alterTable($tableName, $callback);
        }
    }

    /**
     * Alters core tables.
     */
    public function installStep2()
    {
        $sm = $this->schemaManager();

        foreach ($this->getAlterTables() as $tableName => $callback)
        {
            $sm->alterTable($tableName, $callback);
        }
    }

    /**
     * Applies default permissions
     */
    public function installStep3()
    {
        $this->applyDefaultPermissions();
    }

    /**
     * Blocks upgrading from versions prior to v2.0.4
     *
     * @throws PrintableException
     */
    public function upgrade204Step1()
    {
        throw new PrintableException(
            'User Essentials v2.0.4+ is required to upgrade.'
        );
    }

    public function upgrade207Step1()
    {
        $this->db()->query("
                DELETE FROM xf_permission_entry
                WHERE permission_id IN ('addPollToOwnThread', 'addPollToOwnThreadLimit', 'unvotePollLimit')
            ");

        $this->db()->query("
                DELETE FROM xf_permission_entry_content
                WHERE permission_id IN ('addPollToOwnThread', 'addPollToOwnThreadLimit', 'unvotePollLimit')
            ");
    }

    public function upgrade2070001Step1()
    {
        $sm = $this->schemaManager();

        $tables = $this->getTables();
        if ($sm->tableExists('useress_thread_lock') && isset($tables['xf_sv_thread_lock']))
        {
            $callback = $tables['xf_sv_thread_lock'];
            $columns = $sm->getTableColumnDefinitions('useress_thread_lock');
            if (empty($columns['lockedByUser']) || empty($columns['allowLockByUser']) || empty($columns['allowUnlockByUser']))
            {
                $sm->alterTable('useress_thread_lock', $callback);
                $this->db()->query('
                    UPDATE useress_thread_lock
                    SET allowUnlockByUser = 0, allowLockByUser = 0
                    WHERE lockedByUser = 0
                ');
            }
        }
    }

    /**
     * Applies new permission defaults.
     */
    public function upgrade2070900Step1()
    {
        $this->applyDefaultPermissions(2070900);
    }

    public function upgrade3000200Step1()
    {
        $sm = $this->schemaManager();

        $sm->dropTable('useress_unc_queue');
        $sm->dropTable('useress_unc_queue_content');
        $this->migrateTable('useress_unc', 'xf_sv_unc');
        $this->migrateTable('useress_unc_cron', 'xf_sv_unc_cron');
        $this->migrateTable('useress_user_log', 'xf_sv_user_log');
        $this->migrateTable('useress_thread_lock', 'xf_sv_thread_lock');
    }

    /**
     * Creates add-on tables.
     */
    public function upgrade3000200Step2()
    {
        $this->installStep1();
    }

    /**
     * Alters core tables.
     */
    public function upgrade3000200Step3()
    {
        $this->installStep2();
    }

    /**
     * @param int   $previousVersion
     * @param array $stateChanges
     */
    public function postUpgrade($previousVersion, array &$stateChanges)
    {
        if ($this->applyDefaultPermissions($previousVersion))
        {
            $this->app->jobManager()->enqueueUnique(
                'permissionRebuild',
                'XF:PermissionRebuild',
                [],
                false
            );
        }
    }

    /**
     * Drops add-on tables.
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
     * Drops columns from core tables.
     */
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

        $tables['xf_sv_unc'] = function ($table) {
            /** @var Create|Alter $table */
            $this->addOrChangeColumn($table, 'unc_id', 'int')->autoIncrement();
            $this->addOrChangeColumn($table, 'user_id', 'int');
            $this->addOrChangeColumn($table, 'from_username', 'varchar', 50);
            $this->addOrChangeColumn($table, 'to_username', 'varchar', 50);
            $this->addOrChangeColumn($table, 'date', 'int');
            $this->addOrChangeColumn($table, 'ip_address', 'varbinary', 16)->setDefault('');
            $this->addOrChangeColumn($table, 'is_private', 'tinyint')->setDefault(0);
            $this->addOrChangeColumn($table, 'via_acp', 'tinyint')->setDefault(0);
            $this->addOrChangeColumn($table, 'user_note', 'varchar', 255)->setDefault('');
            $this->addOrChangeColumn($table, 'moderator_note', 'varchar', 255)->setDefault('');
            $this->addOrChangeColumn($table, 'moderator_id', 'int');
            $this->addOrChangeColumn($table, 'moderation_date', 'int');
            $this->addOrChangeColumn($table, 'status', 'enum')->values(['approved', 'denied', 'moderated'])->setDefault('approved');
            $table->addKey('user_id');
        };

        $tables['xf_sv_unc_cron'] = function ($table) {
            /** @var Create|Alter $table */
            $this->addOrChangeColumn($table, 'user_id', 'int');
            $this->addOrChangeColumn($table, 'date', 'int');
            $this->addOrChangeColumn($table, 'old_custom_title', 'varchar', 50)->setDefault('');
            $this->addOrChangeColumn($table, 'new_custom_title', 'varchar', 50)->setDefault('');
            $table->addPrimaryKey('user_id');
        };

        $tables['xf_sv_user_log'] = function ($table) {
            /** @var Create|Alter $table */
            $this->addOrChangeColumn($table, 'user_log_id', 'int')->autoIncrement();
            $this->addOrChangeColumn($table, 'log_date', 'int');
            $this->addOrChangeColumn($table, 'user_id', 'int');
            $this->addOrChangeColumn($table, 'ip_address', 'varbinary', 16)->setDefault('');
            $this->addOrChangeColumn($table, 'content_type', 'varchar', 25);
            $this->addOrChangeColumn($table, 'content_id', 'int');
            $this->addOrChangeColumn($table, 'content_user_id', 'int');
            $this->addOrChangeColumn($table, 'content_username', 'varchar', 50);
            $this->addOrChangeColumn($table, 'content_title', 'varchar', 200);
            $this->addOrChangeColumn($table, 'content_url', 'text');
            $this->addOrChangeColumn($table, 'discussion_content_type', 'varchar', 25);
            $this->addOrChangeColumn($table, 'discussion_content_id', 'int');
            $this->addOrChangeColumn($table, 'action', 'varchar', 25);
            $this->addOrChangeColumn($table, 'action_params', 'mediumblob');
            $table->addKey('log_date');
            $table->addKey(['user_id', 'content_type', 'content_id'], 'user_id_content_type_id');
            $table->addKey(['user_id', 'log_date'], 'user_id_log_date');
        };

        $tables['xf_sv_thread_lock'] = function ($table) {
            /** @var Create|Alter $table */
            $this->addOrChangeColumn($table, 'thread_id', 'int');
            $this->addOrChangeColumn($table, 'user_id', 'int')->setDefault(null)->nullable();
            $this->addOrChangeColumn($table, 'lockedByUser', 'tinyint', 3)->setDefault(0);
            $this->addOrChangeColumn($table, 'allowLockByUser', 'tinyint', 3)->setDefault(1);
            $this->addOrChangeColumn($table, 'allowUnlockByUser', 'tinyint', 3)->setDefault(1);
            $this->addOrChangeColumn($table, 'replyBanInOwnThread', 'tinyint', 3)->setDefault(1);
            $table->addPrimaryKey('thread_id');
        };

        $tables['xf_sv_content_mentions'] = function ($table) {
            /** @var Create|Alter $table */
            $this->addOrChangeColumn($table, 'content_type', 'varbinary', 25);
            $this->addOrChangeColumn($table, 'content_id', 'int');
            $this->addOrChangeColumn($table, 'mention_ids', 'blob');
            $this->addOrChangeColumn($table, 'has_mentions', 'tinyint', 3);
            $table->addPrimaryKey(['content_type', 'content_id']);
        };

        return $tables;
    }

    /**
     * @return array
     */
    protected function getAlterTables()
    {
        $tables = [];

        $tables['xf_thread'] = function (Alter $table) {
            $table->addKey('last_post_user_id', 'last_post_user_id');
        };

        $tables['xf_report'] = function (Alter $table) {
            $table->addKey('last_modified_user_id', 'last_modified_user_id');
        };

        $tables['xf_user'] = function (Alter $table) {
            $this->addOrChangeColumn($table, 'useress_tags', 'mediumblob')->nullable(true)->setDefault(null);
        };

        $tables['xf_user_upgrade'] = function (Alter $table) {
            $this->addOrChangeColumn($table, 'quantity', 'int')->setDefault(0);
        };

        return $tables;
    }

    protected function getRemoveAlterTables()
    {
        $tables = [];

        $tables['xf_user'] = function (Alter $table) {
            $table->dropColumns('useress_tags');
        };

        $tables['xf_user_upgrade'] = function (Alter $table) {
            $table->dropIndexes('quantity');
        };

        return $tables;
    }

    /**
     * @param int $previousVersion
     * @return bool True if permissions were applied.
     */
    protected function applyDefaultPermissions($previousVersion = 0)
    {
        $applied = false;

        if ($previousVersion < 207)
        {
            $this->applyGlobalPermissionIntForGroup('forum', 'editOwnThreadTitleLimit', -1, User::GROUP_REG);
            $this->applyGlobalPermissionForGroup('forum', 'createPoll', User::GROUP_REG);

            $applied = true;
        }
        if ($previousVersion < 261)
        {
            $this->applyGlobalPermissionForGroup('forum', 'useressGoInvisible', User::GROUP_REG);

            $applied = true;
        }
        if ($previousVersion <= 2070900)
        {
            $this->applyGlobalPermission('forum', 'userEssReplyToOthers', 'forum', 'postReply');

            $applied = true;
        }

        return $applied;
    }


    use InstallerSoftRequire;

    /**
     * @param array $errors
     * @param array $warnings
     */
    public function checkRequirements(&$errors = [], &$warnings = [])
    {
        $this->checkSoftRequires($errors, $warnings);
        $this->isCliRecommended($warnings, 'svUserEssentialsCliWarning');
    }
}

