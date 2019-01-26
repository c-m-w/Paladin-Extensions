<?php

namespace SV\UserEssentials\XF\Service\ProfilePost;



/**
 * Extends \XF\Service\ProfilePost\Notifier
 */
class Notifier extends XFCP_Notifier
{
    public function setNotifyInsert(array $mentioned)
    {
        $this->notifyInsert = \array_unique($mentioned);
    }
}