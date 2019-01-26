<?php

namespace xenMade\AED\XF\ControllerPlugin;

class Login extends XFCP_Login
{
    // Kompatibilität mit dem LAU2 Add-On
    public $lau_login = false;

    public function completeLogin(\XF\Entity\User $user, $remember)
    {
        $res = parent::completeLogin($user, $remember);

        try
        {
            // LAU Login?
            if(!empty($this->lau_login))
            {
                return $res;
            }

            $options = \XF::options();

            $excludeGroups = $options->aed_ExcludeUserGroups;
            $excludeUsers = $options->aed_ExcludeUsers;

            //Prüfe zuerst ob der User Sonderstatus hat :)
            if(!$user->isMemberOf($excludeGroups) && !in_array($user->user_id, $excludeUsers))
            {
                $doubleAccount = 'user_cookie';

                $aedCookie = (int)$this->request->getCookie($this->getAEDCookieName());

                if(!$aedCookie)
                {
                    $aedCookie = $user->user_id;
                }

                $fromUserId = $aedCookie;

                $userIp = \XF::app()->request()->getIp();
                $userInfos = [
                    'local_ip' => gethostbyname(gethostname()),
                    'user_ip' =>  $userIp,
                    'host_name' =>  gethostbyname($userIp),
                    'browser' =>  (!empty($_SERVER['HTTP_USER_AGENT']) ? $_SERVER['HTTP_USER_AGENT'] : 'Unknow'),
                ];

                $md5UserInfos = md5(implode(',', $userInfos));

                /** @var \xenMade\AED\Repository\AEDLog $aedRepo */
                $aedFinder = $this->finder('xenMade\AED:AEDLog')
                    ->order('login_date', 'DESC');

                $aedFound = $aedFinder
                    ->whereOr(
                        [
                            ['user_fingerprint', '=', $md5UserInfos],
                            ['from_user_id', '!=', 'to_user_id']
                        ],
                        [
                            ['user_fingerprint', '=', $md5UserInfos],
                            ['from_user_id', '=', 'to_user_id']
                        ]
                    )
                    ->fetchOne();

                if($aedFound)
                {
                    $doubleAccount = 'user_fingerprint';
                }

                if(!$aedFound)
                {
                    $doubleAccount = 'user_ip';

                    $aedFinder->resetWhere();

                    $aedFound = $aedFinder
                        ->whereOr(
                            [
                                ['ip_address', '=', \XF\Util\Ip::convertIpStringToBinary($userIp)],
                                ['from_user_id', '!=', 'to_user_id']
                            ],
                            [
                                ['ip_address', '=', \XF\Util\Ip::convertIpStringToBinary($userIp)],
                                ['from_user_id', '=', 'to_user_id']
                            ]
                        )
                        ->where('login_date', '>=', \XF::$time - 3637440)
                        ->fetchOne();
                }

                if($aedFound)
                {
                    $fromUserId = $aedFound->from_user_id;
                }

                if($fromUserId != $user->user_id)
                {
                    // Write LoginLog
                    $this->writeAEDLog($md5UserInfos, $userIp, $user->user_id, $fromUserId);

                    if($options->aed_Alert['mode'] == 'thread')
                    {
                        $this->writeThread($fromUserId, $user->user_id);
                    }
                    elseif($options->aed_Alert['mode'] == 'conversation')
                    {
                        $this->writeConversation($fromUserId, $user->user_id);
                    }

                }
            }

        }
        catch (\Exception $e)
        {
            if(\XF::$debugMode)
                \XF::app()->logException($e);
        }

        return $res;
    }

    protected function setCookie($userId)
    {
        \XF::app()->response()->setCookie($this->getAEDCookieName(), $userId, \XF::options()->aed_CookieLifeTime * 86400);
    }

    protected function clearCookieSkipList()
    {
        $res = parent::clearCookieSkipList();

        $res[] = $this->getAEDCookieName();

        return $res;
    }

    protected function getAEDCookieName()
    {
        $cookieName = \XF::options()->aed_CookieName;

        if(!$cookieName)
        {
            $cookieName = 'aid';
        }

        return $cookieName;
    }

    protected function writeAEDLog($md5UserInfos, $userIp, $userId, $toUserId)
    {
        $aedEntry = $this->em()->create('xenMade\AED:AEDLog');
        $aedEntry->set('user_fingerprint', $md5UserInfos);
        $aedEntry->set('from_user_id', $userId);
        $aedEntry->set('to_user_id', $toUserId);
        $aedEntry->set('ip_address', \XF\Util\Ip::convertIpStringToBinary($userIp));
        $aedEntry->save();

        $this->setCookie($userId);
    }

