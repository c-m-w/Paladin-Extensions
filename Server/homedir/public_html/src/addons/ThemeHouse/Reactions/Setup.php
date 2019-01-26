<?php

namespace ThemeHouse\Reactions;

use XF\AddOn\AbstractSetup;
use XF\AddOn\StepRunnerInstallTrait;
use XF\AddOn\StepRunnerUninstallTrait;
use XF\AddOn\StepRunnerUpgradeTrait;
use XF\Db\Schema\Alter;
use XF\Db\Schema\Create;
use XF\Util\Xml;

class Setup extends AbstractSetup
{
    use StepRunnerInstallTrait;
    use StepRunnerUpgradeTrait;
    use StepRunnerUninstallTrait;

    /**
     * Install Functions
     */
    public function installStep1()
    {
        $schemaManager = $this->db()->getSchemaManager();

        $schemaManager->createTable('xf_th_reaction', function (Create $table) {
            $table->addColumn('reaction_id', 'int')->autoIncrement();
            $table->addColumn('title', 'varchar', 50);
            $table->addColumn('reaction_type_id', 'varchar', 25);
            $table->addColumn('styling_type', 'varchar', 25);
            $table->addColumn('reaction_text', 'varchar', 10);
            $table->addColumn('image_url', 'varchar', 250);
            $table->addColumn('image_url_2x', 'varchar', 250);
            $table->addColumn('image_type', 'varchar', 25);
            $table->addColumn('styling', 'text');
            $table->addColumn('user_criteria', 'mediumblob')->nullable();
            $table->addColumn('react_handler', 'varbinary', 255);
            $table->addColumn('options', 'text');
            $table->addColumn('display_order', 'int')->setDefault(1);
            $table->addColumn('like_wrapper', 'bool')->setDefault(0);
            $table->addColumn('random', 'bool')->setDefault(0);
            $table->addColumn('enabled', 'bool')->setDefault(1);
            $table->addColumn('is_default', 'bool')->setDefault(0);
        });

        $schemaManager->createTable('xf_th_reaction_type', function (Create $table) {
            $table->addColumn('reaction_type_id', 'varchar', 25);
            $table->addColumn('title', 'varchar', 50);
            $table->addColumn('color', 'varchar', 25);
            $table->addColumn('display_order', 'int')->setDefault(1);
            $table->addColumn('notable_member', 'bool')->setDefault(0);
            $table->addPrimaryKey('reaction_type_id');
        });

        $schemaManager->createTable('xf_th_reacted_content', function (Create $table) {
            $table->addColumn('react_id', 'int')->autoIncrement();
            $table->addColumn('reaction_id', 'int');
            $table->addColumn('content_type', 'varbinary', 25);
            $table->addColumn('content_id', 'int');
            $table->addColumn('react_user_id', 'int');
            $table->addColumn('react_date', 'int');
            $table->addColumn('content_user_id', 'int');
            $table->addColumn('is_counted', 'bool')->setDefault(1);
            $table->addKey(['content_type', 'content_id', 'react_user_id'], 'content_type_id_react_user_id');
            $table->addKey(['react_user_id', 'content_type', 'content_id'], 'react_user_content_type_id');
            $table->addKey(['content_user_id', 'react_date'], 'content_user_id_react_date');
            $table->addKey('react_date', 'react_date');
        });

        $schemaManager->createTable('xf_th_reaction_user_count', function (Create $table) {
            $table->addColumn('user_id', 'int');
            $table->addColumn('reaction_id', 'int');
            $table->addColumn('content_type', 'varbinary', 25);
            $table->addColumn('count_received', 'int')->setDefault(0);
            $table->addColumn('count_given', 'int')->setDefault(0);
            $table->addKey(['user_id', 'reaction_id'], 'user_reaction_id');
            $table->addUniqueKey(['content_type', 'user_id', 'reaction_id'], 'content_type_user_reaction_id');
        });

        $schemaManager->createTable('xf_th_reaction_content_count', function (Create $table) {
            $table->addColumn('content_id', 'int');
            $table->addColumn('content_type', 'varbinary', 25);
            $table->addColumn('reaction_id', 'int');
            $table->addColumn('count', 'int')->setDefault(0);
            $table->addUniqueKey(['content_type', 'content_id'], 'content_type_id');
        });
    }

