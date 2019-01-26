<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\XF\Finder;

/**
 * Extends \XF\Finder\ProfilePost
 */
class ProfilePost extends XFCP_ProfilePost
{
    /**
     * @param bool $withProfile
     *
     * @return \XF\Finder\ProfilePost
     */
    public function forFullView($withProfile = false)
    {
        $this->with('Mentions');

        return parent::forFullView($withProfile);
    }
}
