<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\XF\Pub\Controller;

/**
 * Extends \XF\Pub\Controller\Post
 */
class Post extends XFCP_Post
{
    /**
     * @param \XF\Service\Post\Editor        $editor
     * @param \XF\Service\Thread\Editor|null $threadEditor
     */
    protected function finalizePostEdit(
        \XF\Service\Post\Editor $editor,
        \XF\Service\Thread\Editor $threadEditor = null
    ) {
        /** @var \SV\UserEssentials\XF\Service\Post\Editor $editor */
        $editor->sendNotifications();
        parent::finalizePostEdit($editor, $threadEditor);
    }
}
