<?php

/*************************************************************************
 * Login As User - XenConcept (c) 2017
 * All Rights Reserved.
 **************************************************************************
 * This file is subject to the terms and conditions defined in the Licence
 * Agreement available at Try it like it buy it :)
 *************************************************************************/

namespace XenConcept\LoginAsUser\XF\Pub\Controller;

class Misc extends XFCP_Misc
{


    protected function setupLoginAsUser()
    {
        $username = $this->filter('username', 'str');
        $reason   = $this->filter('reason', 'str');

        /** @var \XenConcept\LoginAsUser\XF\ControllerPlugin\Login $loginPlugin */
        $loginPlugin = $this->plugin('XF:Login');

        if (!$username)
        {
            Throw $this->exception($this->error(\XF::phraseDeferred('xc_login_as_user_please_select_user')));
        }

        if (count(explode(',', $username)) != 1)
        {
            Throw $this->exception($this->error(\XF::phraseDeferred('xc_login_as_user_you_can_not_select_multiple_users')));
        }

        /**
         * @var \XF\Entity\User $user
         */
        $user = $this->getUserRepo()->getUserByNameOrEmail($username);

        if (!$user)
        {
            Throw $this->exception($this->error(\XF::phraseDeferred('xc_login_as_user_does_not_exist')));
        }

        $loginPlugin->loginAsUser($user, \XF::visitor());

        $options = $this->options();

        $sendConversation = $options->xc_login_as_user_send_conversation;

        if ($sendConversation)
        {
            $title   = $options->xc_login_as_user_conversation_title;
            $message = $options->xc_login_as_user_conversation_content;
            $convOptions = $options->xc_login_as_user_conversation_options;

            $message = str_replace('{username}', $username, $message);
            $message = str_replace('{reason}', $reason, $message);
            $message = str_replace(PHP_EOL, '<br>', $message);
            $bbCode = \XF\Html\Renderer\BbCode::renderFromHtml($message);
            $message = \XF::cleanString($bbCode);

            /** @var \XF\Service\Conversation\Creator $creator */
            $creator = $this->service('XF:Conversation\Creator', \XF::visitor());

            $optionsInput = [
                'open_invite' => $convOptions['messageOpenInvite'] ? 0 : 1,
                'conversation_open' => $convOptions['messageLocked'] ? 0 : 1
            ];

            \XF::dump($optionsInput);

            $creator->setRecipients($username);
            $creator->setContent($title, $message);
            $creator->setOptions($optionsInput);

            $creator->save();
        }

        //return;
    }

    public function actionLoginAsUser()
    {
        /** @var \XenConcept\LoginAsUser\XF\Entity\User $visitor */
        $visitor  = \XF::visitor();

        if (!$visitor->canLoginAsUser($error))
        {
            return $this->noPermission($error);
        }

        $userId = $this->filter('user_id', 'int');

        $user = null;

        if ($userId)
        {
            $user = $this->getUserRepo()->getVisitor($userId);
        }

        if ($this->isPost())
        {

            $this->setupLoginAsUser();

            return $this->redirect($this->buildLink('index'));
        }
        else
        {
            $viewParams = [
                'username' => $user['username'] ? $user['username'] : ''
            ];

            return $this->view('XenConcept\LoginAsUser:Misc\LoginAsUser', 'xc_login_as_user_misc_login_as_user', $viewParams);
        }
    }

    public function actionLogoutAsUser()
    {
        $session = $this->session();
        $sessionLoginAsUser = $session->get('login_as_user');

        if ($sessionLoginAsUser)
        {

            /** @var \XenConcept\LoginAsUser\XF\ControllerPlugin\Login $loginPlugin */
            $loginPlugin = $this->plugin('XF:Login');

            $loginPlugin->logoutAsUser();

            return $this->redirect($this->buildLink('index'));
        }

        return $this->redirect($this->buildLink('index'));
    }



    /**
     * @return \XF\Repository\User
     */
    protected function getUserRepo()
    {
        return $this->repository('XF:User');
    }
}