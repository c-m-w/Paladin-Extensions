<?php

namespace ThemeHouse\Bookmarks\XF\Entity;

class Node extends XFCP_Node
{
    use \ThemeHouse\Bookmarks\Entity\BookmarkableTrait;

    protected function canBookmarkExtra()
    {
        if ($this->node_type_id !== 'Forum') {
            return false;
        }

        return true;
    }

    protected function _postDelete()
    {
        parent::_postDelete();

        $repo = $this->repository('ThemeHouse\Bookmarks:Bookmark');
        $repo->fastDeleteBookmarksForContent('node', $this->node_id);
    }
}