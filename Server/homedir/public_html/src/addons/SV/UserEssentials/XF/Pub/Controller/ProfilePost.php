<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\XF\Pub\Controller;

/**
 * Extends \XF\Pub\Controller\ProfilePost
 */
class ProfilePost extends XFCP_ProfilePost
{
    /**
     * @param \XF\Service\ProfilePost\Editor $editor
     */
    protected function finalizeEdit(\XF\Service\ProfilePost\Editor $editor)
    {
        /** @var \SV\UserEssentials\XF\Service\ProfilePost\Editor $editor */
        $editor->sendNotifications();
        parent::finalizeEdit($editor);
    }

    /**
     * @param \XF\Service\ProfilePostComment\Editor $editor
     */
    protected function finalizeCommentEdit(
        \XF\Service\ProfilePostComment\Editor $editor
    ) {
        /** @var \SV\UserEssentials\XF\Service\ProfilePostComment\Editor $editor */
        $editor->sendNotifications();
        parent::finalizeCommentEdit($editor);
    }
}
