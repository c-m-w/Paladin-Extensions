<?php

namespace ThemeHouse\Bookmarks\Finder;

use XF\Mvc\Entity\Finder;

class Bookmark extends Finder
{
    public function user($userId)
    {
        $this->where('user_id', '=', $userId);

        return $this;
    }

    public function isPublic()
    {
        $this->where('public', '=', true);

        return $this;
    }

    public function sticky()
    {
        $this->recent();
        $this->where('sticky', '=', true);

        return $this;
    }

    public function recent()
    {
        $this->order('sticky', 'desc');
        $this->order('bookmark_date', 'desc');

        return $this;
    }

    public function forContentType($contentType)
    {
        if ($contentType) {
            $this->where('content_type', '=', $contentType);
        }

        return $this;
    }
}