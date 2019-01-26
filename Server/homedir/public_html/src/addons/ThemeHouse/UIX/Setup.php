<?php

namespace ThemeHouse\UIX;

use XF\AddOn\AbstractSetup;
use XF\AddOn\StepRunnerInstallTrait;
use XF\AddOn\StepRunnerUninstallTrait;
use XF\AddOn\StepRunnerUpgradeTrait;
use XF\Db\Schema\Alter;

class Setup extends AbstractSetup
{
    use StepRunnerInstallTrait;
    use StepRunnerUpgradeTrait;
    use StepRunnerUninstallTrait;

    // Upgrading from XF1 version of add-on
    public function upgrade2000031Step1()
    {
        $schemaManager = \XF::db()->getSchemaManager();
        $schemaManager->alterTable('xf_style', function (Alter $table) {
            $table->dropColumns([
                'audentio',
                'uix_pid',
                'uix_version',
                'uix_latest_version',
                'uix_update_available',
            ]);
        });

        $schemaManager->alterTable('xf_forum', function (Alter $table) {
            $table->dropColumns([
                'uix_last_sticky_action',
            ]);
        });

        $this->db()->delete('xf_node_type', 'node_type_id = \'uix_nodeLayoutSeparator\'');
        $schemaManager->dropTable('uix_node_layout');
        $schemaManager->dropTable('uix_node_fields');
    }

    public function upgrade2000031Step2()
    {
        $schemaManager = \XF::db()->getSchemaManager();
        $schemaManager->alterTable('xf_user_option', function (Alter $table) {
            $table->dropColumns([
                'uix_sidebar',
                'uix_collapse_stuck_threads',
                'uix_sticky_navigation',
                'uix_sticky_userbar',
                'uix_sticky_sidebar',
                'uix_width',
                'uix_collapse_user_info',
                'uix_collapse_stuck_threads',
                'uix_collapse_signature',
            ]);
        });
    }

    public function upgrade2000031Step3()
    {
        $schema = \XF::db()->getSchemaManager();
        $schema->alterTable('xf_style', function (Alter $table) {
            $table->addColumn('th_product_id_uix', 'int')->setDefault(0);
            $table->addColumn('th_product_version_uix', 'varchar', 250)->nullable()->setDefault(null);
        });

        $this->createWidget('footer_forumStatistics', 'forum_statistics', [
            'positions' => ['th_footer_uix' => 10]
        ]);
        $this->createWidget('footer_newPosts', 'new_posts', [
            'positions' => ['th_footer_uix' => 20]
        ]);
        $this->createWidget('footer_onlineStatistics', 'online_statistics', [
            'positions' => ['th_footer_uix' => 30]
        ]);
        $this->createWidget('footer_sharePage', 'share_page', [
            'positions' => ['th_footer_uix' => 40]
        ]);
    }

    public function upgrade2000032Step1()
    {
        $schemaManager = $this->schemaManager();
        $schemaManager->alterTable('xf_user_option', function (Alter $table) {
            if ($table->getColumnDefinition('th_width_uix')) {
                $table->dropColumns([
                    'th_width_uix',
                    'th_sidebar_collapsed_uix',
                ]);
            }
        });
    }

    public function upgrade2000411Step1()
    {
        $schemaManager = $this->schemaManager();
        $schemaManager->alterTable('xf_style', function (Alter $table) {
            $table->addColumn('th_primary_child_uix', 'boolean')->setDefault(0);
        });
    }

    public function upgrade2000531Step1()
    {
        $schemaManager = $this->schemaManager();
        $schemaManager->alterTable('xf_style', function (Alter $table) {
            $table->addColumn('th_child_style_xml_uix', 'varchar', 100)->setDefault('');
            $table->addColumn('th_child_style_cache_uix', 'blob')->nullable();
        });
    }

    public function postUpgrade($previousVersion, array &$stateChanges)
    {
        if ($this->applyDefaultPermissions($previousVersion)) {
            $this->app->jobManager()->enqueueUnique(
                'permissionRebuild',
                'XF:PermissionRebuild',
                [],
                false
            );
        }
    }

