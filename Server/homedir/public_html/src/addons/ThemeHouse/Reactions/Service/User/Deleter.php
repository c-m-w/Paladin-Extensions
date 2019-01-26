<?php

namespace ThemeHouse\Reactions\Service\User;

use ThemeHouse\Reactions\React\Post;
use ThemeHouse\Reactions\XF\Entity\Thread;
use XF\Entity\User;
use XF\MultiPartRunnerTrait;
use XF\Service\AbstractService;

class Deleter extends AbstractService
{
    use MultiPartRunnerTrait;

    protected $userId;

    public function getUserId()
    {
        return $this->userId;
    }

    public function setUserId($userId)
    {
        $this->userId = $userId;
    }

    protected $steps = [
        'stepDeleteReactedContentData',
        'stepDeleteReactionUserCount',
        'stepPruneThreadFirstPostReactCacheData',
        'stepPruneConversationFirstMessageReactCacheData',
        'stepPrunePostReactUsersCacheData',
        'stepPruneMessageReactUserCacheData',
        'stepPruneProfilePostReactUserCacheData',
        'stepPruneProfilePostCommentReactUserCacheData'
    ];

    protected $xfrmSteps = [
        'stepPruneResourceUpdateReactUserCacheData'
    ];

    protected $xfmgSteps = [
        'stepPruneMediaItemReactUserCacheData',
        'stepPruneMediaCommentReactUserCacheData',
        'stepPruneAlbumReactUserCacheData',
    ];

    protected function getSteps()
    {
        $steps = $this->steps;

        if (!empty($this->app->registry()['addOns']['XFRM'])) {
            $steps = array_merge($steps, $this->xfrmSteps);
        }
        if (!empty($this->app->registry()['addOns']['XFMG'])) {
            $steps = array_merge($steps, $this->xfmgSteps);
        }

        return $steps;
    }

    public function delete($maxRunTime = 0)
    {
        if (!$this->userId) {
            throw new \LogicException("No user ID provided");
        }

        $this->db()->beginTransaction();
        $result = $this->runLoop($maxRunTime);
        $this->db()->commit();

        return $result;
    }

    protected $stepSize = 500;

    /**
     * @param $entityType
     * @param $dbTable
     * @param $idColumn
     * @param $lastOffset
     * @param $maxRunTime
     * @return null
     * @throws \XF\PrintableException
     */
    protected function pruneReactUsersCacheForEntity($entityType, $lastOffset, $maxRunTime, $column = 'react_users')
    {
        $start = microtime(true);

        $entity = $this->em()->create($entityType);
        $idColumn = $entity->structure()->primaryKey;
        $dbTable = $entity->structure()->table;
        $end = $this->db()->fetchOne("SELECT MAX({$idColumn}) FROM {$dbTable}");
        $currentOffset = $lastOffset ? $lastOffset : 0;
        $userId = $this->getUserId();

        while ($currentOffset <= $end) {
            $entity = $this->em()->find($entityType, $currentOffset);

            if ($entity) {
                $reactUsers = $entity->getValue($column);

                if ($reactUsers) {
                    foreach ($reactUsers as $key => $reactUser) {
                        if(isset($reactUser['user_id'])) {
                            if ($reactUser['user_id'] == $userId) {
                                unset($reactUsers[$key]);
                            }
                        }
                    }
                    $entity->$column = $reactUsers;
                    $entity->save();
                }
            }

            $currentOffset++;
            if ($maxRunTime && microtime(true) - $start > $maxRunTime) {
                return $currentOffset;
            }
        }

        return null;
    }

    /**
     * @param $lastOffset
     * @param $maxRunTime
     * @return bool|null
     * @throws \XF\PrintableException
     */
    public function stepDeleteReactedContentData($lastOffset, $maxRunTime)
    {
        $start = microtime(true);
        $userId = $this->getUserId();

        while ($reactedContent = $this->finder('ThemeHouse\Reactions:ReactedContent')->where('react_user_id', '=',
            $userId)->fetchOne()) {
            $reactedContent->delete();

            if ($maxRunTime && microtime(true) - $start > $maxRunTime) {
                return true; // Continue this task
            }
        }

        return null; // finished
    }

