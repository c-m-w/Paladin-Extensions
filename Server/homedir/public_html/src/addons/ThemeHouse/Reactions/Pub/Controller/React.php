<?php

namespace ThemeHouse\Reactions\Pub\Controller;

use XF\Mvc\ParameterBag;
use XF\Mvc\FormAction;
use XF\Mvc\Reply\View;
use XF\Mvc\Entity\Entity;
use ThemeHouse\Reactions\Entity\ReactedContent;
use XF\Pub\Controller\AbstractController;

/**
 * Class React
 * @package ThemeHouse\Reactions\Pub\Controller
 */
class React extends AbstractController
{

    /**
     * @param $action
     * @param null $floodingLimit
     * @throws \XF\Mvc\Reply\Exception
     */
    public function assertNotFlooding($action, $floodingLimit = null)
    {
        $visitor = \XF::visitor();

        /** @var \XF\Service\FloodCheck $floodChecker */
        $floodChecker = $this->service('XF:FloodCheck');
        $timeRemaining = $floodChecker->checkFlooding($action, $visitor->user_id, $floodingLimit);
        if ($timeRemaining)
        {
            throw $this->exception($this->responseFlooding($timeRemaining));
        }
    }

    /**
     * @param ParameterBag $params
     * @return \XF\Mvc\Reply\Redirect|View
     * @throws \XF\Mvc\Reply\Exception
     */
    public function actionReact(ParameterBag $params)
    {
        $this->assertNotFlooding('react', 3);

        /** @var \ThemeHouse\Reactions\Repository\ReactedContent $reactRepo */
        $reactRepo = $this->repository('ThemeHouse\Reactions:ReactedContent');

        /** @noinspection PhpUndefinedFieldInspection */
        $entity = $this->buildContentEntity($params->content_id, $params->content_type);
        /** @var \ThemeHouse\Reactions\Entity\ReactedContent $react */
        /** @noinspection PhpUndefinedFieldInspection */
        $react = $reactRepo->buildReactedContent($entity, $params->reaction_id);

        $this->assertReactionPermissions($entity, $react, ['canReact']);

        $this->verifyReactionId($entity, $react);

        /** @var \ThemeHouse\Reactions\ControllerPlugin\React $reactPlugin */
        $reactPlugin = $this->plugin('ThemeHouse\Reactions:React');
        return $reactPlugin->actionToggleReact($entity, $react, 'insert');
    }

    /**
     * @param ParameterBag $params
     * @return \XF\Mvc\Reply\Redirect|View
     * @throws \XF\Mvc\Reply\Exception
     */
    public function actionUnreact(ParameterBag $params)
    {
        /** @var \ThemeHouse\Reactions\Entity\ReactedContent $react */
        /** @noinspection PhpUndefinedFieldInspection */
        $react = \XF::finder('ThemeHouse\Reactions:ReactedContent')
            ->where('react_id', $params->react_id)
            ->fetchOne();

        if (!$react) {
            throw $this->exception($this->notFound("Provided react ID not found"));
        }

        /** @noinspection PhpUndefinedFieldInspection */
        $entity = $this->buildContentEntity($react->content_id, $react->content_type);

        $this->assertReactionPermissions($entity, $react, ['canUnreact']);

        /** @var \ThemeHouse\Reactions\ControllerPlugin\React $reactPlugin */
        $reactPlugin = $this->plugin('ThemeHouse\Reactions:React');
        return $reactPlugin->actionToggleReact($entity, $react, 'delete');
    }

    /**
     * @param ParameterBag $params
     * @return \XF\Mvc\Reply\Redirect|View
     * @throws \XF\Mvc\Reply\Exception
     */
    public function actionUnreacts(ParameterBag $params)
    {
        /** @var \ThemeHouse\Reactions\Repository\ReactedContent $reactRepo */
        $reactRepo = $this->repository('ThemeHouse\Reactions:ReactedContent');

        /** @noinspection PhpUndefinedFieldInspection */
        $entity = $this->buildContentEntity($params->content_id, $params->content_type);
        /** @var \ThemeHouse\Reactions\Entity\ReactedContent $react */
        /** @noinspection PhpUndefinedFieldInspection */
        $react = $reactRepo->buildReactedContent($entity, $params->reaction_id);

        $this->assertReactionPermissions($entity, $react, ['canUnreact']);

        /** @var \ThemeHouse\Reactions\ControllerPlugin\React $reactPlugin */
        $reactPlugin = $this->plugin('ThemeHouse\Reactions:React');
        return $reactPlugin->actionToggleReact($entity, $react, 'delete');
    }

    /**
     * @param ParameterBag $params
     * @return \XF\Mvc\Reply\Message|View
     * @throws \XF\Mvc\Reply\Exception
     */
    public function actionList(ParameterBag $params)
    {
        /** @var \ThemeHouse\Reactions\Repository\ReactedContent $reactRepo */
        $reactRepo = $this->repository('ThemeHouse\Reactions:ReactedContent');

        /** @noinspection PhpUndefinedFieldInspection */
        $entity = $this->buildContentEntity($params->content_id, $params->content_type);
        /** @var \ThemeHouse\Reactions\Entity\ReactedContent $react */
        $react = $reactRepo->buildReactedContent($entity);

        $this->assertReactionPermissions($entity, $react, ['canViewReactsList']);

        /** @var \ThemeHouse\Reactions\ControllerPlugin\React $reactPlugin */
        $reactPlugin = $this->plugin('ThemeHouse\Reactions:React');

        return $reactPlugin->actionList($entity);
    }

