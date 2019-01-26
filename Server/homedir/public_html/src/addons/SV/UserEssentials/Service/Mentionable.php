<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\Service;

use SV\UserEssentials\Entity\MentionableInterface as EntityMentionableInterface;

/*
 * A trait for mentionable services.
 */
trait Mentionable
{
    /**
     * Service post-insert events.
     */
    public function afterInsert()
    {
        parent::afterInsert();
        /** @noinspection PhpParamsInspection */
        $this->getEntity()->addContentMentions($this);
    }

    /**
     * Service post-update events.
     */
    public function afterUpdate()
    {
        parent::afterUpdate();
        /** @noinspection PhpParamsInspection */
        $this->getEntity()->addContentMentions($this);
    }

    /**
     * @param array|string|null $types
     *
     * @return array
     */
    public function getNewContentMentions($types = null)
    {
        if (!\XF::options()->svSendEditedInMentions)
        {
            return [];
        }

        $mentions = $this->getEntity()->getContentMentions(false);
        return $mentions ? $mentions->getNewIds($types) : [];
    }

    /**
     * @return EntityMentionableInterface
     */
    protected function getEntity()
    {
        if (!property_exists($this, 'entityKey')) {
            $rootClass = \XF::extension()->resolveExtendedClassToRoot($this);
            throw new \LogicException(
                "Mentionable service must define 'entityKey' property ({$rootClass})"
            );
        }
        $key = $this->entityKey;

        $entity = $this->{$key};
        if (!($entity instanceof EntityMentionableInterface)) {
            $rootClass = \XF::extension()->resolveExtendedClassToRoot($entity);
            throw new \LogicException(
                "Entity must implement MentionableInterface ({$rootClass}), make sure the SV/UserEssentials add-on is enabled"
            );
        }

        return $entity;
    }
}
