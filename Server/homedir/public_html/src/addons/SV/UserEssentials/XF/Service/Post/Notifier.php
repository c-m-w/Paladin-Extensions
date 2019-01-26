<?php

namespace SV\UserEssentials\XF\Service\Post;



/**
 * Extends \XF\Service\Post\Notifier
 */
class Notifier extends XFCP_Notifier
{
    protected $onlySendMentions = false;

    public function setOnlySendMentions($onlySendMentions)
    {
        $this->onlySendMentions = $onlySendMentions;
    }

    public function setupFromJobData(array $data)
    {
        parent::setupFromJobData($data);
        $this->onlySendMentions = empty($data['onlySendMentions']) ? false : $data['onlySendMentions'];
    }

    public function getJobData()
    {
        $data = parent::getJobData();
        $data['onlySendMentions'] = $this->onlySendMentions;

        return $data;
    }


    protected function loadNotifiers()
    {
        $notifiers = parent::loadNotifiers();
        if ($this->onlySendMentions)
        {
            $notifiers = [
                'quote' => $notifiers['quote'],
                'mention' => $notifiers['mention'],
            ];
        }

        return $notifiers;
    }
}