<?php

/*************************************************************************
 * Captcha login - XenConcept (c) 2017
 * All Rights Reserved.
 **************************************************************************
 * This file is subject to the terms and conditions defined in the Licence
 * Agreement available at Try it like it buy it :)
 *************************************************************************/

namespace XenConcept\CaptchaLogin\XF\Admin\Controller;

use XF\Mvc\Reply\View;

class Login extends XFCP_Login
{

    public function actionForm()
    {
        $response =  parent::actionForm();

        if ($response instanceof View)
        {
            $options = $this->options();

            if ($options->xc_captcha_login_enable_captcha_admin)
            {
                $response->setParam('captcha', true);
            }
        }

        return $response;
    }

    public function actionLogin()
    {
        $options = $this->options();

        if ($options->xc_captcha_login_enable_captcha_admin)
        {
            if (!$this->captchaIsValid(true))
            {
                return $this->error( \XF::phrase('did_not_complete_the_captcha_verification_properly'));
            }

            return parent::actionLogin();
        }
        else
        {
            return parent::actionLogin();
        }
    }


}