<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\XF\Str;

/**
 * Extends \XF\Str\MentionFormatter
 */
class MentionFormatter extends XFCP_MentionFormatter
{
    /**
     * @param string $message
     *
     * @return string
     */
    public function getMentionsPlainTextFromBbCode($message)
    {
        return preg_replace(
            '/\[(user|usergroup)[^\]]*\](.+)\[\/\\1\]/isU',
            '$2',
            $message
        );
    }

    /**
     * @param string $message
     *
     * @return string
     */
    public function getMentionsPlainTextFromStructuredText($message)
    {
        return preg_replace(
            '/@(UG)?\[\d+:([^\]]+)\]/isU',
            '$2',
            $message
        );
    }
}
