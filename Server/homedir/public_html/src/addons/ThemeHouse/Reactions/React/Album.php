<?php

namespace ThemeHouse\Reactions\React;

use XF\Mvc\Entity\Entity;
use ThemeHouse\Reactions\Entity\ReactedContent;

class Album extends AbstractHandler
{
    protected $statHandlerKey = 'react_album_item';

    public function reactsCounted(Entity $entity)
    {
        return ($entity->album_state == 'visible');
    }

    public function getAddOnId()
    {
        return 'XFMG';
    }

    public function getListTitle(Entity $entity)
    {
        return \XF::phrase('threactions_members_who_reacted_album_x', ['title' => $entity->title]);
    }

    public function getLinkDetails()
    {
        return [
            'link' => 'album'
        ];
    }

    public function canReactContent(Entity $entity, ReactedContent $react = null, &$error = null)
    {
        if ($entity->album_state != 'visible') {
            return false;
        }

        return parent::canReactContent($entity, $react, $error);
    }

    public function getStateField()
    {
        return 'album_state';
    }

    public function isPublic()
    {
        return true;
    }
}