    public function installStep2()
    {
        $schemaManager = $this->db()->getSchemaManager();

        $this->applyGlobalPermission('thReactions', 'canReact');
        $this->applyGlobalPermission('thReactions', 'canRemoveOwnReacts');
        $this->applyGlobalPermission('thReactions', 'canViewReactsList');

        $this->applyGlobalPermissionInt('thReactions', 'maxReactsPerContent', '1');
        $this->applyGlobalPermissionInt('thReactions', 'maxReactsPerContent', '1');
        $this->applyGlobalPermissionInt('thReactions', 'dailyReactLimit', '-1');

        $schemaManager->alterTable('xf_thread', function (Alter $table) {
            $table->addColumn('first_react_users', 'mediumblob')->nullable();
        });

        $schemaManager->alterTable('xf_conversation_master', function (Alter $table) {
            $table->addColumn('first_react_users', 'mediumblob')->nullable();
        });

        $schemaManager->alterTable('xf_user', function (Alter $table) {
            $table->addColumn('react_count', 'mediumblob')->nullable();
        });
    }

    public function installStep3()
    {
        $schemaManager = $this->db()->getSchemaManager();
        $schemaManager->alterTable('xf_post', function (Alter $table) {
            $table->addColumn('react_users', 'mediumblob')->nullable();
        });
    }

    public function installStep4()
    {
        $schemaManager = $this->db()->getSchemaManager();
        $schemaManager->alterTable('xf_conversation_message', function (Alter $table) {
            $table->addColumn('react_users', 'mediumblob')->nullable();
        });
    }

    public function installStep5()
    {
        $schemaManager = $this->db()->getSchemaManager();

        $schemaManager->alterTable('xf_profile_post', function (Alter $table) {
            $table->addColumn('react_users', 'mediumblob')->nullable();
        });
        $schemaManager->alterTable('xf_profile_post_comment', function (Alter $table) {
            $table->addColumn('react_users', 'mediumblob')->nullable();
        });
    }

    public function installStep6()
    {
        /** @var \ThemeHouse\Reactions\Repository\Setup $repo */
        $repo = \XF::repository('ThemeHouse\Reactions:Setup');

        if (!empty($this->app->registry()['addOns']['XFRM'])) {
            $repo->setupColumnsForAddOn('XFRM');
        }

        if (!empty($this->app->registry()['addOns']['XFMG'])) {
            $repo->setupColumnsForAddOn('XFMG');
        }
    }

    public function installStep7()
    {
        $this->applyDefaultWidgets();
    }

    public function postInstall(array &$stateChanges)
    {
        /** @var \ThemeHouse\Reactions\Service\Import $reactionImporter */
        $reactionImporter = \XF::service('ThemeHouse\Reactions:Import');

        $xml = Xml::openFile(\XF::getSourceDirectory() . '/addons/ThemeHouse/Reactions/reactions.xml');
        if ($xml) {
            $reactionTypes = $reactionImporter->getReactionTypeFromXml($xml);
            $reactionImporter->importReactionTypes($reactionTypes);

            $reactions = $reactionImporter->getReactionFromXml($xml);
            $reactionImporter->importReactions($reactions);
        }

        $this->applyDefaultWidgets();
    }

    public function upgrade1000294Step1()
    {
        $schemaManager = $this->schemaManager();

        $schemaManager->alterTable('xf_th_reaction', function (Alter $table) {
            $table->changeColumn('user_criteria', 'mediumblob')->nullable();
        });
    }

    public function upgrade1000294Step2()
    {
        $schemaManager = $this->schemaManager();

        $schemaManager->alterTable('xf_thread', function (Alter $table) {
            $table->changeColumn('first_react_users', 'blob')->nullable();
        });

        $schemaManager->alterTable('xf_conversation_master', function (Alter $table) {
            $table->changeColumn('first_react_users', 'blob')->nullable();
        });

        $schemaManager->alterTable('xf_user', function (Alter $table) {
            $table->changeColumn('react_count', 'blob')->nullable();
        });
    }

