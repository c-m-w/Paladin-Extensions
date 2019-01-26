<?php

namespace xenMade\LAU\XF\Repository;

use XF\Mvc\Entity\Finder;
use XF\Mvc\Entity\Repository;
use XF\Mvc\ParameterBag;

class Thread extends XFCP_Thread
{
    public function markThreadReadByVisitor(\XF\Entity\Thread $thread, $newRead = null)
    {
        $session = \XF::app()->session();

        if(!$session->exists())
            return parent::markThreadReadByVisitor($thread, $newRead);

        if(
            $session->offsetExists('lau_id') &&
            $session->offsetExists('lau_stealth')
        )
        {
            return false;
        }

        return parent::markThreadReadByVisitor($thread, $newRead);
    }
}
if(false)
{
    class XFCP_Thread extends \XF\Repository\Thread {}
}