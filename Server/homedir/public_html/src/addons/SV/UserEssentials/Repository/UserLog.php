<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\Repository;

use XF\Mvc\Entity\Repository;

/**
 * A repository for user log entities.
 */
class UserLog extends Repository
{
    /**
     * @return \XF\Mvc\Entity\Finder
     */
    public function findLogsForList()
    {
        return $this->finder('SV\UserEssentials:UserLog')
                    ->with('User')
                    ->setDefaultOrder('log_date', 'DESC');
    }

    /**
     * @param int $cutOff
     * @return int
     */
    public function pruneUserLogs($cutOff = null)
    {
        if ($cutOff === null)
        {
            $logLength = $this->options()->useressLogLength;
            if (!$logLength)
            {
                return 0;
            }

            $cutOff = (\XF::$time - (86400 * $logLength));
        }

        return $this->db()->delete('xf_sv_user_log', 'log_date < ?', $cutOff);
    }

    public function clearUserLog()
    {
        $this->db()->emptyTable('xf_sv_user_log');
    }
}
