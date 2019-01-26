<?php

namespace ThemeHouse\Reactions\MemberStat;

class Reaction
{
	public static function getReactionTypeUsers(\XF\Entity\MemberStat $memberStat, \XF\Finder\User $finder)
	{
        $reactionTypeId = \XF::repository('ThemeHouse\Reactions:ReactionType')->parseMemberStatKey($memberStat->member_stat_key);
        $users = \XF::repository('ThemeHouse\Reactions:UserReactionCount')->getReactionCountForUsers($reactionTypeId);

        return $users;
	}
}