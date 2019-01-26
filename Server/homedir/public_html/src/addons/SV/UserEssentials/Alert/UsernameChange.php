<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\Alert;

use XF\Alert\AbstractHandler;
use XF\Mvc\Entity\Entity;

use SV\UserEssentials\XF\Entity\User;

/**
 * An alert handler for user name changes.
 */
class UsernameChange extends AbstractHandler
{
    /**
     * @param Entity|\SV\UserEssentials\Entity\UsernameChange $entity
     * @param string|null                                     $error
     * @return bool
     */
    public function canViewContent(Entity $entity, &$error = null)
    {
        return true;
    }

    /**
     * @param string $action
     * @return string
     */
    public function getTemplateName($action)
    {
        return "public:sv_ue_alert_unc_{$action}";
    }

    /**
     * @return array
     */
    public function getEntityWith()
    {
        return ['User'];
    }

    /**
     * @return array
     */
    public function getOptOutActions()
    {
        // changes to this should be reflected in the UNC entity structure
        // based off the various sv_ue_alert_unc_* templates
        $alerts = ['approved_own', 'denied_own'];

        /** @var User $visitor */
        $visitor = \XF::visitor();
        if ($visitor->canViewUsernameChangeDetails())
        {
            array_unshift($alerts, 'approved_other');
        }

        return $alerts;
    }

    /**
     * @return int
     */
    public function getOptOutDisplayOrder()
    {
        return 90000;
    }
}
