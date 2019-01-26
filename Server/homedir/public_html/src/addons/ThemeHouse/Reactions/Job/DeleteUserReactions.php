<?php

namespace ThemeHouse\Reactions\Job;

use XF\Cli\Command\JobRunnerTrait;
use XF\Job\AbstractJob;

class DeleteUserReactions extends AbstractJob {
    use JobRunnerTrait;

    protected $defaultData = [
        'userId' => null,
        'currentStep' => 0,
        'lastOffset' => 0,
        'start' => 0
    ];

    public function run($maxRunTime)
    {
        $this->data['start']++;

        if(!$this->data['userId']) {
            return $this->complete();
        }

        /** @var \ThemeHouse\Reactions\Service\User\Deleter $deleter */
        $deleter = $this->app->service('ThemeHouse\Reactions:User\Deleter');
        $deleter->setUserId($this->data['userId']);
        $deleter->restoreState($this->data['currentStep'], $this->data['lastOffset']);

        $result = $deleter->delete($maxRunTime);
        if ($result->isCompleted())
        {
            return $this->complete();
        }
        else
        {
            $continueData = $result->getContinueData();
            $this->data['currentStep'] = $continueData['currentStep'];
            $this->data['lastOffset'] = $continueData['lastOffset'];

            return $this->resume();
        }
    }

    public function getStatusMessage()
    {
        $actionPhrase = \XF::phrase('threactions_deleting_user_reactions');
        return sprintf('%s... (%s)', $actionPhrase, $this->data['start']);
    }

    public function canCancel()
    {
        return false;
    }

    public function canTriggerByChoice()
    {
        return false;
    }
}