<?php

namespace xenMade\LAU\XF\Repository;

use XF\Mvc\Entity\Finder;
use XF\Mvc\Entity\Repository;
use XF\Mvc\ParameterBag;

class Ip extends XFCP_Ip
{
    public function logIp($userId, $ip, $contentType, $contentId, $action = '')
    {
        if(\XF::app()->offsetExists('lau_loginlogout'))
        {
            return false;
        }

        $session = \XF::app()->session();
        if(!empty($session->offsetExists('lau_id')))
        {
            return false;

        }

        return parent::logIp($userId, $ip, $contentType, $contentId, $action);
    }
}
if(false)
{
    class XFCP_Ip extends \XF\Repository\Ip {}
}