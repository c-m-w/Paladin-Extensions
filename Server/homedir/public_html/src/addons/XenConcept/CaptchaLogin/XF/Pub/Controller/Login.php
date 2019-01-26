<?php

/*************************************************************************
 * Captcha login - XenConcept (c) 2017
 * All Rights Reserved.
 **************************************************************************
 * This file is subject to the terms and conditions defined in the Licence
 * Agreement available at Try it like it buy it :)
 *************************************************************************/

namespace XenConcept\CaptchaLogin\XF\Pub\Controller;

use XF\Mvc\Reply\View;

class Login extends XFCP_Login
{

    public function actionIndex()
    {
        $response = parent::actionIndex();

        if (!$response instanceof View)
        {
            return $response;
        }

        if ($this->options()->xc_captcha_login_enable_captcha)
        {
            $response->setParam('captcha', true);
        }

        return $response;
    }

    public function actionLogin()
    {
        $response = parent::actionLogin();

        if ($this->isPost())
        {
            $ip = $this->request->getIp();

            $input = $this->filter([
                'login' => 'str',
                'password' => 'str',
                'remember' => 'bool'
            ]);

            /** @var \XF\Service\User\Login $loginService */
            $loginService = $this->service('XF:User\Login', $input['login'], $ip);

            if ($this->options()->xc_captcha_login_enable_captcha && !$loginService->isLoginLimited($limitType))
            {
                if (!$this->captchaIsValid(true))
                {
                    $viewParams = [
                        'captcha' => true,
                        'login' => $input['login'],
                        'error' => \XF::phrase('did_not_complete_the_captcha_verification_properly')
                    ];
                    return $this->view('XF:Login\Form', 'login', $viewParams);
                }
            }

            return $response;
        }
        else
        {
            if ($response instanceof View)
            {
                if ($this->options()->xc_captcha_login_enable_captcha)
                {
                    $response->setParam('captcha', true);
                }

                return $response;
            }
        }
    }

}