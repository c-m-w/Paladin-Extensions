<?php

namespace ThemeHouse\Bookmarks\Pub\Controller;

use XF\Mvc\ParameterBag;
use XF\Pub\Controller\AbstractController;

class Bookmark extends AbstractController
{
    public function actionIndex()
    {
        $bookmarkRepo = $this->getBookmarkRepository();
        $visitor = \XF::visitor();


        $page = $this->filterPage();
        $perPage = $this->options()->th_bookmarksPerPage_bookmarks;

        $contentTypes = $bookmarkRepo->getContentTypeOptions(true);
        $contentType = $this->filter('content_type', 'array', array_keys($contentTypes));

        if (empty($contentType)) {
            $contentType = $this->filter('content_type', 'string');
            $contentType = explode(',', $contentType);
        }

        $bookmarkFinder = $bookmarkRepo->findBookmarksForUser($visitor)->forContentType($contentType);
        $bookmarks = $bookmarkFinder->limitByPage($page, $perPage)->fetch();

        $bookmarkRepo->addContentToBookmarks($bookmarks);
        $bookmarks = $bookmarks->filterViewable();

        $pageNavParams = [
            'content_type' => implode(',', $contentType),
        ];

        $viewParams = [
            'bookmarks' => $bookmarks,
            'contentType' => $contentType,
            'contentTypes' => $contentTypes,

            'page' => $page,
            'perPage' => $perPage,
            'totalBookmarks' => $bookmarkFinder->total(),

            'pageNavParams' => $pageNavParams,
        ];

        return $this->view('ThemeHouse\Bookmarks:Bookmark\Index', 'th_bookmark_list_bookmarks', $viewParams);
    }

    public function actionPopup()
    {
        $options = \XF::options();
        $visitor = \XF::visitor();

        if (!$visitor->user_id) {
            return $this->noPermission();
        }

        $bookmarkRepo = $this->getBookmarkRepository();

        $limit = $options->th_popupLimit_bookmarks;

        $bookmarks = $bookmarkRepo->getBookmarksForPopup()->fetch($limit);
        $bookmarkRepo->addContentToBookmarks($bookmarks);
        $bookmarks = $bookmarks->filterViewable();

        if ($options->th_navigationDropdown_bookmarks === 'disabled') {
            return $this->noPermission();
        }

        $viewParams = [
            'bookmarks' => $bookmarks,
        ];
        return $this->view('ThemeHouse\Bookmarks:Bookmark\Popup', 'th_bookmark_popup_bookmarks', $viewParams);
    }

    public function actionConfirm()
    {
        $contentType = $this->filter('content_type', 'string');
        $contentId = $this->filter('content_id', 'uint');

        $visitor = \XF::visitor();

        /** @var \ThemeHouse\Bookmarks\Entity\Bookmark $bookmark */
        $bookmark = $this->em()->create('ThemeHouse\Bookmarks:Bookmark');

        $bookmark->content_type = $contentType;
        $bookmark->content_id = $contentId;

        return $this->addEditBookmark($bookmark);
    }

    public function actionEdit(ParameterBag $params)
    {
        $bookmark = $this->assertBookmarkExistsForUser($params['bookmark_id']);

        return $this->addEditBookmark($bookmark);
    }

    public function actionSave(ParameterBag $params)
    {
        $visitor = \XF::visitor();

        if ($params['bookmark_id']) {
            $bookmark = $this->assertBookmarkExistsForUser($params['bookmark_id']);
        } else {
            $contentId = $this->filter('content_id', 'uint');
            $contentType = $this->filter('content_type', 'string');
            /** @var \ThemeHouse\Bookmarks\Entity\Bookmark $bookmark */
            $bookmark = $this->em()->create('ThemeHouse\Bookmarks:Bookmark');

            $bookmark->content_type = $contentType;
            $bookmark->content_id = $contentId;
            $bookmark->user_id = $visitor->user_id;
        }

        $content = $bookmark->Content;

        if (!$content->canBookmark()) {
            return $this->noPermission();
        }

        /** @var \ThemeHouse\Bookmarks\Repository\Bookmark $bookmarkRepo */
        $bookmarkRepo = $this->repository('ThemeHouse\Bookmarks:Bookmark');

        $handler = $bookmarkRepo->getHandlerForContentType($bookmark->content_type);
        if (!$handler) {
            return $this->error(\XF::phrase('th_this_content_cannot_be_bookmarked_bookmarks'));
        }

        $this->bookmarkSaveProcess($bookmark)->run();

        $redirect = $this->filter('redirect', 'string');
        if (!$redirect) {
            $redirect = $handler->getContentUrl($content);
        }

        return $this->redirect($redirect);
    }

