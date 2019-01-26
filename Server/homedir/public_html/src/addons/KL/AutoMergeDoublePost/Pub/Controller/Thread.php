<?php

namespace KL\AutoMergeDoublePost\Pub\Controller;

use XF\Entity\Post;
use XF\Mvc\ParameterBag;
use XF\Service\Post\Editor;

class Thread extends XFCP_Thread
{
    /**
     * @param ParameterBag $params
     * @return \XF\Mvc\Reply\Redirect|\XF\Mvc\Reply\View
     * @throws \XF\Mvc\Reply\Exception
     */
    public function actionAddReply(ParameterBag $params)
    {
        $this->assertPostOnly();

        /** @var \XF\Entity\User $visitor */
        $visitor = \XF::visitor();

        /** @var \XF\Entity\Thread $thread */
        $thread = $this->assertViewableThread($params->thread_id);

        /** @var Post $lastPost */
        $lastPost = $thread->LastPost;

        /* Skip post merge if last post is from a different user */
        if($lastPost->user_id === \XF::visitor()->user_id) {
            /** @var \KL\AutoMergeDoublePost\Repository\MergeTime $mergeRepo */
            $mergeRepo = $this->repository('KL\AutoMergeDoublePost:MergeTime');
            $mergeTime = $mergeRepo->getVisitorMergeTime($thread->Forum);


            if(\XF::$time <= $mergeTime + $lastPost->post_date) {
                return $this->mergeReply($params, $lastPost);
            }
        }

        return parent::actionAddReply($params);
    }

    /**
     * @param ParameterBag $params
     * @param Post $post
     * @return \XF\Mvc\Reply\Error|\XF\Mvc\Reply\Redirect|\XF\Mvc\Reply\View
     */
    protected function mergeReply(ParameterBag $params, Post $post) {
        /** @var \XF\ControllerPlugin\Editor $editorPlugin */
        $editorPlugin = $this->plugin('XF:Editor');
        $secondMessage = $editorPlugin->fromInput('message');

        $time = \XF::$time;
        $message = "{$post->message}\n[automerge]{$time}[/automerge]\n{$secondMessage}";

        $thread = $post->Thread;

        /** @var Editor $editor */
        $editor = $this->service('XF:Post\Editor', $post);
        $editor->setMessage($message);

        $forum = $post->Thread->Forum;
        if ($forum->canUploadAndManageAttachments())
        {
            $editor->setAttachmentHash($this->filter('attachment_hash', 'str'));
        }

        /** @var \XF\Repository\UserAlert $alertRepo */
        $alertRepo = $this->repository('XF:UserAlert');
        $alertRepo->alert(
            $thread->User,
            0, '',
            'user', \XF::visitor()->user_id,
            "post_merged", [
                'post_id' => $post->post_id,
                'thread_id' => $post->thread_id,
                'title' => $thread->title
            ]
        );

        $editor->checkForSpam();

        if (!$editor->validate($errors))
        {
            return $this->error($errors);
        }

        $editor->save();

        $this->finalizePostMerge($editor);

        /* Delete Draft */
        $thread->draft_reply->delete();

        return $this->redirect($this->buildLink('posts', $post));
    }

    /**
     * @param Editor $editor
     * @param \XF\Service\Thread\Editor|null $threadEditor
     */
    protected function finalizePostMerge(Editor $editor, \XF\Service\Thread\Editor $threadEditor = null)
    {

    }

    /**s
     * @param \XF\Entity\Thread $thread
     * @param array $threadChanges Returns a list of whether certain important thread fields are changed
     *
     * @return \XF\Service\Thread\Editor
     */
    protected function setupFirstPostThreadMerge(\XF\Entity\Thread $thread, &$threadChanges)
    {
        /** @var \XF\Service\Thread\Editor $threadEditor */
        $threadEditor = $this->service('XF:Thread\Editor', $thread);

        $prefixId = $this->filter('prefix_id', 'uint');
        if ($prefixId != $thread->prefix_id && !$thread->Forum->isPrefixUsable($prefixId))
        {
            $prefixId = 0; // not usable, just blank it out
        }
        $threadEditor->setPrefix($prefixId);

        $threadEditor->setTitle($this->filter('title', 'str'));

        $customFields = $this->filter('custom_fields', 'array');
        $threadEditor->setCustomFields($customFields);

        $threadChanges = [
            'title' => $thread->isChanged(['title', 'prefix_id']),
            'customFields' => $thread->isChanged('custom_fields')
        ];

        return $threadEditor;
    }
}