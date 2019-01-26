<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\XF\Admin\Controller;

use XF\Entity\User as UserEntity;
use XF\Mvc\FormAction;
use XF\Mvc\Reply\View;
use XF\Mvc\ParameterBag;

/**
 * Extends \XF\Admin\Controller\User
 */
class User extends XFCP_User
{
    /**
     * @param ParameterBag $params
     *
     * @return \XF\Mvc\Reply\AbstractReply
     */
    public function actionUserLoginAttempts(ParameterBag $params)
    {
        /** @noinspection PhpUndefinedFieldInspection */
        $user = $this->assertUserExists($params->user_id);

        /** @var \SV\UserEssentials\XF\Repository\LoginAttempt $loginAttemptRepo */
        $loginAttemptRepo = $this->repository('XF:LoginAttempt');
        $loginAttemptFinder = $loginAttemptRepo->findLoginAttemptsForUser($user);
        $attempts = $loginAttemptFinder->fetch();

        $viewParams = [
            'user'     => $user,
            'attempts' => $attempts
        ];
        return $this->view(
            'XF:User\LoginAttemptList',
            'sv_ue_user_login_attempt_list',
            $viewParams
        );
    }

    /**
     * @param ParameterBag $params
     *
     * @return \XF\Mvc\Reply\AbstractReply
     */
    public function actionEdit(ParameterBag $params)
    {
        $reply = parent::actionEdit($params);

        if ($reply instanceof View) {
            /** @var \XF\Entity\User $user */
            $user = $reply->getParam('user');

            /** @var \SV\UserEssentials\Repository\UsernameChange $usernameChangeRepo */
            $usernameChangeRepo = \XF::repository('SV\UserEssentials:UsernameChange');
            $finder = $usernameChangeRepo->findUsernameChangesForUser($user);
            $previousUsernameChanges = $finder->fetch(3);
            $unseenUsernameChanges = ($finder->total() - $previousUsernameChanges->count());

            $reply->setParam('previousUsernameChanges', $previousUsernameChanges);
            $reply->setParam('unseenUsernameChanges', $unseenUsernameChanges);
        }

        return $reply;
    }

    /**
     * @param UserEntity $user
     *
     * @return FormAction
     */
    protected function userSaveProcess(UserEntity $user)
    {
        /** @var FormAction $action */
        $form = parent::userSaveProcess($user);

        if ($user->isUpdate()) {
            $username = $this->filter('user.username', 'str');
            if ($username != $user->username) {
                $usernameChangeCreator = $this->setupUsernameChangeCreate(
                    $user,
                    $username
                );

                $form->validate(function (FormAction $form) use ($usernameChangeCreator) {
                    if (!$usernameChangeCreator->validate($errors)) {
                        $form->logErrors($errors);
                    }
                });

                $form->apply(function () use ($usernameChangeCreator) {
                    $usernameChangeCreator->save();
                    $this->finalizeUsernameChangeCreate($usernameChangeCreator);
                });
            }

            $revertTitle = $this->filter('user.custom_title_revert', 'bool');
            if ($revertTitle) {
                $form->apply(function () use ($user) {
                    $user->revertUsernameChangeTitle();
                });
            }
        }

        return $form;
    }

    /**
     * @param UserEntity $user
     * @param string     $username
     * @return \SV\UserEssentials\Service\UsernameChange\Creator
     */
    protected function setupUsernameChangeCreate(UserEntity $user, $username)
    {
        /** @var \SV\UserEssentials\Service\UsernameChange\Creator $creator */
        $creator = $this->service(
            'SV\UserEssentials:UsernameChange\Creator',
            $user,
            $username
        );
        $creator->setAdminEdit(true);
        $creator->setPrivate($this->filter('sv_ue_private', 'bool'));

        return $creator;
    }

    /**
     * @param \SV\UserEssentials\Service\UsernameChange\Creator $creator
     */
    protected function finalizeUsernameChangeCreate(
        /** @noinspection PhpUnnecessaryFullyQualifiedNameInspection */
        \SV\UserEssentials\Service\UsernameChange\Creator $creator
    ) {
        // TODO: only apply user title if display_acp is true?
        $creator->applyUserTitle();
        if ($this->filter('sv_ue_notify', 'bool')) {
            $creator->sendNotifications();
        }
    }

    /**
     * @param int         $id
     * @param array|null  $with
     * @param string|null $phraseKey
     *
     * @return UserEntity
     */
    protected function assertUserExists($id, $with = null, $phraseKey = null)
    {
        $this->app->db()->query(
            "UPDATE xf_user AS user
                INNER JOIN xf_session_activity AS activity
                    ON (activity.user_id > 0 AND activity.user_id = user.user_id)
                SET user.last_activity = activity.view_date
                WHERE user.user_id = ?
                    AND user.last_activity < activity.view_date",
            $id
        );

        return parent::assertUserExists($id, $with, $phraseKey);
    }
}
