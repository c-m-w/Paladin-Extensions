<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\ApprovalQueue;

use XF\ApprovalQueue\AbstractHandler;
use XF\Entity\ApprovalQueue;
use XF\Mvc\Entity\Entity;

use SV\UserEssentials\Entity\UsernameChange as UsernameChangeEntity;
use SV\UserEssentials\XF\Entity\User;

/**
 * An approval queue handler for user name changes.
 */
class UsernameChange extends AbstractHandler
{
    /**
     * @param Entity $content
     * @param string $error
     * @return bool
     */
    protected function canViewContent(Entity $content, &$error = null)
    {
        return true;
    }

    /**
     * @param Entity $content
     * @param string $error
     * @return bool
     */
    protected function canActionContent(Entity $content, &$error = null)
    {
        /** @var User $visitor */
        $visitor = \XF::visitor();

        return $visitor->canApproveRejectUsername();
    }

    /**
     * @return array
     */
    public function getEntityWith()
    {
        return ['User'];
    }

    /**
     * @return string
     */
    public function getTemplateName()
    {
        return 'public:sv_ue_approval_item_unc';
    }

    /**
     * @param ApprovalQueue $unapprovedItem
     * @return array
     */
    public function getTemplateData(ApprovalQueue $unapprovedItem)
    {
        $templateData = parent::getTemplateData($unapprovedItem);

        /** @var \SV\UserEssentials\Entity\UsernameChange $content */
        $content = $unapprovedItem->Content;
        /** @var \XF\Entity\User $user */
        $user = $content->User;

        /** @var \SV\UserEssentials\Repository\UsernameChange $usernameChangeRepo */
        $usernameChangeRepo = \XF::repository('SV\UserEssentials:UsernameChange');
        $finder = $usernameChangeRepo->findUsernameChangesForList($user);
        $previousUsernameChanges = $finder->fetch(3);
        $unseenUsernameChanges = ($finder->total() - $previousUsernameChanges->count());

        $templateData['user'] = $user;
        $templateData['previousUsernameChanges'] = $previousUsernameChanges;
        $templateData['unseenUsernameChanges'] = $unseenUsernameChanges;

        return $templateData;
    }

    /**
     * @param UsernameChangeEntity $usernameChange
     */
    public function actionApprove(UsernameChangeEntity $usernameChange)
    {
        $note = $this->getInput('note', $usernameChange->unc_id);

        /** @var \SV\UserEssentials\Service\UsernameChange\Approver $approver */
        $approver = \XF::service(
            'SV\UserEssentials:UsernameChange\Approver',
            $usernameChange,
            $note
        );
        if ($usernameChange->canEditPrivacy())
        {
            $approver->setIsPrivate($this->getInput(
                'is_private',
                $usernameChange->unc_id
            ));
        }
        $approver->approve();

        \XF::app()->logger()->logModeratorAction(
            'unc',
            $usernameChange,
            'approved',
            ['note' => $note]
        );
    }

    /**
     * @param UsernameChangeEntity $usernameChange
     */
    public function actionReject(UsernameChangeEntity $usernameChange)
    {
        $note = $this->getInput('note', $usernameChange->unc_id);

        $usernameChange->status = 'denied';
        $usernameChange->moderator_id = \XF::visitor()->user_id;
        $usernameChange->moderation_date = \XF::$time;
        $usernameChange->moderator_note = $note;
        $usernameChange->save();

        /** @var \SV\UserEssentials\Service\UsernameChange\Notifier $notifier */
        $notifier = \XF::service(
            'SV\UserEssentials:UsernameChange\Notifier',
            $usernameChange
        );
        $notifier->setNotifyModerators([]);
        $notifier->setSkipUsers([\XF::visitor()->user_id]);
        $notifier->notify();

        \XF::app()->logger()->logModeratorAction(
            'unc',
            $usernameChange,
            'denied',
            ['note' => $note]
        );
    }
}
