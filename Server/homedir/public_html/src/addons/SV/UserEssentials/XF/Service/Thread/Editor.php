<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\XF\Service\Thread;

/**
 * Extends \XF\Service\Thread\Editor
 */
class Editor extends XFCP_Editor
{
    /**
     * @var \SV\UserEssentials\Entity\ThreadPermissions
     */
    protected $threadPermissions;

    /**
     * @return \SV\UserEssentials\Entity\ThreadPermissions
     */
    public function getThreadPermissions()
    {
        if ($this->threadPermissions === null)
        {
            $this->threadPermissions = $this->thread->getRelationOrDefault(
                'ThreadPermissions'
            );
            $this->threadPermissions->user_id = \XF::visitor()->user_id;
        }

        return $this->threadPermissions;
    }

    /**
     * @param array $permissions
     */
    public function setThreadPermissions(array $permissions)
    {
        $threadPermissions = $this->getThreadPermissions();
        $threadPermissions->bulkSet($permissions);
    }

    public function setTitle($title)
    {
        /** @var \SV\UserEssentials\XF\Entity\Thread $thread */
        $thread = $this->thread;
        if ($thread->canEditTitle()) {
            parent::setTitle($title);
        }
    }

    public function setPrefix($prefixId)
    {
        /** @var \SV\UserEssentials\XF\Entity\Thread $thread */
        $thread = $this->thread;
        if ($thread->canEditTitle()) {
            parent::setPrefix($prefixId);
        }
    }
}
