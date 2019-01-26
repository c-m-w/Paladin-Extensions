<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\XF\BbCode\Renderer;
use XF\Str\Formatter;
use XF\Template\Templater;

/**
 * Extends \XF\BbCodeRenderer\Html
 */
class Html extends XFCP_Html
{
    protected $svDisplayMiniAvatars;

    public function __construct(Formatter $formatter, Templater $templater)
    {
        parent::__construct($formatter, $templater);
        $this->svDisplayMiniAvatars = \XF::options()->svDisplayMiniAvatars;
    }

    /**
     * @noparent
     *
     * @param array  $children
     * @param string $option
     * @param array  $tag
     * @param array  $options
     *
     * @return string
     */
    public function renderTagUser(
        array $children,
        $option,
        array $tag,
        array $options
    ) {
        $content = $this->renderSubTree($children, $options);
        if ($content === '') {
            return '';
        }

        $userId = intval($option);
        if ($userId <= 0) {
            return $content;
        }

        $user = $this->svDisplayMiniAvatars ? \XF::em()->findCached('XF:User', $userId) : null;
        if (!$user) {
            return parent::renderTagUser($children, $option, $tag, $options);
        }

        return $this->templater->renderTemplate('public:bb_code_tag_user', [
            'user' => $user
        ]);
    }
}
