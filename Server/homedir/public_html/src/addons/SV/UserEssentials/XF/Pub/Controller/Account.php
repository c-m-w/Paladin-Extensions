<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\XF\Pub\Controller;

use XF\Entity\User;
use XF\Mvc\Entity\ArrayCollection;

/**
 * Extends \XF\Pub\Controller\Account
 */
class Account extends XFCP_Account
{
    // TODO: set password for external auth users in actionSecurity()?

    /**
     * @param User $visitor
     *
     * @return \XF\Mvc\FormAction
     */
    protected function accountDetailsSaveProcess(User $visitor)
    {
        /** @var \XF\Mvc\FormAction $form */
        $form = parent::accountDetailsSaveProcess($visitor);

        if ($visitor->hasPermission('general', 'editCustomTitle')) {
            $revertTitle = $this->filter('user.custom_title_revert', 'bool');
            if ($revertTitle) {
                $form->apply(function () use ($visitor) {
                    /** @var \SV\UserEssentials\XF\Entity\User $visitor */
                    $visitor->revertUsernameChangeTitle();
                });
            }
        }

        return $form;
    }

    /**
     * @return \XF\Mvc\Reply\AbstractReply
     */
    public function actionUsernameChange()
    {
        /** @var \SV\UserEssentials\XF\Entity\User $visitor */
        $visitor = \XF::visitor();

        if (!$visitor->canChangeUsername($error))
        {
            return $this->noPermission($error);
        }

        $auth = $visitor->Auth->getAuthenticationHandler();
        if (!$auth)
        {
            return $this->noPermission();
        }
        if (!$auth->hasPassword())
        {
            return $this->noPermission(
                \XF::phraseDeferred(
                    'sv_ue_your_user_name_cannot_be_changed_while_your_account_does_not_have_password'
                )
            );
        }

        if ($visitor->pending_username_change)
        {
            return $this->error(\XF::phrase(
                'sv_ue_you_currently_have_a_user_name_change_pending_approval'
            ));
        }

        $remainingUsernameChanges = $visitor->remaining_username_changes_in_period;
        if ($remainingUsernameChanges === 0)
        {
            $usernameChangePeriodEnd = $visitor->username_change_period_end;

            return $this->error(\XF::phrase(
                'sv_ue_you_can_not_change_your_user_name_again_until_x',
                ['periodEnd' => \XF::language()->date($usernameChangePeriodEnd)]
            ));
        }

        if ($this->isPost())
        {
            $username = $this->filter('username', 'str');
            if ($username === $visitor->username)
            {
                return $this->redirect($this->buildLink('account/account-details'));
            }

            $password = $this->filter('password', 'str');
            if (!$visitor->authenticate($password))
            {
                throw $this->errorException(
                    \XF::phrase('your_existing_password_is_not_correct')
                );
            }

            $note = $this->filter('note', 'str');
            $creator = $this->setupUsernameChangeCreate(
                $visitor,
                $username,
                $note
            );
            if (!$creator->validate($errors))
            {
                return $this->error($errors);
            }
            /** @noinspection PhpUnusedLocalVariableInspection */
            $usernameChange = $creator->save();
            $this->finalizeUsernameChangeCreate($creator);

            return $this->redirect($this->buildLink('account/account-details'));
        }

        /** @var \SV\UserEssentials\Repository\UsernameChange $usernameChangeRepo */
        $usernameChangeRepo = $this->repository('SV\UserEssentials:UsernameChange');
        $messageList = $usernameChangeRepo->getDisplayMessages();

        $viewParams = [
            'messageList' => $messageList
        ];
        $view = $this->view(
            'XF:Account\Username',
            'sv_ue_account_username',
            $viewParams
        );

        return $this->addAccountWrapperParams($view, 'account_details');
    }

    /**
     * @param \SV\UserEssentials\XF\Entity\User $user
     * @param string                            $username
     * @param string                            $note
     * @return \SV\UserEssentials\Service\UsernameChange\Creator
     */
    protected function setupUsernameChangeCreate(
        /** @noinspection PhpUnnecessaryFullyQualifiedNameInspection */
        \SV\UserEssentials\XF\Entity\User $user,
        $username,
        $note
    )
    {
        /** @var \SV\UserEssentials\Service\UsernameChange\Creator $creator */
        $creator = $this->service(
            'SV\UserEssentials:UsernameChange\Creator',
            $user,
            $username
        );

        if ($user->isUsernameChangeModerated())
        {
            $creator->setNote($note);
        }

        return $creator;
    }

    /**
     * @param \SV\UserEssentials\Service\UsernameChange\Creator $creator
     */
    protected function finalizeUsernameChangeCreate(
        /** @noinspection PhpUnnecessaryFullyQualifiedNameInspection */
        \SV\UserEssentials\Service\UsernameChange\Creator $creator
    )
    {
        $creator->applyUsernameChange();
        $creator->applyUserTitle();
        $creator->sendNotifications();
    }

    /**
     * @return \XF\Mvc\Reply\AbstractReply
     */
    public function actionLikesGiven()
    {
        $visitor = \XF::visitor();

        $page = $this->filterPage();
        $perPage = 20;

        /** @var \SV\UserEssentials\XF\Repository\LikedContent $likeRepo */
        $likeRepo = $this->repository('XF:LikedContent');

        $likeFinder = $likeRepo->findUserLikesGiven($visitor);

        $total = $likeFinder->total();
        $this->assertValidPage($page, $perPage, $total, 'account/likes-given');

        /** @var \XF\Entity\LikedContent[]|ArrayCollection $likes */
        $likes = $likeFinder->limitByPage($page, $perPage)->fetch();
        $likeRepo->addContentToLikes($likes);
        $likes = $likes->filterViewable();

        $viewParams = [
            'likes'   => $likes,
            'page'    => $page,
            'perPage' => $perPage,
            'total'   => $total
        ];
        $view = $this->view(
            'XF:Account\LikesGiven',
            'sv_ue_account_likes_given',
            $viewParams
        );

        return $this->addAccountWrapperParams($view, 'likes_given');
    }

}