    public function upgrade1000294Step3()
    {
        $schemaManager = $this->schemaManager();

        $schemaManager->alterTable('xf_post', function (Alter $table) {
            $table->changeColumn('react_users', 'blob')->nullable();
        });
    }

    public function upgrade1000294Step4()
    {
        $schemaManager = $this->db()->getSchemaManager();

        $schemaManager->alterTable('xf_conversation_message', function (Alter $table) {
            $table->changeColumn('react_users', 'blob')->nullable();
        });
    }

    public function upgrade1000294Step5()
    {
        $schemaManager = $this->db()->getSchemaManager();

        $schemaManager->alterTable('xf_profile_post', function (Alter $table) {
            $table->changeColumn('react_users', 'blob')->nullable();
        });
        $schemaManager->alterTable('xf_profile_post_comment', function (Alter $table) {
            $table->changeColumn('react_users', 'blob')->nullable();
        });
    }

    public function upgrade1000470Step1()
    {
        $schemaManager = $this->schemaManager();

        $schemaManager->renameTable('xf_th_reaction_count', 'xf_th_reaction_user_count');

        $schemaManager->createTable('xf_th_reaction_content_count', function (Create $table) {
            $table->addColumn('content_id', 'int');
            $table->addColumn('content_type', 'varbinary', 25);
            $table->addColumn('reaction_id', 'int');
            $table->addColumn('count', 'int')->setDefault(0);
            $table->addUniqueKey(['content_type', 'content_id'], 'content_type_id');
        });
    }

    public function upgrade1000711Step1()
    {
        $schemaManager = $this->schemaManager();

        if (!empty($this->app->registry()['addOns']['XFRM'])) {
            $schemaManager->alterTable('xf_rm_resource_update', function (Alter $table) {
                $table->addColumn('react_users', 'blob')->nullable();
            });
        }
    }

    public function upgrade1000711Step2()
    {
        $schemaManager = $this->schemaManager();

        if (!empty($this->app->registry()['addOns']['XFMG'])) {
            $schemaManager->alterTable('xf_mg_media_item', function (Alter $table) {
                $table->addColumn('react_users', 'blob')->nullable();
            });
        }
    }

    public function upgrade1000712Step1()
    {
        $schemaManager = $this->schemaManager();

        $schemaManager->alterTable('xf_th_reaction_type', function (Alter $table) {
            $table->addColumn('notable_member', 'bool')->setDefault(0);
        });
    }

    public function upgrade1000870Step1()
    {
        $schemaManager = $this->schemaManager();

        $schemaManager->alterTable('xf_th_reaction_user_count', function (Alter $table) {
            $table->dropIndexes('user_reaction_id');
            $table->addKey(['user_id', 'reaction_id'], 'user_reaction_id');
        });
    }

    public function upgrade1001110Step1()
    {
        $schemaManager = $this->schemaManager();

        $schemaManager->alterTable('xf_th_reaction', function (Alter $table) {
            $table->addColumn('is_default', 'bool')->setDefault(0);
        });

        $db = $this->db();

        $db->query('UPDATE xf_th_reaction SET is_default=1 where like_wrapper=1');
    }

    public function upgrade1001370Step1()
    {
        $schemaManager = $this->schemaManager();

        if (!empty($this->app->registry()['addOns']['XFMG'])) {
            $schemaManager->alterTable('xf_mg_comment', function (Alter $table) {
                $table->addColumn('react_users', 'blob')->nullable();
            });
        }
    }

    public function upgrade1001370Step2()
    {
        if (!empty($this->app->registry()['addOns']['XFMG'])) {
            $this->db()->rawQuery("UPDATE xf_th_reaction SET react_handler = CONCAT(react_handler, ',xfmg_comment')");
        }
    }

    public function upgrade1001391Step1()
    {
        $this->schemaManager()->alterTable('xf_thread', function (Alter $table) {
            $table->changeColumn('first_react_users', 'mediumblob')->nullable();
        });
    }

