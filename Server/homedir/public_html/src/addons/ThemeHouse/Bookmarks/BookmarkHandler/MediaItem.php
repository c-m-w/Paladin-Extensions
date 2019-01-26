<?php

namespace ThemeHouse\Bookmarks\BookmarkHandler;

use ThemeHouse\Bookmarks\Entity\Bookmark;
use XF\Template\Templater;

class MediaItem extends AbstractHandler
{
    protected $contentType = 'xfmg_media';

    public function canUse()
    {
        return isset($this->app->registry()['addOns']['XFMG']);
    }

    public function getEntityWith()
    {
        return ['User'];
    }

    protected function _renderIcon(Bookmark $bookmark, $type, Templater $templater)
    {
        /** @var \XFMG\Entity\MediaItem $media */
        $media = $bookmark->Content;

        return $templater->renderMacro('public:th_bookmark_icon_macros_bookmarks', 'xfmg_media', [
            'media' => $media,
        ]);
    }

    protected function _renderBookmark(Bookmark $bookmark, $type, Array $options = [], Templater $templater)
    {
        $media = $bookmark->Content;

        $params = [
            'bookmark' => $bookmark,
            'media' => $media,

            'options' => $options,
        ];
        return $templater->renderTemplate('public:th_bookmark_row_xfmg_media_bookmarks', $params);
    }

    public function getContentUrl($content)
    {
        return \XF::app()->router()->buildLink('media', $content);
    }

    public function getBookmarkPhrase($content)
    {
        return \XF::phrase('th_bookmark_media_bookmarks');
    }

    public function getUnbookmarkPhrase($content)
    {
        return \XF::phrase('th_unbookmark_media_bookmarks');
    }
}