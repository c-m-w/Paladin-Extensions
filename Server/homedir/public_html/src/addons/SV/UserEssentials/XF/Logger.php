<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\XF;

use XF\Mvc\Entity\Entity;

use SV\UserEssentials\Entity\UserLog;
use SV\UserEssentials\UserLog\Logger as UserLogger;

/**
 * Extends \XF\Logger
 */
class Logger extends XFCP_Logger
{
    /**
     * @var UserLogger
     */
    protected $userLogger;

    /**
     * @return UserLogger
     */
    public function userLogger()
    {
        if (!$this->userLogger)
        {
            $class = 'SV\UserEssentials\UserLog\Logger';
            $class = $this->app->extendClass($class);

            $this->userLogger = new $class(
                $this->app->getContentTypeField('sv_user_log_handler_class')
            );
        }

        return $this->userLogger;
    }

    /**
     * @param string $type
     * @param mixed  $content
     * @param string $action
     * @param array  $params
     * @param bool   $throw
     * @return UserLog|array|null
     */
    public function logUserAction(
        $type,
        $content,
        $action,
        array $params = [],
        $throw = true
    )
    {
        return $this->userLogger()->log(
            $type,
            $content,
            $action,
            $params,
            $throw
        );
    }

    /**
     * @param string $type
     * @param mixed  $content
     * @param string $field
     * @param bool   $throw
     * @return UserLog|null
     */
    public function logUserChange($type, $content, $field, $throw = true)
    {
        return $this->userLogger()->logChange($type, $content, $field, $throw);
    }

    /**
     * @param string $type
     * @param Entity $content
     * @param bool   $throw
     * @return array
     */
    public function logUserChanges($type, Entity $content, $throw = true)
    {
        return $this->userLogger()->logChanges($type, $content, $throw);
    }
}
