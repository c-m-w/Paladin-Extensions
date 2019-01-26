<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\XF\Pub\Controller;

use XF\Mvc\ParameterBag;

use SV\UserEssentials\XF\Entity\User;

/**
 * Extends \XF\Pub\Controller\Member
 */
class Member extends XFCP_Member
{
    /**
     * @param ParameterBag $params
     *
     * @return \XF\Mvc\Reply\AbstractReply
     */
    public function actionView(ParameterBag $params)
    {
        $reply = parent::actionView($params);

        if (\XF::options()->svDisplayMiniAvatars && $reply instanceof \XF\Mvc\Reply\View) {
            /** @var \XF\Mvc\Entity\AbstractCollection $profilePosts */
            $profilePosts = $reply->getParam('profilePosts');
            if ($profilePosts->count()) {
                $collections = [$profilePosts];
                foreach ($profilePosts as $profilePost) {
                    if ($profilePost->Comments) {
                        $collections[] = $profilePost->Comments;
                    }
                }

                /** @var \SV\UserEssentials\Repository\ContentMentions $mentionsRepo */
                $mentionsRepo = $this->repository('SV\UserEssentials:ContentMentions');
                $mentionsRepo->getMentionEntities('m', ...$collections);
                $mentionsRepo->getMentionEntities('mg', ...$collections);
            }
        }

        return $reply;
    }

    /**
     * @param ParameterBag $params
     * @return \XF\Mvc\Reply\AbstractReply
     */
    public function actionUsernameChanges(ParameterBag $params)
    {
        /** @var User $visitor */
        $visitor = \XF::visitor();
        /** @var User $user */
        /** @noinspection PhpUndefinedFieldInspection */
        $user = $this->assertViewableUser($params->user_id);
        if (!$visitor->canViewUsernameChanges($user))
        {
            return $this->noPermission();
        }

        /** @var \SV\UserEssentials\Repository\UsernameChange $usernameChangeRepo */
        $usernameChangeRepo = $this->repository('SV\UserEssentials:UsernameChange');
        $usernameChangeFinder = $usernameChangeRepo->findUsernameChangesForList($user);

        $usernameChanges = $usernameChangeFinder->fetch();
        $usernameChanges = $usernameChanges->filter(function ($usernameChange) {
            /** @var \SV\UserEssentials\Entity\UsernameChange $usernameChange */
            return $usernameChange->canViewInList();
        });
        if (!$usernameChanges->count())
        {
            return $this->message(\XF::phrase(
                'sv_ue_this_member_has_not_changed_their_user_name'
            ));
        }

        $viewParams = [
            'user'            => $user,
            'usernameChanges' => $usernameChanges
        ];

        return $this->view(
            'XF:Member\UsernameChanges',
            'sv_ue_member_username_changes',
            $viewParams
        );
    }

    /**
     * @return \XF\Mvc\Reply\AbstractReply
     */
    public function actionUsernameChange()
    {
        $uncId = $this->filter('unc_id', 'uint');
        $usernameChange = $this->assertViewableUsernameChange(
            $uncId,
            ['User', 'Moderator']
        );

        /** @var \SV\UserEssentials\XF\Entity\User $user */
        $user = $usernameChange->User;
        if (!$user)
        {
            return $this->notFound();
        }

        if ($this->isPost())
        {
            if (!$usernameChange->canEditPrivacy())
            {
                return $this->noPermission();
            }

            $isPrivate = $this->filter('is_private', 'bool');
            if ($isPrivate !== $usernameChange->is_private) {
                /** @var \XF\Db\AbstractAdapter $db */
                $db = $this->app->db();
                $db->beginTransaction();

                $usernameChange->is_private = $isPrivate;
                $usernameChange->save(true, false);

                if ($usernameChange->isLastUsernameChange()) {
                    if ($usernameChange->is_private) {
                        $user->revertUsernameChangeTitle();
                    } else {
                        $usernameChange->applyUserTitle();
                    }
                }

                $db->commit();
            }

            return $this->redirect($this->getDynamicRedirect());
        }

        $viewParams = [
            'user'           => $user,
            'moderator'      => $usernameChange->Moderator,
            'usernameChange' => $usernameChange
        ];

        return $this->view(
            'XF:Member\UsernameChange',
            'sv_ue_username_change_info',
            $viewParams
        );
    }

    /**
     * @param ParameterBag $params
     * @return \XF\Mvc\Reply\AbstractReply
     */
    public function actionTags(ParameterBag $params)
    {
        /** @var User $user */
        /** @noinspection PhpUndefinedFieldInspection */
        $user = $this->assertViewableUser($params->user_id);
        if (!$user->canEditTags())
        {
            return $this->noPermission();
        }

        /** @var \XF\Service\Tag\Changer $tagger */
        $tagger = $this->service('XF:Tag\Changer', 'user', $user);

        if ($this->isPost())
        {
            $tagger->setEditableTags($this->filter('tags', 'str'));
            if ($tagger->hasErrors())
            {
                return $this->error($tagger->getErrors());
            }

            $tagger->save();

            return $this->redirect($this->getDynamicRedirect(
                $this->buildLink('members', $user)
            ));
        }
        else
        {
            $grouped = $tagger->getExistingTagsByEditability();

            $viewParams = [
                'user'           => $user,
                'editableTags'   => $grouped['editable'],
                'uneditableTags' => $grouped['uneditable']
            ];

            return $this->view('XF:Member\Tags', 'sv_ue_member_tags', $viewParams);
        }
    }

    /**
     * @param int   $id
     * @param array $extraWith
     * @return \SV\UserEssentials\Entity\UsernameChange
     * @throws \XF\Mvc\Reply\Exception
     */
    protected function assertViewableUsernameChange($id, array $extraWith = [])
    {
        /** @var \SV\UserEssentials\Entity\UsernameChange $usernameChange */
        $usernameChange = $this->em()->find(
            'SV\UserEssentials:UsernameChange',
            $id,
            $extraWith
        );
        if (!$usernameChange)
        {
            throw $this->exception($this->notFound());
        }

        if (!$usernameChange->canView($error))
        {
            throw $this->exception($this->noPermission($error));
        }

        return $usernameChange;
    }
}
