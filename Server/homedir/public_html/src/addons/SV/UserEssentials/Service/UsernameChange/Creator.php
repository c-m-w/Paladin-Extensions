<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\Service\UsernameChange;

use SV\UserEssentials\XF\Logger;
use XF\App;
use SV\UserEssentials\XF\Entity\User;

use SV\UserEssentials\Entity\UsernameChange;
use XF\Service\AbstractService;
use XF\Service\ValidateAndSavableTrait;
use XF\Util\Ip;

/**
 * A service for creating username changes.
 */
class Creator extends AbstractService
{
    use ValidateAndSavableTrait;

    /**
     * @var User
     */
    protected $user;

    /**
     * @var UsernameChange
     */
    protected $usernameChange;

    /**
     * @var bool
     */
    protected $logIp = true;

    /**
     * @var bool
     */
    protected $adminEdit = false;

    /**
     * @param App         $app
     * @param User        $user
     * @param string|null $username
     */
    public function __construct(App $app, User $user, $username = null)
    {
        parent::__construct($app);

        $this->setUser($user);
        $this->setDefaults();

        if ($username)
        {
            $this->setUsername($username);
        }
    }

    /**
     * @param User $user
     */
    protected function setUser(User $user)
    {
        $this->user = $user;
        $this->usernameChange = $user->getNewUsernameChange();
    }

    /**
     * @return User
     */
    public function getUser()
    {
        return $this->user;
    }

    /**
     * @return UsernameChange
     */
    public function getUsernameChange()
    {
        return $this->usernameChange;
    }

    protected function setDefaults()
    {
        $this->usernameChange->status = $this->usernameChange->getNewStatus();
    }

    /**
     * @param bool $logIp
     */
    public function setLogIp($logIp)
    {
        $this->logIp = $logIp;
    }

    /**
     * @param bool $adminEdit
     */
    public function setAdminEdit($adminEdit)
    {
        $this->adminEdit = $adminEdit;
        $this->usernameChange->setOption('admin_edit', $adminEdit);
        $this->usernameChange->via_acp = $adminEdit;

        if ($adminEdit)
        {
            $this->usernameChange->status = 'approved';
            $this->usernameChange->moderator_id = \XF::visitor()->user_id;
        }
        else
        {
            $this->usernameChange->status = $this->usernameChange->getNewStatus();
            $this->usernameChange->moderator_id = 0;
        }
    }

    /**
     * @param string $username
     */
    public function setUsername($username)
    {
        $this->usernameChange->to_username = $username;
    }

    /**
     * @param bool $private
     */
    public function setPrivate($private)
    {
        $this->usernameChange->is_private = $private;
    }

    /**
     * @param string $note
     */
    public function setNote($note)
    {
        $this->usernameChange->user_note = $note;
    }

    /**
     * Final setup prior to saving the username change.
     */
    protected function finalSetup()
    {
        $usernameChange = $this->usernameChange;
        $usernameChange->date = time();

        if ($this->logIp)
        {
            $usernameChange->ip_address = Ip::convertIpStringToBinary(
                \XF::app()->request()->getIp()
            );
        }

        if ($this->adminEdit)
        {
            $usernameChange->moderation_date = time();
        }
    }

    /**
     * @return array
     */
    protected function _validate()
    {
        $this->finalSetup();

        $usernameChange = $this->usernameChange;
        $usernameChange->preSave();

        return $usernameChange->getErrors();
    }

    /**
     * @return UsernameChange
     */
    protected function _save()
    {
        $usernameChange = $this->usernameChange;
        $usernameChange->save();
        /** @var Logger $logger */
        $logger = $this->app->logger();

        if (!$this->adminEdit)
        {
            if ($usernameChange->isApproved())
            {
                $logger->logUserAction(
                    'user',
                    $usernameChange->user_id,
                    'username_request',
                    ['new' => $usernameChange->to_username]
                );
            }
            else
            {
                $logger->logUserAction(
                    'user',
                    $usernameChange->user_id,
                    'username',
                    ['old' => $usernameChange->from_username]
                );
            }
        }

        return $usernameChange;
    }

    /**
     * Apply the new username to the user.
     */
    public function applyUsernameChange()
    {
        $usernameChange = $this->usernameChange;
        if ($usernameChange->isApproved())
        {
            $usernameChange->applyUsernameChange();
        }
    }

    /**
     * Apply the title to the user, if applicable.
     */
    public function applyUserTitle()
    {
        $usernameChange = $this->usernameChange;
        if ($usernameChange->isApproved())
        {
            if ($usernameChange->is_private) {
                // revert any prior user name change title
                $this->user->revertUsernameChangeTitle();
            } else {
                $usernameChange->applyUserTitle();
            }
        }
    }

    /**
     * Sends username change notifications.
     */
    public function sendNotifications()
    {
        $usernameChange = $this->usernameChange;
        if ($usernameChange->isApproved())
        {
            /** @var \SV\UserEssentials\Service\UsernameChange\Notifier $notifier */
            $notifier = $this->service(
                'SV\UserEssentials:UsernameChange\Notifier',
                $usernameChange
            );
            if (!$this->app->options()->uncModerateAlert)
            {
                $notifier->setNotifyModerators([]);
            }
            $notifier->setSkipUsers([\XF::visitor()->user_id]);
            $notifier->notify();
        }
    }
}
