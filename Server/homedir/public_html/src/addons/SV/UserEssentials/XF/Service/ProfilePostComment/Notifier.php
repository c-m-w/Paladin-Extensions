<?php

namespace SV\UserEssentials\XF\Service\ProfilePostComment;

/**
 * Extends \XF\Service\ProfilePostComment\Notifier
 */
class Notifier extends XFCP_Notifier
{
    public function setNotifyProfileOwner(array $mentioned)
    {
        $this->notifyProfileOwner = \array_unique($mentioned);
    }

    public function setNotifyProfilePostAuthor(array $mentioned)
    {
        $this->notifyProfilePostAuthor = \array_unique($mentioned);
    }
}