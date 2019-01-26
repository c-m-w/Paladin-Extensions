<?php

namespace ThemeHouse\Bookmarks\BookmarkHandler;

use ThemeHouse\Bookmarks\Entity\Bookmark;
use XF\Mvc\Entity\Entity;
use XF\Template\Templater;

class Thread extends AbstractHandler
{
    protected $contentType = 'thread';

    public function getEntityWith()
    {
        $visitor = \XF::visitor();

        return ['User', 'Forum', 'Forum.Node.Permissions|' . $visitor->permission_combination_id];
    }

    protected function _renderBookmark(Bookmark $bookmark, $type, Array $options = [], Templater $templater)
    {
        $params = [
            'bookmark' => $bookmark,
            'thread' => $bookmark->Content,
            'forum' => $bookmark->Content->Forum,

            'options' => $options,
        ];
        return $templater->renderTemplate('public:th_bookmark_row_thread_bookmarks', $params);
    }

    protected function _renderExtraCreateFields($content, Templater $templater)
    {
        return $this->_renderExtraEditFields($content, $templater);
    }

    protected function _renderExtraEditFields($content, Templater $templater)
    {
        $visitor = \XF::visitor();

        $watch = $content->Watch[$visitor->user_id];

        $params = [
            'content' => $content,
            'bookmark' => $content->Bookmark,

            'forum' => $content->Forum,

            'watch' => $watch,
        ];

        return $templater->renderTemplate('public:th_bookmark_edit_threadFields_bookmarks', $params);
    }

    protected function _renderExtraDeleteFields($content, Templater $templater)
    {
        $visitor = \XF::visitor();

        $watch = $content->Watch[$visitor->user_id];

        $params = [
            'content' => $content,
            'bookmark' => $content->Bookmark,

            'forum' => $content->Forum,

            'watch' => $watch,
        ];

        return $templater->renderTemplate('public:th_bookmark_delete_threadFields_bookmarks', $params);
    }

    protected function _postCreateBookmark(Bookmark $bookmark)
    {
        $this->_postUpdateBookmark($bookmark);
    }

    protected function _postUpdateBookmark(Bookmark $bookmark)
    {
        /** @var \XF\Entity\Thread $thread */
        $thread = $bookmark->Content;

        $watchThread = $this->app->request()->filter('watch_thread', 'bool');
        $emailSubscribe = $this->app->request()->filter('email_subscribe', 'bool');

        if ($watchThread) {
            if ($emailSubscribe) {
                $newState = 'watch_email';
            } else {
                $newState = 'watch_no_email';
            }
        } else {
            $newState = 'delete';
        }

        /** @var \XF\Repository\ThreadWatch $watchRepo */
        $watchRepo = $this->repository('XF:ThreadWatch');
        $watchRepo->setWatchState($thread, \XF::visitor(), $newState);
    }

    protected function _postDeleteBookmark(Bookmark $bookmark)
    {
        /** @var \XF\Entity\Thread $thread */
        $thread = $bookmark->Content;

        $unwatchThread = $this->app->request()->filter('unwatch_thread', 'bool');

        if ($unwatchThread) {
            $newState = 'delete';

            /** @var \XF\Repository\ThreadWatch $watchRepo */
            $watchRepo = $this->repository('XF:ThreadWatch');
            $watchRepo->setWatchState($thread, \XF::visitor(), $newState);
        }
    }

    protected function _renderIcon(Bookmark $bookmark, $type, Templater $templater)
    {
        return $templater->fnAvatar($templater, $escape, $bookmark->Content->User, 's');
    }

    public function getContentUrl($content)
    {
        return $this->app->router()->buildLink('threads', $content);
    }

    public function getBookmarkPhrase($content)
    {
        return \XF::phrase('th_bookmark_thread_bookmarks');
    }

    public function getUnbookmarkPhrase($content)
    {
        return \XF::phrase('th_unbookmark_thread_bookmarks');
    }
}