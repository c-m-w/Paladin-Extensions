<?php

namespace ThemeHouse\Bookmarks\Import\Data;

use XF\Import\Data\AbstractEmulatedData;

class Bookmark extends AbstractEmulatedData
{
    public function getImportType()
    {
        return 'th_bookmark';
    }

    public function getEntityShortName()
    {
        return 'ThemeHouse\Bookmarks:Bookmark';
    }

    protected function preSave($oldId)
    {
        if ($this->content_type === 'post') {
            $post = $this->em()->find('XF:Post', $this->content_id);

            if ($post && $post->position === 0) {
                $this->set('content_type', 'thread');
                $this->set('content_id', $post->thread_id);
            }
        }
        parent::preSave($oldId);
    }
}