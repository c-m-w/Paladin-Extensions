<?php

namespace ThemeHouse\Bookmarks\Entity;

use XF\Mvc\Entity\Entity;
use XF\Mvc\Entity\Structure;

class Bookmark extends Entity
{
    public static function getStructure(Structure $structure)
    {
        $structure->table = 'xf_th_bookmark';
        $structure->shortName = 'ThemeHouse\Bookmarks:Bookmark';
        $structure->primaryKey = 'bookmark_id';
        $structure->columns = [
            'bookmark_id' => ['type' => self::UINT, 'autoIncrement' => true],
            'note' => ['type' => self::STR, 'default' => ''],
            'sticky' => ['type' => self::BOOL, 'default' => false],
            'public' => ['type' => self::BOOL, 'default' => true],
            'user_id' => ['type' => self::UINT, 'required' => true],
            'content_id' => ['type' => self::UINT, 'required' => true],
            'content_type' => ['type' => self::STR, 'maxLength' => 25, 'required' => true],
            'bookmark_date' => ['type' => self::UINT, 'default' => \XF::$time],
        ];
        $structure->getters = [
            'Content' => true,
        ];
        $structure->relations = [];
        $structure->options = [];

        return $structure;
    }

    protected function _preSave()
    {
        $handler = $this->getHandler();
        if ($this->isInsert()) {
            $handler->preCreateBookmark($this, $error);
        } else {
            $handler->preUpdateBookmark($this, $error);
        }

        if ($error) {
            $this->error($error);
            return false;
        }

        return true;
    }

    protected function _postSave()
    {
        $handler = $this->getHandler();
        if ($this->isInsert()) {
            $handler->postCreateBookmark($this);
        } else {
            $handler->postUpdateBookmark($this);
        }
    }

    protected function _preDelete()
    {
        $this->getHandler()->preDeleteBookmark($this, $error);

        if ($error) {
            $this->error($error);
            return false;
        }

        return true;
    }

    protected function _postDelete()
    {
        $this->getHandler()->postDeleteBookmark($this);
    }

    public function canView(&$error = null)
    {
        $handler = $this->getHandler();
        $content = $this->Content;

        if ($handler && $content) {
            return $handler->canViewContent($content, $error) && $handler->canViewBookmark($this, $error);;
        }

        return false;
    }

    public function render($type='popup', $options)
    {
        if (!is_array($options)) {
            $options = [];
        }

        $handler = $this->getHandler();
        $content = $this->Content;

        if ($handler && $content && $this->canView()) {
            return $handler->renderBookmark($this, $type, $options);
        }

        return false;
    }

    public function renderIcon($type='popup')
    {
        $handler = $this->getHandler();
        $content = $this->Content;

        if ($handler && $content && $this->canView()) {
            return $handler->renderIcon($this, $type);
        }

        return false;
    }

    public function getContentUrl()
    {
        $handler = $this->getHandler();
        $content = $this->Content;

        if ($handler && $content && $this->canView()) {
            return $handler->getContentUrl($content);
        }

        return false;
    }

    public function getContentTypePhraseName($plural = false)
    {
        $handler = $this->getHandler();

        if ($handler) {
            return $handler->getContentTypePhraseName($plural);
        }

        return false;
    }

    public function setContent(Entity $content = null)
    {
        $this->_getterCache['Content'] = $content;
    }

    /**
     * @return null|Entity
     */
    public function getContent()
    {
        $handler = $this->getHandler();
        return $handler ? $handler->getContent($this->content_id) : null;
    }

    /**
     * @return \ThemeHouse\Bookmarks\BookmarkHandler\AbstractHandler
     */
    public function getHandler()
    {
        return $this->getBookmarkRepo()->getHandlerForContentType($this->content_type);
    }

    /**
     * @return \ThemeHouse\Bookmarks\Repository\Bookmark
     */
    protected function getBookmarkRepo()
    {
        return $this->repository('ThemeHouse\Bookmarks:Bookmark');
    }
}