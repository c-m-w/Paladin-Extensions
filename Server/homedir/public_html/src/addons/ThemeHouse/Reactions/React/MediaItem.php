<?php

namespace ThemeHouse\Reactions\React;

use XF\Mvc\Entity\Entity;
use ThemeHouse\Reactions\Entity\ReactedContent;

class MediaItem extends AbstractHandler
{
    protected $statHandlerKey = 'react_media_item';

    public function reactsCounted(Entity $entity)
    {
        return ($entity->media_state == 'visible');
    }

    public function getAddOnId()
    {
        return 'XFMG';
    }

    public function getListTitle(Entity $entity)
    {
        return \XF::phrase('th_members_who_reacted_media_x_reactions', ['title' => $entity->title]);
    }

    public function getLinkDetails()
    {
        return [
            'link' => 'media'
        ];
    }

    public function canReactContent(Entity $entity, ReactedContent $react = null, &$error = null)
    {
        $visitor = \XF::visitor();

        if ($entity->media_state != 'visible') {
            return false;
        }

        return parent::canReactContent($entity, $react, $error);
    }

    public function getStateField()
    {
        return 'media_state';
    }

    public function isPublic()
    {
        return true;
    }
}