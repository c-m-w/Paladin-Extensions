<?php

namespace ThemeHouse\Reactions\Repository;

use XF\Mvc\Entity\Finder;
use XF\Mvc\Entity\Repository;

class ReactionType extends Repository
{
    /**
     * @return Finder
     */
    public function findReactionTypesForList()
    {
        return $this->finder('ThemeHouse\Reactions:ReactionType')
            ->order('display_order');
    }

    public function getReactionTypeList()
    {
        $reactionTypes = $this->findReactionTypesForList()->fetch();

        return $reactionTypes->toArray();
    }

    public function getReactionTypeCacheData()
    {
        $reactionTypes = $this->finder('ThemeHouse\Reactions:ReactionType')
            ->order(['display_order', 'title'])
            ->fetch();

        $cache = [];

        foreach ($reactionTypes AS $reactionTypeId => $reactionType) {
            $reactionType = $reactionType->toArray();

            $cache[$reactionTypeId] = $reactionType;
        }

        return $cache;
    }

    public function rebuildReactionTypeCache()
    {
        $cache = $this->getReactionTypeCacheData();
        \XF::registry()->set('reactionTypes', $cache);

        $this->repository('XF:Style')->updateAllStylesLastModifiedDate();

        return $cache;
    }

    public function getNotableMemberEntry($reactionTypeId)
    {
        return $this->finder('XF:MemberStat')
            ->where('member_stat_key', $this->buildMemberStatKey($reactionTypeId))->fetchOne();
    }

    public function updateNotableMemberEntry(\ThemeHouse\Reactions\Entity\ReactionType $reactionType)
    {
        if (!$memberStat = $this->getNotableMemberEntry($reactionType->reaction_type_id)) {
            $memberStat = $this->em->create('XF:MemberStat');
        }

        $memberStat->bulkSet([
            'member_stat_key' => $this->buildMemberStatKey($reactionType->reaction_type_id),
            'callback_class' => 'ThemeHouse\Reactions\MemberStat\Reaction',
            'callback_method' => 'getReactionTypeUsers',
            'sort_order' => '',
            'display_order' => (1000 * $reactionType->display_order),
            'addon_id' => 'ThemeHouse/Reactions',
            'cache_lifetime' => 0
        ]);

        return $memberStat->save();
    }

    public function deleteNotableMemberEntry(\ThemeHouse\Reactions\Entity\ReactionType $reactionType)
    {
        if (!$memberStat = $this->getNotableMemberEntry($reactionType->reaction_type_id)) {
            return false;
        }

        $memberStat->delete();
        return true;
    }

    public function parseMemberStatKey($memberStatKey)
    {
        return str_replace(['th_', '_reaction_type'], '', $memberStatKey);
    }

    public function buildMemberStatKey($reactionTypeId)
    {
        return 'th_' . $reactionTypeId . '_reaction_type';
    }
}