<?php

namespace ThemeHouse\Bookmarks\BookmarkHandler;

use ThemeHouse\Bookmarks\Entity\Bookmark;
use XF\Template\Templater;

class ResourceItem extends AbstractHandler
{
    protected $contentType = 'resource';

    public function canUse()
    {
        return isset($this->app->registry()['addOns']['XFRM']);
    }

    public function getEntityWith()
    {
        return ['User'];
    }

    protected function _renderIcon(Bookmark $bookmark, $type, Templater $templater)
    {
        /** @var \XFRM\Entity\ResourceItem $resource */
        $resource = $bookmark->Content;

        return $templater->renderMacro('public:th_bookmark_icon_macros_bookmarks', 'resource', [
            'resource' => $resource,
        ]);
    }

    protected function _renderBookmark(Bookmark $bookmark, $type, Array $options = [], Templater $templater)
    {
        $resource = $bookmark->Content;

        $params = [
            'bookmark' => $bookmark,
            'resource' => $resource,
            'category' => $resource->Category,

            'options' => $options,
        ];
        return $templater->renderTemplate('public:th_bookmark_row_resource_bookmarks', $params);
    }

    public function getContentUrl($content)
    {
        return \XF::app()->router()->buildLink('resources', $content);
    }

    public function getBookmarkPhrase($content)
    {
        return \XF::phrase('th_bookmark_resource_bookmarks');
    }

    public function getUnbookmarkPhrase($content)
    {
        return \XF::phrase('th_unbookmark_resource_bookmarks');
    }
}