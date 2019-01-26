<?php

namespace xenMade\LAU\XF\Pub\Controller;

use XF\Mvc\ParameterBag;
use XF\Mvc\Reply\AbstractReply;
use XF\Mvc\Reply\View;
use XF\Util\Ip;

class Login extends XFCP_Login
{
    public function actionLauin()
    {
        $visitor = \XF::visitor();

        if (!$visitor->canUseLau() || !$visitor->user_id)
        {
            return $this->error(\XF::phrase('requested_page_not_found'));
        }

        $username = $this->filter('username', 'str');

        $options = \XF::options();

        // Session?  Ist das etwas zum Essen?
        $session = $this->session();

        if($session->offsetExists('lau_id'))
        {
            return $this->error(\XF::phrase('you_already_logged_in', ['link' => $this->buildLink('forums')]));
        }

        if ($this->isPost())
        {
            $user = $this->finder('XF:User')->where('username', $username)->fetchOne();

            if(empty($user) || !$user instanceof \XF\Entity\User)
            {
                return $this->error(\XF::phrase('requested_user_not_found'));
            }

            if($user->user_id == $visitor->user_id)
            {
                return $this->error(\XF::phrase('you_already_logged_in', ['link' => $this->buildLink('forums')]));
            }

            if(in_array($user->user_id, $options->lau_DisallowedUsers))
            {
                return $this->error(\XF::phrase('lau_not_allowed_login_with_username_x', ['username' => $user->username]));
            }

            $reason = $this->filter('reason', 'str');

            if(!$reason && $options->lau_ReasonRequired)
            {
                return $this->error(\XF::phrase('lau_please_enter_reason_for_login_to_user'));
            }

            $lauId = $visitor->user_id;
            $lauName = $visitor->username;

            if($session->offsetExists('lau_id'))
            {
                $lauId = $session->get('lau_id');
                $lauName = $session->get('lau_name');

                // Session exists? Dann erst einmal den alten Rotz ausloggen :)
                if($user->user_id == $lauId)
                {
                    return $this->rerouteController(__CLASS__, 'logout');
                }
            }

            /** @var \XF\ControllerPlugin\Login $loginPlugin */
            \XF::app()->offsetSet('lau_loginlogout', true);
            $loginPlugin = $this->plugin('XF:Login');
            $loginPlugin->lau_login = true;
            $loginPlugin->completeLogin($user, 0);


            $user->setOption('enqueue_rename_cleanup', false);

            $session->lau_id = $lauId;
            $session->lau_name = $lauName;
            $session->lau_to_name = $user->username;
            $session->lau_from_name = $visitor->username;

            if($options->lau_Stealth)
            {
                $session->lau_stealth = true;
            }

            $logData = [
                'to_user_id' => $user->user_id,
                'to_username' => $user->username,

                'from_user_id' => $visitor->user_id,
                'from_username' => $visitor->username,

                'reason' => $reason,
                'ip_address' => Ip::convertIpStringToBinary(\XF::app()->request()->getIp()),
            ];

            $loginLog = $this->em()->create('xenMade\LAU:LauLog');
            $loginLog->bulkSet($logData);
            $loginLog->save();

            return $this->redirect(
                $this->getDynamicRedirectIfNot($this->buildLink('login'))
            );
        }

        $viewParams = [
            'username' => $username
        ];

        return $this->view('xenmade/LAU:LAU', 'lau_login', $viewParams);
    }
}
if(false)
{
    class XFCP_Login extends \XF\Pub\Controller\Login {};
}