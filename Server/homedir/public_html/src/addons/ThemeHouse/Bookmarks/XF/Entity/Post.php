<?php

namespace ThemeHouse\Bookmarks\XF\Entity;

use XF\Mvc\Entity\Entity;
use XF\Mvc\Entity\Structure;

class Post extends XFCP_Post
{
    use \ThemeHouse\Bookmarks\Entity\BookmarkableTrait;

    protected function canBookmarkExtra()
    {
        if ($this->isFirstPost()) {
            return false;
        }

        return true;
    }

    protected function _postDelete()
    {
        parent::_postDelete();

        $repo = $this->repository('ThemeHouse\Bookmarks:Bookmark');
        $repo->fastDeleteBookmarksForContent('post', $this->post_id);
    }
}