    /**
     * @param $lastOffset
     * @param $maxRunTime
     * @return bool|null
     * @throws \XF\PrintableException
     */
    public function stepDeleteReactionUserCount($lastOffset, $maxRunTime)
    {
        $start = microtime(true);
        $userId = $this->getUserId();

        while ($reactionCount = $this->finder('ThemeHouse\Reactions:UserReactionCount')->where('user_id', '=',
            $userId)->fetchOne()) {
            $reactionCount->delete();

            if ($maxRunTime && microtime(true) - $start > $maxRunTime) {
                return true; // Continue this task
            }
        }

        return null; // finished
    }

    ############### THREAD & POST CACHES ###############

    /**
     * @param $lastOffset
     * @param $maxRunTime
     * @return mixed
     * @throws \XF\PrintableException
     */
    public function stepPruneThreadFirstPostReactCacheData($lastOffset, $maxRunTime)
    {
        return $this->pruneReactUsersCacheForEntity('XF:Thread', $lastOffset, $maxRunTime, 'first_react_users');
    }

    /**
     * @param $lastOffset
     * @param $maxRunTime
     * @return null
     * @throws \XF\PrintableException
     */
    public function stepPrunePostReactUsersCacheData($lastOffset, $maxRunTime)
    {
        return $this->pruneReactUsersCacheForEntity('XF:Post', $lastOffset, $maxRunTime);
    }

    ############### CONVERSATION CACHES ###############

    /**
     * @param $lastOffset
     * @param $maxRunTime
     * @return null
     * @throws \XF\PrintableException
     */
    public function stepPruneConversationFirstMessageReactCacheData($lastOffset, $maxRunTime)
    {
        return $this->pruneReactUsersCacheForEntity('XF:ConversationMaster', $lastOffset, $maxRunTime,
            'first_react_users');
    }

    /**
     * @param $lastOffset
     * @param $maxRunTime
     * @return null
     * @throws \XF\PrintableException
     */
    public function stepPruneMessageReactUserCacheData($lastOffset, $maxRunTime)
    {
        return $this->pruneReactUsersCacheForEntity('XF:ConversationMessage', $lastOffset, $maxRunTime);
    }

    ############### PROFILE POST & COMMENT CACHES ###############

    /**
     * @param $lastOffset
     * @param $maxRunTime
     * @return null
     * @throws \XF\PrintableException
     */
    public function stepPruneProfilePostReactUserCacheData($lastOffset, $maxRunTime)
    {
        return $this->pruneReactUsersCacheForEntity('XF:ProfilePost', $lastOffset, $maxRunTime);
    }

    /**
     * @param $lastOffset
     * @param $maxRunTime
     * @return null
     * @throws \XF\PrintableException
     */
    public function stepPruneProfilePostCommentReactUserCacheData($lastOffset, $maxRunTime)
    {
        return $this->pruneReactUsersCacheForEntity('XF:ProfilePostComment', $lastOffset, $maxRunTime);
    }

    ############### XFRM CACHES ###############

    /**
     * @param $lastOffset
     * @param $maxRunTime
     * @throws \XF\PrintableException
     */
    public function stepPruneResourceUpdateReactUserCacheData($lastOffset, $maxRunTime)
    {
        $this->pruneReactUsersCacheForEntity('XFRM:ResourceUpdate', $lastOffset, $maxRunTime);
    }

    ############### XFMG CACHES ###############

    /**
     * @param $lastOffset
     * @param $maxRunTime
     * @throws \XF\PrintableException
     */
    public function stepPruneMediaItemReactUserCacheData($lastOffset, $maxRunTime)
    {
        $this->pruneReactUsersCacheForEntity('XFMG:MediaItem', $lastOffset, $maxRunTime);
    }

    /**
     * @param $lastOffset
     * @param $maxRunTime
     * @throws \XF\PrintableException
     */
    public function stepPruneMediaCommentReactUserCacheData($lastOffset, $maxRunTime)
    {
        $this->pruneReactUsersCacheForEntity('XFMG:Comment', $lastOffset, $maxRunTime);
    }

    /**
     * @param $lastOffset
     * @param $maxRunTime
     * @throws \XF\PrintableException
     */
    public function stepPruneAlbumReactUserCacheData($lastOffset, $maxRunTime)
    {
        $this->pruneReactUsersCacheForEntity('XFMG:Album', $lastOffset, $maxRunTime);
    }
}