<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\UserLog;

use XF\Entity\User as UserEntity;
use XF\Mvc\Entity\Entity;

use SV\UserEssentials\Entity\UserLog;
use XF\Util\Ip;

/**
 * The abstract user log handler.
 */
abstract class AbstractHandler
{
    /**
     * @var string
     */
    protected $contentType;

    /**
     * @param string $contentType
     */
    public function __construct($contentType)
    {
        $this->contentType = $contentType;
    }

    /**
     * @param Entity $content
     * @param string $field
     * @param string $newValue
     * @param string $oldValue
     * @return string|bool|array
     */
    abstract protected function getLogActionForChange(
        Entity $content,
        $field,
        $newValue,
        $oldValue
    );

    /**
     * @param UserLog $log
     * @param Entity  $content
     */
    abstract protected function setupLogEntityContent(
        UserLog $log,
        Entity $content
    );

    /**
     * @param Entity     $content
     * @param string     $action
     * @param UserEntity $actor
     * @return bool
     */
    public function isLoggable(
        /** @noinspection PhpUnusedParameterInspection */
        Entity $content,
        $action,
        UserEntity $actor
    )
    {
        return true;
    }

    /**
     * @param UserEntity $actor
     * @return bool
     */
    public function isLoggableUser(UserEntity $actor)
    {
        return $actor->user_id ? true : false;
    }

    /**
     * @param Entity     $content
     * @param string     $field
     * @param string     $newValue
     * @param string     $oldValue
     * @param UserEntity $actor
     * @return UserLog|null
     */
    public function logChange(
        Entity $content,
        $field,
        $newValue,
        $oldValue,
        UserEntity $actor
    )
    {
        $action = $this->getLogActionForChange(
            $content,
            $field,
            $newValue,
            $oldValue
        );
        if (!$action)
        {
            return null;
        }

        if (is_array($action))
        {
            list($action, $params) = $action;
        }
        else
        {
            $params = [];
        }

        return $this->log($content, $action, $params, $actor);
    }

    /**
     * @param Entity     $content
     * @param string     $action
     * @param array      $params
     * @param UserEntity $actor
     * @return UserLog|null
     * @throws \InvalidArgumentException When entity has a complex key
     */
    public function log(
        Entity $content,
        $action,
        array $params,
        UserEntity $actor
    )
    {
        if (!$this->isLoggable($content, $action, $actor))
        {
            return null;
        }

        /** @var UserLog $log */
        $log = \XF::em()->create('SV\UserEssentials:UserLog');
        $log->content_type = $this->contentType;
        $id = $content->getIdentifierValues();
        if (!$id || count($id) != 1)
        {
            throw new \InvalidArgumentException(
                "Entity does not have an ID or does not have a simple key"
            );
        }
        $log->content_id = intval(reset($id));

        $this->setupLogEntityActor($log, $actor);
        $this->setupLogEntityContent($log, $content);

        $log->action = $action;
        $log->action_params = $params;
        $log->save();

        return $log;
    }

    /**
     * @param UserLog    $log
     * @param UserEntity $actor
     */
    protected function setupLogEntityActor(UserLog $log, UserEntity $actor)
    {
        $log->user_id = $actor->user_id;

        if ($actor->user_id === \XF::visitor()->user_id)
        {
            $log->ip_address = Ip::convertIpStringToBinary(
                \XF::app()->request()->getIp()
            );
        }
    }

    /**
     * @param UserLog $log
     * @return string
     */
    public function getContentTitle(UserLog $log)
    {
        return \XF::app()->stringFormatter()->censorText($log->content_title_);
    }

    /**
     * @param UserLog $log
     * @return string
     */
    public function getAction(UserLog $log)
    {
        return \XF::phrase(
            $this->getActionPhraseName($log),
            $this->getActionPhraseParams($log)
        );
    }

    /**
     * @param UserLog $log
     * @return string
     */
    public function getActionPhraseName(UserLog $log)
    {
        $contentType = $log->content_type;
        $action = $log->action;

        return "mod_log.{$contentType}_{$action}";
    }

    /**
     * @param UserLog $log
     * @return array
     */
    protected function getActionPhraseParams(UserLog $log)
    {
        return $log->action_params;
    }

    /**
     * @return array
     */
    public function getEntityWith()
    {
        return [];
    }

    /**
     * @param int $id
     * @return Entity
     */
    public function getContent($id)
    {
        return \XF::app()->findByContentType(
            $this->contentType,
            $id,
            $this->getEntityWith()
        );
    }

    /**
     * @return string
     */
    public function getContentType()
    {
        return $this->contentType;
    }
}
