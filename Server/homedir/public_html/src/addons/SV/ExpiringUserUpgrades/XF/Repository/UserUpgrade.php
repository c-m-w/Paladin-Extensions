<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\ExpiringUserUpgrades\XF\Repository;

use SV\ExpiringUserUpgrades\Globals;
use XF\Entity\UserUpgradeActive;
use XF\Entity\UserUpgrade as UserUpgradeEntity;
use XF\PrintableException;

/**
 * Extends \XF\Repository\UserUpgrade
 */
class UserUpgrade extends XFCP_UserUpgrade
{
    /**
     * @return string
     */
    public function getUpgradeUrl()
    {
        $options = \XF::options();
        $exup_upgradeUrl = $options->exup_upgradeUrl;
        $upgradeUrlType = empty($exup_upgradeUrl['type']) ? 'default' : $exup_upgradeUrl['type'];
        if ($upgradeUrlType === 'custom' && isset($exup_upgradeUrl['custom']))
        {
            return $exup_upgradeUrl['custom'];
        }

        return $this->app()->router('public')->buildLink('canonical:account/upgrades');
    }

    public function downgradeExpiredUpgrades()
    {
        Globals::$forceDowngradeAlert = true;
        Globals::$downgradeReason = 'expired_upgrade';
        try
        {
            parent::downgradeExpiredUpgrades();
        }
        finally
        {
            Globals::$forceDowngradeAlert = false;
            Globals::$downgradeReason = null;
        }
    }

