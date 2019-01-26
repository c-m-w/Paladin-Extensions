<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\Entity;

use XF\Mvc\Entity\Structure;

/*
 * A trait for mentionable entities.
 */
trait Mentionable
{
    /**
     * @return string
     */
    public function getContentMentionRelation()
    {
        return 'Mentions';
    }

    /**
     * @param $require
     * @return \SV\UserEssentials\Entity\ContentMentions
     */
    public function getContentMentions($require)
    {
        $relationName = $this->getContentMentionRelation();
        if ($require)
        {
            return $this->getRelationOrDefault($relationName);
        }

        return !empty($this->_relations[$relationName]) ? $this->_relations[$relationName] : null;
    }

    /**
     * Adds mentioned user IDs to the content mentions entity.
     *
     * @param \XF\Service\AbstractService|Mentionable $preparer
     * @return null|ContentMentions
     */
    public function addContentMentions($preparer)
    {
        $mentionIds = [];
        if (is_callable([$preparer, 'getExplicitMentionedUserIds']))
        {
            /** @noinspection PhpUndefinedMethodInspection */
            $mentionIds = $preparer->getExplicitMentionedUserIds();
        }
        else if (is_callable([$preparer, 'getMentionedUserIds']))
        {
            /** @noinspection PhpUndefinedMethodInspection */
            $mentionIds = $preparer->getMentionedUserIds(false);
        }

        $groupMentionIds = [];
        $implicitMentionIds = [];
        if (is_callable([$preparer, 'getMentionedUserGroupIds']) && is_callable([$preparer, 'getImplicitMentionedUserIds'])) {
            /** @noinspection PhpUndefinedMethodInspection */
            $groupMentionIds = $preparer->getMentionedUserGroupIds();
            /** @noinspection PhpUndefinedMethodInspection */
            $implicitMentionIds = $preparer->getImplicitMentionedUserIds();
        }

        $quotedIds = [];
        if (is_callable([$preparer, 'getQuotedUserIds']))
        {
            /** @noinspection PhpUndefinedMethodInspection */
            $quotedIds = $preparer->getQuotedUserIds();
        }

        if ($mentionIds || $groupMentionIds || $implicitMentionIds || $quotedIds)
        {
            $mentions = $this->getContentMentions(true);
            $mentions->addIds('m', $mentionIds, ['m', 'mgu']);
            $mentions->addIds('mg', $groupMentionIds);
            $mentions->addIds('mgu', $implicitMentionIds, ['m', 'mgu']);
            $mentions->addIds('q', $quotedIds);
            $mentions->saveIfMentionsChanged();

            return $mentions;
        }

        return $this->getContentMentions(false);
    }

    /**
     * @param Structure $structure
     *
     * @return Structure
     */
    public static function getStructure(Structure $structure)
    {
        $structure = parent::getStructure($structure);

        $structure->relations['Mentions'] = [
            'entity'     => 'SV\UserEssentials:ContentMentions',
            'type'       => self::TO_ONE,
            'conditions' => [
                ['content_type', '=', $structure->contentType],
                ['content_id', '=', "\${$structure->primaryKey}"]
            ],
            'primary'    => true
        ];

        return $structure;
    }
}
