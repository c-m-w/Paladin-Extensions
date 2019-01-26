<?php

namespace xenMade\LAU\XF\Repository;

use XF\Mvc\Entity\Finder;
use XF\Mvc\Entity\Repository;
use XF\Mvc\ParameterBag;

class Conversation extends XFCP_Conversation
{
    public function markUserConversationRead(\XF\Entity\ConversationUser $userConv, $newRead = null)
    {
        $session = \XF::app()->session();

        if(!$session->exists())
            return parent::markUserConversationRead($userConv, $newRead);

        if(
            $session->offsetExists('lau_id') &&
            $session->offsetExists('lau_stealth')
        )
        {
            return false;
        }

        return parent::markUserConversationRead($userConv, $newRead);
    }
}
if(false)
{
    class XFCP_Conversation extends \XF\Repository\Conversation {}
}