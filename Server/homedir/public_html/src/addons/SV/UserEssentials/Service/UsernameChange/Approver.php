<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\Service\UsernameChange;

use XF\App;
use XF\Service\AbstractService;

use SV\UserEssentials\Entity\UsernameChange;

/**
 * A service for approving username changes.
 */
class Approver extends AbstractService
{
    /**
     * @var UsernameChange
     */
    protected $usernameChange;

    /**
     * @var string
     */
    protected $note;

    /**
     * @var bool|null
     */
    protected $isPrivate;

    /**
     * @param App            $app
     * @param UsernameChange $usernameChange
     * @param string         $note
     */
    public function __construct(
        App $app,
        UsernameChange $usernameChange,
        $note
    )
    {
        parent::__construct($app);

        $this->usernameChange = $usernameChange;
        $this->note = $note;
    }

    /**
     * @return UsernameChange
     */
    public function getUsernameChange()
    {
        return $this->usernameChange;
    }

    /**
     * @param bool $isPrivate
     */
    public function setIsPrivate($isPrivate)
    {
        $this->isPrivate = $isPrivate;
    }

    /**
     * @return bool
     */
    public function approve()
    {
        $usernameChange = $this->usernameChange;
        if ($usernameChange->status === 'moderated')
        {
            $usernameChange->status = 'approved';
            $usernameChange->moderator_id = \XF::visitor()->user_id;
            $usernameChange->moderation_date = \XF::$time;
            $usernameChange->moderator_note = $this->note;
            if ($this->isPrivate !== null)
            {
                $usernameChange->is_private = $this->isPrivate;
            }
            $usernameChange->save();

            $this->onApprove();

            return true;
        }

        return false;
    }

    /**
     * Actions to take after approving a user name change.
     */
    protected function onApprove()
    {
        $usernameChange = $this->usernameChange;
        $usernameChange->applyUsernameChange();
        if ($usernameChange->is_private) {
            // revert any prior user name change title
            /** @var \SV\UserEssentials\XF\Entity\User $user */
            $user = $usernameChange->User;
            $user->revertUsernameChangeTitle();
        } else {
            $usernameChange->applyUserTitle();
        }

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
