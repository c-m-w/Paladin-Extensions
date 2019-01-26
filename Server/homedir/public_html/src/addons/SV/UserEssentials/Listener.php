<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials;

use XF\Entity\User;
use XF\Pub\App;
use XF\Service\User\ContentChange;
use XF\Service\User\DeleteCleanUp;
use XF\Service\User\Merge;

/**
 * Contains event listener callbacks.
 */
class Listener
{
    /**
     * @param \XF\Entity\User &$visitor
     */
    public static function visitorSetup(\XF\Entity\User &$visitor)
    {
        if ($visitor->user_id &&
            ($customFields = $visitor->Profile->custom_fields) &&
            ($definitionSet = $customFields->getDefinitionSet()))
        {
            /** @var \XF\CustomField\Set $customFields */

            // "As-designed" - Custom user field deletion does not delete entry data
            // https://xenforo.com/community/threads/custom-user-field-deletion-does-not-delete-entry-data.113392/
            // as such, need to check the definition exists.

            if ($customFields->offsetExists('useress_threadsPerPage') && $definitionSet->offsetExists('useress_threadsPerPage'))
            {
                $discussionsPerPage = intval($customFields->useress_threadsPerPage);
                if ($discussionsPerPage > 0)
                {
                    \XF::app()->options()->discussionsPerPage = $discussionsPerPage;
                }
            }
            if ($customFields->offsetExists('useress_messagesPerPage') && $definitionSet->offsetExists('useress_messagesPerPage'))
            {
                $messagesPerPage = intval($customFields->useress_messagesPerPage);
                if ($messagesPerPage > 0)
                {
                    \XF::app()->options()->messagesPerPage = $messagesPerPage;
                }
            }
        }
    }

    /**
     * @param ContentChange $changeService
     * @param array                          $updates
     */
    public static function userContentChangeInit(
        /** @noinspection PhpUnusedParameterInspection */
        ContentChange $changeService,
        array &$updates
    )
    {
        $updates['xf_sv_unc'] = [
            ['user_id'],
            ['moderator_id']
        ];
        $updates['xf_sv_unc_cron'] = ['user_id'];
        $updates['xf_sv_user_log'] = [
            ['user_id'],
            ['content_user_id', 'content_username']
        ];
    }

    /**
     * @param DeleteCleanUp $deleteService
     * @param array                          $deletes
     */
    public static function userDeleteCleanInit(
        /** @noinspection PhpUnusedParameterInspection */
        DeleteCleanUp $deleteService,
        array &$deletes
    )
    {
        if (\XF::options()->uncAllowPreviousNames) {
            $deletes['xf_sv_unc'] = 'user_id = ?';
        }
        $deletes['xf_sv_unc_cron'] = 'user_id = ?';
    }

    /**
     * @param User        $target
     * @param User        $source
     * @param Merge $mergeService
     */
    public static function userMergeCombine(
        /** @noinspection PhpUnusedParameterInspection */
        User $target,
        User $source,
        Merge $mergeService
    )
    {
        $sourceBan = $source->Ban;
        if ($sourceBan && !$sourceBan->triggered) {
            /** @var \XF\Entity\UserBan $targetBan */
            $targetBan = $target->getRelationOrDefault('Ban', false);
            if (
                $targetBan->isInsert()
                || (
                    $targetBan->end_date
                    && (
                        !$sourceBan->end_date
                        || ($targetBan->end_date < $sourceBan->end_date)
                    )
                )
            ) {
                $targetBan->bulkSet([
                    'ban_user_id' => $sourceBan->ban_user_id,
                    'ban_date'    => $sourceBan->ban_date,
                    'end_date'    => $sourceBan->end_date,
                    'user_reason' => $sourceBan->user_reason,
                    'triggered'   => $sourceBan->triggered
                ]);
                if ($targetBan->preSave()) {
                    $targetBan->save();
                }
            }
        }

        // TODO: send notifications / set user title?
        /** @var \SV\UserEssentials\XF\Entity\User $target */
        $usernameChange = $target->getNewUsernameChange();
        $usernameChange->setOption('admin_edit', true);
        $usernameChange->from_username = $source->username;
        $usernameChange->to_username = $target->username;
        $usernameChange->via_acp = true;
        $usernameChange->user_note = \XF::app()->language(0)->phrase(
            'sv_ue_user_was_merged'
        );
        $usernameChange->save();
    }
}
