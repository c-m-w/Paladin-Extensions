<?php

namespace ThemeHouse\Bookmarks\XFRM\Entity;

class ResourceItem extends XFCP_ResourceItem
{
    use \ThemeHouse\Bookmarks\Entity\BookmarkableTrait;

    protected function _postDelete()
    {
        parent::_postDelete();

        $repo = $this->repository('ThemeHouse\Bookmarks:Bookmark');
        $repo->fastDeleteBookmarksForContent($this->getContentType(), $this->resource_id);
    }
}