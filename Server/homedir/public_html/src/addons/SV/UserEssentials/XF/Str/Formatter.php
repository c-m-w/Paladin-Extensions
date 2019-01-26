<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\XF\Str;

use SV\UserEssentials\Util\AddOn;

/**
 * Extends \XF\Str\Formatter
 */
class Formatter extends XFCP_Formatter
{
    /**
     * @noparent
     *
     * @param string $string
     *
     * @return string
     */
    public function linkStructuredTextMentions($string)
    {
        $string = $this->moveHtmlToPlaceholders($string, $restorePlaceholders);

        $svDisplayMiniAvatars = \XF::options()->svDisplayMiniAvatars;

        $string = preg_replace_callback(
            '#(?<=^|\s|[\](,]|--|@)@\[(\d+):(\'|"|&quot;|)(.*)\\2\]#iU',
            function (array $match) use ($svDisplayMiniAvatars) {
                $userId = intval($match[1]);
                $user = $svDisplayMiniAvatars ? \XF::em()->findCached('XF:User', $userId) : null;
                if (!$user) {
                    $link = \XF::app()->router('public')->buildLink(
                        'full:members',
                        ['user_id' => $userId]
                    );
                    $username = $this->removeHtmlPlaceholders($match[3]);
                    $username = htmlspecialchars(
                        $username,
                        ENT_QUOTES,
                        'utf-8',
                        false
                    );

                    return sprintf(
                        '<a href="%s" class="username" data-user-id="%d" data-username="%s" data-xf-init="member-tooltip">%s</a>',
                        htmlspecialchars($link),
                        $userId,
                        $username,
                        $username
                    );
                }

                $template = \XF::app()->templater()->renderTemplate(
                    'public:bb_code_tag_user',
                    ['user' => $user]
                );
                // the message may later be run through nl2br(),
                // so we need to strip any newlines
                return str_replace(
                    ["\n", "\r"],
                    '',
                    $template
                );
            },
            $string
        );

        if (AddOn::isActive('SV/UserMentionsImprovements', 2020200)) {
            $string = preg_replace_callback(
                '#(?<=^|\s|[\](,]|--|@)@UG\[(\d+):(\'|"|&quot;|)(.*)\\2\]#iU',
                function (array $match) use ($svDisplayMiniAvatars){
                    $userGroupId = intval($match[1]);
                    $userGroup = $svDisplayMiniAvatars ? \XF::em()->findCached('XF:UserGroup', $userGroupId) : null;
                    if (!$userGroup) {
                        $link = \XF::app()->router()->buildLink(
                            'full:members/usergroup',
                            ['user_group_id' => $userGroupId]
                        );
                        $title = $this->removeHtmlPlaceholders($match[3]);
                        $title = htmlspecialchars($title, ENT_QUOTES, 'utf-8', false);

                        return sprintf(
                            '<a href="%s" class="usergroup">%s</a>',
                            htmlspecialchars($link),
                            $title
                        );
                    }

                    $template = \XF::app()->templater()->renderTemplate(
                        'public:bb_code_tag_usergroup',
                        ['userGroup' => $userGroup]
                    );
                    // the message may later be run through nl2br(),
                    // so we need to strip any newlines
                    return str_replace(
                        ["\n", "\r"],
                        '',
                        $template
                    );
                },
                $string
            );
        }

        $string = $restorePlaceholders($string);
        return $string;
    }
}
