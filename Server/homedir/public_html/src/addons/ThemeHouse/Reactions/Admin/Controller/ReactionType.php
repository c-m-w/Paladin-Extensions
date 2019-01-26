<?php

namespace ThemeHouse\Reactions\Admin\Controller;

use XF\Admin\Controller\AbstractController;
use XF\Http\Request;
use XF\Mvc\FormAction;
use XF\Mvc\ParameterBag;

class ReactionType extends AbstractController
{
    /**
     * @param $action
     * @param ParameterBag $params
     * @throws \XF\Mvc\Reply\Exception
     */
    protected function preDispatchController($action, ParameterBag $params)
    {
        $this->assertAdminPermission('thReactions');
    }

    public function actionIndex()
    {
        $reactionTypes = $this->getReactionTypeRepo()->getReactionTypeList();

        $viewParams = [
            'reactionTypes' => $reactionTypes,
        ];

        return $this->view('ThemeHouse\Reactions:ReactionType\Listing', 'th_reaction_type_list_reactions', $viewParams);
    }

    public function reactionTypeAddEdit(\ThemeHouse\Reactions\Entity\ReactionType $reactionType)
    {
        $viewParams = [
            'reactionType' => $reactionType,
        ];

        return $this->view('ThemeHouse\Reactions:ReactionType\Edit', 'th_reaction_type_edit_reactions', $viewParams);
    }

    /**
     * @param ParameterBag $params
     * @return \XF\Mvc\Reply\View
     * @throws \XF\Mvc\Reply\Exception
     */
    public function actionEdit(ParameterBag $params)
    {
        $reactionType = $this->assertReactionTypeExists($params['reaction_type_id']);
        return $this->reactionTypeAddEdit($reactionType);
    }

    public function actionAdd()
    {
        /** @var \ThemeHouse\Reactions\Entity\ReactionType $reactionType */
        $reactionType = $this->em()->create('ThemeHouse\Reactions:ReactionType');

        return $this->reactionTypeAddEdit($reactionType);
    }

    protected function reactionTypeSaveProcess(\ThemeHouse\Reactions\Entity\ReactionType $reactionType)
    {
        $entityInput = $this->filter([
            'reaction_type_id' => 'str',
            'title' => 'str',
            'color' => 'str',
            'display_order' => 'uint',
            // 'notable_member' => 'bool'
        ]);

        $form = $this->formAction();
        $form->basicEntitySave($reactionType, $entityInput);

        return $form;
    }

    /**
     * @param ParameterBag $params
     * @return \XF\Mvc\Reply\Redirect
     * @throws \XF\Mvc\Reply\Exception
     * @throws \XF\PrintableException
     */
    public function actionSave(ParameterBag $params)
    {
        $this->assertPostOnly();

        if ($params['reaction_type_id']) {
            $reactionType = $this->assertReactionTypeExists($params['reaction_type_id']);
        } else {
            $reactionType = $this->em()->create('ThemeHouse\Reactions:ReactionType');
        }

        $this->reactionTypeSaveProcess($reactionType)->run();

        return $this->redirect($this->buildLink('reaction-types'));
    }

    /**
     * @param ParameterBag $params
     * @return \XF\Mvc\Reply\Error|\XF\Mvc\Reply\Redirect|\XF\Mvc\Reply\View
     * @throws \XF\PrintableException
     * @throws \XF\Mvc\Reply\Exception
     */
    public function actionDelete(ParameterBag $params)
    {
        $reactionType = $this->assertReactionTypeExists($params['reaction_type_id']);
        if (!$reactionType->canDeleteReactionType()) {
            return $this->error(\XF::phrase('th_reactions_exist_using_reaction_type_reactions'));
        }

        if ($this->isPost()) {
            $reactionType->delete();
            return $this->redirect($this->buildLink('reaction-types'));
        } else {
            $viewParams = [
                'reactionType' => $reactionType
            ];

            return $this->view('ThemeHouse\Reactions:ReactionType\Delete', 'th_reaction_type_delete_reactions', $viewParams);
        }
    }

    /**
     * @param string $id
     * @param array|string|null $with
     * @param null|string $phraseKey
     *
     * @return \ThemeHouse\Reactions\Entity\ReactionType
     * @throws \XF\Mvc\Reply\Exception
     */
    protected function assertReactionTypeExists($id, $with = null, $phraseKey = null)
    {
        /** @noinspection PhpIncompatibleReturnTypeInspection */
        return $this->assertRecordExists('ThemeHouse\Reactions:ReactionType', $id, $with, $phraseKey);
    }

    /**
     * @return \ThemeHouse\Reactions\Repository\ReactionType
     */
    protected function getReactionTypeRepo()
    {
        /** @noinspection PhpIncompatibleReturnTypeInspection */
        return $this->repository('ThemeHouse\Reactions:ReactionType');
    }
}