<?php

namespace ThemeHouse\Bookmarks\Entity;

trait BookmarkableTrait
{
    public function canBookmark()
    {
        $options = \XF::options();
        $visitor = \XF::visitor();

        if (!$visitor->user_id) {
            return false;
        }

        if (!$visitor->hasPermission('th_bookmarks', 'canBookmark')) {
            return false;
        }

        if (!in_array($this->getEntityContentType(), $options->th_enableContentTypes_bookmarks)) {
            return false;
        }

        return $this->canBookmarkExtra();
    }

    protected function canBookmarkExtra()
    {
        return true;
    }
}