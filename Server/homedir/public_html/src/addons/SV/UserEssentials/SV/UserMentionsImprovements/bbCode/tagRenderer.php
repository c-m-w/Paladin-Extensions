<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\SV\UserMentionsImprovements\bbCode;

use XF\BbCode\Renderer\Html;

/**
 * Extends \SV\UserMentionsImprovements\bbCode\tagRenderer
 */
class tagRenderer extends XFCP_tagRenderer
{
    protected $svDisplayMiniAvatars;

    public function __construct(Html $renderer, $type)
    {
        parent::__construct($renderer, $type);
        $this->svDisplayMiniAvatars = \XF::options()->svDisplayMiniAvatars;
    }

    /**
     * @param int    $userGroupId
     * @param string $css
     * @param string $link
     * @param string $content
     *
     * @return string
     */
    public function renderTagUserGroupHtml($userGroupId, $css, $link, $content)
    {
        $userGroup = $this->svDisplayMiniAvatars ? \XF::em()->findCached('XF:UserGroup', $userGroupId) : null;
        if (!$userGroup) {
            return parent::renderTagUserGroupHtml(
                $userGroupId,
                $css,
                $link,
                $content
            );
        }

        return \XF::app()->templater()->renderTemplate(
            'public:bb_code_tag_usergroup',
            ['userGroup' => $userGroup]
        );
    }
}
