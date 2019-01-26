<?php

namespace NF\GiftUpgrades\XF\Admin\Controller;

use XF\Mvc\FormAction;

/**
 * Extends \XF\Admin\Controller\UserUpgrade
 */
class UserUpgrade extends XFCP_UserUpgrade
{
    protected function upgradeSaveProcess(\XF\Entity\UserUpgrade $upgrade)
    {
        $form = parent::upgradeSaveProcess($upgrade);

        $canGift = $this->filter('can_gift', 'bool');
        $form->setup(function(FormAction $form) use ($canGift, $upgrade)
        {
            $upgrade->can_gift = $canGift;
        });

        return $form;
    }
}