<?php

namespace ThemeHouse\Bookmarks\BookmarkHandler;

use ThemeHouse\Bookmarks\Entity\Bookmark;
use XF\Template\Templater;

class Node extends AbstractHandler
{
    protected $contentType = 'node';

    public function getEntityWith()
    {
        $visitor = \XF::visitor();

        return ['Permissions|' . $visitor->permission_combination_id];
    }

    protected function _renderIcon(Bookmark $bookmark, $type, Templater $templater)
    {
        $extras = [];
        $extras = $bookmark->Content->getNodeListExtras();
        $params = [
            'extras' => $extras,
            'node' => $bookmark->Content,
            'hasThNodes' => (isset($addOns['ThemeHouse/Nodes']) ? true : false),
        ];

        return $templater->renderTemplate('public:th_node_icon_bookmarks', $params);
    }

    protected function _renderBookmark(Bookmark $bookmark, $type, Array $options = [], Templater $templater)
    {
        $params = [
            'bookmark' => $bookmark,
            'node' => $bookmark->Content,

            'options' => $options,
        ];
        return $templater->renderTemplate('public:th_bookmark_row_node_bookmarks', $params);
    }

    public function getContent($id)
    {
        $data = \XF::finder('XF:Node')->where('node_id', '=', $id);

        if (is_array($id)) {
            $nodes = $data->fetch();
            $this->_getNodeRepository()->loadNodeTypeDataForNodes($nodes);

            return $nodes;
        } else {
            return $data->fetchOne();
        }
    }

    public function getContentUrl($content)
    {
        /** @var \XF\Entity\Node $content */
        $route = $content->getRoute();

        return \XF::app()->router()->buildLink($route, $content);
    }

    public function getBookmarkPhrase($content)
    {
        return \XF::phrase('th_bookmark_forum_bookmarks');
    }

    public function getUnbookmarkPhrase($content)
    {
        return \XF::phrase('th_unbookmark_forum_bookmarks');
    }

    /**
     * @return \XF\Repository\Node
     */
    protected function _getNodeRepository()
    {
        return $this->repository('XF:Node');
    }
}