<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\ExpiringUserUpgrades\XF\Admin\Controller;

use SV\ExpiringUserUpgrades\Globals;

/**
 * Extends \XF\Admin\Controller\UserUpgrade
 */
class UserUpgrade extends XFCP_UserUpgrade
{
    /**
     * @param \XF\Entity\UserUpgrade $upgrade
     * @return \XF\Mvc\FormAction
     */
    protected function upgradeSaveProcess(\XF\Entity\UserUpgrade $upgrade)
    {
        $form = parent::upgradeSaveProcess($upgrade);

        $input = $this->filter([
            'exup_days' => 'int',
        ]);

        $form->setupEntityInput($upgrade, $input);

        return $form;
    }

    /**
     * @return \XF\Mvc\Reply\Redirect|\XF\Mvc\Reply\View
     */
    public function actionDowngrade()
    {
        Globals::$forceDowngradeAlert = true;
        // todo: indicate if an admin downgrade is a reveral or expire, with the option to force alerting
        Globals::$downgradeReason = 'expired_upgrade'; //'payment_reversal_upgrade';
        try
        {
            return parent::actionDowngrade();
        }
        finally
        {
            Globals::$forceDowngradeAlert = false;
            Globals::$downgradeReason = null;
        }
    }
}