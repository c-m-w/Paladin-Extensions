<?php

namespace ThemeHouse\Bookmarks\XFMG\Entity;

class MediaItem extends XFCP_MediaItem
{
    use \ThemeHouse\Bookmarks\Entity\BookmarkableTrait;

    protected function _postDelete()
    {
        parent::_postDelete();

        $repo = $this->repository('ThemeHouse\Bookmarks:Bookmark');
        $repo->fastDeleteBookmarksForContent('xfmg_media', $this->media_id);
    }
}