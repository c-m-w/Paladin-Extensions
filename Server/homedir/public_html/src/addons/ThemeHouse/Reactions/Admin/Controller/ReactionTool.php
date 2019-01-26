<?php

namespace ThemeHouse\Reactions\Admin\Controller;

use XF\Http\Request;
use XF\Mvc\FormAction;
use XF\Mvc\ParameterBag;

class ReactionTool extends \XF\Admin\Controller\AbstractController
{
    protected function preDispatchController($action, ParameterBag $params)
    {
        $this->assertAdminPermission('thReactions');
    }

    public function actionIndex()
    {
        $viewParams = [
            'success' => $this->filter('success', 'bool')
        ];

        return $this->view('ThemeHouse\Reactions:ReactionTool\Listing', 'th_reaction_tool_list_reactions', $viewParams);
    }

    public function actionAddon()
    {
        $schemaManager = \XF::db()->getSchemaManager();

        if (!empty($this->app->registry()['addOns']['XFRM'])) {
            $schemaManager->alterTable('xf_rm_resource_update', function(\XF\Db\Schema\Alter $table) {
                $table->addColumn('react_users', 'blob')->nullable();
            });
        }

        if (!empty($this->app->registry()['addOns']['XFMG'])) {
            $schemaManager->alterTable('xf_mg_media_item', function(\XF\Db\Schema\Alter $table) {
                $table->addColumn('react_users', 'blob')->nullable();
            });
        }

        return $this->redirect($this->buildLink('reaction-tools', null, ['success' => 1]));
    }
}