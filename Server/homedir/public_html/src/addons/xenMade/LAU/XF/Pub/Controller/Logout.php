<?php

namespace xenMade\LAU\XF\Pub\Controller;

use XF\Mvc\ParameterBag;
use XF\Mvc\Reply\AbstractReply;
use XF\Mvc\Reply\View;

class Logout extends XFCP_Logout
{
    public function assertIpNotBanned() {}
    public function assertNotBanned() {}
    public function assertNotRejected($action) {}
    public function assertNotDisabled($action) {}

    public function actionLauout()
    {
        $session = $this->session();

        if ($session->exists())
        {
            if($session->offsetExists('lau_id'))
            {
                $userId = $session->get('lau_id');

                $user = $this->em()->find('XF:User', $userId);

                if(empty($user) || !$user instanceof \XF\Entity\User)
                {
                    return $this->error(\XF::phrase('requested_user_not_found'));
                }

                /** @var \XF\ControllerPlugin\Login $loginPlugin */
                \XF::app()->offsetSet('lau_loginlogout', true);
                $loginPlugin = $this->plugin('XF:Login');
                $loginPlugin->completeLogin($user, 0);

                $session = $this->session();

                unset($session->lau_id);
                unset($session->lau_name);
                unset($session->lau_stealth);
                unset($session->lau_to_name);
                unset($session->lau_from_name);
            }
            else
            {
                if(!\XF::visitor()->canUseLau())
                {
                    return $this->error(\XF::phrase('requested_page_not_found'));
                }
            }
        }
        else
        {
            if(!\XF::visitor()->canUseLau())
            {
                return $this->error(\XF::phrase('requested_page_not_found'));
            }
        }

        return $this->redirect(
            $this->getDynamicRedirectIfNot($this->buildLink('logout'))
        );
    }
}
if(false)
{
    class XFCP_Logout extends \XF\Pub\Controller\Logout {};
}