<?php

/*************************************************************************
 * Login As User - XenConcept (c) 2017
 * All Rights Reserved.
 **************************************************************************
 * This file is subject to the terms and conditions defined in the Licence
 * Agreement available at Try it like it buy it :)
 *************************************************************************/

namespace XenConcept\LoginAsUser\XF\Repository;


class Ip extends XFCP_Ip
{

    public function logIp($userId, $ip, $contentType, $contentId, $action = '')
    {

        if (\XF::session()->get('login_as_user'))
        {
            return 0;
        }

        return parent::logIp($userId, $ip, $contentType, $contentId, $action);
    }

}