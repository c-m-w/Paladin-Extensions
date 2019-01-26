<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\Service;

/**
 * An interface for mentionable services.
 */
interface MentionableInterface
{
    /**
     * @param array|string|null $types
     *
     * @return array
     */
    public function getNewContentMentions($types = null);
}