    public function installStep1()
    {
        $schema = \XF::db()->getSchemaManager();
        $schema->alterTable('xf_style', function (Alter $table) {
            $table->addColumn('th_product_id_uix', 'int')->setDefault(0);
            $table->addColumn('th_product_version_uix', 'varchar', 250)->nullable()->setDefault(null);
            $table->addColumn('th_primary_child_uix', 'boolean')->setDefault(0);
            $table->addColumn('th_child_style_xml_uix', 'varchar', 100)->setDefault('');
            $table->addColumn('th_child_style_cache_uix', 'blob')->nullable();
        });
    }

    /**
     * @throws \XF\PrintableException
     */
    public function installStep2()
    {
        $this->applyDefaultWidgets();
    }

    /**
     * @param array $stateChanges
     * @throws \XF\PrintableException
     */
    public function postInstall(array &$stateChanges)
    {
        $this->applyDefaultWidgets();
        $this->applyDefaultPermissions();
    }

    public function uninstallStep1()
    {
        $schema = \XF::db()->getSchemaManager();
        $schema->alterTable('xf_style', function (Alter $table) {
            $table->dropColumns([
                'th_product_id_uix',
                'th_product_version_uix',
                'th_primary_child_uix',
                'th_child_style_xml_uix'
            ]);
        });
    }

