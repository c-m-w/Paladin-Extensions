<?php

/*************************************************************************
 * Login As User - XenConcept (c) 2017
 * All Rights Reserved.
 **************************************************************************
 * This file is subject to the terms and conditions defined in the Licence
 * Agreement available at Try it like it buy it :)
 *************************************************************************/

namespace XenConcept\LoginAsUser\XF\Entity;

class User extends XFCP_User
{

    public function canLoginAsUser(&$error = null)
    {
        return $this->hasPermission('general', 'loginAsUser');
    }

}