<?php

namespace ThemeHouse\Reactions\React;

use XF\Mvc\Entity\Entity;
use ThemeHouse\Reactions\Entity\ReactedContent;

class ResourceUpdate extends AbstractHandler
{
    protected $statHandlerKey = 'react_resource_update';

    public function reactsCounted(Entity $entity)
    {
        return ($entity->message_state == 'visible');
    }

    public function getAddOnId()
    {
        return 'XFRM';
    }

    public function getTitle()
    {
        return \XF::phrase('xfrm_resources');
    }

    public function getListTitle(Entity $entity)
    {
        return \XF::phrase('th_members_who_reacted_resource_x_reactions', ['title' => $entity->Resource->title]);
    }

    public function getLinkDetails()
    {
        return [
            'link' => 'resources'
        ];
    }

    public function canReactContent(Entity $entity, ReactedContent $react = null, &$error = null)
    {
        $visitor = \XF::visitor();

        if ($entity->message_state != 'visible') {
            return false;
        }

        if (!$entity->isDescription()) {
            return false;
        }

        return parent::canReactContent($entity, $react, $error);
    }

    public function getStateField()
    {
        return 'message_state';
    }

    public function isPublic()
    {
        return true;
    }
}