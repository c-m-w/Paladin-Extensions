<?php

namespace xenMade\LAU\XF\Repository;

use XF\Mvc\Entity\Finder;
use XF\Mvc\Entity\Repository;
use XF\Mvc\ParameterBag;

class Forum extends XFCP_Forum
{
    public function markForumReadByVisitor(\XF\Entity\Forum $forum, $newRead = null)
    {
        $session = \XF::app()->session();

        if(!$session->exists())
            return parent::markForumReadByVisitor($forum, $newRead);

        if(
            $session->offsetExists('lau_id') &&
            $session->offsetExists('lau_stealth')
        )
        {
            return false;
        }

        return parent::markForumReadByVisitor($forum, $newRead);
    }

    public function markForumTreeReadByVisitor(\XF\Entity\AbstractNode $baseNode = null, $newRead = null)
    {
        $session = \XF::app()->session();

        if(!$session->exists())
            return parent::markForumTreeReadByVisitor($baseNode, $newRead);

        if(
            $session->offsetExists('lau_id') &&
            $session->offsetExists('lau_stealth')
        )
        {
            return false;
        }


        return parent::markForumTreeReadByVisitor($baseNode, $newRead);
    }
}
if(false)
{
    class XFCP_Forum extends \XF\Repository\Forum {}
}