    /**
     * @param int $limit
     */
    public function alertExpiringUserUpgrades($limit = 1000)
    {
        $limit = intval($limit);
        $limitSql = $limit > 0 ? 'LIMIT ' . $limit : '';
        $expiringActiveUpgradeIds = $this->db()->fetchAllKeyed("
            SELECT distinct active.user_upgrade_record_id
            FROM xf_user_upgrade_active AS active
            INNER JOIN xf_user_upgrade AS upgrade
              ON (upgrade.user_upgrade_id = active.user_upgrade_id)
            INNER JOIN xf_user AS user
              ON (user.user_id = active.user_id)
            WHERE active.end_date > 0 AND
                  upgrade.exup_days > 0 AND
                  active.notified_date = 0 AND
                  active.end_date <= (UNIX_TIMESTAMP() + (86400 * upgrade.exup_days))
            {$limitSql}
        ", 'user_upgrade_record_id');

        if (empty($expiringActiveUpgradeIds))
        {
            return;
        }

        /** @var \XF\Entity\UserUpgradeActive[] $expired */
        $expiring = $this->finder('XF:UserUpgradeActive')
                         ->with('Upgrade')
                         ->with('User')
                         ->whereIds($expiringActiveUpgradeIds)
                         ->fetch();

        /** @var \XF\Entity\UserUpgradeActive|\SV\ExpiringUserUpgrades\XF\Entity\UserUpgradeActive $upgradeAboutToExpire */
        foreach ($expiring AS $upgradeAboutToExpire)
        {
            /** @var \XF\Entity\UserUpgrade|\SV\ExpiringUserUpgrades\XF\Entity\UserUpgrade $upgrade */
            $upgrade = $upgradeAboutToExpire->Upgrade;

            if ($upgrade && $upgrade->recurring)
            {
                // For recurring payments give a 24 hour grace period
                if ($upgradeAboutToExpire->end_date + 86400 >= \XF::$time)
                {
                    continue;
                }
            }

            if ($upgrade)
            {
                $notifyAction = 'expiring_upgrade';
                if ($upgrade->recurring)
                {
                    $notifyAction = 'expiring_subscription';
                }

                try
                {
                    $this->svNotifyUser($upgradeAboutToExpire, $upgrade, $notifyAction);
                }
                catch (PrintableException $e)
                {
                    \XF::logException($e);
                }
            }

            // mark the active upgrade as notified because no point in trying to send alert again for a upgrade which is
            // deleted
            try
            {
                $upgradeAboutToExpire->notified_date = \XF::$time;
                $upgradeAboutToExpire->save();
            }
            catch (PrintableException $e)
            {
                \XF::logException($e);
            }
            catch (\Exception $e)
            {
                \XF::logException($e);
            }
        }
    }

    /**
     * Alerts and/or emails and/or sends conversation user upon expiring/expired/reversed upgrades
     * Should be wrapped in a \XF::asVisitor() call
     *
     * @param                   $record
     * @param UserUpgradeEntity $userUpgrade
     * @param                   $action
     */
    public function svNotifyUser(UserUpgradeActive $record, UserUpgradeEntity $userUpgrade, $action)
    {
        if (!$record)
        {
            return;
        }
        /** @var \XF\Entity\User $user */
        $user = $record->User;
        /** @var \SV\ExpiringUserUpgrades\XF\Entity\UserOption $userOption */
        $userOption = $user->Option;
        $upgradeAvailable = false;
        $exitingUpgradeId = $userUpgrade->user_upgrade_id;
        list ($available, $purchased) = $this->getFilteredUserUpgradesForList();
        switch ($action)
        {
            case 'purchased_upgrade':
            case 'purchased_subscription':
                $upgradeAvailable = true;
                $sendMail = $userOption->sv_exup_email_on_upgrade_purchase;
                break;

            case 'reversal_extend_subscription':
            case 'reversal_extend_upgrade':
            case 'payment_reversal_upgrade':
            case 'payment_reversal_subscription':
                $sendMail = $userOption->sv_exup_email_on_upgrade_reversal;
                break;

            case 'expiring_upgrade':
            case 'expiring_subscription':
                foreach ($purchased AS $upgradeId => $upgrade)
                {
                    /** @var UserUpgradeEntity $upgrade */
                    // this upgrade has somehow been purchased after it has been expired, don't send an expired notice
                    if ($upgradeId === $exitingUpgradeId && $upgrade->can_purchase)
                    {
                        $upgradeAvailable = true;
                    }
                }
                $sendMail = $userOption->sv_exup_email_on_expiring_expired_upgrade;
                break;

            case 'expired_upgrade':
            case 'expired_subscription':
                // determine if this upgrade has been prevented from being applyable due to another purchase
                $exitingUpgradeId = $record->user_upgrade_id;
                foreach ($purchased AS $upgradeId => $upgrade)
                {
                    /** @var UserUpgradeEntity $upgrade */
                    // this upgrade has somehow been purchased after it has been expired, don't send an expired notice
                    if ($upgradeId === $exitingUpgradeId)
                    {
                        return;
                    }

                    foreach ($upgrade->disabled_upgrade_ids AS $disabledId)
                    {
                        if ($disabledId == $exitingUpgradeId)
                        {
                            return;
                        }
                    }
                }
                $sendMail = $userOption->sv_exup_email_on_expiring_expired_upgrade;
                break;

            default:
                return;
        }

        // determine if this upgrade is still available
        if (!$upgradeAvailable)
        {
            foreach ($available as $upgradeId => $upgrade)
            {
                if ($upgradeId == $exitingUpgradeId)
                {
                    $upgradeAvailable = true;
                    break;
                }
            }
        }

        $options = \XF::options();
        $bccActions = explode("\n", $options->ExUp_BccEmail_Action);
        $doBcc = is_array($bccActions) && in_array($action, $bccActions, true);
        $notifyBy = $options->exup_notify_by;
        $upgradeUrl = $this->getUpgradeUrl();
        /** @var \SV\ExpiringUserUpgrades\XF\Entity\UserUpgrade $upgradeFromRecord */
        $upgradeFromRecord = $record->Upgrade;

        $params = [
            'username'      => $record->User->username,
            'upgrade_title' => $userUpgrade->title,
            'url'           => $upgradeUrl,
            'upgrade_url'   => $upgradeUrl,
            'upgradeUrl'    => $upgradeUrl,
            'upgradeDenied' => !$upgradeAvailable,
            'boardUrl'      => $options->boardUrl,
            'boardTitle'    => $options->boardTitle,
        ];

        if ($action == 'expiring_upgrade' || $action == 'expiring_subscription')
        {
            if (empty($upgradeFromRecord->exup_days))
            {
                return;
            }

            $numDays = $upgradeFromRecord->exup_days;
            $cutOff = \XF::$time + (86400 * $numDays);
            $numDays = ceil($numDays - (($cutOff - $record->end_date) / 86400));
            if ($numDays < 0)
            {
                $numDays = 0;
            }
            $params['num_days'] = $numDays;
        }

        if (!empty($notifyBy['alert']['active']))
        {
            $alertParams = $params;
            // do not store the following in the alerts
            unset($alertParams['url']);
            unset($alertParams['upgrade_url']);
            unset($alertParams['upgradeUrl']);
            unset($alertParams['boardUrl']);
            unset($alertParams['boardTitle']);

            /** @var \XF\Repository\UserAlert $alertRepo */
            $alertRepo = $this->repository('XF:UserAlert');
            $alertRepo->alert(
                $user,
                0,
                '',
                'exup',
                $user->user_id,
                $action,
                $alertParams
            );
        }

        // has email, is valid, and not banned
        if (!empty($notifyBy['email']['active']) &&
            $user->email && $user->user_state == 'valid' && !$user->is_banned &&
            (!$options->exup_respect_email_privacy || $user->Option->receive_admin_email))
        {
            if ($sendMail)
            {
                $templateName = 'exup_email_' . $action . '_body';
                $mail = $this->app()->mailer()->newMail()
                             ->setToUser($record->User)
                             ->setTemplate($templateName, $params);
                if ($doBcc)
                {
                    $bccEmail = trim(strval($options->ExUp_BccEmail));
                    if ($bccEmail)
                    {
                        $mail->addHeader('bcc', $bccEmail);
                    }
                }
                $mail->queue();
            }
        }

        if (!empty($notifyBy['conversation']['active']) && !empty($notifyBy['conversation']['sender_username']))
        {
            /** @var \XF\Finder\User $userFinder */
            $userFinder = $this->finder('XF:User');
            /** @var \XF\Entity\User $notifyByUser */
            $notifyByUser = $userFinder
                ->where('username', '=', $notifyBy['conversation']['sender_username'])
                ->with([
                    'Profile',
                    'Privacy',
                    'PermissionCombination'
                ])->fetchOne();

            if (!$notifyByUser)
            {
                return;
            }

            $title = \XF::phrase('exup_conversation_' . $action . '_title', $params);
            $body = \XF::phrase('exup_conversation_' . $action . '_message', $params)->render('raw');
            $tokens = [
                '{name}' => $user->username,
                '{id}'   => $user->user_id
            ];
            $body = strtr($body, $tokens);

            \XF::asVisitor($notifyByUser, function () use ($notifyByUser, $user, $title, $body, $options) {
                /** @var \XF\Service\Conversation\Creator $conversationCreator */
                $conversationCreator = $this->app()->service('XF:Conversation\Creator', $notifyByUser);
                $conversationCreator->setIsAutomated();
                $conversationCreator->setRecipientsTrusted([$user]);
                $conversationCreator->setContent($title, $body);
                $conversationCreator->setAutoSendNotifications(false);
                if ($conversationCreator->validate($errors))
                {
                    /** @var \XF\Entity\ConversationMaster $conversation */
                    $conversation = $conversationCreator->save();
                    $recipientState = $options->exup_autoLeaveConversation;
                    $convRecipients = $conversation
                        ->getRelationFinder('Recipients')
                        ->with('ConversationUser')
                        ->fetch();

                    /** @var \XF\Entity\ConversationRecipient $convRecipient */
                    foreach ($convRecipients AS $convRecipient)
                    {
                        if ($convRecipient->user_id === $notifyByUser->user_id)
                        {
                            continue;
                        }

                        switch ($recipientState)
                        {
                            case '':
                            case 'no_delete':
                                break;
                            case 'delete':
                            case 'delete_ignore':
                                $convRecipient->recipient_state = $recipientState;
                                $convRecipient->save();
                                break;
                        }
                    }

                    $conversationCreator->sendNotifications();
                }
            });
        }
    }
}