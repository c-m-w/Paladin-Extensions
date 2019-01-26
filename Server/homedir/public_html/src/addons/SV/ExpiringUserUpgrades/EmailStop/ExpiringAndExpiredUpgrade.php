<?php

namespace SV\ExpiringUserUpgrades\EmailStop;

use XF\EmailStop\AbstractHandler;

/**
 * Class ExpiringAndExpiredUpgrade
 *
 * @package SV\ExpiringUserUpgrades
 */
class ExpiringAndExpiredUpgrade extends AbstractHandler
{
    /**
     * @param \XF\Entity\User $user
     * @param                 $contentId
     * @return null
     */
    public function getStopOneText(\XF\Entity\User $user, $contentId)
    {
        return null;
    }

    /**
     * @param \XF\Entity\User $user
     * @return \XF\Phrase
     */
    public function getStopAllText(\XF\Entity\User $user)
    {
        return \XF::phrase('expiringUserUpgrades_stop_notifications_email_for_all_expiring_and_expired_upgrades');
    }

    /**
     * @param \XF\Entity\User $user
     * @param                 $contentId
     */
    public function stopOne(\XF\Entity\User $user, $contentId)
    {
    }

    /**
     * @param \XF\Entity\User $user
     */
    public function stopAll(\XF\Entity\User $user)
    {
        /** @var \SV\ExpiringUserUpgrades\XF\Entity\UserOption $option */
        $option = $user->Option;
        $option->sv_exup_email_on_expiring_expired_upgrade = false;
        $option->saveIfChanged();
    }
}