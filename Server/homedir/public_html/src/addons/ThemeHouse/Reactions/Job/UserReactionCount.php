<?php

namespace ThemeHouse\Reactions\Job;

use XF\Job\AbstractJob;

class UserReactionCount extends AbstractJob
{
    protected $defaultData = [
        'steps' => 0,
        'start' => 0,
        'batch' => 50,
        'truncate' => false,
    ];

    public function run($maxRunTime)
    {
        $db = $this->app->db();

        if ($this->data['truncate']) {
            $db->query('
                TRUNCATE xf_th_reaction_user_count
            ');

            $this->data['truncate'] = false;
        }

        $start = microtime(true);

        $this->data['steps']++;

        $ids = $db->fetchAllColumn($db->limit(
                "
                SELECT DISTINCT react_user_id AS user_id
                FROM xf_th_reacted_content
                WHERE react_user_id > ?
                ORDER BY react_user_id
            ", $this->data['batch']
            ), $this->data['start'])
            +
            $db->fetchAllColumn($db->limit(
                "
                SELECT DISTINCT content_user_id AS user_id
                FROM xf_th_reacted_content
                WHERE content_user_id > ?
                ORDER BY content_user_id
            ", $this->data['batch']
            ), $this->data['start']);

        if (empty($ids)) {
            return $this->complete();
        }

        $userReactionCountRepo = $this->app->repository('ThemeHouse\Reactions:UserReactionCount');
        $done = 0;

        foreach ($ids AS $id) {
            if (microtime(true) - $start >= $maxRunTime) {
                break;
            }

            $this->data['start'] = $id;

            $foundCounts = array_merge($db->fetchAll("
                    SELECT reaction_id, content_type, COUNT(DISTINCT react_id) AS received
                    FROM xf_th_reacted_content
                    WHERE content_user_id = ? AND is_counted = 1
                    GROUP BY reaction_id, content_type
                ", $id
            ), $db->fetchAll("
                    SELECT reaction_id, content_type, COUNT(DISTINCT react_id) AS given
                    FROM xf_th_reacted_content
                    WHERE react_user_id = ? AND is_counted = 1
                    GROUP BY reaction_id, content_type
                ", $id
            ));

            $counts = [];
            foreach ($foundCounts as $foundCount) {
                $cacheId = $foundCount['reaction_id'] . '|' . $foundCount['content_type'];
                $countType = (isset($foundCount['received']) ? 'received' : 'given');

                $counts[$cacheId][$countType][] = [
                    'userId' => $id,
                    'amount' => $foundCount[$countType],
                    'forceCount' => true
                ];
            }

            foreach ($counts as $cacheId => $count) {
                list($reactionId, $contentType) = explode('|', $cacheId);
                $userReactionCountRepo->updateUserReactionCounts($reactionId, $contentType, $count);
            }

            $done++;
        }

        /* Rebuilding for the current batch might've taken a lot less longer than the next batch will,
         * due to the fact that the current batch doesn't have any reactions. Trying to account for that
         * by halfing the calculated optimal. Not guaranteed to solve the memory problem, but should help
         * out.
         */
        $this->data['batch'] = (int)($this->calculateOptimalBatch($this->data['batch'], $done, $start, $maxRunTime,
                1000) / 2);

        return $this->resume();
    }

    public function getStatusMessage()
    {
        $actionPhrase = \XF::phrase('rebuilding');
        $typePhrase = \XF::phrase('th_rebuild_user_reaction_count_reactions');
        return sprintf('%s... %s (%s)', $actionPhrase, $typePhrase, $this->data['start']);
    }

    public function canCancel()
    {
        return true;
    }

    public function canTriggerByChoice()
    {
        return true;
    }
}