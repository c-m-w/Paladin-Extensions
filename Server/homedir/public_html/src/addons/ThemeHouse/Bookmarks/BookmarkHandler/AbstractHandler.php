<?php

namespace ThemeHouse\Bookmarks\BookmarkHandler;

use ThemeHouse\Bookmarks\Entity\Bookmark;
use XF\Mvc\Entity\Entity;
use XF\Template\Templater;

abstract class AbstractHandler
{
    protected $contentType;

    /** @var \XF\App */
    protected $app;

    public function __construct(\XF\App $app)
    {
        $this->app = $app;
    }

    public function getContent($id)
    {
        return $this->app->findByContentType($this->contentType, $id, $this->getEntityWith());
    }

    public function getContentTypePhraseName($plural = false, $render = true)
    {
        $phraseKey = \XF::app()->getContentTypePhraseName($this->contentType, $plural);

        if ($render) {
            return \XF::phrase($phraseKey);
        }

        return $phraseKey;
    }

    public function canViewContent(Entity $entity, &$error = null)
    {
        if (method_exists($entity, 'canView'))
        {
            return $entity->canView($error);
        }

        throw new \LogicException("Could not determine content viewability; please override");
    }

    public function canViewBookmark(Bookmark $bookmark, &$error = null)
    {
        return true;
    }

    public function canUse()
    {
        return true;
    }

    public function getContentType()
    {
        return $this->contentType;
    }

    public function renderIcon(Bookmark $bookmark, $type)
    {
        return $this->_renderIcon($bookmark, $type, $this->app->templater());
    }

    public function renderBookmark(Bookmark $bookmark, $type, Array $options = [])
    {
        return $this->_renderBookmark($bookmark, $type, $options, $this->app->templater());
    }

    public function renderExtraCreateFields($content)
    {
        return $this->_renderExtraCreateFields($content, $this->app->templater());
    }

    public function renderExtraEditFields($content)
    {
        return $this->_renderExtraEditFields($content, $this->app->templater());
    }

    public function renderExtraDeleteFields($content)
    {
        return $this->_renderExtraDeleteFields($content, $this->app->templater());
    }

    public function preCreateBookmark(Bookmark $bookmark, &$error = false)
    {
        return $this->_preCreateBookmark($bookmark, $error);
    }

    public function postCreateBookmark(Bookmark $bookmark)
    {
        return $this->_postCreateBookmark($bookmark);
    }

    public function preUpdateBookmark(Bookmark $bookmark, &$error = false)
    {
        return $this->_preUpdateBookmark($bookmark, $error);
    }

    public function postUpdateBookmark(Bookmark $bookmark)
    {
        return $this->_postUpdateBookmark($bookmark);
    }

    public function preDeleteBookmark(Bookmark $bookmark, &$error = false)
    {
        return $this->_preDeleteBookmark($bookmark, $error);
    }

    public function postDeleteBookmark(Bookmark $bookmark)
    {
        return $this->_postDeleteBookmark($bookmark);
    }

    public function getEntityWith()
    {
        return [];
    }

    public abstract function getContentUrl($content);
    public abstract function getBookmarkPhrase($content);
    public abstract function getUnbookmarkPhrase($content);

    protected abstract function _renderBookmark(Bookmark $bookmark, $type, Array $options = [], Templater $templater);

    protected function _renderIcon(Bookmark $bookmark, $type, Templater $templater)
    {
        return false;
    }

    protected function _preDeleteBookmark(Bookmark $bookmark, &$error)
    {
        return true;
    }

    protected function _postDeleteBookmark(Bookmark $bookmark)
    {
        return true;
    }

    protected function _preCreateBookmark(Bookmark $bookmark, &$error)
    {
        return true;
    }

    protected function _postCreateBookmark(Bookmark $bookmark)
    {
        return true;
    }

    protected function _preUpdateBookmark(Bookmark $bookmark, &$error)
    {
        return true;
    }

    protected function _postUpdateBookmark(Bookmark $bookmark)
    {
        return true;
    }

    protected function _renderExtraCreateFields($content, Templater $templater)
    {
        return false;
    }

    protected function _renderExtraEditFields($content, Templater $templater)
    {
        return false;
    }

    protected function _renderExtraDeleteFields($content, Templater $templater)
    {
        return false;
    }

    /**
     * @return \XF\Mvc\Entity\Manager
     */
    public function em()
    {
        return $this->app->em();
    }

    /**
     * @param string $type
     *
     * @return \XF\Mvc\Entity\Finder
     */
    public function finder($type)
    {
        return $this->app->em()->getFinder($type);
    }

    /**
     * @param string $identifier
     *
     * @return \XF\Mvc\Entity\Repository
     */
    public function repository($identifier)
    {
        return $this->app->em()->getRepository($identifier);
    }

    /**
     * @param string $class
     *
     * @return \XF\Service\AbstractService
     */
    public function service($class)
    {
        return call_user_func_array([$this->app, 'service'], func_get_args());
    }
}