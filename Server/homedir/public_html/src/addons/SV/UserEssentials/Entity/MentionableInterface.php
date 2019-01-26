<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\Entity;

/**
 * An interface for mentionable entities.
 */
interface MentionableInterface
{
    /**
     * @return string
     */
    public function getContentMentionRelation();

    /**
     * @param bool $require
     * @return \SV\UserEssentials\Entity\ContentMentions
     */
    public function getContentMentions($require);

    /**
     * Adds mentioned user IDs to the content mentions entity.
     *
     * @param \XF\Service\AbstractService|Mentionable $preparer
     * @return null|\SV\UserEssentials\Entity\ContentMentions
     */
    public function addContentMentions($preparer);
}
