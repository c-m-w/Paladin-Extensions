<?php

namespace ThemeHouse\Reactions\React;

use XF\Mvc\Entity\Entity;
use ThemeHouse\Reactions\Entity\ReactedContent;

class MediaComment extends AbstractHandler
{
    protected $statHandlerKey = 'react_media_comment';

    public function reactsCounted(Entity $entity)
    {
        return ($entity->comment_state == 'visible');
    }

    public function getAddOnId()
    {
        return 'XFMG';
    }

    public function getListTitle(Entity $entity)
    {
        return \XF::phrase('threactions_members_who_reacted_media_comment_x', [
            'title' => $entity->content_type == 'xfmg_media' ? $entity->Media->title : $entity->Album->title,
            'user' => $entity->username
        ]);
    }

    public function getLinkDetails()
    {
        return [
            'link' => 'media/comments'
        ];
    }

    public function canReactContent(Entity $entity, ReactedContent $react = null, &$error = null)
    {
        if ($entity->comment_state != 'visible') {
            return false;
        }

        return parent::canReactContent($entity, $react, $error);
    }

    public function getStateField()
    {
        return 'comment_state';
    }

    public function isPublic()
    {
        return true;
    }
}