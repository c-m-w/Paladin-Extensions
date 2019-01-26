<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\XF\Pub\Controller;

use XF\Entity\Thread as ThreadEntity;
use XF\Mvc\ParameterBag;

/*
 * Extends \XF\Pub\Controller\Thread
 */
class Thread extends XFCP_Thread
{
    /**
     * @param ParameterBag $params
     *
     * @return \XF\Mvc\Reply\AbstractReply
     */
    public function actionIndex(ParameterBag $params)
    {
        $reply = parent::actionIndex($params);

        if (\XF::options()->svDisplayMiniAvatars && $reply instanceof \XF\Mvc\Reply\View) {
            $posts = $reply->getParam('posts');
            if ($posts->count()) {
                /** @var \SV\UserEssentials\Repository\ContentMentions $mentionsRepo */
                $mentionsRepo = $this->repository('SV\UserEssentials:ContentMentions');
                $mentionsRepo->getMentionEntities('m', $posts);
                $mentionsRepo->getMentionEntities('mg', $posts);
            }
        }

        return $reply;
    }

    protected function finalizeThreadReply(\XF\Service\Thread\Replier $replier)
    {
        if (\XF::options()->svDisplayMiniAvatars)
        {
            /** @var \SV\UserEssentials\Repository\ContentMentions $mentionsRepo */
            $mentionsRepo = $this->repository('SV\UserEssentials:ContentMentions');
            $mentionsRepo->getMentionEntities('m', [$replier->getPost()]);
            $mentionsRepo->getMentionEntities('mg', [$replier->getPost()]);
        }

        parent::finalizeThreadReply($replier);
    }

    protected function getNewPostsReply(\XF\Entity\Thread $thread, $lastDate)
    {
        $view = parent::getNewPostsReply($thread, $lastDate);
        if (\XF::options()->svDisplayMiniAvatars && ($posts = $view->getParam('posts')))
        {
            /** @var \SV\UserEssentials\Repository\ContentMentions $mentionsRepo */
            $mentionsRepo = $this->repository('SV\UserEssentials:ContentMentions');
            $mentionsRepo->getMentionEntities('m', $posts);
            $mentionsRepo->getMentionEntities('mg', $posts);
        }

        return $view;
    }

    /**
     * @return array
     */
    protected function getThreadViewExtraWith()
    {
        $extraWith = parent::getThreadViewExtraWith();

        if (\XF::visitor()->user_id)
        {
            $extraWith[] = 'ThreadPermissions';
        }

        return $extraWith;
    }

    /**
     * @param ThreadEntity $thread
     * @return \XF\Service\Thread\Editor
     */
    protected function setupThreadEdit(ThreadEntity $thread)
    {
        /** @var \SV\UserEssentials\XF\Entity\Thread $thread */
        /** @var \SV\UserEssentials\XF\Service\Thread\Editor $editor */
        $editor = parent::setupThreadEdit($thread);

        if (
            $thread->canEditLockPermissions()
            || $thread->canEditReplyBanPermissions()
        )
        {
            $threadPermissions = [];
            if ($thread->canEditLockPermissions())
            {
                $threadPermissions['allowLockByUser'] = $this->filter(
                    'allow_user_lock',
                    'bool'
                );
                $threadPermissions['allowUnlockByUser'] = $this->filter(
                    'allow_user_unlock',
                    'bool'
                );
            }
            if ($thread->canEditReplyBanPermissions())
            {
                $threadPermissions['replyBanInOwnThread'] = $this->filter(
                    'allow_user_reply_ban',
                    'bool'
                );
            }

            $editor->setThreadPermissions($threadPermissions);
        }

        return $editor;
    }
}
