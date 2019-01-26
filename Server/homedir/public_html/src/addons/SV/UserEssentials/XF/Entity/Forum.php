<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\XF\Entity;

/**
 * Extends \XF\Entity\Forum
 */
class Forum extends XFCP_Forum
{
    /**
     * @param string|null $error
     * @return bool
     */
    public function canCreatePoll(&$error = null)
    {
        $canCreatePoll = parent::canCreatePoll($error);

        if ($canCreatePoll)
        {
            $visitor = \XF::visitor();
            if ($visitor->hasNodePermission($this->node_id, 'manageAnyThread'))
            {
                return true;
            }

            return \XF::visitor()->hasNodePermission(
                $this->node_id,
                'createPoll'
            );
        }

        return $canCreatePoll;
    }
}
