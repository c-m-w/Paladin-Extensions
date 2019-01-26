<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\Cron;

/**
 * Cron class for performing periodic clean-up tasks.
 */
class CleanUp
{
    /**
     * Prunes user logs and reverts custom expired titles from username changes.
     */
    public static function runDailyCleanUp()
    {
        /** @var \SV\UserEssentials\Repository\UserLog $userLogRepo */
        $userLogRepo = \XF::repository('SV\UserEssentials:UserLog');
        $userLogRepo->pruneUserLogs();

        /** @var \SV\UserEssentials\Repository\UsernameChange $usernameChangeRepo */
        $usernameChangeRepo = \XF::repository('SV\UserEssentials:UsernameChange');
        $usernameChangeRepo->revertExpiredUserTitles();
    }
}
