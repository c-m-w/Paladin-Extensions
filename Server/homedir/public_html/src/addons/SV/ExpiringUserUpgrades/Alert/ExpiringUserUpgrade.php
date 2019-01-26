<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\ExpiringUserUpgrades\Alert;

use SV\ExpiringUserUpgrades\XF\Repository\UserUpgrade;
use XF\Alert\AbstractHandler;
use XF\Entity\UserAlert;
use XF\Mvc\Entity\Entity;

/**
 * Class ExpiringUserUpgrade
 *
 * @package SV\ExpiringUserUpgrades
 */
class ExpiringUserUpgrade extends AbstractHandler
{
    /**
     * @param Entity $entity
     * @param null   $error
     * @return bool
     */
    public function canViewContent(Entity $entity, &$error = null)
    {
        return true;
    }

    /**
     * @param             $action
     * @param UserAlert   $alert
     * @param Entity|null $content
     * @return array
     */
    public function getTemplateData($action, UserAlert $alert, Entity $content = null)
    {
        $data = parent::getTemplateData($action, $alert, $content);

        /** @var UserUpgrade $userUpgradeRepo */
        $userUpgradeRepo = \XF::repository('XF:UserUpgrade');

        $options = \XF::options();
        $upgradeUrl = $userUpgradeRepo->getUpgradeUrl();

        $data = array_merge($data, [
            'boardUrl'    => $options->boardUrl,
            'boardTitle'  => $options->boardTitle,
            'url'         => $upgradeUrl,
            'upgrade_url' => $upgradeUrl,
            'upgradeUrl'  => $upgradeUrl
        ]);

        return $data;
    }

    /**
     * @param $id
     * @return null|\XF\Mvc\Entity\ArrayCollection|Entity
     */
    public function getContent($id)
    {
        return \XF::app()->findByContentType('user', $id, $this->getEntityWith());
    }

    /**
     * @return string
     */
    public function getContentType()
    {
        return 'exup';
    }

    /**
     * @return int
     */
    public function getOptOutDisplayOrder()
    {
        return 60000;
    }
}