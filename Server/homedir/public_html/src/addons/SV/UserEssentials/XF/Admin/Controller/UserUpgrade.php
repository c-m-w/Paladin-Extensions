<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\XF\Admin\Controller;

use XF\Entity\UserUpgrade as UserUpgradeEntity;

/*
 * Extends \XF\Admin\Controller\UserUpgrade
 */
class UserUpgrade extends XFCP_UserUpgrade
{
    /**
     * @param UserUpgradeEntity $upgrade
     *
     * @return \XF\Mvc\FormAction
     */
    protected function upgradeSaveProcess(UserUpgradeEntity $upgrade)
    {
        /** @var \SV\UserEssentials\XF\Entity\UserUpgrade $upgrade */
        /** @var \XF\Mvc\FormAction $form */
        $form = parent::upgradeSaveProcess($upgrade);

        $form->setup(function () use ($upgrade) {
            $upgrade->quantity = $this->filter('quantity', 'uint');
        });

        return $form;
    }
}
