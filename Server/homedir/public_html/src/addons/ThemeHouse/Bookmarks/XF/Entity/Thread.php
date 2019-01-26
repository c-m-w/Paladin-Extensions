<?php

namespace ThemeHouse\Bookmarks\XF\Entity;

class Thread extends XFCP_Thread
{
    use \ThemeHouse\Bookmarks\Entity\BookmarkableTrait;

    protected function _postDelete()
    {
        parent::_postDelete();

        $repo = $this->repository('ThemeHouse\Bookmarks:Bookmark');
        $repo->fastDeleteBookmarksForContent('thread', $this->thread_id);
    }
}