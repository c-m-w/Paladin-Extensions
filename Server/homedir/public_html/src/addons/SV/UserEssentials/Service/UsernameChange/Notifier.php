<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\Service\UsernameChange;

use XF\App;
use XF\Entity\User;

use SV\UserEssentials\Entity\UsernameChange;
use XF\Service\AbstractService;

/**
 * A service for notifying users about username changes.
 */
class Notifier extends AbstractService
{
    /**
     * @var UsernameChange
     */
    protected $usernameChange;

    /**
     * @var string
     */
    protected $notificationType;

    /**
     * @var string
     */
    protected $notificationNote = '';

    /**
     * @var array|null
     */
    protected $notifyUsers;

    /**
     * @var array|null
     */
    protected $notifyModerators;

    /**
     * @var array|null
     */
    protected $skipUsers;

    /**
     * @var array
     */
    protected $usersNotified = [];

    /**
     * @param App            $app
     * @param UsernameChange $usernameChange
     */
    public function __construct(App $app, UsernameChange $usernameChange)
    {
        parent::__construct($app);

        $this->usernameChange = $usernameChange;
        $this->setNotificationType($this->usernameChange->status);
        $this->setNotificationNote($this->usernameChange->moderator_note);
    }

    /**
     * @param string $notificationType
     */
    public function setNotificationType($notificationType)
    {
        $this->notificationType = $notificationType;
    }

    /**
     * @return string
     */
    public function getNotificationType()
    {
        return $this->notificationType;
    }

    /**
     * @param string $notificationNote
     */
    public function setNotificationNote($notificationNote)
    {
        $this->notificationNote = $notificationNote;
    }

    /**
     * @return string
     */
    public function getNotificationNote()
    {
        return $this->notificationNote;
    }

    /**
     * @param array $notifyUsers
     */
    public function setNotifyUsers(array $notifyUsers)
    {
        $this->notifyUsers = $notifyUsers;
    }

    /**
     * @return array
     */
    public function getNotifyUsers()
    {
        if ($this->notifyUsers === null)
        {
            $this->notifyUsers = [$this->usernameChange->user_id];
        }

        return $this->notifyUsers;
    }

    /**
     * @param array $notifyModerators
     */
    public function setNotifyModerators(array $notifyModerators)
    {
        $this->notifyModerators = $notifyModerators;
    }

    /**
     * @return array
     */
    public function getNotifyModerators()
    {
        if ($this->notifyModerators === null)
        {
            $moderators = $this->finder('XF:Moderator')->fetch();
            $this->notifyModerators = $moderators->pluckNamed('user_id');
        }

        return $this->notifyModerators;
    }

    /**
     * @param array $skipUsers
     */
    public function setSkipUsers(array $skipUsers)
    {
        $this->skipUsers = $skipUsers;
    }

    /**
     * @return array
     */
    public function getSkipUsers()
    {
        if ($this->skipUsers === null)
        {
            $this->skipUsers = [];
        }

        return $this->skipUsers;
    }

    public function notify()
    {
        $notifiableUsers = $this->getUsersForNotification();

        $users = $this->getNotifyUsers();
        foreach ($users as $userId)
        {
            if (isset($notifiableUsers[$userId]) &&
                ($user = $notifiableUsers[$userId]) &&
                $this->canNotify($user))
            {
                $this->sendNotification($user);
            }
        }

        $moderators = $this->getNotifyModerators();
        foreach ($moderators as $userId)
        {
            if (isset($notifiableUsers[$userId]) &&
                ($user = $notifiableUsers[$userId]) &&
                $this->canNotify($user))
            {
                $this->sendNotification($user);
            }
        }
    }

    /**
     * @return array
     */
    protected function getUsersForNotification()
    {
        $userIds = array_merge(
            $this->getNotifyUsers(),
            $this->getNotifyModerators()
        );
        $userIds = array_diff(
            $userIds,
            $this->getSkipUsers()
        );

        $users = $this->app->em()->findByIds('XF:User', $userIds);
        if (!$users->count())
        {
            return [];
        }

        /** @var \SV\UserEssentials\XF\Entity\User[] $users */
        return $users;
    }

    /**
     * @param User $user
     * @return bool
     */
    public function canNotify(/** @noinspection PhpUnusedParameterInspection */User $user)
    {
        return true;
    }

    /**
     * @param User $user
     * @return bool
     */
    public function canSendAlert(/** @noinspection PhpUnusedParameterInspection */User $user)
    {
        return true;
    }

    /**
     * @param User $user
     * @return bool
     */
    public function canSendEmail(User $user)
    {
        return (
            $user->user_state === 'valid'
            && !$user->is_banned
            && $user->email
        );
    }

    /**
     * @param User $user
     * @return bool
     */
    protected function sendNotification(User $user)
    {
        if (!empty($this->usersNotified[$user->user_id]))
        {
            return false;
        }

        $usernameChange = $this->usernameChange;
        $notificationType = $this->notificationType;
        $notificationNote = $this->notificationNote;

        if ($user->user_id === $usernameChange->user_id)
        {
            if ($this->canSendAlert($user))
            {
                /** @var \XF\Repository\UserAlert $alertRepo */
                $alertRepo = $this->app->repository('XF:UserAlert');
                $alertRepo->alertFromUser(
                    $user,
                    null,
                    'unc',
                    $usernameChange->unc_id,
                    "{$notificationType}_own",
                    [
                        'name' => $usernameChange->to_username,
                        'note' => $notificationNote
                    ]
                );
            }
            if ($this->canSendEmail($user))
            {
                $this->app->mailer()->newMail()
                          ->setToUser($user)
                          ->setTemplate("sv_ue_unc_{$notificationType}", [
                              'name' => $usernameChange->to_username,
                              'note' => $notificationNote
                          ])
                          ->queue();
            }
        }
        else
        {
            if ($this->canSendAlert($user))
            {
                /** @var \XF\Repository\UserAlert $alertRepo */
                $alertRepo = $this->app->repository('XF:UserAlert');
                $alertRepo->alertFromUser(
                    $user,
                    null,
                    'unc',
                    $usernameChange->unc_id,
                    "{$notificationType}_other",
                    [
                        'old_name' => $usernameChange->from_username,
                        'name'     => $usernameChange->to_username,
                        'note'     => $notificationNote
                    ]
                );
            }
        }

        $this->usersNotified[$user->user_id] = true;

        return true;
    }
}
