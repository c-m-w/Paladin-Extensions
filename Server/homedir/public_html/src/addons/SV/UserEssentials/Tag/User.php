<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\Tag;

use SV\UserEssentials\XF\Entity\User as UserEntity;
use XF\Mvc\Entity\Entity;
use XF\Tag\AbstractHandler;

/**
 * A tag handler for users.
 */
class User extends AbstractHandler
{
    /**
     * @param Entity $entity
     * @throws \InvalidArgumentException if entity is not a User entity.
     * @return array
     */
    public function getPermissionsFromContext(Entity $entity)
    {
        if ($entity instanceof UserEntity)
        {
            $user = $entity;
        }
        else
        {
            throw new \InvalidArgumentException('Entity must be a User entity');
        }

        $edit = $user->canEditTags();

        $visitor = \XF::visitor();
        if (
            ($user->user_id == $visitor->user_id)
            && $visitor->hasPermission('general', 'useress_manageowntags')
        )
        {
            $removeOthers = true;
        }
        else
        {
            $removeOthers = $visitor->hasPermission(
                'general',
                'useress_managealltags'
            );
        }

        $minTotal = 0;

        return [
            'edit'         => $edit,
            'removeOthers' => $removeOthers,
            'minTotal'     => $minTotal
        ];
    }

    /**
     * @param Entity $entity
     * @return int
     */
    public function getContentDate(Entity $entity)
    {
        /** @var UserEntity $entity */
        return $entity->register_date;
    }

    /**
     * @param Entity $entity
     * @return string
     */
    public function getContentVisibility(Entity $entity)
    {
        /** @var UserEntity $entity */
        return $entity->visible;
    }

    /**
     * @param Entity $entity
     * @param string $error
     * @return bool
     */
    public function canViewContent(Entity $entity, &$error = null)
    {
        /** @var UserEntity $entity */
        return $entity->canViewFullProfile($error);
    }

    /**
     * @return string
     */
    public function getTemplateName()
    {
        return 'public:sv_ue_search_result_user';
    }

    /**
     * @param Entity $entity
     * @param array  $options
     * @return array
     */
    public function getTemplateData(Entity $entity, array $options = [])
    {
        return [
            'user'    => $entity,
            'options' => $options
        ];
    }

    /**
     * @param Entity $content
     * @param array  $cache
     */
    public function updateContentTagCache(Entity $content, array $cache)
    {
        /** @var UserEntity $content */
        $content->useress_tags = $cache;
        $content->save();
    }
}
