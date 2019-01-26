<?php

namespace KL\AutoMergeDoublePost\Pub\Controller;

use XF\Mvc\ParameterBag;

class Thread extends XFCP_Thread
{
    public function actionAddReply(ParameterBag $params)
    {
        $this->assertPostOnly();

        $visitor = \XF::visitor();
        $thread = $this->assertViewableThread($params->thread_id, ['Watch|' . $visitor->user_id]);

        $lastPost = $thread->LastPost;

        if ($lastPost->user_id === $visitor->user_id) {
            if(!$visitor->hasPermission('klAMDP', 'klAMDPBypassMerge')) {
                $hours = $visitor->hasPermission('klAMDP', 'klAMDPMergeTime');

                if($hours === -1) {
                    $time = \XF::$time;
                }
                else {
                    $time = \XF::$time - $hours * 3600;
                }

                /** @var \XF\ControllerPlugin\Editor $plugin */
                $plugin = $this->plugin('XF:Editor');
                $message = $plugin->fromInput('message');

                if($lastPost->post_date >= $time) {
                    $phrase = \XF::Phrase('kl_amdp_merged');
                    $lastPost->message .= "\n\n---- " . $phrase->render() . " ----\n\n" . $message;
                    $lastPost->last_edit_date = \XF::$time;
                    $lastPost->edit_count++;
                    $lastPost->last_edit_user_id = $visitor->user_id;
                    $lastPost->save();

                    $confirmation = \XF::phrase('kl_amdp_your_message_has_been_automatically_merged');
                    return $this->redirect($this->buildLink('posts', $lastPost), $confirmation);
                }
            }
        }

        return parent::actionAddReply($params);
    }
}