    public function upgrade1001391Step2()
    {
        $this->schemaManager()->alterTable('xf_conversation_master', function (Alter $table) {
            $table->changeColumn('first_react_users', 'mediumblob')->nullable();
        });
    }

    public function upgrade1001391Step3()
    {
        $this->schemaManager()->alterTable('xf_user', function (Alter $table) {
            $table->changeColumn('react_count', 'mediumblob')->nullable();
        });
    }

    public function upgrade1001391Step4()
    {
        $this->schemaManager()->alterTable('xf_post', function (Alter $table) {
            $table->changeColumn('react_users', 'mediumblob')->nullable();
        });
    }

    public function upgrade1001391Step5()
    {
        $this->schemaManager()->alterTable('xf_conversation_message', function (Alter $table) {
            $table->changeColumn('react_users', 'mediumblob')->nullable();
        });
    }

    public function upgrade1001391Step6()
    {
        $this->schemaManager()->alterTable('xf_profile_post', function (Alter $table) {
            $table->changeColumn('react_users', 'mediumblob')->nullable();
        });
    }

    public function upgrade1001391Step7()
    {
        $this->schemaManager()->alterTable('xf_profile_post_comment', function (Alter $table) {
            $table->changeColumn('react_users', 'mediumblob')->nullable();
        });
    }

    public function upgrade1001391Step8()
    {
        if (!empty($this->app->registry()['addOns']['XFRM'])) {
            $this->schemaManager()->alterTable('xf_rm_resource_update', function (Alter $table) {
                $table->changeColumn('react_users', 'mediumblob')->nullable();
            });
        }
    }

    public function upgrade1001391Step9()
    {
        if (!empty($this->app->registry()['addOns']['XFMG'])) {
            try {
                $this->schemaManager()->alterTable('xf_mg_media_item', function (Alter $table) {
                    $table->changeColumn('react_users', 'mediumblob')->nullable();
                });

                $this->schemaManager()->alterTable('xf_mg_comment', function (Alter $table) {
                    $table->changeColumn('react_users', 'mediumblob')->nullable();
                });
            }
            catch(\InvalidArgumentException $e) {
                \XF::repository('ThemeHouse\Reactions:Setup')->setupColumnsForAddOn('XFMG');
            }
        }
    }

    public function upgrade1001392Step1()
    {
        if (!empty($this->app->registry()['addOns']['XFMG'])) {
            $this->schemaManager()->alterTable('xf_mg_album', function (Alter $table) {
                $table->addColumn('react_users', 'blob')->nullable();
            });
        }
    }

    public function upgrade1001392Step2()
    {
        if (!empty($this->app->registry()['addOns']['XFMG'])) {
            $this->db()->rawQuery("UPDATE xf_th_reaction SET react_handler = CONCAT(react_handler, ',xfmg_album')");
        }
    }

    /**
     * @param $previousVersion
     * @param array $stateChanges
     * @throws \XF\PrintableException
     */
    public function postUpgrade($previousVersion, array &$stateChanges)
    {
        $this->addNewContentTypesToExistingReactions($previousVersion);
        $this->applyDefaultWidgets($previousVersion);

        /** @noinspection PhpUndefinedMethodInspection */
        $this->app->repository('ThemeHouse\Reactions:Reaction')->rebuildReactionCache();
    }

    /**
     * @param $previousVersion
     * @throws \XF\PrintableException
     */
    protected function addNewContentTypesToExistingReactions($previousVersion)
    {
        $newContentTypes = [];

        if ($previousVersion < 1000711) {
            $newContentTypes[] = 'resource_update';
            $newContentTypes[] = 'xfmg_media';
        }

        if (!empty($newContentTypes)) {
            foreach (\XF::finder('ThemeHouse\Reactions:Reaction') as $reaction) {
                /** @var \ThemeHouse\Reactions\Entity\Reaction $reaction */
                $reactHandler = $reaction->react_handler;
                foreach ($newContentTypes as $contentType) {
                    if (in_array($contentType, $reactHandler)) {
                        continue;
                    }

                    $reactHandler[] = $contentType;
                }

                $reaction->set('react_handler', $reactHandler);
                $reaction->save(false);
            }
        }
    }

