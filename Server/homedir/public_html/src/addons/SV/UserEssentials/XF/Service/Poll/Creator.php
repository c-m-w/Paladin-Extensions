<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\XF\Service\Poll;

use SV\UserEssentials\XF\Logger;

/**
 * Extends \XF\Service\Poll\Creator
 */
class Creator extends XFCP_Creator
{
    protected function _save()
    {
        $poll = parent::_save();

        $content = $poll->Content;
        $contentType = $poll->content_type;
        if (
            isset($content->User)
            && ($content->User->user_id == \XF::visitor()->user_id)
        )
        {
            /** @var Logger $logger */
            $logger = $this->app->logger();
            $logger->logUserAction($contentType, $content, 'poll_create');
        }

        return $poll;
    }
}
