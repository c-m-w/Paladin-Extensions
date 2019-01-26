<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\XF\Service\ProfilePostComment;

/**
 * Extends \XF\Service\ProfilePostComment\Editor
 */
class Editor extends XFCP_Editor
{
    /**
     * Send notifications to newly mentioned users.
     */
    public function sendNotifications()
    {
        if ($this->comment->isVisible()) {
            /** @var \SV\UserEssentials\Service\MentionableInterface $preparer */
            $preparer = $this->preparer;
            /** @var \SV\UserEssentials\XF\Service\ProfilePostComment\Notifier $notifier */
            $notifier = $this->service(
                'XF:ProfilePostComment\Notifier',
                $this->comment
            );
            $notifier->setNotifyProfileOwner([]);
            $notifier->setNotifyProfilePostAuthor([]);
            $notifier->setNotifyMentioned($preparer->getNewContentMentions(
                ['m', 'mgu']
            ));
            $notifier->notify();
        }
    }
}