    protected function writeThread($fromUserId, $toUserId)
    {
        $options = \XF::options();

        if(empty($options->aed_Alert['thread_user']) || empty($options->aed_Alert['node_id']))
        {
            return;
        }

        /** @var \XF\Entity\User $user */
        $user = $this->finder('XF:User')->where('username', $options->aed_Alert['thread_user'])->fetchOne();

        if(!$user)
        {
            return;
        }

        // node Finder
        $nodeFinder = \XF::app()->em()->getFinder('XF:Forum');
        $nodeFinder->with('Node', true);
        $nodeFinder->where('node_id', $options->aed_Alert['node_id']);

        /** @var \XF\Entity\Forum $forum */
        $forum = $nodeFinder->fetchOne();

        if(!$forum)
        {
            return;
        }

        /** @var \XF\Entity\User $fromUser */
        $fromUser = \XF::app()->find('XF:User', $fromUserId);

        /** @var \XF\Entity\User $toUse */
        $toUse = \XF::app()->find('XF:User', $toUserId);

        if(!$fromUser || !$toUse)
        {
            return;
        }

        $title = \XF::phrase('aed_thread_title', ['from_username' => $fromUser->username]);
        $message = \XF::phrase('aed_thread_message',
            [
                'to_username' => '[USER=' . $toUse->user_id . ']@' . $toUse->username . '[/USER]',
                'from_username' => '[USER=' . $fromUser->user_id . ']@' . $fromUser->username . '[/USER]'
            ]
        );

        if(!$title || !$message)
            return;

        /** @var \xenMade\AED\Service\Thread\CreatorSimple  $creator */
        $creator = \XF::service('xenMade\AED:Thread\CreatorSimple', $forum, $user);
        $creator->setContent($title, $message);
        $creator->setIsAutomated();
        $creator->save();

        return $creator->getThread();
    }

    protected function writeConversation($fromUserId, $toUserId)
    {
        $options = \XF::options();

        if(empty($options->aed_Alert['con_starter']) || empty($options->aed_Alert['con_participants']))
        {
            return;
        }

        $starter = $options->aed_Alert['con_starter'];

        $starterUser = null;
        if ($starter)
        {
            /** @var \XF\Entity\User $user */
            $starterUser = $this->finder('XF:User')->where('username', $options->aed_Alert['con_starter'])->fetchOne();
        }

        if (!$starterUser)
        {
            \XF::logError('Cannot send welcome message as there are no valid participants to send the message from.');
            return;
        }

        $participants = $options->aed_Alert['con_participants'];

        $recipients = null;
        if ($participants)
        {
            $participants = preg_split('#,#', $participants, -1, PREG_SPLIT_NO_EMPTY);

            /** @var \XF\Repository\User $userRepo */
            $userRepo = $this->repository('XF:User');
            $recipients = $userRepo->getUsersByNames($participants);
        }

        if(empty($recipients))
            return;

        /** @var \XF\Entity\User $fromUser */
        $fromUser = \XF::app()->find('XF:User', $fromUserId);

        /** @var \XF\Entity\User $toUse */
        $toUse = \XF::app()->find('XF:User', $toUserId);

        if(!$fromUser || !$toUse)
        {
            return;
        }

        $title = \XF::phrase('aed_thread_title', ['from_username' => $fromUser->username]);
        $message = \XF::phrase('aed_thread_message',
            [
                'to_username' => '[USER=' . $toUse->user_id . ']@' . $toUse->username . '[/USER]',
                'from_username' => '[USER=' . $fromUser->user_id . ']@' . $fromUser->username . '[/USER]'
            ]
        );

        /** @var \XF\Service\Conversation\Creator $conversationCreator */
        $conversationCreator = $this->service('XF:Conversation\Creator', $starterUser);
        $conversationCreator->setRecipientsTrusted($recipients);
        $conversationCreator->setContent($title, $message);
        $conversationCreator->setIsAutomated();
        $conversationCreator->save();
        $conversationCreator->sendNotifications();
    }

    protected function prepareTokens(\XF\Entity\User $user)
    {
        return [
            '{name}' => $user->username,
            '{email}' => $user->email,
            '{id}' => $user->user_id
        ];
    }

}
if(false)
{
    class XFCP_Login extends \XF\ControllerPlugin\Login {}
}