    /**
     * @param int $previousVersion
     * @return bool
     * @throws \XF\PrintableException
     */
    protected function applyDefaultWidgets($previousVersion = 0)
    {
        $widgets = [];

        if ($previousVersion < 2000000) {
            $widgets[] = [
                'key' => 'thuix_footer_aboutUsWidget',
                'definition_id' => 'html',
                'title' => 'About us',
                'config' => [
                    'positions' => [
                        'th_footer_uix' => 10,
                    ],
                    'options' => [
                        'advanced_mode' => true,
                        'template_title' => '_widget_thuix_aboutUsWidget',
                    ],
                ],
                'template_contents' => '<div class="block" data-widget-definition="th_aboutUs">
    <div class="block-container">
        <h3 class="block-minorHeader">About us</h3>
        <ul class="block-body">
            <li class="block-row">Our community has been around for many years and pride ourselves on offering unbiased, critical discussion among people of all different backgrounds. We are working every day to make sure our community is one of the best.</li>
        </ul>
    </div>
</div>',
            ];

            $widgets[] = [
                'key' => 'thuix_footer_quickNavWidget',
                'definition_id' => 'html',
                'title' => 'Quick navigation',
                'config' => [
                    'positions' => [
                        'th_footer_uix' => 20,
                    ],
                    'options' => [
                        'advanced_mode' => true,
                        'template_title' => '_widget_thuix_quickNavWidget',
                    ],
                ],
                'template_contents' => '<div class="block" data-widget-definition="th_navigation">
    <div class="block-container">
        <h3 class="block-minorHeader">Quick Navigation</h3>
        <div class="block-body">
            <xf:if is="$xf.options.homePageUrl">
            <a class="blockLink rippleButton" href="{$xf.options.homePageUrl}">{{ phrase(\'home\') }}</a>
            </xf:if>
            <a class="blockLink rippleButton" href="{{ link(\'forums\') }}">{{ phrase(\'forums\') }}</a>
            <xf:if is="$xf.visitor.canUseContactForm()">
                <xf:if is="$xf.options.contactUrl.type == \'default\'">
                    <a class="blockLink rippleButton" href="{{ link(\'misc/contact\') }}" data-xf-click="overlay">{{ phrase(\'contact_us\') }}</a>
                <xf:elseif is="$xf.options.contactUrl.type == \'custom\'" />
                    <a class="blockLink rippleButton" href="{$xf.options.contactUrl.custom}" data-xf-click="{{ $xf.options.contactUrl.overlay ? \'overlay\' : \'\' }}">{{ phrase(\'contact_us\') }}</a>
                </xf:if>
            </xf:if>
        </div>
    </div>
</div>',
            ];

            $widgets[] = [
                'key' => 'thuix_footer_userNavWidget',
                'definition_id' => 'html',
                'title' => 'User menu',
                'config' => [
                    'positions' => [
                        'th_footer_uix' => 30,
                    ],
                    'options' => [
                        'advanced_mode' => true,
                        'template_title' => '_widget_thuix_userNavWidget',
                    ],
                ],
                'template_contents' => '<div class="block" data-widget-definition="th_userNavigation">
    <div class="block-container">
        <h3 class="block-minorHeader">User Menu</h3>
        <div class="block-body">
            <xf:if is="$xf.visitor.user_id">
                <a class="blockLink rippleButton" href="{{ link(\'members\', $xf.visitor) }}">{{ phrase(\'th_profile_uix\') }}</a>
                <a class="blockLink rippleButton" href="{{ link(\'account/account-details\') }}">{{ phrase(\'account_details\') }}</a>
                <a class="blockLink rippleButton" href="{{ link(\'whats-new/news-feed\') }}">{{ phrase(\'news_feed\') }}</a>
                <a class="blockLink rippleButton" href="{{ link(\'logout\', null, {\'t\': csrf_token()}) }}">{{ phrase(\'log_out\') }}</a>
            <xf:else />
                <a class="blockLink rippleButton" href="{{ link(\'login\') }}">{{ phrase(\'login\') }}</a>
            </xf:if>
        </div>
    </div>
</div>',
            ];

            $widgets[] = [
                'key' => 'thuix_footer_facebookWidget',
                'definition_id' => 'thuix_socialMedia',
                'title' => 'Follow us on Facebook',
                'config' => [
                    'positions' => [
                        'th_footer_uix' => 40,
                    ],
                    'options' => [
                        'platform' => 'facebook',
                        'name' => 'themehouse',
                    ],
                ],
            ];
        }

        foreach ($widgets as $widget) {
            $title = '';
            if (!empty($widget['title'])) {
                $title = $widget['title'];
            }

            if ($widget['definition_id'] === 'html' && !empty($widget['config']['options']['template_title']) && isset($widget['template_contents'])) {
                $templateTitle = $widget['config']['options']['template_title'];

                /** @var \XF\Entity\Template $template */
                $template = $this->app->em()->getFinder('XF:Template')->where('style_id', '=', 0)->where('title', '=',
                    $templateTitle)->where('type', '=', 'public')->fetchOne();
                if (!$template) {
                    $template = $this->app->em()->create('XF:Template');
                    $template->style_id = 0;
                    $template->title = $templateTitle;
                    $template->type = 'public';
                }

                $template->template = $widget['template_contents'];
                $template->save();
            }

            $this->createWidget($widget['key'], $widget['definition_id'], $widget['config'], $title);
        }

        if (empty($widgets)) {
            return false;
        }

        return true;
    }

    protected function applyDefaultPermissions($previousVersion = 0)
    {
        $permissions = [];
        $db = $this->db();
        if ($previousVersion < 2000032) {
            $permissions[] = [
                'user_group_id' => 1,
                'permission_id' => 'showWelcomeSection',
                'permission_value' => 'allow',
            ];

            $permissions[] = [
                'user_group_id' => 1,
                'permission_id' => 'togglePageWidth',
                'permission_value' => 'allow',
            ];
            $permissions[] = [
                'user_group_id' => 2,
                'permission_id' => 'togglePageWidth',
                'permission_value' => 'allow',
            ];

            $permissions[] = [
                'user_group_id' => 1,
                'permission_id' => 'collapseCategories',
                'permission_value' => 'allow',
            ];
            $permissions[] = [
                'user_group_id' => 2,
                'permission_id' => 'collapseCategories',
                'permission_value' => 'allow',
            ];

            $permissions[] = [
                'user_group_id' => 1,
                'permission_id' => 'collapseSidebar',
                'permission_value' => 'allow',
            ];
            $permissions[] = [
                'user_group_id' => 2,
                'permission_id' => 'collapseSidebar',
                'permission_value' => 'allow',
            ];
        }

        foreach ($permissions as $permission) {
            $permission = array_merge([
                'user_id' => 0,
                'permission_group_id' => 'th_uix',
                'permission_value' => 'use_int',
                'permission_value_int' => 0,
            ], $permission);

            try {
                $db->insert('xf_permission_entry', $permission);
            } catch (\Exception $e) {
            }
        }

        if (empty($permissions)) {
            return false;
        }

        return true;
    }
}