    protected function applyDefaultWidgets($previousVersion = 0)
    {
        $widgets = [];

        if ($previousVersion < 1000711) {
            $widgets[] = [
                'key' => 'th_memberReact_reactions',
                'definition_id' => 'th_memberReact_reactions',
                'config' => [
                    'positions' => [
                        'member_view_sidebar' => 50,
                    ],
                ],
            ];
        }

        foreach ($widgets as $widget) {
            $title = '';
            if (!empty($widget['title'])) {
                $title = $widget['title'];
            }
            $this->createWidget($widget['key'], $widget['definition_id'], $widget['config'], $title);
        }

        if (empty($widgets)) {
            return false;
        }

        return true;
    }

    /**
     * Uninstall Functions
     */
    public function uninstallStep1()
    {
        $schemaManager = $this->db()->getSchemaManager();

        $schemaManager->dropTable('xf_th_reaction');
        $schemaManager->dropTable('xf_th_reaction_type');
        $schemaManager->dropTable('xf_th_reacted_content');
        $schemaManager->dropTable('xf_th_reaction_user_count');
        $schemaManager->dropTable('xf_th_reaction_content_count');
    }

    public function uninstallStep2()
    {
        $schemaManager = $this->db()->getSchemaManager();

        $schemaManager->alterTable('xf_thread', function (Alter $table) {
            $table->dropColumns(['first_react_users']);
        });
    }

    public function uninstallStep3()
    {
        $schemaManager = $this->db()->getSchemaManager();

        $schemaManager->alterTable('xf_post', function (Alter $table) {
            $table->dropColumns(['react_users']);
        });
    }

    public function uninstallStep4()
    {
        $schemaManager = $this->db()->getSchemaManager();

        $schemaManager->alterTable('xf_conversation_message', function (Alter $table) {
            $table->dropColumns(['react_users']);
        });
    }

    public function uninstallStep5()
    {
        $schemaManager = $this->db()->getSchemaManager();

        $schemaManager->alterTable('xf_conversation_master', function (Alter $table) {
            $table->dropColumns(['react_users']);
        });
    }

    public function uninstallStep6()
    {
        $schemaManager = $this->db()->getSchemaManager();

        $schemaManager->alterTable('xf_profile_post', function (Alter $table) {
            $table->dropColumns(['react_users']);
        });
    }

    public function uninstallStep7()
    {
        $schemaManager = $this->db()->getSchemaManager();

        $schemaManager->alterTable('xf_profile_post_comment', function (Alter $table) {
            $table->dropColumns(['react_users']);
        });
    }

    public function uninstallStep8()
    {
        $schemaManager = $this->db()->getSchemaManager();

        $schemaManager->alterTable('xf_user', function (Alter $table) {
            $table->dropColumns(['react_count']);
        });
    }

    public function uninstallStep9()
    {
        $schemaManager = $this->db()->getSchemaManager();

        try {
            if (!empty($this->app->registry()['addOns']['XFMG'])) {
                $schemaManager->alterTable('xf_mg_media_item', function (Alter $table) {
                    $table->dropColumns(['react_users']);
                });
                $schemaManager->alterTable('xf_mg_comment', function (Alter $table) {
                    $table->dropColumns(['react_users']);
                });
                $schemaManager->alterTable('xf_mg_album', function (Alter $table) {
                    $table->dropColumns(['react_users']);
                });
            }
        } catch (\Exception $e) {
        }
    }

    public function uninstallStep10()
    {
        $schemaManager = $this->db()->getSchemaManager();

        try {
            if (!empty($this->app->registry()['addOns']['XFRM'])) {
                $schemaManager->alterTable('xf_rm_resource_update', function (Alter $table) {
                    $table->dropColumns(['react_users']);
                });
            }
        } catch (\Exception $e) {
        }
    }

    public function uninstallStep11()
    {
        \XF::registry()->delete(['reactions', 'reactionTypes']);
    }
}