<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\UserLog;

use XF\Entity\User;
use XF\Mvc\Entity\Entity;

use SV\UserEssentials\Entity\UserLog;

/**
 * A logger for user actions.
 */
class Logger
{
    /**
     * @var array
     */
    protected $types;

    /**
     * @var array
     */
    protected $handlers = [];

    /**
     * @param array $types
     */
    public function __construct(array $types)
    {
        $this->types = $types;
    }

    /**
     * @param string $type
     * @param Entity $content
     * @param bool   $throw
     * @param User   $actor
     * @return array
     */
    public function logChanges(
        $type,
        Entity $content,
        $throw = true,
        User $actor = null
    )
    {
        $handler = $this->handler($type, $throw);
        if (!$handler)
        {
            return [];
        }

        $actor = $actor ?: \XF::visitor();
        if (!$handler->isLoggableUser($actor))
        {
            return [];
        }

        $logs = [];
        $potentials = [];

        $changedValues = $content->getNewValues();
        if ($changedValues)
        {
            foreach ($changedValues as $field => $value)
            {
                $oldValue = $content->getExistingValue($field);
                if ($value !== $oldValue)
                {
                    $potentials[$field] = ['new' => $value, 'old' => $oldValue];
                }
            }
        }
        else
        {
            foreach ($content->getPreviousValues() as $field => $oldValue)
            {
                $value = $content->getValue($field);
                if ($value !== $oldValue)
                {
                    $potentials[$field] = ['new' => $value, 'old' => $oldValue];
                }
            }
        }

        foreach ($potentials as $field => $values)
        {
            $success = $handler->logChange(
                $content,
                $field,
                $values['new'],
                $values['old'],
                $actor
            );
            if ($success)
            {
                $logs[$field] = $success;
            }
        }

        return $logs;
    }

    /**
     * @param string $type
     * @param mixed  $content
     * @param string $field
     * @param bool   $throw
     * @param mixed  $newValue
     * @param mixed  $oldValue
     * @param User   $actor
     * @return UserLog|array|null
     * @throws \InvalidArgumentException If content is not a valid entity
     */
    public function logChange(
        $type,
        $content,
        $field,
        $throw = true,
        $newValue = null,
        $oldValue = null,
        User $actor = null
    )
    {
        $handler = $this->handler($type, $throw);
        if (!$handler)
        {
            return [];
        }

        if (!($content instanceof Entity))
        {
            $content = $handler->getContent($content);
        }
        if (!($content instanceof Entity))
        {
            if ($throw)
            {
                throw new \InvalidArgumentException(
                    'Content must be an entity or an ID of a valid entity'
                );
            }
            else
            {
                return [];
            }
        }

        $actor = $actor ?: \XF::visitor();
        if (!$handler->isLoggableUser($actor))
        {
            return [];
        }

        if ($newValue === null)
        {
            $newValue = $content->getValue($field);
        }
        if ($oldValue === null)
        {
            $oldValue = $content->getExistingValue($field);
        }

        if ($newValue === $oldValue)
        {
            return null;
        }

        return $handler->logChange(
            $content,
            $field,
            $newValue,
            $oldValue,
            $actor
        );
    }

    /**
     * @param string $type
     * @param mixed  $content
     * @param string $action
     * @param array  $params
     * @param bool   $throw
     * @param User   $actor
     * @return UserLog|array|null
     * @throws \InvalidArgumentException If content is not a valid entity
     */
    public function log(
        $type,
        $content,
        $action,
        array $params = [],
        $throw = true,
        User $actor = null
    )
    {
        $handler = $this->handler($type, $throw);
        if (!$handler)
        {
            return [];
        }

        if (!($content instanceof Entity))
        {
            $content = $handler->getContent($content);
        }
        if (!($content instanceof Entity))
        {
            if ($throw)
            {
                throw new \InvalidArgumentException(
                    'Content must be an entity or an ID of a valid entity'
                );
            }
            else
            {
                return [];
            }
        }

        $actor = $actor ?: \XF::visitor();
        if (!$handler->isLoggableUser($actor))
        {
            return [];
        }

        return $handler->log($content, $action, $params, $actor);
    }

    /**
     * @param UserLog $log
     * @return string
     */
    public function getContentTitle(UserLog $log)
    {
        return $this->handler($log->content_type)->getContentTitle($log);
    }

    /**
     * @param UserLog $log
     * @return string
     */
    public function getAction(UserLog $log)
    {
        return $this->handler($log->content_type)->getAction($log);
    }

    /**
     * @param $type
     * @return bool
     */
    public function isValidContentType($type)
    {
        return isset($this->types[$type]) && class_exists($this->types[$type]);
    }

    /**
     * @param string $type
     * @param bool   $throw
     * @return \SV\UserEssentials\UserLog\AbstractHandler | null
     * @throws \InvalidArgumentException If log handler is unknown
     */
    public function handler($type, $throw = true)
    {
        if (isset($this->handlers[$type]))
        {
            return $this->handlers[$type];
        }

        if (!isset($this->types[$type]))
        {
            if ($throw)
            {
                throw new \InvalidArgumentException(
                    "Unknown user log handler type '$type'"
                );
            }
            else
            {
                return null;
            }
        }

        $class = $this->types[$type];
        if (class_exists($class))
        {
            $class = \XF::extendClass($class);
        }

        $this->handlers[$type] = new $class($type);

        return $this->handlers[$type];
    }
}