    protected function bookmarkSaveProcess(\ThemeHouse\Bookmarks\Entity\Bookmark $bookmark)
    {
        $input = $this->filter([
            'note' => 'str',
            'sticky' => 'bool',
            'public' => 'bool',
        ]);

        $form = $this->formAction();
        $form->basicEntitySave($bookmark, $input);

        return $form;
    }

    public function actionDelete(ParameterBag $params)
    {
        $bookmark = $this->assertBookmarkExistsForUser($params['bookmark_id']);
        $content = $bookmark->Content;

        if (!$content) {
            $bookmark->delete();
            return $this->notFound();
        }

        $handler = $bookmark->getHandler();

        if ($this->isPost()) {
            $handler->preDeleteBookmark($bookmark, $error);

            if ($error) {
                return $this->error($error);
            }

            $bookmark->delete();

            $handler->postDeleteBookmark($bookmark);

            return $this->redirect($this->buildLink('bookmarks'));
        }

        $viewParams = [
            'bookmark' => $bookmark,

            'handler' => $handler,
            'content' => $bookmark->Content,
        ];

        return $this->view('ThemeHouse\Bookmarks:Bookmark:Delete', 'th_bookmark_delete_bookmarks', $viewParams);
    }

    protected function addEditBookmark(\ThemeHouse\Bookmarks\Entity\Bookmark $bookmark)
    {
        /** @var \ThemeHouse\Bookmarks\Repository\Bookmark $bookmarkRepo */
        $bookmarkRepo = $this->repository('ThemeHouse\Bookmarks:Bookmark');

        $handler = $bookmarkRepo->getHandlerForContentType($bookmark->content_type);
        if (!$handler) {
            return $this->error(\XF::phrase('th_this_content_cannot_be_bookmarked_bookmarks'));
        }

        $content = $handler->getContent($bookmark->content_id);
        if (!$content) {
            return $this->notFound();
        }

        if (!$content->canBookmark()) {
            return $this->noPermission();
        }

        $viewParams = [
            'bookmark' => $bookmark,

            'handler' => $bookmark->getHandler(),
            'content' => $bookmark->Content,

            'contentType' => $bookmark->content_type,
            'contentId' => $bookmark->content_id,

            'redirect' => $this->filter('redirect', 'string'),
        ];

        return $this->view('ThemeHouse\Bookmarks:Bookmark:Create', 'th_bookmark_edit_bookmarks', $viewParams);
    }

    /**
     * @param $id
     * @param \XF\Entity\User $user
     *
     * @return \ThemeHouse\Bookmarks\Entity\Bookmark
     */
    protected function assertBookmarkExistsForUser($id, \XF\Entity\User $user = null)
    {
        if (!$user) {
            $user = \XF::visitor();
        }

        $bookmark = $this->assertBookmarkExists($id);

        if ($bookmark->user_id !== $user->user_id) {
            throw $this->exception(
                $this->notFound(\XF::phrase('requested_page_not_found'))
            );
        }

        return $bookmark;
    }

    /**
     * @param $id
     * @param \XF\Entity\User $user
     *
     * @return \ThemeHouse\Bookmarks\Entity\Bookmark
     */
    protected function assertBookmarkExists($id)
    {
        return $this->assertRecordExists('ThemeHouse\Bookmarks:Bookmark', $id);
    }

    /**
     * @return \ThemeHouse\Bookmarks\Repository\Bookmark
     */
    protected function getBookmarkRepository()
    {
        return $this->repository('ThemeHouse\Bookmarks:Bookmark');
    }
}