    /**
     * @param ParameterBag $params
     * @return \XF\Mvc\Reply\Message|View
     * @throws \XF\Mvc\Reply\Exception
     */
    public function actionModify(ParameterBag $params)
    {
        /** @var \ThemeHouse\Reactions\Repository\ReactedContent $reactRepo */
        $reactRepo = $this->repository('ThemeHouse\Reactions:ReactedContent');

        /** @noinspection PhpUndefinedFieldInspection */
        $entity = $this->buildContentEntity($params->content_id, $params->content_type);
        /** @var \ThemeHouse\Reactions\Entity\ReactedContent $react */
        $react = $reactRepo->buildReactedContent($entity);

        $this->assertReactionPermissions($entity, $react, ['canUnreact']);

        /** @var \ThemeHouse\Reactions\ControllerPlugin\React $reactPlugin */
        $reactPlugin = $this->plugin('ThemeHouse\Reactions:React');

        /** @noinspection PhpMethodParametersCountMismatchInspection */
        return $reactPlugin->actionModify($entity, $react);
    }

    /**
     * @param Entity $entity
     * @param ReactedContent $react
     * @throws \XF\Mvc\Reply\Exception
     */
    protected function verifyReactionId(Entity $entity, ReactedContent &$react)
    {
        /** @var \ThemeHouse\Reactions\React\AbstractHandler $reactHandler */
        /** @noinspection PhpUndefinedMethodInspection */
        $reactHandler = $this->repository('ThemeHouse\Reactions:ReactHandler')->getReactHandlerByEntity($entity, true);
        /** @noinspection PhpUndefinedFieldInspection */
        $reaction = $reactHandler->getReactionById($react->reaction_id);

        if ($reaction && $reaction['random']) {
            $reactions = $reactHandler->buildValidReactionsList('react');
            $validReactions = [];
            foreach ($reactions as $tempReactionId => $reaction) {
                if ($reaction['random']) {
                    continue;
                }

                if ($reactHandler->canReactContent($entity, $react)) {
                    $validReactions[] = $tempReactionId;
                }
            }

            if (empty($validReactions)) {
                throw $this->exception($this->notFound(\XF::phraseDeferred('th_random_reaction_not_found_reactions')));
            }

            /** @noinspection PhpUndefinedMethodInspection */
            $this->plugin('ThemeHouse\Reactions:React')->actionToggleReact($entity, $react, 'insert');
            $react->reaction_id = $validReactions[array_rand($validReactions)];
        }
    }

    /**
     * @param $contentId
     * @param $contentType
     * @return mixed
     * @throws \XF\Mvc\Reply\Exception
     */
    protected function buildContentEntity($contentId, $contentType)
    {
        if (!$contentType) {
            throw $this->exception($this->notFound("Provided entity must defined a content type in its structure"));
        }

        /** @var \ThemeHouse\Reactions\React\AbstractHandler $reactHandler */
        /** @noinspection PhpUndefinedMethodInspection */
        $reactHandler = $this->repository('ThemeHouse\Reactions:ReactHandler')->getReactHandlerByType($contentType,
            true);

        $entity = $reactHandler->getContent($contentId);
        if (!$entity) {
            throw $this->exception($this->notFound("No entity found for '$contentType' with ID $contentId"));
        }

        return $entity;
    }

    /**
     * @param Entity $entity
     * @param ReactedContent $react
     * @param array $checkPermissions
     * @throws \XF\Mvc\Reply\Exception
     */
    protected function assertReactionPermissions(Entity $entity, ReactedContent $react, array $checkPermissions = [])
    {
        /** @var \ThemeHouse\Reactions\React\AbstractHandler $reactHandler */
        /** @noinspection PhpUndefinedMethodInspection */
        $reactHandler = $this->repository('ThemeHouse\Reactions:ReactHandler')->getReactHandlerByEntity($entity, true);

        if (!$reactHandler->getStatus()) {
            throw $this->exception($this->noPermission(\XF::phraseDeferred('th_x_content_type_not_enabled_reactions',
                ['contentType' => $reactHandler->getContentType()])));
        }

        if (!$reactHandler->canViewContent($entity, $react, $error)) {
            throw $this->exception($this->noPermission($error));
        }

        if (in_array('canReact', $checkPermissions)) {
            if (!$reactHandler->canReactContent($entity, $react, $error)) {
                throw $this->exception($this->noPermission($error));
            }
        }

        if (in_array('canUnreact', $checkPermissions)) {
            if (!$reactHandler->canUnreactContent($entity, $react, $error)) {
                throw $this->exception($this->noPermission($error));
            }
        }

        if (in_array('canViewReactsList', $checkPermissions)) {
            if (!$reactHandler->canViewReactsList($entity, $react, $error)) {
                throw $this->exception($this->noPermission($error));
            }
        }
    }

    protected function getReactedContentRepo()
    {
        return $this->repository('ThemeHouse\Reactions:ReactedContent');
    }
}