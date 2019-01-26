<?php

namespace ThemeHouse\Reactions\Repository;

use XF\Mvc\Entity\Finder;
use XF\Mvc\Entity\Repository;
use XF\Mvc\Entity\Entity;

class UserReactionCount extends Repository
{
    /**
     * @param integer $userId
     * @param integer $reactionId
     * @param string $contentType
     * @return Finder
     */
    public function findUserReactionCountsByReactionIdContentTypeId($userId, $reactionId, $contentType)
    {
        return $this->finder('ThemeHouse\Reactions:UserReactionCount')
            ->where([
                'user_id' => $userId,
                'reaction_id' => $reactionId,
                'content_type' => $contentType,
            ]
        );
    }

    public function updateUserReactionCounts($reactionId, $contentType, array $counts = array())
    {
        $reactionCounts = [];

        $countTypes = ['received', 'given'];
        foreach ($countTypes as $countType) {
            if (array_key_exists($countType, $counts)) {
                $field = 'count_' . $countType;

                foreach ($counts[$countType] as $entry) {
                    $reactionCount = $this->findUserReactionCountsByReactionIdContentTypeId($entry['userId'], $reactionId, $contentType)->fetchOne();
                    if (empty($reactionCount)) {
                        $reactionCount = $this->em->create('ThemeHouse\Reactions:UserReactionCount');
                        $reactionCount->user_id = $entry['userId'];
                        $reactionCount->reaction_id = $reactionId;
                        $reactionCount->content_type = $contentType;
                    }

                    if (isset($entry['forceCount'])) {
                        $reactionCount->$field = $entry['amount'] ?: 0;
                    } else {
                        $reactionCount->$field += $entry['amount'] ?: 0;
                    }

                    $reactionCount->save();
                    $reactionCounts[] = $reactionCount;
                }
            }
        }

        return $reactionCounts;
    }

    public function getUserReactionCounts($userId)
    {
        $reactions = $this->finder('ThemeHouse\Reactions:Reaction')->where('enabled', '=', 1)->fetch();
        $reactionCounts = $this->finder('ThemeHouse\Reactions:UserReactionCount')->where('user_id', '=', $userId)->fetch();

        $return = [];

        foreach ($reactions as $reaction) {
            $return[$reaction->reaction_id] = [
                'reaction' => $reaction,
                'count_given' => 0,
                'count_received' => 0,
            ];
        }

        foreach ($reactionCounts as $reactionCount) {
            if (!isset($return[$reactionCount->reaction_id])) {
                continue;
            }
            $return[$reactionCount->reaction_id]['count_given'] = $return[$reactionCount->reaction_id]['count_given'] + $reactionCount->count_given;
            $return[$reactionCount->reaction_id]['count_received'] = $return[$reactionCount->reaction_id]['count_received'] + $reactionCount->count_received;
        }

        return $return;
    }

    public function getReactionCountForUsers($reactionTypeId = null)
    {
        $reactions = [];
        foreach (\XF::app()->container('reactions') as $reaction) {
            if ($reactionTypeId === null || $reaction['reaction_type_id'] == $reactionTypeId) {
                $reactions[$reaction['reaction_id']] = $reaction;
            }
        }

        $updateRes = $this->db()->query('
            SELECT user.*, COUNT(`th_reaction_user_count`.count_given) as count_given, COUNT(`th_reaction_user_count`.count_received) as count_received
            FROM xf_th_reaction_user_count AS th_reaction_user_count
            LEFT JOIN xf_user AS user ON
                (th_reaction_user_count.user_id = user.user_id)
            WHERE th_reaction_user_count.reaction_id IN(' . $this->db()->quote(array_keys($reactions)) . ')
            GROUP BY th_reaction_user_count.user_id
        ');

        $users = [];
        while ($update = $updateRes->fetch()) {
            $users[$update['user_id']] = [
                'count_given' => $update['count_given'],
                'count_received' => $update['count_received'],
                'user' => $update
            ];
        }

        return $users;
    }
}