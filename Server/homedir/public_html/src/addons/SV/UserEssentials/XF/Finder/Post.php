<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\XF\Finder;

/**
 * Extends \XF\Finder\Post
 */
class Post extends XFCP_Post
{
    /**
     * @return \XF\Finder\Post
     */
    public function forFullView()
    {
        $this->with('Mentions');

        return parent::forFullView();
    }
}
