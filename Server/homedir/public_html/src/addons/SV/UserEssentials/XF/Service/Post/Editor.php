<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\XF\Service\Post;

/**
 * Extends \XF\Service\Post\Editor
 */
class Editor extends XFCP_Editor
{
    /**
     * Send notifications to newly mentioned users.
     */
    public function sendNotifications()
    {
        if ($this->post->isVisible()) {
            /** @var \SV\UserEssentials\Service\MentionableInterface $preparer */
            $preparer = $this->postPreparer;
            /** @var \SV\UserEssentials\XF\Service\Post\Notifier $notifier */
            $notifier = $this->service('XF:Post\Notifier', $this->post, 'reply');
            $notifier->setOnlySendMentions(true);
            $notifier->setMentionedUserIds($preparer->getNewContentMentions(
                ['m', 'mgu']
            ));
            $notifier->setQuotedUserIds($preparer->getNewContentMentions('q'));
            $notifier->notifyAndEnqueue(0.1);
        }
    }
}
