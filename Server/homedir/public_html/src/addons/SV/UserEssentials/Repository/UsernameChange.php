<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\Repository;

use XF\Entity\User;
use XF\Mvc\Entity\Repository;

/**
 * A repository for username change entities.
 */
class UsernameChange extends Repository
{
    /**
     * @param User|int $userId
     * @return \XF\Mvc\Entity\Finder
     */
    public function findUsernameChangesForUser($userId)
    {
        if ($userId instanceof User)
        {
            $userId = $userId->user_id;
        }

        $finder = $this->finder('SV\UserEssentials:UsernameChange')
                       ->where('user_id', $userId)
                       ->setDefaultOrder('date', 'DESC');

        return $finder;
    }

    /**
     * @param User|int $userId
     * @return \XF\Mvc\Entity\Finder
     */
    public function findUsernameChangesForList($userId)
    {
        $finder = $this->findUsernameChangesForUser($userId);

        if (!$this->options()->uncDisplayChangesViaACP)
        {
            $finder->where('via_acp', '0');
        }

        return $finder;
    }

    /**
     * @param User|int $userId
     * @return \XF\Mvc\Entity\Finder
     */
    public function findUsernameChangesInPeriodForUser($userId)
    {
        if ($userId instanceof User)
        {
            $userId = $userId->user_id;
        }

        $finder = $this->finder('SV\UserEssentials:UsernameChange')
                       ->where('user_id', $userId)
                       ->where('status', '!=', 'denied')
                       ->where('via_acp', 0)
                       ->setDefaultOrder('date', 'ASC');

        $options = $this->options();
        $maxUsernameChanges = $options->uncMaxChanges;
        if ($maxUsernameChanges)
        {
            $finder->limit($maxUsernameChanges);

            $usernameChangePeriod = ($options->uncResetDays * 86400);
            if ($usernameChangePeriod)
            {
                $usernameChangePeriodStart = (\XF::$time - $usernameChangePeriod);
                $finder->where('date', '>', $usernameChangePeriodStart);
            }
        }

        return $finder;
    }

    /**
     * @param User|int $userId
     * @return \XF\Mvc\Entity\Finder
     */
    public function findPendingUsernameChangesForUser($userId)
    {
        if ($userId instanceof User)
        {
            $userId = $userId->user_id;
        }

        $finder = $this->finder('SV\UserEssentials:UsernameChange')
                       ->with('ApprovalQueue')
                       ->where('user_id', $userId)
                       ->where('status', 'moderated')
                       ->setDefaultOrder('date', 'ASC');

        return $finder;
    }

    /**
     * @return array
     */
    public function getDisplayMessages()
    {
        /** @var \SV\UserEssentials\XF\Entity\User $visitor */
        $visitor = \XF::visitor();

        $messages = [];
        $options = $this->options();

        $maxUsernameChanges = $options->uncMaxChanges;
        if ($maxUsernameChanges)
        {
            $usernameChangesInPeriod = $visitor->username_changes_in_period;
            if ($usernameChangesInPeriod->count())
            {
                $remainingUsernameChanges = $visitor->remaining_username_changes_in_period;
                $usernameChangePeriodEnd = $visitor->username_change_period_end;
                if ($usernameChangePeriodEnd)
                {
                    $messages[] = \XF::phrase(
                        'sv_ue_you_can_change_your_user_name_x_more_times_before_y',
                        [
                            'remaining' => $remainingUsernameChanges,
                            'periodEnd' => \XF::language()->date($usernameChangePeriodEnd)
                        ]
                    );
                }
                else
                {
                    $messages[] = \XF::phrase(
                        'sv_ue_you_can_change_your_user_name_x_more_times',
                        ['remaining' => $remainingUsernameChanges]
                    );
                }
            }
            else
            {
                $usernameChangePeriod = $options->uncResetDays;
                if ($usernameChangePeriod)
                {
                    $messages[] = \XF::phrase(
                        'sv_ue_you_can_change_your_user_name_x_times_every_y_days',
                        [
                            'max'    => $maxUsernameChanges,
                            'period' => $usernameChangePeriod
                        ]
                    );
                }
                else
                {
                    $messages[] = \XF::phrase(
                        'sv_ue_you_can_change_your_user_name_x_times',
                        ['max' => $maxUsernameChanges]
                    );
                }
            }
        }

        $maxMessageCount = $options->uncMaxPostCount;
        if ($maxMessageCount)
        {
            $messages[] = \XF::phrase(
                'sv_ue_you_can_not_change_your_user_name_after_you_post_more_than_x_messages',
                ['max' => $maxMessageCount]
            );
        }

        $usernameChangeModerated = $visitor->isUsernameChangeModerated();
        if ($usernameChangeModerated)
        {
            $messages[] = \XF::phrase(
                'sv_ue_your_user_name_change_must_be_approved_by_a_moderator'
            );
        }

        return $messages;
    }

    /**
     * Reverts expired user titles.
     */
    public function revertExpiredUserTitles()
    {
        $db = $this->db();

        $db->beginTransaction();

        $userTitleDays = $this->options()->uncCustomTitleDays;
        $pruneDate = (\XF::$time - ($userTitleDays * 86400));
        $userTitles = $db->fetchAllKeyed(
            'SELECT *
                FROM xf_sv_unc_cron
                WHERE date < ?',
            'user_id',
            $pruneDate
        );
        if (!$userTitles)
        {
            return 0;
        }

        $userIds = array_keys($userTitles);

        $users = $this->em->findByIds('XF:User', $userIds);
        foreach ($userTitles as $userId => $userTitle)
        {
            if (empty($users[$userId]))
            {
                continue;
            }
            $user = $users[$userId];

            if ($user->custom_title == $userTitle['new_custom_title'])
            {
                $user->fastUpdate(
                    'custom_title',
                    $userTitle['old_custom_title']

                );
            }
        }

        $quotedUserIds = $db->quote($userIds);
        $db->delete(
            'xf_sv_unc_cron',
            "user_id IN ({$quotedUserIds})"
        );

        $db->commit();
    }
}
